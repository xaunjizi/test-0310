#ifndef _PWM_H_
#define _PWM_H_



void PWM11Init(uint8 clkdiv,uint16 idle0,uint16 idle1);




//pwm1
extern void pwm1Init(uint8 div,uint16 pwml,uint16 pwmh);
extern void pwm1Set(uint16 pwml,uint16 pwmh);
extern void pwm1En(void);
extern void pwm1Dis(void);
extern void pwm1DTSet(uint8 pwm1DTen,uint8 pwm1invDTen,uint8 DTdiv,uint8 pwm1DTcnt,uint16 pwm1invDTcnt);
//pwm2
extern void pwm2Init(uint8 div,uint8 pwml,uint8 pwmh);
extern void pwm2Set(uint8 pwml,uint8 pwmh);
extern void pwm2En(void);
extern void pwm2Dis(void);
//pwm3
extern void pwm3Init(uint8 div,uint16 pwml,uint16 pwmh);
extern void pwm3Set(uint16 pwml,uint16 pwmh);
extern void pwm3En(void);
extern void pwm3Dis(void);
extern void pwm3DTSet(uint8 pwm3DTen,uint8 pwm3invDTen,uint8 DTdiv,uint8 pwm3DTcnt,uint16 pwm3invDTcnt);
//pwm4
extern void pwm4Init(uint8 div,uint8 pwml,uint8 pwmh);
extern void pwm4Set(uint8 pwml,uint8 pwmh);
extern void pwm4En(void);
extern void pwm4Dis(void);
//pwm5
extern void pwm5Init(uint8 div,uint16 pwml,uint16 pwmh);
extern void pwm5Set(uint16 pwml,uint16 pwmh);
extern void pwm5En(void);
extern void pwm5Dis(void);
extern void pwm5DTSet(uint8 pwm5DTen,uint8 pwm5invDTen,uint8 DTdiv,uint8 pwm5DTcnt,uint16 pwm5invDTcnt);


#endif  
