/************************************************************************************************ 
  Company: Shenzhen Chipsbank Technologies Co., Ltd
  FileName: pwm.c  
  Author: Joe.huang        
  Version : V1.0      
  Date: 20191022
  Description: pwmģ�麯��

  Function List: 
				void pwm1Init(uint8 div,uint16 pwml,uint16 pwmh);
				void pwm1Set(uint16 pwml,uint16 pwmh);
				void pwm1En(void);
				void pwm1Dis(void);
				void pwm2Init(uint8 div,uint8 pwml,uint8 pwmh);
				void pwm2Set(uint8 pwml,uint8 pwmh);
				void pwm2En(void);
				void pwm2Dis(void);
				void pwm3Init(uint8 div,uint16 pwml,uint16 pwmh);
				void pwm3Set(uint16 pwml,uint16 pwmh);
				void pwm3En(void);
				void pwm3Dis(void);
				void pwm4Init(uint8 div,uint8 pwml,uint8 pwmh);
				void pwm4Set(uint8 pwml,uint8 pwmh);
				void pwm4En(void);
				void pwm4Dis(void);
				void pwm5Init(uint8 div,uint16 pwml,uint16 pwmh);
				void pwm5Set(uint16 pwml,uint16 pwmh);
				void pwm5En(void);
				void pwm5Dis(void);

  History: //��ʷ�޸ļ�¼   
	<author>		<time>			<Re_version >			<desc>  
	Joe.huang		20191022		V1.0					����
	
*************************************************************************************************/
#include "CBM7216.h"



/*      
function  ��PWM��ʼ��
parameter ��
		clkdiv(��Ƶϵ��): bit2-0  000-111 = 2-256��Ƶ
		idle0 �� ��ʼ��ƽʱ��
		idle1 �� ����ʼ��ƽʱ��
		����256��Ƶ��idel0=60000��
		pwm��ƽ����ʱ�� = (div/16M)*idle0=(256/16M)*60000 = 0.96s
*/
void PWM11Init(uint8 clkdiv,uint16 idle0,uint16 idle1)
{
		MDLCKCR_PWMEN = 1 << 6;
		PWM1CR =  (1 << 4) | ((clkdiv & 0x07) << 0);    //��ʼ��ƽΪ�͵�ƽ����Ƶϵ��
		PWM1LRL = ( idle0 & 0x00ff) ;            //����ռ�ձ�
	  PWM1LRH = ((idle0 & 0xff00) >> 8) ; 
		PWM1HRL = ( idle1 & 0x00ff) ;
	  PWM1HRH = ((idle1 & 0xff00) >> 8) ; 
		PWM1CR_PWM1EN = 1 << 5;               //ʹ��PWM1

}


/******************************pwm1(16λ)��غ���**********************************/
/*********************************************************************************** 
Function   : void pwm1Init(uint8 div,uint16 pwml,uint16 pwmh) 
Description: PWM1ģ���ʼ��������ʱ�ӷ�Ƶ���ã��������(Ĭ�������ʼ��ƽΪ0)
Input      : div: ����ʱ�ӷ�Ƶ��(ʱ��Դ��SCLKϵͳʱ��) 
				0 - 2��Ƶ��1 - 4��Ƶ��2 - 8��Ƶ��3 - 16��Ƶ��
				4 - 32��Ƶ��5 - 64��Ƶ��6 - 128��Ƶ��7 - 256��Ƶ��
			 pwml: �͵�ƽʱ��=pwml*Tpwm
			 pwmh: �ߵ�ƽʱ��=pwmh*Tpwm  
Output     : No	                  
Return     : No
************************************************************************************/
void pwm1Init(uint8 div,uint16 pwml,uint16 pwmh) 
{
	MDLCKCR_PWMEN = 1 << 6 ;//ʹ��PWMģ���ʱ��
	PWM1CR = (1 << 4) | (div & 0x07);//bit4��0-PWM1��ʼ�͵�ƽ��1-PWM1��ʼ�ߵ�ƽ��div���ü���ʱ�ӷ�Ƶ��
	PWM1LRL = pwml & 0x00ff ;//����PWM1L,PWM1H,��������
	PWM1LRH = (pwml & 0xff00) >> 8;
	PWM1HRL = pwmh & 0x00ff;
	PWM1HRH = (pwmh & 0xff00) >> 8;
	
}

