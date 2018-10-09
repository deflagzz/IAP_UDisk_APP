#include "button.h"


Senser_InPut  g_Senser_InPut;
Senser_Enable g_Senser_Enable = 
{
	1,
	1,
	1,
	1,
	1,
	1
}
;









//PF4 -- ֹͣ
//PF5 -- ����
//PF6 -- ��_��Ͳ������� 	-- (ԭ��ͣ)

//PF14-- ǰ_������� 		-- (ǣ���˿���2)   Զ
//PF10-- ��_������� 		-- (ǣ���˿���1)	Զ

//PF9 -- ǰ����---��
//PF8 -- �����--��

//PA6 -- ǰ��ײ
//PA7 -- ���ײ

//PF7 -- ��_��Ͳ������� 	-- (���ÿ���1) 


//�ⲿ�жϳ�ʼ������
void button_input_init(void)//��������,�͵�ƽ����
{	
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
		
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7| GPIO_Pin_8| GPIO_Pin_9|
	GPIO_Pin_10| GPIO_Pin_14; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
}



u8 AGV_input_24V_buff[16];
u8 g_stop_button_down;
u8 g_start_button_down;
void agv_24V_input(void)	//δ����������,������
{
	//��ťһֱ�����Ա������ܶ��,����ֻ��������һ��
	if(!g_button_stop)								//���ֹͣ��ť	0:����	//g_jixieKEy_stop
	{
		g_Senser_InPut.button_Stop = 1;				//1��λ
	}
	else
	{
		g_Senser_InPut.button_Stop = 0;
		g_stop_button_down = 0;						//���±�־��λ
	}
		
	if(!g_button_start)								//���������ť	g_jixieKEY_start
	{
		g_Senser_InPut.button_Start = 1;
	}
	else
	{
		g_start_button_down = 0;
		g_Senser_InPut.button_Start = 0;			//���±�־��λ
	}		
	
	if(g_Senser_Enable.IR_qian_yuan) //AGV_SYS.Key_IR_jin
	{
		if(!g_flag_IR_qian_yuan)					//ǰԶ����  	//g_IR_yuan_CAR_qian
		{
			g_Senser_InPut.IR_qian_yuan =  1;		//1:��λ
		}
		else
		{
			g_Senser_InPut.IR_qian_yuan =  0;
		}		
	}
	else
	{
		g_Senser_InPut.IR_qian_yuan =  0;					
	}


	if(g_Senser_Enable.IR_hou_yuan)
	{
		if(!g_flag_IR_hou_yuan)						//��Զ����		//g_IR_yuan_CAR_hou
		{
			g_Senser_InPut.IR_hou_yuan = 1;
		}
		else
		{
			g_Senser_InPut.IR_hou_yuan = 0;
		}			
	}	
	else
	{
			g_Senser_InPut.IR_hou_yuan = 0;
		
	}	

	if(g_Senser_Enable.IR_qian_jin)
	{
		if(!g_flag_IR_qian_jin)						//ǰ������  	//g_IR_jin_CAR_qian
		{
			g_Senser_InPut.IR_qian_jin = 1;
			g_Warning.IR_qian = 1;
		}
		else
		{
			g_Senser_InPut.IR_qian_jin= 0;
			g_Warning.IR_qian = 0;
		}		
	}	
	else
	{
			g_Senser_InPut.IR_qian_jin= 0;
			g_Warning.IR_qian = 0;
	}	
	
	if(g_Senser_Enable.IR_hou_jin)
	{
		if(!g_flag_IR_hou_jin)						//�������  	//g_IR_jin_CAR_hou
		{
			g_Senser_InPut.IR_hou_jin = 1;
			g_Warning.IR_hou = 1;
		}
		else
		{
			g_Senser_InPut.IR_hou_jin =  0;
			g_Warning.IR_hou = 0;
		}	
	}
	else
	{
			g_Senser_InPut.IR_hou_jin =  0;
			g_Warning.IR_hou = 0;
	}	
	
	if(g_Senser_Enable.jixie_qian)
	{	
		if(!g_flag_fangzhuang_qian)					//��еǰ		g_jiexie_qian
		{
			g_Senser_InPut.JiXie_qian = 1;
			g_Warning.jixie_qian = 1;
		}
		else
		{
			g_Senser_InPut.JiXie_qian = 0;
			g_Warning.jixie_qian = 0;
		}		
	}
	else
	{
			g_Senser_InPut.JiXie_qian = 0;
			g_Warning.jixie_qian = 0;
	}

	if(g_Senser_Enable.jixie_qian)
	{
		if(!g_flag_fangzhuang_hou)					//��е��		g_jiexie_hou
		{
			g_Senser_InPut.JiXie_hou = 1;
			g_Warning.jixie_hou = 1;
		}
		else
		{
			g_Senser_InPut.JiXie_hou = 0;
			g_Warning.jixie_hou = 0;
		}		
	}
	else
	{
			g_Senser_InPut.JiXie_hou = 0;
			g_Warning.jixie_hou = 0;
	}
		
	
	
	if(!g_flag_guntong_zuo)				//g_IR_guntong_left
	{
		g_Senser_InPut.gunt_IR_L = 1;		
	}
	else
	{
		g_Senser_InPut.gunt_IR_L = 0; 
	}	
	
	if(!g_flag_guntong_you)				//g_IR_guntong_right
	{
		g_Senser_InPut.gunt_IR_R = 1;
	}
	else
	{
		g_Senser_InPut.gunt_IR_R = 0;
	}	
	
	







}
u8 g_temp_i[4];
void SD2ZD_check_UP(void)
{

	
	if(g_shoudong_manual == 1 && !g_temp_i[0])						//��Ļ���ֶ���������ʱ
	{
		Shou_Dong();							//�е��ֶ�����	
		g_temp_i[0] = 1;			 
	}
	else if(g_shoudong_auto == 1 && !g_temp_i[0])					//��Ļ���Զ���������ʱ
	{
		Zi_Dong();								//�е��Զ�����		
		g_temp_i[0] = 1;		
	}
	else if(g_shoudong_manual == 0 && g_shoudong_auto == 0)
	{
		g_temp_i[0] = 0;		
	}
}

