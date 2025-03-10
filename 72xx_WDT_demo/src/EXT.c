#include "CBM7216.h"

/* 
���� ���ⲿ�жϳ�ʼ��
������
	sel��������ʽ
			000-�ߵ�ƽ��001-�͵�ƽ��101-�����ء�110-�½��ء�111-˫���ء�����-������
			�ⲿ�ж�5���⣬000��001��Ч
	  n��ѡ���ⲿ�жϣ�0-5
*/
void EXTInit(uint8 sel ,uint8 n)
{
		IFLTCNTR =   0x0f;   //�����˲�ʱ��
//	uint8  Trg = 0x03,EXTn = 0;
	switch(n)	
	{
     case 0:
		 {
				XINT01TRGR =  sel << 0 ;   //������ʽ
				IRQ0ER_XINT0 = 1 << 0;        //ʹ���ⲿ�ж�0
			  EX0 = 1;               //ʹ���ں��ж�0
			}  break ;
		 case 1:
		 {
				XINT01TRGR = sel << 4 ;   //������ʽΪ
				IRQ1ER_XINT1 = 1 << 0;        //ʹ���ⲿ�ж�1
			  EX1 = 1;               //ʹ���ں��ж�0
			}      break ;
		case 2:
		 {
				XINT23TRGR = sel<< 0 ;   //������ʽ
				IRQ2ER_XINT2 = 1 << 0;        //ʹ���ⲿ�ж�2
			  EX2 = 1;               //ʹ���ں��ж�0
			}          break ;
		case 3:
		 {
				XINT23TRGR = sel << 4 ;   //������ʽ
				IRQ3ER_XINT3 = 1 << 0;        //ʹ���ⲿ�ж�3
			  EX3 = 1;               //ʹ���ں��ж�0
			}            break ;
		case 4:
		 {
				XINT45TRGR = sel << 0 ;   //������ʽ
				IRQ4ER_XINT4 = 1 << 0;        //ʹ���ⲿ�ж�4
			  EX4 = 1;               //ʹ���ں��ж�0
			}             break ;
		case 5:
		 {
				XINT45TRGR = sel << 4 ;   //������ʽ
				IRQ5ER_XINT5 = 1 << 0;        //ʹ���ⲿ�ж�5
			  EX5 = 1;               //ʹ���ں��ж�0
			}      break ;
			default :break;
	}
	  EA = 1;           //���ں����жϣ����Ƶ�����ôκ��������жϿ��ؿ��Ա��ֿ������Ƴ��������⣩
}



