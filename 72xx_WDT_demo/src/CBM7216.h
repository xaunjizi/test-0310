/************************************************************************************************ 
  Company: Shenzhen Chipsbank Technologies Co., Ltd
  FileName: main.c  
  Author: Joe.huang        
  Version : V1.0      
  Date: 2021-06-18  
  Description: CBM72xx系列MCU头文件

  Function List:    


  History:         //历史修改记录  
      <author>         <time>           <Re_version >           <desc>  
  	  
*************************************************************************************************/
#ifndef __CBM7216_H__
#define __CBM7216_H__
#include"absacc.h"

typedef	unsigned char 	        boolean;
typedef	unsigned char 	        uint8;
typedef	unsigned short int      uint16;
typedef	unsigned long int 	    uint32;
typedef	signed char 	        int8;
typedef	signed short int        int16;
typedef	signed long int		    int32;


/*---------------8051 standard registers---------------*/
//BYTE Registers
sfr		P0		=		0x80;
sfr		P1		=		0x90;
sfr		P2		=		0xA0;
sfr		P3		=		0xB0;

sfr		B		=		0xF0;
sfr		ACC		=		0xE0;
sfr		PSW		=		0xD0;
sfr		IP2		=		0xC8;//bit1-0: INT4；bit3-2: INT5
sfr		IP1		=		0xB8;//bit1-0: INT0；bit3-2: INT1；bit5-4: INT2；bit7-6: INT3；					
sfr		IE		=		0xA8;
sfr		VTOR	=		0x88;	
sfr		PCON	=		0x87;
sfr		PSEQ	=		0x86;
sfr		DPH		=		0x83;
sfr		DPL		=		0x82;
sfr16   DPTR	=		0x82;
sfr		SP		=		0x81;

//bit register define
sbit	P0_7	=		0x87;
sbit	P0_6	=		0x86;
sbit	P0_5	=		0x85;
sbit	P0_4	=		0x84;
sbit	P0_3	=		0x83;
sbit	P0_2	=		0x82;
sbit	P0_1	=		0x81;
sbit	P0_0	=		0x80;	

sbit	P1_7	=		0x97;
sbit	P1_6	=		0x96;
sbit	P1_5	=		0x95;
sbit	P1_4	=		0x94;
sbit	P1_3	=		0x93;
sbit	P1_2	=		0x92;
sbit	P1_1	=		0x91;
sbit	P1_0	=		0x90;

sbit	P2_7	=		0xA7;
sbit	P2_6	=		0xA6;
sbit	P2_5	=		0xA5;
sbit	P2_4	=		0xA4;
sbit	P2_3	=		0xA3;
sbit	P2_2	=		0xA2;
sbit	P2_1	=		0xA1;
sbit	P2_0	=		0xA0;

sbit	P3_1	=		0xB1;
sbit	P3_0	=		0xB0;

//PSW
sbit	CY		=		0xD7;
sbit	AC		=		0xD6;
sbit	F0		=		0xD5;
sbit	RS1		=		0xD4;
sbit	RS0		=		0xD3;
sbit	OV		=		0xD2;
sbit	P		=		0xD0;

//IE
sbit	EA		=		0xAF;
//
sbit	EX5		=		0xAD;
sbit	EX4		=		0xAC;
sbit	EX3		=		0xAB;
sbit	EX2		=		0xAA;
sbit	EX1		=		0xA9;
sbit	EX0		=		0xA8;


/*---------------7316F standard registers---------------*/
//define IO const
#define		P00IOCFG		XBYTE[0x1000]
#define		P01IOCFG		XBYTE[0x1001]
#define		P02IOCFG		XBYTE[0x1002]
#define		P03IOCFG		XBYTE[0x1003]
#define		P04IOCFG		XBYTE[0x1004]
#define		P05IOCFG		XBYTE[0x1005]
#define		P06IOCFG		XBYTE[0x1006]
#define		P07IOCFG		XBYTE[0x1007]

#define		P10IOCFG		XBYTE[0x1008]
#define		P11IOCFG		XBYTE[0x1009]
#define		P12IOCFG		XBYTE[0x100A]
#define		P13IOCFG		XBYTE[0x100B]
#define		P14IOCFG		XBYTE[0x100C]
#define		P15IOCFG		XBYTE[0x100D]
#define		P16IOCFG		XBYTE[0x100E]
#define		P17IOCFG		XBYTE[0x100F]

#define		P20IOCFG		XBYTE[0x1010]
#define		P21IOCFG		XBYTE[0x1011]
#define		P22IOCFG		XBYTE[0x1012]
#define		P23IOCFG		XBYTE[0x1013]
#define		P24IOCFG		XBYTE[0x1014]
#define		P25IOCFG		XBYTE[0x1015]
#define		P26IOCFG		XBYTE[0x1016]
#define		P27IOCFG		XBYTE[0x1017]

#define		P30IOCFG		XBYTE[0x1018]
#define		P31IOCFG		XBYTE[0x1019]

#define		P0PU			XBYTE[0x25FF]
	#define		P0PU_7				XBYTE[0x2580]
	#define		P0PU_6				XBYTE[0x2540]
	#define		P0PU_5				XBYTE[0x2520]
	#define		P0PU_4				XBYTE[0x2510]
	#define		P0PU_3				XBYTE[0x2508]
	#define		P0PU_2				XBYTE[0x2504]
	#define		P0PU_1				XBYTE[0x2502]
	#define		P0PU_0				XBYTE[0x2501]

#define		P1PU			XBYTE[0x26FF]
	#define		P1PU_7				XBYTE[0x2680]
	#define		P1PU_6				XBYTE[0x2640]
	#define		P1PU_5				XBYTE[0x2620]
	#define		P1PU_4				XBYTE[0x2610]
	#define		P1PU_3				XBYTE[0x2608]
	#define		P1PU_2				XBYTE[0x2604]
	#define		P1PU_1				XBYTE[0x2602]
	#define		P1PU_0				XBYTE[0x2601]

#define		P2PU			XBYTE[0x27FF]
	#define		P2PU_7				XBYTE[0x2780]
	#define		P2PU_6				XBYTE[0x2740]
	#define		P2PU_5				XBYTE[0x2720]
	#define		P2PU_4				XBYTE[0x2710]
	#define		P2PU_3				XBYTE[0x2708]
	#define		P2PU_2				XBYTE[0x2704]
	#define		P2PU_1				XBYTE[0x2702]
	#define		P2PU_0				XBYTE[0x2701]

#define		P3PU			XBYTE[0x28FF]
	#define		P3PU_1				XBYTE[0x2802]
	#define		P3PU_0				XBYTE[0x2801]

#define		P0OE			XBYTE[0x2AFF]
	#define		P0OE_7				XBYTE[0x2A80]
	#define		P0OE_6				XBYTE[0x2A40]
	#define		P0OE_5				XBYTE[0x2A20]
	#define		P0OE_4				XBYTE[0x2A10]
	#define		P0OE_3				XBYTE[0x2A08]
	#define		P0OE_2				XBYTE[0x2A04]
	#define		P0OE_1				XBYTE[0x2A02]
	#define		P0OE_0				XBYTE[0x2A01]

#define		P1OE			XBYTE[0x2BFF]
	#define		P1OE_7				XBYTE[0x2B80]
	#define		P1OE_6				XBYTE[0x2B40]
	#define		P1OE_5				XBYTE[0x2B20]
	#define		P1OE_4				XBYTE[0x2B10]
	#define		P1OE_3				XBYTE[0x2B08]
	#define		P1OE_2				XBYTE[0x2B04]
	#define		P1OE_1				XBYTE[0x2B02]
	#define		P1OE_0				XBYTE[0x2B01]

#define		P2OE			XBYTE[0x2CFF]
	#define		P2OE_7				XBYTE[0x2C80]
	#define		P2OE_6				XBYTE[0x2C40]
	#define		P2OE_5				XBYTE[0x2C20]
	#define		P2OE_4				XBYTE[0x2C10]
	#define		P2OE_3				XBYTE[0x2C08]
	#define		P2OE_2				XBYTE[0x2C04]
	#define		P2OE_1				XBYTE[0x2C02]
	#define		P2OE_0				XBYTE[0x2C01]

#define		P3OE			XBYTE[0x2DFF]
	#define		P3OE_1				XBYTE[0x2D02]
	#define		P3OE_0				XBYTE[0x2D01]

#define		P0PURSELRL		XBYTE[0x30FF]
	#define		P0PURSELRL_3		XBYTE[0x30C0]
	#define		P0PURSELRL_2		XBYTE[0x3030]
	#define		P0PURSELRL_1		XBYTE[0x300C]
	#define		P0PURSELRL_0		XBYTE[0x3003]

