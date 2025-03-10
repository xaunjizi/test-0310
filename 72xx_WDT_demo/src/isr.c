#include "CBM7216.h"
#include "rtc.h"
#include "uart1.h"


uint16 count = 0;
uint8 flag = 0;


/*********************************************************************************** 
Function   : void EXT0_IRQHandler(void)
Description: ϵͳ�ж�0��ں���
Input      : No      
Output     : No	                  
Return     : No
************************************************************************************/
void EXT0_IRQHandler(void) interrupt 0
{
	/*---�ⲿ�ж�0---*/
    if(0x01 == IRQ0SR_XINT0)
    {   
        IRQ0SR_XINT0 = 0;
				
    }
    
    /*---T3�ж�0---*/
    if(0x02 == IRQ0SR_TCM3INT0) 
		{	
			T3SR_INT0SR = 0 << 0; //��T3�ж�0��־λ

			/*�жϴ������......*/
		}
		
			/*---WDT�ж�---*/	
		if(0x04 == IRQ0SR_WDTINT) 
		{
			if(0x01 == WDTSR_WDTINT) 
			{
				WDTSR_WDTINT = 0;
				P2_0 = ~P2_0;
				UartPrintf("Run");            //�жϲ���
		    UartPrintf("\r\n");
				/* �жϴ������......*/			
			}
		}
    
    /*---LVD�ж�---*/
    if(0x08 == IRQ0SR_LVDINT)
    {
        if(LVDCR_LVDSR==0x80)
        {
            LVDCR_LVDSR=0;//�����ֶ�����������һֱ��Ӧ�ж�
        }
    }
}

/*********************************************************************************** 
Function   : void EXT1_IRQHandler(void)
Description: ϵͳ�ж�1��ں���
Input      : No      
Output     : No	                  
Return     : No
************************************************************************************/
void EXT1_IRQHandler(void)	interrupt 1
{
//	static uint16 timer3_cnt1 = 0;
    /*---�ⲿ�ж�1---*/
    if(0x01 == IRQ1SR_XINT1)
    {   
        IRQ1SR_XINT1 = 0;
	
    }

    if(0x02 == IRQ1SR_TCM3INT1) //T3�ж�1 
		{	
			T3SR_INT1SR = 0 << 1;		//��T3�ж�1��־λ

			/*�жϴ������......*/	
		}

//	if(0x04 == IRQ1SR_SADCINT)
	
    /*---ESD�ж�---*/
    if(0x08 == IRQ1SR_ESDINT)
    {
        IRQ1SR_ESDINT = 1 ;//д1����
        if(MISCR3_ESDSR ==0x04)
        {
            MISCR3_ESDSR = 0 ; //�����ֶ�����������һֱ��Ӧ�ж�
        }
    }
}

/*********************************************************************************** 
Function   : void EXT2_IRQHandler(void)
Description: ϵͳ�ж�2��ں���
Input      : No      
Output     : No	                  
Return     : No
************************************************************************************/
void EXT2_IRQHandler(void)	interrupt 2 
{
    /*---�ⲿ�ж�2---*/
    if(0x01 == IRQ2SR_XINT2)
    {
        IRQ2SR_XINT2 = 0;
		/*�жϴ������......*/
			
    }

		if(0x02 == IRQ2SR_TCM0INT) //T0�ж�
		{			
			T0SR_INTSR = 0 << 0; //��T0�жϱ�־λ
					/*�жϴ������......*/
		}

    if(0x04 == IRQ2SR_RTCINT) 
		{
			if(0x01 == RTCSR_INTSSR) 
			{
				RTCSR_INTSSR = 0 << 0;
				/*�жϴ������......*/
			} 
			if(0x02 == RTCSR_INTMSR) 
			{
				RTCSR_INTMSR = 0 << 1;           
				/*�жϴ������......*/
			}
			if(0x04 == RTCSR_INTHSR) 
			{
				RTCSR_INTHSR = 0 << 2;
				/*�жϴ������......*/
			}
			if(0x08 == RTCSR_INTDSR) 
			{
				RTCSR_INTDSR = 0 << 3;
				/*�жϴ������......*/
			}
			if(0x10 == RTCSR_INTCSR)  
			{
				RTCSR_INTCSR = 0 << 4;
				/*�жϴ������......*/
			}			
		}
		if(0x08 == IRQ2SR_UART3INT) //UART3�ж�
		{			
				if(0x08 == USR3_RXREADY)
				{     
					USR3=0x08;
					/*�жϴ������......*/ 
				}
				if(0x80 == USR3_RXTMOUT)
				{
					USR3 = 0x80 ;//д1��0�������һֱ���ж�
					/*�жϴ������......*/ 
				}
    }	

    if(0x10 == IRQ2SR_SYSCLKFINT)
    {
        MISCR3_SYSCLKFINTSR = 0;
		/*�жϴ������......*/
    }
}

