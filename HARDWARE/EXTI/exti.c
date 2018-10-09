#include "exti.h"


 

 
//PA6--TIM3-CH1
//PA7--TIM3-CH2
//PE5--TIM9-CH1
//PE6--TIM9-CH2	  

//�ⲿ�жϳ�ʼ������
void EXTIX_Init(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
		
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOF, &GPIO_InitStructure);//???GPIOE2,3,4

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource4);//PA6 ���ӵ��ж���6
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource5);//PA7 ���ӵ��ж���7

	/* ����EXTI_Line567 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line5 ;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
	EXTI_Init(&EXTI_InitStructure);//����

	EXTI_InitStructure.EXTI_Line = EXTI_Line4 ;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
	EXTI_Init(&EXTI_InitStructure);//����

	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//�ⲿ�ж�0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);//����	


	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//�ⲿ�ж�0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);//����	   
}


//PA6--TIM3-CH1
//PA7--TIM3-CH2
//PE5--TIM9-CH1
//PE6--TIM9-CH2
 
u8 g_flag_butt_stop;
u8 g_flag_butt_start;

void EXTI4_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line4) == SET)
	{
		if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_4)==0)  //ֹͣ����
		{	
			MotoStop(1);  
			g_flag_MOTORstart = 0; //��������ź�
			g_flag_butt_stop = 1;
			g_flag_butt_start = 0;
			
		}
		EXTI_ClearITPendingBit(EXTI_Line4); //���LINE5�ϵ��жϱ�־λ 		
	}	
}



//�ⲿ�ж�0�������
void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line5) == SET)	 
	{
		if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_5)==0)  //��������
		{
			MotoStart(1);
//			g_flag_MOTORstart = 1; //��������ź�
			g_flag_butt_start = 1;
			g_flag_butt_stop  = 0;
			g_xunzheng_ok = 0;
		}
		
		EXTI_ClearITPendingBit(EXTI_Line5); //���LINE5�ϵ��жϱ�־λ 
	}	

//	if(EXTI_GetITStatus(EXTI_Line6) == SET)	 
//	{
//		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==0)
//		{
//			g_val1++;
//		}
//		if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6)==0)
//		{
//			g_val4++;
//		}
//		
//		 
//		
//		EXTI_ClearITPendingBit(EXTI_Line6); //���LINE5�ϵ��жϱ�־λ 
//	}	
//	
//	if(EXTI_GetITStatus(EXTI_Line7) == SET)	 
//	{
//		 g_val2++;
//		
//		EXTI_ClearITPendingBit(EXTI_Line7); //���LINE5�ϵ��жϱ�־λ 
//	}	
	
	 
}	