#define		P0PURSELRH		XBYTE[0x31FF]
	#define		P0PURSELRH_7		XBYTE[0x31C0]
	#define		P0PURSELRH_6		XBYTE[0x3130]
	#define		P0PURSELRH_5		XBYTE[0x310C]
	#define		P0PURSELRH_4		XBYTE[0x3103]

#define		P1PURSELRL		XBYTE[0x32FF]
	#define		P1PURSELRL_3		XBYTE[0x32C0]
	#define		P1PURSELRL_2		XBYTE[0x3230]
	#define		P1PURSELRL_1		XBYTE[0x320C]
	#define		P1PURSELRL_0		XBYTE[0x3203]

#define		P1PURSELRH		XBYTE[0x33FF]
	#define		P1PURSELRH_7		XBYTE[0x33C0]
	#define		P1PURSELRH_6		XBYTE[0x3330]
	#define		P1PURSELRH_5		XBYTE[0x330C]
	#define		P1PURSELRH_4		XBYTE[0x3303]

#define		P2PURSELRL		XBYTE[0x34FF]
	#define		P2PURSELRL_3		XBYTE[0x34C0]
	#define		P2PURSELRL_2		XBYTE[0x3430]
	#define		P2PURSELRL_1		XBYTE[0x340C]
	#define		P2PURSELRL_0		XBYTE[0x3403]

#define		P2PURSELRH		XBYTE[0x35FF]
	#define		P2PURSELRH_7		XBYTE[0x35C0]
	#define		P2PURSELRH_6		XBYTE[0x3530]
	#define		P2PURSELRH_5		XBYTE[0x350C]
	#define		P2PURSELRH_4		XBYTE[0x3503]

#define		P3PURSELRL		XBYTE[0x36FF]
	#define		P3PURSELRL_1		XBYTE[0x360C]
	#define		P3PURSELRL_0		XBYTE[0x3603]

#define		P0OD			XBYTE[0x3AFF]
	#define		P0OD_7				XBYTE[0x3A80]
	#define		P0OD_6				XBYTE[0x3A40]
	#define		P0OD_5				XBYTE[0x3A20]
	#define		P0OD_4				XBYTE[0x3A10]
	#define		P0OD_3				XBYTE[0x3A08]
	#define		P0OD_2				XBYTE[0x3A04]
	#define		P0OD_1				XBYTE[0x3A02]
	#define		P0OD_0				XBYTE[0x3A01]

#define		P1OD			XBYTE[0x3BFF]
	#define		P1OD_7				XBYTE[0x3B80]
	#define		P1OD_6				XBYTE[0x3B40]
	#define		P1OD_5				XBYTE[0x3B20]
	#define		P1OD_4				XBYTE[0x3B10]
	#define		P1OD_3				XBYTE[0x3B08]
	#define		P1OD_2				XBYTE[0x3B04]
	#define		P1OD_1				XBYTE[0x3B02]
	#define		P1OD_0				XBYTE[0x3B01]

#define		P2OD			XBYTE[0x3CFF]
	#define		P2OD_7				XBYTE[0x3C80]
	#define		P2OD_6				XBYTE[0x3C40]
	#define		P2OD_5				XBYTE[0x3C20]
	#define		P2OD_4				XBYTE[0x3C10]
	#define		P2OD_3				XBYTE[0x3C08]
	#define		P2OD_2				XBYTE[0x3C04]
	#define		P2OD_1				XBYTE[0x3C02]
	#define		P2OD_0				XBYTE[0x3C01]

#define		P3OD			XBYTE[0x3DFF]
	#define		P3OD_1				XBYTE[0x3D02]
	#define		P3OD_0				XBYTE[0x3D01]

#define		P0LDRVRL		XBYTE[0x40FF]
	#define		P0LDRVRL_3			XBYTE[0x40C0]
	#define		P0LDRVRL_2			XBYTE[0x4030]
	#define		P0LDRVRL_1			XBYTE[0x400C]
	#define		P0LDRVRL_0			XBYTE[0x4003]

#define		P0LDRVRH		XBYTE[0x41FF]
	#define		P0LDRVRH_7			XBYTE[0x41C0]
	#define		P0LDRVRH_6			XBYTE[0x4130]
	#define		P0LDRVRH_5			XBYTE[0x410C]
	#define		P0LDRVRH_4			XBYTE[0x4103]

#define		P1LDRVRL		XBYTE[0x42FF] 
	#define		P1LDRVRL_3			XBYTE[0x42C0]
	#define		P1LDRVRL_2			XBYTE[0x4230]
	#define		P1LDRVRL_1			XBYTE[0x420C]
	#define		P1LDRVRL_0			XBYTE[0x4203]

#define		P1LDRVRH		XBYTE[0x43FF] 
	#define		P1LDRVRH_7			XBYTE[0x43C0]
	#define		P1LDRVRH_6			XBYTE[0x4330]
	#define		P1LDRVRH_5			XBYTE[0x430C]
	#define		P1LDRVRH_4			XBYTE[0x4303]

#define		P2LDRVRL		XBYTE[0x44FF] 
	#define		P2LDRVRL_3			XBYTE[0x44C0]
	#define		P2LDRVRL_2			XBYTE[0x4430]
	#define		P2LDRVRL_1			XBYTE[0x440C]
	#define		P2LDRVRL_0			XBYTE[0x4403]

#define		P2LDRVRH		XBYTE[0x45FF]  
	#define		P2LDRVRH_7			XBYTE[0x45C0]
	#define		P2LDRVRH_6			XBYTE[0x4530]
	#define		P2LDRVRH_5			XBYTE[0x450C]
	#define		P2LDRVRH_4			XBYTE[0x4503]

#define		P3LDRVRL		XBYTE[0x46FF]
	#define		P3LDRVRL_1			XBYTE[0x460C]
	#define		P3LDRVRL_0			XBYTE[0x4603]

#define     P0SMEN			XBYTE[0x4BFF]
    #define     P0SMEN_7 			XBYTE[0x4B80]
    #define     P0SMEN_6 			XBYTE[0x4B40]
    #define     P0SMEN_5 			XBYTE[0x4B20]
    #define     P0SMEN_4 			XBYTE[0x4B10]
    #define     P0SMEN_3 			XBYTE[0x4B08]
    #define     P0SMEN_2 			XBYTE[0x4B04]
    #define     P0SMEN_1 			XBYTE[0x4B02]
    #define     P0SMEN_0 			XBYTE[0x4B01]
#define     P1SMEN			XBYTE[0x4CFF]
    #define     P1SMEN_7 			XBYTE[0x4C80]
    #define     P1SMEN_6 			XBYTE[0x4C40]
    #define     P1SMEN_5 			XBYTE[0x4C20]
    #define     P1SMEN_4 			XBYTE[0x4C10]
    #define     P1SMEN_3 			XBYTE[0x4C08]
    #define     P1SMEN_2 			XBYTE[0x4C04]
    #define     P1SMEN_1 			XBYTE[0x4C02]
    #define     P1SMEN_0 			XBYTE[0x4C01]
#define     P2SMEN			XBYTE[0x4DFF]
    #define     P2SMEN_7 			XBYTE[0x4D80]
    #define     P2SMEN_6 			XBYTE[0x4D40]
    #define     P2SMEN_5 			XBYTE[0x4D20]
    #define     P2SMEN_4 			XBYTE[0x4D10]
    #define     P2SMEN_3 			XBYTE[0x4D08]
    #define     P2SMEN_2 			XBYTE[0x4D04]
    #define     P2SMEN_1 			XBYTE[0x4D02]
    #define     P2SMEN_0 			XBYTE[0x4D01]
#define     P3SMEN			XBYTE[0x4EFF]
    #define     P3SMEN_1 			XBYTE[0x4E02]
    #define     P3SMEN_0 			XBYTE[0x4E01]


//系统相关控制寄存器
#define		CKDIVCR			XBYTE[0x50FF]
	#define		CKDIVCR_ILCLKDIV	XBYTE[0x50E0]
	#define		CKDIVCR_MCLKDIV		XBYTE[0x501F]

#define		IHPLLCLKSELCR	XBYTE[0x5AFF]

#define		MDLCKCR			XBYTE[0x51FF]
	#define		MDLCKCR_TLCKSEL	XBYTE[0x5180]
	#define		MDLCKCR_PWMEN		XBYTE[0x5140]
	#define		MDLCKCR_SPIEN		XBYTE[0x5120]
	#define		MDLCKCR_UART1EN	    XBYTE[0x5110]
	#define		MDLCKCR_IOCEN		XBYTE[0x5108]
	#define		MDLCKCR_TIMEREN	    XBYTE[0x5104]
	#define		MDLCKCR_LEDEN		XBYTE[0x5102]
	#define		MDLCKCR_WDTEN		XBYTE[0x5101]

