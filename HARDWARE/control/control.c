#include "control.h" 

Fencha_struct g_CDH8_qian_1;
Fencha_struct g_CDH8_qian_2;
Fencha_struct g_CDH8_hou_1;
Fencha_struct g_CDH8_hou_2;


float Cdh1_Inc;
float Cdh2_Inc;
float Cdh3_Inc;
float Cdh4_Inc;

PIDspeed PID_speed;
u16 CT_chugui_delay = 1;			//空点检测10ms
int  g_fencha_yiwei_val = 0;		//磁导航分叉移位值
//磁导航PID调节
void PID_AUTO_QianLun(u16 j_speed,float kp,float ki,float kd)
{
	u8 num = 0;
//	PID.Kp = j_speed * kp /1000;	//动态PID
//	PID.Ki = j_speed * ki /1000;	//动态PID
	PID.Kp =  kp ;	//动态PID
	PID.Ki =  ki ;	//动态PID
	PID.Kd = kd; 
	
	PID.SetTarget = g_fencha_yiwei_val;		//PID目标值
	
	if(g_AGV_Sta.Car_dir == 0)						//前进
	{
		while( g_CDH8_qian_1.Num==0 && num<CT_chugui_delay )//空点检测10ms
		{
			num++;
			delay_rtos(0,0,0,10);
		}			
		if(g_CDH8_qian_1.Num==0)					//磁条出轨					
		{
			//停止
			Ting_Zhi();		
			g_Warning.chugui = 1;					//出轨标志置一
			//加一次寻轨
			if(!check_CDH_chugui(1))							//前1磁导航 0:左出轨 1:右出轨
			{
				speek("前1左");
				delay_rtos(0,0,0,500);
				
				CtXunZheng_qian(1,1,AGV_SYS.XZ_CiTiao_Speed);	//左出轨右寻正
			}
			else
			{
				speek("前1右");
				delay_rtos(0,0,0,500);
				
				CtXunZheng_qian(1,0,AGV_SYS.XZ_CiTiao_Speed);	//右出轨左寻正	
			}
			if(!g_CtXunZheng.XunZ_OK_qian_1)	//出轨寻正未OK	//未检出到磁条停止
			{
				Ting_Zhi();										//停止
				HmiTaskState = 6;								//触摸屏显示车辆停止
				speek("前1");
				delay_rtos(0,0,0,500);					
			}
			else								//出轨寻正OK								
			{
				g_Warning.chugui = 0;			//出轨标志清零
				if(g_CtXunZheng.XunZ_OK_hou_1)	//后1也寻到轨
				{
					HmiTaskState = 5;								//正在运行

					if(!g_CDH8_qian_1.Error)		//未出错进入
					{
						Cdh1_Inc = IncPIDCalc(g_CDH8_qian_1.Distance);	//1 位置式PID//输入差值										
					}
					PID_speed.moter1_speed = j_speed+Cdh1_Inc;
					PID_speed.moter2_speed = j_speed-Cdh1_Inc;
					
					if(PID_speed.moter1_speed>j_speed)	PID_speed.moter1_speed = j_speed;
					if(PID_speed.moter2_speed>j_speed)	PID_speed.moter2_speed = j_speed;

					if(PID_speed.moter1_speed<0)	PID_speed.moter1_speed = 0;
					if(PID_speed.moter2_speed<0)	PID_speed.moter2_speed = 0;

					LunZi_Go(1,PID_speed.moter1_speed);LunZi_Go(2,PID_speed.moter2_speed);							
				}
				else							//另一个轮子未上轨--后1未上轨
				{
					delay_rtos(0,0,0,10);		
				}
				
			}			
		}
		else												//检测到磁条
		{
			g_Warning.chugui = 0;			//出轨标志清零
			HmiTaskState = 5;								//正在运行
			if(!g_CDH8_qian_1.Error)		//未出错进入
			{
				Cdh1_Inc = IncPIDCalc(g_CDH8_qian_1.Distance);	//1 位置式PID//输入差值											
			}
			PID_speed.moter1_speed = j_speed+Cdh1_Inc;
			PID_speed.moter2_speed = j_speed-Cdh1_Inc;
			
			if(PID_speed.moter1_speed>j_speed)	PID_speed.moter1_speed = j_speed;
			if(PID_speed.moter2_speed>j_speed)	PID_speed.moter2_speed = j_speed;

			if(PID_speed.moter1_speed<0)	PID_speed.moter1_speed = 0;
			if(PID_speed.moter2_speed<0)	PID_speed.moter2_speed = 0;

			LunZi_Go(1,PID_speed.moter1_speed);LunZi_Go(2,PID_speed.moter2_speed);			
		}
	}
	else if(g_AGV_Sta.Car_dir == 1)					//后退
	{		
		while(g_CDH8_qian_2.Num==0 && num<CT_chugui_delay)		//空点检测
		{
			num++;
			delay_rtos(0,0,0,10);
		}
		if(g_CDH8_qian_2.Num==0) 
		{	
			//停止
			Ting_Zhi();	
			g_Warning.chugui = 1;			//出轨标志置一			
			//加一次寻轨
			if(!check_CDH_chugui(2))							//前1磁导航 0:左出轨 1:右出轨
			{
				speek("前2左");
				delay_rtos(0,0,0,500);
				CtXunZheng_qian(2,1,AGV_SYS.XZ_CiTiao_Speed);	//左出轨右寻正
			}
			else
			{	
				speek("前2右");
				delay_rtos(0,0,0,500);
				
				CtXunZheng_qian(2,0,AGV_SYS.XZ_CiTiao_Speed);	//右出轨左寻正	
			}			
			
			if(!g_CtXunZheng.XunZ_OK_qian_2)	//出轨寻正未OK	//未检出到磁条停止
			{
				Ting_Zhi();					//停止
				HmiTaskState = 6;					//无磁条停止
				speek("前2");
				delay_rtos(0,0,0,500);			
			}
			else								//出轨寻正OK								
			{
				g_Warning.chugui = 0;			//出轨标志清零
				if(g_CtXunZheng.XunZ_OK_hou_2)	//后2也寻到轨
				{
					HmiTaskState = 5;					//正在运行
					if(!g_CDH8_qian_2.Error)
					{
						Cdh2_Inc = IncPIDCalc(g_CDH8_qian_2.Distance);//2 位置式PID//输入差值				
					}
					PID_speed.moter2_speed = j_speed-Cdh2_Inc;	
					PID_speed.moter1_speed = j_speed+Cdh2_Inc;
									
					
					if(PID_speed.moter1_speed>j_speed)	PID_speed.moter1_speed = j_speed;
					if(PID_speed.moter2_speed>j_speed)	PID_speed.moter2_speed = j_speed;

					if(PID_speed.moter1_speed<0)	PID_speed.moter1_speed = 0;
					if(PID_speed.moter2_speed<0)	PID_speed.moter2_speed = 0;

					LunZi_Back(2,PID_speed.moter2_speed);LunZi_Back(1,PID_speed.moter1_speed);			
				
				}
				else							//另一个轮子未上轨--后2未上轨
				{
					delay_rtos(0,0,0,10);		
				}
			}						
		}
		else
		{
			g_Warning.chugui = 0;			//出轨标志清零
			HmiTaskState = 5;					//正在运行
			if(!g_CDH8_qian_2.Error)
			{
				Cdh2_Inc = IncPIDCalc(g_CDH8_qian_2.Distance);//2 位置式PID//输入差值				
			}
			PID_speed.moter2_speed = j_speed-Cdh2_Inc;	
			PID_speed.moter1_speed = j_speed+Cdh2_Inc;
							
			
			if(PID_speed.moter1_speed>j_speed)	PID_speed.moter1_speed = j_speed;
			if(PID_speed.moter2_speed>j_speed)	PID_speed.moter2_speed = j_speed;

			if(PID_speed.moter1_speed<0)	PID_speed.moter1_speed = 0;
			if(PID_speed.moter2_speed<0)	PID_speed.moter2_speed = 0;

			LunZi_Back(2,PID_speed.moter2_speed);LunZi_Back(1,PID_speed.moter1_speed);
		
		}
	}
}

