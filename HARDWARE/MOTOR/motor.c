#include "motor.h"


#if 0
////电机驱动器
////使能信号,方向信号,引脚初始化
//void motor_init(void) 
//{
//	GPIO_InitTypeDef  GPIO_InitStructure;


//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);	//
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);	//


//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10| GPIO_Pin_11| GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			//输出
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//推挽
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;		//100MHz
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;			//上拉
//	GPIO_Init(GPIOG, &GPIO_InitStructure);					//
//	GPIO_SetBits(GPIOG,GPIO_Pin_10| GPIO_Pin_11| GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15);
//		
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			//输出
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//推挽
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;		//100MHz
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;			//上拉
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

void Motor_Zzhuan(u8 Motor,u32 speed)           //这是电机驱动口的控制处
{	
	if(speed > AGV_SYS.Motor_MAX_Speed)	//2999
	{
		speed = AGV_SYS.Motor_MAX_Speed;
	}
	switch(Motor)
	{
		case 1:									//电机1		
			AGV_CanOpen_Send3(1,speed);
		break;
		case 2:									//电机2
			AGV_CanOpen_Send3(2,speed);
		break;                                  
		case 3:									//电机3
			AGV_CanOpen_Send3(3,speed);
		break;                                  
		case 4:									//电机4
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
		case 1:									//电机1		
			AGV_CanOpen_Send3(1,tmep_spd);
		break;
		case 2:									//电机2
			AGV_CanOpen_Send3(2,tmep_spd);
		break;                                  
		case 3:									//电机3
			AGV_CanOpen_Send3(3,tmep_spd);
		break;                                  
		case 4:									//电机4
			AGV_CanOpen_Send3(4,tmep_spd);
		break;
		default:
		break;
	}
}

//
//前驱动轮的控制
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





void qianlun_TurnL(u16 temp_speed)		//前轮左转
{
	if(temp_speed > AGV_SYS.XZ_MAX_Speed)
	{
		temp_speed = AGV_SYS.XZ_MAX_Speed;
	}

	LunZi_Back(1,temp_speed);
	LunZi_Go(2,temp_speed);
}
void qianlun_TurnR(u16 temp_speed)		//前轮右转
{
	if(temp_speed > AGV_SYS.XZ_MAX_Speed)
	{
		temp_speed = AGV_SYS.XZ_MAX_Speed;
	}
	

	LunZi_Go(1,temp_speed);
	LunZi_Back(2,temp_speed);
}

void houlun_TurnL(u16 temp_speed)		//后轮左转
{
	if(temp_speed > AGV_SYS.XZ_MAX_Speed)
	{
		temp_speed = AGV_SYS.XZ_MAX_Speed;
	}
	
	LunZi_Back(3,temp_speed);
	LunZi_Go(4,temp_speed);
}
void houlun_TurnR(u16 temp_speed)		//后轮右转
{
	if(temp_speed > AGV_SYS.XZ_MAX_Speed)
	{
		temp_speed = AGV_SYS.XZ_MAX_Speed;
	}
	LunZi_Go(3,temp_speed);
	LunZi_Back(4,temp_speed);
}



//电位器0对应前驱动
//电位器1对应后驱动
u16 g_xz_dwq[2];
u8 g_XZ_Ok;
u8 g_XZ_Beep;

