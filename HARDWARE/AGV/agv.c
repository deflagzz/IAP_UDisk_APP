#include "agv.h"


//ǰ������
//- 	    |			+
//-  		|			+
//-			|			+

//����
//+ 	    |			-
//+  		|			-
//+			|			-


AGV_System AGV_SYS;

AGV_status g_AGV_Sta = 
{
	0,
	0,
	0,					//Ĭ���Զ�
	0,
};

 AGV_RunState g_RunSta;
 AGV_Warning  g_Warning;


void delay_rtos(u32 h,u32 m,u32 s,u32 ms)
{
	OS_ERR err;
	OSTimeDlyHMSM(h,m,s,ms,OS_OPT_TIME_HMSM_NON_STRICT,&err);	//OS_OPT_TIME_HMSM_NON_STRICT:��ʱ���޴�С
}





void UserConfigInit(void)
{

	W25QXX_Init();			//W25QXX��ʼ��
	
	do
	{
		LED4 = !LED4;//DS0��˸
		BEEP = !BEEP;
		delay_rtos(0,0,0,200);
	}while(W25QXX_ReadID()!=W25Q128);//��ⲻ��W25Q128��LED��˸
	LED4 = 1;
	BEEP = 0;
	delay_rtos(0,0,0,500);
    GetAllParameterFromSystem();		//��ȡ���Ե�ϵͳ����

    if(SystemParameter[0] != 5) 		//�״�flash��û����ʱ�������⵼�����ݶ�ʧ��ˢ���ʼ��
    {
#if 1									//Ϊ1	//����ǰ100���ڴ���д���ʼ�� -- ϵͳ����
        SystemParameter[0] = 5;			//�ж��Ƿ��һ��д��ı�־
        SystemParameter[1] = 0;	
        SystemParameter[2] = 0;
        SystemParameter[3] = 4;			//�ֶ��ٶȱ��� -- 4/10*3000
        SystemParameter[4] = 0; 
        SystemParameter[5] = 0; 		//���ģʽ -- ���籣��
        SystemParameter[6] = 0;			//
        SystemParameter[7] = 0;
		
        SystemParameter[8] = 0;  		
        SystemParameter[9] = 0; 		
        SystemParameter[10] = 0; 		
		
        SystemParameter[11] = 0;		
        SystemParameter[12] = 0; 	
        SystemParameter[13] = 0; 	
        SystemParameter[14] = 0; 		
        SystemParameter[15] = 0; 		
        SystemParameter[16] = 0;
        SystemParameter[17] = 0;
        SystemParameter[18] = 0; 		
        SystemParameter[19] = 0; 		
        SystemParameter[20] = 0; 		
        SystemParameter[21] = 0;
        SystemParameter[22] = 0;
        SystemParameter[23] = 0;
        SystemParameter[24] = 0; 		//·����
        SystemParameter[25] = 0; 		//
        SystemParameter[26] = 0; 		//
        SystemParameter[27] = 0; 		//
        SystemParameter[28] = 0; 		//
        SystemParameter[29] = 0; 		//
        SystemParameter[30] = 1;		//����
        SystemParameter[31] = 3; 		//ϵͳ����
        SystemParameter[32] = 1; 		//ϵͳ����
        SystemParameter[33] = 0; 		//ϵͳ�������� -- 0:��1:�ر�
        SystemParameter[34] = 0; 		//����״̬��   -- 0:��1:�ر�
        SystemParameter[35] = 300; 		//����
        SystemParameter[36] = 800; 		//����
        SystemParameter[37] = 1200; 	//����
        SystemParameter[38] = 300; 		//��λ�Խ��ٶ�
        SystemParameter[39] = 0;
        SystemParameter[40] = 800;	//Ѱ������ٶ�
        SystemParameter[41] = 35;	//��λ��Ѱ���ٶȱ�
        SystemParameter[42] = 600;	//�����Ϲ��ٶ�
        SystemParameter[43] = 1200;	//�������ٶ�
        SystemParameter[44] = 0;
        SystemParameter[45] = 0;	
        SystemParameter[46] = 0;
        SystemParameter[47] = 0;
        SystemParameter[48] = 0;
        SystemParameter[49] = 0;
        SystemParameter[50] = 40;	//�Զ�Kp
        SystemParameter[51] = 80;   //�Զ�Ki
        SystemParameter[52] = 0;	//�Զ�Kd
        SystemParameter[53] = 30;	//�ֶ�Kp
        SystemParameter[54] = 60;	//�ֶ�Ki
        SystemParameter[55] = 0;	//�ֶ�Kd
        SystemParameter[56] = 10;	//PID����ʱ��
        SystemParameter[57] = 108;	//ǰ����ֵ
        SystemParameter[58] = 199;	//ǰ����ֵ
        SystemParameter[59] = 288;  //ǰ����ֵ

        SystemParameter[60] = 58; 	//������ֵ
        SystemParameter[61] = 145; 	//������ֵ
        SystemParameter[62] = 238; 	//������ֵ
        SystemParameter[63] = 0; 	//
        SystemParameter[64] = 0; 	//
        SystemParameter[65] = 0; 	//
        SystemParameter[66] = 0; 	//
        SystemParameter[67] = 0; 	//
        SystemParameter[68] = 0; 	//
        SystemParameter[69] = 0; 	//
        SystemParameter[70] = 15; 	//�޵籨��ֵ
        SystemParameter[71] = 0; 	//
        SystemParameter[72] = 0; 	//
        SystemParameter[73] = 0; 	//
        SystemParameter[74] = 0; 	//
        SystemParameter[75] = 0; 	//
		SystemParameter[76] = 0; 	//
        SystemParameter[77] = 0;
        SystemParameter[78] = 0;
        SystemParameter[79] = 0;
        SystemParameter[80] = 0;	//��_���⿪�� 1:��
        SystemParameter[81] = 0;	//Զ_���⿪�� 1:��
        SystemParameter[82] = 1;	//ǰ_��е���� 1:��
        SystemParameter[83] = 1;	//��_��е���� 1:��
        SystemParameter[84] = 0;	//ԭ�㷽�� 0:ǰ������ 1:���˷���
        SystemParameter[85] = 0;
        SystemParameter[86] = 0;
        SystemParameter[87] = 0;	
        SystemParameter[88] = 0;	//
        SystemParameter[89] = 0;
		SystemParameter[97] = 0; 	//�ͻ���ʱ
        SystemParameter[98] = 0; 
        SystemParameter[99] = 0; 
#endif
        //�洢����ϵͳ����
        SetAllParameterToSystem();

#if 1
        //���·������վ����
        memset(RouteStationNum, 0, RouteNum);
        //��������·��������վ����
        SetAllStationNum();

        //������̰�������
        memset(ProcessStepNum, 0, ProcessNum);
        //�����������̰����Ĳ���
        SetAllStepNum();
#endif
    }


	
//	
//ϵͳ�������µ���������
//	
		
	
	//	
	//ϵͳ������Flash���µ�ϵͳ��
	//				
	AGV_SYS.SD_Speed_bili       = 		  SystemParameter[3];	//�ֶ��ٶȱ��� -- 4/10*3000
	g_RunSta.chongdian 			= 		  SystemParameter[5];	//���ģʽ��־ -- ���籣��
	AGV_SYS.ID 					=         SystemParameter[30];	//����
	AGV_SYS.yinliang			=         SystemParameter[31]; 	//ϵͳ����
	AGV_SYS.Auto_Speed_bili		=         SystemParameter[32]; 	//�Զ������ٶȵı���
	AGV_SYS.Key_yuyin 			=         SystemParameter[33]; 	//ϵͳ��������
	AGV_SYS.Key_RGB_LED 		=         SystemParameter[34]; 	//����״̬��
	AGV_SYS.L_speed 			=         SystemParameter[35];  //����
	AGV_SYS.M_speed 			=         SystemParameter[36];  //����
	AGV_SYS.H_speed 			=         SystemParameter[37]; 	//����
	AGV_SYS.duijie_speed 		=         SystemParameter[38]; 	//��λ�Խ��ٶ�
		   
	AGV_SYS.XZ_MAX_Speed 		=         SystemParameter[40]; 	//Ѱ������ٶ�
	AGV_SYS.XZ_DWQ_Speed_bili	=         SystemParameter[41];	//��λ��Ѱ���ٶȱ�
	AGV_SYS.XZ_CiTiao_Speed 	=         SystemParameter[42]; 	//�����Ϲ��ٶ�
	AGV_SYS.Motor_MAX_Speed 	=         SystemParameter[43];	//�������ٶ�


	AGV_SYS.AUTO_Kp       		=		  SystemParameter[50];	//�Զ�Kp
	AGV_SYS.AUTO_Ki        		=		  SystemParameter[51];  //�Զ�Ki
	AGV_SYS.AUTO_Kd        		=		  SystemParameter[52];	//�Զ�Kd
	AGV_SYS.SD_Kp       		=		  SystemParameter[53];	//�ֶ�Kp
	AGV_SYS.SD_Ki        		=		  SystemParameter[54];	//�ֶ�Ki
	AGV_SYS.SD_Kd        		=		  SystemParameter[55];	//�ֶ�Kd
	AGV_SYS.PID_time 			=         SystemParameter[56];	//PID����ʱ��

	g_DWQ.qianlun_L_val        	=		  SystemParameter[57];	//ǰ����ֵ
	g_DWQ.qianlun_zhong_val     =	      SystemParameter[58];	//ǰ����ֵ
	g_DWQ.qianlun_R_val        	=		  SystemParameter[59];  //ǰ����ֵ

	g_DWQ.houlun_L_val        	=		  SystemParameter[60]; 	//������ֵ
	g_DWQ.houlun_zhong_val    	=		  SystemParameter[61]; 	//������ֵ
	g_DWQ.houlun_R_val        	=		  SystemParameter[62]; 	//������ֵ
	AGV_SYS.add_time_yuzhi      = 		  SystemParameter[63];	//��ʱ��
	AGV_SYS.yuandian_ID         = 		  SystemParameter[64];	//ԭ��ID
	AGV_SYS.chongdian_ID        = 		  SystemParameter[65];	//���ID
	AGV_SYS.zhongzhuan_ID       = 		  SystemParameter[66];	//��ת̨ID

	
	
	Battery_Warining.Warining_Val_NoBattery = SystemParameter[70];	//�͵�������ֵ
	
	AGV_SYS.GunT_daozhong_time  =         SystemParameter[75];
	
	g_Senser_Enable.IR_qian_jin    	=		  SystemParameter[80]; 	//�����⿪��
	g_Senser_Enable.IR_hou_jin    	=		  SystemParameter[80]; 	//�����⿪��
	g_Senser_Enable.IR_qian_yuan    =		  SystemParameter[81]; 	//Զ����
	g_Senser_Enable.IR_hou_yuan    	=		  SystemParameter[81]; 	//Զ����
	g_Senser_Enable.jixie_qian    	=		  SystemParameter[82]; 	//ǰ��е
	g_Senser_Enable.jixie_hou   	=		  SystemParameter[83]; 	//���е
	AGV_SYS.yuandian_dir            = 		  SystemParameter[84];	//ԭ�㷽��

	//
	//ϵͳ������Flash���µ���������
	//				
	g_shoudong_screen_speed     = 		  SystemParameter[3];	//�ֶ��ٶȱ��� -- 4/10*3000
	g_Mode_chongdian			=		  SystemParameter[5];	//���ģʽ���籣��
	g_AGV_ID 					=         SystemParameter[30];	//����
	g_AGV_speaker_val 			=         SystemParameter[31]; 	//ϵͳ����
	g_sys_set_agvSPEED			=         SystemParameter[32]; 	//ϵͳ���� -- �Զ�
	g_AGV_speaker_key 			=         SystemParameter[33]; 	//ϵͳ��������
	g_AGV_LED_car_state			=         SystemParameter[34]; 	//����״̬��
	HmiDiSu       				=         SystemParameter[35];  //����
	HmiZhongSu     				=         SystemParameter[36];  //����
	HmiGaoSu      				=         SystemParameter[37]; 	//����
	g_AGV_speed_duijie			=         SystemParameter[38]; 	//��λ�Խ��ٶ�
			   	   
	XZ_Speed40					=         SystemParameter[40]; 	//Ѱ������ٶ�
	XZ_Speed41					=         SystemParameter[41];	//��λ��Ѱ���ٶȱ�
	XZ_Speed42					=         SystemParameter[42]; 	//�����Ϲ��ٶ�
	XZ_Speed43					=         SystemParameter[43];	//�������ٶ�

	g_screen_Auto_Kp			=		  SystemParameter[50];	//�Զ�Kp
	g_screen_Auto_Ki			=		  SystemParameter[51];  //�Զ�Ki
	g_screen_Auto_Kd			=		  SystemParameter[52];	//�Զ�Kd
	g_screen_Manu_Kp			=		  SystemParameter[53];	//�ֶ�Kp
	g_screen_Manu_Ki			=		  SystemParameter[54];	//�ֶ�Ki
	g_screen_Manu_Kd			=		  SystemParameter[55];	//�ֶ�Kd
	g_screen_control_TIME		=         SystemParameter[56];	//PID����ʱ��

	g_screen_qianlun_ZuoZhi		=		  SystemParameter[57];	//ǰ����ֵ
	g_screen_qianlun_ZhongZhi	=	      SystemParameter[58];	//ǰ����ֵ
	g_screen_qianlun_YouZhi		=		  SystemParameter[59];  //ǰ����ֵ

	g_screen_houlun_ZuoZhi		=		  SystemParameter[60]; 	//������ֵ
	g_screen_houlun_ZhongZhi 	=		  SystemParameter[61]; 	//������ֵ
	g_screen_houlun_YouZhi 		=		  SystemParameter[62]; 	//������ֵ
	g_add_time                  = 		  SystemParameter[63];	//��ʱ��
	g_yuandi_ID                 = 		  SystemParameter[64];	//
	g_chongdian_ID              = 		  SystemParameter[65];	//	
	g_zhongzhuan_ID				= 		  SystemParameter[66];	
	
	Li_Warning_val_NoBattery 	= 		  SystemParameter[70];	//�͵�������ֵ
	
	GunT_zhong_time  			=         SystemParameter[75];

	g_AGV_Enable_IR_jin      	=		  SystemParameter[80]; 	//�����⿪��
	g_AGV_Enable_IR_yuan        =		  SystemParameter[81]; 	//Զ����
	g_AGV_Enable_JiXie_qian    	=		  SystemParameter[82]; 	//ǰ��е
	g_AGV_Enable_JiXie_hou   	=		  SystemParameter[83]; 	//���е
	g_AGV_yuandian_dir          = 		  SystemParameter[84]; 	//ԭ���ʼ����
	
	
	//ң�������Ʋ�������
	g_AGV_yaokong.jiaodu_Max		= 50;	//����޽Ƕ�:��ֵ+-70��
	g_AGV_yaokong.GunTong_chufa_val = 50;	//ҡ���Ƶ��м�50
	g_AGV_yaokong.Start_chufa_val   = 15;	//ǰ����������
	
	
	switch(AGV_SYS.Auto_Speed_bili)
	{
		case 0:
				AGV_SYS.Car_Auto_Speed 	= AGV_SYS.L_speed;
			break;
		case 1:
				AGV_SYS.Car_Auto_Speed 	= AGV_SYS.M_speed;
			break;	
		case 2:
				AGV_SYS.Car_Auto_Speed 	= AGV_SYS.H_speed;
			break;	
		default :
			break;
	}	
	yinling(AGV_SYS.yinliang);
	PrintCom(YIN_SU4,9);osdelay_ms(10);		//����4
	PrintCom(YIN_DIAO5,9);osdelay_ms(10);	//���4		

//
//�����Զ�������Ϣ
//
    //HmiAutoReload();


    //��ȡ·������վ����
    GetRouteStationNum(HmiRouteNum);

    //��ȡ��ǰ·����Ϣ
    GetRouteData(HmiRouteNum);
	
    //��ȡ��������������
    GetProcessData();
	
	g_AGV_Sta.Flash_get_OK = 1;
}


	




