/*********************************************************************************** 
Function   : void pwm1Set(uint16 pwml,uint16 pwmh) 
Description: PWM1�������
Input      : pwml: �͵�ƽʱ��=pwml*Tpwm
			 pwmh: �ߵ�ƽʱ��=pwmh*Tpwm  
Output     : No	                  
Return     : No
************************************************************************************/
void pwm1Set(uint16 pwml,uint16 pwmh) 
{
	PWM1LRL = pwml & 0x00ff ;//����PWM1L,PWM1H,������
	PWM1LRH = (pwml & 0xff00) >> 8;
	PWM1HRL = pwmh & 0x00ff;
	PWM1HRH = (pwmh & 0xff00) >> 8;
}

/*********************************************************************************** 
Function   : void pwm1Dis(void) 
Description: �ر�PWM1���
Input      : No 
Output     : No	                  
Return     : No
************************************************************************************/
void pwm1Dis(void) 
{
	PWM1CR_PWM1EN = 0 << 5 ;//PWM1_EN=0,�ر�PWM1���
}

/*********************************************************************************** 
Function   : void pwm1En(void) 
Description: ʹ��PWM1���
Input      : No 
Output     : No	                  
Return     : No
************************************************************************************/
void pwm1En(void) 
{								
	PWM1CR_PWM1EN = 1 << 5 ;//PWM1_EN=1,ʹ��PWM1���
}

/*********************************************************************************** 
Function   : void pwm1DTSet(uint8 pwm1DTen,uint8 pwm1invDTen,uint8 DTdiv,uint8 pwm1DTcnt,uint16 pwm1invDTcnt) 
Description: PWM1��������
Input      : pwm1DTen: pwm1���ͨ��������ʱ�����ʹ��λ��1��Ч��;
						 pwm1invDTen��pwm1�������ͨ��������ʱ�����ʹ��λ��1��Ч��;
						 DTdiv��pwm135ͨ��������ʱ���ʱ�ӷ�Ƶϵ��(ʱ��ԴΪSCLKϵͳʱ��) 
						 pwm1DTcnt��pwm1���ͨ��������ʱ���ʱ�Ӹ���  ����ʱ�� = pwm1DTcnt*��Ƶ������ʱ�� = pwm1DTcnt* DTdiv^2 / SCLK
Output     : No	                  
Return     : No
************************************************************************************/
void pwm1DTSet(uint8 pwm1DTen,uint8 pwm1invDTen,uint8 DTdiv,uint8 pwm1DTcnt,uint16 pwm1invDTcnt) 
{
	PWM135DTCTRL&=0x3c;//��0
	PWM135OUTCR&=0xfc;//PMW1���PWM1
	PWM135INVOUTCR&=0xfc;//PMW1_INV���PWM1_INV
	PWM1DTCR=pwm1DTcnt;
	PWM1INVDTCR=pwm1invDTcnt;
	PWM135DTCTRL|=(DTdiv<<6)| (pwm1DTen&0x01) | ((pwm1invDTen<<1)&0x02);
}

