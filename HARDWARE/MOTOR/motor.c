#include "motor.h"


#if 0
////���������
////ʹ���ź�,�����ź�,���ų�ʼ��
//void motor_init(void) 
//{
//	GPIO_InitTypeDef  GPIO_InitStructure;


//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);	//
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);	//


//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10| GPIO_Pin_11| GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			//���
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//����
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;		//100MHz
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;			//����
//	GPIO_Init(GPIOG, &GPIO_InitStructure);					//
//	GPIO_SetBits(GPIOG,GPIO_Pin_10| GPIO_Pin_11| GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15);
//		
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			//���
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//����
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;		//100MHz
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;			//����
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
//	GPIO_SetBits(GPIOB,GPIO_Pin_3 | GPIO_Pin_4);
//	
//	
//}


//void motec_pulse(u8 speed)	//0~100
//{
//	u16 temp_true=0;
//	
//	//--100k -- 210    210 00 000
//	//--1k -- 21000
//	if(speed<1)
//	{
//		speed = 1;
//	}
//	else if(speed>100)
//	{
//		speed = 100;
//	}
//	temp_true = 500/speed;		

////100k -- 10/2=5
////1k -- 1000/2=500
//	PWM_1 = !PWM_1;
//	delay_us(temp_true);	//100k	
//	
//}
#endif
//

void Motor_Zzhuan(u8 Motor,u32 speed)           //���ǵ�������ڵĿ��ƴ�
{	
	if(speed > AGV_SYS.Motor_MAX_Speed)	//2999
	{
		speed = AGV_SYS.Motor_MAX_Speed;
	}
	switch(Motor)
	{
		case 1:									//���1		
			AGV_CanOpen_Send3(1,speed);
		break;
		case 2:									//���2
			AGV_CanOpen_Send3(2,speed);
		break;                                  
		case 3:									//���3
			AGV_CanOpen_Send3(3,speed);
		break;                                  
		case 4:									//���4
			AGV_CanOpen_Send3(4,speed);
		break;                                  
		default:
		break;
	}
}

void Motor_Fzhuan(u8 Motor,u32 speed)
{
	int tmep_spd=0;
	
		
	if(speed == 0)
	{
		tmep_spd = 0;
	}
	else if(speed > AGV_SYS.Motor_MAX_Speed)
	{
		tmep_spd = -AGV_SYS.Motor_MAX_Speed;
	}
	else
	{
		tmep_spd = -speed;
	}
	
	switch(Motor)
	{
		case 1:									//���1		
			AGV_CanOpen_Send3(1,tmep_spd);
		break;
		case 2:									//���2
			AGV_CanOpen_Send3(2,tmep_spd);
		break;                                  
		case 3:									//���3
			AGV_CanOpen_Send3(3,tmep_spd);
		break;                                  
		case 4:									//���4
			AGV_CanOpen_Send3(4,tmep_spd);
		break;
		default:
		break;
	}
}

//
//ǰ�����ֵĿ���
//
void LunZi_Go(u8 ID,u16 temp_speed)			
{

	switch(ID)
	{	
		case 1:
			Motor_Zzhuan(1,temp_speed); 
			break;
		case 2:
			Motor_Fzhuan(2,temp_speed); 
			break;	
		case 3:
			Motor_Zzhuan(3,temp_speed); 
			break;	
		case 4:
			Motor_Fzhuan(4,temp_speed); 
			break;	
		default:
			break;
	}
	
}

void LunZi_Back(u8 ID,u16 temp_speed)			
{

	switch(ID)
	{	
		case 1:
			Motor_Fzhuan(1,temp_speed); 
			break;
		case 2:
			Motor_Zzhuan(2,temp_speed); 
			break;	
		case 3:
			Motor_Fzhuan(3,temp_speed); 
			break;	
		case 4:
			Motor_Zzhuan(4,temp_speed); 
			break;	
		default:
			break;
	}
	
}





