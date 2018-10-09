#ifndef _ETHERNET_H
#define _ETHERNET_H

#include "my_include.h"


#define g_ethernet_RXbuff_len 250
#define g_ethernet_TXbuff_len 250

extern char g_ethernet_RXbuff[g_ethernet_RXbuff_len];
extern char g_ethernet_TXbuff[g_ethernet_TXbuff_len];
extern u8 g_dma_RXData_number2;





void USART2_Configuration(u32 bound);			//�ر�232�ӿ�  -- ��������̫��ת���ڵĽӿ�

void DMA_Uart2_Init(void);
void Uart2_Start_DMA_Tx(u16 size);



void WIFI_Send(char *str,u16 len);
void WIFI_delay(void);
void WIFI_init(u8 ID);






#endif


