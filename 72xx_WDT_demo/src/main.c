#include "include.h"




void main()
{
	uint8 i;
	sysClkInit(0x01,0x00,0x00,0x00);//IHpllclksel-16m；sysclksel-IH；mclkDiv-1分频；sclk1Div-1分频；
  ioPortInit();
	User_IOInit();
	Timer1Init(125,0,0x06);                        //1ms
	
	Uart1Init(0x08,0x8A,200);             //使能uart中断，115200bps 8bit数据位 1bit停止位 无奇偶校验位  
	P00IOCFG = 0x27; //配置P00通用串口1输出
  P01IOCFG = 0x33; //配置P01通用串口1输入 
	
	wdtInit(0x0c,0x02); //(2^12)*（2+1）*160us
	
	

	while(1)
	{
		
		wdtClear();


	}
}