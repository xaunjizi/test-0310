#include "CBM7216.h"
#include "math.h"
#include "pwm.h"
#include "ledbreath.h"

#define PI	(3.1415926/BREATH_DUTY)
#define BREATH_DUTYSTEP	((BREATH_DUTY)/(BREATH_STEPLEVEL))//每一级占空比STEP的长度
/*--------------------------global variable definition-----------------------------*/
uint16 g_breathDutyCnt1 = 0,g_breathDutyCnt2 = 50,g_breathDutyCnt3 = 100,g_breathDutyCnt4 = 150,g_breathDutyCnt5 = 200;//计数器
uint16 g_breathDutyH1 = 0,g_breathDutyH2 = 0,g_breathDutyH3 = 0,g_breathDutyH4 = 0,g_breathDutyH5 = 0;//g_breathDutyH为有效电平宽度，即点亮LED灯的电平宽度

/*********************************************************************************** 
Function   : void breath1(void)
Description: 更新pwm1占空比，以BREATH_REFRESH1的刷新间隔时间来调用             
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
Description: 更新pwm2占空比，以BREATH_REFRESH2的刷新间隔时间来调用             
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
	pwm2Set(BREATH_DUTY-g_breathDutyH2,g_breathDutyH2) ;//注意PWM2的占空比是8位的；g_breathDutyH为有效电平宽度，即点亮LED灯的电平宽度
}

/*********************************************************************************** 
Function   : void breath3(void)
Description: 更新pwm3占空比，以BREATH_REFRESH3的刷新间隔时间来调用             
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
Description: 更新pwm4占空比，以BREATH_REFRESH4的刷新间隔时间来调用             
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
	pwm4Set(BREATH_DUTY-g_breathDutyH4,g_breathDutyH4) ;//注意PWM4的占空比是8位的；g_breathDutyH为有效电平宽度，即点亮LED灯的电平宽度
}

/*********************************************************************************** 
Function   : void breath5(void)
Description: 更新pwm5占空比，以BREATH_REFRESH5的刷新间隔时间来调用             
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
