#include "include.h"




void main()
{
	uint8 i;
	sysClkInit(0x01,0x00,0x00,0x00);//IHpllclksel-16m��sysclksel-IH��mclkDiv-1��Ƶ��sclk1Div-1��Ƶ��
  ioPortInit();
	User_IOInit();
	Timer1Init(125,0,0x06);                        //1ms
	
	Uart1Init(0x08,0x8A,200);             //ʹ��uart�жϣ�115200bps 8bit����λ 1bitֹͣλ ����żУ��λ  
	P00IOCFG = 0x27; //����P00ͨ�ô���1���
  P01IOCFG = 0x33; //����P01ͨ�ô���1���� 
	
	wdtInit(0x0c,0x02); //(2^12)*��2+1��*160us
	
	

	while(1)
	{
		
		wdtClear();


	}
}