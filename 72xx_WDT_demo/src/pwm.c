/************************************************************************************************ 
  Company: Shenzhen Chipsbank Technologies Co., Ltd
  FileName: pwm.c  
  Author: Joe.huang        
  Version : V1.0      
  Date: 20191022
  Description: pwm模块函数

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

  History: //历史修改记录   
	<author>		<time>			<Re_version >			<desc>  
	Joe.huang		20191022		V1.0					初版
	
*************************************************************************************************/
#include "CBM7216.h"



/*      
function  ：PWM初始化
parameter ：
		clkdiv(分频系数): bit2-0  000-111 = 2-256分频
		idle0 ： 初始电平时间
		idle1 ： 反初始电平时间
		假设256分频，idel0=60000；
		pwm电平持续时间 = (div/16M)*idle0=(256/16M)*60000 = 0.96s
*/
void PWM11Init(uint8 clkdiv,uint16 idle0,uint16 idle1)
{
		MDLCKCR_PWMEN = 1 << 6;
		PWM1CR =  (1 << 4) | ((clkdiv & 0x07) << 0);    //初始电平为低电平、分频系数
		PWM1LRL = ( idle0 & 0x00ff) ;            //配置占空比
	  PWM1LRH = ((idle0 & 0xff00) >> 8) ; 
		PWM1HRL = ( idle1 & 0x00ff) ;
	  PWM1HRH = ((idle1 & 0xff00) >> 8) ; 
		PWM1CR_PWM1EN = 1 << 5;               //使能PWM1

}


/******************************pwm1(16位)相关函数**********************************/
/*********************************************************************************** 
Function   : void pwm1Init(uint8 div,uint16 pwml,uint16 pwmh) 
Description: PWM1模块初始化，计数时钟分频设置，脉宽调制(默认输出初始电平为0)
Input      : div: 计数时钟分频数(时钟源是SCLK系统时钟) 
				0 - 2分频、1 - 4分频、2 - 8分频、3 - 16分频、
				4 - 32分频、5 - 64分频、6 - 128分频、7 - 256分频。
			 pwml: 低电平时间=pwml*Tpwm
			 pwmh: 高电平时间=pwmh*Tpwm  
Output     : No	                  
Return     : No
************************************************************************************/
void pwm1Init(uint8 div,uint16 pwml,uint16 pwmh) 
{
	MDLCKCR_PWMEN = 1 << 6 ;//使能PWM模块的时钟
	PWM1CR = (1 << 4) | (div & 0x07);//bit4：0-PWM1初始低电平，1-PWM1初始高电平；div配置计数时钟分频数
	PWM1LRL = pwml & 0x00ff ;//配置PWM1L,PWM1H,调制脉宽
	PWM1LRH = (pwml & 0xff00) >> 8;
	PWM1HRL = pwmh & 0x00ff;
	PWM1HRH = (pwmh & 0xff00) >> 8;
	
}

/*********************************************************************************** 
Function   : void pwm1Set(uint16 pwml,uint16 pwmh) 
Description: PWM1脉宽调制
Input      : pwml: 低电平时间=pwml*Tpwm
			 pwmh: 高电平时间=pwmh*Tpwm  
Output     : No	                  
Return     : No
************************************************************************************/
void pwm1Set(uint16 pwml,uint16 pwmh) 
{
	PWM1LRL = pwml & 0x00ff ;//配置PWM1L,PWM1H,调制脉
	PWM1LRH = (pwml & 0xff00) >> 8;
	PWM1HRL = pwmh & 0x00ff;
	PWM1HRH = (pwmh & 0xff00) >> 8;
}

/*********************************************************************************** 
Function   : void pwm1Dis(void) 
Description: 关闭PWM1输出
Input      : No 
Output     : No	                  
Return     : No
************************************************************************************/
void pwm1Dis(void) 
{
	PWM1CR_PWM1EN = 0 << 5 ;//PWM1_EN=0,关闭PWM1输出
}

