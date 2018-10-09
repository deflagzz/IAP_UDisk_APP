#include "myNVIC.h"


void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	//--�ⲿ�ж�--���ȼ�--//
	
	

	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;  			//����2 -- ��̫��ת232
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
    NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream0_IRQn;  	//��λ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//			//����3  -- ���ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;		
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;             
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                     
	NVIC_Init(&NVIC_InitStructure);            
	
  	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;  			//����4 -- ������
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);  
	

	
	NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;  			//����6 -- �����ӿ�,��ʱû��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

//    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream3_IRQn;  	//����3�����ж�
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);	
	
//    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream4_IRQn;  	//����4�����ж�
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);	
	
//	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream6_IRQn;  	//����2�����ж�
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);	
	
//	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream1_IRQn;  
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);	
	
//	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream7_IRQn;  	//����6�����ж�
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
	
	
	




}











