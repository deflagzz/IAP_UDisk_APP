#ifndef __CAN_H
#define __CAN_H	 
#include "my_include.h"	    

	


	
	
	
	
	
	
//CAN1����RX0�ж�ʹ��
#define CAN1_RX0_INT_ENABLE	1		//0,��ʹ��;1,ʹ��.		
//CAN2����RX0�ж�ʹ��
#define CAN2_RX0_INT_ENABLE	1		//0,��ʹ��;1,ʹ��.	


extern u8 g_Get_RFID_buff[16];
extern u8 g_cinavi5_RXbuff[16];  //ǰ�ŵ���
extern u8 g_cinavi6_RXbuff[16];	//��ŵ���




extern u16 g_AGV_RFID_ID;//�ر�


extern u8  g_flag_RFID_beep;
extern u8 g_flag_Motec_init;

extern u8 g_cinavi1_RXbuff[16];  //ǰ�ŵ���
extern u8 g_cinavi2_RXbuff[16];	
extern u8 g_cinavi3_RXbuff[16];  
extern u8 g_cinavi4_RXbuff[16];	//��ŵ���



extern int g_Ct_chugui[5];
extern u16 g_CT_bit[5];

extern u16 g_u16_val[5];





										 							 				    
u8 CAN1_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode);//CAN��ʼ��
u8 CAN2_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode);//CAN��ʼ��
 
u8 CAN1_Send_Msg(u16 ID,char* msg,u8 len);						//��������

u8 CAN1_Receive_Msg(void);							//��������

u8 CAN2_Receive_Msg(u8 *buf);
u8 CAN2_Send_Msg(u16 ID,char* msg,u8 len);

u16 bit16_huan(u16 temp_bit);







#endif

















