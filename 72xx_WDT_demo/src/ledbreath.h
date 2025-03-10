#ifndef _LEDBREATH_H_
#define _LEDBREATH_H_

/*-----------------------用户仅需要通过更改以下宏定义就可实现想要的呼吸效果-------------------------*/
#define BREATH_DUTY			250L//BREATH_DUTY越小越好，决定了LED_PWM的驱动频率f = 1/(BREATH_DUTY*0.125us)，建议f>5khz
#define BREATH_STEPLEVEL	250L//把BREATH_DUTY占空比周期分成BREATH_STEPLEVEL级可调
#define BREATH_REFRESH 		20//刷新间隔; 一个完整的呼吸周期 = BREATH_STEPLEVEL * BREATH_REFRESH（ms）

extern void breath1(void) ;
extern void breath2(void) ;
extern void breath3(void) ;
extern void breath4(void) ;
extern void breath5(void) ;

#endif