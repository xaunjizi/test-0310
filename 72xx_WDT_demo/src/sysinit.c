/************************************************************************************************ 
  Company: Shenzhen Chipsbank Technologies Co., Ltd
  FileName: sysinit.c  
  Author: joe.huang        
  Version : V1.0      
  Date: 20191022  
  Description: 系统相关时钟初始化、Io口初始化

  Function List:
				uint8 sysClkInit(uint8 IHpllclksel, uint8 sysclksel, uint8 mclkDiv, uint8 sclk1Div)
				void ioPortInit(void);

  History: //历史修改记录   
	<author>		<time>			<Re_version >			<desc>  
	Joe.huang		20191022		V1.0					初版 
  	  
*************************************************************************************************/
#include "CBM7216.h"
#include "intrins.h"

/*********************************************************************************** 
Function   : uint8 sysClkInit(uint8 IHpllclksel, uint8 sysclk_TLclksel, uint8 mclkDiv, uint8 sclk1Div)
Description: 系统时钟初始化
Input      : 
             IHpllclksel: 内部高速PLL时钟源选择 0-24M；1-16M
		
             TLclk_sysclksel: 
						bit7：TLclksel-timer低速时钟选择； 0-1Mhz; 1-100Khz
						bit0：sysclksel-系统时钟源选择； 0-IH（内部高速时钟）；1-IL（内部低速时钟1M）
				
             mclkDiv  	：系统main时钟分频器（0~31）  MCLK=SCLK/(mclkDiv+1)
			 
             sclk1Div  	：系统副时钟1分频器（0-3） sclk1=SCLK/(sclk1Div+1)
Output     : No	                  
Return     : retOSC: 系统所选时钟源1-1M; 16-16M；24-24M
************************************************************************************/
uint8 sysClkInit(uint8 IHpllclksel, uint8 TLclk_sysclksel, uint8 mclkDiv, uint8 sclk1Div)
{
	uint8 retOSCV = 0;
	uint8 sysclksel;
	uint8 TLclksel;
	
	IHpllclksel &= 0x01;//内部高速PLL时钟源选择 0-24M；1-16M
	TLclksel = (TLclk_sysclksel&0x80)>>7;//timer低速时钟选择； 0-1Mhz; 1-100Khz
	sysclksel = TLclk_sysclksel&0x01;//系统时钟源选择；0-IH（内部高速时钟）；1-IL（内部低速时钟1M）
	if(sysclksel)
	{
		retOSCV = 1;//1M
	}
	else
	{
		if(IHpllclksel)
		{
			retOSCV = 16;//16M
		}
		else
		{
			retOSCV = 24;//24M
		}
	}
	
	MDLCKCR_IOCEN = 0x01<<3;
	MISCR2_IHCLKEN = 1<<0;//使能内部高速时钟
	IHPLLCLKSELCR = IHpllclksel;//选择内部高速时钟：0-24m(默认值0) 1-16m
	MISCR1_SYSCLKSEL = sysclksel<<4;//选择系统时钟源  0-IH（内部高速时钟-默认值0）；1-IL（内部低速时钟1M）
	_nop_();_nop_();_nop_();_nop_();_nop_();//等待OSC稳定
	_nop_();_nop_();_nop_();_nop_();_nop_();//等待OSC稳定
	_nop_();_nop_();_nop_();_nop_();_nop_();//等待OSC稳定
	_nop_();_nop_();_nop_();_nop_();_nop_();//等待OSC稳定
	_nop_();_nop_();_nop_();_nop_();_nop_();//等待OSC稳定
	_nop_();_nop_();_nop_();_nop_();_nop_();//等待OSC稳定
	_nop_();_nop_();_nop_();_nop_();_nop_();//等待OSC稳定
	_nop_();_nop_();_nop_();_nop_();_nop_();//等待OSC稳定	
	CKDIVCR_MCLKDIV = (mclkDiv&31)<<0;//MCLK
	MISCR2_SCLK1DIV = (sclk1Div&3)<<6; //SCLK1：外设计数时钟
	CKDIVCR_ILCLKDIV = (0&7)<<6; //SCLK2：1M低速时钟
								//0-1分频-1M；1-2分频-500K；2-4分频-250K；3-8分频-125K；
								//4-10分频-100K；5-16分频=62.5k；6-32分频=31.25k；7-64分频=15.625k；
	MDLCKCR_TLCKSEL = TLclksel<<7;//timer低速时钟选择 0-1Mhz; 1-100Khz
	RTCCLKSELR = 1;//=0-RTC选择30K时钟（支持低功耗下RTC继续工作）；=1-RTC选择100K时钟
    
	//IHPLL监测功能
	MISCR2_IHCLKCHKEN = 0<<1;//使能PLL出错自动重启（默认值0）
	MISCR2_SYSCLKSWITCHEN = 0<<3;//IHCLK出错时自动切换到1MHZ
	MISCR3_SYSCLKFINTEN = 1<<5;
	IRQ2ER_SYSCLKFINTEN = 1<<4;
	
	if(((ECCCR&0x0D)!=0x05) && ((ECCCR&0x0D)!=0x09))//只有没开ecc时，才可以打开MISCR_FMFIFOEN、MISCR_FMULRDEN
	{
			MISCR1_FMFIFOEN = 0x01<<3 ; //flash重读机制采用流水取指操作
			MISCR1_FMULRDEN = 0x01<<2 ; //开flash重读机制
	}
	
	return retOSCV;
}
/*********************************************************************************** 
Function   : void ioPortInit(void)
Description: Io端口配置（功能重映射、电流大小、上拉电阻大小、上下拉使能、开漏使能、数据、方向选择）
Input      : No      
Output     : No	                  
Return     : No
************************************************************************************/
void ioPortInit(void)
{
  MDLCKCR_IOCEN = 0x01<<3 ;
    /*----------IoPort Remap Config----------*/
   //P00/P01 Por default debug_uart(0x01/0x30), others Por default IoPort(0x00)
  P00IOCFG=0X01 ;//调试串口输出
	P01IOCFG=0X30 ;//调试串口输入
	P02IOCFG=0X00 ;
	P03IOCFG=0X00 ;
	P04IOCFG=0X00 ;
	P05IOCFG=0X00 ;
	P06IOCFG=0X00 ;
	P07IOCFG=0X00 ;

	P10IOCFG=0X00 ;
	P11IOCFG=0X00 ;
	P12IOCFG=0X00 ;
	P13IOCFG=0X00 ;
	P14IOCFG=0X00 ;
	P15IOCFG=0X00 ;
	P16IOCFG=0X00 ;
	P17IOCFG=0X00 ;

	P20IOCFG=0X00 ;
	P21IOCFG=0X00 ;
	P22IOCFG=0X00 ;
	P23IOCFG=0X00 ;
	P24IOCFG=0X00 ;
	P25IOCFG=0X00 ;
	P26IOCFG=0X00 ;
	P27IOCFG=0X00 ;

	P30IOCFG=0X00 ;
	P31IOCFG=0X00 ;

    /*----------Io Current Config----------*/
	//驱动电流 Por default 00(00/11:6mA; 01:30mA; 10:60mA;)
	P0LDRVRL = 0x00 ; 	
	P0LDRVRH = 0x00 ;
	P1LDRVRL = 0x00 ; 	
	P1LDRVRH = 0x00 ;
	P2LDRVRL = 0x00 ;
	P2LDRVRH = 0x00 ;
	P3LDRVRL = 0x00 ; 	

    /*----------Io Up/Down Config----------*/
	//上拉电阻选择 Por default 0(00:88K；01:10K; 10:4.5K; 11:2.2K)
	P0PURSELRL = 0x00 ;
	P0PURSELRH = 0x00 ;
	P1PURSELRL = 0x00 ;
	P1PURSELRH = 0x00 ;
	P2PURSELRL = 0x00 ;
	P2PURSELRH = 0x00 ;
	P3PURSELRL = 0x00 ;

    /*----------Io OpenDrain Config----------*/
	//开漏 Por default 0(禁止开漏)
	P0OD = 0x00 ;
	P1OD = 0x00 ;
	P2OD = 0x00 ;
	P3OD = 0x00 ;
    
    /*----------Io PortData----------*/
    //数据寄存器 Por default 1
	P0 = 0xFF ;
	P1 = 0xFF ;
	P2 = 0xFF ;
	P3 = 0xFF ;
	
    /*----------Io PortDirection Config----------*/    
	//方向 Por default 1(输入)
	P0OE = 0xFF ;
	P1OE = 0xFF ;
	P2OE = 0xFF ;
	P3OE = 0xFF ;
	
	/*----------Io PULLUP Config----------*/
	//上拉 Por default 0(禁止上拉)
	P0PU = 0xff ;
	P1PU = 0xff ;
	P2PU = 0xff ;
	P3PU = 0xff ;

	/*----------Io smith Config----------*/    
	//IO复用作为LCD功能时必需配置为0xff，否则必须配置为0x00； Por default 0x00(关闭)
	P0SMEN = 0x00 ;
	P1SMEN = 0x00 ;
	P2SMEN = 0x00 ;
	P3SMEN = 0x00 ;
}



