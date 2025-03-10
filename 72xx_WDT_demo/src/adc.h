#ifndef  _ADC_H_
#define  _ADC_H_

void adcInit(uint8 div,uint8 ctrl) ;                           //分频
uint16 adcSampStart(uint8 flitnum_chlnum); 
float ADCSampValue(uint8 mode,uint8 flitnum_chlnum );
void ADCPortInit(void);                                           //ADC引脚初始化     
//bit adcLdoTrimming(void);                                         //温漂校准


#endif 