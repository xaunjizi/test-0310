#include "CBM7216.h"

/*           
���ܣ�WDT��ʼ��
������
	div����Ƶϵ��[7:4]    0000��0001��1100 = 1��2��4096��Ƶ��1101~1111 = 8192��Ƶ
	length:���ڳ���[3��0]  0-15
	
	1��WDT ������� = 2^CNTDIV* (CNTLEN + 1) * 16 * 10us(T100K)����160us~21s��
  2��WDT ��λ���� = 2 * ������� = 2 * 2CNTDIV* (CNTLEN + 1) * 16 * 10us(T100K)����320us~42s��
*/
void wdtInit(uint8 div, uint8 length)
{
		MDLCKCR_WDTEN = 1 << 0;  //ʹ��WDT
		WDTCR = 0x5A;     //��WDT
	  WDTCR = 0xA5;
	  WDTSETR_CNTDIV = (div & 0x0f) << 4;       //��Ƶ
	  WDTSETR_CNTLEN = (length & 0x0f ) << 0;    //����
		IRQ0ER_WDTINT = 0x04;    //ʹ��WDTģ��
	  EX0 = 1;               //ʹ���ں��ж�
		EA = 1;            //ʹ�����ж�
		WDTENR_CNTEN = 1 << 0;  //��ʼ����
}


/*           
���ܣ���WDT
*/
void wdtClear(void)
{
		WDTCR = 0x5A;     //��WDT
	  WDTCR = 0xA5;
}


