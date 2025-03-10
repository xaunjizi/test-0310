#include "CBM7216.h"
#include "stdio.h"
#include "uart1.h"

/****************************************************************       
founction：ADC初始化
parameter：
		clkdiv ：分频系数ADC 采样时钟= fSYSCLK /(2*(ADCDIVCR+1)) ；当 fSYSCLK=48M 时,ADCDIVCR 的值必须>=17。  （ADC最大1.4M）
		sel  ：bit6-4 000-110 = 1-64次采样滤波
****************************************************************/
void adcInit(uint8 div,uint8 ctrl) 
{
		ADCDIVCR = div;//配置ADC的采样时钟频率
		ADCSR = 0 << 0;//清ADC中断	
		ADCCR =  ctrl|0x20;//配置ADC中断、参考电压、操作方式、采样时间
		LDOCR1 |= 0x40;//常规模式下采样通道为内部vref1v时或为硬件模式时必须使能
		IRQ4ER_ADCINT = 1 << 2;//使能ADC相关中断
		EX4 = 1;
		EA = 1;
}

///****************************************************************        
//founction：ADC通道选择采集
//parameter：
//		chlsel ：（通道选择） bit4-0 0000-0111 = AN0-AN25、11010=VREF（内部1v）、11011 = 内部1/4*VDD
//		flitnum：（滤波级数）bit7-5 000-110 = 1-64次采样滤波
//****************************************************************/
uint16 adcSampStart(uint8 flitnum_chlnum) 
{
	uint8 i=20;	
	ADCSELR =flitnum_chlnum;//设置采样通道
	while(i--);//选择采样通道后延时再采样   延时>=5us
	ADCCR_TRIG = 1 << 7;//触发一次ADC采样
	while(0x00 == ADCSR_SAMPEND);//等待采样完成
	ADCSR_SAMPEND = 0 << 0;
	return 	(ADCDRH << 8) | ADCDRL;//返回采样AD值
}



/****************************************************************   
founction：ADC采样值（小数形式）
parameter：
		mode ：工作模式  0-常规模式、1-硬件模式
    chlsel ：（通道选择） bit3-0 0000-0111 = AN0-AN7、1000=VREF（内部1v）、1001-1111 = 内部1/4*VDD
		flitnum：（滤波级数）bit6-4 000-110 = 1-64次采样滤波

****************************************************************/
float ADCSampValue(uint8 flitnum_chlnum )
{
	    uint16 ADCSamp = 0;            //ADC采样值为整型
	    float ADCValue = 0;            //转化为小数形式，浮点型
			if((ADCCR & 0x40) == 0)
			{
				ADCSamp =  adcSampStart(flitnum_chlnum);
				ADCValue = 5.0*(ADCSamp & 0xfff)/4096 ;               //AD 输入电压 Vin=VDD*采样输出值/1024 v
			}
			else
			{
			  ADCSamp=  adcSampStart(flitnum_chlnum);  
				ADCValue = (ADCSamp >>12)+((ADCSamp & 0x0fff )/4096);      //AD 输入电压 Vin =(采样输出值>>10) + (采样输出值&0x3FF)/1024 v

			}
				return ADCValue;				
}



/****************************************************************   
function：初始化ADC引脚
parameter：void	
****************************************************************/
void ADCPortInit(void)
{
		P06IOCFG = 0x09;     	 //设置为ADC通道
		P07IOCFG = 0x09; 
		P10IOCFG = 0x09; 
		P11IOCFG = 0x09; 
		P12IOCFG = 0x09; 
		P13IOCFG = 0x09; 
		P14IOCFG = 0x09; 
		P15IOCFG = 0x09; 
	
	
		P0OE_6 = 0x01;          //输入方向
		P0OE_7 = 0x09;
		P1OE_0 = 0x09;
		P1OE_1 = 0x09;
		P1OE_2 = 0x09;
		P1OE_3 = 0x09;
		P1OE_4 = 0x09;
		P1OE_5 = 0x09;    
		
		P0PU_6 = 0x00;         //上拉关闭
		P0PU_7 = 0x00;
		P1PU_0 = 0x00;
		P1PU_1 = 0x00;
		P1PU_2 = 0x00;
		P1PU_3 = 0x00;
		P1PU_4 = 0x00;
		P1PU_5 = 0x00;
}


///*********************************************************************************** 
//Function   : bit adcLdo0Trimming(void)
//Description: 对ADC LDO0进行温漂校准-微调（先进行粗调然后再微调），建议温度变化较大时在1~5分钟进行校准一次
//Input      : NO				  
//Output     : No	                  
//Return     : No
//************************************************************************************/
//bit adcLdo0Trimming(void)
//{
//			uint8 i=0,j; 
//	   bit ret=0;
//			LDOCR0 = 1 << 5;   //使能温漂粗调
//	    
//			while(i<=32)
//			{
//				LDOCR0 = LDOCR0 | i;      //修改TRIMOVAL值从00000-11111
//				for(j=0;j<100;j++);       //延时约10us
//				if(0x80 == (LDOCR0&0x80))  //
//				{
//						ret = 1;//表示粗调成功
//		    	break;
//				}
//				i++;
//				 LDOCR0 &= 0xDF;//关闭LDO0 Trimming  
//	       return ret;
//			}
//}


///*********************************************************************************** 
//Function   : bit adcLdo1Trimming(void)
//Description: 对ADC LDO1进行温漂校准-微调（先进行粗调然后再微调），建议温度变化较大时在1~5分钟进行校准一次
//Input      : NO				  
//Output     : No	                  
//Return     : No
//************************************************************************************/
//bit adcLdo1Trimming(void)
//{
//	uint8 i = 0,j;
//	bit ret=0;	
//    LDOCR1 |= 1 << 5;//使能LDO0 Trimming  
//    do 
//   	{	
//        LDOCR1 &= 0xE0;
//		LDOCR1 |= i;
//        for(j=0;j<100;j++);//等待10us
//		if(0x80 == (LDOCR1&0x80))//判断输出是否为1
//		{	
//			ret = 1;//表示微调成功
//			break;
//		}
//    	i++;	
//    }
//	while(32 > i);
//    LDOCR1 &= 0xDF;//关闭LDO0 Trimming  
//	return ret;
//}

///*********************************************************************************** 
//Function   : bit adcLdoTrimming(void)
//Description: 对ADC LDO进行温漂校准（先进行粗调然后再微调），建议温度变化较大时在1~5分钟进行校准一次
//Input      : NO				  
//Output     : No	                  
//Return     : No
//************************************************************************************/
//bit adcLdoTrimming(void)
//{
//	bit ret=0;	
//	if(adcLdo0Trimming())//先粗调
//		ret = adcLdo1Trimming() ;//再微调
//	return ret;
//}