#define		MISCR1			XBYTE[0x56FF]
	#define		MISCR1_UART3CKEN	XBYTE[0x5680]
	#define		MISCR1_SENSORCKEN	XBYTE[0x5640]
	#define		MISCR1_UART2CKEN	XBYTE[0x5620]
	#define		MISCR1_SYSCLKSEL	XBYTE[0x5610]
	#define		MISCR1_FMFIFOEN		XBYTE[0x5608]
	#define		MISCR1_FMULRDEN		XBYTE[0x5604]
	#define		MISCR1_NVR2CRCEN	XBYTE[0x5602]
	#define		MISCR1_POREN		XBYTE[0x5601]

#define		MISCR2		    XBYTE[0x5BFF]
    #define   MISCR2_SCLK1DIV     	XBYTE[0X5BC0]
    #define   MISCR2_ILCLK30KEN	    XBYTE[0x5B20]
    #define   MISCR2_LPCLKEN        XBYTE[0x5B10]
    #define   MISCR2_SYSCLKSWITCHEN XBYTE[0x5B08]
    #define   MISCR2_ILCLK1MEN      XBYTE[0x5B04]
    #define   MISCR2_IHCLKCHKEN   	XBYTE[0x5B02]
    #define   MISCR2_IHCLKEN    	XBYTE[0x5B01]
  
#define		MISCR3			XBYTE[0x59FF]
 	#define		MISCR3_SYSCLKSR		XBYTE[0x5980]
 	#define		MISCR3_SYSCLKFINTSR	XBYTE[0x5940]
 	#define		MISCR3_SYSCLKFINTEN	XBYTE[0x5920]
    //NA
 	#define		MISCR3_ESDEN		XBYTE[0x5908]
	#define		MISCR3_ESDSR		XBYTE[0x5904]
 	#define		MISCR3_NVR2CRCSR	XBYTE[0x5902]
	#define		MISCR3_LVDSTOPWDT   XBYTE[0x5901]
			
#define		ESDCR			XBYTE[0x57FF]
	#define		ESDCR_CLKSTOPEN	    XBYTE[0x5780]
	#define		ESDCR_CLRCNT		XBYTE[0x5770]
	#define		ESDCR_VOUTSEL		XBYTE[0x570C]
	#define		ESDCR_RES			XBYTE[0x5703]
    
#define		SLPWKCR			XBYTE[0x52FF]
	#define	   SLPWKCR_XINT0EDGESEL XBYTE[0x5280]
	#define		SLPWKCR_DRSEL		XBYTE[0x5270]
	#define		SLPWKCR_XINT0WKEN	XBYTE[0x5208]
	#define		SLPWKCR_SENSORWKEN	XBYTE[0x5204]
	#define		SLPWKCR_RTCWKEN		XBYTE[0x5202]
	#define		SLPWKCR_AUTOWKEN	XBYTE[0x5201]	

#define		SLPWKDR			XBYTE[0x53FF]
#define     SLPWKSR         XBYTE[0x5DFF]
    #define     SLPWKSR_XINT0WKS    XBYTE[0x5D08]
    #define     SLPWKSR_SENSORWKS   XBYTE[0x5D04]
    #define     SLPWKSR_RTCWKS      XBYTE[0x5D02]
    #define     SLPWKSR_AUTOWKS     XBYTE[0x5D01]

#define		RSTSR			XBYTE[0x54FF]
    #define		RSTSR_SRST		    XBYTE[0x5410]
	#define		RSTSR_HRST		    XBYTE[0x5408]
	#define		RSTSR_LVD			XBYTE[0x5404]
	#define		RSTSR_WDT			XBYTE[0x5402]
	#define		RSTSR_POR			XBYTE[0x5401]

#define		LVDCR			XBYTE[0x55FF]
	#define		LVDCR_LVDSR			XBYTE[0x5580]
	#define		LVDCR_LVDCURSR		XBYTE[0x5540]
	#define		LVDCR_FLTLEN		XBYTE[0x5530]
	#define		LVDCR_VOLSEL		XBYTE[0x55C0]
	#define		LVDCR_OPER			XBYTE[0x5503]

#define		SRSTCR		    XBYTE[0x5C00]
#define		OSC1MTRIMR	XBYTE[0x1040]
#define     PLLTRIMR        XBYTE[0x1041]
#define		OSC30KTRIMCR   	XBYTE[0x1047]
#define		LDOCR0	    	XBYTE[0x1045]
#define		LDOCR1  		XBYTE[0x1046]//LDOCR1.bit6必须为1


//低功耗IDLE/STOP
#define     LPEN            XBYTE[0x1050]//1-进入对应低功耗模式，唤醒时自动清0
#define         LPEN_STOP           1//bit1(默认0)  =1-进入低功耗STOP
#define         LPEN_IDLE           0//bit0(默认0)  =1-进入低功耗IDLE

#define     LPCR            XBYTE[0x1051]//uart、iic的LPIDLE唤醒使能控制位在对应模块的控制寄存器里
#define         LPCR_RTCWKUPEN      5//bit5(默认0)  LP STOP/IDLE下：=1-使能RTC唤醒；=0-不使能
#define         LPCR_ILCLK1MEN      4//bit4(默认0)  LP STOP/IDLE下：=1-开启1M；=0-关闭
#define         LPCR_AUTOTMWKUPEN   3//bit3(默认0)  LP STOP/IDLE下：=1-使能自动定时唤醒；=0-不使能
#define         LPCR_XINTWKUPEN     2//bit2(默认0)  LP STOP/IDLE下：=1-使能外部电平唤醒（双沿）；=0-不使能
#define         LPCR_SENSORWKUPEN   1//bit1(默认0)  LP IDLE下：=1-使能触摸唤醒；=0-不使能  
#define         LPCR_STOPMODE30KEN  0//bit0(默认1)  LP STOP下：=1-STOP下使能30K；=0-关30K（则RTC、自动定时唤醒不可用，仅XINT可唤醒）

#define     LPWKUPSR        XBYTE[0x1060]//低功耗唤醒源标志，写0清0
//#define         LPWKUPSR_AUTOTM     0x80//bit7(默认0)  IDLE/STOP
//#define         LPWKUPSR_I2C        0x40//bit6(默认0)  IDLE
//#define         LPWKUPSR_UART3      0x20//bit5(默认0)  IDLE
//#define         LPWKUPSR_UART2      0x10//bit4(默认0)  IDLE    
//#define         LPWKUPSR_UART1      0x08//bit3(默认0)  IDLE
//#define         LPWKUPSR_SENSOR     0x04//bit2(默认0)  IDLE
//#define         LPWKUPSR_RTC        0x02//bit1(默认0)  IDLE/STOP
//#define         LPWKUPSR_XINT       0x01//bit0(默认0)  IDLE/STOP

#define     LPXINTWKUPSR    XBYTE[0x1061]//低功耗唤醒源标志，写0清0
//#define         LPINTWKUPSR_XINT5   0x20//bit5(默认0)  IDLE/STOP
//#define         LPINTWKUPSR_XINT4   0x10//bit4(默认0)  IDLE/STOP    
//#define         LPINTWKUPSR_XINT3   0x08//bit3(默认0)  IDLE/STOP
//#define         LPINTWKUPSR_XINT2   0x04//bit2(默认0)  IDLE/STOP
//#define         LPINTWKUPSR_XINT1   0x02//bit1(默认0)  IDLE/STOP
//#define         LPINTWKUPSR_XINT0   0x01//bit0(默认0)  IDLE/STOP

#define   LPWKUPDELAYWORKTM XBYTE[0x1052]//低功耗唤醒后延时多久MCU才开始工作
//bit3:0(默认0x0F)    n*8us

#define     LPAUTOTMWKCNTL  XBYTE[0x1055]//低功耗IDLE/STOP自动定时唤醒时间
#define     LPAUTOTMWKCNTH  XBYTE[0x1056]
//bit[15:0](默认0xFFFF) n*10ms

#define     LPMLDOUPWAITTM  XBYTE[0x1054]//唤醒后主LDO上电延时等待时间
//bit[3:0](默认0x0F)  n*128us

#define     MLDOCR        XBYTE[0x1057]
//#define         POREN_HW             0x10//bit1(默认0)  ；禁止低压复位硬件电路，1-关，低压不复位；0-开，低压复位
//#define         MLDODRIVE            0x01//bit0(默认1)  ；主LDO驱动能力控制位：1-增加型驱动（增强~2mA），0-正常驱动

#define		LPLDOCR  		XBYTE[0x1048]//LP低功耗LDO控制寄存器：0-正常；1-超低功耗