/*******************************pwm2(8λ)��غ���**********************************/
/*********************************************************************************** 
Function   : void pwm2Init(uint8 div,uint8 pwml,uint8 pwmh)
Description: PWM2ģ���ʼ��������ʱ�ӷ�Ƶ���ã��������(Ĭ�������ʼ��ƽΪ0)
Input      : div: ����ʱ�ӷ�Ƶ��(ʱ��Դ��SCLKϵͳʱ��) 
				0 - 2��Ƶ��1 - 4��Ƶ��2 - 8��Ƶ��3 - 16��Ƶ��4 - 32��Ƶ�� 
			    5 - 64��Ƶ��6 - 128��Ƶ��7 - 256��Ƶ��8 - 512��Ƶ��9 - 1024��Ƶ��10 - 2048��Ƶ��
			    11 - 4096��Ƶ��12 - 8192��Ƶ��13 - 16384��Ƶ��14 - 32768��Ƶ��15 - 65536��Ƶ
			 pwml: �͵�ƽʱ��=pwml*Tpwm
			 pwmh: �ߵ�ƽʱ��=pwmh*Tpwm  
Output     : No	                  
Return     : No
************************************************************************************/
void pwm2Init(uint8 div,uint8 pwml,uint8 pwmh) 
{
	MDLCKCR_PWMEN = 1 << 6 ;//ʹ��PWMģ���ʱ��
	PWM2CR = (1 << 4) | ((div & 0x0f) << 0) ;//bit4��0-PWM2��ʼ�͵�ƽ��1-PWM2��ʼ�ߵ�ƽ��div���ü���ʱ�ӷ�Ƶ��
	PWM2LR = pwml ;//����PWM2LR,PWM2HR,��������
	PWM2HR = pwmh ;	
}

/*********************************************************************************** 
Function   : void pwm2Set(uint8 pwml,uint8 pwmh) 
Description: PWM2�������
Input      : pwml: �͵�ƽʱ��=pwml*Tpwm
			 pwmh: �ߵ�ƽʱ��=pwmh*Tpwm  
Output     : No	                  
Return     : No
************************************************************************************/								   
void pwm2Set(uint8 pwml,uint8 pwmh) 
{
	PWM2LR = pwml ;//����PWM2LR,PWM2HR,��������
	PWM2HR = pwmh ;					 
}

/*********************************************************************************** 
Function   : void pwm2Dis(void) 
Description: �ر�PWM2���
Input      : No 
Output     : No	                  
Return     : No
************************************************************************************/
void pwm2Dis(void) 
{
	PWM2CR_PWM2EN = 0 << 5 ;//PWM2CR_PWM2EN=0,�ر�PWM2���
}

/*********************************************************************************** 
Function   : void pwm2En(void) 
Description: ʹ��PWM2���
Input      : No 
Output     : No	                  
Return     : No
************************************************************************************/
void pwm2En(void) 
{
	PWM2CR_PWM2EN = 1 << 5 ;//PWM2CR_PWM2EN=1,ʹ��PWM2���
}

/******************************pwm3(16λ)��غ���**********************************/
/*********************************************************************************** 
Function   : void pwm3Init(uint8 div,uint16 pwml,uint16 pwmh) 
Description: PWM3ģ���ʼ��������ʱ�ӷ�Ƶ���ã��������(Ĭ�������ʼ��ƽΪ0)
Input      : div: ����ʱ�ӷ�Ƶ��(ʱ��Դ��SCLKϵͳʱ��) 
				0 - 2��Ƶ��1 - 4��Ƶ��2 - 8��Ƶ��3 - 16��Ƶ��
				4 - 32��Ƶ��5 - 64��Ƶ��6 - 128��Ƶ��7 - 256��Ƶ��
			 pwml: �͵�ƽʱ��=pwml*Tpwm
			 pwmh: �ߵ�ƽʱ��=pwmh*Tpwm  
Output     : No	                  
Return     : No
************************************************************************************/
void pwm3Init(uint8 div,uint16 pwml,uint16 pwmh) 
{
	MDLCKCR_PWMEN = 1 << 6 ;//ʹ��PWMģ���ʱ��
	PWM3CR = (1 << 4) | (div & 0x07);//bit4��0-PWM3��ʼ�͵�ƽ��1-PWM3��ʼ�ߵ�ƽ��div���ü���ʱ�ӷ�Ƶ��
	PWM3LRL = pwml & 0x00ff ;//����PWM3L,PWM3H,��������
	PWM3LRH = (pwml & 0xff00) >> 8;
	PWM3HRL = pwmh & 0x00ff;
	PWM3HRH = (pwmh & 0xff00) >> 8;
}