/*********************************************************************************** 
Function   : void User_IOInit(void)
Description: 自定义IO（功能重映射、电流大小、上拉电阻大小、上下拉使能、开漏使能、数据、方向选择）
Input      : No      
Output     : No	                  
Return     : No
************************************************************************************/
void User_IOInit(void)
{
//		P21IOCFG = 0x00;                    //IO功能
//		P20IOCFG = 0x00;
//		P02IOCFG = 0x00;
//		P17IOCFG = 0x00;
//		
//		
//		P2LDRVRL_1 = 0x04;                 //电流60ma
//		P2LDRVRL_0 = 0x01;
//		P0LDRVRL_2 = 0x10;
//		P1LDRVRH_7 = 0x40;
//		
//		P2OE_1 = 0x00;                    //输出方向
//		P2OE_0 = 0x00;
//		P0OE_2 = 0x00;
//		P1OE_7 = 0x00;
//		
//		P2_1 = 1;                         //共阳端
	
//		P2_0 = 0;                         //LED低电平亮
//		P0_2 = 0;
	



//	//////touch
//	P30IOCFG=0X08;	
//	P25IOCFG=0X08;		
//	P03IOCFG=0X08;
//	P22IOCFG=0X08;		
//	P3PU_0=0x00;
//	P2PU_5=0x00;
//	P0PU_3=0x00;
//	P2PU_2=0x00;
//	
//  P20IOCFG = 0x00;                    //IO功能
//	P07IOCFG = 0x00;
//	P21IOCFG = 0x00;
//	P02IOCFG = 0x00;
//	P17IOCFG = 0x00;
//	
//	
//	P2LDRVRL_0 = 0x01;                 //电流60ma
//	P0LDRVRH_7 = 0x40;
//	P2LDRVRL_1 = 0x04;
//	P0LDRVRL_2 = 0x10;
//	P1LDRVRH_7 = 0x40;
//	
//	P2OE_0 = 0x00;                 //输出方向
//	P0OE_7 = 0x00;
//	P2OE_1 = 0x00;
//	P0OE_2 = 0x00;
//	P1OE_7 = 0x00;
//	
//	P2_0 = 1;
//	P0_7 =0;
//	P2_1 =0;
//	P0_2 =0;
//	P1_7 =0;
	
	
	
}

