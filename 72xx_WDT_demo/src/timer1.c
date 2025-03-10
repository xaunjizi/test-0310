#include "CBM7216.h"



/*  
function ：定时器1初始化
parameter ：
	cmp0 ：timer0定时周期  0x00-0xff
  clksel：时钟选择  0-16M  ，1-800k
	clkdiv：分频系数  bit3-0 0000-0111 = 2-256分频，1000=1分频  、
	    1001-上升沿 、1010-下降沿、1011-双边沿、1100~1111-1分频
*/
void Timer1Init(uint8 cmp,uint8 clksel, uint8 clkdiv)
{
	 uint8 j=200;										
		MDLCKCR_TIMEREN = 1 << 2;           																 //使能timer1模块
		T1CR = 0;                           																 //bit0  ,关闭timer1进行配置
		T1SR = 0x00;                        																 //清标志
		T1CMP = cmp;
		T1CKCR = (1 << 5) | (clksel << 4) | ((clkdiv &0x0f ) << 0);          //打开计数时钟、时钟速率选择（M/K）、分频系数
	  T1CR = (clksel << 7) | (1 << 6) | (2 << 4) | (1 << 3) | (0 << 1) ;	 //配置timer0读计数器模式、匹配翻转、定时器模式初始低电平（bit5-4）、中断使能、定时器模式
		IRQ3ER_TCM1INT = 0x02;                      										  	 //使能外设模块中断
		EX3 = 1   ;                                 										  	 //内核中断开
		EA = 1;                                     										  	 //总中断开
	  while(j--){;}                               										  	 //等待3*tick
	  T1CR_TEN = 1 << 0;                          										  	 //timer1使能启动
}


/*  
function ：设定定时周期
parameter ：
	cmp0 ：timer1定时周期  0x00-0xff
  
*/
void Timer1Set(uint8 cmp0)
{
		T1CMP = cmp0;
}


/*  
function ：定时器1PWM初始化，
					周期固定=（0xff + 1）
				  占空比：初始高电平=T1CMP/256  、 初始低电平=（0x100 - T1CMP） / 256
parameter ：
	cmp ：timer1定时周期  0x00-0xff
  clksel：时钟选择  0-16M  ，1-800k
	clkdiv：分频系数  bit3-0 0000-0111 = 2-256分频，1000=1分频  、
	        1001-上升沿 、1010-下降沿、1011-双边沿、1100~1111-1分频
*/
void Timer1PWMInit(uint8 cmp,uint8 clksel, uint8 clkdiv)
{
	  uint8 j=200;
		MDLCKCR_TIMEREN = 1 << 2;           											           //使能timer1模块
		T1CR_TEN = 0;                       											           //bit0  ,关闭timer1进行配置
		T1SR = 0x00;                        											           //清标志
		T1CMP = cmp;                                                         //装载计数值
		T1CKCR = (1 << 5) | (clksel << 4) | ((clkdiv &0x0f ) << 0);          //打开计数时钟、时钟速率选择（M/K）、分频系数 
	  T1CR = (clksel << 7) | (1 << 6)  | (1 << 3) |(0 << 2) | (1 << 1) ;   //配置timer0读计数器模式、匹配翻转、PWM初始低电平（bit5-4）、中断使能、PWM模式
		IRQ3ER_TCM1INT = 0x02;                     											     //使能外设模块中断
		EX3 = 1   ;                                											 		 //内核
		EA = 1;                                    											 		 //总
	  while(j--){;}                              											 		 //等待3*tick
	  T1CR_TEN = 1 << 0;                         											 		 //timer1使能启动
}											


/*  
function ：设定PWM占空比
parameter ：
	cmp （设置PWM占空比）：   初始高电平=T1CMP/256  、 初始低电平=（0x100 - T1CMP） / 256
  
*/
void Timer1PWMSet(uint8 cmp)
{
		T1CMP = cmp;         
}



/*  
function ：定时器外部事件计数始化，
parameter ：
	cmp ：timer1定时周期  0x00-0xff
  clksel：时钟选择  0-16M  ，1-800k
	clkdiv：分频系数  bit3-0 0000-0111 = 2-256分频，1000=1分频  、
	    1001-上升沿 、1010-下降沿、1011-双边沿、1100~1111-1分频
*/
void Timer1CountInit(uint8 cmp,uint8 clksel, uint8 clkdiv)
{
	 uint8 j=200;
		MDLCKCR_TIMEREN = 1 << 2;           											           //使能timer1模块
		T1CR_TEN = 0;                       											           //bit0  ,关闭timer1进行配置
		T1SR = 0x00;                        											           //清标志
		T1CMP = cmp;                                                         //装载计数值
		T1CKCR = (1 << 5) | (clksel << 4) | ((clkdiv &0x0f ) << 0);          //开启计数时钟、时钟速率选择、分频系数
	  T1CR = (clksel << 7) | (1 << 6)  | (1 << 3) |(0 << 2) | (0 << 1) ;   //配置timer0读计数器模式、匹配翻转）、初始低电平（bit5-4）、中断使能、定时器模式
		IRQ3ER_TCM1INT = 0x02;                     											     //使能外设模块中断
		EX3 = 1   ;                                											 		 //内核
		EA = 1;                                    											 		 //总
	  while(j--){;}                              											 		 //等待3*tick
	  T1CR_TEN = 1 << 0;                         											 		 //timer1使能启动
}


/*  
function ：timer1定时周期  
parameter ：
	cmp ：  0x00-0xff
  
*/
void Timer1CountSet(uint8 cmp)
{
		T1CMP = cmp;
}


/*  
function ：读取timer1当前计数值
parameter ：

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
		if((Tcnt0==Tcnt1) || (Tcnt0==Tcnt2))  //判断如果两个值相等则计数正确
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