#define    LPDATASAVECLKSEL XBYTE[0x1058]
//bit0(默认0)  1-1M，0-24M/2

#define     LPVALIDCR       XBYTE[0x1059]
//#define         LPVALIDCR_IDLEVALID               0x20//bit5(默认0)  1-无低功耗，0-有
//#define         LPVALIDCR_STOPVALID               0x10//bit4(默认0)  1-无低功耗，0-有
//#define         LPVALIDCR_IDLEMODE_DATASAVEEN     0x02//bit1(默认0)  0-保存有效，1-不保存
//#define         LPVALIDCR_STOPMODE_DATASAVEEN     0x01//bit0(默认0)  0-保存有效，1-不保存

#define     LPPORCR       XBYTE[0x105C]
//#define         LPPORCR_RSTSR       0x10//bit4(默认0)  1-上电POR复位，0-发生LP POR复位
//#define         LPPORCR_POREN       0x01//bit0(默认0)  1-禁止POR复位，0-充许POR复位（进LPMODE前置1，唤醒后至少延时10ms再清0）,默认0

#define     LPRSTMASKCR       XBYTE[0x105D]//进LP前必须先置1，出LP后必须清0
//#define         LPRSTMASKCR_RST     0x01//bit0(默认0)   

/*
#define     LPUARTWKUPTMOUT XBYTE[0x1053]//uart唤醒超时时间，发0x55唤醒
//bit7:0(默认0xFF)    n*32*1us

#define     LPI2CWKUP_BPRTM XBYTE[0xDFFF]//master发送一bit的时间=LPI2CWKUP_BPRTIME*1us，例master=100K, 则1bit时间=10us，LPI2CWKUP_BPRTIME=10
//(默认0xFF)

#define     LPI2CWKUPTMOUT  XBYTE[0xDAF0]//唤醒超时时间=LPI2CWKUPTMOUT*(LPI2CWKUP_BPRTIME*8)us
(默认0x0F)
//*/


//外部电平中断寄存器
#define		IFLTCNTR		XBYTE[0xF0FF]

#define		XINT01TRGR		XBYTE[0xF1FF]
	#define		XINT01TRGR_XINT1TRG	XBYTE[0xF170]
	#define		XINT01TRGR_XINT0TRG	XBYTE[0xF107]

#define		XINT23TRGR		XBYTE[0xF2FF]
	#define		XINT23TRGR_XINT3TRG	XBYTE[0xF270]
	#define		XINT23TRGR_XINT2TRG	XBYTE[0xF207]

#define		XINT45TRGR		XBYTE[0xF3FF]
	#define		XINT45TRGR_XINT5TRG	XBYTE[0xF370]
	#define		XINT45TRGR_XINT4TRG	XBYTE[0xF307]


//中断寄存器IRQM
#define		IRQ0SR		   	XBYTE[0xF4FF]
	#define		IRQ0SR_LVDINT		XBYTE[0xF408]
	#define		IRQ0SR_WDTINT		XBYTE[0xF404]
	#define		IRQ0SR_TCM3INT0		XBYTE[0xF402]
	#define		IRQ0SR_XINT0		XBYTE[0xF401]

#define		IRQ1SR		   	XBYTE[0xF5FF]
	#define		IRQ1SR_ESDINT		XBYTE[0xF508]
	#define		IRQ1SR_SADCINT		XBYTE[0xF504]
	#define		IRQ1SR_TCM3INT1		XBYTE[0xF502]
	#define		IRQ1SR_XINT1	    XBYTE[0xF501]

#define		IRQ2SR		   	XBYTE[0xF6FF]
	#define		IRQ2SR_SYSCLKFINT	XBYTE[0xF610]
	#define		IRQ2SR_UART3INT		XBYTE[0xF608]
	#define		IRQ2SR_RTCINT		XBYTE[0xF604]
	#define		IRQ2SR_TCM0INT		XBYTE[0xF602]
	#define		IRQ2SR_XINT2		XBYTE[0xF601]

#define		IRQ3SR		   	XBYTE[0xF7FF]
	#define		IRQ3SR_ECCFINT		XBYTE[0xF710]
	#define		IRQ3SR_TCM2INT1		XBYTE[0xF708]
	#define		IRQ3SR_UART1INT		XBYTE[0xF704]
	#define		IRQ3SR_TCM1INT		XBYTE[0xF702]
	#define		IRQ3SR_XINT3		XBYTE[0xF701]

#define		IRQ4SR		   	XBYTE[0xF8FF]
	#define		IRQ4SR_UART2INT		XBYTE[0xF808]
	#define		IRQ4SR_ADCINT		XBYTE[0xF804]
	#define		IRQ4SR_TCM2INT0		XBYTE[0xF802]
	#define		IRQ4SR_XINT4		XBYTE[0xF801]

#define		IRQ5SR		   	XBYTE[0xF9FF]
	#define		IRQ5SR_I2CMINT		XBYTE[0xF908]
	#define		IRQ5SR_SPIINT		XBYTE[0xF904]
	#define		IRQ5SR_I2CSINT		XBYTE[0xF902]
	#define		IRQ5SR_XINT5		XBYTE[0xF901]

#define		IRQ0ER		 	XBYTE[0xFAFF]
	#define		IRQ0ER_LVDINT		XBYTE[0xFA08]
	#define		IRQ0ER_WDTINT		XBYTE[0xFA04]
	#define		IRQ0ER_TCM3INT0	    XBYTE[0xFA02]
	#define		IRQ0ER_XINT0		XBYTE[0xFA01]

#define		IRQ1ER		 	XBYTE[0xFBFF]
	#define		IRQ1ER_ESDINT		XBYTE[0xFB08]
	#define		IRQ1ER_SADCINT		XBYTE[0xFB04]
	#define		IRQ1ER_TCM3INT1		XBYTE[0xFB02]
	#define		IRQ1ER_XINT1		XBYTE[0xFB01]

#define		IRQ2ER		 	XBYTE[0xFCFF] 
    #define     IRQ2ER_SYSCLKFINTEN XBYTE[0xFC10]
	#define		IRQ2ER_UART3INT		XBYTE[0xFC08]
	#define		IRQ2ER_RTCINT		XBYTE[0xFC04]
	#define		IRQ2ER_TCM0INT		XBYTE[0xFC02]
	#define		IRQ2ER_XINT2		XBYTE[0xFC01]

#define		IRQ3ER		 	XBYTE[0xFDFF]
    #define		IRQ3ER_ECCFINT		XBYTE[0xFD10]
	#define		IRQ3ER_TCM2INT1		XBYTE[0xFD08]
	#define		IRQ3ER_UART1INT		XBYTE[0xFD04]
	#define		IRQ3ER_TCM1INT		XBYTE[0xFD02]
	#define		IRQ3ER_XINT3		XBYTE[0xFD01]

#define		IRQ4ER		 	XBYTE[0xFEFF]
	#define		IRQ4ER_UART2INT		XBYTE[0xFE08]
	#define		IRQ4ER_ADCINT		XBYTE[0xFE04]
	#define		IRQ4ER_TCM2INT0		XBYTE[0xFE02]
	#define		IRQ4ER_XINT4		XBYTE[0xFE01]

#define		IRQ5ER			XBYTE[0xFFFF]
	#define		IRQ5ER_I2CMINT		XBYTE[0xFF08]
	#define		IRQ5ER_SPIINT		XBYTE[0xFF04]
	#define		IRQ5ER_I2CSINT		XBYTE[0xFF02]
	#define		IRQ5ER_XINT5		XBYTE[0xFF01]


// EFC
#define		FXRAMBUFLENR	XBYTE[0xB001]
#define		FXRAMBUFADRL	XBYTE[0xB002]
#define		FXRAMBUFADRH	XBYTE[0xB003]
#define		FADRL			XBYTE[0xB1FF]
#define		FADRH			XBYTE[0xB2FF]

#define		FCR				XBYTE[0xB3FF]
    #define     FCR_CRCSEQ          XBYTE[0xB3F0]
    #define		FCR_NVRREADSEL	    XBYTE[0xB308]
	#define		FCR_NVRSEL		    XBYTE[0xB304]
	#define		FCR_ERASE			XBYTE[0xB302]
	#define		FCR_PROG			XBYTE[0xB301]
							 
#define		FPSR			XBYTE[0xB4FF]
#define		FDIVR			XBYTE[0XB5FF]
#define     FCRCER          XBYTE[0xB6FF]
    #define     FCRCER_CODECRCEN    XBYTE[0xB601]

#define     FCRCSR          XBYTE[0xB7FF]
    #define     FCRCSR_CODECRCSR    XBYTE[0xB701]