/*********************************************************************************** 
Function   : void pwm3Set(uint16 pwml,uint16 pwmh) 
Description: PWM3�������
Input      : pwm3: �͵�ƽʱ��=pwm3*Tpwm
			 pwmh: �ߵ�ƽʱ��=pwmh*Tpwm  
Output     : No	                  
Return     : No
************************************************************************************/
void pwm3Set(uint16 pwml,uint16 pwmh) 
{
	PWM3LRL = pwml & 0x00ff ;//����PWM3L,PWM3H,������
	PWM3LRH = (pwml & 0xff00) >> 8;
	PWM3HRL = pwmh & 0x00ff;
	PWM3HRH = (pwmh & 0xff00) >> 8;
}

/*********************************************************************************** 
Function   : void pwm3Dis(void) 
Description: �ر�PWM3���
Input      : No 
Output     : No	                  
Return     : No
************************************************************************************/
void pwm3Dis(void) 
{
	PWM3CR&= ~(1 << 5) ;//PWM3_EN=0,�ر�PWM3���
}

/*********************************************************************************** 
Function   : void pwm3En(void) 
Description: ʹ��PWM3���
Input      : No 
Output     : No	                  
Return     : No
************************************************************************************/
void pwm3En(void) 
{								
	PWM3CR|= 1 << 5 ;//PWM3_EN=1,ʹ��PWM3���
}

/*********************************************************************************** 
Function   : void pwm3DTSet(uint8 pwm3DTen,uint8 pwm3invDTen,uint8 DTdiv,uint8 pwm3DTcnt,uint16 pwm3invDTcnt) 
Description: PWM3��������
Input      : pwm3DTen: pwm3���ͨ��������ʱ�����ʹ��λ��1��Ч��;
						 pwm3invDTen��pwm3�������ͨ��������ʱ�����ʹ��λ��1��Ч��;
						 DTdiv��pwm135ͨ��������ʱ���ʱ�ӷ�Ƶϵ��(ʱ��ԴΪSCLKϵͳʱ��) 
						 pwm3DTcnt��pwm3���ͨ��������ʱ���ʱ�Ӹ���  ����ʱ�� = pwm3DTcnt*��Ƶ������ʱ�� = pwm3DTcnt* DTdiv^2 / SCLK
Output     : No	                  
Return     : No
************************************************************************************/
void pwm3DTSet(uint8 pwm3DTen,uint8 pwm3invDTen,uint8 DTdiv,uint8 pwm3DTcnt,uint16 pwm3invDTcnt) 
{
	PWM135DTCTRL&=0x33;//��0 
	PWM135OUTCR&=0xf3;//PMW3���PWM3
	PWM135INVOUTCR&=0xf3;//PMW3_INV���PWM3_INV
	PWM3DTCR=pwm3DTcnt;
	PWM3INVDTCR=pwm3invDTcnt;
	PWM135DTCTRL|=(DTdiv<<6)| ((pwm3DTen<<2)&0x04) | ((pwm3invDTen<<3)&0x08);
}


