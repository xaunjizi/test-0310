#ifndef _LEDBREATH_H_
#define _LEDBREATH_H_

/*-----------------------�û�����Ҫͨ���������º궨��Ϳ�ʵ����Ҫ�ĺ���Ч��-------------------------*/
#define BREATH_DUTY			250L//BREATH_DUTYԽСԽ�ã�������LED_PWM������Ƶ��f = 1/(BREATH_DUTY*0.125us)������f>5khz
#define BREATH_STEPLEVEL	250L//��BREATH_DUTYռ�ձ����ڷֳ�BREATH_STEPLEVEL���ɵ�
#define BREATH_REFRESH 		20//ˢ�¼��; һ�������ĺ������� = BREATH_STEPLEVEL * BREATH_REFRESH��ms��

extern void breath1(void) ;
extern void breath2(void) ;
extern void breath3(void) ;
extern void breath4(void) ;
extern void breath5(void) ;

#endif