//AGV_station agv_routr2station[StationNum];		//



//ִ��վ�㶯��
void StationAction(u16 num)
{
	u16 buff_speed=0;
	u16 set_speed=0;
	u8  flag_stop=0;
	
	
    while(g_AGV_Sta.Car_Auto2Manu_mode  || !g_Start_flag.Start_Auto_PID )	 //���������߷��Զ�
    {
        osdelay_ms(10); 
    }

	
    HmiStationSerialNum++;
    //��յر�
    g_AGV_RFID_ID = 0;
	memset(g_CDH_add_num,0,sizeof(g_CDH_add_num));	//��մŵ�������ر�ļ���

    //Ŀ��ر���ʾ
    HmiNextRfidNum = NowRouteInfor[num][5];								//4x90
	
	//GetRFIDbuff(g_AGV_RFID_ID,g_dispatch_message.Position_Last,g_dispatch_message.Position_Now,g_dispatch_message.Position_next,num);

	//�ȴ�Ŀ��ر�
    while(g_AGV_RFID_ID != NowRouteInfor[num][5])	//ɨ���ر꣬��Ŀ��ֵ�Ļ�������while
    {
        if(!g_AGV_Sta.Car_Auto2Manu_mode)//�Զ�ģʽ�¼��ر�
        {
			            //�ر����� 1:ʵ�� 0:����
			if(NowRouteInfor[num][18])			//ʵ��ر�
			{
				if(g_AGV_RFID_ID && (g_AGV_RFID_ID != g_AGV_Sta.RFID_buff[0]))			//�����ر�ֵ
				{
					if(g_AGV_RFID_ID != NowRouteInfor[num][5])	//����Ŀ��ֵ,����ѭ��
					{
						break;
					}

				}
			}			
            //����ر���	
			else								//����ر�
			{
				if(NowRouteInfor[num][15])	//�ֲ�ر�
				{					
					if(!g_AGV_Sta.Car_fencha_Start_qian)
					{
						g_AGV_Sta.fencha_RFID_qian = num;
						g_AGV_Sta.Car_fencha_Start_qian = 1;
					}

					if(!g_AGV_Sta.Car_fencha_Start_hou)
					{
						g_AGV_Sta.fencha_RFID_hou = num;
						g_AGV_Sta.Car_fencha_Start_hou  = 1;
					}						
				}
				else						//��ͨ�ر�
				{
					if(NowRouteInfor[num][7] && g_CDH_add_num[1] == NowRouteInfor[num][11] )	//ǰ������Ԫ����
					{
						g_AGV_RFID_ID = NowRouteInfor[num][5];
					}
					

					if(NowRouteInfor[num][9] && g_CDH_add_num[3] == NowRouteInfor[num][13])		//��������Ԫ����
					{
						g_AGV_RFID_ID = NowRouteInfor[num][5];
					}	
					
				}
				if(g_AGV_RFID_ID)			//�����ر�ֵ
				{
					if(g_AGV_RFID_ID != NowRouteInfor[num][5])	//����Ŀ��ֵ,����ѭ��
					{
						break;
					}
				}				
			}

        } 
		osdelay_ms(10);
    }	
	if(g_AGV_RFID_ID != NowRouteInfor[num][5] )
	{

		Ting_Zhi();						//�ر��ȡ����,ͣ��
		HmiTaskState = 3;				//�ر��쳣
		g_Warning.RFID_err = 1;			//�ر����
		while(1)
		{
			g_AGV_speaker_flag.RFID_READ_err = 1;
			delay_rtos(0,0,0,1500);		
		}
	}
	else								//�ر��ȡ��ȷ
	{
		g_Warning.RFID_err = 0;			//�ر�����
		g_AGV_Sta.juedui_RFID = g_AGV_RFID_ID;
		HmiRfidNum = g_AGV_RFID_ID;		//��⵽�ر����µ�ǰ�ر�				//4x130
		g_shoudong_screen_RFID = g_AGV_Sta.juedui_RFID; //���µ�ǰ�ر�	
		
		GetRFIDbuff(g_AGV_RFID_ID,g_dispatch_message.Position_Last,g_dispatch_message.Position_Now,g_dispatch_message.Position_next,num);

		switch(NowRouteInfor[num][6])	//ֹͣ��ǰ���������󡢺����ҡ�����������
		{
			case 0:
				break;	//ͨ��
			case 1:		//ֹͣ
			case 2:		//ǰ��	
			case 3:		//����
				Ting_Zhi();			//��վֹͣ	
				flag_stop = 1;		
				break;
			case 4:		//��ͷ����
			{
				if(g_AGV_Sta.Car_dir == 1)
				{
					Ting_Zhi();			//��վֹͣ	
					flag_stop = 1;					
				}			
			}
				break;
			case 5:		//��β����
			{
				if(g_AGV_Sta.Car_dir == 0)
				{
					Ting_Zhi();			//��վֹͣ	
					flag_stop = 1;					
				}			
			}				
				break;
			default:
				break;
		}

		
		if(flag_stop == 0)  
		{
			//���˵ķֲ��
			if(NowRouteInfor[num][18])		//ʵ��ر�
			{
				switch(NowRouteInfor[num][2])//�ֲ��ж�
				{
					case 0:
						break;//�����ϴ���Ϣ
					case 1://��ֲ�
					{
						Zuo_Fen();	//00111100
					}
					break;
					case 2://�ҷֲ�
					{
						You_Fen();
					}
					break;
					case 3://ֱ��
					{
						ZhiXing();
					}
					break;
					default:
					break;
				}	
			}			
		}
		else
		{
			//��վ��ʱ
			if(NowRouteInfor[num][1] > 0)
			{
				if(NowRouteInfor[num][1] > 9999)
				{
					NowRouteInfor[num][1] = 9999;
				}
				delay_rtos(0,0,0,NowRouteInfor[num][1]);	//���9999
			}		
		
		
		}
				
		
		
			
		
	
		
		buff_speed = AGV_SYS.Car_Auto_Speed;			//�����ٶ�
		switch(NowRouteInfor[num][4])//�ٶȵ�λ�ж�
		{
			case 0:
				set_speed = buff_speed;
				break;//�����ϴ���Ϣ
			case 1://����
			{			
				set_speed = HmiDiSu;
			}
			break;
			case 2://����
			{
				set_speed = HmiZhongSu;
			}
			break;
			case 3://����
			{
				set_speed = HmiGaoSu;
			}
			break;
			case 4://�Խӵ���
			{
				set_speed = AGV_SYS.duijie_speed;
			}
			break;
			default:
			break;
		}
		if(set_speed > buff_speed)
		{
			Ruan_Qi_jia(buff_speed,set_speed,&AGV_SYS.Car_Auto_Speed);

		}
		else
		{
			Ruan_jian(buff_speed,set_speed,&AGV_SYS.Car_Auto_Speed);


		}	
		
		switch(NowRouteInfor[num][0])//Զ�̺���
		{
			case 0:
				break;//�����ϴ���Ϣ
			case 1://��
			{
				g_Senser_Enable.IR_qian_yuan = 1;
				g_Senser_Enable.IR_hou_yuan  = 1;
				
	//			speek("Զ�����");
	//			osdelay_ms(g_Speaker_delay);
				
			}
			break;
			case 2://��
			{
				g_Senser_Enable.IR_qian_yuan = 0;
				g_Senser_Enable.IR_hou_yuan  = 0;
				
	//			speek("Զ����ر�");
	//			osdelay_ms(g_Speaker_delay);

			}
			break;
		}
		switch(NowRouteInfor[num][19])//���̺���
		{
			case 0:
				break;//�����ϴ���Ϣ
			case 1://��
			{
				g_Senser_Enable.IR_qian_jin = 1;
				g_Senser_Enable.IR_hou_jin  = 1;
	//			
	//			speek("�������");
	//			osdelay_ms(g_Speaker_delay);
			}
			break;
			case 2://��
			{
				g_Senser_Enable.IR_qian_jin = 0;
				g_Senser_Enable.IR_hou_jin  = 0;
				
	//			speek("������ر�");
	//			osdelay_ms(g_Speaker_delay);
			}
			break;
		}

		
		GunTong_PLC(num,NowRouteInfor[num][3]); //��Ͳ����

	//@@
	//���ýӿ�
	//	
	#if 0
		//�ж��Ƿ���Ҫ��ʱ
		if(NowRouteInfor[num][8]!=0)
			osdelay_s(NowRouteInfor[num][8]);

		switch(NowRouteInfor[num][11])//���е���豸ͨ��
		{
		case 0:
			//û���������
			PLC2_Data[32] = 0;
			break;//û�����豸����
		case 1://��һ���豸����
		{
			Ting_Zhi();
			//���豸������������ź�
			PLC2_Data[32] = NowRouteInfor[num][11];
			g_AGV_Status.Car_Speaker_flag = 22; //�����������
			//�ȴ�׼���ź�
			while(PLC2_Data[33] != 1)
			{
				osdelay_ms(10);
			}
			Qi_Dong();
			g_AGV_Status.Car_Speaker_flag = 23; //�����������
			//�����������ź�
			PLC2_Data[32] = 0;
			//���׼���ź�
			PLC2_Data[33] = 0;
		}
		break;
		case 2://�Ͷ����豸����
		{
			Ting_Zhi();
			//���豸������������ź�
			PLC2_Data[32] = NowRouteInfor[num][11];
			g_AGV_Status.Car_Speaker_flag = 22; //�����������
			//�ȴ�׼���ź�
			while(PLC2_Data[34] != 1)
			{
				osdelay_ms(10);
			}
			Qi_Dong();
			g_AGV_Status.Car_Speaker_flag = 23; //�����������

			//�����������ź�
			PLC2_Data[32] = 0;
			//���׼���ź�
			PLC2_Data[34] = 0;
		}
		break;
		case 3://�������豸����
		{
			Ting_Zhi();
			//���豸������������ź�
			PLC2_Data[32] = NowRouteInfor[num][11];
			g_AGV_Status.Car_Speaker_flag = 22; //�����������
			//�ȴ�׼���ź�
			while(PLC2_Data[35] != 1)
			{
				osdelay_ms(10);
			}
			Qi_Dong();
			g_AGV_Status.Car_Speaker_flag = 23; //�����������

			//�����������ź�
			PLC2_Data[32] = 0;
			//���׼���ź�
			PLC2_Data[35] = 0;
		}
		break;
		case 4://���ĺ��豸����
		{
			Ting_Zhi();
			//���豸������������ź�
			PLC2_Data[32] = NowRouteInfor[num][11];
			g_AGV_Status.Car_Speaker_flag = 22; //�����������
			//�ȴ�׼���ź�
			while(PLC2_Data[36] != 1)
			{
				osdelay_ms(10);
			}
			Qi_Dong();
			g_AGV_Status.Car_Speaker_flag = 23; //�����������
			//�����������ź�
			PLC2_Data[32] = 0;
			//���׼���ź�
			PLC2_Data[36] = 0;
		}
		break;
		}

		switch(NowRouteInfor[num][7])//�����豸������
		{
		case 0:
			PLC2_Data[38] = 0;
			PLC2_Data[39] = 0;
			PLC2_Data[40] = 0;
			PLC2_Data[41] = 0;
			break;
		case 1:
			PLC2_Data[38] = 1;
			break;
		case 2:
			PLC2_Data[39] = 1;
			break;
		case 3:
			PLC2_Data[40] = 1;
			break;
		case 4:
			PLC2_Data[41] = 1;
			break;
		}


		//AGV�Ե��ݵ�ʹ�����
		switch(NowRouteInfor[num][10])
		{
		case 0:
			break;//���ݲ�ʹ��
		case 1://AGVȥһ¥
		{
			AGV_QuYiLou();
		}
		break;
		case 2://AGVȥ��¥
		{
			AGV_QuSanLou();
		}
		break;
		}
	#endif
	//
	//���ýӿ�
	//@@	

		switch(NowRouteInfor[num][6])//����ִ�����ж�	//��վ����	 0������	1��ֹͣ	2:ǰ��	3����λ�Խ�  4������ 
		{
			case 0:
				break;//ͨ��
			case 1:
				break;//ֹͣ
			case 2://ǰ��
			{
				g_AGV_Sta.Car_dir = g_AGV_Sta.Car_dir;
				//Qi_Dong();			
				
			}
				break;		
			case 3://����
			{
				g_AGV_Sta.Car_dir = !g_AGV_Sta.Car_dir;
				Qi_Dong();
			}
				break;
			case 4://��ͷ����
			{
				if(g_AGV_Sta.Car_dir)
				{
					g_AGV_Sta.Car_dir = 0;
					Qi_Dong();				
				}

			}
				break;
			case 5://��β����
			{
				if(!g_AGV_Sta.Car_dir)
				{
					g_AGV_Sta.Car_dir = 1;
					Qi_Dong();				
				}

			}
				break;			
			default:
				break;
		}	
		
		if(flag_stop == 1) //����
		{
			if(NowRouteInfor[num][18])		//ʵ��ر�
			{
				switch(NowRouteInfor[num][2])//�ֲ��ж�
				{
					case 0:
						break;//�����ϴ���Ϣ
					case 1://��ֲ�
					{
						Zuo_Fen();	//00111100
					}
					break;
					case 2://�ҷֲ�
					{
						You_Fen();
					}
					break;
					case 3://ֱ��
					{
						ZhiXing();
					}
					break;
				}	
			}		
		
		}
	}	 
}