#define     CHKCFGCR        XBYTE[0xB004]
//                CHKCFGCR_STAT     BIT4        R
//                CHKCFGCR_EN       BIT0        R/W

#define     ECCCR           XBYTE[0xB005]
//                ECC_RDNUM           BIT[7:4]  R/W
//                ECC_TYPE            BIT[3:2]  R
//                ECC_ERRSTAT         BIT1      R
//                ECC_EN              BIT0      R

#define     FRDDLYCR        XBYTE[0xB007]
#define     ECCINTCR        XBYTE[0xB008]
#define     ECCSR           XBYTE[0xB009]


// UART1
#define		UCR1		    XBYTE[0xD0FF]
	#define		UCR1_RXTMOUTEN	    XBYTE[0xD010]
//	#define		UCR1_LPIDLEWKUPEN	XBYTE[0xD008]
	#define		UCR1_BPRREC			XBYTE[0xD004]
	#define		UCR1_RXEN			XBYTE[0xD002]
	#define		UCR1_TXEN			XBYTE[0xD001]

#define		USETR1			XBYTE[0xD1FF]
	#define		USETR1_PARSEL		XBYTE[0xD160]
	#define		USETR1_STOPBIT	    XBYTE[0xD110]
	#define		USETR1_BITNUM		XBYTE[0xD10F]
	
#define		UBPRL1			XBYTE[0xD2FF]
#define		UBPRH1			XBYTE[0xD3FF]

#define		UIER1			XBYTE[0xD4FF]
	#define		UIER1_TXIE			XBYTE[0xD480]
	#define		UIER1_RXIE			XBYTE[0xD440]
    #define     UIER1_TXDONEIE      XBYTE[0XD420]
    #define     UIER1_RXFULLIE      XBYTE[0XD410]
    #define     UIER1_RXTMOUTIE     XBYTE[0XD408]

#define		USR1			XBYTE[0xD5FF]
    #define     USR1_RXTMOUT        XBYTE[0XD580]
    #define     USR1_DMATXDONE      XBYTE[0XD540]
    #define     USR1_DMARXFULL      XBYTE[0XD520]
	#define		USR1_TXDONE			XBYTE[0xD510]
	#define		USR1_RXREADY		XBYTE[0xD508]
	#define		USR1_OVER			XBYTE[0xD504]
	#define		USR1_STOPB			XBYTE[0xD502]
	#define		USR1_PAR			XBYTE[0xD501]
       
#define		UTX1DR			XBYTE[0xD700]
#define		URX1DR			XBYTE[0xD701]

#define     UTX1DMACR       XBYTE[0XD702]
#define     UTX1DMAADDRL    XBYTE[0xD703]
#define     UTX1DMAADDRH    XBYTE[0xD704]

#define     URX1DMACR       XBYTE[0XD705]
#define     URX1DMAADDRL    XBYTE[0xD706]
#define     URX1DMAADDRH    XBYTE[0xD707]

#define     URX1TMOUT       XBYTE[0xD709]
#define     URX1TMOUTRXLEN  XBYTE[0xD70A]


// UART2
#define		UCR2            XBYTE[0x18FF]
	#define		UCR2_RXTMOUTEN	    XBYTE[0x1810]
//	#define		UCR2_LPIDLEWKUPEN	XBYTE[0x1808]
	#define		UCR2_BPRREC		    XBYTE[0x1804]
	#define		UCR2_RXEN			XBYTE[0x1802]
	#define		UCR2_TXEN			XBYTE[0x1801]

#define		USETR2			XBYTE[0x19FF]
	#define		USETR2_PARSEL		XBYTE[0x1960]
	#define		USETR2_STOPBIT	    XBYTE[0x1910]
	#define		USETR2_BITNUM		XBYTE[0x190F]
	
#define		UBPRL2			XBYTE[0x1AFF]
#define		UBPRH2			XBYTE[0x1BFF]

#define		UIER2			XBYTE[0x1CFF]
	#define		UIER2_TXIE			XBYTE[0x1C80]
	#define		UIER2_RXIE			XBYTE[0x1C40]
    #define     UIER2_TXDONEIE      XBYTE[0X1C20]
    #define     UIER2_RXFULLIE      XBYTE[0X1C10]
    #define     UIER2_RXTMOUTIE     XBYTE[0X1C08]

#define		USR2			XBYTE[0x1DFF]     
    #define     USR2_RXTMOUT        XBYTE[0X1D80]
    #define     USR2_DMATXDONE      XBYTE[0X1D40]
    #define     USR2_DMARXFULL      XBYTE[0X1D20]
	#define		USR2_TXDONE			XBYTE[0x1D10]
	#define		USR2_RXREADY		XBYTE[0x1D08]
	#define		USR2_OVER			XBYTE[0x1D04]
	#define		USR2_STOPB			XBYTE[0x1D02]
	#define		USR2_PAR		    XBYTE[0x1D01] 
      
#define		UTX2DR			XBYTE[0x1F00]
#define		URX2DR			XBYTE[0x1F01]

#define     UTX2DMACR       XBYTE[0X1F02]
#define     UTX2DMAADDRL    XBYTE[0x1F03]
#define     UTX2DMAADDRH    XBYTE[0x1F04]

#define     URX2DMACR       XBYTE[0X1F05]
#define     URX2DMAADDRL    XBYTE[0x1F06]
#define     URX2DMAADDRH    XBYTE[0x1F07]

#define     URX2TMOUT       XBYTE[0x1F09]
#define     URX2TMOUTRXLEN  XBYTE[0x1F0A]


// UART3
#define		UCR3            XBYTE[0x12FF]
	#define		UCR3_RXTMOUTEN	    XBYTE[0x1210]
//	#define		UCR3_LPIDLEWKUPEN	XBYTE[0x1208]
	#define		UCR3_BPRREC		    XBYTE[0x1204]
	#define		UCR3_RXEN			XBYTE[0x1202]
	#define		UCR3_TXEN			XBYTE[0x1201]

#define		USETR3			XBYTE[0x13FF]
	#define		USETR3_PARSEL		XBYTE[0x1360]
	#define		USETR3_STOPBIT	    XBYTE[0x1310]
	#define		USETR3_BITNUM		XBYTE[0x130F]
	
#define		UBPRL3			XBYTE[0x14FF]
#define		UBPRH3			XBYTE[0x15FF]

#define		UIER3			XBYTE[0x16FF]
	#define		UIER3_TXIE			XBYTE[0x1680]
	#define		UIER3_RXIE			XBYTE[0x1640]
    #define     UIER3_TXDONEIE      XBYTE[0X1620]
    #define     UIER3_RXFULLIE      XBYTE[0X1610]
    #define     UIER3_RXTMOUTIE     XBYTE[0X1608]

#define		USR3			XBYTE[0x17FF]     
    #define     USR3_RXTMOUT        XBYTE[0X1780]
    #define     USR3_DMATXDONE      XBYTE[0X1740]
    #define     USR3_DMARXFULL      XBYTE[0X1720]
	#define		USR3_TXDONE			XBYTE[0x1710]
	#define		USR3_RXREADY		XBYTE[0x1708]
	#define		USR3_OVER			XBYTE[0x1704]
	#define		USR3_STOPB			XBYTE[0x1702]
	#define		USR3_PAR		    XBYTE[0x1701] 
      
#define		UTX3DR			XBYTE[0x1E00]
#define		URX3DR			XBYTE[0x1E01]

#define     UTX3DMACR       XBYTE[0X1E02]
#define     UTX3DMAADDRL    XBYTE[0x1E03]
#define     UTX3DMAADDRH    XBYTE[0x1E04]

#define     URX3DMACR       XBYTE[0X1E05]
#define     URX3DMAADDRL    XBYTE[0x1E06]
#define     URX3DMAADDRH    XBYTE[0x1E07]

#define     URX3TMOUT       XBYTE[0x1E09]
#define     URX3TMOUTRXLEN  XBYTE[0x1E0A]


// SPI
#define		SPICR			XBYTE[0xE0FF]
	#define		SPICR_MSSEL			XBYTE[0xE080]
	#define		SPICR_CSMODE		XBYTE[0xE040]
	#define		SPICR_DORD			XBYTE[0xE020]
	#define		SPICR_FIFOCLR		XBYTE[0xE010]
	#define		SPICR_CPHA			XBYTE[0xE008]
	#define		SPICR_CPOL			XBYTE[0xE004]
	#define		SPICR_TXEN			XBYTE[0xE002]
	#define		SPICR_RXEN			XBYTE[0xE001]

#define		SPISFMR			XBYTE[0XE1FF]
	#define     SPISFMR_CS          XBYTE[0XE101] 

