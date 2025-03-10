#include "CBM7216.h"
#include "stdio.h"
#include "uart1.h"

/****************************************************************       
founction��ADC��ʼ��
parameter��
		clkdiv ����Ƶϵ��ADC ����ʱ��= fSYSCLK /(2*(ADCDIVCR+1)) ���� fSYSCLK=48M ʱ,ADCDIVCR ��ֵ����>=17��  ��ADC���1.4M��
		sel  ��bit6-4 000-110 = 1-64�β����˲�
****************************************************************/
void adcInit(uint8 div,uint8 ctrl) 
{
		ADCDIVCR = div;//����ADC�Ĳ���ʱ��Ƶ��
		ADCSR = 0 << 0;//��ADC�ж�	
		ADCCR =  ctrl|0x20;//����ADC�жϡ��ο���ѹ��������ʽ������ʱ��
		LDOCR1 |= 0x40;//����ģʽ�²���ͨ��Ϊ�ڲ�vref1vʱ��ΪӲ��ģʽʱ����ʹ��
		IRQ4ER_ADCINT = 1 << 2;//ʹ��ADC����ж�
		EX4 = 1;
		EA = 1;
}

///****************************************************************        
//founction��ADCͨ��ѡ��ɼ�
//parameter��
//		chlsel ����ͨ��ѡ�� bit4-0 0000-0111 = AN0-AN25��11010=VREF���ڲ�1v����11011 = �ڲ�1/4*VDD
//		flitnum�����˲�������bit7-5 000-110 = 1-64�β����˲�
//****************************************************************/
uint16 adcSampStart(uint8 flitnum_chlnum) 
{
	uint8 i=20;	
	ADCSELR =flitnum_chlnum;//���ò���ͨ��
	while(i--);//ѡ�����ͨ������ʱ�ٲ���   ��ʱ>=5us
	ADCCR_TRIG = 1 << 7;//����һ��ADC����
	while(0x00 == ADCSR_SAMPEND);//�ȴ��������
	ADCSR_SAMPEND = 0 << 0;
	return 	(ADCDRH << 8) | ADCDRL;//���ز���ADֵ
}



/****************************************************************   
founction��ADC����ֵ��С����ʽ��
parameter��
		mode ������ģʽ  0-����ģʽ��1-Ӳ��ģʽ
    chlsel ����ͨ��ѡ�� bit3-0 0000-0111 = AN0-AN7��1000=VREF���ڲ�1v����1001-1111 = �ڲ�1/4*VDD
		flitnum�����˲�������bit6-4 000-110 = 1-64�β����˲�

****************************************************************/
float ADCSampValue(uint8 flitnum_chlnum )
{
	    uint16 ADCSamp = 0;            //ADC����ֵΪ����
	    float ADCValue = 0;            //ת��ΪС����ʽ��������
			if((ADCCR & 0x40) == 0)
			{
				ADCSamp =  adcSampStart(flitnum_chlnum);
				ADCValue = 5.0*(ADCSamp & 0xfff)/4096 ;               //AD �����ѹ Vin=VDD*�������ֵ/1024 v
			}
			else
			{
			  ADCSamp=  adcSampStart(flitnum_chlnum);  
				ADCValue = (ADCSamp >>12)+((ADCSamp & 0x0fff )/4096);      //AD �����ѹ Vin =(�������ֵ>>10) + (�������ֵ&0x3FF)/1024 v

			}
				return ADCValue;				
}



/****************************************************************   
function����ʼ��ADC����
parameter��void	
****************************************************************/
void ADCPortInit(void)
{
		P06IOCFG = 0x09;     	 //����ΪADCͨ��
		P07IOCFG = 0x09; 
		P10IOCFG = 0x09; 
		P11IOCFG = 0x09; 
		P12IOCFG = 0x09; 
		P13IOCFG = 0x09; 
		P14IOCFG = 0x09; 
		P15IOCFG = 0x09; 
	
	
		P0OE_6 = 0x01;          //���뷽��
		P0OE_7 = 0x09;
		P1OE_0 = 0x09;
		P1OE_1 = 0x09;
		P1OE_2 = 0x09;
		P1OE_3 = 0x09;
		P1OE_4 = 0x09;
		P1OE_5 = 0x09;    
		
		P0PU_6 = 0x00;         //�����ر�
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
//Description: ��ADC LDO0������ƯУ׼-΢�����Ƚ��дֵ�Ȼ����΢�����������¶ȱ仯�ϴ�ʱ��1~5���ӽ���У׼һ��
//Input      : NO				  
//Output     : No	                  
//Return     : No
//************************************************************************************/
//bit adcLdo0Trimming(void)
//{
//			uint8 i=0,j; 
//	   bit ret=0;
//			LDOCR0 = 1 << 5;   //ʹ����Ư�ֵ�
//	    
//			while(i<=32)
//			{
//				LDOCR0 = LDOCR0 | i;      //�޸�TRIMOVALֵ��00000-11111
//				for(j=0;j<100;j++);       //��ʱԼ10us
//				if(0x80 == (LDOCR0&0x80))  //
//				{
//						ret = 1;//��ʾ�ֵ��ɹ�
//		    	break;
//				}
//				i++;
//				 LDOCR0 &= 0xDF;//�ر�LDO0 Trimming  
//	       return ret;
//			}
//}


///*********************************************************************************** 
//Function   : bit adcLdo1Trimming(void)
//Description: ��ADC LDO1������ƯУ׼-΢�����Ƚ��дֵ�Ȼ����΢�����������¶ȱ仯�ϴ�ʱ��1~5���ӽ���У׼һ��
//Input      : NO				  
//Output     : No	                  
//Return     : No
//************************************************************************************/
//bit adcLdo1Trimming(void)
//{
//	uint8 i = 0,j;
//	bit ret=0;	
//    LDOCR1 |= 1 << 5;//ʹ��LDO0 Trimming  
//    do 
//   	{	
//        LDOCR1 &= 0xE0;
//		LDOCR1 |= i;
//        for(j=0;j<100;j++);//�ȴ�10us
//		if(0x80 == (LDOCR1&0x80))//�ж�����Ƿ�Ϊ1
//		{	
//			ret = 1;//��ʾ΢���ɹ�
//			break;
//		}
//    	i++;	
//    }
//	while(32 > i);
//    LDOCR1 &= 0xDF;//�ر�LDO0 Trimming  
//	return ret;
//}

///*********************************************************************************** 
//Function   : bit adcLdoTrimming(void)
//Description: ��ADC LDO������ƯУ׼���Ƚ��дֵ�Ȼ����΢�����������¶ȱ仯�ϴ�ʱ��1~5���ӽ���У׼һ��
//Input      : NO				  
//Output     : No	                  
//Return     : No
//************************************************************************************/
//bit adcLdoTrimming(void)
//{
//	bit ret=0;	
//	if(adcLdo0Trimming())//�ȴֵ�
//		ret = adcLdo1Trimming() ;//��΢��
//	return ret;
//}