//ִ������
void ActiveProcess(void)
{
    //�������̺�
    SetOneParameterToSystem(HmiProcessNum, 25);
    SystemParameter[26] = HmiTask;
    //���������
    SetOneParameterToSystem(HmiTask, 26);

    //����״̬Ϊ��������
    HmiTaskState = 5;

    HmiTask = 2;

    //�����Զ�������Ϣ
    HmiAutoReload();

    g_AGV_Sta.Car_dir = AGV_SYS.yuandian_dir; //�����л���ǰ��

    //��ת���Զ�����
    HmiScreenSetGet = ZiDongJieMian;
}



u16 u8_to_u16(u8 *H_Bit,u8 *L_Bit)
{
	u16 temp_out=0;
	temp_out = *H_Bit;
	temp_out = temp_out<<8|*L_Bit;

	return temp_out;
}


u16 g_LastCDH_buff[5];		//�ϴ���ʷֵ	   -- 4���ŵ�����ֵ
u8  g_CDH_add_num[5];		//�ŵ���ͻ���ۼ�ֵ -- ǰ������������Ԫ��ֵ [0]:ǰ���� [2]:������
//������Ԫ�ϵ������ŵ���ͬʱȫ������һ��ͻ�䴥��
void CDH_ADD(u16 *last_data,u16 *buff,u8 *cdh_add_num_buff)
{
	u8 temp_i=0;
	for(temp_i=1;temp_i<5;temp_i+=2)
	{
		if(last_data[temp_i] || last_data[temp_i+1])
		{
			if( buff[temp_i] == 0x0000 && buff[temp_i+1] == 0x0000)
			{
				osdelay_ms(10);//��ʱ����
				if(buff[temp_i] == 0x0000 && buff[temp_i+1] == 0x0000)
				{
					if(cdh_add_num_buff[temp_i] < 100)
					{
						cdh_add_num_buff[temp_i]++;
					}
				}
			}		
		}

		last_data[temp_i] = buff[temp_i];	
		last_data[temp_i+1] = buff[temp_i+1];	

	}	
	


}

