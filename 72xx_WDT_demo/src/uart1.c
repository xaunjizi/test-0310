#include "CBM7216.h"
#include "stdio.h"


uint8 g_UTRBuffer[256] = 0;//��������buffer
uint8 g_URLength = 0 , g_UTLength = 0 ;//֡����
bit g_URXFlg=0;//֡������ɱ�־ 



/*  
function �����ڳ�ʼ��
parameter ��
	format ��
			bit6-5:00-��У�顢01��У�顢10-żУ�顢11-��żУ��
			bit4��0-ֹͣλ1bit��1-ֹͣλ2bit
			bit3-0������λ 1000-8λ��0111-7λ��0110-6λ��0101-5λ������-��ֹ
	bpr��UBPR = CLKUART1 / bpr - 1��
	  16M:	115200 - 0x8A
                  
*/
void Uart1Init(uint8 format,uint16 bpr,uint16 timeoutcnt )
{
		MDLCKCR_UART1EN = 1 << 4;   //ʹ�ܴ���ʱ��
		UCR1 = 0;
	
	  UTX1DMACR = 0 << 0;  //����ģʽλ��ͨģʽ
	  URX1DMACR = 0 << 0;  //����ģʽλ��ͨģʽ
		USETR1 = format ;
		UBPRL1 = (bpr & 0x00ff) >> 0;
		UBPRH1 = (bpr & 0xff00) >> 8;
	  UCR1 = (0 << 2 ) | (1 << 1) | (1 << 0);       //����������UBPRL/H���á�ʹ�ܽ��ա�ʹ�ܷ���
		USR1 = 0x00;
	  UIER1 = (0 << 7)|(1 << 6) |( 1 << 3);                  //��ͨģʽ��������жϽ�ֹʹ�ܡ���������ж�ʹ�ܡ�֡�����ʱʹ��
		IRQ3ER_UART1INT = 1 << 2;                
		if(timeoutcnt>0)
		{
			URX1TMOUT=timeoutcnt;
			UCR1_RXTMOUTEN =(1<< 4);
		}
	  EX3 = 1;
	  EA = 1;
}



/*  
function �����ڷ���1byte����             
*/
void UartSendByte(uint8 dat)
{
	UTX1DR = dat; 
	while( 0x00 == USR1_TXDONE);   //�ȴ��������
}


/*  
function �����ڷ����ַ���             
*/
void UartPrintf(uint8 *p)
{
	while( *p != 0)           
	{
			UartSendByte(*(p++));
	}
}

/*  
function ��������0-9ת����   ASCLL���'0'-'9',         
*/
void uartSendAsc(uint8 dat) {
//   UartSendByte(dat+0x30);     //��Ч 0x30=48��ӦASCLL��'0'
	   UartSendByte(dat+'0'); 
}


/*  
function ������ASCLL�����ִ�,         
*/
void Uart1SendAscNum(uint16 dat)
{
	 if(dat/10000 != 0)             uartSendAsc(dat/10000);
	 if(dat%10000/1000 != 0)        uartSendAsc(dat%10000/1000);
	 if(dat%10000%1000/100 != 0)    uartSendAsc(dat%10000%1000/100);
	 if(dat%10000%1000%100/10 != 0) uartSendAsc(dat%10000%1000%100/10);
	  uartSendAsc(dat%10);

}


/* 
ʮ����ת��λ16�����ַ���ʽ����   

*/
char hexStr[]="0123456789ABCDEF";            //16���ƶ�Ӧ���
void printDec2Hex(uint32 num)
{
	char cs[9] , cs1[9] ;
	uint8 j = 8 , i = 8 ;
	
	do      
	{
		cs1[--i] = hexStr[num%16] ;  //��λ��ʼ�棬���ڴӵ�λ��ʼ������PC�պ���ʾ��λ��ǰ����λ�ں�
		num /= 16;
	}
	while(num);
	if(i%2) cs1[--i] = '0';        //���λ��Ϊ1����ʾ�ַ�0
	
	cs1[8] = '\0';
	
	UartPrintf(&cs1[i]);    //�����λi��ʼ���ͣ����λ��һ���ڵ�0λ
}






