#ifndef  _TIMER0_H_
#define  _TIMER0_H_

void Timer0Init(uint8 cmp0,uint8 clksel, uint8 clkdiv);   //��ʱ��0��ʱ��ģʽ��ʼ��
void Timer0SetCmp0(uint8 cmp0);

void Timer0PWMInit(uint8 cmp0,uint8 cmp1,uint8 clksel, uint8 clkdiv);   //��ʱ��0PWM��ʼ��
void Timer0PWMSetCmp0(uint8 cmp0,uint8 cmp1);

#endif