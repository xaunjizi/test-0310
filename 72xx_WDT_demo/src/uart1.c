#include "CBM7216.h"
#include "stdio.h"


uint8 g_UTRBuffer[256] = 0;//串口数据buffer
uint8 g_URLength = 0 , g_UTLength = 0 ;//帧长度
bit g_URXFlg=0;//帧接收完成标志 



/*  
function ：串口初始化
parameter ：
	format ：
			bit6-5:00-无校验、01奇校验、10-偶校验、11-奇偶校验
			bit4：0-停止位1bit、1-停止位2bit
			bit3-0：数据位 1000-8位、0111-7位、0110-6位、0101-5位、其他-禁止
	bpr：UBPR = CLKUART1 / bpr - 1；
	  16M:	115200 - 0x8A
                  
*/
void Uart1Init(uint8 format,uint16 bpr,uint16 timeoutcnt )
{
		MDLCKCR_UART1EN = 1 << 4;   //使能串口时钟
		UCR1 = 0;
	
	  UTX1DMACR = 0 << 0;  //发送模式位普通模式
	  URX1DMACR = 0 << 0;  //接收模式位普通模式
		USETR1 = format ;
		UBPRL1 = (bpr & 0x00ff) >> 0;
		UBPRH1 = (bpr & 0xff00) >> 8;
	  UCR1 = (0 << 2 ) | (1 << 1) | (1 << 0);       //波特率依据UBPRL/H设置、使能接收、使能发送
		USR1 = 0x00;
	  UIER1 = (0 << 7)|(1 << 6) |( 1 << 3);                  //普通模式发送完成中断禁止使能、接收完成中断使能、帧间隔超时使能
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
function ：串口发送1byte数据             
*/
void UartSendByte(uint8 dat)
{
	UTX1DR = dat; 
	while( 0x00 == USR1_TXDONE);   //等待发送完成
}


/*  
function ：串口发送字符串             
*/
void UartPrintf(uint8 *p)
{
	while( *p != 0)           
	{
			UartSendByte(*(p++));
	}
}

/*  
function ：把数字0-9转化成   ASCLL码的'0'-'9',         
*/
void uartSendAsc(uint8 dat) {
//   UartSendByte(dat+0x30);     //等效 0x30=48对应ASCLL的'0'
	   UartSendByte(dat+'0'); 
}


/*  
function ：发送ASCLL码数字串,         
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
十进制转化位16进制字符形式发送   

*/
char hexStr[]="0123456789ABCDEF";            //16进制对应码表
void printDec2Hex(uint32 num)
{
	char cs[9] , cs1[9] ;
	uint8 j = 8 , i = 8 ;
	
	do      
	{
		cs1[--i] = hexStr[num%16] ;  //高位开始存，串口从低位开始发，在PC刚好显示高位在前，低位在后
		num /= 16;
	}
	while(num);
	if(i%2) cs1[--i] = '0';        //最高位不为1则显示字符0
	
	cs1[8] = '\0';
	
	UartPrintf(&cs1[i]);    //从最高位i开始发送，最高位不一定在第0位
}






/*   重定向printf（）      */
char putchar(char c)
{
		UartSendByte(c);
		return c;

}



/*  
function ：串口MDA初始化
parameter ：
	format ：
			bit6-5:00-无校验、01奇校验、10-偶校验、11-奇偶校验
			bit4：0-停止位1bit、1-停止位2bit
			bit3-0：数据位 1000-8位、0111-7位、0110-6位、0101-5位、其他-禁止
	bpr：UBPR = CLKUART1 / bpr - 1；
	  48M:	115200 - 0x01A0、19200 - 0x09C3、9600 - 0x1387、 4800 - 0x270F
	txLengh：发送缓冲区大小   （最大128byte）
	rxLengh：接收缓冲区大小
	tx_addr：DMA发送起始地址  0x00-0x600(1536Byte)
  rx_addr：DMA接收起始地址  0x00-0x600(1536Byte)               
*/
void Uart1DMAInit(uint8 format,uint16 bpr ,uint8 txLengh,uint8 rxLengh,uint16 tx_addr,uint16 rx_addr,uint8 timeoutcnt)
{
		MDLCKCR_UART1EN = 1 << 4;   //使能串口时钟
		UCR1 = 0;
		UTX1DMACR = ((txLengh-1) << 1) | (0x01);           //发送缓冲区大小、发送模式位DMA模式
		UTX1DMAADDRL = (tx_addr & 0x00ff);          //DMA发送起始地址
		UTX1DMAADDRH = (tx_addr & 0xff00) >> 8;
	  URX1DMACR = ((rxLengh-1) << 1) |(0x01);           //接收缓冲区大小、接收模式位DMA模式
		URX1DMAADDRL = (rx_addr & 0x00ff);           //DMA接收起始地址  
		URX1DMAADDRH = (rx_addr & 0xff00) >> 8;
		USETR1 = format ;
		UBPRL1 = (bpr & 0x00ff) >> 0;
		UBPRH1 = (bpr & 0xff00) >> 8;
	  UCR1 = (0 << 2 ) | (1 << 1) | (1 << 0);       //波特率依据UBPRL/H设置、使能接收、使能发送
		USR1 = 0x00;
	  UIER1 = (0 << 5)|(1 << 4);                  //DMA模式发送完成中断禁止使能、接收完成中断使能
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
function 发送使能         
*/
void Uart1DMATxEn(void)
{
		/*-----用户在发送下一帧前，先在此将要发送的数据帧写入到发送Buffer里------*/
	
	USR1 = 0x40 ;//bit6：写1清0并马上启动发送下一帧数据；  不可进行位操作
	UIER1_TXDONEIE = 0x20;//使能发送完成中断
}


/*  
function 接收使能         
*/
void Uart1DMARxEn(void)
{
	/*-----用户在接收下一帧数据前，先在此读出接收Buffer里已经接收到的数据帧------*/
	
	USR1 = 0x20 ;//bit5：写1清0，并马上开始接收下一帧数据,用户必需在接收下一帧数据之前读取完当前接收到的数据帧，否则数据将被覆盖
	UIER1_RXFULLIE = 0x10;//使能接收完成中断
}