/*********************************************************************************** 
Function   : void EXT3_IRQHandler(void)
Description: ϵͳ�ж�3��ں���
Input      : No      
Output     : No	                  
Return     : No
************************************************************************************/
void EXT3_IRQHandler(void) interrupt 3
{		
	/*---�ⲿ�ж�3---*/
    if(0x01 == IRQ3SR_XINT3)
    {   
        IRQ3SR_XINT3 = 0;
		/*�жϴ������......*/
    }
		if(0x08 == IRQ3SR_TCM2INT1)//T2�ж�1 
		{
			T2SR_INT1SR=0;
			/*�жϴ������......*/		
		}

    if(0x02 == IRQ3SR_TCM1INT)//T1�ж� 
    {			
			T1SR_INTSR = 0 << 0;		//��T1�жϱ�־λ
			if(++count >= 5)
			{
					count = 0;
					flag = 1;
			}

			 //�жϴ������......
		}

		if(0x04 == IRQ3SR_UART1INT) //�ж��Ƿ���uart�ж� 
		{			
			if(0x08 == USR1_RXREADY) 
			{			
				USR1=0x08;
				/*�жϴ������......*/ 				
			}	
			if(0x80 == USR1_RXTMOUT)
			{
				USR1 = 0x80 ;//д1��0�������һֱ���ж� 
				/*�жϴ������......*/ 			
			}
			
		}
}

/*********************************************************************************** 
Function   : void EXT4_IRQHandler(void)
Description: ϵͳ�ж�4��ں���
Input      : No      
Output     : No	                  
Return     : No
************************************************************************************/
void EXT4_IRQHandler(void) interrupt 4 
{
	/*---�ⲿ�ж�4---*/
    if(0x01 == IRQ4SR_XINT4)
    {  
        IRQ4SR_XINT4 = 0;
			
    }

    if(0x02 == IRQ4SR_TCM2INT0)//T2�ж� 
		{	
			T2SR_INT0SR = 0 << 0;		//��T2�жϱ�־λ             
			//�жϴ������......
		}

    if(0x04 == IRQ4SR_ADCINT)//ADCת������жϱ�־
    {
        IRQ4SR_ADCINT = 0;
//        ADCSR_SAMPEND = 0 ;//��ת����ɱ�־
//        g_adcDat = ADCDRH;
//        g_adcDat <<= 8;
//        g_adcDat |= ADCDRL;
//        g_adcDatFlg = 1;
    }
	
		if(0x08 == IRQ4SR_UART2INT) //�ж��Ƿ���uart�ж� 
		{			
			if(0x08 == USR2_RXREADY) 
			{		
				USR2=0x08;
				/*�жϴ������......*/  
			}
			if(0x80 == USR2_RXTMOUT)
			{
				USR2 = 0x80 ;//д1��0�������һֱ���ж�
				/*�жϴ������......*/ 
			}			
		}
}

/*********************************************************************************** 
Function   : void EXT5_IRQHandler(void)
Description: ϵͳ�ж�5��ں���
Input      : No      
Output     : No	                  
Return     : No
************************************************************************************/
void EXT5_IRQHandler(void) interrupt 5 
{
	/*---�ⲿ�ж�5---*/
    if(0x01 == IRQ5SR_XINT5)
    {  
        IRQ5SR_XINT5 = 0;
				
    }

    if(0x02 == IRQ5SR_I2CSINT)//I2C�ӻ��ж�
		{
			if(I2CSSR_RXDATA == 0x02)//I2C���������ж�
			{
				I2CSSR_RXDATA = 0;
			}
		}
	
		if(0x04 == IRQ5SR_SPIINT)//SPI�ж�
		{
					
		}
		
		if(0x08 == IRQ5SR_I2CMINT)//I2C�����ж�
		{
					
		}
}