//1:��ֲ�  2:�ҷֲ� 
//����ֲ�ر�--11:ǰ����ֲ� 12:ǰ���ҷֲ�  21:������ֲ� 22:�����ҷֲ�
//0:ǰ�� 1:����
void fencha_1to2_qian(u8 fencha_dir,u8 *FC_dir_qian)
{
	switch (fencha_dir)
	{
		case 1:
		case 11:
			*FC_dir_qian = 1;

			break;
		case 2:
		case 12:
			*FC_dir_qian = 2;
	
			break;
		default:
			break;
	}	
}
void fencha_1to2_hou(u8 fencha_dir,u8 *FC_dir_hou)
{
	switch (fencha_dir)
	{
		case 1:
		case 21:
			*FC_dir_hou  = 1;
			break;
		case 2:
		case 22:

			*FC_dir_hou  = 2;			
			break;
		default:
			break;		
	}	
}

void GetRFIDbuff(u16 RFID,u16 *last,u16 *now,u16 *next,u16 num)
{
	u16 temp_i=0;
	
	*next = NowRouteInfor[num][5];
	if(*now)
	{
		temp_i = *now;
		*last = temp_i;	
	}

	*now  = RFID;
	if(num+1 < HmiStationNum)
	{
		if(*now == *next)
		{
			*next  = NowRouteInfor[num+1][5];
		}
	}

}