/*********************************************************************************** 
Function   : void pwm1En(void) 
Description: 使能PWM1输出
Input      : No 
Output     : No	                  
Return     : No
************************************************************************************/
void pwm1En(void) 
{								
	PWM1CR_PWM1EN = 1 << 5 ;//PWM1_EN=1,使能PWM1输出
}

/*********************************************************************************** 
Function   : void pwm1DTSet(uint8 pwm1DTen,uint8 pwm1invDTen,uint8 DTdiv,uint8 pwm1DTcnt,uint16 pwm1invDTcnt) 
Description: PWM1死区配置
Input      : pwm1DTen: pwm1输出通道的死区时间控制使能位（1有效）;
						 pwm1invDTen：pwm1输出互补通道的死区时间控制使能位（1有效）;
						 DTdiv：pwm135通道的死区时间的时钟分频系数(时钟源为SCLK系统时钟) 
						 pwm1DTcnt：pwm1输出通道的死区时间的时钟个数  死区时间 = pwm1DTcnt*分频后死区时钟 = pwm1DTcnt* DTdiv^2 / SCLK
Output     : No	                  
Return     : No
************************************************************************************/
void pwm1DTSet(uint8 pwm1DTen,uint8 pwm1invDTen,uint8 DTdiv,uint8 pwm1DTcnt,uint16 pwm1invDTcnt) 
{
	PWM135DTCTRL&=0x3c;//清0
	PWM135OUTCR&=0xfc;//PMW1输出PWM1
	PWM135INVOUTCR&=0xfc;//PMW1_INV输出PWM1_INV
	PWM1DTCR=pwm1DTcnt;
	PWM1INVDTCR=pwm1invDTcnt;
	PWM135DTCTRL|=(DTdiv<<6)| (pwm1DTen&0x01) | ((pwm1invDTen<<1)&0x02);
}

/*******************************pwm2(8位)相关函数**********************************/
/*********************************************************************************** 
Function   : void pwm2Init(uint8 div,uint8 pwml,uint8 pwmh)
Description: PWM2模块初始化，计数时钟分频设置，脉宽调制(默认输出初始电平为0)
Input      : div: 计数时钟分频数(时钟源是SCLK系统时钟) 
				0 - 2分频、1 - 4分频、2 - 8分频、3 - 16分频、4 - 32分频、 
			    5 - 64分频、6 - 128分频、7 - 256分频、8 - 512分频、9 - 1024分频、10 - 2048分频、
			    11 - 4096分频、12 - 8192分频、13 - 16384分频、14 - 32768分频、15 - 65536分频
			 pwml: 低电平时间=pwml*Tpwm
			 pwmh: 高电平时间=pwmh*Tpwm  
Output     : No	                  
Return     : No
************************************************************************************/
void pwm2Init(uint8 div,uint8 pwml,uint8 pwmh) 
{
	MDLCKCR_PWMEN = 1 << 6 ;//使能PWM模块的时钟
	PWM2CR = (1 << 4) | ((div & 0x0f) << 0) ;//bit4：0-PWM2初始低电平，1-PWM2初始高电平；div配置计数时钟分频数
	PWM2LR = pwml ;//配置PWM2LR,PWM2HR,调制脉宽
	PWM2HR = pwmh ;	
}

/*********************************************************************************** 
Function   : void pwm2Set(uint8 pwml,uint8 pwmh) 
Description: PWM2脉宽调制
Input      : pwml: 低电平时间=pwml*Tpwm
			 pwmh: 高电平时间=pwmh*Tpwm  
Output     : No	                  
Return     : No
************************************************************************************/								   
void pwm2Set(uint8 pwml,uint8 pwmh) 
{
	PWM2LR = pwml ;//配置PWM2LR,PWM2HR,调制脉宽
	PWM2HR = pwmh ;					 
}

/*********************************************************************************** 
Function   : void pwm2Dis(void) 
Description: 关闭PWM2输出
Input      : No 
Output     : No	                  
Return     : No
************************************************************************************/
void pwm2Dis(void) 
{
	PWM2CR_PWM2EN = 0 << 5 ;//PWM2CR_PWM2EN=0,关闭PWM2输出
}