/*   �ض���printf����      */
char putchar(char c)
{
		UartSendByte(c);
		return c;

}



/*  
function ������MDA��ʼ��
parameter ��
	format ��
			bit6-5:00-��У�顢01��У�顢10-żУ�顢11-��żУ��
			bit4��0-ֹͣλ1bit��1-ֹͣλ2bit
			bit3-0������λ 1000-8λ��0111-7λ��0110-6λ��0101-5λ������-��ֹ
	bpr��UBPR = CLKUART1 / bpr - 1��
	  48M:	115200 - 0x01A0��19200 - 0x09C3��9600 - 0x1387�� 4800 - 0x270F
	txLengh�����ͻ�������С   �����128byte��
	rxLengh�����ջ�������С
	tx_addr��DMA������ʼ��ַ  0x00-0x600(1536Byte)
  rx_addr��DMA������ʼ��ַ  0x00-0x600(1536Byte)               
*/
void Uart1DMAInit(uint8 format,uint16 bpr ,uint8 txLengh,uint8 rxLengh,uint16 tx_addr,uint16 rx_addr,uint8 timeoutcnt)
{
		MDLCKCR_UART1EN = 1 << 4;   //ʹ�ܴ���ʱ��
		UCR1 = 0;
		UTX1DMACR = ((txLengh-1) << 1) | (0x01);           //���ͻ�������С������ģʽλDMAģʽ
		UTX1DMAADDRL = (tx_addr & 0x00ff);          //DMA������ʼ��ַ
		UTX1DMAADDRH = (tx_addr & 0xff00) >> 8;
	  URX1DMACR = ((rxLengh-1) << 1) |(0x01);           //���ջ�������С������ģʽλDMAģʽ
		URX1DMAADDRL = (rx_addr & 0x00ff);           //DMA������ʼ��ַ  
		URX1DMAADDRH = (rx_addr & 0xff00) >> 8;
		USETR1 = format ;
		UBPRL1 = (bpr & 0x00ff) >> 0;
		UBPRH1 = (bpr & 0xff00) >> 8;
	  UCR1 = (0 << 2 ) | (1 << 1) | (1 << 0);       //����������UBPRL/H���á�ʹ�ܽ��ա�ʹ�ܷ���
		USR1 = 0x00;
	  UIER1 = (0 << 5)|(1 << 4);                  //DMAģʽ��������жϽ�ֹʹ�ܡ���������ж�ʹ��
		IRQ3ER_UART1INT = 1 << 2;
		if(timeoutcnt>0)
		{
			URX1TMOUT=timeoutcnt;
			UCR1_RXTMOUTEN =(1<< 4);
			 UIER1|=0x08;
		}
	  EX3 = 1;
	  EA = 1;
}


/*  
function ����ʹ��         
*/
void Uart1DMATxEn(void)
{
		/*-----�û��ڷ�����һ֡ǰ�����ڴ˽�Ҫ���͵�����֡д�뵽����Buffer��------*/
	
	USR1 = 0x40 ;//bit6��д1��0����������������һ֡���ݣ�  ���ɽ���λ����
	UIER1_TXDONEIE = 0x20;//ʹ�ܷ�������ж�
}


/*  
function ����ʹ��         
*/
void Uart1DMARxEn(void)
{
	/*-----�û��ڽ�����һ֡����ǰ�����ڴ˶�������Buffer���Ѿ����յ�������֡------*/
	
	USR1 = 0x20 ;//bit5��д1��0�������Ͽ�ʼ������һ֡����,�û������ڽ�����һ֡����֮ǰ��ȡ�굱ǰ���յ�������֡���������ݽ�������
	UIER1_RXFULLIE = 0x10;//ʹ�ܽ�������ж�
}




