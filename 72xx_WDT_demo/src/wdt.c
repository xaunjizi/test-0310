#include "CBM7216.h"

/*           
功能：WDT初始化
参数：
	div：分频系数[7:4]    0000、0001、1100 = 1、2、4096分频，1101~1111 = 8192分频
	length:周期长度[3：0]  0-15
	
	1、WDT 溢出周期 = 2^CNTDIV* (CNTLEN + 1) * 16 * 10us(T100K)。（160us~21s）
  2、WDT 复位周期 = 2 * 溢出周期 = 2 * 2CNTDIV* (CNTLEN + 1) * 16 * 10us(T100K)。（320us~42s）
*/
void wdtInit(uint8 div, uint8 length)
{
		MDLCKCR_WDTEN = 1 << 0;  //使能WDT
		WDTCR = 0x5A;     //清WDT
	  WDTCR = 0xA5;
	  WDTSETR_CNTDIV = (div & 0x0f) << 4;       //分频
	  WDTSETR_CNTLEN = (length & 0x0f ) << 0;    //长度
		IRQ0ER_WDTINT = 0x04;    //使能WDT模块
	  EX0 = 1;               //使能内核中断
		EA = 1;            //使能总中断
		WDTENR_CNTEN = 1 << 0;  //开始计数
}


/*           
功能：清WDT
*/
void wdtClear(void)
{
		WDTCR = 0x5A;     //清WDT
	  WDTCR = 0xA5;
}


