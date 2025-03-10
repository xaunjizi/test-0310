#include "CBM7216.h"

/*  
function ：定时器0初始化
parameter ：
	cmp0 ：timer0定时周期  0x00-0xff
  clksel：时钟选择  0-16M  ，1-800k
	clkdiv：分频系数  bit0-2 000-110 = 2-128分频，111=1分频
*/
void Timer0Init(uint8 cmp0,uint8 clksel, uint8 clkdiv)
{
	 uint16 j=200;																				
		MDLCKCR_TIMEREN = 1 << 2;        																			  //使能timer0模块
		T0CR_TEN = 0 << 0;               																		    //bit0  ,关闭timer0进行配置
		T0SR = 0x00;                     																				//清标志
		T0CMP0 = cmp0;																				                  //timer0定时周期    							
		T0CKCR = (1 << 5) | (clksel << 4) | ((clkdiv &0x07 ) << 0);  					  //开启时钟、选择时钟（M/K）、分频系数
	  T0CR = (0<<4) | (1 << 3) | (0 << 2) | (0 << 1) ;												//bit4配置timer0读计数器模式为0（默认是M级时钟）、中断使能、初始输出电平为低电平、定时器模式
		IRQ2ER_TCM0INT = 1 << 1;             												            //使能外设模块中断
		EX2 = 1   ;                          												            //内核中断
		EA = 1;                              												            //总
	  while(j--){;}                        												            //等待3*tick
	  T0CR_TEN = 1 << 0;                   												            //timer0使能启动
}


/*  
function ：设定定时周期
parameter ：
	cmp0 ：timer0定时周期  0x00-0xff
*/
void Timer0SetCmp0(uint8 cmp0)
{
		T0CMP0 = cmp0;
}

/*  
function ：PWM初始化
parameter ：
	cmp0 ：PWM定时周期  0x00-0xff(cmp0*时钟周期)
  cmp1 ：PWM占空比 = cmp1 / cmp0(初始电平位高电平)、初始为低电平时占空比=（cmp0-cmp1）/ cmp0;
  clksel：时钟选择  0-16M  ，1-800k
	clkdiv：分频系数  bit0-2 000-110 = 2-128分频，111=1分频
*/
void Timer0PWMInit(uint8 cmp0,uint8 cmp1,uint8 clksel, uint8 clkdiv)
{
	  uint8 j=200;
		MDLCKCR_TIMEREN = 1 << 2;                													 //使能timer0模块
		T0CR_TEN = 0;                            													 //bit0  ,关闭timer0进行配置
		T0SR = 0x00;                             													 //清标志
		T0CMP0 = cmp0;
		T0CMP1 = cmp1;
		T0CKCR = (1 << 5) | (clksel << 4) | ((clkdiv &0x07 ) << 0); 			 //开启时钟、选择时钟（M/K）、分频系数
	  T0CR = (clksel << 4) | (1 << 3) | (0 << 2) | (1 << 1) ;						 //bit4配置timer0读计数器模式为clksel时钟、中断使能、初始输出电平为低电平、PWM模式
		IRQ2ER_TCM0INT = 0x02;            										             //使能外设模块中断
		EX2 = 1   ;                       										             //内核中断
		EA = 1;                           										             //总中断
	  while(j--){;}                     										             //等待3*tick
	  T0CR_TEN = 1 << 0;                										             //timer0使能启动
}

/*  
function ：设定PWM周期、占空比
parameter ：
	cmp0 ：PWM定时周期  0x00-0xff
  cmp1 ：PWM占空比 = cmp1 / cmp0(初始电平位高电平)、初始为低电平时占空比=（cmp0-cmp1）/ cmp0;
*/
void Timer0PWMSetCmp0(uint8 cmp0,uint8 cmp1)
{
		T0CMP0 = cmp0;
		T0CMP1 = cmp1;
}