void ZD_check_UP(void)
{
	
	if(g_shoudong_start == 1 && !g_temp_i[1])			//����
	{
		HmiTaskState = 5;				//��������
		g_AGV_speaker_flag.start = 1;		//�Զ�ģʽ��:��������������
		delay_rtos(0,0,0,g_Speaker_delay);		
		g_temp_i[1] = 1;		
	}

	else if(g_shoudong_stop == 1 && !g_temp_i[1])		 	//ֹͣ
	{
		HmiTaskState = 4;					//ֹͣ
		g_AGV_speaker_flag.stop = 1;
		delay_rtos(0,0,0,g_Speaker_delay);	
		g_temp_i[1] = 1;	
	}
	else if(g_shoudong_goto == 1 && !g_temp_i[1])		//�Զ�ģʽ��,�������߷���
	{
		Qian_Jin();		
		g_temp_i[1] = 1;	
	}
	else if(g_shoudong_goback == 1 && !g_temp_i[1]) 	//�Զ�ģʽ��,�������߷���
	{
		Hou_Tui();	
		g_temp_i[1] = 1;	
	}
	else if(g_Manu_L_FenCha == 1 && !g_temp_i[1]) 		//�Զ�ģʽ��,���÷ֲ淽��-��
	{
		Zuo_Fen();
		g_temp_i[1] = 1;	
	}	
	else if(g_Manu_R_FenCha == 1 && !g_temp_i[1]) 		//�Զ�ģʽ��,���÷ֲ淽��-��
	{
		You_Fen();
		g_temp_i[1] = 1;	
	}	
	else if(g_shoudong_start == 0&&g_shoudong_stop == 0&&g_shoudong_goto == 0&&g_shoudong_goback == 0&&g_Manu_L_FenCha == 0&&g_Manu_R_FenCha == 0)
	{
		g_temp_i[1] = 0;	

	}
}


void SD_check_UP(void)
{

	
	if(g_shoudong_guntong_youzhuan == 1 && !g_temp_i[2])				//��Ͳ��ת
	 {
	//		g_AGV_speaker_flag.GunT_R = 1;
	//		delay_rtos(0,0,0,10);
	//	 
	//		guntong_start = 1;
	//		guntong_fanzhuan = 1;
			GunTong_R(1);
			g_temp_i[2] = 1;	
	 }
	//else if(g_shoudong_guntong_youzhuan == 0 && !temp_i)
	//{
	//	g_AGV_speaker_flag.GunT_stop = 1;
	//	delay_rtos(0,0,0,10);
	// 
	//	guntong_start = 0;
	//	guntong_fanzhuan = 0;
	//	temp_i = 1;	
	//}
	 else if(g_shoudong_guntong_zuozhuan == 1 && !g_temp_i[2])				//��Ͳ��ת
	 {
	//		g_AGV_speaker_flag.GunT_L = 1;
	//		delay_rtos(0,0,0,10);
	//		guntong_start = 1;	
		 
			GunTong_L(1);
		 
			g_temp_i[2] = 1;	
	 }	
	 else if(g_shoudong_guntong_youzhuan == 0&&g_shoudong_guntong_zuozhuan == 0&&g_temp_i[2])
	 {
			GunTong_L(0);
			g_temp_i[2] = 0;		
	 }	

}


void ZD_check_UP_AUTO(void)								//�Զ����߽���
{

	if(g_shoudong_start == 1 && !g_temp_i[3])			//����
	{
		HmiTaskState = 5;				//��������
		g_AGV_speaker_flag.start = 1;		//�Զ�ģʽ��:��������������
		delay_rtos(0,0,0,g_Speaker_delay);		
				
		g_temp_i[3] = 1;		
	}

	else if(g_shoudong_stop == 1 && !g_temp_i[3])		 	//ֹͣ
	{
		HmiTaskState = 4;					//ֹͣ
		g_AGV_speaker_flag.stop = 1;
		delay_rtos(0,0,0,g_Speaker_delay);	
		g_temp_i[3] = 1;	
	}

	else if(g_shoudong_start == 0&&g_shoudong_stop == 0)
	{
		g_temp_i[3] = 0;	

	}
}

u16 Last_speed_AGV;
void IR_yuan(u16 *last_speed,u16 *agv_spped)
{
	
	if(g_Senser_InPut.IR_hou_yuan)	//Զ���ⴥ��
	{
		if(!last_speed)
		{
			*last_speed = *agv_spped;
		}
		
		*agv_spped = *last_speed/2;
	}
	else
	{
		*agv_spped = *last_speed;
		*last_speed = 0;
	}






}











	