void GunTong_PLC(u16 num,u16 type) //0:	//��ת  1://������  2://�Ҳ����
{
	switch(type)//��Ͳ����
	{
		case 0:	//��ת
			break;
		case 1://������
		{
			g_RunSta.roller = 1;	//����״̬
			*g_PLC_message[AGV_SYS.ID-1].StoveID = NowRouteInfor[num][8];	//AGV����PLC��Ҫͨ�ŵ�¯��ID 
			*g_PLC_message[AGV_SYS.ID-1].Flag_Position_OK 	= 1;			//AGV����PLC����ָ��λ��
			
			//����PLC��ǰ��λ������Ϣ 1:���� 2:ȡ��
			if(*g_PLC_message[AGV_SYS.ID-1].StoveID == AGV_SYS.zhongzhuan_ID)		//��еץ��
			{
				if(AGV_SYS.ToPLC_task/10 == 1)
				{
					*g_PLC_message[AGV_SYS.ID-1].TO_PLC_Task_data = 2;		//ȡ��
				}
				else if(AGV_SYS.ToPLC_task/10 == 2)
				{
					*g_PLC_message[AGV_SYS.ID-1].TO_PLC_Task_data = 1;		//����
				}
				
			}
			else
			{
				if(*g_PLC_message[AGV_SYS.ID-1].StoveID==1||*g_PLC_message[AGV_SYS.ID-1].StoveID==2||*g_PLC_message[AGV_SYS.ID-1].StoveID==3||*g_PLC_message[AGV_SYS.ID-1].StoveID==4||NowRouteInfor[num][8]==5)
				{
					*g_PLC_message[AGV_SYS.ID-1].TO_PLC_Task_data = AGV_SYS.ToPLC_task / 10;	//ȡ��
				}				
			}




			
			
			g_AGV_speaker_flag.Down_L = 1;
			delay_rtos(0,0,0,20);
			GunTong_Trun_L_DOWN();
			
			g_AGV_speaker_flag.UP_L = 1;
			delay_rtos(0,0,0,20);
			GunTong_Trun_L_UP();
			
			*g_PLC_message[AGV_SYS.ID-1].StoveID = 0;						//AGV����PLC��Ҫͨ�ŵ�¯��ID 
			*g_PLC_message[AGV_SYS.ID-1].Flag_Position_OK 	 = 0;			//AGV����PLC����ָ��λ��				
			//����PLC��ǰ��λ������Ϣ 1:���� 2:ȡ��
			*g_PLC_message[AGV_SYS.ID-1].TO_PLC_Task_data    = 0;
			*g_PLC_message[AGV_SYS.ID-1].Flag_RecTray_Ready  = 0;			//AGV����PLC��������׼������
			*g_PLC_message[AGV_SYS.ID-1].Flag_RecTray_Finish = 0;			//AGV����PLC���̽������
			g_RunSta.roller = 0;	//������״̬
		}
		break;
		case 2://�Ҳ����
		{
			g_RunSta.roller = 1;	//����״̬
			*g_PLC_message[AGV_SYS.ID-1].StoveID = NowRouteInfor[num][8];	//AGV����PLC��Ҫͨ�ŵ�¯��ID 
			*g_PLC_message[AGV_SYS.ID-1].Flag_Position_OK 	= 1;			//AGV����PLC����ָ��λ��
			
			//����PLC��ǰ��λ������Ϣ 1:���� 2:ȡ��
			if(*g_PLC_message[AGV_SYS.ID-1].StoveID == AGV_SYS.zhongzhuan_ID)		//��еץ��
			{
				if(AGV_SYS.ToPLC_task/10 == 1)
				{
					*g_PLC_message[AGV_SYS.ID-1].TO_PLC_Task_data = 2;		//ȡ��
				}
				else if(AGV_SYS.ToPLC_task/10 == 2)
				{
					*g_PLC_message[AGV_SYS.ID-1].TO_PLC_Task_data = 1;		//����
				}
				
			}
			else
			{
				if(*g_PLC_message[AGV_SYS.ID-1].StoveID==1||*g_PLC_message[AGV_SYS.ID-1].StoveID==2||*g_PLC_message[AGV_SYS.ID-1].StoveID==3||*g_PLC_message[AGV_SYS.ID-1].StoveID==4||NowRouteInfor[num][8]==5)
				{
					*g_PLC_message[AGV_SYS.ID-1].TO_PLC_Task_data = AGV_SYS.ToPLC_task/10;	//ȡ��
				}			
			}



			
			g_AGV_speaker_flag.Down_R = 1;
			delay_rtos(0,0,0,20);
			GunTong_Trun_R_DOWN();
			g_AGV_speaker_flag.UP_R = 1;
			delay_rtos(0,0,0,20);
			GunTong_Trun_R_UP();
			
			*g_PLC_message[AGV_SYS.ID-1].StoveID = 0;						//AGV����PLC��Ҫͨ�ŵ�¯��ID 
			*g_PLC_message[AGV_SYS.ID-1].Flag_Position_OK 	 = 0;			//AGV����PLC����ָ��λ��				
			//����PLC��ǰ��λ������Ϣ 1:���� 2:ȡ��
			*g_PLC_message[AGV_SYS.ID-1].TO_PLC_Task_data    = 0;				
			*g_PLC_message[AGV_SYS.ID-1].Flag_RecTray_Ready  = 0;			//AGV����PLC��������׼������
			*g_PLC_message[AGV_SYS.ID-1].Flag_RecTray_Finish = 0;			//AGV����PLC���̽������	
			g_RunSta.roller = 0;	//������״̬				
		}
		break;
		//case 3://���װ��
		//{
		//	g_AGV_speaker_flag.UP_L = 1;
		//	GunTong_Trun_L_UP();
		//}
		//break;	
		
		//case 4://�Ҳ�װ��
		//{
		//	g_AGV_speaker_flag.UP_R = 1;
		//	GunTong_Trun_R_UP();
		//}		
		//break;
		default:
			break;

	}
}
void AGV_LED(void)			//AGV�г���
{
	Car_LED_Blue 	 =1;
	//Car_LED_Yellow =1;
	
	Car_LED_Qian_Enable	 = 0;
	Car_LED_Hou_Enable   = 0;
	while(1)
	{
		if(!AGV_SYS.Key_RGB_LED)
		{
			//���ߺ�ֹͣ��״̬��
			if(g_Start_flag.Start_Manu_PID || g_Start_flag.Start_Auto_PID)		
			{
				Car_LED_Blue 	= 1 ;				//��50ms
				delay_rtos(0,0,0,100);
				Car_LED_Blue 	= 0 ;				//��2��
				delay_rtos(0,0,0,100);
				Car_LED_Blue 	= 1 ;				//��50ms
				delay_rtos(0,0,0,100);
				Car_LED_Blue 	= 0 ;				//��2��
				delay_rtos(0,0,0,100);	
				delay_rtos(0,0,0,1500);		

			}
			else		//ֹͣ -- ��������
			{
				Car_LED_Blue 	= 1 ;				//��50ms
				delay_rtos(0,0,0,500);
				Car_LED_Blue 	= 0 ;				//��2��
				delay_rtos(0,0,0,2000);
			
			}
			
			
			//����ͻ�е���ϵ�״̬��
			if(!g_Start_flag.Start_IR || !g_Start_flag.button_bizhang_Start)	//ֹͣ
			{
				Car_LED_Yellow = 1;			//�Ƶ���˸
				delay_rtos(0,0,0,1000);
				Car_LED_Yellow = 0;
			}			
		}
		else
		{
			Car_LED_Blue 	= 0 ;
			Car_LED_Yellow = 0;
		}		

		delay_rtos(0,0,0,10);
	}
}