#define		SPIIER			XBYTE[0xE2FF]
	#define		SPIIER_RXFFULL		XBYTE[0xE210]
	#define		SPIIER_RXFHALF		XBYTE[0xE208]
	#define		SPIIER_RXFNOTEMPTY	XBYTE[0xE204]
	#define		SPIIER_TXFFULL		XBYTE[0xE202]
	#define		SPIIER_TXFEMPTY		XBYTE[0xE201]

#define		SPIBPR			XBYTE[0xE3FF]

#define		SPISR			XBYTE[0xE4FF]
	#define		SPISR_TRANS			XBYTE[0xE480]
	#define		SPISR_FWRSR			XBYTE[0xE440]
	#define		SPISR_RXFOV			XBYTE[0xE420]
	#define		SPISR_RXFFULL		XBYTE[0xE410]
	#define		SPISR_RXFHALF		XBYTE[0xE408]
	#define		SPISR_RXFNOTEMPTY	XBYTE[0xE404]
	#define		SPISR_TXFFULL		XBYTE[0xE402]
	#define		SPISR_TXFEMPTY		XBYTE[0xE401]

#define		SPIDR			XBYTE[0xE5FF] 


// WDT
#define		WDTCR			XBYTE[0x60FF]
	#define		WDTCR_WDPC		    XBYTE[0x60FE]
	#define		WDTCR_WDP			XBYTE[0x6001]

#define		WDTSETR			XBYTE[0x61FF]
	#define		WDTSETR_CNTDIV		XBYTE[0x61F0]
	#define		WDTSETR_CNTLEN		XBYTE[0x610F]

#define		WDTSR			XBYTE[0x62FF]
	#define		WDTSR_WDTINT		XBYTE[0x6201]

#define     WDTENR          XBYTE[0x63FF]
	#define		WDTENR_CNTEN		XBYTE[0x6301]


// RTC
#define		RTCCLKSELR		XBYTE[0x105B]

#define		RTCCR			XBYTE[0xE8FF]
	#define		RTCCR_RTCEN			XBYTE[0xE880]
	#define		RTCCR_INTCEN		XBYTE[0xE810]
	#define		RTCCR_INTDEN		XBYTE[0xE808]
	#define		RTCCR_INTHEN		XBYTE[0xE804]
	#define		RTCCR_INTMEN		XBYTE[0xE802]
	#define		RTCCR_INTSEN		XBYTE[0xE801]

#define		RTCSR			XBYTE[0xE9FF]
	#define		RTCSR_SETEN			XBYTE[0xE980]
	#define		RTCSR_INTCSR		XBYTE[0xE910]
	#define		RTCSR_INTDSR		XBYTE[0xE908]
	#define		RTCSR_INTHSR		XBYTE[0xE904]
	#define		RTCSR_INTMSR		XBYTE[0xE902]
	#define		RTCSR_INTSSR		XBYTE[0xE901]

#define		RTCHDR			XBYTE[0xEAFF]
#define		RTCMDR			XBYTE[0xEBFF]
#define		RTCSDR			XBYTE[0xECFF]
#define		RTCAHDR			XBYTE[0xEDFF]
#define		RTCAMDR			XBYTE[0xEEFF]
#define		RTCASDR			XBYTE[0xEFFF]


// ADC
#define		ADCDIVCR		XBYTE[0xB8FF]
#define		ADCSELR			XBYTE[0xB9FF]
	#define   	ADCSELR_FLITNUM		XBYTE[0xB9E0]
	#define   	ADCSELR_CHLNUM		XBYTE[0xB91F]

#define		ADCSR			XBYTE[0xBAFF]
	#define		ADCSR_SAMPEND		XBYTE[0xBA01]
		
#define		ADCCR			XBYTE[0xBBFF]
	#define		ADCCR_TRIG			XBYTE[0xBB80]
	#define		ADCCR_MODE			XBYTE[0xBB40]
	#define		ADCCR_VREFS			XBYTE[0xBB20]//必须为1
	#define		ADCCR_SLEEP			XBYTE[0xBB10]
	#define		ADCCR_INTEN			XBYTE[0xBB08]
	#define		ADCCR_TRIM			XBYTE[0xBB04]
	#define		ADCCR_SAMPCNT		XBYTE[0xBB03]

#define		ADCDRL			XBYTE[0xBCFF]
#define		ADCDRH			XBYTE[0xBDFF]


//I2C Slaver		
#define		I2CSCR 			XBYTE[0xD8FF]
//	#define     I2CSCR_LPIDLEWKUPEN XBYTE[0xD880]
	#define     I2CSCR_MODE    		XBYTE[0xD860]
	#define     I2CSCR_ACKEN   		XBYTE[0xD810]
	#define    I2CSSR_RXIDADDRINTEN XBYTE[0xD808]
	#define     I2CSSR_TXDATAINTEN	XBYTE[0xD804]
	#define     I2CSSR_RXDATAINTEN  XBYTE[0xD802]
	#define     I2CSSR_RXHADDRINTEN XBYTE[0xD801]

#define		I2CSSR			XBYTE[0xD9FF]
	#define     I2CSSR_SENDBUSY     XBYTE[0xD910]
	#define     I2CSSR_RXIDADDR     XBYTE[0xD908]
	#define     I2CSSR_TXDATA	    XBYTE[0xD904]
	#define     I2CSSR_RXDATA       XBYTE[0xD902]
	#define     I2CSSR_RXHADDR      XBYTE[0xD901]

#define		I2CSDRSEL		XBYTE[0xDA03]
#define		I2CSDR			XBYTE[0xDBFF]

#define		I2CSADDR		XBYTE[0xDCFF]
	#define     I2C_ADDRESS         XBYTE[0xDCFE]
	#define     I2C_WEN		        XBYTE[0xDC01]

#define		I2CSRHADR		XBYTE[0xDDFF]
#define		I2CSHADR		XBYTE[0xDEFF]


// I2C Master
#define		I2CMPRERL		XBYTE[0xC8FF]
#define		I2CMPRERH		XBYTE[0xC9FF]

#define		I2CMCR			XBYTE[0xCAFF]
	#define		I2CMCR_I2CMEN		XBYTE[0XCA80]
	#define		I2CMCR_I2CMIE		XBYTE[0XCA40]

#define		I2CMDR		    XBYTE[0xCBFF]

#define		I2CMCTR			XBYTE[0xCCFF]
	#define		I2CMCTR_START		XBYTE[0xCC80]
	#define		I2CMCTR_STOP		XBYTE[0xCC40]
	#define		I2CMCTR_RD			XBYTE[0xCC20]
	#define		I2CMCTR_WR			XBYTE[0xCC10]
	#define		I2CMCTR_ACK			XBYTE[0xCC02]
	#define		I2CMCTR_CLRIF		XBYTE[0xCC01]

#define		I2CMSR			XBYTE[0xCDFF]
	#define		I2CMSR_RXACK		XBYTE[0xCD80]
	#define		I2CMSR_BUSY			XBYTE[0xCD40]
	#define		I2CMSR_AL			XBYTE[0xCD20]
	#define		I2CMSR_TIP			XBYTE[0xCD02]
	#define		I2CMSR_IF			XBYTE[0xCD01]


// SADC
#define 	SCR0			XBYTE[0x90FF]
 #define		SCR0_VSET		XBYTE[0x9080]   //ADD 72
	#define		SCR0_START			XBYTE[0x9040]
	#define 	SCR0_CTRLMODE		XBYTE[0x9030]
	#define 	SCR0_FLTMODE		XBYTE[0x9008]
//	#define		SCR0_BLEN			  XBYTE[0x9004]
	#define 	SCR0_FLTEN			XBYTE[0x9002]
	#define		SCR0_SAMPEN			XBYTE[0x9001]

#define 	SCR1			XBYTE[0x91FF]
	#define 	SCR1_WORKMODE		XBYTE[0x9180]
	#define 	SCR1_ANALOGEN		XBYTE[0x9140]
	#define		SCR1_VSET			  XBYTE[0x9130]
	#define		SCR1_SHIFT			XBYTE[0x910c]
	#define		SCR1_FLOW			XBYTE[0x9102]
	#define		SCR1_RESSEL			XBYTE[0x9101]

#define 	SCR2			XBYTE[0x92FF]
//	#define		SCR2_STABLEN		XBYTE[0X92FC]
//	#define		SCR2_BITLEN			XBYTE[0X9203]

#define 	SCR3			XBYTE[0x93FF]
	#define		SCR3_SHDIV			XBYTE[0x933F]


#define 	SSCAN			XBYTE[0x94FF]
   #define		SSCAN_EN			  XBYTE[0x9480]
   #define		SSCAN_VREFSET		XBYTE[0x9470]
   #define		SSCAN_SHIFT		  XBYTE[0x940F]
