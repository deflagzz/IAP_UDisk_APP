	
#include "uart4.h"	

////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif

//初始化IO 串口4
//bound:波特率
void uart4_init(u32 bound)
{
  //GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);//使能UART4时钟
 
	//串口4对应引脚复用映射
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_UART4);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_UART4);

	//UART4端口配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; //GPIOA9与GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA0，PA1
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);	
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);

  //UART4 初始化设置
	USART_InitStructure.USART_BaudRate = bound;									//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;					//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(UART4, &USART_InitStructure);										//初始化串口1
	

#if My_DMA_RX_U4			//1:开启DMA 0:关闭
	// DMA+空闲中断
	//	
	USART_ITConfig(UART4, USART_IT_IDLE, ENABLE);
	USART_Cmd(UART4, ENABLE);  //使能串口1 
	USART_ClearFlag(UART4, USART_FLAG_TC);
	USART_DMACmd(UART4, USART_DMAReq_Rx, ENABLE);
	USART_DMACmd(UART4, USART_DMAReq_Tx, ENABLE);

	#else
	//普通接收中断
	//
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
	USART_Cmd(UART4, ENABLE);  
	USART_ClearFlag(UART4, USART_FLAG_TC);

#endif	
	
}

//DMA+空闲中断
#if My_DMA_RX_U4
u16 g_modbus_RX_num;
void UART4_IRQHandler(void)                
{
	
#if SYSTEM_SUPPORT_OS 	
	OSIntEnter();    
#endif
	
	if(USART_GetITStatus(UART4, USART_IT_IDLE) != RESET) 
	{
		DMA_Cmd(DMA1_Stream2,DISABLE);
        rece_index = UART4->SR; 
        rece_index = UART4->DR; 
        rece_index = UART_RX_LEN - DMA_GetCurrDataCounter(DMA1_Stream2); 
        DMA1_Stream2->NDTR = UART_RX_LEN;
		if(rece_index>0)		//***
		{
			if(receBuf[0]==0x01||receBuf[0]==0x00)
			{
				AnalyzeRecieve(receBuf,UART_RX_LEN);
				if(receBuf[0]==0x01)
					send_comm();								//PA2拉高发送
					LED3 = !LED3;
			}
		} 		
		DMA_Cmd(DMA1_Stream2, ENABLE);
	} 
	//MDA发送
	if(USART_GetITStatus(UART4, USART_IT_TC) != RESET)			//DMA发送用这个
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);						//PA2拉低接收
		NVIC_ClearPendingIRQ(UART4_IRQn);
		USART_ClearITPendingBit(UART4,USART_IT_TC);
	}

	
#if SYSTEM_SUPPORT_OS 	
	OSIntExit();  											 
#endif
} 

//普通中断
#else 				
u16 g_modbus_RX_num;
void UART4_IRQHandler(void)                
{
	
#if SYSTEM_SUPPORT_OS 	
	OSIntEnter();    
#endif
	
	if(USART_GetFlagStatus(UART4, USART_IT_RXNE) != RESET) 
	{
		if(g_modbus_RX_num < UART_RX_LEN)	//250
		{
			receBuf[g_modbus_RX_num] = USART_ReceiveData(UART4);
			g_modbus_RX_num++;		
			
			if(g_modbus_RX_num >= 8)	//modbus  一帧报文8个字节
			{
				if(receBuf[0]==0x01||receBuf[0]==0x00)
				{	
					AnalyzeRecieve();
					if(receBuf[0]==0x01)
					send_comm();	
				}			
				g_modbus_RX_num = 0;
				LED3 = !LED3;
			}	
		}

		USART_ClearFlag(UART4,USART_IT_RXNE);
	} 

#if SYSTEM_SUPPORT_OS 	
	OSIntExit();  											 
#endif
} 




#endif

//





