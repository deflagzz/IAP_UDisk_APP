#ifndef __Modbus_slave_H
#define	__Modbus_slave_H	 
#include "stm32f4xx.h"

#define InPut_Length 256
#define OutPut_Length 256
#define Data_Length 256

extern u8 PLC_InPut[InPut_Length];//PLC����״̬�Ĵ���
extern u8 PLC_OutPut[OutPut_Length];//PLC���״̬�Ĵ���
extern u16 PLC_Data[Data_Length];//PLC���ݼĴ���

void AnalyzeRecieve(u8 *RX_buff,u16 buff_len);                              
void send_comm(void);
void Recirve_01(void);
void Recirve_02(void);
void Recirve_03(void);
void Recirve_04(void);
void Recirve_05(void);
void Recirve_06(void);
void Recirve_10(void);
void errorsend(u8 func,u8 type);
u16 CalcCrc(unsigned char *chData,unsigned short uNo);


#endif
