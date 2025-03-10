#include "CBM7216.h"



/****************************************************************************************  
function ：RTC初始化
*****************************************************************************************/
void RtcInit(void)
{
//		MISCR2_RTCCLKSEL = 0 << 5;			//选择内部100K时钟作为工作时钟,0-内部时钟，1-外部晶振
		RTCCR = 0;                			//不使能RTC
		RTCSR = 0x00;             			//清标志位
		RTCCR = 0x7f;             			//使能所有RTC中断
		IRQ2ER_RTCINT = 1 << 2;   			//使能外设模块中断
	  EX2 = 1;                  			//内核中断
		EA = 1;                         //总中断    
		//RTCCR_RTCEN = 1 << 7;        //使能RTC
}

/****************************************************************************************  
function ：RTC时间设置
*****************************************************************************************/
void RtcSetTime(uint8 hour,uint8 mimute,uint8 second)
{
	while(RTCSR_SETEN == 0); //查看一次只能配置一个寄存器
		RTCHDR = hour;
	while(RTCSR_SETEN == 0);
		RTCMDR = mimute;
	while(RTCSR_SETEN == 0);
		RTCSDR = second;
}


/****************************************************************************************   
function ：RTC时间读取
parameter：
		timer：读取时钟缓冲区（数组）
*****************************************************************************************/
void RtcReadTime(uint8 *timer)
{
	do {*timer =RTCHDR ;}      //读一次判断读到的和目前是否一直，如果不一样则一直读
	   while( *timer != RTCHDR);
	timer++;
	do {*timer =RTCMDR ;}
	   while( *timer != RTCMDR);
	timer++;
	do {*timer =RTCSDR ;}
	   while( *timer != RTCSDR);

}

/****************************************************************************************    
function ：RTC闹钟时间设置
parameter： hour,mimute,second
		
*****************************************************************************************/
void RtcSetClockTime(uint8 hour,uint8 mimute,uint8 second)
{
	while(RTCSR_SETEN == 0);
		RTCAHDR = hour;
	while(RTCSR_SETEN == 0);
		RTCAMDR = mimute;
	while(RTCSR_SETEN == 0);
		RTCASDR = second;
}


/****************************************************************************************     
function ：RTC闹钟时间读取
parameter：
		timer：读取时钟缓冲区（数组）
*****************************************************************************************/
void RtcReadClockTime(uint8 *timer)
{
		do {*timer =RTCAHDR ;}      //读一次判断读到的和目前是否一直，如果不一样则一直读
	   while( *timer != RTCAHDR);
	timer++;
	do {*timer =RTCAMDR ;}
	   while( *timer != RTCAMDR);
	timer++;
	do {*timer =RTCASDR ;}
	   while( *timer != RTCASDR);
	
}



/****************************************************************************************   
function ：开启RTC  (一般初始配置时间时先关闭RTC，减少时钟和闹钟之间的误差)
*****************************************************************************************/
void RtcOpen(void)
{
		 RTCCR_RTCEN = 1 << 7;       //使能RTC
}


/****************************************************************************************    
function ：关闭RTC
*****************************************************************************************/
void RtcClose(void)
{
		 RTCCR_RTCEN = 0 << 7;       //禁止使能RTC
}