void AGV_Auto_speed(u16* buff_speed,u16 *true_speed,u8 Car_dir)	//�ο��ٶ�
{
	static u8 flag_i=0;
	if(Car_dir == 0 && g_Senser_InPut.IR_qian_yuan)				//ǰ������
	{	
		if(!flag_i)
		{			
			*buff_speed = *true_speed;
			Ruan_jian(*buff_speed,*buff_speed/2,true_speed);
			flag_i = 1;	
		}	
	}
	else if(Car_dir == 1 && g_Senser_InPut.IR_hou_yuan)			//���˷���			
	{
		if(!flag_i)
		{			
			*buff_speed = *true_speed;
			Ruan_jian(*buff_speed,*buff_speed/2,true_speed);
			flag_i = 1;	
		}							
	}
	else
	{
		if(flag_i)											
		{						
			Ruan_Qi_jia(*buff_speed/2,*buff_speed,true_speed);		
			flag_i = 0;
		}
		else
		{	
			*true_speed = *buff_speed/2;
		}
		
	}			

}
void AGV_Manu_speed(u16 now_speed,u16 *true_speed,u8 Car_dir)	//�ο��ٶ�
{
	u8 temp_vel = 6;	//10
	static u8 flag_i=0;
	if(Car_dir == 0 && g_Senser_InPut.IR_qian_yuan)				//ǰ������
	{	
		if(now_speed*temp_vel/10 < *true_speed)
		{
			Ruan_jian(*true_speed,now_speed*temp_vel/10,true_speed);
		}
		else 
		{
			*true_speed = now_speed*temp_vel/10;
		}
		flag_i = 1;		
	}
	else if(Car_dir == 1 && g_Senser_InPut.IR_hou_yuan)			//���˷���			
	{
		if(now_speed*temp_vel/10 < *true_speed)
		{
			Ruan_jian(*true_speed,now_speed*temp_vel/10,true_speed);
		}
		else 
		{
			*true_speed = now_speed*temp_vel/10;
		}

		flag_i = 1;	
	}
	else
	{
		if(flag_i)											
		{														
			Ruan_Qi_jia(now_speed*temp_vel/10,now_speed,true_speed);		
			flag_i = 0;
		}
		else
		{
			*true_speed = now_speed;
		}
		
	}			

}