void PID_AUTO_HouLun(u16 j_speed2,float kp2,float ki2,float kd2)	//后轮的PID调节
{
	u8 num2 = 0;
//	PID2.Kp = j_speed2 * kp2 /1000;		//动态PID
//	PID2.Ki = j_speed2 * ki2 /1000;
	PID2.Kp =  kp2 ;		//动态PID
	PID2.Ki =  ki2;	
	PID2.Kd = kd2; 

	
	PID2.SetTarget = g_fencha_yiwei_val;//PID2目标值	
	
	if(g_AGV_Sta.Car_dir == 0)	//前进
	{
		while( g_CDH8_hou_1.Num==0 && num2<CT_chugui_delay )				//空点检测
		{
			num2++;
			delay_rtos(0,0,0,10);
		}			
		if(g_CDH8_hou_1.Num==0 )								//未检出到磁条停止
		{
			//停止
			Ting_Zhi();
			g_Warning.chugui = 1;			//出轨标志
			//加一次寻轨
			if(!check_CDH_chugui(3))							//前1磁导航 0:左出轨 1:右出轨
			{
				speek("后1左");
				delay_rtos(0,0,0,500);
				
				CtXunZheng_hou(3,1,AGV_SYS.XZ_CiTiao_Speed);	//左出轨右寻正
			}
			else
			{	
				speek("后1右");
				delay_rtos(0,0,0,50);
				
				CtXunZheng_hou(3,0,AGV_SYS.XZ_CiTiao_Speed);	//右出轨左寻正	
			}
			if(!g_CtXunZheng.XunZ_OK_hou_1)	//出轨寻正未OK	//未检出到磁条停止
			{
				Ting_Zhi();							//停止
				HmiTaskState = 6;								//触摸屏显示车辆停止
				speek("后1");
				delay_rtos(0,0,0,500);				
			}
			else								//出轨寻正OK								
			{
				g_Warning.chugui = 0;			//出轨标志清零
				if(g_CtXunZheng.XunZ_OK_qian_1)	//前1也寻到轨
				{
					HmiTaskState = 5;								//正在运行
					if(!g_CDH8_hou_1.Error)
					{
						Cdh3_Inc = IncPIDCalc2(g_CDH8_hou_1.Distance);	//1 位置式PID//输入差值								
					}			
					PID_speed.moter3_speed = j_speed2+Cdh3_Inc;
					PID_speed.moter4_speed = j_speed2-Cdh3_Inc;
					
					if(PID_speed.moter3_speed>j_speed2)	PID_speed.moter3_speed = j_speed2;
					if(PID_speed.moter4_speed>j_speed2)	PID_speed.moter4_speed = j_speed2;

					if(PID_speed.moter3_speed<0)	PID_speed.moter3_speed = 0;
					if(PID_speed.moter4_speed<0)	PID_speed.moter4_speed = 0;

					LunZi_Go(3,PID_speed.moter3_speed);LunZi_Go(4,PID_speed.moter4_speed);								
				}
				else							//另一个轮子未上轨--前1未上轨
				{
					delay_rtos(0,0,0,10);		
				}
			}			
		}
		else
		{
			g_Warning.chugui = 0;			//出轨标志清零
			HmiTaskState = 5;								//正在运行
			if(!g_CDH8_hou_1.Error)
			{
				Cdh3_Inc = IncPIDCalc2(g_CDH8_hou_1.Distance);	//1 位置式PID//输入差值								
			}			
			PID_speed.moter3_speed = j_speed2+Cdh3_Inc;
			PID_speed.moter4_speed = j_speed2-Cdh3_Inc;
			
			if(PID_speed.moter3_speed>j_speed2)	PID_speed.moter3_speed = j_speed2;
			if(PID_speed.moter4_speed>j_speed2)	PID_speed.moter4_speed = j_speed2;

			if(PID_speed.moter3_speed<0)	PID_speed.moter3_speed = 0;
			if(PID_speed.moter4_speed<0)	PID_speed.moter4_speed = 0;

			LunZi_Go(3,PID_speed.moter3_speed);LunZi_Go(4,PID_speed.moter4_speed);	
		}
	}
	else if(g_AGV_Sta.Car_dir == 1)					//后退
	{
				
		while(g_CDH8_hou_2.Num==0 && num2<CT_chugui_delay)		//空点检测0.5秒
		{
			num2++;
			delay_rtos(0,0,0,10);
		}
		if(g_CDH8_hou_2.Num==0 )
		{
			//停止
			Ting_Zhi();		
			g_Warning.chugui = 1;			//出轨标志			
			//加一次寻轨
			if(!check_CDH_chugui(4))							//前1磁导航 0:左出轨 1:右出轨
			{
				speek("后2左");
				delay_rtos(0,0,0,500);
				
				CtXunZheng_hou(4,1,AGV_SYS.XZ_CiTiao_Speed);	//左出轨右寻正
			}
			else
			{	
				speek("后2右");
				delay_rtos(0,0,0,500);
				
				CtXunZheng_hou(4,0,AGV_SYS.XZ_CiTiao_Speed);	//右出轨左寻正	
			}			
			
			if(!g_CtXunZheng.XunZ_OK_hou_2)	//出轨寻正未OK	//未检出到磁条停止
			{
				Ting_Zhi();
				HmiTaskState = 6;					//无磁条停止
				speek("后2");
				delay_rtos(0,0,0,500);		
			}
			else								//出轨寻正OK								
			{
				g_Warning.chugui = 0;			//出轨标志清零
				if(g_CtXunZheng.XunZ_OK_qian_2)	//前2寻到轨
				{
					HmiTaskState = 5;					//正在运行
					if(!g_CDH8_hou_2.Error)
					{
						Cdh4_Inc = IncPIDCalc2(g_CDH8_hou_2.Distance);//2 位置式PID//输入差值
					}
					PID_speed.moter4_speed = j_speed2-Cdh4_Inc;	
					PID_speed.moter3_speed = j_speed2+Cdh4_Inc;
									
					
					if(PID_speed.moter4_speed>j_speed2)	PID_speed.moter4_speed = j_speed2;
					if(PID_speed.moter3_speed>j_speed2)	PID_speed.moter3_speed = j_speed2;

					if(PID_speed.moter4_speed<0)	PID_speed.moter4_speed = 0;
					if(PID_speed.moter3_speed<0)	PID_speed.moter3_speed = 0;
			
					LunZi_Back(4,PID_speed.moter4_speed);LunZi_Back(3,PID_speed.moter3_speed);			
				}
				else							//另一个轮子未上轨--前2未上轨
				{
					delay_rtos(0,0,0,10);		
				}				
			}			
		}
		else
		{
			g_Warning.chugui = 0;			//出轨标志清零
			HmiTaskState = 5;					//正在运行
			if(!g_CDH8_hou_2.Error)
			{
				Cdh4_Inc = IncPIDCalc2(g_CDH8_hou_2.Distance);//2 位置式PID//输入差值
			}
			PID_speed.moter4_speed = j_speed2-Cdh4_Inc;	
			PID_speed.moter3_speed = j_speed2+Cdh4_Inc;
							
			
			if(PID_speed.moter4_speed>j_speed2)	PID_speed.moter4_speed = j_speed2;
			if(PID_speed.moter3_speed>j_speed2)	PID_speed.moter3_speed = j_speed2;

			if(PID_speed.moter4_speed<0)	PID_speed.moter4_speed = 0;
			if(PID_speed.moter3_speed<0)	PID_speed.moter3_speed = 0;
	
			LunZi_Back(4,PID_speed.moter4_speed);LunZi_Back(3,PID_speed.moter3_speed);			
		}
	}
}


