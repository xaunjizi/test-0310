#include "CBM7216.h"


/*  
function ：定时器3初始化
parameter ：
	cmp0 ：timer0定时周期  0x00-0xff
  clksel：时钟选择  0-16M  ，1-800k
	clkdiv：分频系数  bit2-0 000-011 = 2-16分频，1xxx= 输入引脚有效沿作为计数时钟
*/
void Timer3Init(uint16 cmp0,uint8 clksel, uint8 clkdiv)
{
	 uint8 j=200;
		MDLCKCR_TIMEREN = 1 << 2;
	  T3CR_MODE = 0;                    //关闭Timer3
		T3SR = 0x00;
		T3CMP0L = (cmp0 & 0x00ff) >> 0;  //必须先修改T3CMP0L
	  T3CMP0H = (cmp0 & 0xff00) >> 8;
		
//计数时钟使能 时钟选择、读时钟选择、分频系数	
		T3CKCR = (1 << 7) | (clksel << 6) | ((clkdiv & 0x07)<<0);
	//连续脉冲模式，初始低电平，T3CMP0匹配翻转 T3CMP1匹配不翻转
	  T3OCR = (0<<4) | (1<<2) | (0 << 1) | (1<<0);
//配置timer3中断是否使能
		T3CR = (2 << 6) | (3 << 4) | (0 << 3) | (0 << 0) ;
		IRQ0ER_TCM3INT0 = 0x02;         //T3中断0使能
	  IRQ1ER_TCM3INT1 = 0x02;         //T3中断1使能
	  EX0 = 1;
		EX1 = 1;
		EA = 1;
		while(j--){;}
		T3CR_MODE = 6 << 0;             //使能T3定时器模式 
}




/*  
function ：设定定时周期
parameter ：
	cmp0 ：timer3定时周期  0x0000-0xffff
  
*/
void Timer3Set(uint16 cmp0)
{
		T3CMP0L = (cmp0 & 0x00ff) >> 0;  //必须先修改T3CMP0L
	  T3CMP0H = (cmp0 & 0xff00) >> 8;
}


/*  
function ：定时器3PWM初始化
parameter ：
	cmp0 ：timer0定时周期  0x00-0xff
  clksel：时钟选择  0-16M  ，1-800k
	clkdiv：分频系数  bit2-0 000-011 = 2-16分频，1xxx= 输入引脚有效沿作为计数时钟
*/
void Timer3PWMInit(uint16 cmp0,uint16 cmp1,uint8 clksel, uint8 clkdiv)
{
	 uint8 j=200;
		MDLCKCR_TIMEREN = 1 << 2;
	  T3CR = 0;
		T3SR = 0x00;
		T3CMP0L = (cmp0 & 0x00ff) >> 0;  //必须先修改T3CMP0L
	  T3CMP0H = (cmp0 & 0xff00) >> 8;
		T3CMP1L = (cmp1 & 0x00ff) >> 0;  //必须先修改T3CMP1L
	  T3CMP1H = (cmp1 & 0xff00) >> 8;
		
//计数时钟使能 时钟选择、读时钟选择、分频系数	
		T3CKCR = (1 << 7) | (clksel << 6) | ((clkdiv & 0x07)<<0);
	//连续脉冲模式，初始低电平，T3CMP0匹配翻转 T3CMP1匹配不翻转
	  T3OCR = (0<<4) | (1<<2) | (0 << 1) | (1<<0);
//配置timer3中断是否使能
		T3CR = (0 << 6) | (3 << 4) | (0 << 3) | (0 << 0) ;
		IRQ0ER_TCM3INT0 = 0x02;         //T3中断0使能
	  IRQ1ER_TCM3INT1 = 0x02;         //T3中断1使能
	  EX0 = 1;
		EX1 = 1;
		EA = 1;
		while(j--){;}
		T3CR_MODE = 6 << 0;              //使能T3定时器模式 
}


/*  
function ：设定PWM定时周期
parameter ：
	cmp0 ：timer3定时周期  0x0000-0xffff
  
*/
void Timer3PWMSet(uint16 cmp0,uint16 cmp1)
{
		T3CMP0L = (cmp0 & 0x00ff) >> 0;  //必须先修改T3CMP0L
	  T3CMP0H = (cmp0 & 0xff00) >> 8;
		T3CMP1L = (cmp1 & 0x00ff) >> 0;  //必须先修改T3CMP1L
	  T3CMP1H = (cmp1 & 0xff00) >> 8;
}


/*  
function ：定时器3外部计数初始化
parameter ：
	cmp0 ：timer0定时周期  0x00-0xff
  clksel：时钟选择  0-16M  ，1-800k
	clkdiv：分频系数  bit2-0 000-011 = 2-16分频，1xxx= 输入引脚有效沿作为计数时钟
*/
void Timer3CountInit(uint16 cmp0,uint8 clksel)
{
	 uint8 j=200;
		MDLCKCR_TIMEREN = 1 << 2;
	  T3CR = 0;
		T3SR = 0x00;
		T3CMP0L = (cmp0 & 0x00ff) >> 0;  //必须先修改T3CMP0L
	  T3CMP0H = (cmp0 & 0xff00) >> 8;	
//计数时钟使能 时钟选择、读时钟选择、分频系数	
		T3CKCR = (1 << 7) | (clksel << 6) | (0x08<<0);
	//连续脉冲模式，初始低电平，T3CMP0匹配翻转 T3CMP1匹配不翻转
	  T3OCR = (0<<4) | (1<<2) |  (0<<0);
	//配置timer3:CMP1捕获、CMP0比较、使能10中断、CMP0在0反沿有效
		T3CR = (1<<7) | (0 << 6) | (3 << 4) | (0 << 3) | (0 << 0) ;
		IRQ0ER_TCM3INT0 = 0x02;         //T3中断0使能
	  IRQ1ER_TCM3INT1 = 0x02;         //T3中断1使能
	  EX0 = 1;
		EX1 = 1;
		EA = 1;
		while(j--){;}
		T3CR_MODE = 6 << 0;              //使能T3定时器模式 
}


/*  
function ：设定外部计数定时周期
parameter ：
	cmp0 ：timer3定时周期  0x0000-0xffff
  
*/
void Timer3CountSet(uint16 cmp0,uint16 cmp1)
{
		T3CMP0L = (cmp0 & 0x00ff) >> 0;  //必须先修改T3CMP0L
	  T3CMP0H = (cmp0 & 0xff00) >> 8;
}


/*  
function ：读取外部计数
parameter ：void
*/
uint8 Timer3CountRead(void)
{
		return ((T3CNTH << 8) +T3CNTL) ;        //16位计数值
}
