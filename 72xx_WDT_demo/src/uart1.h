#ifndef  _UART1_H_
#define  _UART1_H_


extern uint8 g_UTRBuffer[256];//��������buffer
extern uint8 g_URLength, g_UTLength ;//֡����
extern bit g_URXFlg;//֡������ɱ�־ 




#define TXLengh  1       //���ͻ��������ȣ���С��
#define RXLengh  1     //���ջ���������

extern xdata uint8 *txBuffer ,*rxBuffer;//�����շ�bufferָ��
extern bit g_URXDoneFlg ;//֡������ɱ�־
extern bit g_UTXDoneFlg ;//֡������ɱ�־



void Uart1Init(uint8 format,uint16 bpr,uint16 timeoutcnt );
void UartSendByte(uint8 dat);             //���ͳ�ȥΪ16������
void UartPrintf(uint8 *p);           

void uartSendAsc(uint8 dat);   //ת��ΪASCLL��0-9
void Uart1SendAscNum(uint16 dat);
void printDec2Hex(uint32 num);             //10����ת��Ϊ16����

void Uart1DMAInit(uint8 format,uint16 bpr ,uint8 txLengh,uint8 rxLengh,uint16 tx_addr,uint16 rx_addr,uint8 timeoutcnt);    //����DMAģʽ��ʼ��
void Uart1DMATxEn(void);
void Uart1DMARxEn(void);



#endif