int DWQ1_Inc;
int DWQ2_Inc;
int DWQ3_Inc;
int DWQ4_Inc;

PIDspeed PID__SD_speed;
u8 g_Trun_Val = 10;			//手动转向角度
void PID_SD_Adjust(u16 j_speed,float kp,u16 ki,float kd)
{
	PID2.Kp = PID.Kp = j_speed * kp /1000;			//动态PID
	PID2.Ki = PID.Ki = j_speed * ki /1000; 
	PID2.Kd = PID.Kd = kd; 
	
	HmiTaskState = 5;								//正在运行 -- 手动

	switch(g_AGV_yaokong.SD_ir)	//设定目标值
	{
		case 1:					//前进
			PID.SetTarget  = g_DWQ.qianlun_zhong_val + g_AGV_yaokong.jiaodu;		//PID目标值--前_驱动轮电位器中值 
			PID2.SetTarget = g_DWQ.houlun_zhong_val;		//PID目标值--后_驱动轮电位器中值 						
			break;	
		
		case 2:					//后退
			PID2.SetTarget = g_DWQ.houlun_zhong_val + g_AGV_yaokong.jiaodu;		//PID目标值--后_驱动轮电位器中值 	
			PID.SetTarget  = g_DWQ.qianlun_zhong_val;		//PID目标值--前_驱动轮电位器中值 
				break;	
				
		default:
			break;
	}	
	
	switch(g_AGV_yaokong.SD_ir)	//实际控制电机的速度			
	{
		case 1:					//前进

			DWQ1_Inc = IncPIDCalc(g_After_filter[1]);		//1 位置式PID//输入差值	 0-4096				
			PID__SD_speed.moter1_speed = j_speed+DWQ1_Inc;
			PID__SD_speed.moter2_speed = j_speed-DWQ1_Inc;
			
			DWQ2_Inc = IncPIDCalc2(g_After_filter[2]);		//2 位置式PID//输入差值						
			PID__SD_speed.moter3_speed = j_speed+DWQ2_Inc;
			PID__SD_speed.moter4_speed = j_speed-DWQ2_Inc;
			break;
		
		case 2:					//后退

			DWQ2_Inc = IncPIDCalc2(g_After_filter[2]);		//1 位置式PID//输入差值	 0-4096				
			PID__SD_speed.moter4_speed = j_speed+DWQ2_Inc;
			PID__SD_speed.moter3_speed = j_speed-DWQ2_Inc;
			
			DWQ1_Inc = IncPIDCalc(g_After_filter[1]);		//2 位置式PID//输入差值						
			PID__SD_speed.moter2_speed = j_speed+DWQ1_Inc;
			PID__SD_speed.moter1_speed = j_speed-DWQ1_Inc;
			break;			
		
		default:
			break;

	}

	if(PID__SD_speed.moter1_speed > 300*AGV_SYS.SD_Speed_bili)	PID__SD_speed.moter1_speed = 300*AGV_SYS.SD_Speed_bili;
	if(PID__SD_speed.moter2_speed > 300*AGV_SYS.SD_Speed_bili)	PID__SD_speed.moter2_speed = 300*AGV_SYS.SD_Speed_bili;
	if(PID__SD_speed.moter3_speed > 300*AGV_SYS.SD_Speed_bili)	PID__SD_speed.moter3_speed = 300*AGV_SYS.SD_Speed_bili;
	if(PID__SD_speed.moter4_speed > 300*AGV_SYS.SD_Speed_bili)	PID__SD_speed.moter4_speed = 300*AGV_SYS.SD_Speed_bili;


	if(PID__SD_speed.moter1_speed<0)	PID__SD_speed.moter1_speed = 0;
	if(PID__SD_speed.moter2_speed<0)	PID__SD_speed.moter2_speed = 0;
	if(PID__SD_speed.moter3_speed<0)	PID__SD_speed.moter3_speed = 0;
	if(PID__SD_speed.moter4_speed<0)	PID__SD_speed.moter4_speed = 0;


	switch(g_AGV_yaokong.SD_ir)	//实际控制电机的速度			
	{
		case 1:					//前进
			LunZi_Go(1,PID__SD_speed.moter1_speed);LunZi_Go(2,PID__SD_speed.moter2_speed);
			
			LunZi_Go(3,PID__SD_speed.moter3_speed);LunZi_Go(4,PID__SD_speed.moter4_speed);
		break;
		
		case 2:					//后退
			LunZi_Back(4,PID__SD_speed.moter4_speed);LunZi_Back(3,PID__SD_speed.moter3_speed);		
			LunZi_Back(2,PID__SD_speed.moter2_speed);LunZi_Back(1,PID__SD_speed.moter1_speed);			
			break;			
		
		default:
			break;
	}

}

