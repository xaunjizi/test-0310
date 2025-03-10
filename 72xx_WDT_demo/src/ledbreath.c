#include "CBM7216.h"
#include "math.h"
#include "pwm.h"
#include "ledbreath.h"

#define PI	(3.1415926/BREATH_DUTY)
#define BREATH_DUTYSTEP	((BREATH_DUTY)/(BREATH_STEPLEVEL))//ÿһ��ռ�ձ�STEP�ĳ���
/*--------------------------global variable definition-----------------------------*/
uint16 g_breathDutyCnt1 = 0,g_breathDutyCnt2 = 50,g_breathDutyCnt3 = 100,g_breathDutyCnt4 = 150,g_breathDutyCnt5 = 200;//������
uint16 g_breathDutyH1 = 0,g_breathDutyH2 = 0,g_breathDutyH3 = 0,g_breathDutyH4 = 0,g_breathDutyH5 = 0;//g_breathDutyHΪ��Ч��ƽ��ȣ�������LED�Ƶĵ�ƽ���

/*********************************************************************************** 
Function   : void breath1(void)
Description: ����pwm1ռ�ձȣ���BREATH_REFRESH1��ˢ�¼��ʱ��������             
Input      : No      
Output     : No	                  
Return     : No
************************************************************************************/
void breath1(void)
{
	g_breathDutyCnt1 += BREATH_DUTYSTEP ;
	if(g_breathDutyCnt1 > BREATH_DUTY)
	{
		g_breathDutyCnt1 = 0 ;
	}
	g_breathDutyH1 = BREATH_DUTY*sin(g_breathDutyCnt1*PI) ;
	pwm1Set(BREATH_DUTY-g_breathDutyH1,g_breathDutyH1) ;
}

/*********************************************************************************** 
Function   : void breath2(void)
Description: ����pwm2ռ�ձȣ���BREATH_REFRESH2��ˢ�¼��ʱ��������             
Input      : No      
Output     : No	                  
Return     : No
************************************************************************************/
void breath2(void)
{
	g_breathDutyCnt2 += BREATH_DUTYSTEP ;
	if(g_breathDutyCnt2 > BREATH_DUTY)
	{
		g_breathDutyCnt2 = 0 ;
	}
	g_breathDutyH2 = BREATH_DUTY*sin(g_breathDutyCnt2*PI) ;
	pwm2Set(BREATH_DUTY-g_breathDutyH2,g_breathDutyH2) ;//ע��PWM2��ռ�ձ���8λ�ģ�g_breathDutyHΪ��Ч��ƽ��ȣ�������LED�Ƶĵ�ƽ���
}

/*********************************************************************************** 
Function   : void breath3(void)
Description: ����pwm3ռ�ձȣ���BREATH_REFRESH3��ˢ�¼��ʱ��������             
Input      : No      
Output     : No	                  
Return     : No
************************************************************************************/
void breath3(void)
{
	g_breathDutyCnt3 += BREATH_DUTYSTEP ;
	if(g_breathDutyCnt3 > BREATH_DUTY)
	{
		g_breathDutyCnt3 = 0 ;
	}
	g_breathDutyH3 = BREATH_DUTY*sin(g_breathDutyCnt3*PI) ;
	pwm3Set(BREATH_DUTY-g_breathDutyH3,g_breathDutyH3) ;
}

/*********************************************************************************** 
Function   : void breath4(void)
Description: ����pwm4ռ�ձȣ���BREATH_REFRESH4��ˢ�¼��ʱ��������             
Input      : No      
Output     : No	                  
Return     : No
************************************************************************************/
void breath4(void)
{
	g_breathDutyCnt4 += BREATH_DUTYSTEP ;
	if(g_breathDutyCnt4 > BREATH_DUTY)
	{
		g_breathDutyCnt4 = 0 ;
	}
	g_breathDutyH4 = BREATH_DUTY*sin(g_breathDutyCnt4*PI) ;
	pwm4Set(BREATH_DUTY-g_breathDutyH4,g_breathDutyH4) ;//ע��PWM4��ռ�ձ���8λ�ģ�g_breathDutyHΪ��Ч��ƽ��ȣ�������LED�Ƶĵ�ƽ���
}

/*********************************************************************************** 
Function   : void breath5(void)
Description: ����pwm5ռ�ձȣ���BREATH_REFRESH5��ˢ�¼��ʱ��������             
Input      : No      
Output     : No	                  
Return     : No
************************************************************************************/
void breath5(void)
{
	g_breathDutyCnt5 += BREATH_DUTYSTEP ;
	if(g_breathDutyCnt5 > BREATH_DUTY)
	{
		g_breathDutyCnt5 = 0 ;
	}
	g_breathDutyH5 = BREATH_DUTY*sin(g_breathDutyCnt5*PI) ;
	pwm5Set(BREATH_DUTY-g_breathDutyH5,g_breathDutyH5) ;
}
