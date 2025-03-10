#ifndef  _TIMER0_H_
#define  _TIMER0_H_

void Timer0Init(uint8 cmp0,uint8 clksel, uint8 clkdiv);   //定时器0定时器模式初始化
void Timer0SetCmp0(uint8 cmp0);

void Timer0PWMInit(uint8 cmp0,uint8 cmp1,uint8 clksel, uint8 clkdiv);   //定时器0PWM初始化
void Timer0PWMSetCmp0(uint8 cmp0,uint8 cmp1);

#endif