u8 check_CDH_chugui(u8 ID)		//返回0:左出轨 1:右出轨
{
	u8 temp_s=0;
	
	if(!g_AGV_Sta.Car_dir)		//前进方向
	{
		if(g_Ct_chugui[ID] > 0)
		{
			temp_s = 1;				//从右边出轨
		}
		else if(g_Ct_chugui[ID] < 0)
		{
			temp_s = 0;				//从左边出轨
		}		
	}
	else						//后退方向
	{
		if(g_Ct_chugui[ID] > 0)
		{
			temp_s = 0;				//从左边出轨
		}
		else if(g_Ct_chugui[ID] < 0)
		{
			temp_s = 1;				//从右边出轨			
		}	
	}


	return temp_s;

}










//上层的行走方向控制函数开始
void Zi_Dong(void)						//切到自动程序
{
//	if(g_AGV_Sta.Car_Auto2Manu_mode)	//从手动切换回来时先停止
//	{
//		Ting_Zhi();
//	}
	g_Start_flag.Start_button_Car = 0;
	g_Start_flag.Stop_button_Car  = 1;
	
	g_AGV_Sta.Car_Auto2Manu_mode = 0;

	g_AGV_speaker_flag.Auto = 1;
	delay_rtos(0,0,0,g_Speaker_delay);
	
}
void Shou_Dong(void)
{
	*g_dispatch_message.RunState = 0;					//切换到非就绪模式
	if(!g_AGV_Sta.Car_Auto2Manu_mode)	//从自动切换过来时先停止
	{
		Ting_Zhi();
	}
	g_AGV_speaker_flag.Manu = 1;
	delay_rtos(0,0,0,g_Speaker_delay);
	g_AGV_Sta.Car_Auto2Manu_mode = 1;

}
void Qian_Jin(void)
{
	g_AGV_Sta.Car_dir = 0;

	g_AGV_speaker_flag.dir_Go = 1;
	delay_rtos(0,0,0,g_Speaker_delay);
}
void Hou_Tui(void)
{
	g_AGV_Sta.Car_dir = 1;

	g_AGV_speaker_flag.dir_Back = 1;
	delay_rtos(0,0,0,g_Speaker_delay);
}

