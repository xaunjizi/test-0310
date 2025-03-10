#include "CBM7216.h"



/*  
function ����ʱ��1��ʼ��
parameter ��
	cmp0 ��timer0��ʱ����  0x00-0xff
  clksel��ʱ��ѡ��  0-16M  ��1-800k
	clkdiv����Ƶϵ��  bit3-0 0000-0111 = 2-256��Ƶ��1000=1��Ƶ  ��
	    1001-������ ��1010-�½��ء�1011-˫���ء�1100~1111-1��Ƶ
*/
void Timer1Init(uint8 cmp,uint8 clksel, uint8 clkdiv)
{
	 uint8 j=200;										
		MDLCKCR_TIMEREN = 1 << 2;           																 //ʹ��timer1ģ��
		T1CR = 0;                           																 //bit0  ,�ر�timer1��������
		T1SR = 0x00;                        																 //���־
		T1CMP = cmp;
		T1CKCR = (1 << 5) | (clksel << 4) | ((clkdiv &0x0f ) << 0);          //�򿪼���ʱ�ӡ�ʱ������ѡ��M/K������Ƶϵ��
	  T1CR = (clksel << 7) | (1 << 6) | (2 << 4) | (1 << 3) | (0 << 1) ;	 //����timer0��������ģʽ��ƥ�䷭ת����ʱ��ģʽ��ʼ�͵�ƽ��bit5-4�����ж�ʹ�ܡ���ʱ��ģʽ
		IRQ3ER_TCM1INT = 0x02;                      										  	 //ʹ������ģ���ж�
		EX3 = 1   ;                                 										  	 //�ں��жϿ�
		EA = 1;                                     										  	 //���жϿ�
	  while(j--){;}                               										  	 //�ȴ�3*tick
	  T1CR_TEN = 1 << 0;                          										  	 //timer1ʹ������
}


/*  
function ���趨��ʱ����
parameter ��
	cmp0 ��timer1��ʱ����  0x00-0xff
  
*/
void Timer1Set(uint8 cmp0)
{
		T1CMP = cmp0;
}


/*  
function ����ʱ��1PWM��ʼ����
					���ڹ̶�=��0xff + 1��
				  ռ�ձȣ���ʼ�ߵ�ƽ=T1CMP/256  �� ��ʼ�͵�ƽ=��0x100 - T1CMP�� / 256
parameter ��
	cmp ��timer1��ʱ����  0x00-0xff
  clksel��ʱ��ѡ��  0-16M  ��1-800k
	clkdiv����Ƶϵ��  bit3-0 0000-0111 = 2-256��Ƶ��1000=1��Ƶ  ��
	        1001-������ ��1010-�½��ء�1011-˫���ء�1100~1111-1��Ƶ
*/
void Timer1PWMInit(uint8 cmp,uint8 clksel, uint8 clkdiv)
{
	  uint8 j=200;
		MDLCKCR_TIMEREN = 1 << 2;           											           //ʹ��timer1ģ��
		T1CR_TEN = 0;                       											           //bit0  ,�ر�timer1��������
		T1SR = 0x00;                        											           //���־
		T1CMP = cmp;                                                         //װ�ؼ���ֵ
		T1CKCR = (1 << 5) | (clksel << 4) | ((clkdiv &0x0f ) << 0);          //�򿪼���ʱ�ӡ�ʱ������ѡ��M/K������Ƶϵ�� 
	  T1CR = (clksel << 7) | (1 << 6)  | (1 << 3) |(0 << 2) | (1 << 1) ;   //����timer0��������ģʽ��ƥ�䷭ת��PWM��ʼ�͵�ƽ��bit5-4�����ж�ʹ�ܡ�PWMģʽ
		IRQ3ER_TCM1INT = 0x02;                     											     //ʹ������ģ���ж�
		EX3 = 1   ;                                											 		 //�ں�
		EA = 1;                                    											 		 //��
	  while(j--){;}                              											 		 //�ȴ�3*tick
	  T1CR_TEN = 1 << 0;                         											 		 //timer1ʹ������
}											


/*  
function ���趨PWMռ�ձ�
parameter ��
	cmp ������PWMռ�ձȣ���   ��ʼ�ߵ�ƽ=T1CMP/256  �� ��ʼ�͵�ƽ=��0x100 - T1CMP�� / 256
  
*/
void Timer1PWMSet(uint8 cmp)
{
		T1CMP = cmp;         
}



/*  
function ����ʱ���ⲿ�¼�����ʼ����
parameter ��
	cmp ��timer1��ʱ����  0x00-0xff
  clksel��ʱ��ѡ��  0-16M  ��1-800k
	clkdiv����Ƶϵ��  bit3-0 0000-0111 = 2-256��Ƶ��1000=1��Ƶ  ��
	    1001-������ ��1010-�½��ء�1011-˫���ء�1100~1111-1��Ƶ
*/
void Timer1CountInit(uint8 cmp,uint8 clksel, uint8 clkdiv)
{
	 uint8 j=200;
		MDLCKCR_TIMEREN = 1 << 2;           											           //ʹ��timer1ģ��
		T1CR_TEN = 0;                       											           //bit0  ,�ر�timer1��������
		T1SR = 0x00;                        											           //���־
		T1CMP = cmp;                                                         //װ�ؼ���ֵ
		T1CKCR = (1 << 5) | (clksel << 4) | ((clkdiv &0x0f ) << 0);          //��������ʱ�ӡ�ʱ������ѡ�񡢷�Ƶϵ��
	  T1CR = (clksel << 7) | (1 << 6)  | (1 << 3) |(0 << 2) | (0 << 1) ;   //����timer0��������ģʽ��ƥ�䷭ת������ʼ�͵�ƽ��bit5-4�����ж�ʹ�ܡ���ʱ��ģʽ
		IRQ3ER_TCM1INT = 0x02;                     											     //ʹ������ģ���ж�
		EX3 = 1   ;                                											 		 //�ں�
		EA = 1;                                    											 		 //��
	  while(j--){;}                              											 		 //�ȴ�3*tick
	  T1CR_TEN = 1 << 0;                         											 		 //timer1ʹ������
}


/*  
function ��timer1��ʱ����  
parameter ��
	cmp ��  0x00-0xff
  
*/
void Timer1CountSet(uint8 cmp)
{
		T1CMP = cmp;
}


/*  
function ����ȡtimer1��ǰ����ֵ
parameter ��

*/
uint8 readTimer1Counter(void)
{
	idata volatile uint8 Tcnt0 ,Tcnt1 ,Tcnt2;
	idata uint8 i = 3;
	while(i--)           
	{

		Tcnt0 = T1CNT;
		Tcnt1 = T1CNT;
		Tcnt2 = T1CNT;
		if((Tcnt0==Tcnt1) || (Tcnt0==Tcnt2))  //�ж��������ֵ����������ȷ
		{
			return Tcnt0;
		}
		else if(Tcnt1==Tcnt2)
		{
			return Tcnt1;
		}
	}
	return 0;
	
//	return T1CNT;
}

