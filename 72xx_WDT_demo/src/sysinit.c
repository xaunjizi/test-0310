/************************************************************************************************ 
  Company: Shenzhen Chipsbank Technologies Co., Ltd
  FileName: sysinit.c  
  Author: joe.huang        
  Version : V1.0      
  Date: 20191022  
  Description: ϵͳ���ʱ�ӳ�ʼ����Io�ڳ�ʼ��

  Function List:
				uint8 sysClkInit(uint8 IHpllclksel, uint8 sysclksel, uint8 mclkDiv, uint8 sclk1Div)
				void ioPortInit(void);

  History: //��ʷ�޸ļ�¼   
	<author>		<time>			<Re_version >			<desc>  
	Joe.huang		20191022		V1.0					���� 
  	  
*************************************************************************************************/
#include "CBM7216.h"
#include "intrins.h"

/*********************************************************************************** 
Function   : uint8 sysClkInit(uint8 IHpllclksel, uint8 sysclk_TLclksel, uint8 mclkDiv, uint8 sclk1Div)
Description: ϵͳʱ�ӳ�ʼ��
Input      : 
             IHpllclksel: �ڲ�����PLLʱ��Դѡ�� 0-24M��1-16M
		
             TLclk_sysclksel: 
						bit7��TLclksel-timer����ʱ��ѡ�� 0-1Mhz; 1-100Khz
						bit0��sysclksel-ϵͳʱ��Դѡ�� 0-IH���ڲ�����ʱ�ӣ���1-IL���ڲ�����ʱ��1M��
				
             mclkDiv  	��ϵͳmainʱ�ӷ�Ƶ����0~31��  MCLK=SCLK/(mclkDiv+1)
			 
             sclk1Div  	��ϵͳ��ʱ��1��Ƶ����0-3�� sclk1=SCLK/(sclk1Div+1)
Output     : No	                  
Return     : retOSC: ϵͳ��ѡʱ��Դ1-1M; 16-16M��24-24M
************************************************************************************/
uint8 sysClkInit(uint8 IHpllclksel, uint8 TLclk_sysclksel, uint8 mclkDiv, uint8 sclk1Div)
{
	uint8 retOSCV = 0;
	uint8 sysclksel;
	uint8 TLclksel;
	
	IHpllclksel &= 0x01;//�ڲ�����PLLʱ��Դѡ�� 0-24M��1-16M
	TLclksel = (TLclk_sysclksel&0x80)>>7;//timer����ʱ��ѡ�� 0-1Mhz; 1-100Khz
	sysclksel = TLclk_sysclksel&0x01;//ϵͳʱ��Դѡ��0-IH���ڲ�����ʱ�ӣ���1-IL���ڲ�����ʱ��1M��
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
	MISCR2_IHCLKEN = 1<<0;//ʹ���ڲ�����ʱ��
	IHPLLCLKSELCR = IHpllclksel;//ѡ���ڲ�����ʱ�ӣ�0-24m(Ĭ��ֵ0) 1-16m
	MISCR1_SYSCLKSEL = sysclksel<<4;//ѡ��ϵͳʱ��Դ  0-IH���ڲ�����ʱ��-Ĭ��ֵ0����1-IL���ڲ�����ʱ��1M��
	_nop_();_nop_();_nop_();_nop_();_nop_();//�ȴ�OSC�ȶ�
	_nop_();_nop_();_nop_();_nop_();_nop_();//�ȴ�OSC�ȶ�
	_nop_();_nop_();_nop_();_nop_();_nop_();//�ȴ�OSC�ȶ�
	_nop_();_nop_();_nop_();_nop_();_nop_();//�ȴ�OSC�ȶ�
	_nop_();_nop_();_nop_();_nop_();_nop_();//�ȴ�OSC�ȶ�
	_nop_();_nop_();_nop_();_nop_();_nop_();//�ȴ�OSC�ȶ�
	_nop_();_nop_();_nop_();_nop_();_nop_();//�ȴ�OSC�ȶ�
	_nop_();_nop_();_nop_();_nop_();_nop_();//�ȴ�OSC�ȶ�	
	CKDIVCR_MCLKDIV = (mclkDiv&31)<<0;//MCLK
	MISCR2_SCLK1DIV = (sclk1Div&3)<<6; //SCLK1���������ʱ��
	CKDIVCR_ILCLKDIV = (0&7)<<6; //SCLK2��1M����ʱ��
								//0-1��Ƶ-1M��1-2��Ƶ-500K��2-4��Ƶ-250K��3-8��Ƶ-125K��
								//4-10��Ƶ-100K��5-16��Ƶ=62.5k��6-32��Ƶ=31.25k��7-64��Ƶ=15.625k��
	MDLCKCR_TLCKSEL = TLclksel<<7;//timer����ʱ��ѡ�� 0-1Mhz; 1-100Khz
	RTCCLKSELR = 1;//=0-RTCѡ��30Kʱ�ӣ�֧�ֵ͹�����RTC������������=1-RTCѡ��100Kʱ��
    
	//IHPLL��⹦��
	MISCR2_IHCLKCHKEN = 0<<1;//ʹ��PLL�����Զ�������Ĭ��ֵ0��
	MISCR2_SYSCLKSWITCHEN = 0<<3;//IHCLK����ʱ�Զ��л���1MHZ
	MISCR3_SYSCLKFINTEN = 1<<5;
	IRQ2ER_SYSCLKFINTEN = 1<<4;
	
	if(((ECCCR&0x0D)!=0x05) && ((ECCCR&0x0D)!=0x09))//ֻ��û��eccʱ���ſ��Դ�MISCR_FMFIFOEN��MISCR_FMULRDEN
	{
			MISCR1_FMFIFOEN = 0x01<<3 ; //flash�ض����Ʋ�����ˮȡָ����
			MISCR1_FMULRDEN = 0x01<<2 ; //��flash�ض�����
	}
	
	return retOSCV;
}
/*********************************************************************************** 
Function   : void ioPortInit(void)
Description: Io�˿����ã�������ӳ�䡢������С�����������С��������ʹ�ܡ���©ʹ�ܡ����ݡ�����ѡ��
Input      : No      
Output     : No	                  
Return     : No
************************************************************************************/
void ioPortInit(void)
{
  MDLCKCR_IOCEN = 0x01<<3 ;
    /*----------IoPort Remap Config----------*/
   //P00/P01 Por default debug_uart(0x01/0x30), others Por default IoPort(0x00)
  P00IOCFG=0X01 ;//���Դ������
	P01IOCFG=0X30 ;//���Դ�������
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
	//�������� Por default 00(00/11:6mA; 01:30mA; 10:60mA;)
	P0LDRVRL = 0x00 ; 	
	P0LDRVRH = 0x00 ;
	P1LDRVRL = 0x00 ; 	
	P1LDRVRH = 0x00 ;
	P2LDRVRL = 0x00 ;
	P2LDRVRH = 0x00 ;
	P3LDRVRL = 0x00 ; 	

    /*----------Io Up/Down Config----------*/
	//��������ѡ�� Por default 0(00:88K��01:10K; 10:4.5K; 11:2.2K)
	P0PURSELRL = 0x00 ;
	P0PURSELRH = 0x00 ;
	P1PURSELRL = 0x00 ;
	P1PURSELRH = 0x00 ;
	P2PURSELRL = 0x00 ;
	P2PURSELRH = 0x00 ;
	P3PURSELRL = 0x00 ;

    /*----------Io OpenDrain Config----------*/
	//��© Por default 0(��ֹ��©)
	P0OD = 0x00 ;
	P1OD = 0x00 ;
	P2OD = 0x00 ;
	P3OD = 0x00 ;
    
    /*----------Io PortData----------*/
    //���ݼĴ��� Por default 1
	P0 = 0xFF ;
	P1 = 0xFF ;
	P2 = 0xFF ;
	P3 = 0xFF ;
	
    /*----------Io PortDirection Config----------*/    
	//���� Por default 1(����)
	P0OE = 0xFF ;
	P1OE = 0xFF ;
	P2OE = 0xFF ;
	P3OE = 0xFF ;
	
	/*----------Io PULLUP Config----------*/
	//���� Por default 0(��ֹ����)
	P0PU = 0xff ;
	P1PU = 0xff ;
	P2PU = 0xff ;
	P3PU = 0xff ;

	/*----------Io smith Config----------*/    
	//IO������ΪLCD����ʱ��������Ϊ0xff�������������Ϊ0x00�� Por default 0x00(�ر�)
	P0SMEN = 0x00 ;
	P1SMEN = 0x00 ;
	P2SMEN = 0x00 ;
	P3SMEN = 0x00 ;
}