void DWQ_XZ_qian(void)
{	
	u16 temp_i=300;
	int temp_cha[2]={0,0};
	
	g_xz_dwq[0] = g_After_filter[1];	
	temp_cha[0] = g_xz_dwq[0] - g_DWQ.qianlun_zhong_val;
	while( abs(temp_cha[0]) > 3 && temp_i--)	//10ms*300=3S   //电位器寻正长鸣叫在这里
	{
		BEEP = 1;
		if(g_xz_dwq[0] > g_DWQ.qianlun_zhong_val)		//驱动偏右,左转
		{
			qianlun_TurnL( abs(temp_cha[0]) * AGV_SYS.XZ_DWQ_Speed_bili );			//最大速度90*10左右
		} 
		if(g_xz_dwq[0]<g_DWQ.qianlun_zhong_val)		//驱动偏左,右转
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
	while( abs(temp_cha[1]) > 3 && temp_j--)	//10ms*300=3S   //电位器寻正长鸣叫在这里
	{
		BEEP = 1;
		if(g_xz_dwq[1]>g_DWQ.houlun_zhong_val)		//驱动偏右,左转
		{
			houlun_TurnL( abs(temp_cha[1]) * AGV_SYS.XZ_DWQ_Speed_bili );
		}
		if(g_xz_dwq[1]<g_DWQ.houlun_zhong_val)		//驱动偏左,右转
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

u8 g_CT_XZ_jiian = 30;				//0-90度,取90-30度

void CtXunZheng_qian(u8 cidaohang_id,u8 XZ_dir,u16 xunzheng_speed0)
{
	OS_ERR err;
	
	u16 temp_val=500;					//500*10=5s
	u8 *temp_CDH_num=NULL;
	
	u16 temp_dianweiqi_1=0;
	u8 temp_flag_L_jixian0=0;
	u8 temp_flag_R_jixian0=0;
	
	if(cidaohang_id == 1)			//前1磁导航
	{
		temp_CDH_num = &g_CDH8_qian_1.Num;	
	}
	else if(cidaohang_id == 2)		//前2磁导航
	{
		temp_CDH_num = &g_CDH8_qian_2.Num;
	}

	while(*temp_CDH_num < 2 && temp_val--)		//少于2个亮点,超时退出		
	{									
		//停止按键被按下或者避障触发
		if(g_shoudong_stop == 1 || g_Senser_InPut.button_Stop==1 || g_Start_flag.button_bizhang_Start==0)	//避障传感器触发 0:触发	
		{
			break;
		}		
		temp_dianweiqi_1 = g_After_filter[1];	//前驱动电位器
		if(!XZ_dir)						//0:先左寻 
		{
			if(!temp_flag_L_jixian0)			//左极限未到位
			{
				if(temp_dianweiqi_1 > (g_DWQ.qianlun_L_val+g_CT_XZ_jiian))	//轮子左转电位器值变小 2.0
				{
					qianlun_TurnL(xunzheng_speed0);		//第一次左转
				}
				else						//第一次到左极限后右转
				{
					MotoStop(1);
					MotoStop(2);
					qianlun_TurnR(xunzheng_speed0);
					temp_flag_L_jixian0 = 1;	//左极限到位标志
				}				
			}
			else								//左极限到位
			{
				if(!temp_flag_R_jixian0)			//右极限未到位
				{
					if(temp_dianweiqi_1 < g_DWQ.qianlun_R_val-g_CT_XZ_jiian)	//轮子右转电位器值变大 2.0
					{
						qianlun_TurnR(xunzheng_speed0);		//右转
					}
					else						//右极限后左转
					{
						MotoStop(1);
						MotoStop(2);
						//qianlun_TurnL(xunzheng_speed0);
						temp_flag_R_jixian0 = 1;	//右极限到位标志
					}				
				}
				else							//右极限到位
				{			
					DWQ_XZ_qian();				//左右遍历结束未找到磁导航,电位器寻正结束				
					break;
				}					
			}
		}
		else							//1:先右寻
		{
			if(!temp_flag_R_jixian0)			//右极限未到位
			{
				if(temp_dianweiqi_1 < g_DWQ.qianlun_R_val-g_CT_XZ_jiian)	//轮子右转电位器值变大 2.0
				{
					qianlun_TurnR(xunzheng_speed0);		//右转
				}
				else						//右极限后左转
				{
					MotoStop(1);
					MotoStop(2);
					qianlun_TurnL(xunzheng_speed0);
					temp_flag_R_jixian0 = 1;	//右极限到位标志
				}				
			}
			else
			{
				if(!temp_flag_L_jixian0)			//左极限未到位
				{
					if(temp_dianweiqi_1 > (g_DWQ.qianlun_L_val+g_CT_XZ_jiian))	//轮子左转电位器值变小 2.0
					{
						qianlun_TurnL(xunzheng_speed0);		//第一次左转
					}
					else						//第一次到左极限后右转
					{
						MotoStop(1);
						MotoStop(2);
						//qianlun_TurnR(xunzheng_speed0);
						temp_flag_L_jixian0 = 1;	//左极限到位标志
					}				
				}
				else							//右极限到位
				{
					DWQ_XZ_qian();			//左右遍历结束未找到磁导航,电位器寻正结束				
					break;
				}			
			
			
			}
		}		
		delay_rtos(0,0,0,10);
			
	}	
	//退出循环判断
	if(*temp_CDH_num >= 2)
	{
		if(cidaohang_id == 1)			//前1磁导航
		{
			g_CtXunZheng.XunZ_OK_qian_1 = 1;
		}
		else if(cidaohang_id == 2)		//前2磁导航
		{
			g_CtXunZheng.XunZ_OK_qian_2 = 1;
		}
	}
	else
	{
		MotoStop(1);
		MotoStop(2);
		
		if(cidaohang_id == 1)			//前1磁导航
		{
			g_CtXunZheng.XunZ_OK_qian_1 = 0;
			g_AGV_speaker_flag.DOWN_gui_qian1 = 1;		
			delay_rtos(0,0,0,g_Speaker_delay);
		}
		else if(cidaohang_id == 2)		//前2磁导航
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
	u8 temp_flag_L_jixian=0;		//左极限到位标志
	u8 temp_flag_R_jixian=0;		//右极限到位标志
	

	if(cidaohang_id == 1)			//后1磁导航
	{
		temp_CDH_num2 = &g_CDH8_hou_1.Num;	
	}
	else if(cidaohang_id == 2)		//后2磁导航
	{
		temp_CDH_num2 = &g_CDH8_hou_2.Num;
	}
	
	while(*temp_CDH_num2 < 2 && temp_val--)		//少于2个亮点,超时退出				
	{			
		//停止按键被按下或者避障触发
		if(g_shoudong_stop == 1 || g_Senser_InPut.button_Stop==1 || g_Start_flag.button_bizhang_Start==0)	//避障传感器触发 0:触发	
		{
			break;
		}		
		
		temp_dianweiqi_2 = g_After_filter[2];	//后驱动电位器
		if(!XZ_dir)						//0:先左寻 
		{
			if(!temp_flag_L_jixian)			//左极限未到位
			{
				if(temp_dianweiqi_2 > (g_DWQ.houlun_L_val+g_CT_XZ_jiian))	//轮子左转电位器值变小 2.0
				{
					houlun_TurnL(xunzheng_speed);		//第一次左转
				}
				else						//第一次到左极限后右转
				{
					MotoStop(3);
					MotoStop(4);
					houlun_TurnR(xunzheng_speed);
					temp_flag_L_jixian = 1;	//左极限到位标志
				}				
			}
			else								//左极限到位
			{
				if(!temp_flag_R_jixian)			//右极限未到位
				{
					if(temp_dianweiqi_2 < g_DWQ.houlun_R_val-g_CT_XZ_jiian)	//轮子右转电位器值变大 2.0
					{
						houlun_TurnR(xunzheng_speed);		//右转
					}
					else						//右极限后左转
					{
						MotoStop(3);
						MotoStop(4);
						//qianlun_TurnL(xunzheng_speed0);
						temp_flag_R_jixian = 1;	//右极限到位标志
					}				
				}
				else							//右极限到位
				{
					DWQ_XZ_hou();			//左右遍历结束未找到磁导航,电位器寻正结束			
					break;
				}					
			}
		}
		else							//1:先右寻
		{
			if(!temp_flag_R_jixian)			//右极限未到位
			{
				if(temp_dianweiqi_2 < g_DWQ.houlun_R_val-g_CT_XZ_jiian)	//轮子右转电位器值变大 2.0
				{
					houlun_TurnR(xunzheng_speed);		//右转
				}
				else						//右极限后左转
				{
					MotoStop(3);
					MotoStop(4);
					houlun_TurnL(xunzheng_speed);
					temp_flag_R_jixian = 1;	//右极限到位标志
				}				
			}
			else
			{
				if(!temp_flag_L_jixian)			//左极限未到位
				{
					if(temp_dianweiqi_2 > (g_DWQ.houlun_L_val+g_CT_XZ_jiian))	//轮子左转电位器值变小 2.0
					{
						houlun_TurnL(xunzheng_speed);		//第一次左转
					}
					else						//第一次到左极限后右转
					{
						MotoStop(3);
						MotoStop(4);
						//qianlun_TurnR(xunzheng_speed0);
						temp_flag_L_jixian = 1;	//左极限到位标志
					}				
				}
				else							//右极限到位
				{
					DWQ_XZ_hou();			//左右遍历结束未找到磁导航,电位器寻正结束				
					break;
				}			
			}
		}			
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err);	
	}		
		
	//退出循环判断
	if(*temp_CDH_num2 >= 2)
	{
		if(cidaohang_id == 1)			//后1磁导航
		{
			g_CtXunZheng.XunZ_OK_hou_1 = 1;
		}
		else if(cidaohang_id == 2)		//后2磁导航
		{
			g_CtXunZheng.XunZ_OK_hou_2 = 1;
		}
	}
	else
	{
		MotoStop(3);
		MotoStop(4);
		if(cidaohang_id == 1)			//后1磁导航
		{
			g_CtXunZheng.XunZ_OK_hou_1 = 0;
			
			g_AGV_speaker_flag.DOWN_gui_hou1 = 1;		
			delay_rtos(0,0,0,g_Speaker_delay);
		}
		else if(cidaohang_id == 2)		//后2磁导航
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
	
	if(!g_AGV_Sta.Car_dir)	//0:前进
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
	else				//1:后退
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
	
	buff_speed = AGV_SYS.Car_Auto_Speed;		//缓存速度
	AGV_SYS.Car_Auto_Speed = 0;					//软启前速度给0
	g_Start_flag.Start_Auto_PID = temp_Val;		//1:找到磁条 0:未找到
	
	if(temp_Val)	//找到磁条
	{
		g_Warning.chugui = 0;					//出轨标志
		g_AGV_speaker_flag.Ruan_Qi = 1;			//自动模式下:软起的语音播报
		delay_rtos(0,0,0,g_Speaker_delay);

		Ruan_Qi_jia(0,buff_speed,&AGV_SYS.Car_Auto_Speed);//软启加速
	}
	else			//未找到磁条
	{
		//这里添加出轨函数并反馈给上位机,并切换到未就绪状态
		g_Warning.chugui = 1;					//出轨标志
		AGV_SYS.Car_Auto_Speed = buff_speed;	//还原速度
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
	
	
//	if(预留1 == 0)							//上位机启动信号
//	{
//		g_Start_flag.button_bizhang_Start = 1;
//	}			
	if(g_shoudong_start == 1)				//短触发 -- 触摸屏启动按键 1有效
	{		
		g_Start_flag.Start_button_Car = 1;
	}		
	if(g_Senser_InPut.button_Start==1 && g_Senser_InPut.button_Stop==0)	
	{
		g_Start_flag.Start_button_Car = 1;	//短触发--车辆面板启动按键
		if(!g_AGV_Sta.Car_Auto2Manu_mode)
		{
			if(!g_start_button_down)
			{
				speek("启动");	
				g_start_button_down = 1;	
			}		
		}


		
	}
	if(g_Start_flag.Start_AGV_SysCode)		//长触发--程序调用这个变量来启动停止 //1启动
	{
		g_Start_flag.Start_AGV_SysCode = 0;
		g_Start_flag.Start_button_Car = 1;
	}	
	
	
	
	if(g_Start_flag.Start_IR)				//长触发--程序调用这个变量来启动停止 //1启动
	{
		g_Start_flag.button_bizhang_Start = 1;
	}	

	if(g_Start_flag.Start_jixie)			//长触发--程序调用这个变量来启动停止 //1启动
	{
		g_Start_flag.button_bizhang_Start = 1;
	}	

//////////////////////////////////////////////////////////////////

//	if(预留2 == 1)							//上位机停止信号
//	{
//		g_Start_flag.button_bizhang_Start = 0;
//	}			
	if(g_shoudong_stop == 1)				//短触发--触摸屏停止按键 1有效
	{
		g_Start_flag.Stop_button_Car = 1;
	}			
	if(g_Senser_InPut.button_Stop==1)			//短触发--车辆面板停止按键 -- 系统程序中停车也用这个变量停
	{
		g_Start_flag.Stop_button_Car = 1;
		if(!g_stop_button_down)
		{
			speek("停止");	
			g_stop_button_down = 1;	
		}
	
	}	
	if(g_Start_flag.Stop_AGV_SysCode)		//长触发--程序调用这个变量来启动停止 //1启动
	{
		g_Start_flag.Stop_AGV_SysCode = 0;
		g_Start_flag.Stop_button_Car = 1;
	}			

	
	
	if(!g_Start_flag.Start_IR)				//长触发--//程序调用这个变量来启动停止 //1启动
	{
		g_Start_flag.button_bizhang_Start = 0;

	}		

	
	if(!g_Start_flag.Start_jixie)			//长触发--程序调用这个变量来启动停止 //1启动
	{
		g_Start_flag.button_bizhang_Start = 0;

	}	
	

	

	if(!g_AGV_Sta.Car_Auto2Manu_mode)	//0:自动
	{
		//AGV磁条寻正
		if(g_Start_flag.Start_button_Car==1 && g_Start_flag.button_bizhang_Start==1)	
		{
			if(!g_Start_flag.Start_Auto_PID)			//自动模式未运行		-- 这块要修改?
			{
				if(!g_CtXunZheng.XunZ_Start)	//磁条寻正未进行
				{
					//自动模式--磁导航寻正
					g_CtXunZheng.XunZ_Start = 1;					
				}							
			}
			g_Start_flag.Start_button_Car = 0;			//清除自动启动标志
			g_Start_flag.Stop_button_Car = 0;			
		}
		//AGV启动后
		if(g_Start_flag.Stop_button_Car==0 && g_Start_flag.button_bizhang_Start==1)				//避障未触发
		{
			if(g_glag_bizhang == 1)
			{				
				if(!g_CtXunZheng.XunZ_Start)	//磁条寻正未进行
				{
					//自动模式--磁导航寻正
					g_CtXunZheng.XunZ_Start = 1;					
				}				
				g_glag_bizhang = 0;					
			}
		}
		//AGV停止
		if(g_Start_flag.Stop_button_Car==1 || g_Start_flag.button_bizhang_Start==0)		
		{
			if(g_Start_flag.button_bizhang_Start==0)		//避障停止
			{	
				g_glag_bizhang = 1;
			}
			
			if(g_Start_flag.Start_Auto_PID)	//正在自动行走才能进来
			{
				Ruan_Stop(&AGV_SYS.Car_Auto_Speed);			
			}

		}
	}	
	else				//1:手动
	{
		if(g_Start_flag.Stop_button_Car==1 || g_Start_flag.button_bizhang_Start==0)	//避障传感器触发 0:触发	
		{
			g_Start_flag.Stop_button_Car = 0;
			g_Start_flag.Start_Manu_PID	 = 0;				//给键停止标志

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
	0, 		//u8 Start_AGV_SysCode;		//系统程序调用
	0, 		//u8 Start_IR;				//系统程序调用
	0,		//u8 Start_jixie;			//系统程序调用
	0,		//u8 button_Start;		
	0, 		//u8 Start_Auto_PID;		//底层PID函数的开关--自动
	0,   	//u8 Start_Manu_PID;		//底层PID函数的开关--手动
	0,
	0,
	1
};     
       















