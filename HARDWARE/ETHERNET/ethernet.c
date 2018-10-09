#include "ethernet.h"


char g_ethernet_RXbuff[g_ethernet_RXbuff_len];
char g_ethernet_TXbuff[g_ethernet_TXbuff_len];


//�ر�232�ӿ�  -- ��������̫��ת���ڵĽӿ�	
void USART2_Configuration(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate            = bound  ;
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;
	USART_InitStructure.USART_Parity              = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure);	
	
	
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	
	USART_Cmd(USART2, ENABLE);  
	USART_ClearFlag(USART2, USART_FLAG_TC);

}

u8 g_dma_RXData_number2;
void USART2_IRQHandler(void)      	 	//��̫��ת232       
{

#if SYSTEM_SUPPORT_OS 	
	OSIntEnter();    
#endif
	

	  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)                   //�����Ϊ�˱���STM32 USART ��һ���ֽڷ�����ȥ��BUG 
	  {  
		char c=USART_ReceiveData(USART2);
		Dbus.InPut(c);
		USART_ClearFlag(USART2, USART_IT_RXNE);
	  }	

#if SYSTEM_SUPPORT_OS 	
	OSIntExit();  											 
#endif
	
}









//void DMA_Uart2_Init(void)
//{
//    DMA_InitTypeDef DMA_InitStructure;  
//    /* DMA clock enable */
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);//ע���õ��Ǹ�AHB
//      
//	/*--- LUMMOD_UART_Tx_DMA_Channel DMA Config ---*/
// 
//    DMA_Cmd(DMA1_Stream6, DISABLE);
//    DMA_DeInit(DMA1_Stream6);
//	DMA_InitStructure.DMA_Channel = DMA_Channel_4;
//    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART2->DR);
//	
//    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)g_ethernet_TXbuff;  //����buff
//	
//	
//    DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
//    DMA_InitStructure.DMA_BufferSize = g_ethernet_TXbuff_len;			  //����buff����
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
//    DMA_Init(DMA1_Stream6, &DMA_InitStructure);
//	DMA_Cmd(DMA1_Stream6, DISABLE);
//    DMA_ITConfig(DMA1_Stream6, DMA_IT_TC, ENABLE);
//   
///*--- LUMMOD_UART_Rx_DMA_Channel DMA Config ---*/
// 

////    DMA_Cmd(DMA1_Stream5, DISABLE);
////    DMA_DeInit(DMA1_Stream5);
////	  DMA_InitStructure.DMA_Channel = DMA_Channel_4;
////    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART2->DR);
////    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)g_ethernet_RXbuff; 	//����buff
////    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory ;
////    DMA_InitStructure.DMA_BufferSize = g_ethernet_RXbuff_len;				//����buff����
////    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
////    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
////    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
////    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
////    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
////	  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable; 
////    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;	
////    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
////	  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//�洢��ͻ�����δ���
////	  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//����ͻ�����δ���
////    DMA_Init(DMA1_Stream5, &DMA_InitStructure);
////    DMA_Cmd(DMA1_Stream5, ENABLE);  


//}

//void Uart2_Start_DMA_Tx(u16 size)
//{
//    DMA_SetCurrDataCounter(DMA1_Stream6,size);
//    DMA_Cmd(DMA1_Stream6, ENABLE);
//}


void WIFI_Send(char *str,u16 len)
{
	//�ַ����ͺ���
	USART_OUT(USART2,str,len);
}
void WIFI_delay(void)
{
//    OS_ERR *err;
    //OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,err);
    delay_ms(10);
}


void WIFI_init(u8 ID)
{
	//��ʼ��DBUS
    Dbus.Init(ID);//����Ĳ����Ǳ���ID
	Dbus.OutPut_interrupt(WIFI_Send);	
	Dbus.Delay_interrupt(WIFI_delay);

}




