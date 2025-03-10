#include "CBM7216.h"
#include "rtc.h"
#include "uart1.h"


uint16 count = 0;
uint8 flag = 0;


/*********************************************************************************** 
Function   : void EXT0_IRQHandler(void)
Description: 系统中断0入口函数
Input      : No      
Output     : No	                  
Return     : No
************************************************************************************/
void EXT0_IRQHandler(void) interrupt 0
{
	/*---外部中断0---*/
    if(0x01 == IRQ0SR_XINT0)
    {   
        IRQ0SR_XINT0 = 0;
				
    }
    
    /*---T3中断0---*/
    if(0x02 == IRQ0SR_TCM3INT0) 
		{	
			T3SR_INT0SR = 0 << 0; //清T3中断0标志位

			/*中断处理程序......*/
		}
		
			/*---WDT中断---*/	
		if(0x04 == IRQ0SR_WDTINT) 
		{
			if(0x01 == WDTSR_WDTINT) 
			{
				WDTSR_WDTINT = 0;
				P2_0 = ~P2_0;
				UartPrintf("Run");            //中断测试
		    UartPrintf("\r\n");
				/* 中断处理程序......*/			
			}
		}
    
    /*---LVD中断---*/
    if(0x08 == IRQ0SR_LVDINT)
    {
        if(LVDCR_LVDSR==0x80)
        {
            LVDCR_LVDSR=0;//必须手动清除，否则会一直响应中断
        }
    }
}

/*********************************************************************************** 
Function   : void EXT1_IRQHandler(void)
Description: 系统中断1入口函数
Input      : No      
Output     : No	                  
Return     : No
************************************************************************************/
void EXT1_IRQHandler(void)	interrupt 1
{
//	static uint16 timer3_cnt1 = 0;
    /*---外部中断1---*/
    if(0x01 == IRQ1SR_XINT1)
    {   
        IRQ1SR_XINT1 = 0;
	
    }

    if(0x02 == IRQ1SR_TCM3INT1) //T3中断1 
		{	
			T3SR_INT1SR = 0 << 1;		//清T3中断1标志位

			/*中断处理程序......*/	
		}

//	if(0x04 == IRQ1SR_SADCINT)
	
    /*---ESD中断---*/
    if(0x08 == IRQ1SR_ESDINT)
    {
        IRQ1SR_ESDINT = 1 ;//写1清零
        if(MISCR3_ESDSR ==0x04)
        {
            MISCR3_ESDSR = 0 ; //必须手动清除，否则会一直响应中断
        }
    }
}

/*********************************************************************************** 
Function   : void EXT2_IRQHandler(void)
Description: 系统中断2入口函数
Input      : No      
Output     : No	                  
Return     : No
************************************************************************************/
void EXT2_IRQHandler(void)	interrupt 2 
{
    /*---外部中断2---*/
    if(0x01 == IRQ2SR_XINT2)
    {
        IRQ2SR_XINT2 = 0;
		/*中断处理程序......*/
			
    }

		if(0x02 == IRQ2SR_TCM0INT) //T0中断
		{			
			T0SR_INTSR = 0 << 0; //清T0中断标志位
					/*中断处理程序......*/
		}

    if(0x04 == IRQ2SR_RTCINT) 
		{
			if(0x01 == RTCSR_INTSSR) 
			{
				RTCSR_INTSSR = 0 << 0;
				/*中断处理程序......*/
			} 
			if(0x02 == RTCSR_INTMSR) 
			{
				RTCSR_INTMSR = 0 << 1;           
				/*中断处理程序......*/
			}
			if(0x04 == RTCSR_INTHSR) 
			{
				RTCSR_INTHSR = 0 << 2;
				/*中断处理程序......*/
			}
			if(0x08 == RTCSR_INTDSR) 
			{
				RTCSR_INTDSR = 0 << 3;
				/*中断处理程序......*/
			}
			if(0x10 == RTCSR_INTCSR)  
			{
				RTCSR_INTCSR = 0 << 4;
				/*中断处理程序......*/
			}			
		}
		if(0x08 == IRQ2SR_UART3INT) //UART3中断
		{			
				if(0x08 == USR3_RXREADY)
				{     
					USR3=0x08;
					/*中断处理程序......*/ 
				}
				if(0x80 == USR3_RXTMOUT)
				{
					USR3 = 0x80 ;//写1清0，否则会一直进中断
					/*中断处理程序......*/ 
				}
    }	

    if(0x10 == IRQ2SR_SYSCLKFINT)
    {
        MISCR3_SYSCLKFINTSR = 0;
		/*中断处理程序......*/
    }
}

