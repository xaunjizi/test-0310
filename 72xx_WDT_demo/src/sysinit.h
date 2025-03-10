#ifndef _SYSINIT_H_
#define _SYSINIT_H_

uint8 sysClkInit(uint8 IHpllclksel, uint8 TLclk_sysclksel, uint8 mclkDiv, uint8 sclk1Div);
void ioPortInit(void);

void User_IOInit(void);            //自定义IO功能


#endif