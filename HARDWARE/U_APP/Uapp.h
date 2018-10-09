#ifndef _UAPP_H_
#define _UAPP_H_
#include "my_include.h"  
 


#define IAP_Bootloat_SIZE 		0x8000	//32K
#define FLASH_APP1_ADDR			(0x08000000+IAP_Bootloat_SIZE) 	//+32*1024	//第一个应用程序起始地址(存放在FLASH)   
#define CAN_RX_BUFF_LEN			2048			//1K或者2KSRAM缓存CAN中断的数据,根据MCU的FLASH大小决定	


typedef struct
{
	
	u8  RX_BUFF[CAN_RX_BUFF_LEN];
	u16 APP_RX_len;
	u8  key_start_IAP;			//1:更新

}stm32_iap;

extern stm32_iap 	g_iap;
extern USBH_HOST  	USB_Host;
extern USB_OTG_CORE_HANDLE  USB_OTG_Core;




#endif