void Ting_Zhi(void)				
{
	AGV_System_Stop();
	g_AGV_speaker_flag.stop = 1;
	delay_rtos(0,0,0,g_Speaker_delay);
	HmiTaskState = 4;					//停止	
	delay_rtos(0,0,0,500);	
}
void Qi_Dong(void)
{
	AGV_System_Start();
	
	HmiTaskState = 5;				//正在运行
	g_AGV_speaker_flag.start = 1;		//自动模式下:启动的语音播报
	delay_rtos(0,0,0,g_Speaker_delay);

}
void Zuo_Fen(void)
{
	if(!g_AGV_Sta.Car_dir)						//前进
	{
		g_AGV_Sta.Car_fencha_dir = 1;			
	}
	else										//后退
	{
		g_AGV_Sta.Car_fencha_dir = 2;			//分叉标志		
	}
//	g_AGV_Sta.Car_fencha_dir = 1;
	g_AGV_speaker_flag.FenCha_L = 1;		
	delay_rtos(0,0,0,g_Speaker_delay);
}

void You_Fen(void)
{
	if(!g_AGV_Sta.Car_dir)						//前进
	{
		g_AGV_Sta.Car_fencha_dir = 2;			
	}
	else										//后退
	{
		g_AGV_Sta.Car_fencha_dir = 1;			//分叉标志		
	}
	
//	g_AGV_Sta.Car_fencha_dir = 2;			//分叉标志
	g_AGV_speaker_flag.FenCha_R = 1;		
	delay_rtos(0,0,0,g_Speaker_delay);
}
void ZhiXing(void)							//直行
{
//	if(g_AGV_Sta.Car_dir)						//后退
//	{
//		g_AGV_Sta.Car_fencha_dir = 1;			//分叉标志
//	}
//	else										//前进
//	{
//		g_AGV_Sta.Car_fencha_dir = 1;			//分叉标志
//	}	
}