/*********************************************************************************** 
Function   : void pwm2En(void) 
Description: 使能PWM2输出
Input      : No 
Output     : No	                  
Return     : No
************************************************************************************/
void pwm2En(void) 
{
	PWM2CR_PWM2EN = 1 << 5 ;//PWM2CR_PWM2EN=1,使能PWM2输出
}

/******************************pwm3(16位)相关函数**********************************/
/*********************************************************************************** 
Function   : void pwm3Init(uint8 div,uint16 pwml,uint16 pwmh) 
Description: PWM3模块初始化，计数时钟分频设置，脉宽调制(默认输出初始电平为0)
Input      : div: 计数时钟分频数(时钟源是SCLK系统时钟) 
				0 - 2分频、1 - 4分频、2 - 8分频、3 - 16分频、
				4 - 32分频、5 - 64分频、6 - 128分频、7 - 256分频。
			 pwml: 低电平时间=pwml*Tpwm
			 pwmh: 高电平时间=pwmh*Tpwm  
Output     : No	                  
Return     : No
************************************************************************************/
void pwm3Init(uint8 div,uint16 pwml,uint16 pwmh) 
{
	MDLCKCR_PWMEN = 1 << 6 ;//使能PWM模块的时钟
	PWM3CR = (1 << 4) | (div & 0x07);//bit4：0-PWM3初始低电平，1-PWM3初始高电平；div配置计数时钟分频数
	PWM3LRL = pwml & 0x00ff ;//配置PWM3L,PWM3H,调制脉宽
	PWM3LRH = (pwml & 0xff00) >> 8;
	PWM3HRL = pwmh & 0x00ff;
	PWM3HRH = (pwmh & 0xff00) >> 8;
}

/*********************************************************************************** 
Function   : void pwm3Set(uint16 pwml,uint16 pwmh) 
Description: PWM3脉宽调制
Input      : pwm3: 低电平时间=pwm3*Tpwm
			 pwmh: 高电平时间=pwmh*Tpwm  
Output     : No	                  
Return     : No
************************************************************************************/
void pwm3Set(uint16 pwml,uint16 pwmh) 
{
	PWM3LRL = pwml & 0x00ff ;//配置PWM3L,PWM3H,调制脉
	PWM3LRH = (pwml & 0xff00) >> 8;
	PWM3HRL = pwmh & 0x00ff;
	PWM3HRH = (pwmh & 0xff00) >> 8;
}

/*********************************************************************************** 
Function   : void pwm3Dis(void) 
Description: 关闭PWM3输出
Input      : No 
Output     : No	                  
Return     : No
************************************************************************************/
void pwm3Dis(void) 
{
	PWM3CR&= ~(1 << 5) ;//PWM3_EN=0,关闭PWM3输出
}

/*********************************************************************************** 
Function   : void pwm3En(void) 
Description: 使能PWM3输出
Input      : No 
Output     : No	                  
Return     : No
************************************************************************************/
void pwm3En(void) 
{								
	PWM3CR|= 1 << 5 ;//PWM3_EN=1,使能PWM3输出
}

/*********************************************************************************** 
Function   : void pwm3DTSet(uint8 pwm3DTen,uint8 pwm3invDTen,uint8 DTdiv,uint8 pwm3DTcnt,uint16 pwm3invDTcnt) 
Description: PWM3死区配置
Input      : pwm3DTen: pwm3输出通道的死区时间控制使能位（1有效）;
						 pwm3invDTen：pwm3输出互补通道的死区时间控制使能位（1有效）;
						 DTdiv：pwm135通道的死区时间的时钟分频系数(时钟源为SCLK系统时钟) 
						 pwm3DTcnt：pwm3输出通道的死区时间的时钟个数  死区时间 = pwm3DTcnt*分频后死区时钟 = pwm3DTcnt* DTdiv^2 / SCLK
Output     : No	                  
Return     : No
************************************************************************************/
void pwm3DTSet(uint8 pwm3DTen,uint8 pwm3invDTen,uint8 DTdiv,uint8 pwm3DTcnt,uint16 pwm3invDTcnt) 
{
	PWM135DTCTRL&=0x33;//清0 
	PWM135OUTCR&=0xf3;//PMW3输出PWM3
	PWM135INVOUTCR&=0xf3;//PMW3_INV输出PWM3_INV
	PWM3DTCR=pwm3DTcnt;
	PWM3INVDTCR=pwm3invDTcnt;
	PWM135DTCTRL|=(DTdiv<<6)| ((pwm3DTen<<2)&0x04) | ((pwm3invDTen<<3)&0x08);
}