void qianlun_TurnL(u16 temp_speed)		//ǰ����ת
{
	if(temp_speed > AGV_SYS.XZ_MAX_Speed)
	{
		temp_speed = AGV_SYS.XZ_MAX_Speed;
	}

	LunZi_Back(1,temp_speed);
	LunZi_Go(2,temp_speed);
}
void qianlun_TurnR(u16 temp_speed)		//ǰ����ת
{
	if(temp_speed > AGV_SYS.XZ_MAX_Speed)
	{
		temp_speed = AGV_SYS.XZ_MAX_Speed;
	}
	

	LunZi_Go(1,temp_speed);
	LunZi_Back(2,temp_speed);
}

void houlun_TurnL(u16 temp_speed)		//������ת
{
	if(temp_speed > AGV_SYS.XZ_MAX_Speed)
	{
		temp_speed = AGV_SYS.XZ_MAX_Speed;
	}
	
	LunZi_Back(3,temp_speed);
	LunZi_Go(4,temp_speed);
}
void houlun_TurnR(u16 temp_speed)		//������ת
{
	if(temp_speed > AGV_SYS.XZ_MAX_Speed)
	{
		temp_speed = AGV_SYS.XZ_MAX_Speed;
	}
	LunZi_Go(3,temp_speed);
	LunZi_Back(4,temp_speed);
}



//��λ��0��Ӧǰ����
//��λ��1��Ӧ������
u16 g_xz_dwq[2];
u8 g_XZ_Ok;
u8 g_XZ_Beep;

void DWQ_XZ_qian(void)
{	
	u16 temp_i=300;
	int temp_cha[2]={0,0};
	
	g_xz_dwq[0] = g_After_filter[1];	
	temp_cha[0] = g_xz_dwq[0] - g_DWQ.qianlun_zhong_val;
	while( abs(temp_cha[0]) > 3 && temp_i--)	//10ms*300=3S   //��λ��Ѱ��������������
	{
		BEEP = 1;
		if(g_xz_dwq[0] > g_DWQ.qianlun_zhong_val)		//����ƫ��,��ת
		{
			qianlun_TurnL( abs(temp_cha[0]) * AGV_SYS.XZ_DWQ_Speed_bili );			//����ٶ�90*10����
		} 
		if(g_xz_dwq[0]<g_DWQ.qianlun_zhong_val)		//����ƫ��,��ת
		{
			qianlun_TurnR( abs(temp_cha[0]) * AGV_SYS.XZ_DWQ_Speed_bili );
		}
		
		g_xz_dwq[0] =  g_After_filter[1];		
		temp_cha[0] = g_xz_dwq[0] - g_DWQ.qianlun_zhong_val;
		
		delay_rtos(0,0,0,10);
	}
	MotoStop(1);	
	MotoStop(2);	
	BEEP = 0;
}
void DWQ_XZ_hou(void)
{
	u16 temp_j=300;
	int temp_cha[2]={0,0};
	
	g_xz_dwq[1] = g_After_filter[2];	
	temp_cha[1] = g_xz_dwq[1] - g_DWQ.houlun_zhong_val;
	while( abs(temp_cha[1]) > 3 && temp_j--)	//10ms*300=3S   //��λ��Ѱ��������������
	{
		BEEP = 1;
		if(g_xz_dwq[1]>g_DWQ.houlun_zhong_val)		//����ƫ��,��ת
		{
			houlun_TurnL( abs(temp_cha[1]) * AGV_SYS.XZ_DWQ_Speed_bili );
		}
		if(g_xz_dwq[1]<g_DWQ.houlun_zhong_val)		//����ƫ��,��ת
		{
			houlun_TurnR( abs(temp_cha[1]) * AGV_SYS.XZ_DWQ_Speed_bili );
		}
	
		g_xz_dwq[1] = g_After_filter[2];		
		temp_cha[1] = g_xz_dwq[1] - g_DWQ.houlun_zhong_val;
		
		delay_rtos(0,0,0,10);
	}	
	MotoStop(3);	
	MotoStop(4);	
	BEEP = 0;
}