//manu: 0:�Զ�Ѱ�� 1:�ֶ�����֧·
//����ֵ: 0:��ǰվ����֧·��,1:��ǰվ������·��
u8 zhilu2zonglu(u8 manu,u8 in_or_out,u16 now_id,u16* zonglu_id)
{
	u8 i=0;
	u8 flag_getAGV_in_way=0;
	u8 num_route=0;
	u8 zhilu_id=0;
	u8 flag_zhilu_or_zonglu=0;
	
	if(manu)	//1:�ֶ�����֧·
	{
		flag_getAGV_in_way = 0;
	
	}
	else		//0:�Զ�Ѱ��
	{	
		//��ȡ���ɵ�·������Ϣ
		GetRouteData(main_way_L2R_ID);	
		//���agv�Ƿ������ɵ���
		for(i=0;i<RouteStationNum[main_way_L2R_ID-1];i++)
		{
			if(now_id == NowRouteInfor[i][5])
			{
				flag_getAGV_in_way = 1;
			}	
		}		
	}


	//�������ɵ�,����ʻ�����ɵ���
	if(!flag_getAGV_in_way)
	{
		if(!in_or_out) //0:��,
		{
			zhilu_id = 30+now_id;
		}
		else 			//1:��
		{
			zhilu_id = 40+now_id;
		}
		flag_zhilu_or_zonglu = 0;
		num_route = GetRouteStationNum(zhilu_id); 	//��ȡ��ǰ֧·��վ������
		GetRouteData(zhilu_id);				  		//��ȡ��ǰ֧·��վ����Ϣ
		
		if(!in_or_out) //0:��,1:��
		{
			zhilu_id = 30+now_id;
			*zonglu_id = NowRouteInfor[num_route-1][5];	//��ȡ��ǰ֧·�����һ��վ���		luzi_id/10

		}
		else 
		{
			zhilu_id = 40+now_id;
			*zonglu_id = NowRouteInfor[0][5];	//��ȡ��ǰ֧·�ĵ�һ��վ���		luzi_id/10
			
		}			
	}
	//�����ɵ���
	else
	{
		flag_zhilu_or_zonglu = 1;
		*zonglu_id = now_id;
	}
	return flag_zhilu_or_zonglu;
}

//__num :ĩβ������,������ĩβ������Ϊֹ
u8 run_path(u8 path_id,u8 start_id,u8 end_id,u8 start_num,u8 __num) 
{
	u8 i=0;
	u8 flag_start=0;
	u8 flag_end=0;
	u8 num_start=0;
	u8 num_end=0;
	u8 flag_return=0;
	
	//ѡ��·��
	HmiRouteNum = path_id;
	//��ȡ·������Ϣ
	GetRouteData(path_id);
	//��������յ��Ƿ��ڵ�ǰ·����
	for(i=0;i<RouteStationNum[path_id-1];i++)
	{
		if(start_id == NowRouteInfor[i][5])
		{
			flag_start = 1;
			num_start  = i;
		}	
		if(end_id == NowRouteInfor[i][5])
		{
			flag_end = 1;
			num_end  = i;
		}
	}
	if(flag_start && flag_end)
	{
		if(!g_Start_flag.Start_Auto_PID) //��ֹͣ���������л�����
		{
			//4:��ͷ���� 5:��β����
			if(NowRouteInfor[num_start+1][6] == 4) //��һ���ر�ķ���
			{
					g_AGV_Sta.Car_dir = 0; 	//�����л���ǰ��  						
			}
			else if(NowRouteInfor[num_start+1][6] == 5)
			{
				g_AGV_Sta.Car_dir = 1; 	//�����л�  //����			
			}
			//�������ź�
			Qi_Dong();				
		}

		if(!g_AGV_Sta.flag_fist_zhilu)
		{
			num_start += 1;
			g_AGV_Sta.flag_fist_zhilu = 1;
		}
		
		for(i = num_start-start_num; i < num_end+1-__num; i++)
		{
			StationAction(i);					
		}	
		flag_return	= 1;	
	}
	else
	{
		flag_return	= 0;
	}
	return flag_return;
}



//ʮλ�Ƕ�������λ��λ��[��3,��4][¯��ʵ�ʱ��] 
//�����ڹ�λ�Ͻ����µ����� 1--6