/*******************************pwm4(8λ)��غ���**********************************/
/*********************************************************************************** 
Function   : void pwm4Init(uint8 div,uint8 pwml,uint8 pwmh)
Description: PWM4ģ���ʼ��������ʱ�ӷ�Ƶ���ã��������(Ĭ�������ʼ��ƽΪ0)
Input      : div: ����ʱ�ӷ�Ƶ��(ʱ��Դ��SCLKϵͳʱ��) 
				0 - 2��Ƶ��1 - 4��Ƶ��2 - 8��Ƶ��3 - 16��Ƶ��4 - 32��Ƶ�� 
			    5 - 64��Ƶ��6 - 128��Ƶ��7 - 256��Ƶ��8 - 512��Ƶ��9 - 1024��Ƶ��10 - 2048��Ƶ��
			    11 - 4096��Ƶ��12 - 8192��Ƶ��13 - 16384��Ƶ��14 - 32768��Ƶ��15 - 65536��Ƶ
			 pwml: �͵�ƽʱ��=pwml*Tpwm
			 pwmh: �ߵ�ƽʱ��=pwmh*Tpwm  
Output     : No	                  
Return     : No
************************************************************************************/
void pwm4Init(uint8 div,uint8 pwml,uint8 pwmh) 
{
	MDLCKCR_PWMEN = 1 << 6 ;//ʹ��PWMģ���ʱ��
	PWM4CR = (1 << 4) | ((div & 0x0f) << 0) ;//bit4��0-PWM4��ʼ�͵�ƽ��1-PWM4��ʼ�ߵ�ƽ��div���ü���ʱ�ӷ�Ƶ��
	PWM4LR = pwml ;//����PWM4LR,PWM4HR,��������
	PWM4HR = pwmh ;	
}

/*********************************************************************************** 
Function   : void pwm4Set(uint8 pwml,uint8 pwmh) 
Description: PWM4�������
Input      : pwml: �͵�ƽʱ��=pwml*Tpwm
			 pwmh: �ߵ�ƽʱ��=pwmh*Tpwm  
Output     : No	                  
Return     : No
************************************************************************************/								   
void pwm4Set(uint8 pwml,uint8 pwmh) 
{
	PWM4LR = pwml ;//����PWM4LR,PWM4HR,��������
	PWM4HR = pwmh ;	
}

/*********************************************************************************** 
Function   : void pwm4Dis(void) 
Description: �ر�PWM4���
Input      : No 
Output     : No	                  
Return     : No
************************************************************************************/
void pwm4Dis(void) 
{
	PWM4CR &= ~(1 << 5) ;//PWM4CR_PWM4EN=0,�ر�PWM4���
}

/*********************************************************************************** 
Function   : void pwm4En(void) 
Description: ʹ��PWM4���
Input      : No 
Output     : No	                  
Return     : No
************************************************************************************/
void pwm4En(void) 
{
	PWM4CR |= 1 << 5 ;//PWM4CR_PWM4EN=1,ʹ��PWM4���
}

/*******************************pwm5(8λ)��غ���**********************************/
/*********************************************************************************** 
Function   : void pwm5Init(uint8 div,uint16 pwml,uint16 pwmh) 
Description: PWM3ģ���ʼ��������ʱ�ӷ�Ƶ���ã��������(Ĭ�������ʼ��ƽΪ0)
Input      : div: ����ʱ�ӷ�Ƶ��(ʱ��Դ��SCLKϵͳʱ��) 
				0 - 2��Ƶ��1 - 4��Ƶ��2 - 8��Ƶ��3 - 16��Ƶ��
				4 - 32��Ƶ��5 - 64��Ƶ��6 - 128��Ƶ��7 - 256��Ƶ��
			 pwml: �͵�ƽʱ��=pwml*Tpwm
			 pwmh: �ߵ�ƽʱ��=pwmh*Tpwm  
Output     : No	                  
Return     : No
************************************************************************************/
void pwm5Init(uint8 div,uint16 pwml,uint16 pwmh) 
{
	MDLCKCR_PWMEN = 1 << 6 ;//ʹ��PWMģ���ʱ��
	PWM5CR = (1 << 4) | (div & 0x07);//bit4��0-PWM5��ʼ�͵�ƽ��1-PWM5��ʼ�ߵ�ƽ��div���ü���ʱ�ӷ�Ƶ��
	PWM5LRL = pwml & 0x00ff ;//����PWM5L,PWM5H,��������
	PWM5LRH = (pwml & 0xff00) >> 8;
	PWM5HRL = pwmh & 0x00ff;
	PWM5HRH = (pwmh & 0xff00) >> 8;
}

