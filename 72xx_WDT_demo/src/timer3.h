#ifndef  _TIMER3_H_
#define  _TIMER3_H_

//void timer3TcmInit(uint8 clksel,uint8 inten,uint16 cmp0);
void Timer3Init(uint16 cmp0,uint8 clksel, uint8 clkdiv);   //��ʱ��3��ʱ��ģʽ��ʼ��
void Timer3Set(uint16 cmp0);                   //���ö�ʱ��ģʽ����


void Timer3PWMInit(uint16 cmp0,uint16 cmp1,uint8 clksel, uint8 clkdiv);      //��ʱ��3PWMģʽ��ʼ��
void Timer3PWMSet(uint16 cmp0,uint16 cmp1);    //����PWMģʽ����

void Timer3CountInit(uint16 cmp0,uint8 clksel);    //��ʱ��3�ⲿ����ģʽ��ʼ��
void Timer3CountSet(uint16 cmp0,uint16 cmp1);  
uint8 Timer3CountRead(void);
#endif