void DwqXunZheng_QH(void)
{
	DWQ_XZ_qian();
	delay_rtos(0,0,0,100);
	DWQ_XZ_hou();
	
	g_XZ_Ok = 1;
	
}

AGV_CtXunZheng g_CtXunZheng;

u8 g_CT_XZ_jiian = 30;				//0-90��,ȡ90-30��

void CtXunZheng_qian(u8 cidaohang_id,u8 XZ_dir,u16 xunzheng_speed0)
{
	OS_ERR err;
	
	u16 temp_val=500;					//500*10=5s
	u8 *temp_CDH_num=NULL;
	
	u16 temp_dianweiqi_1=0;
	u8 temp_flag_L_jixian0=0;
	u8 temp_flag_R_jixian0=0;
	
	if(cidaohang_id == 1)			//ǰ1�ŵ���
	{
		temp_CDH_num = &g_CDH8_qian_1.Num;	
	}
	else if(cidaohang_id == 2)		//ǰ2�ŵ���
	{
		temp_CDH_num = &g_CDH8_qian_2.Num;
	}

	while(*temp_CDH_num < 2 && temp_val--)		//����2������,��ʱ�˳�		
	{									
		//ֹͣ���������»��߱��ϴ���
		if(g_shoudong_stop == 1 || g_Senser_InPut.button_Stop==1 || g_Start_flag.button_bizhang_Start==0)	//���ϴ��������� 0:����	
		{
			break;
		}		
		temp_dianweiqi_1 = g_After_filter[1];	//ǰ������λ��
		if(!XZ_dir)						//0:����Ѱ 
		{
			if(!temp_flag_L_jixian0)			//����δ��λ
			{
				if(temp_dianweiqi_1 > (g_DWQ.qianlun_L_val+g_CT_XZ_jiian))	//������ת��λ��ֵ��С 2.0
				{
					qianlun_TurnL(xunzheng_speed0);		//��һ����ת
				}
				else						//��һ�ε����޺���ת
				{
					MotoStop(1);
					MotoStop(2);
					qianlun_TurnR(xunzheng_speed0);
					temp_flag_L_jixian0 = 1;	//���޵�λ��־
				}				
			}
			else								//���޵�λ
			{
				if(!temp_flag_R_jixian0)			//�Ҽ���δ��λ
				{
					if(temp_dianweiqi_1 < g_DWQ.qianlun_R_val-g_CT_XZ_jiian)	//������ת��λ��ֵ��� 2.0
					{
						qianlun_TurnR(xunzheng_speed0);		//��ת
					}
					else						//�Ҽ��޺���ת
					{
						MotoStop(1);
						MotoStop(2);
						//qianlun_TurnL(xunzheng_speed0);
						temp_flag_R_jixian0 = 1;	//�Ҽ��޵�λ��־
					}				
				}
				else							//�Ҽ��޵�λ
				{			
					DWQ_XZ_qian();				//���ұ�������δ�ҵ��ŵ���,��λ��Ѱ������				
					break;
				}					
			}
		}
		else							//1:����Ѱ
		{
			if(!temp_flag_R_jixian0)			//�Ҽ���δ��λ
			{
				if(temp_dianweiqi_1 < g_DWQ.qianlun_R_val-g_CT_XZ_jiian)	//������ת��λ��ֵ��� 2.0
				{
					qianlun_TurnR(xunzheng_speed0);		//��ת
				}
				else						//�Ҽ��޺���ת
				{
					MotoStop(1);
					MotoStop(2);
					qianlun_TurnL(xunzheng_speed0);
					temp_flag_R_jixian0 = 1;	//�Ҽ��޵�λ��־
				}				
			}
			else
			{
				if(!temp_flag_L_jixian0)			//����δ��λ
				{
					if(temp_dianweiqi_1 > (g_DWQ.qianlun_L_val+g_CT_XZ_jiian))	//������ת��λ��ֵ��С 2.0
					{
						qianlun_TurnL(xunzheng_speed0);		//��һ����ת
					}
					else						//��һ�ε����޺���ת
					{
						MotoStop(1);
						MotoStop(2);
						//qianlun_TurnR(xunzheng_speed0);
						temp_flag_L_jixian0 = 1;	//���޵�λ��־
					}				
				}
				else							//�Ҽ��޵�λ
				{
					DWQ_XZ_qian();			//���ұ�������δ�ҵ��ŵ���,��λ��Ѱ������				
					break;
				}			
			
			
			}
		}		
		delay_rtos(0,0,0,10);
			
	}	
	//�˳�ѭ���ж�
	if(*temp_CDH_num >= 2)
	{
		if(cidaohang_id == 1)			//ǰ1�ŵ���
		{
			g_CtXunZheng.XunZ_OK_qian_1 = 1;
		}
		else if(cidaohang_id == 2)		//ǰ2�ŵ���
		{
			g_CtXunZheng.XunZ_OK_qian_2 = 1;
		}
	}
	else
	{
		MotoStop(1);
		MotoStop(2);
		
		if(cidaohang_id == 1)			//ǰ1�ŵ���
		{
			g_CtXunZheng.XunZ_OK_qian_1 = 0;
			g_AGV_speaker_flag.DOWN_gui_qian1 = 1;		
			delay_rtos(0,0,0,g_Speaker_delay);
		}
		else if(cidaohang_id == 2)		//ǰ2�ŵ���
		{
			g_CtXunZheng.XunZ_OK_qian_2 = 0;
			g_AGV_speaker_flag.DOWN_gui_qian2 = 1;		
			delay_rtos(0,0,0,g_Speaker_delay);
		}
	}
	

	MotoStop(1);
	MotoStop(2);			
}
void CtXunZheng_hou(u8 cidaohang_id,u8 XZ_dir,u16 xunzheng_speed)
{
	OS_ERR err;
	
	u16 temp_val=500;					//500*10=5s
	u8 *temp_CDH_num2=NULL;
	
	u16 temp_dianweiqi_2=0;
	u8 temp_flag_L_jixian=0;		//���޵�λ��־
	u8 temp_flag_R_jixian=0;		//�Ҽ��޵�λ��־
	

	if(cidaohang_id == 1)			//��1�ŵ���
	{
		temp_CDH_num2 = &g_CDH8_hou_1.Num;	
	}
	else if(cidaohang_id == 2)		//��2�ŵ���
	{
		temp_CDH_num2 = &g_CDH8_hou_2.Num;
	}
	
	while(*temp_CDH_num2 < 2 && temp_val--)		//����2������,��ʱ�˳�				
	{			
		//ֹͣ���������»��߱��ϴ���
		if(g_shoudong_stop == 1 || g_Senser_InPut.button_Stop==1 || g_Start_flag.button_bizhang_Start==0)	//���ϴ��������� 0:����	
		{
			break;
		}		
		
		temp_dianweiqi_2 = g_After_filter[2];	//��������λ��
		if(!XZ_dir)						//0:����Ѱ 
		{
			if(!temp_flag_L_jixian)			//����δ��λ
			{
				if(temp_dianweiqi_2 > (g_DWQ.houlun_L_val+g_CT_XZ_jiian))	//������ת��λ��ֵ��С 2.0
				{
					houlun_TurnL(xunzheng_speed);		//��һ����ת
				}
				else						//��һ�ε����޺���ת
				{
					MotoStop(3);
					MotoStop(4);
					houlun_TurnR(xunzheng_speed);
					temp_flag_L_jixian = 1;	//���޵�λ��־
				}				
			}
			else								//���޵�λ
			{
				if(!temp_flag_R_jixian)			//�Ҽ���δ��λ
				{
					if(temp_dianweiqi_2 < g_DWQ.houlun_R_val-g_CT_XZ_jiian)	//������ת��λ��ֵ��� 2.0
					{
						houlun_TurnR(xunzheng_speed);		//��ת
					}
					else						//�Ҽ��޺���ת
					{
						MotoStop(3);
						MotoStop(4);
						//qianlun_TurnL(xunzheng_speed0);
						temp_flag_R_jixian = 1;	//�Ҽ��޵�λ��־
					}				
				}
				else							//�Ҽ��޵�λ
				{
					DWQ_XZ_hou();			//���ұ�������δ�ҵ��ŵ���,��λ��Ѱ������			
					break;
				}					
			}
		}
		else							//1:����Ѱ
		{
			if(!temp_flag_R_jixian)			//�Ҽ���δ��λ
			{
				if(temp_dianweiqi_2 < g_DWQ.houlun_R_val-g_CT_XZ_jiian)	//������ת��λ��ֵ��� 2.0
				{
					houlun_TurnR(xunzheng_speed);		//��ת
				}
				else						//�Ҽ��޺���ת
				{
					MotoStop(3);
					MotoStop(4);
					houlun_TurnL(xunzheng_speed);
					temp_flag_R_jixian = 1;	//�Ҽ��޵�λ��־
				}				
			}
			else
			{
				if(!temp_flag_L_jixian)			//����δ��λ
				{
					if(temp_dianweiqi_2 > (g_DWQ.houlun_L_val+g_CT_XZ_jiian))	//������ת��λ��ֵ��С 2.0
					{
						houlun_TurnL(xunzheng_speed);		//��һ����ת
					}
					else						//��һ�ε����޺���ת
					{
						MotoStop(3);
						MotoStop(4);
						//qianlun_TurnR(xunzheng_speed0);
						temp_flag_L_jixian = 1;	//���޵�λ��־
					}				
				}
				else							//�Ҽ��޵�λ
				{
					DWQ_XZ_hou();			//���ұ�������δ�ҵ��ŵ���,��λ��Ѱ������				
					break;
				}			
			}
		}			
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err);	
	}		
		
	//�˳�ѭ���ж�
	if(*temp_CDH_num2 >= 2)
	{
		if(cidaohang_id == 1)			//��1�ŵ���
		{
			g_CtXunZheng.XunZ_OK_hou_1 = 1;
		}
		else if(cidaohang_id == 2)		//��2�ŵ���
		{
			g_CtXunZheng.XunZ_OK_hou_2 = 1;
		}
	}
	else
	{
		MotoStop(3);
		MotoStop(4);
		if(cidaohang_id == 1)			//��1�ŵ���
		{
			g_CtXunZheng.XunZ_OK_hou_1 = 0;
			
			g_AGV_speaker_flag.DOWN_gui_hou1 = 1;		
			delay_rtos(0,0,0,g_Speaker_delay);
		}
		else if(cidaohang_id == 2)		//��2�ŵ���
		{
			g_CtXunZheng.XunZ_OK_hou_2 = 0;
			g_AGV_speaker_flag.DOWN_gui_hou2 = 1;		
			delay_rtos(0,0,0,g_Speaker_delay);
		}
	}	
	
	
	MotoStop(3);		
	MotoStop(4);		


}


