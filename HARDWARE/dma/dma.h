#ifndef __DMA_H
#define	__DMA_H	   
#include "my_include.h"
#define UART_RX_LEN     250
#define UART_TX_LEN     250
#define UART6_RX_LEN    250




extern u8 rece_index,rece2_index,rece6_index,rece3_index;
extern u8 sendBuf[UART_RX_LEN],receBuf[UART_RX_LEN],*ps,*pr;


void DMA_adc1_Init(void);
void DMA_Uart2_Init(void);
void DMA_Uart3_Init(void);
void DMA_Uart4_Init(void);
void DMA_Uart6_Init(void);
void Uart3_Start_DMA_Tx(u16 size);
void Uart4_Start_DMA_Tx(u16 size);
void Uart6_Start_DMA_Tx(u16 size);

#endif






























