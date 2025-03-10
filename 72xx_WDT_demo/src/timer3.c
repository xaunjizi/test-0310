#include "CBM7216.h"


/*  
function ����ʱ��3��ʼ��
parameter ��
	cmp0 ��timer0��ʱ����  0x00-0xff
  clksel��ʱ��ѡ��  0-16M  ��1-800k
	clkdiv����Ƶϵ��  bit2-0 000-011 = 2-16��Ƶ��1xxx= ����������Ч����Ϊ����ʱ��
*/
void Timer3Init(uint16 cmp0,uint8 clksel, uint8 clkdiv)
{
	 uint8 j=200;
		MDLCKCR_TIMEREN = 1 << 2;
	  T3CR_MODE = 0;                    //�ر�Timer3
		T3SR = 0x00;
		T3CMP0L = (cmp0 & 0x00ff) >> 0;  //�������޸�T3CMP0L
	  T3CMP0H = (cmp0 & 0xff00) >> 8;
		
//����ʱ��ʹ�� ʱ��ѡ�񡢶�ʱ��ѡ�񡢷�Ƶϵ��	
		T3CKCR = (1 << 7) | (clksel << 6) | ((clkdiv & 0x07)<<0);
	//��������ģʽ����ʼ�͵�ƽ��T3CMP0ƥ�䷭ת T3CMP1ƥ�䲻��ת
	  T3OCR = (0<<4) | (1<<2) | (0 << 1) | (1<<0);
//����timer3�ж��Ƿ�ʹ��
		T3CR = (2 << 6) | (3 << 4) | (0 << 3) | (0 << 0) ;
		IRQ0ER_TCM3INT0 = 0x02;         //T3�ж�0ʹ��
	  IRQ1ER_TCM3INT1 = 0x02;         //T3�ж�1ʹ��
	  EX0 = 1;
		EX1 = 1;
		EA = 1;
		while(j--){;}
		T3CR_MODE = 6 << 0;             //ʹ��T3��ʱ��ģʽ 
}




/*  
function ���趨��ʱ����
parameter ��
	cmp0 ��timer3��ʱ����  0x0000-0xffff
  
*/
void Timer3Set(uint16 cmp0)
{
		T3CMP0L = (cmp0 & 0x00ff) >> 0;  //�������޸�T3CMP0L
	  T3CMP0H = (cmp0 & 0xff00) >> 8;
}


/*  
function ����ʱ��3PWM��ʼ��
parameter ��
	cmp0 ��timer0��ʱ����  0x00-0xff
  clksel��ʱ��ѡ��  0-16M  ��1-800k
	clkdiv����Ƶϵ��  bit2-0 000-011 = 2-16��Ƶ��1xxx= ����������Ч����Ϊ����ʱ��
*/
void Timer3PWMInit(uint16 cmp0,uint16 cmp1,uint8 clksel, uint8 clkdiv)
{
	 uint8 j=200;
		MDLCKCR_TIMEREN = 1 << 2;
	  T3CR = 0;
		T3SR = 0x00;
		T3CMP0L = (cmp0 & 0x00ff) >> 0;  //�������޸�T3CMP0L
	  T3CMP0H = (cmp0 & 0xff00) >> 8;
		T3CMP1L = (cmp1 & 0x00ff) >> 0;  //�������޸�T3CMP1L
	  T3CMP1H = (cmp1 & 0xff00) >> 8;
		
//����ʱ��ʹ�� ʱ��ѡ�񡢶�ʱ��ѡ�񡢷�Ƶϵ��	
		T3CKCR = (1 << 7) | (clksel << 6) | ((clkdiv & 0x07)<<0);
	//��������ģʽ����ʼ�͵�ƽ��T3CMP0ƥ�䷭ת T3CMP1ƥ�䲻��ת
	  T3OCR = (0<<4) | (1<<2) | (0 << 1) | (1<<0);
//����timer3�ж��Ƿ�ʹ��
		T3CR = (0 << 6) | (3 << 4) | (0 << 3) | (0 << 0) ;
		IRQ0ER_TCM3INT0 = 0x02;         //T3�ж�0ʹ��
	  IRQ1ER_TCM3INT1 = 0x02;         //T3�ж�1ʹ��
	  EX0 = 1;
		EX1 = 1;
		EA = 1;
		while(j--){;}
		T3CR_MODE = 6 << 0;              //ʹ��T3��ʱ��ģʽ 
}


/*  
function ���趨PWM��ʱ����
parameter ��
	cmp0 ��timer3��ʱ����  0x0000-0xffff
  
*/
void Timer3PWMSet(uint16 cmp0,uint16 cmp1)
{
		T3CMP0L = (cmp0 & 0x00ff) >> 0;  //�������޸�T3CMP0L
	  T3CMP0H = (cmp0 & 0xff00) >> 8;
		T3CMP1L = (cmp1 & 0x00ff) >> 0;  //�������޸�T3CMP1L
	  T3CMP1H = (cmp1 & 0xff00) >> 8;
}


/*  
function ����ʱ��3�ⲿ������ʼ��
parameter ��
	cmp0 ��timer0��ʱ����  0x00-0xff
  clksel��ʱ��ѡ��  0-16M  ��1-800k
	clkdiv����Ƶϵ��  bit2-0 000-011 = 2-16��Ƶ��1xxx= ����������Ч����Ϊ����ʱ��
*/
void Timer3CountInit(uint16 cmp0,uint8 clksel)
{
	 uint8 j=200;
		MDLCKCR_TIMEREN = 1 << 2;
	  T3CR = 0;
		T3SR = 0x00;
		T3CMP0L = (cmp0 & 0x00ff) >> 0;  //�������޸�T3CMP0L
	  T3CMP0H = (cmp0 & 0xff00) >> 8;	
//����ʱ��ʹ�� ʱ��ѡ�񡢶�ʱ��ѡ�񡢷�Ƶϵ��	
		T3CKCR = (1 << 7) | (clksel << 6) | (0x08<<0);
	//��������ģʽ����ʼ�͵�ƽ��T3CMP0ƥ�䷭ת T3CMP1ƥ�䲻��ת
	  T3OCR = (0<<4) | (1<<2) |  (0<<0);
	//����timer3:CMP1����CMP0�Ƚϡ�ʹ��10�жϡ�CMP0��0������Ч
		T3CR = (1<<7) | (0 << 6) | (3 << 4) | (0 << 3) | (0 << 0) ;
		IRQ0ER_TCM3INT0 = 0x02;         //T3�ж�0ʹ��
	  IRQ1ER_TCM3INT1 = 0x02;         //T3�ж�1ʹ��
	  EX0 = 1;
		EX1 = 1;
		EA = 1;
		while(j--){;}
		T3CR_MODE = 6 << 0;              //ʹ��T3��ʱ��ģʽ 
}


/*  
function ���趨�ⲿ������ʱ����
parameter ��
	cmp0 ��timer3��ʱ����  0x0000-0xffff
  
*/
void Timer3CountSet(uint16 cmp0,uint16 cmp1)
{
		T3CMP0L = (cmp0 & 0x00ff) >> 0;  //�������޸�T3CMP0L
	  T3CMP0H = (cmp0 & 0xff00) >> 8;
}


/*  
function ����ȡ�ⲿ����
parameter ��void
*/
uint8 Timer3CountRead(void)
{
		return ((T3CNTH << 8) +T3CNTL) ;        //16λ����ֵ
}
