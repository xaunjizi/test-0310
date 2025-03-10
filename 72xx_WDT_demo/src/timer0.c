#include "CBM7216.h"

/*  
function ����ʱ��0��ʼ��
parameter ��
	cmp0 ��timer0��ʱ����  0x00-0xff
  clksel��ʱ��ѡ��  0-16M  ��1-800k
	clkdiv����Ƶϵ��  bit0-2 000-110 = 2-128��Ƶ��111=1��Ƶ
*/
void Timer0Init(uint8 cmp0,uint8 clksel, uint8 clkdiv)
{
	 uint16 j=200;																				
		MDLCKCR_TIMEREN = 1 << 2;        																			  //ʹ��timer0ģ��
		T0CR_TEN = 0 << 0;               																		    //bit0  ,�ر�timer0��������
		T0SR = 0x00;                     																				//���־
		T0CMP0 = cmp0;																				                  //timer0��ʱ����    							
		T0CKCR = (1 << 5) | (clksel << 4) | ((clkdiv &0x07 ) << 0);  					  //����ʱ�ӡ�ѡ��ʱ�ӣ�M/K������Ƶϵ��
	  T0CR = (0<<4) | (1 << 3) | (0 << 2) | (0 << 1) ;												//bit4����timer0��������ģʽΪ0��Ĭ����M��ʱ�ӣ����ж�ʹ�ܡ���ʼ�����ƽΪ�͵�ƽ����ʱ��ģʽ
		IRQ2ER_TCM0INT = 1 << 1;             												            //ʹ������ģ���ж�
		EX2 = 1   ;                          												            //�ں��ж�
		EA = 1;                              												            //��
	  while(j--){;}                        												            //�ȴ�3*tick
	  T0CR_TEN = 1 << 0;                   												            //timer0ʹ������
}


/*  
function ���趨��ʱ����
parameter ��
	cmp0 ��timer0��ʱ����  0x00-0xff
*/
void Timer0SetCmp0(uint8 cmp0)
{
		T0CMP0 = cmp0;
}

/*  
function ��PWM��ʼ��
parameter ��
	cmp0 ��PWM��ʱ����  0x00-0xff(cmp0*ʱ������)
  cmp1 ��PWMռ�ձ� = cmp1 / cmp0(��ʼ��ƽλ�ߵ�ƽ)����ʼΪ�͵�ƽʱռ�ձ�=��cmp0-cmp1��/ cmp0;
  clksel��ʱ��ѡ��  0-16M  ��1-800k
	clkdiv����Ƶϵ��  bit0-2 000-110 = 2-128��Ƶ��111=1��Ƶ
*/
void Timer0PWMInit(uint8 cmp0,uint8 cmp1,uint8 clksel, uint8 clkdiv)
{
	  uint8 j=200;
		MDLCKCR_TIMEREN = 1 << 2;                													 //ʹ��timer0ģ��
		T0CR_TEN = 0;                            													 //bit0  ,�ر�timer0��������
		T0SR = 0x00;                             													 //���־
		T0CMP0 = cmp0;
		T0CMP1 = cmp1;
		T0CKCR = (1 << 5) | (clksel << 4) | ((clkdiv &0x07 ) << 0); 			 //����ʱ�ӡ�ѡ��ʱ�ӣ�M/K������Ƶϵ��
	  T0CR = (clksel << 4) | (1 << 3) | (0 << 2) | (1 << 1) ;						 //bit4����timer0��������ģʽΪclkselʱ�ӡ��ж�ʹ�ܡ���ʼ�����ƽΪ�͵�ƽ��PWMģʽ
		IRQ2ER_TCM0INT = 0x02;            										             //ʹ������ģ���ж�
		EX2 = 1   ;                       										             //�ں��ж�
		EA = 1;                           										             //���ж�
	  while(j--){;}                     										             //�ȴ�3*tick
	  T0CR_TEN = 1 << 0;                										             //timer0ʹ������
}

/*  
function ���趨PWM���ڡ�ռ�ձ�
parameter ��
	cmp0 ��PWM��ʱ����  0x00-0xff
  cmp1 ��PWMռ�ձ� = cmp1 / cmp0(��ʼ��ƽλ�ߵ�ƽ)����ʼΪ�͵�ƽʱռ�ձ�=��cmp0-cmp1��/ cmp0;
*/
void Timer0PWMSetCmp0(uint8 cmp0,uint8 cmp1)
{
		T0CMP0 = cmp0;
		T0CMP1 = cmp1;
}