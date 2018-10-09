#include "myNVIC.h"


void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	//--外部中断--优先级--//
	
	

	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;  			//串口2 -- 以太网转232
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
    NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream0_IRQn;  	//电位器
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//			//串口3  -- 电池通信
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;		
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;             
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                     
	NVIC_Init(&NVIC_InitStructure);            
	
  	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;  			//串口4 -- 触摸屏
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);  
	

	
	NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;  			//串口6 -- 蓝牙接口,暂时没有
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

//    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream3_IRQn;  	//串口3发送中断
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);	
	
//    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream4_IRQn;  	//串口4发送中断
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);	
	
//	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream6_IRQn;  	//串口2发送中断
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);	
	
//	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream1_IRQn;  
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);	
	
//	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream7_IRQn;  	//串口6发送中断
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
	
	
	




}











