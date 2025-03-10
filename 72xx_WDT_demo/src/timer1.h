#ifndef  _TIMER1_H_
#define  _TIMER1_H_


void Timer1Init(uint8 cmp,uint8 clksel, uint8 clkdiv);    //定时器1初始化
void Timer1Set(uint8 cmp0);                              //周期设置

void Timer1PWMInit(uint8 cmp,uint8 clksel, uint8 clkdiv);     //定时器1PWM初始化
void Timer1PWMSet(uint8 cmp);            //PWM占空比设置

void Timer1CountInit(uint8 cmp,uint8 clksel, uint8 clkdiv);   //外部事件计数初始化
void Timer1CountSet(uint8 cmp);                            //计数最大值设置
uint8 readTimer1Counter(void) ;              //读取计数值

#endif  