//ʮλ�Ƕ�������λ��λ��[����1,����2][¯��ʵ�ʱ��]
//���ɵ���·����:8
//start_typ 0:�Զ�Ѱ 1:�ֶ�����֮·��
u8 get_path(u16 now_id,u16 luzi_id) //Ŀ��:¯��ID
{
    u8 i=0;
	u8 flag_getAGV_in_way=0;
	u8 num_route=0;
	u16 start_id=0;
	u16 end_id=0;
	u8  zonglu_id=0;
	u8  start_zhilu_or_zonglu=0;
	u8  end_zhilu_or_zonglu=0;
	
	u8 start_num=0;
	u8 end_num=0;
	u8 flag_return=0;
	
	//1.ȷ������֧··��:agv�Ƿ������ɵ���,���ڵĻ�����ʻ�����ɵ� 
	//2.ȷ�����յ�Ŀ��id��֧··�� 
	//3.���������յ������ȷ�����ɵ���·�� 
	//4.ƴװ����·��,�γ�һ������
	
	if(now_id == luzi_id)
	{
		path_1 = 0;
		path_2 = 0;
		path_3 = 40+luzi_id;
		//ѡ��·��
		HmiRouteNum = path_3;
		//��ȡ·������Ϣ
		GetRouteData(path_3);
		//��������յ��Ƿ��ڵ�ǰ·����
		if(NowRouteInfor[RouteStationNum[path_3-1]-1][5] == luzi_id)
		{
			GunTong_PLC(RouteStationNum[path_3-1]-1,NowRouteInfor[RouteStationNum[path_3-1]-1][3]);	
			//��վ��ʱ
			if(NowRouteInfor[RouteStationNum[path_3-1]-1][1] > 0)
			{
				if(NowRouteInfor[RouteStationNum[path_3-1]-1][1] > 9999)
				{
					NowRouteInfor[RouteStationNum[path_3-1]-1][1] = 9999;
				}
				delay_rtos(0,0,0,NowRouteInfor[RouteStationNum[path_3-1]-1][1]);	//���9999
			}				
		}
		else
		{
			flag_return = 0;
			return flag_return;				
		}
	}
	else
	{
		//ȷ���������
		start_zhilu_or_zonglu = zhilu2zonglu(0,0,now_id,&start_id); 			
		//ȷ���յ�����							
		end_zhilu_or_zonglu = zhilu2zonglu(0,0,luzi_id,&end_id);		
		//�����������յ�����ȷ����·��·���� 	
		//��������������ҵ��������겢�Ҵ����������ҵ��յ�����,
		//˵����·��·����Ϊ38(������),		
		//��֮��·��·����Ϊ48(��������) 		
		
		

		//��ȡ�������ҵ����ɵ�·������Ϣ
		GetRouteData(main_way_L2R_ID);	
		//��������յ���������·�ϵĵڼ���λ��
		for(i=0;i<RouteStationNum[main_way_L2R_ID-1];i++)
		{
			if(start_id == NowRouteInfor[i][5])
			{
				start_num = i+1;
			}	
			if(end_id == NowRouteInfor[i][5])
			{
				end_num = i+1; 
			}
		}
		//�����ʼ�㶼����·��,���֧·+��·+�յ�֧·
		if(start_num && end_num)
		{
			//���֧·+��·+�յ�֧·
			if(start_num < end_num)
			{
				zonglu_id = main_way_L2R_ID; 	//38
			}
			//���֧·+��·+�յ�֧·
			else if(start_num > end_num) 
			{
				zonglu_id = main_way_R2L_ID; 	//48
			}
			//����֧·�н���,ֱ������֧·ƴ��zonglu_id=0
			else if(start_num == end_num) 
			{
				zonglu_id = 0; 
			}		
		}


		//�������յ㻻��ƴ�ӵ�֧·��··��

		
		
		//���֧·
		if(!start_zhilu_or_zonglu) //0:֧·
		{
			path_1 = 30+now_id;
			if(!run_path(path_1,now_id,start_id,0,1))
			{
				flag_return = 0;
				return flag_return;
			}
		}
		else
		{
			path_1 = 0;
		}
		//��· + �յ�֧·
		if(!end_zhilu_or_zonglu) //0:֧·
		{
			path_2 = zonglu_id;
			path_3 = 40+luzi_id;
			if(path_2)
			{
				if(!run_path(path_2,start_id,end_id,0,1))
				{
					flag_return = 0;
					return flag_return;		
				}		
			}

			if(!run_path(path_3,end_id,luzi_id,0,0))
			{
				flag_return = 0;
				return flag_return;		
			}			
			
		}
		else					//1:�յ�����·��
		{
			if(zonglu_id/10 == 3) 	//0:�� 3:��
			{
				path_3 = 30+luzi_id;
			}
			else if(zonglu_id/10 == 4)	//1:��	//4:��
			{
				path_3 = 40+luzi_id;
			}	
			
			path_2 = zonglu_id;
			if(path_2)
			{
				if(!run_path(path_2,start_id,end_id,0,2))
				{
					flag_return = 0;	
					return flag_return;		
				}
				if(!run_path(path_3,end_id,luzi_id,1,0)) 
				{
					flag_return = 0;
					return flag_return;		
				}			
			}
	//		else		//�ڵ�ǰ�� ִ������
	//		{
	//			path_3 = 40+luzi_id;
	//			//ѡ��·��
	//			HmiRouteNum = path_3;
	//			//��ȡ·������Ϣ
	//			GetRouteData(path_3);
	//			//��������յ��Ƿ��ڵ�ǰ·����
	//			if(NowRouteInfor[RouteStationNum[path_3-1]-1][5] == luzi_id)
	//			{
	//				GunTong_PLC(RouteStationNum[path_3-1]-1,NowRouteInfor[RouteStationNum[path_3-1]-1][3]);	
	//			}
	//			else
	//			{
	//				flag_return = 0;
	//				return flag_return;				
	//			}
	//		}
		}
	}	
	

	flag_return = 1;
	return flag_return;	
	

//��������ִ����� ��ʱ���û�������� �ͻ�ԭ��
//���������ԭ�صȴ�

}
//ʮλ�Ƕ�������λ��λ��[����1,����2][¯��ʵ�ʱ��]
//type: 0:PC����  1:������������
u8 AGV_run_path(u8 type,u8 path)
{
	u8 flag_goback=0;
	
	if(!type)
	{
		if(path/10 == 1)		//1:����
		{
			if(!get_path(g_AGV_Sta.juedui_RFID ,AGV_SYS.zhongzhuan_ID))//¯��   --> ��еץ��ID
			{
				flag_goback = 0;
				return flag_goback;
			}
			
			g_AGV_Sta.flag_fist_zhilu = 0;
			if(!get_path(g_AGV_Sta.juedui_RFID ,path%10))//��ǰ�� --> ¯��ID
			{
				flag_goback = 0;
				return flag_goback;
			}
				
		}
		else if(path/10 == 2)	//2:ȡ��
		{
			if(!get_path(g_AGV_Sta.juedui_RFID ,path%10))//��ǰ�� --> ¯��ID
			{
				flag_goback = 0;
				return flag_goback;			
			}	
			g_AGV_Sta.flag_fist_zhilu = 0;
			if(!get_path(g_AGV_Sta.juedui_RFID,AGV_SYS.zhongzhuan_ID))//¯��   --> ��еץ��ID
			{
				flag_goback = 0;
				return flag_goback;			
			}
				
		}	
	}
	else 
	{
		if(!get_path(g_AGV_Sta.juedui_RFID ,path))//��������
		{
			flag_goback = 0;
			return flag_goback;			
		}
			
		g_AGV_Sta.flag_fist_zhilu = 0;		
	}
	
	flag_goback = 1;
	return flag_goback;		

}




 









