#ifndef  _RTC_H_
#define  _RTC_H_

void RtcInit(void);                                               //RTC��ʼ��
void RtcSetTime(uint8 hour,uint8 mimute,uint8 second);           //ʱ������
void RtcReadTime(uint8 *timer);                                 //��ʱ��
void RtcSetClockTime(uint8 hour,uint8 mimute,uint8 second);    //��������
void RtcReadClockTime(uint8 *timer);                          //������
void RtcOpen(void);                   //����rtc
void RtcClose(void);                 //�ر�rtc
#endif 