void check_CtXunZ_OK(u16 XunZ_speed)
{
	u8 temp_Val=0;
	u16 buff_speed=0;
	
	if(!g_AGV_Sta.Car_dir)	//0:ǰ��
	{
		CtXunZheng_qian(1,0,XunZ_speed);
		CtXunZheng_hou (1,0,XunZ_speed);		
		
		
		if(g_CtXunZheng.XunZ_OK_qian_1 && g_CtXunZheng.XunZ_OK_hou_1)
		{
			g_CtXunZheng.XunZ_OK_go_on_Both = 1;
			temp_Val = 1;
		}
		else
		{
			g_CtXunZheng.XunZ_OK_go_on_Both = 0;
			temp_Val = 0;		
		}	
	}
	else				//1:����
	{
		CtXunZheng_hou (2,1,XunZ_speed);	
		CtXunZheng_qian(2,1,XunZ_speed);
				
		if(g_CtXunZheng.XunZ_OK_hou_2 && g_CtXunZheng.XunZ_OK_qian_2)
		{
			g_CtXunZheng.XunZ_OK_go_back_Both = 1;
			temp_Val = 1;
		}
		else
		{
			g_CtXunZheng.XunZ_OK_go_back_Both = 0;
			temp_Val = 0;
		}	
	}
	
	buff_speed = AGV_SYS.Car_Auto_Speed;		//�����ٶ�
	AGV_SYS.Car_Auto_Speed = 0;					//����ǰ�ٶȸ�0
	g_Start_flag.Start_Auto_PID = temp_Val;		//1:�ҵ����� 0:δ�ҵ�
	
	if(temp_Val)	//�ҵ�����
	{
		g_Warning.chugui = 0;					//�����־
		g_AGV_speaker_flag.Ruan_Qi = 1;			//�Զ�ģʽ��:�������������
		delay_rtos(0,0,0,g_Speaker_delay);

		Ruan_Qi_jia(0,buff_speed,&AGV_SYS.Car_Auto_Speed);//��������
	}
	else			//δ�ҵ�����
	{
		//������ӳ��캯������������λ��,���л���δ����״̬
		g_Warning.chugui = 1;					//�����־
		AGV_SYS.Car_Auto_Speed = buff_speed;	//��ԭ�ٶ�
	}
}