#define 	SSCANH		   XBYTE[0x95FF]
   #define		OP_SIGN				XBYTE[0x9580]
   #define		OP_SHIFT		 	XBYTE[0x9570]
    #define		OP_DATA				XBYTE[0x950F]
#define 	SSR		  		XBYTE[0x96FF]
//	#define 	SSR_CAPDONE			XBYTE[0x9708]
	#define 	SSR_BLEND			XBYTE[0x9604]
	#define 	SSR_FLTEND			XBYTE[0x9602]
	#define 	SSR_SAMPEND			XBYTE[0x9601]

#define 	SDRL			XBYTE[0x97FF]
#define 	SDRM			XBYTE[0x98FF]
#define		SFLTCNT		    XBYTE[0x99FF]
#define		SSELR			XBYTE[0x9AFF]
	#define 	WAIT_CENT		XBYTE[0x9AE0]       //72 ADD 
	#define 	SENSOR_ID		XBYTE[0x9A1F]       //72 ADD 
#define		SNUMR			XBYTE[0x9BFF]
#define			CAP_NUM		 		XBYTE[0x9BE0]
#define			H_SENSOR_NUM		XBYTE[0x9B1F]

#define		BASELINEMIDRL	XBYTE[0x9CFF]
#define		BASELINEMIDRH	XBYTE[0x9DFF]
#define		SWKCR			XBYTE[0x9EFF]
    #define		CHARG_CLK_SEL		XBYTE[0x9E40]    //72 ADD RANG choice
	#define		SWKCR_PD_TIME		XBYTE[0x9E38]
	#define		SWKCR_CMPR_SET		XBYTE[0x9E07]
												 
#define		SALGCR			XBYTE[0x9FFF]
    //NA
	#define		SALGCR_FLTSTART		XBYTE[0x9F40]
	#define		SALGCR_BLSTART		XBYTE[0x9F20]
	#define		SALGCR_INDEX		XBYTE[0x9F1F]

#define		NOISEPOS		XBYTE[0xA0FF]
#define		NOISENEG		XBYTE[0xA1FF]
#define		BUCKPOSL		XBYTE[0xA2FF]
#define		BUCKPOSH		XBYTE[0xA3FF]
#define		BUCKNEGL		XBYTE[0xA4FF]
#define		BUCKNEGH		XBYTE[0xA5FF]
#define		RAMADRL			XBYTE[0xA6FF]
#define		RAMADRH			XBYTE[0xA7FF]
#define		BSSTEP			XBYTE[0xA8FF]
#define 	SDRH		   	XBYTE[0xA9FF]

// SADC
#define 	SCR0			XBYTE[0x90FF]
 #define		SCR0_VSET		XBYTE[0x9080]   //ADD 72
	#define		SCR0_START		XBYTE[0x9040]
	#define 	SCR0_CTRLMODE		XBYTE[0x9030]
	#define 	SCR0_FLTMODE		XBYTE[0x9008]
	#define		SCR0_BLEN		XBYTE[0x9004]
	#define 	SCR0_FLTEN		XBYTE[0x9002]
	#define		SCR0_SAMPEN		XBYTE[0x9001]

#define 	SCR1			XBYTE[0x91FF]
	#define 	SCR1_WORKMODE		XBYTE[0x9180]
	#define 	SCR1_ANALOGEN		XBYTE[0x9140]
	#define		SCR1_VSET		XBYTE[0x9130]
	#define		SCR1_SHIFT		XBYTE[0x910c]
	#define		SCR1_FLOW		XBYTE[0x9102]
	#define		SCR1_RESSEL		XBYTE[0x9101]

#define 	SCR2			XBYTE[0x92FF]

#define 	SCR3			XBYTE[0x93FF]
	#define		SCR3_SHDIV			XBYTE[0x933F]


#define 	SSCANL			XBYTE[0x94FF]
   #define		SSCAN_EN			  XBYTE[0x9480]
   #define		SSCAN_VREFSET		XBYTE[0x9470]
   #define		SSCAN_SHIFT		  XBYTE[0x940F]
#define 	SSCANH		   XBYTE[0x95FF]
   #define		OP_SIGN				XBYTE[0x9580]
   #define		OP_SHIFT		 	XBYTE[0x9570]
    #define		OP_DATA				XBYTE[0x950F]
#define 	SSR		  		XBYTE[0x96FF]
//	#define 	SSR_CAPDONE			XBYTE[0x9708]
	#define 	SSR_BLEND			XBYTE[0x9604]
	#define 	SSR_FLTEND			XBYTE[0x9602]
	#define 	SSR_SAMPEND			XBYTE[0x9601]

#define 	SDRL			XBYTE[0x97FF]
#define 	SDRM			XBYTE[0x98FF]
#define		SFLTCNT		    	XBYTE[0x99FF]
#define		SSELR			XBYTE[0x9AFF]
	#define 	WAIT_CENT		XBYTE[0x9AE0]       //72 ADD 
	#define 	SENSOR_ID		XBYTE[0x9A1F]       //72 ADD 
#define		SNUMR			XBYTE[0x9BFF]
#define			CAP_NUM		 		XBYTE[0x9BE0]
#define			H_SENSOR_NUM		XBYTE[0x9B1F]

#define		BASELINEMIDRL	XBYTE[0x9CFF]
#define		BASELINEMIDRH	XBYTE[0x9DFF]
#define		SWKCR			XBYTE[0x9EFF]
    #define		CHARG_CLK_SEL		XBYTE[0x9E40]    //72 ADD RANG choice
	#define		SWKCR_PD_TIME		XBYTE[0x9E38]
	#define		SWKCR_CMPR_SET		XBYTE[0x9E07]
												 
#define		SALGCR			XBYTE[0x9FFF]
    	//NA
	#define		SALGCR_FLTSTART		XBYTE[0x9F40]
	#define		SALGCR_BLSTART		XBYTE[0x9F20]
	#define		SALGCR_INDEX		XBYTE[0x9F1F]

#define		NOISEPOS		XBYTE[0xA0FF]
#define		NOISENEG		XBYTE[0xA1FF]
#define		BUCKPOSL		XBYTE[0xA2FF]
#define		BUCKPOSH		XBYTE[0xA3FF]
#define		BUCKNEGL		XBYTE[0xA4FF]
#define		BUCKNEGH		XBYTE[0xA5FF]
#define		RAMADRL			XBYTE[0xA6FF]
#define		RAMADRH			XBYTE[0xA7FF]
#define		BSSTEP			XBYTE[0xA8FF]
#define 	SDRH		   	XBYTE[0xA9FF]
	

// LED
#define		LEDDR0			XBYTE[0x1100]
#define		LEDDR1			XBYTE[0x1101]
#define		LEDDR2			XBYTE[0x1102] 
#define		LEDDR3			XBYTE[0x1103]
#define		LEDDR4			XBYTE[0x1104]
#define		LEDDR5			XBYTE[0x1105]
#define		LEDDR6			XBYTE[0x1106]
#define		LEDDR7			XBYTE[0x1107]
#define		LEDDR8			XBYTE[0x1108]
#define		LEDDR9			XBYTE[0x1109]
#define		LEDDR10			XBYTE[0x110A]
#define		LEDDR11			XBYTE[0x110B] 
#define		LEDDR12			XBYTE[0x110C] 
#define		LEDDR13			XBYTE[0x110D]

#define		LEDCR			XBYTE[0xC0FF]
 	#define    LEDCR_WREN			XBYTE[0xC002]
	#define    LEDCR_ONOFF		    XBYTE[0xC001]

#define		LEDSETR			XBYTE[0xC1FF]
	#define		LEDSETR_TYPE		XBYTE[0xC180]
	#define		LEDSETR_DISPLAYMODE XBYTE[0xC170]
	#define		LEDSETR_DRIVEMODE	XBYTE[0xC108]
	#define		LEDSETR_GRAY		XBYTE[0xC107]

#define		LEDDIVR			XBYTE[0xC2FF]
	#define		LEDDIVR_SEGDR	    XBYTE[0xC210]
	#define		LEDDIVR_COMSSEL     XBYTE[0xC208]
	#define		LEDDIVR_DIVR		XBYTE[0xC207]

#define		GRIDVLDL			XBYTE[0xC3FF]
#define		GRIDVLDH			XBYTE[0xC4FF]


//PWM
#define 	PWM1CR			XBYTE[0x68FF]
	#define		PWM1CR_PWM1EN		XBYTE[0x6820]
	#define		PWM1CR_OUTINIT	    XBYTE[0x6810]
	#define		PWM1CR_CLKDIV		XBYTE[0x6807]

#define 	PWM2CR			XBYTE[0x69FF]
	#define		PWM2CR_PWM2EN		XBYTE[0x6920]
	#define		PWM2CR_OUTINIT		XBYTE[0x6910]
	#define		PWM2CR_CLKDIV		XBYTE[0x690F]