void SD_Trun_L(void)
{
											//车左转向
	delay_rtos(0,0,0,g_Speaker_delay);
}

void SD_Trun_R(void)
{
											//车右转向
	
	delay_rtos(0,0,0,g_Speaker_delay);
}



void Ruan_Qi_jia(u16 speed_min1,u16 speed_max,u16 * speed_zhi)
{	
	u16 temp_cha=0;
	u16 temp_cha2=0;
	u8 temp_i=0;
	u16 temp_chu=0;
	u16 temp_val=0;
	
	HmiTaskState = 5;	
	temp_cha = abs(speed_max-speed_min1);	//800-0
	
	if(temp_cha <= 600)
	{
		temp_chu = 5;
	}
	else
	{
		temp_chu = 10;
	}
	if(speed_max > speed_min1)
	{
		temp_cha2 = temp_cha/temp_chu;
		for(temp_i=0;temp_i<temp_chu;temp_i++)
		{
			temp_val += temp_cha2;
			if(speed_min1+temp_val > speed_max)
			{
				*speed_zhi = speed_max;
				break;
			}	
			else
			{
				*speed_zhi = speed_min1+temp_val;
			}		
			
			delay_rtos(0,0,0,125);			//2.5秒加速
		}		
	}
	else
	{
		*speed_zhi = speed_max;
	}	
}

