#ifndef  _ADC_H_
#define  _ADC_H_

void adcInit(uint8 div,uint8 ctrl) ;                           //��Ƶ
uint16 adcSampStart(uint8 flitnum_chlnum); 
float ADCSampValue(uint8 mode,uint8 flitnum_chlnum );
void ADCPortInit(void);                                           //ADC���ų�ʼ��     
//bit adcLdoTrimming(void);                                         //��ƯУ׼


#endif 