/*******************************pwm4(8位)相关函数**********************************/
/*********************************************************************************** 
Function   : void pwm4Init(uint8 div,uint8 pwml,uint8 pwmh)
Description: PWM4模块初始化，计数时钟分频设置，脉宽调制(默认输出初始电平为0)
Input      : div: 计数时钟分频数(时钟源是SCLK系统时钟) 
				0 - 2分频、1 - 4分频、2 - 8分频、3 - 16分频、4 - 32分频、 
			    5 - 64分频、6 - 128分频、7 - 256分频、8 - 512分频、9 - 1024分频、10 - 2048分频、
			    11 - 4096分频、12 - 8192分频、13 - 16384分频、14 - 32768分频、15 - 65536分频
			 pwml: 低电平时间=pwml*Tpwm
			 pwmh: 高电平时间=pwmh*Tpwm  
Output     : No	                  
Return     : No
************************************************************************************/
void pwm4Init(uint8 div,uint8 pwml,uint8 pwmh) 
{
	MDLCKCR_PWMEN = 1 << 6 ;//使能PWM模块的时钟
	PWM4CR = (1 << 4) | ((div & 0x0f) << 0) ;//bit4：0-PWM4初始低电平，1-PWM4初始高电平；div配置计数时钟分频数
	PWM4LR = pwml ;//配置PWM4LR,PWM4HR,调制脉宽
	PWM4HR = pwmh ;	
}

/*********************************************************************************** 
Function   : void pwm4Set(uint8 pwml,uint8 pwmh) 
Description: PWM4脉宽调制
Input      : pwml: 低电平时间=pwml*Tpwm
			 pwmh: 高电平时间=pwmh*Tpwm  
Output     : No	                  
Return     : No
************************************************************************************/								   
void pwm4Set(uint8 pwml,uint8 pwmh) 
{
	PWM4LR = pwml ;//配置PWM4LR,PWM4HR,调制脉宽
	PWM4HR = pwmh ;	
}

/*********************************************************************************** 
Function   : void pwm4Dis(void) 
Description: 关闭PWM4输出
Input      : No 
Output     : No	                  
Return     : No
************************************************************************************/
void pwm4Dis(void) 
{
	PWM4CR &= ~(1 << 5) ;//PWM4CR_PWM4EN=0,关闭PWM4输出
}

/*********************************************************************************** 
Function   : void pwm4En(void) 
Description: 使能PWM4输出
Input      : No 
Output     : No	                  
Return     : No
************************************************************************************/
void pwm4En(void) 
{
	PWM4CR |= 1 << 5 ;//PWM4CR_PWM4EN=1,使能PWM4输出
}

/*******************************pwm5(8位)相关函数**********************************/
/*********************************************************************************** 
Function   : void pwm5Init(uint8 div,uint16 pwml,uint16 pwmh) 
Description: PWM3模块初始化，计数时钟分频设置，脉宽调制(默认输出初始电平为0)
Input      : div: 计数时钟分频数(时钟源是SCLK系统时钟) 
				0 - 2分频、1 - 4分频、2 - 8分频、3 - 16分频、
				4 - 32分频、5 - 64分频、6 - 128分频、7 - 256分频。
			 pwml: 低电平时间=pwml*Tpwm
			 pwmh: 高电平时间=pwmh*Tpwm  
Output     : No	                  
Return     : No
************************************************************************************/
void pwm5Init(uint8 div,uint16 pwml,uint16 pwmh) 
{
	MDLCKCR_PWMEN = 1 << 6 ;//使能PWM模块的时钟
	PWM5CR = (1 << 4) | (div & 0x07);//bit4：0-PWM5初始低电平，1-PWM5初始高电平；div配置计数时钟分频数
	PWM5LRL = pwml & 0x00ff ;//配置PWM5L,PWM5H,调制脉宽
	PWM5LRH = (pwml & 0xff00) >> 8;
	PWM5HRL = pwmh & 0x00ff;
	PWM5HRH = (pwmh & 0xff00) >> 8;
}

