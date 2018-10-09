#include "Uapp.h"


stm32_iap 	g_iap;

USBH_HOST  	USB_Host;
USB_OTG_CORE_HANDLE  USB_OTG_Core;

void systeam_ReStart(void)
{
	u32 time = 65535;
	while(time--)
	{
		__NOP();
	}
	//__set_FAULTMASK(1);	//M4内核貌似用不了这个函数
	INTX_DISABLE();
	NVIC_SystemReset();
}


//用户测试主程序
//返回值:0,正常
//       1,有问题
u8 USH_User_App(void)
{ 
	u8 res=0;
	u8 temp=0;
	while(HCD_IsDeviceConnected(&USB_OTG_Core))//设备连接成功
	{
		if(g_iap.key_start_IAP)
		{
			systeam_ReStart();
		}
		if(temp == 250)
		{
			BEEP = 1;
			delay_rtos(0,0,0,50);
			BEEP = 0;
			
			temp = 0;
		}
		temp++;		
		delay_ms(10);
	}
	
	
	return res;										
}