#ifndef  _TIMER1_H_
#define  _TIMER1_H_


void Timer1Init(uint8 cmp,uint8 clksel, uint8 clkdiv);    //��ʱ��1��ʼ��
void Timer1Set(uint8 cmp0);                              //��������

void Timer1PWMInit(uint8 cmp,uint8 clksel, uint8 clkdiv);     //��ʱ��1PWM��ʼ��
void Timer1PWMSet(uint8 cmp);            //PWMռ�ձ�����

void Timer1CountInit(uint8 cmp,uint8 clksel, uint8 clkdiv);   //�ⲿ�¼�������ʼ��
void Timer1CountSet(uint8 cmp);                            //�������ֵ����
uint8 readTimer1Counter(void) ;              //��ȡ����ֵ

#endif  