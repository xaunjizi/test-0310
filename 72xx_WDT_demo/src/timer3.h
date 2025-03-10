#ifndef  _TIMER3_H_
#define  _TIMER3_H_

//void timer3TcmInit(uint8 clksel,uint8 inten,uint16 cmp0);
void Timer3Init(uint16 cmp0,uint8 clksel, uint8 clkdiv);   //定时器3定时器模式初始化
void Timer3Set(uint16 cmp0);                   //设置定时器模式周期


void Timer3PWMInit(uint16 cmp0,uint16 cmp1,uint8 clksel, uint8 clkdiv);      //定时器3PWM模式初始化
void Timer3PWMSet(uint16 cmp0,uint16 cmp1);    //设置PWM模式周期

void Timer3CountInit(uint16 cmp0,uint8 clksel);    //定时器3外部计数模式初始化
void Timer3CountSet(uint16 cmp0,uint16 cmp1);  
uint8 Timer3CountRead(void);
#endif