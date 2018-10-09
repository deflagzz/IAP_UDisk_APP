#include "dma.h"																	   	  




u8 rece_index=0,rece2_index=0,rece6_index=0,rece3_index=0;
u8  sendBuf[UART_RX_LEN];  //���巢�����飬���������32���֣�64���ֽ�
u8  receBuf[UART_RX_LEN];	//����������飬����������32���֣�64���ֽ�д��



/*****************���������DMA��ʼ������******************/
   

void DMA_Uart4_Init(void)
{
		NVIC_InitTypeDef NVIC_InitStructure;
    DMA_InitTypeDef DMA_InitStructure;  
    /* DMA clock enable */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
      
	/*--- LUMMOD_UART_Tx_DMA_Channel DMA Config ---*/
 
	DMA_Cmd(DMA1_Stream4, DISABLE);
	DMA_DeInit(DMA1_Stream4);

	DMA_InitStructure.DMA_Channel = DMA_Channel_4;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&UART4->DR);
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)sendBuf;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_BufferSize = UART_TX_LEN;
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
		
	DMA_Init(DMA1_Stream4, &DMA_InitStructure);
	DMA_Cmd(DMA1_Stream4, DISABLE);
	DMA_ITConfig(DMA1_Stream4, DMA_IT_TC, ENABLE);//ʹ�ܴ�������ж�
   
/*--- LUMMOD_UART_Rx_DMA_Channel DMA Config ---*/
 
    DMA_Cmd(DMA1_Stream2, DISABLE);
    DMA_DeInit(DMA1_Stream2);
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&UART4->DR);
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)receBuf;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory ;
    DMA_InitStructure.DMA_BufferSize = UART_RX_LEN;
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
		
    DMA_Init(DMA1_Stream2, &DMA_InitStructure);
    DMA_Cmd(DMA1_Stream2, ENABLE);  

	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream4_IRQn;  //����4�����ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);	
}

/***************�������ڵ�DMA��ʼʱ���ͺ���****************/

void Uart4_Start_DMA_Tx(u16 size)
{
	  GPIO_SetBits(GPIOA,GPIO_Pin_2);
	  DMA_SetCurrDataCounter(DMA1_Stream4,size);//DMAͨ����DMA����Ĵ�С
	  DMA_Cmd(DMA1_Stream4, ENABLE);
}

/*****************����DMA�����жϷ�����******************/

void  DMA1_Stream4_IRQHandler(void)//uart4����DMA�жϷ�����
{
#if SYSTEM_SUPPORT_OS 	
	OSIntEnter();    
#endif	

	
    if(DMA_GetITStatus(DMA1_Stream4, DMA_IT_TCIF4))					//������ɱ�־Ϊ��ʱ
    {
		USART_ITConfig(UART4, USART_IT_TC, ENABLE);				//ʹ�ܷ�������ж�

		DMA_ClearITPendingBit(DMA1_Stream4, DMA_IT_TCIF4);		//�崫����ɱ�־
		DMA_Cmd(DMA1_Stream4, DISABLE);							//ʧ�ܡ�����
    }
	
#if SYSTEM_SUPPORT_OS 	
	OSIntExit();  											 
#endif		
}





