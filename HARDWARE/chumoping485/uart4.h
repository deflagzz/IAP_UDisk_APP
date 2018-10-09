#ifndef __UART4_H
#define __UART4_H
#include "my_include.h"	


#define My_DMA_RX_U4	1



extern u16 g_modbus_RX_num;
extern u8 g_modbus_RX_OK;




void uart4_init(u32 bound);
void modbus_work(void);

#endif


