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
u16 CT_chugui_delay = 1;			//�յ���10ms
int  g_fencha_yiwei_val = 0;		//�ŵ����ֲ���λֵ
//�ŵ���PID����
void PID_AUTO_QianLun(u16 j_speed,float kp,float ki,float kd)
{
	u8 num = 0;
//	PID.Kp = j_speed * kp /1000;	//��̬PID
//	PID.Ki = j_speed * ki /1000;	//��̬PID
	PID.Kp =  kp ;	//��̬PID
	PID.Ki =  ki ;	//��̬PID
	PID.Kd = kd; 
	
	PID.SetTarget = g_fencha_yiwei_val;		//PIDĿ��ֵ
	
	if(g_AGV_Sta.Car_dir == 0)						//ǰ��
	{
		while( g_CDH8_qian_1.Num==0 && num<CT_chugui_delay )//�յ���10ms
		{
			num++;
			delay_rtos(0,0,0,10);
		}			
		if(g_CDH8_qian_1.Num==0)					//��������					
		{
			//ֹͣ
			Ting_Zhi();		
			g_Warning.chugui = 1;					//�����־��һ
			//��һ��Ѱ��
			if(!check_CDH_chugui(1))							//ǰ1�ŵ��� 0:����� 1:�ҳ���
			{
				speek("ǰ1��");
				delay_rtos(0,0,0,500);
				
				CtXunZheng_qian(1,1,AGV_SYS.XZ_CiTiao_Speed);	//�������Ѱ��
			}
			else
			{
				speek("ǰ1��");
				delay_rtos(0,0,0,500);
				
				CtXunZheng_qian(1,0,AGV_SYS.XZ_CiTiao_Speed);	//�ҳ�����Ѱ��	
			}
			if(!g_CtXunZheng.XunZ_OK_qian_1)	//����Ѱ��δOK	//δ���������ֹͣ
			{
				Ting_Zhi();										//ֹͣ
				HmiTaskState = 6;								//��������ʾ����ֹͣ
				speek("ǰ1");
				delay_rtos(0,0,0,500);					
			}
			else								//����Ѱ��OK								
			{
				g_Warning.chugui = 0;			//�����־����
				if(g_CtXunZheng.XunZ_OK_hou_1)	//��1ҲѰ����
				{
					HmiTaskState = 5;								//��������

					if(!g_CDH8_qian_1.Error)		//δ�������
					{
						Cdh1_Inc = IncPIDCalc(g_CDH8_qian_1.Distance);	//1 λ��ʽPID//�����ֵ										
					}
					PID_speed.moter1_speed = j_speed+Cdh1_Inc;
					PID_speed.moter2_speed = j_speed-Cdh1_Inc;
					
					if(PID_speed.moter1_speed>j_speed)	PID_speed.moter1_speed = j_speed;
					if(PID_speed.moter2_speed>j_speed)	PID_speed.moter2_speed = j_speed;

					if(PID_speed.moter1_speed<0)	PID_speed.moter1_speed = 0;
					if(PID_speed.moter2_speed<0)	PID_speed.moter2_speed = 0;

					LunZi_Go(1,PID_speed.moter1_speed);LunZi_Go(2,PID_speed.moter2_speed);							
				}
				else							//��һ������δ�Ϲ�--��1δ�Ϲ�
				{
					delay_rtos(0,0,0,10);		
				}
				
			}			
		}
		else												//��⵽����
		{
			g_Warning.chugui = 0;			//�����־����
			HmiTaskState = 5;								//��������
			if(!g_CDH8_qian_1.Error)		//δ�������
			{
				Cdh1_Inc = IncPIDCalc(g_CDH8_qian_1.Distance);	//1 λ��ʽPID//�����ֵ											
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
	else if(g_AGV_Sta.Car_dir == 1)					//����
	{		
		while(g_CDH8_qian_2.Num==0 && num<CT_chugui_delay)		//�յ���
		{
			num++;
			delay_rtos(0,0,0,10);
		}
		if(g_CDH8_qian_2.Num==0) 
		{	
			//ֹͣ
			Ting_Zhi();	
			g_Warning.chugui = 1;			//�����־��һ			
			//��һ��Ѱ��
			if(!check_CDH_chugui(2))							//ǰ1�ŵ��� 0:����� 1:�ҳ���
			{
				speek("ǰ2��");
				delay_rtos(0,0,0,500);
				CtXunZheng_qian(2,1,AGV_SYS.XZ_CiTiao_Speed);	//�������Ѱ��
			}
			else
			{	
				speek("ǰ2��");
				delay_rtos(0,0,0,500);
				
				CtXunZheng_qian(2,0,AGV_SYS.XZ_CiTiao_Speed);	//�ҳ�����Ѱ��	
			}			
			
			if(!g_CtXunZheng.XunZ_OK_qian_2)	//����Ѱ��δOK	//δ���������ֹͣ
			{
				Ting_Zhi();					//ֹͣ
				HmiTaskState = 6;					//�޴���ֹͣ
				speek("ǰ2");
				delay_rtos(0,0,0,500);			
			}
			else								//����Ѱ��OK								
			{
				g_Warning.chugui = 0;			//�����־����
				if(g_CtXunZheng.XunZ_OK_hou_2)	//��2ҲѰ����
				{
					HmiTaskState = 5;					//��������
					if(!g_CDH8_qian_2.Error)
					{
						Cdh2_Inc = IncPIDCalc(g_CDH8_qian_2.Distance);//2 λ��ʽPID//�����ֵ				
					}
					PID_speed.moter2_speed = j_speed-Cdh2_Inc;	
					PID_speed.moter1_speed = j_speed+Cdh2_Inc;
									
					
					if(PID_speed.moter1_speed>j_speed)	PID_speed.moter1_speed = j_speed;
					if(PID_speed.moter2_speed>j_speed)	PID_speed.moter2_speed = j_speed;

					if(PID_speed.moter1_speed<0)	PID_speed.moter1_speed = 0;
					if(PID_speed.moter2_speed<0)	PID_speed.moter2_speed = 0;

					LunZi_Back(2,PID_speed.moter2_speed);LunZi_Back(1,PID_speed.moter1_speed);			
				
				}
				else							//��һ������δ�Ϲ�--��2δ�Ϲ�
				{
					delay_rtos(0,0,0,10);		
				}
			}						
		}
		else
		{
			g_Warning.chugui = 0;			//�����־����
			HmiTaskState = 5;					//��������
			if(!g_CDH8_qian_2.Error)
			{
				Cdh2_Inc = IncPIDCalc(g_CDH8_qian_2.Distance);//2 λ��ʽPID//�����ֵ				
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

void PID_AUTO_HouLun(u16 j_speed2,float kp2,float ki2,float kd2)	//���ֵ�PID����
{
	u8 num2 = 0;
//	PID2.Kp = j_speed2 * kp2 /1000;		//��̬PID
//	PID2.Ki = j_speed2 * ki2 /1000;
	PID2.Kp =  kp2 ;		//��̬PID
	PID2.Ki =  ki2;	
	PID2.Kd = kd2; 

	
	PID2.SetTarget = g_fencha_yiwei_val;//PID2Ŀ��ֵ	
	
	if(g_AGV_Sta.Car_dir == 0)	//ǰ��
	{
		while( g_CDH8_hou_1.Num==0 && num2<CT_chugui_delay )				//�յ���
		{
			num2++;
			delay_rtos(0,0,0,10);
		}			
		if(g_CDH8_hou_1.Num==0 )								//δ���������ֹͣ
		{
			//ֹͣ
			Ting_Zhi();
			g_Warning.chugui = 1;			//�����־
			//��һ��Ѱ��
			if(!check_CDH_chugui(3))							//ǰ1�ŵ��� 0:����� 1:�ҳ���
			{
				speek("��1��");
				delay_rtos(0,0,0,500);
				
				CtXunZheng_hou(3,1,AGV_SYS.XZ_CiTiao_Speed);	//�������Ѱ��
			}
			else
			{	
				speek("��1��");
				delay_rtos(0,0,0,50);
				
				CtXunZheng_hou(3,0,AGV_SYS.XZ_CiTiao_Speed);	//�ҳ�����Ѱ��	
			}
			if(!g_CtXunZheng.XunZ_OK_hou_1)	//����Ѱ��δOK	//δ���������ֹͣ
			{
				Ting_Zhi();							//ֹͣ
				HmiTaskState = 6;								//��������ʾ����ֹͣ
				speek("��1");
				delay_rtos(0,0,0,500);				
			}
			else								//����Ѱ��OK								
			{
				g_Warning.chugui = 0;			//�����־����
				if(g_CtXunZheng.XunZ_OK_qian_1)	//ǰ1ҲѰ����
				{
					HmiTaskState = 5;								//��������
					if(!g_CDH8_hou_1.Error)
					{
						Cdh3_Inc = IncPIDCalc2(g_CDH8_hou_1.Distance);	//1 λ��ʽPID//�����ֵ								
					}			
					PID_speed.moter3_speed = j_speed2+Cdh3_Inc;
					PID_speed.moter4_speed = j_speed2-Cdh3_Inc;
					
					if(PID_speed.moter3_speed>j_speed2)	PID_speed.moter3_speed = j_speed2;
					if(PID_speed.moter4_speed>j_speed2)	PID_speed.moter4_speed = j_speed2;

					if(PID_speed.moter3_speed<0)	PID_speed.moter3_speed = 0;
					if(PID_speed.moter4_speed<0)	PID_speed.moter4_speed = 0;

					LunZi_Go(3,PID_speed.moter3_speed);LunZi_Go(4,PID_speed.moter4_speed);								
				}
				else							//��һ������δ�Ϲ�--ǰ1δ�Ϲ�
				{
					delay_rtos(0,0,0,10);		
				}
			}			
		}
		else
		{
			g_Warning.chugui = 0;			//�����־����
			HmiTaskState = 5;								//��������
			if(!g_CDH8_hou_1.Error)
			{
				Cdh3_Inc = IncPIDCalc2(g_CDH8_hou_1.Distance);	//1 λ��ʽPID//�����ֵ								
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
	else if(g_AGV_Sta.Car_dir == 1)					//����
	{
				
		while(g_CDH8_hou_2.Num==0 && num2<CT_chugui_delay)		//�յ���0.5��
		{
			num2++;
			delay_rtos(0,0,0,10);
		}
		if(g_CDH8_hou_2.Num==0 )
		{
			//ֹͣ
			Ting_Zhi();		
			g_Warning.chugui = 1;			//�����־			
			//��һ��Ѱ��
			if(!check_CDH_chugui(4))							//ǰ1�ŵ��� 0:����� 1:�ҳ���
			{
				speek("��2��");
				delay_rtos(0,0,0,500);
				
				CtXunZheng_hou(4,1,AGV_SYS.XZ_CiTiao_Speed);	//�������Ѱ��
			}
			else
			{	
				speek("��2��");
				delay_rtos(0,0,0,500);
				
				CtXunZheng_hou(4,0,AGV_SYS.XZ_CiTiao_Speed);	//�ҳ�����Ѱ��	
			}			
			
			if(!g_CtXunZheng.XunZ_OK_hou_2)	//����Ѱ��δOK	//δ���������ֹͣ
			{
				Ting_Zhi();
				HmiTaskState = 6;					//�޴���ֹͣ
				speek("��2");
				delay_rtos(0,0,0,500);		
			}
			else								//����Ѱ��OK								
			{
				g_Warning.chugui = 0;			//�����־����
				if(g_CtXunZheng.XunZ_OK_qian_2)	//ǰ2Ѱ����
				{
					HmiTaskState = 5;					//��������
					if(!g_CDH8_hou_2.Error)
					{
						Cdh4_Inc = IncPIDCalc2(g_CDH8_hou_2.Distance);//2 λ��ʽPID//�����ֵ
					}
					PID_speed.moter4_speed = j_speed2-Cdh4_Inc;	
					PID_speed.moter3_speed = j_speed2+Cdh4_Inc;
									
					
					if(PID_speed.moter4_speed>j_speed2)	PID_speed.moter4_speed = j_speed2;
					if(PID_speed.moter3_speed>j_speed2)	PID_speed.moter3_speed = j_speed2;

					if(PID_speed.moter4_speed<0)	PID_speed.moter4_speed = 0;
					if(PID_speed.moter3_speed<0)	PID_speed.moter3_speed = 0;
			
					LunZi_Back(4,PID_speed.moter4_speed);LunZi_Back(3,PID_speed.moter3_speed);			
				}
				else							//��һ������δ�Ϲ�--ǰ2δ�Ϲ�
				{
					delay_rtos(0,0,0,10);		
				}				
			}			
		}
		else
		{
			g_Warning.chugui = 0;			//�����־����
			HmiTaskState = 5;					//��������
			if(!g_CDH8_hou_2.Error)
			{
				Cdh4_Inc = IncPIDCalc2(g_CDH8_hou_2.Distance);//2 λ��ʽPID//�����ֵ
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
u8 g_Trun_Val = 10;			//�ֶ�ת��Ƕ�
void PID_SD_Adjust(u16 j_speed,float kp,u16 ki,float kd)
{
	PID2.Kp = PID.Kp = j_speed * kp /1000;			//��̬PID
	PID2.Ki = PID.Ki = j_speed * ki /1000; 
	PID2.Kd = PID.Kd = kd; 
	
	HmiTaskState = 5;								//�������� -- �ֶ�

	switch(g_AGV_yaokong.SD_ir)	//�趨Ŀ��ֵ
	{
		case 1:					//ǰ��
			PID.SetTarget  = g_DWQ.qianlun_zhong_val + g_AGV_yaokong.jiaodu;		//PIDĿ��ֵ--ǰ_�����ֵ�λ����ֵ 
			PID2.SetTarget = g_DWQ.houlun_zhong_val;		//PIDĿ��ֵ--��_�����ֵ�λ����ֵ 						
			break;	
		
		case 2:					//����
			PID2.SetTarget = g_DWQ.houlun_zhong_val + g_AGV_yaokong.jiaodu;		//PIDĿ��ֵ--��_�����ֵ�λ����ֵ 	
			PID.SetTarget  = g_DWQ.qianlun_zhong_val;		//PIDĿ��ֵ--ǰ_�����ֵ�λ����ֵ 
				break;	
				
		default:
			break;
	}	
	
	switch(g_AGV_yaokong.SD_ir)	//ʵ�ʿ��Ƶ�����ٶ�			
	{
		case 1:					//ǰ��

			DWQ1_Inc = IncPIDCalc(g_After_filter[1]);		//1 λ��ʽPID//�����ֵ	 0-4096				
			PID__SD_speed.moter1_speed = j_speed+DWQ1_Inc;
			PID__SD_speed.moter2_speed = j_speed-DWQ1_Inc;
			
			DWQ2_Inc = IncPIDCalc2(g_After_filter[2]);		//2 λ��ʽPID//�����ֵ						
			PID__SD_speed.moter3_speed = j_speed+DWQ2_Inc;
			PID__SD_speed.moter4_speed = j_speed-DWQ2_Inc;
			break;
		
		case 2:					//����

			DWQ2_Inc = IncPIDCalc2(g_After_filter[2]);		//1 λ��ʽPID//�����ֵ	 0-4096				
			PID__SD_speed.moter4_speed = j_speed+DWQ2_Inc;
			PID__SD_speed.moter3_speed = j_speed-DWQ2_Inc;
			
			DWQ1_Inc = IncPIDCalc(g_After_filter[1]);		//2 λ��ʽPID//�����ֵ						
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


	switch(g_AGV_yaokong.SD_ir)	//ʵ�ʿ��Ƶ�����ٶ�			
	{
		case 1:					//ǰ��
			LunZi_Go(1,PID__SD_speed.moter1_speed);LunZi_Go(2,PID__SD_speed.moter2_speed);
			
			LunZi_Go(3,PID__SD_speed.moter3_speed);LunZi_Go(4,PID__SD_speed.moter4_speed);
		break;
		
		case 2:					//����
			LunZi_Back(4,PID__SD_speed.moter4_speed);LunZi_Back(3,PID__SD_speed.moter3_speed);		
			LunZi_Back(2,PID__SD_speed.moter2_speed);LunZi_Back(1,PID__SD_speed.moter1_speed);			
			break;			
		
		default:
			break;
	}

}

u8 check_CDH_chugui(u8 ID)		//����0:����� 1:�ҳ���
{
	u8 temp_s=0;
	
	if(!g_AGV_Sta.Car_dir)		//ǰ������
	{
		if(g_Ct_chugui[ID] > 0)
		{
			temp_s = 1;				//���ұ߳���
		}
		else if(g_Ct_chugui[ID] < 0)
		{
			temp_s = 0;				//����߳���
		}		
	}
	else						//���˷���
	{
		if(g_Ct_chugui[ID] > 0)
		{
			temp_s = 0;				//����߳���
		}
		else if(g_Ct_chugui[ID] < 0)
		{
			temp_s = 1;				//���ұ߳���			
		}	
	}


	return temp_s;

}










//�ϲ�����߷�����ƺ�����ʼ
void Zi_Dong(void)						//�е��Զ�����
{
//	if(g_AGV_Sta.Car_Auto2Manu_mode)	//���ֶ��л�����ʱ��ֹͣ
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
	*g_dispatch_message.RunState = 0;					//�л����Ǿ���ģʽ
	if(!g_AGV_Sta.Car_Auto2Manu_mode)	//���Զ��л�����ʱ��ֹͣ
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
	HmiTaskState = 4;					//ֹͣ	
	delay_rtos(0,0,0,500);	
}
void Qi_Dong(void)
{
	AGV_System_Start();
	
	HmiTaskState = 5;				//��������
	g_AGV_speaker_flag.start = 1;		//�Զ�ģʽ��:��������������
	delay_rtos(0,0,0,g_Speaker_delay);

}
void Zuo_Fen(void)
{
	if(!g_AGV_Sta.Car_dir)						//ǰ��
	{
		g_AGV_Sta.Car_fencha_dir = 1;			
	}
	else										//����
	{
		g_AGV_Sta.Car_fencha_dir = 2;			//�ֲ��־		
	}
//	g_AGV_Sta.Car_fencha_dir = 1;
	g_AGV_speaker_flag.FenCha_L = 1;		
	delay_rtos(0,0,0,g_Speaker_delay);
}

void You_Fen(void)
{
	if(!g_AGV_Sta.Car_dir)						//ǰ��
	{
		g_AGV_Sta.Car_fencha_dir = 2;			
	}
	else										//����
	{
		g_AGV_Sta.Car_fencha_dir = 1;			//�ֲ��־		
	}
	
//	g_AGV_Sta.Car_fencha_dir = 2;			//�ֲ��־
	g_AGV_speaker_flag.FenCha_R = 1;		
	delay_rtos(0,0,0,g_Speaker_delay);
}
void ZhiXing(void)							//ֱ��
{
//	if(g_AGV_Sta.Car_dir)						//����
//	{
//		g_AGV_Sta.Car_fencha_dir = 1;			//�ֲ��־
//	}
//	else										//ǰ��
//	{
//		g_AGV_Sta.Car_fencha_dir = 1;			//�ֲ��־
//	}	
}


void SD_Trun_L(void)
{
											//����ת��
	delay_rtos(0,0,0,g_Speaker_delay);
}

void SD_Trun_R(void)
{
											//����ת��
	
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
			
			delay_rtos(0,0,0,125);			//2.5�����
		}		
	}
	else
	{
		*speed_zhi = speed_max;
	}	
}

void Ruan_jian(u16 speed_max1,u16 speed_min,u16 * speed_TrueVal)	//�����
{	
	u16 temp_cha=0;
	u16 temp_cha2=0;
	u8 temp_i=0;
	u8 temp_chu=0;
	u16 temp_val=0;
		
	temp_cha = abs(speed_max1-speed_min);	//eg:800-400
	
	if(temp_cha <= 800)
	{
		temp_chu = 5;		//500ms����
	}
	else
	{
		temp_chu = 10;		//1000ms����
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

void Ruan_Stop(u16 * speed_TrueVal)	//�����
{	
	u16 temp_cha=0;
	u16 temp_cha2=0;
	u8 temp_i=0;
	u16 temp_val=0;
	u16 speed_max1=0;
	
	speed_max1 = * speed_TrueVal;

	if(speed_max1>100&&speed_max1 < 600)	//�����Χmotec������ͣ,�Լ�����ͣ
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
	else					//����600,motec�����Լ���ͣ
	{
		g_Start_flag.Start_Auto_PID = 0;	
		MotoStop(0);
	}
		
	
	


		
	
	
}