#define 	PWM3CR			XBYTE[0x6400]
//	bit5		PWM3CR_PWM4EN		
//	bit4		PWM3CR_OUTINIT	    
//	bit2:0		PWM3CR_CLKDIV		

#define 	PWM4CR			XBYTE[0x6401]
//	bit5		PWM4CR_PWM4EN		
//	bit4		PWM4CR_OUTINIT		
//	bit3:0		PWM4CR_CLKDIV		

#define 	PWM5CR			XBYTE[0x6408]	
//	bit5		PWM5CR_PWM5EN		
//	bit4		PWM5CR_OUTINIT		
//	bit2:0		PWM5CR_CLKDIV		

#define		PWM2LR			XBYTE[0x6EFF]
#define		PWM2HR			XBYTE[0x6FFF]
#define		PWM4LR			XBYTE[0x6406]
#define		PWM4HR			XBYTE[0x6407]
#define		PWM1LRL			XBYTE[0x6AFF]
#define		PWM1LRH			XBYTE[0x6BFF]
#define		PWM1HRL			XBYTE[0x6CFF]
#define		PWM1HRH			XBYTE[0x6DFF]
#define		PWM3LRL			XBYTE[0x6402]
#define		PWM3LRH			XBYTE[0x6403]
#define		PWM3HRL			XBYTE[0x6404]
#define		PWM3HRH			XBYTE[0x6405]
#define		PWM5LRL			XBYTE[0x640A]
#define		PWM5LRH			XBYTE[0x640B]
#define		PWM5HRL			XBYTE[0x640C]
#define		PWM5HRH			XBYTE[0x640D]

#define		PWM135DTCTRL	XBYTE[0x6409]
//bit7:6	DTDIV
//bit5		DT5EN_INV
//bit4		DT5EN
//bit3		DT3EN_INV
//bit2		DT3EN
//bit1		DT1EN_INV
//bit0		DT1EN

#define		PWM1DTCR		XBYTE[0x6410]
#define		PWM1INVDTCR		XBYTE[0x6411]
#define		PWM3DTCR		XBYTE[0x6412]
#define		PWM3INVDTCR		XBYTE[0x6413]
#define		PWM5DTCR		XBYTE[0x6414]
#define		PWM5INVDTCR		XBYTE[0x6415]

#define		PWMSYNC		    XBYTE[0x6416]
#define		PWM135OUTCR		XBYTE[0x640E]
#define		PWM135INVOUTCR	XBYTE[0x640F]


//TIMER0
#define		T0CKCR			XBYTE[0x70FF]
	#define		T0CKCR_CLKEN		XBYTE[0x7020]
	#define		T0CKCR_CLKSEL		XBYTE[0x7010]
	#define		T0CKCR_CLKDIV		XBYTE[0x7007]

#define		T0CR			XBYTE[0x71FF]
    #define     T0CR_READMODE       XBYTE[0X7110]
	#define		T0CR_INTEN			XBYTE[0x7108]
	#define		T0CR_OUTSEL		    XBYTE[0x7104]
	#define		T0CR_MODE			XBYTE[0x7102]
	#define		T0CR_TEN		    XBYTE[0x7101]

#define		T0CMP0			XBYTE[0x72FF]
#define		T0CMP1			XBYTE[0x73FF]
#define		T0SR			XBYTE[0x74FF]
	#define		T0SR_WREN			XBYTE[0x7402]
	#define		T0SR_INTSR		    XBYTE[0x7401]
	
#define     T0CNT           XBYTE[0x76FF]


//TIMER1
#define		T1CKCR			XBYTE[0x78FF]
	#define		T1CKCR_CLKEN		XBYTE[0x7820]
	#define		T1CKCR_CLKSEL		XBYTE[0x7810]
	#define		T1CKCR_CLKDIV		XBYTE[0x780F]

#define		T1CR			XBYTE[0x79FF]
    #define     T1CR_READMODE       XBYTE[0X7980]
	#define		T1CR_INVEN			XBYTE[0x7940]
	#define		T1CR_OUTINIT		XBYTE[0x7930]
	#define		T1CR_INTEN			XBYTE[0x7908]
	#define		T1CR_OUTSEL			XBYTE[0x7904]
	#define		T1CR_MODE			XBYTE[0x7902]
	#define		T1CR_TEN		  	XBYTE[0x7901]

#define		T1CMP			XBYTE[0x7AFF] 
#define		T1SR			XBYTE[0x7BFF]
	#define		T1SR_WREN			XBYTE[0x7B02]
	#define		T1SR_INTSR		    XBYTE[0x7B01]
	
#define     T1CNT           XBYTE[0x7DFF]


//TIMER2
#define		T2CR			XBYTE[0x80FF]
	#define		T2CR_CMP1M			XBYTE[0x8080]
	#define		T2CR_CMP0M			XBYTE[0x8040]
	#define		T2CR_INT1EN			XBYTE[0x8020]
	#define		T2CR_INT0EN			XBYTE[0x8010]
	#define		T2CR_CMP0CAP		XBYTE[0x8008]
	#define		T2CR_MODE			XBYTE[0x8007]

#define		T2CKCR			XBYTE[0x81FF]
	#define		T2CKCR_CLKEN		XBYTE[0x8180]
	#define		T2CKCR_CLKSEL		XBYTE[0x8140]
	#define		T2CKCR_EDGESEL	    XBYTE[0x8130]
    #define     T2CKCR_READMODE     XBYTE[0X8108]
	#define		T2CKCR_CLKDIV		XBYTE[0x8107]

#define		T2OCR			XBYTE[0x82FF]
	#define		T2OCR_SPO			XBYTE[0x8220]
	#define		T2OCR_SPOM			XBYTE[0x8210]
	#define		T2OCR_OUTINIT		XBYTE[0x820C]
	#define		T2OCR_INV1EN		XBYTE[0x8202]
	#define		T2OCR_INV0EN		XBYTE[0x8201]

#define		T2CMP0L			XBYTE[0x83FF]
#define		T2CMP0H			XBYTE[0x84FF]
#define		T2CMP1L			XBYTE[0x85FF]
#define		T2CMP1H			XBYTE[0x86FF] 
#define		T2SR			XBYTE[0x87FF]
	#define		T2SR_WREN			XBYTE[0x8708]
	#define		T2SR_T2OV			XBYTE[0x8704]
	#define		T2SR_INT1SR		    XBYTE[0x8702]
	#define		T2SR_INT0SR		    XBYTE[0x8701]

#define     T2CNTL          XBYTE[0xAAFF]
#define     T2CNTH          XBYTE[0xABFF]


//TIMER3
#define		T3CR			XBYTE[0x88FF]
	#define		T3CR_CMP1M			XBYTE[0x8880]
	#define		T3CR_CMP0M			XBYTE[0x8840]
	#define		T3CR_INT1EN			XBYTE[0x8820]
	#define		T3CR_INT0EN			XBYTE[0x8810]
	#define		T3CR_CMP0CAP		XBYTE[0x8808]
	#define		T3CR_MODE			XBYTE[0x8807]

#define		T3CKCR			XBYTE[0x89FF]
	#define		T3CKCR_CLKEN		XBYTE[0x8980]
	#define		T3CKCR_CLKSEL		XBYTE[0x8940]
	#define		T3CKCR_EDGESEL	    XBYTE[0x8930]
    #define     T3CKCR_READMODE     XBYTE[0X8908]
	#define		T3CKCR_CLKDIV		XBYTE[0x8907]

#define		T3OCR			XBYTE[0x8AFF]
	#define		T3OCR_SPO			XBYTE[0x8A20]
	#define		T3OCR_SPOM			XBYTE[0x8A10]
	#define		T3OCR_OUTINIT		XBYTE[0x8A0C]
	#define		T3OCR_INV1EN		XBYTE[0x8A02]
	#define		T3OCR_INV0EN		XBYTE[0x8A01]

#define		T3CMP0L			XBYTE[0x8BFF]
#define		T3CMP0H			XBYTE[0x8CFF]
#define		T3CMP1L			XBYTE[0x8DFF]
#define		T3CMP1H			XBYTE[0x8EFF] 
#define		T3SR			XBYTE[0x8FFF]
	#define		T3SR_WREN			XBYTE[0x8F08]
	#define		T3SR_T3OV			XBYTE[0x8F04]
	#define		T3SR_INT1SR		    XBYTE[0x8F02]
	#define		T3SR_INT0SR		    XBYTE[0x8F01]

#define     T3CNTL          XBYTE[0xADFF]
#define     T3CNTH          XBYTE[0xAEFF]

#endif
