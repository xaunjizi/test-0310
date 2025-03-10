#include "CBM7216.h"

/* 
功能 ：外部中断初始化
参数：
	sel：触发方式
			000-高电平、001-低电平、101-上升沿、110-下降沿、111-双边沿、其他-不触发
			外部中断5特殊，000、001无效
	  n：选择外部中断：0-5
*/
void EXTInit(uint8 sel ,uint8 n)
{
		IFLTCNTR =   0x0f;   //设置滤波时间
//	uint8  Trg = 0x03,EXTn = 0;
	switch(n)	
	{
     case 0:
		 {
				XINT01TRGR =  sel << 0 ;   //触发方式
				IRQ0ER_XINT0 = 1 << 0;        //使能外部中断0
			  EX0 = 1;               //使能内核中断0
			}  break ;
		 case 1:
		 {
				XINT01TRGR = sel << 4 ;   //触发方式为
				IRQ1ER_XINT1 = 1 << 0;        //使能外部中断1
			  EX1 = 1;               //使能内核中断0
			}      break ;
		case 2:
		 {
				XINT23TRGR = sel<< 0 ;   //触发方式
				IRQ2ER_XINT2 = 1 << 0;        //使能外部中断2
			  EX2 = 1;               //使能内核中断0
			}          break ;
		case 3:
		 {
				XINT23TRGR = sel << 4 ;   //触发方式
				IRQ3ER_XINT3 = 1 << 0;        //使能外部中断3
			  EX3 = 1;               //使能内核中断0
			}            break ;
		case 4:
		 {
				XINT45TRGR = sel << 0 ;   //触发方式
				IRQ4ER_XINT4 = 1 << 0;        //使能外部中断4
			  EX4 = 1;               //使能内核中断0
			}             break ;
		case 5:
		 {
				XINT45TRGR = sel << 4 ;   //触发方式
				IRQ5ER_XINT5 = 1 << 0;        //使能外部中断5
			  EX5 = 1;               //使能内核中断0
			}      break ;
			default :break;
	}
	  EA = 1;           //开内核总中断（如果频繁调用次函数，总中断开关可以保持开启，移除到函数外）
}



