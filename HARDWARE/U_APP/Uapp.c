#include "Uapp.h"


stm32_iap 	g_iap;

USBH_HOST  	USB_Host;
USB_OTG_CORE_HANDLE  USB_OTG_Core;


void delay_iap(u32 h,u32 m,u32 s,u32 ms)
{
	OS_ERR err;
	//OS_OPT_TIME_HMSM_NON_STRICT:��ʱ���޴�С
	OSTimeDlyHMSM(h,m,s,ms,OS_OPT_TIME_HMSM_NON_STRICT,&err);	
}

void systeam_ReStart(void)
{
	u32 time = 65535;
	while(time--)
	{
		__NOP();
	}
	//__set_FAULTMASK(1);	//M4�ں�ò���ò����������
	INTX_DISABLE();
	NVIC_SystemReset();
}
void IAP_IRQ_Remap_Init(u32 sizi)
{
	SCB->VTOR = FLASH_BASE | sizi;//����ƫ���� 32K=0x8000
}
void IAP_U_Disk_Init(void)
{
/*************************************U��IAP*******************************************///	
	my_mem_init(SRAMIN);	//��ʼ���ڲ��ڴ��											//
 	exfuns_init();			//Ϊfatfs��ر��������ڴ� 									//																					//
	#if USB_DISK_allow                                                                  //
	f_mount(fs[0],"0:",1); 	//����U��                                                   //
	#endif                                                                              //
	#if EX_FLASH_allow                                                                  //
	f_mount(fs[1],"1:",1); 	//����SPI Flash												//
	#endif																				//
	#if SD_CARD_allow																	//
	f_mount(fs[2],"2:",1); 	//����SD��  												//
	#endif																				//																				//
	printf("�豸������...\r\n");														//
	//��ʼ��USB����																		//
  	USBH_Init(&USB_OTG_Core,USB_OTG_FS_CORE_ID,&USB_Host,&USBH_MSC_cb,&USR_Callbacks);  // 
/*************************************U��IAP*******************************************///	
}

//�û�����������
//����ֵ:0,����
//       1,������
u8 USH_User_App(void)
{ 
	u8 res=0;
	u8 temp=0;
	while(HCD_IsDeviceConnected(&USB_OTG_Core))//�豸���ӳɹ�
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