void Ruan_jian(u16 speed_max1,u16 speed_min,u16 * speed_TrueVal)	//软减速
{	
	u16 temp_cha=0;
	u16 temp_cha2=0;
	u8 temp_i=0;
	u8 temp_chu=0;
	u16 temp_val=0;
		
	temp_cha = abs(speed_max1-speed_min);	//eg:800-400
	
	if(temp_cha <= 800)
	{
		temp_chu = 5;		//500ms减速
	}
	else
	{
		temp_chu = 10;		//1000ms减速
	}
	if(speed_max1 > speed_min)
	{
		temp_cha2 = temp_cha/temp_chu;
		for(temp_i=0;temp_i<temp_chu;temp_i++)
		{
			temp_val += temp_cha2;
			if((speed_max1 - temp_val) < speed_min) //200 -- 500
			{
				*speed_TrueVal = speed_min;
				break;
			}	
			else
			{
				*speed_TrueVal = speed_max1 - temp_val;
			}
					
			delay_rtos(0,0,0,125);			
		}		
	}
	else
	{
		*speed_TrueVal = speed_min;
	}	
}

void Ruan_Stop(u16 * speed_TrueVal)	//软减速
{	
	u16 temp_cha=0;
	u16 temp_cha2=0;
	u8 temp_i=0;
	u16 temp_val=0;
	u16 speed_max1=0;
	
	speed_max1 = * speed_TrueVal;

	if(speed_max1>100&&speed_max1 < 600)	//这个范围motec不给软停,自己做软停
	{
		temp_cha = speed_max1/100;	//eg:800-400
		temp_cha2 = 100;
		for(temp_i=0;temp_i<temp_cha;temp_i++)
		{
			temp_val += temp_cha2;
			if((speed_max1 - temp_val) < 100) //200 -- 500
			{
				g_Start_flag.Start_Auto_PID = 0;	
				MotoStop(0);			
				*speed_TrueVal = speed_max1;
				break;
			}	
			else
			{
				*speed_TrueVal = speed_max1 - temp_val;
			}
					
			delay_rtos(0,0,0,125);			
		}		
	}
	else					//大于600,motec驱动自己软停
	{
		g_Start_flag.Start_Auto_PID = 0;	
		MotoStop(0);
	}
		
	
	


		
	
	
}

