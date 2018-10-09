#ifndef _UAPP_H_
#define _UAPP_H_
#include "my_include.h"  
 


#define IAP_Bootloat_SIZE 		0x8000	//32K
#define FLASH_APP1_ADDR			(0x08000000+IAP_Bootloat_SIZE) 	//+32*1024	//��һ��Ӧ�ó�����ʼ��ַ(�����FLASH)   
#define CAN_RX_BUFF_LEN			2048			//1K����2KSRAM����CAN�жϵ�����,����MCU��FLASH��С����	


typedef struct
{
	
	u8  RX_BUFF[CAN_RX_BUFF_LEN];
	u16 APP_RX_len;
	u8  key_start_IAP;			//1:����

}stm32_iap;

extern stm32_iap 	g_iap;
extern USBH_HOST  	USB_Host;
extern USB_OTG_CORE_HANDLE  USB_OTG_Core;




#endif