void AGV_System_Stop(void)
{
	//MotoStop(0);
	g_Start_flag.Stop_AGV_SysCode = 1;


}	
void AGV_System_Start(void)
{
	g_Start_flag.Start_AGV_SysCode = 1;
	
}


u8 g_glag_bizhang;

void AGV_Stop2Start(void)
{
	
	
//	if(Ԥ��1 == 0)							//��λ�������ź�
//	{
//		g_Start_flag.button_bizhang_Start = 1;
//	}			
	if(g_shoudong_start == 1)				//�̴��� -- �������������� 1��Ч
	{		
		g_Start_flag.Start_button_Car = 1;
	}		
	if(g_Senser_InPut.button_Start==1 && g_Senser_InPut.button_Stop==0)	
	{
		g_Start_flag.Start_button_Car = 1;	//�̴���--���������������
		if(!g_AGV_Sta.Car_Auto2Manu_mode)
		{
			if(!g_start_button_down)
			{
				speek("����");	
				g_start_button_down = 1;	
			}		
		}


		
	}
	if(g_Start_flag.Start_AGV_SysCode)		//������--��������������������ֹͣ //1����
	{
		g_Start_flag.Start_AGV_SysCode = 0;
		g_Start_flag.Start_button_Car = 1;
	}	
	
	
	
	if(g_Start_flag.Start_IR)				//������--��������������������ֹͣ //1����
	{
		g_Start_flag.button_bizhang_Start = 1;
	}	

	if(g_Start_flag.Start_jixie)			//������--��������������������ֹͣ //1����
	{
		g_Start_flag.button_bizhang_Start = 1;
	}	

//////////////////////////////////////////////////////////////////

//	if(Ԥ��2 == 1)							//��λ��ֹͣ�ź�
//	{
//		g_Start_flag.button_bizhang_Start = 0;
//	}			
	if(g_shoudong_stop == 1)				//�̴���--������ֹͣ���� 1��Ч
	{
		g_Start_flag.Stop_button_Car = 1;
	}			
	if(g_Senser_InPut.button_Stop==1)			//�̴���--�������ֹͣ���� -- ϵͳ������ͣ��Ҳ���������ͣ
	{
		g_Start_flag.Stop_button_Car = 1;
		if(!g_stop_button_down)
		{
			speek("ֹͣ");	
			g_stop_button_down = 1;	
		}
	
	}	
	if(g_Start_flag.Stop_AGV_SysCode)		//������--��������������������ֹͣ //1����
	{
		g_Start_flag.Stop_AGV_SysCode = 0;
		g_Start_flag.Stop_button_Car = 1;
	}			

	
	
	if(!g_Start_flag.Start_IR)				//������--//��������������������ֹͣ //1����
	{
		g_Start_flag.button_bizhang_Start = 0;

	}		

	
	if(!g_Start_flag.Start_jixie)			//������--��������������������ֹͣ //1����
	{
		g_Start_flag.button_bizhang_Start = 0;

	}	
	

	

	if(!g_AGV_Sta.Car_Auto2Manu_mode)	//0:�Զ�
	{
		//AGV����Ѱ��
		if(g_Start_flag.Start_button_Car==1 && g_Start_flag.button_bizhang_Start==1)	
		{
			if(!g_Start_flag.Start_Auto_PID)			//�Զ�ģʽδ����		-- ���Ҫ�޸�?
			{
				if(!g_CtXunZheng.XunZ_Start)	//����Ѱ��δ����
				{
					//�Զ�ģʽ--�ŵ���Ѱ��
					g_CtXunZheng.XunZ_Start = 1;					
				}							
			}
			g_Start_flag.Start_button_Car = 0;			//����Զ�������־
			g_Start_flag.Stop_button_Car = 0;			
		}
		//AGV������
		if(g_Start_flag.Stop_button_Car==0 && g_Start_flag.button_bizhang_Start==1)				//����δ����
		{
			if(g_glag_bizhang == 1)
			{				
				if(!g_CtXunZheng.XunZ_Start)	//����Ѱ��δ����
				{
					//�Զ�ģʽ--�ŵ���Ѱ��
					g_CtXunZheng.XunZ_Start = 1;					
				}				
				g_glag_bizhang = 0;					
			}
		}
		//AGVֹͣ
		if(g_Start_flag.Stop_button_Car==1 || g_Start_flag.button_bizhang_Start==0)		
		{
			if(g_Start_flag.button_bizhang_Start==0)		//����ֹͣ
			{	
				g_glag_bizhang = 1;
			}
			
			if(g_Start_flag.Start_Auto_PID)	//�����Զ����߲��ܽ���
			{
				Ruan_Stop(&AGV_SYS.Car_Auto_Speed);			
			}

		}
	}	
	else				//1:�ֶ�
	{
		if(g_Start_flag.Stop_button_Car==1 || g_Start_flag.button_bizhang_Start==0)	//���ϴ��������� 0:����	
		{
			g_Start_flag.Stop_button_Car = 0;
			g_Start_flag.Start_Manu_PID	 = 0;				//����ֹͣ��־

		}				
	}
}









void MotoStop(u8 num)
{
	if(num>0 && num < 5)
	{
		AGV_CanOpen_Send3(num,0);	
	}
	else if(num==0)
	{
		AGV_CanOpen_Send3(1,0);	
		AGV_CanOpen_Send3(2,0);	
		AGV_CanOpen_Send3(3,0);	
		AGV_CanOpen_Send3(4,0);	
				
	}
}








AGV_Start_flag g_Start_flag = 
{
	0, 		//u8 Start_AGV_SysCode;		//ϵͳ�������
	0, 		//u8 Start_IR;				//ϵͳ�������
	0,		//u8 Start_jixie;			//ϵͳ�������
	0,		//u8 button_Start;		
	0, 		//u8 Start_Auto_PID;		//�ײ�PID�����Ŀ���--�Զ�
	0,   	//u8 Start_Manu_PID;		//�ײ�PID�����Ŀ���--�ֶ�
	0,
	0,
	1
};     
       