/*********************************************************************************** 
Function   : void EXT3_IRQHandler(void)
Description: 系统中断3入口函数
Input      : No      
Output     : No	                  
Return     : No
************************************************************************************/
void EXT3_IRQHandler(void) interrupt 3
{		
	/*---外部中断3---*/
    if(0x01 == IRQ3SR_XINT3)
    {   
        IRQ3SR_XINT3 = 0;
		/*中断处理程序......*/
    }
		if(0x08 == IRQ3SR_TCM2INT1)//T2中断1 
		{
			T2SR_INT1SR=0;
			/*中断处理程序......*/		
		}

    if(0x02 == IRQ3SR_TCM1INT)//T1中断 
    {			
			T1SR_INTSR = 0 << 0;		//清T1中断标志位
			if(++count >= 5)
			{
					count = 0;
					flag = 1;
			}

			 //中断处理程序......
		}

		if(0x04 == IRQ3SR_UART1INT) //判断是否是uart中断 
		{			
			if(0x08 == USR1_RXREADY) 
			{			
				USR1=0x08;
				/*中断处理程序......*/ 				
			}	
			if(0x80 == USR1_RXTMOUT)
			{
				USR1 = 0x80 ;//写1清0，否则会一直进中断 
				/*中断处理程序......*/ 			
			}
			
		}
}

/*********************************************************************************** 
Function   : void EXT4_IRQHandler(void)
Description: 系统中断4入口函数
Input      : No      
Output     : No	                  
Return     : No
************************************************************************************/
void EXT4_IRQHandler(void) interrupt 4 
{
	/*---外部中断4---*/
    if(0x01 == IRQ4SR_XINT4)
    {  
        IRQ4SR_XINT4 = 0;
			
    }

    if(0x02 == IRQ4SR_TCM2INT0)//T2中断 
		{	
			T2SR_INT0SR = 0 << 0;		//清T2中断标志位             
			//中断处理程序......
		}

    if(0x04 == IRQ4SR_ADCINT)//ADC转换完成中断标志
    {
        IRQ4SR_ADCINT = 0;
//        ADCSR_SAMPEND = 0 ;//清转换完成标志
//        g_adcDat = ADCDRH;
//        g_adcDat <<= 8;
//        g_adcDat |= ADCDRL;
//        g_adcDatFlg = 1;
    }
	
		if(0x08 == IRQ4SR_UART2INT) //判断是否是uart中断 
		{			
			if(0x08 == USR2_RXREADY) 
			{		
				USR2=0x08;
				/*中断处理程序......*/  
			}
			if(0x80 == USR2_RXTMOUT)
			{
				USR2 = 0x80 ;//写1清0，否则会一直进中断
				/*中断处理程序......*/ 
			}			
		}
}

/*********************************************************************************** 
Function   : void EXT5_IRQHandler(void)
Description: 系统中断5入口函数
Input      : No      
Output     : No	                  
Return     : No
************************************************************************************/
void EXT5_IRQHandler(void) interrupt 5 
{
	/*---外部中断5---*/
    if(0x01 == IRQ5SR_XINT5)
    {  
        IRQ5SR_XINT5 = 0;
				
    }

    if(0x02 == IRQ5SR_I2CSINT)//I2C从机中断
		{
			if(I2CSSR_RXDATA == 0x02)//I2C接收数据中断
			{
				I2CSSR_RXDATA = 0;
			}
		}
	
		if(0x04 == IRQ5SR_SPIINT)//SPI中断
		{
					
		}
		
		if(0x08 == IRQ5SR_I2CMINT)//I2C主机中断
		{
					
		}
}