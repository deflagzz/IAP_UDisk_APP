#include "Uapp.h"


stm32_iap 	g_iap;

USBH_HOST  	USB_Host;
USB_OTG_CORE_HANDLE  USB_OTG_Core;


void delay_iap(u32 h,u32 m,u32 s,u32 ms)
{
	OS_ERR err;
	//OS_OPT_TIME_HMSM_NON_STRICT:延时不限大小
	OSTimeDlyHMSM(h,m,s,ms,OS_OPT_TIME_HMSM_NON_STRICT,&err);	
}

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
void IAP_IRQ_Remap_Init(u32 sizi)
{
	SCB->VTOR = FLASH_BASE | sizi;//设置偏移量 32K=0x8000
}
void IAP_U_Disk_Init(void)
{
/*************************************U盘IAP*******************************************///	
	my_mem_init(SRAMIN);	//初始化内部内存池											//
 	exfuns_init();			//为fatfs相关变量申请内存 									//																					//
	#if USB_DISK_allow                                                                  //
	f_mount(fs[0],"0:",1); 	//挂载U盘                                                   //
	#endif                                                                              //
	#if EX_FLASH_allow                                                                  //
	f_mount(fs[1],"1:",1); 	//挂载SPI Flash												//
	#endif																				//
	#if SD_CARD_allow																	//
	f_mount(fs[2],"2:",1); 	//挂载SD卡  												//
	#endif																				//																				//
	printf("设备连接中...\r\n");														//
	//初始化USB主机																		//
  	USBH_Init(&USB_OTG_Core,USB_OTG_FS_CORE_ID,&USB_Host,&USBH_MSC_cb,&USR_Callbacks);  // 
/*************************************U盘IAP*******************************************///	
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
			delay_iap(0,0,0,100);
			systeam_ReStart();
		}
		if(temp == 100)
		{
			BEEP = 1;
			delay_iap(0,0,0,30);
			BEEP = 0;
			delay_iap(0,0,0,70);
			BEEP = 1;
			delay_iap(0,0,0,30);
			BEEP = 0;
			delay_iap(0,0,0,70);			
			
			temp = 0;
		}
		temp++;		
		delay_iap(0,0,0,10);
	}
	
	
	return res;										
}

void IAP_U_Disk_UpData(void)
{
	u8 temp=0;
	
	while(1)
	{	
		USBH_Process(&USB_OTG_Core, &USB_Host);
		if(temp == 200)
		{
			BEEP = 1;
			delay_iap(0,0,0,30);
			BEEP = 0;
			
			temp = 0;
		}
		temp++;
			
		delay_iap(0,0,0,10);
	}
}












