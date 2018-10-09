#include "battery.h"

//
//��--��--GND
//��--��--R
//��--��--T
//

u8 g_battery_RXbuff[g_battery_RXbuff_len];
u8 g_battery_TXbuff[g_battery_TXbuff_len] = {0xDD, 0xA5, 0x03, 0x00, 0xFF, 0xFD, 0x77};

warning Battery_Warining;

char g_warning[256];


void USART3_Configuration(u32 bound)
{
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); //ʹ��GPIODʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);//ʹ��USART3ʱ��

	//����3��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_USART1); //GPIOD8����ΪUSART3
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_USART1); //GPIOD9����ΪUSART3

	//USART3�˿�����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9; //GPIOD8��GPIOD9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        //�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOD,&GPIO_InitStructure); //��ʼ��PD8��PD9

	//USART3 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;        //�շ�ģʽ
	USART_Init(USART3, &USART_InitStructure); //��ʼ������3
	
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);
	USART_Cmd(USART3, ENABLE);  //ʹ�ܴ���1 
	USART_ClearFlag(USART3, USART_FLAG_TC);
	USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE);
//	USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE);
	
   
}

battery g_battery;

void USART3_IRQHandler(void)             
{
	u16 temp_b=0;
	u8  temp_V=0;
	u8 temp_data3=0;
	
#if SYSTEM_SUPPORT_OS 	
	OSIntEnter();    
#endif
	
	if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET) 
	{
		DMA_Cmd(DMA1_Stream1,DISABLE);
		temp_data3 = USART3->SR;
		temp_data3 = USART3->DR; //���IDLE��־
		temp_data3 = g_battery_RXbuff_len - DMA_GetCurrDataCounter(DMA1_Stream1); 
		DMA1_Stream1->NDTR = g_battery_RXbuff_len;
		
		if((g_battery_RXbuff[0] == 0xDD)&&(g_battery_RXbuff[1] == 0xA5)&&(g_battery_RXbuff[2] == 0x00)) 
		{
			g_battery.dianya 		= 	g_battery_RXbuff[4]<<8  | g_battery_RXbuff[7];
			temp_b					= 	g_battery_RXbuff[8]<<8  | g_battery_RXbuff[9];		
			g_battery.Std_mah		= 	g_battery_RXbuff[10]<<8 | g_battery_RXbuff[11];
			g_battery.XunHuan_time 	= 	g_battery_RXbuff[12]<<8 | g_battery_RXbuff[13];

			if(temp_b < 3500)
			{
				g_battery.Realy_mah = temp_b + 1;
			}	
			else
			{
				g_battery.Realy_mah = 3500;
			}
			temp_V = g_battery.Realy_mah / (g_battery.Std_mah/100);			//20 00 0	3500
			if(temp_V < 100)
			{
				if(temp_V == 0)
				{	
					Sys_battery = temp_V;
				}
				else
				{
					Sys_battery  = temp_V + 1;				
				}

			}
			else
			{
				Sys_battery  = 100;
			}
			
			
		}			
		memset(g_battery_RXbuff,0,sizeof(g_battery_RXbuff));	//��������		
		DMA_Cmd(DMA1_Stream1, ENABLE);
	}
	
	temp_data3 = temp_data3;
#if SYSTEM_SUPPORT_OS 	
	OSIntExit();  											 
#endif
}




void DMA_Uart3_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;	
    DMA_InitTypeDef DMA_InitStructure;  
    /* DMA clock enable */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

	

	/*--- LUMMOD_UART_Tx_DMA_Channel DMA Config ---*/
 
//    DMA_Cmd(DMA1_Stream3, DISABLE);
//    DMA_DeInit(DMA1_Stream3);
//	DMA_InitStructure.DMA_Channel = DMA_Channel_4;
//    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART3->DR);
//    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)g_battery_TXbuff;         //����buff
//    DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
//    DMA_InitStructure.DMA_BufferSize = g_battery_TXbuff_len;					 //����buff����
//    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
//    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
//    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
//    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	
//	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable; 
//    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;	
//    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
//	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//�洢��ͻ�����δ���
//	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//����ͻ�����δ���
//    DMA_Init(DMA1_Stream3, &DMA_InitStructure);
//	DMA_Cmd(DMA1_Stream3, DISABLE);
//    DMA_ITConfig(DMA1_Stream3, DMA_IT_TC, ENABLE);
	
/*--- LUMMOD_UART_Rx_DMA_Channel DMA Config ---*/
 
 
 
 
    DMA_Cmd(DMA1_Stream1, DISABLE);
    DMA_DeInit(DMA1_Stream1);
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART3->DR);
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)g_battery_RXbuff;			//����buff
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory ;
    DMA_InitStructure.DMA_BufferSize = g_battery_RXbuff_len;					//����buff����
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable; 
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;	
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//�洢��ͻ�����δ���
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//����ͻ�����δ���
    DMA_Init(DMA1_Stream1, &DMA_InitStructure);
    DMA_Cmd(DMA1_Stream1, ENABLE); 




	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream1_IRQn;  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
	
	
	
	
}
//void Uart3_Start_DMA_Tx(u16 size)
//{
//	DMA_Cmd(DMA1_Stream3, DISABLE);
//    DMA_SetCurrDataCounter(DMA1_Stream3,size);
//    DMA_Cmd(DMA1_Stream3, ENABLE);
//}

void GET_Battery(void)
{
	USART_OUT(USART3,(char *)g_battery_TXbuff,7);
	delay_rtos(0,0,0,100);
	USART_OUT(USART3,(char *)g_battery_TXbuff,7);
}

void GET_Battery_once(void)
{
	USART_OUT(USART3,(char *)g_battery_TXbuff,7);
	//delay_rtos(0,0,0,10);
}



