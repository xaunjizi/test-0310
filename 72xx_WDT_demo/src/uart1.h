#ifndef  _UART1_H_
#define  _UART1_H_


extern uint8 g_UTRBuffer[256];//串口数据buffer
extern uint8 g_URLength, g_UTLength ;//帧长度
extern bit g_URXFlg;//帧接收完成标志 




#define TXLengh  1       //发送缓冲区长度（大小）
#define RXLengh  1     //接收缓冲区长度

extern xdata uint8 *txBuffer ,*rxBuffer;//定义收发buffer指针
extern bit g_URXDoneFlg ;//帧接收完成标志
extern bit g_UTXDoneFlg ;//帧发送完成标志



void Uart1Init(uint8 format,uint16 bpr,uint16 timeoutcnt );
void UartSendByte(uint8 dat);             //发送出去为16进制数
void UartPrintf(uint8 *p);           

void uartSendAsc(uint8 dat);   //转化为ASCLL码0-9
void Uart1SendAscNum(uint16 dat);
void printDec2Hex(uint32 num);             //10进制转化为16进制

void Uart1DMAInit(uint8 format,uint16 bpr ,uint8 txLengh,uint8 rxLengh,uint16 tx_addr,uint16 rx_addr,uint8 timeoutcnt);    //串口DMA模式初始化
void Uart1DMATxEn(void);
void Uart1DMARxEn(void);



#endif