#ifndef  _RTC_H_
#define  _RTC_H_

void RtcInit(void);                                               //RTC初始化
void RtcSetTime(uint8 hour,uint8 mimute,uint8 second);           //时钟设置
void RtcReadTime(uint8 *timer);                                 //读时钟
void RtcSetClockTime(uint8 hour,uint8 mimute,uint8 second);    //设置闹钟
void RtcReadClockTime(uint8 *timer);                          //读闹钟
void RtcOpen(void);                   //开启rtc
void RtcClose(void);                 //关闭rtc
#endif 