/*********************************************************************************** 
Function   : void pwm5Set(uint16 pwml,uint16 pwmh) 
Description: PWM5脉宽调制
Input      : pwm5: 低电平时间=pwm5*Tpwm
			 pwmh: 高电平时间=pwmh*Tpwm  
Output     : No	                  
Return     : No
************************************************************************************/
void pwm5Set(uint16 pwml,uint16 pwmh) 
{
	PWM5LRL = pwml & 0x00ff ;//配置PWM5L,PWM5H,调制脉
	PWM5LRH = (pwml & 0xff00) >> 8;
	PWM5HRL = pwmh & 0x00ff;
	PWM5HRH = (pwmh & 0xff00) >> 8;
}

/*********************************************************************************** 
Function   : void pwm5Dis(void) 
Description: 关闭PWM5输出
Input      : No 
Output     : No	                  
Return     : No
************************************************************************************/
void pwm5Dis(void) 
{
	PWM5CR&= ~(1 << 5) ;//PWM5_EN=0,关闭PWM5输出
}

/*********************************************************************************** 
Function   : void pwm5En(void) 
Description: 使能PWM5输出
Input      : No 
Output     : No	                  
Return     : No
************************************************************************************/
void pwm5En(void) 
{								
	PWM5CR|= 1 << 5 ;//PWM5_EN=1,使能PWM5输出
}

/*********************************************************************************** 
Function   : void pwm5DTSet(uint8 pwm5DTen,uint8 pwm5invDTen,uint8 DTdiv,uint8 pwm5DTcnt,uint16 pwm5invDTcnt) 
Description: PWM5死区配置
Input      : pwm5DTen: pwm5输出通道的死区时间控制使能位（1有效）;
						 pwm5invDTen：pwm5输出互补通道的死区时间控制使能位（1有效）;
						 DTdiv：pwm135通道的死区时间的时钟分频系数(时钟源为SCLK系统时钟) 
						 pwm5DTcnt：pwm5输出通道的死区时间的时钟个数  死区时间 = pwm5DTcnt*分频后死区时钟 = pwm5DTcnt* DTdiv^2 / SCLK
Output     : No	                  
Return     : No
************************************************************************************/
void pwm5DTSet(uint8 pwm5DTen,uint8 pwm5invDTen,uint8 DTdiv,uint8 pwm5DTcnt,uint16 pwm5invDTcnt) 
{
	PWM135DTCTRL&=0x0f;//清0 
	PWM135OUTCR&=0xcf;//PMW5输出PWM5
	PWM135INVOUTCR&=0xcf;//PMW5_INV输出PWM5_INV
	PWM5DTCR=pwm5DTcnt;
	PWM5INVDTCR=pwm5invDTcnt;
	PWM135DTCTRL|=(DTdiv<<6)| ((pwm5DTen<<4)&0x10) | ((pwm5invDTen<<5)&0x20);
}


/*********************************************************************************** 
Function   : void pwm135outControl(uint8 pwm_en) 
Description: PWM135通道同步输出控制
Input      : pwm_en：PWM1、PWM1_inv、PWM3、PWM3_inv、PWM5、PWM5_inv输出同步使能位
										 0：同时关闭6通道输出   1：同时使能6通道输出
Output     : No	                  
Return     : No
************************************************************************************/
void pwm135outControl(uint8 pwm_en) 
{
	PWMSYNC=(pwm_en&0x01);
}