/*********************************************************************************** 
Function   : void pwm5Set(uint16 pwml,uint16 pwmh) 
Description: PWM5�������
Input      : pwm5: �͵�ƽʱ��=pwm5*Tpwm
			 pwmh: �ߵ�ƽʱ��=pwmh*Tpwm  
Output     : No	                  
Return     : No
************************************************************************************/
void pwm5Set(uint16 pwml,uint16 pwmh) 
{
	PWM5LRL = pwml & 0x00ff ;//����PWM5L,PWM5H,������
	PWM5LRH = (pwml & 0xff00) >> 8;
	PWM5HRL = pwmh & 0x00ff;
	PWM5HRH = (pwmh & 0xff00) >> 8;
}

/*********************************************************************************** 
Function   : void pwm5Dis(void) 
Description: �ر�PWM5���
Input      : No 
Output     : No	                  
Return     : No
************************************************************************************/
void pwm5Dis(void) 
{
	PWM5CR&= ~(1 << 5) ;//PWM5_EN=0,�ر�PWM5���
}

/*********************************************************************************** 
Function   : void pwm5En(void) 
Description: ʹ��PWM5���
Input      : No 
Output     : No	                  
Return     : No
************************************************************************************/
void pwm5En(void) 
{								
	PWM5CR|= 1 << 5 ;//PWM5_EN=1,ʹ��PWM5���
}

/*********************************************************************************** 
Function   : void pwm5DTSet(uint8 pwm5DTen,uint8 pwm5invDTen,uint8 DTdiv,uint8 pwm5DTcnt,uint16 pwm5invDTcnt) 
Description: PWM5��������
Input      : pwm5DTen: pwm5���ͨ��������ʱ�����ʹ��λ��1��Ч��;
						 pwm5invDTen��pwm5�������ͨ��������ʱ�����ʹ��λ��1��Ч��;
						 DTdiv��pwm135ͨ��������ʱ���ʱ�ӷ�Ƶϵ��(ʱ��ԴΪSCLKϵͳʱ��) 
						 pwm5DTcnt��pwm5���ͨ��������ʱ���ʱ�Ӹ���  ����ʱ�� = pwm5DTcnt*��Ƶ������ʱ�� = pwm5DTcnt* DTdiv^2 / SCLK
Output     : No	                  
Return     : No
************************************************************************************/
void pwm5DTSet(uint8 pwm5DTen,uint8 pwm5invDTen,uint8 DTdiv,uint8 pwm5DTcnt,uint16 pwm5invDTcnt) 
{
	PWM135DTCTRL&=0x0f;//��0 
	PWM135OUTCR&=0xcf;//PMW5���PWM5
	PWM135INVOUTCR&=0xcf;//PMW5_INV���PWM5_INV
	PWM5DTCR=pwm5DTcnt;
	PWM5INVDTCR=pwm5invDTcnt;
	PWM135DTCTRL|=(DTdiv<<6)| ((pwm5DTen<<4)&0x10) | ((pwm5invDTen<<5)&0x20);
}


/*********************************************************************************** 
Function   : void pwm135outControl(uint8 pwm_en) 
Description: PWM135ͨ��ͬ���������
Input      : pwm_en��PWM1��PWM1_inv��PWM3��PWM3_inv��PWM5��PWM5_inv���ͬ��ʹ��λ
										 0��ͬʱ�ر�6ͨ�����   1��ͬʱʹ��6ͨ�����
Output     : No	                  
Return     : No
************************************************************************************/
void pwm135outControl(uint8 pwm_en) 
{
	PWMSYNC=(pwm_en&0x01);
}