/*********************************************************************************** 
Function   : void User_IOInit(void)
Description: �Զ���IO��������ӳ�䡢������С�����������С��������ʹ�ܡ���©ʹ�ܡ����ݡ�����ѡ��
Input      : No      
Output     : No	                  
Return     : No
************************************************************************************/
void User_IOInit(void)
{
//		P21IOCFG = 0x00;                    //IO����
//		P20IOCFG = 0x00;
//		P02IOCFG = 0x00;
//		P17IOCFG = 0x00;
//		
//		
//		P2LDRVRL_1 = 0x04;                 //����60ma
//		P2LDRVRL_0 = 0x01;
//		P0LDRVRL_2 = 0x10;
//		P1LDRVRH_7 = 0x40;
//		
//		P2OE_1 = 0x00;                    //�������
//		P2OE_0 = 0x00;
//		P0OE_2 = 0x00;
//		P1OE_7 = 0x00;
//		
//		P2_1 = 1;                         //������
	
//		P2_0 = 0;                         //LED�͵�ƽ��
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
//  P20IOCFG = 0x00;                    //IO����
//	P07IOCFG = 0x00;
//	P21IOCFG = 0x00;
//	P02IOCFG = 0x00;
//	P17IOCFG = 0x00;
//	
//	
//	P2LDRVRL_0 = 0x01;                 //����60ma
//	P0LDRVRH_7 = 0x40;
//	P2LDRVRL_1 = 0x04;
//	P0LDRVRL_2 = 0x10;
//	P1LDRVRH_7 = 0x40;
//	
//	P2OE_0 = 0x00;                 //�������
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

