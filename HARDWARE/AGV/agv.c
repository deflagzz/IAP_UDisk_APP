#include "agv.h"


//前进方向
//- 	    |			+
//-  		|			+
//-			|			+

//后退
//+ 	    |			-
//+  		|			-
//+			|			-


AGV_System AGV_SYS;

AGV_status g_AGV_Sta = 
{
	0,
	0,
	0,					//默认自动
	0,
};

 AGV_RunState g_RunSta;
 AGV_Warning  g_Warning;


void delay_rtos(u32 h,u32 m,u32 s,u32 ms)
{
	OS_ERR err;
	OSTimeDlyHMSM(h,m,s,ms,OS_OPT_TIME_HMSM_NON_STRICT,&err);	//OS_OPT_TIME_HMSM_NON_STRICT:延时不限大小
}





void UserConfigInit(void)
{

	W25QXX_Init();			//W25QXX初始化
	
	do
	{
		LED4 = !LED4;//DS0闪烁
		BEEP = !BEEP;
		delay_rtos(0,0,0,200);
	}while(W25QXX_ReadID()!=W25Q128);//检测不到W25Q128，LED闪烁
	LED4 = 1;
	BEEP = 0;
	delay_rtos(0,0,0,500);
    GetAllParameterFromSystem();		//获取所以的系统参数

    if(SystemParameter[0] != 5) 		//首次flash中没数据时或者意外导致数据丢失先刷入初始量
    {
#if 1									//为1	//车的前100个内存中写入初始量 -- 系统参数
        SystemParameter[0] = 5;			//判断是否第一次写入的标志
        SystemParameter[1] = 0;	
        SystemParameter[2] = 0;
        SystemParameter[3] = 4;			//手动速度比例 -- 4/10*3000
        SystemParameter[4] = 0; 
        SystemParameter[5] = 0; 		//充电模式 -- 掉电保存
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
        SystemParameter[24] = 0; 		//路径号
        SystemParameter[25] = 0; 		//
        SystemParameter[26] = 0; 		//
        SystemParameter[27] = 0; 		//
        SystemParameter[28] = 0; 		//
        SystemParameter[29] = 0; 		//
        SystemParameter[30] = 1;		//车号
        SystemParameter[31] = 3; 		//系统音量
        SystemParameter[32] = 1; 		//系统车速
        SystemParameter[33] = 0; 		//系统语音开关 -- 0:打开1:关闭
        SystemParameter[34] = 0; 		//车身状态灯   -- 0:打开1:关闭
        SystemParameter[35] = 300; 		//低速
        SystemParameter[36] = 800; 		//中速
        SystemParameter[37] = 1200; 	//高速
        SystemParameter[38] = 300; 		//工位对接速度
        SystemParameter[39] = 0;
        SystemParameter[40] = 800;	//寻正最大速度
        SystemParameter[41] = 35;	//电位器寻正速度比
        SystemParameter[42] = 600;	//磁条上轨速度
        SystemParameter[43] = 1200;	//电机最大速度
        SystemParameter[44] = 0;
        SystemParameter[45] = 0;	
        SystemParameter[46] = 0;
        SystemParameter[47] = 0;
        SystemParameter[48] = 0;
        SystemParameter[49] = 0;
        SystemParameter[50] = 40;	//自动Kp
        SystemParameter[51] = 80;   //自动Ki
        SystemParameter[52] = 0;	//自动Kd
        SystemParameter[53] = 30;	//手动Kp
        SystemParameter[54] = 60;	//手动Ki
        SystemParameter[55] = 0;	//手动Kd
        SystemParameter[56] = 10;	//PID控制时间
        SystemParameter[57] = 108;	//前轮左值
        SystemParameter[58] = 199;	//前轮中值
        SystemParameter[59] = 288;  //前轮右值

        SystemParameter[60] = 58; 	//后轮左值
        SystemParameter[61] = 145; 	//后轮中值
        SystemParameter[62] = 238; 	//后轮右值
        SystemParameter[63] = 0; 	//
        SystemParameter[64] = 0; 	//
        SystemParameter[65] = 0; 	//
        SystemParameter[66] = 0; 	//
        SystemParameter[67] = 0; 	//
        SystemParameter[68] = 0; 	//
        SystemParameter[69] = 0; 	//
        SystemParameter[70] = 15; 	//无电报警值
        SystemParameter[71] = 0; 	//
        SystemParameter[72] = 0; 	//
        SystemParameter[73] = 0; 	//
        SystemParameter[74] = 0; 	//
        SystemParameter[75] = 0; 	//
		SystemParameter[76] = 0; 	//
        SystemParameter[77] = 0;
        SystemParameter[78] = 0;
        SystemParameter[79] = 0;
        SystemParameter[80] = 0;	//近_红外开关 1:打开
        SystemParameter[81] = 0;	//远_红外开关 1:打开
        SystemParameter[82] = 1;	//前_机械开关 1:打开
        SystemParameter[83] = 1;	//后_机械开关 1:打开
        SystemParameter[84] = 0;	//原点方向 0:前进方向 1:后退方向
        SystemParameter[85] = 0;
        SystemParameter[86] = 0;
        SystemParameter[87] = 0;	
        SystemParameter[88] = 0;	//
        SystemParameter[89] = 0;
		SystemParameter[97] = 0; 	//客户计时
        SystemParameter[98] = 0; 
        SystemParameter[99] = 0; 
#endif
        //存储所有系统参数
        SetAllParameterToSystem();

#if 1
        //清除路径包含站点数
        memset(RouteStationNum, 0, RouteNum);
        //保存所有路径包含的站点数
        SetAllStationNum();

        //清除流程包含步数
        memset(ProcessStepNum, 0, ProcessNum);
        //保存所有流程包含的步数
        SetAllStepNum();
#endif
    }


	
//	
//系统参数更新到触摸屏上
//	
		
	
	//	
	//系统参数从Flash更新到系统中
	//				
	AGV_SYS.SD_Speed_bili       = 		  SystemParameter[3];	//手动速度比例 -- 4/10*3000
	g_RunSta.chongdian 			= 		  SystemParameter[5];	//充电模式标志 -- 掉电保存
	AGV_SYS.ID 					=         SystemParameter[30];	//车号
	AGV_SYS.yinliang			=         SystemParameter[31]; 	//系统音量
	AGV_SYS.Auto_Speed_bili		=         SystemParameter[32]; 	//自动运行速度的比例
	AGV_SYS.Key_yuyin 			=         SystemParameter[33]; 	//系统语音开关
	AGV_SYS.Key_RGB_LED 		=         SystemParameter[34]; 	//车身状态灯
	AGV_SYS.L_speed 			=         SystemParameter[35];  //低速
	AGV_SYS.M_speed 			=         SystemParameter[36];  //中速
	AGV_SYS.H_speed 			=         SystemParameter[37]; 	//高速
	AGV_SYS.duijie_speed 		=         SystemParameter[38]; 	//工位对接速度
		   
	AGV_SYS.XZ_MAX_Speed 		=         SystemParameter[40]; 	//寻正最大速度
	AGV_SYS.XZ_DWQ_Speed_bili	=         SystemParameter[41];	//电位器寻正速度比
	AGV_SYS.XZ_CiTiao_Speed 	=         SystemParameter[42]; 	//磁条上轨速度
	AGV_SYS.Motor_MAX_Speed 	=         SystemParameter[43];	//电机最大速度


	AGV_SYS.AUTO_Kp       		=		  SystemParameter[50];	//自动Kp
	AGV_SYS.AUTO_Ki        		=		  SystemParameter[51];  //自动Ki
	AGV_SYS.AUTO_Kd        		=		  SystemParameter[52];	//自动Kd
	AGV_SYS.SD_Kp       		=		  SystemParameter[53];	//手动Kp
	AGV_SYS.SD_Ki        		=		  SystemParameter[54];	//手动Ki
	AGV_SYS.SD_Kd        		=		  SystemParameter[55];	//手动Kd
	AGV_SYS.PID_time 			=         SystemParameter[56];	//PID控制时间

	g_DWQ.qianlun_L_val        	=		  SystemParameter[57];	//前轮左值
	g_DWQ.qianlun_zhong_val     =	      SystemParameter[58];	//前轮中值
	g_DWQ.qianlun_R_val        	=		  SystemParameter[59];  //前轮右值

	g_DWQ.houlun_L_val        	=		  SystemParameter[60]; 	//后轮左值
	g_DWQ.houlun_zhong_val    	=		  SystemParameter[61]; 	//后轮中值
	g_DWQ.houlun_R_val        	=		  SystemParameter[62]; 	//后轮右值
	AGV_SYS.add_time_yuzhi      = 		  SystemParameter[63];	//计时器
	AGV_SYS.yuandian_ID         = 		  SystemParameter[64];	//原点ID
	AGV_SYS.chongdian_ID        = 		  SystemParameter[65];	//充电ID
	AGV_SYS.zhongzhuan_ID       = 		  SystemParameter[66];	//中转台ID

	
	
	Battery_Warining.Warining_Val_NoBattery = SystemParameter[70];	//低电量报警值
	
	AGV_SYS.GunT_daozhong_time  =         SystemParameter[75];
	
	g_Senser_Enable.IR_qian_jin    	=		  SystemParameter[80]; 	//近红外开关
	g_Senser_Enable.IR_hou_jin    	=		  SystemParameter[80]; 	//近红外开关
	g_Senser_Enable.IR_qian_yuan    =		  SystemParameter[81]; 	//远红外
	g_Senser_Enable.IR_hou_yuan    	=		  SystemParameter[81]; 	//远红外
	g_Senser_Enable.jixie_qian    	=		  SystemParameter[82]; 	//前机械
	g_Senser_Enable.jixie_hou   	=		  SystemParameter[83]; 	//后机械
	AGV_SYS.yuandian_dir            = 		  SystemParameter[84];	//原点方向

	//
	//系统参数从Flash更新到触摸屏上
	//				
	g_shoudong_screen_speed     = 		  SystemParameter[3];	//手动速度比例 -- 4/10*3000
	g_Mode_chongdian			=		  SystemParameter[5];	//充电模式掉电保存
	g_AGV_ID 					=         SystemParameter[30];	//车号
	g_AGV_speaker_val 			=         SystemParameter[31]; 	//系统音量
	g_sys_set_agvSPEED			=         SystemParameter[32]; 	//系统车速 -- 自动
	g_AGV_speaker_key 			=         SystemParameter[33]; 	//系统语音开关
	g_AGV_LED_car_state			=         SystemParameter[34]; 	//车身状态灯
	HmiDiSu       				=         SystemParameter[35];  //低速
	HmiZhongSu     				=         SystemParameter[36];  //中速
	HmiGaoSu      				=         SystemParameter[37]; 	//高速
	g_AGV_speed_duijie			=         SystemParameter[38]; 	//工位对接速度
			   	   
	XZ_Speed40					=         SystemParameter[40]; 	//寻正最大速度
	XZ_Speed41					=         SystemParameter[41];	//电位器寻正速度比
	XZ_Speed42					=         SystemParameter[42]; 	//磁条上轨速度
	XZ_Speed43					=         SystemParameter[43];	//电机最大速度

	g_screen_Auto_Kp			=		  SystemParameter[50];	//自动Kp
	g_screen_Auto_Ki			=		  SystemParameter[51];  //自动Ki
	g_screen_Auto_Kd			=		  SystemParameter[52];	//自动Kd
	g_screen_Manu_Kp			=		  SystemParameter[53];	//手动Kp
	g_screen_Manu_Ki			=		  SystemParameter[54];	//手动Ki
	g_screen_Manu_Kd			=		  SystemParameter[55];	//手动Kd
	g_screen_control_TIME		=         SystemParameter[56];	//PID控制时间

	g_screen_qianlun_ZuoZhi		=		  SystemParameter[57];	//前轮左值
	g_screen_qianlun_ZhongZhi	=	      SystemParameter[58];	//前轮中值
	g_screen_qianlun_YouZhi		=		  SystemParameter[59];  //前轮右值

	g_screen_houlun_ZuoZhi		=		  SystemParameter[60]; 	//后轮左值
	g_screen_houlun_ZhongZhi 	=		  SystemParameter[61]; 	//后轮中值
	g_screen_houlun_YouZhi 		=		  SystemParameter[62]; 	//后轮右值
	g_add_time                  = 		  SystemParameter[63];	//计时器
	g_yuandi_ID                 = 		  SystemParameter[64];	//
	g_chongdian_ID              = 		  SystemParameter[65];	//	
	g_zhongzhuan_ID				= 		  SystemParameter[66];	
	
	Li_Warning_val_NoBattery 	= 		  SystemParameter[70];	//低电量报警值
	
	GunT_zhong_time  			=         SystemParameter[75];

	g_AGV_Enable_IR_jin      	=		  SystemParameter[80]; 	//近红外开关
	g_AGV_Enable_IR_yuan        =		  SystemParameter[81]; 	//远红外
	g_AGV_Enable_JiXie_qian    	=		  SystemParameter[82]; 	//前机械
	g_AGV_Enable_JiXie_hou   	=		  SystemParameter[83]; 	//后机械
	g_AGV_yuandian_dir          = 		  SystemParameter[84]; 	//原点初始方向
	
	
	//遥控器控制参数载入
	g_AGV_yaokong.jiaodu_Max		= 50;	//最大极限角度:中值+-70度
	g_AGV_yaokong.GunTong_chufa_val = 50;	//摇杆推到中间50
	g_AGV_yaokong.Start_chufa_val   = 15;	//前后启动触发
	
	
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
	PrintCom(YIN_SU4,9);osdelay_ms(10);		//语速4
	PrintCom(YIN_DIAO5,9);osdelay_ms(10);	//语调4		

//
//加载自动界面信息
//
    //HmiAutoReload();


    //获取路径包含站点数
    GetRouteStationNum(HmiRouteNum);

    //获取当前路径信息
    GetRouteData(HmiRouteNum);
	
    //获取及更新流程数据
    GetProcessData();
	
	g_AGV_Sta.Flash_get_OK = 1;
}


	




















//AGV_station agv_routr2station[StationNum];		//



//执行站点动作
void StationAction(u16 num)
{
	u16 buff_speed=0;
	u16 set_speed=0;
	u8  flag_stop=0;
	
	
    while(g_AGV_Sta.Car_Auto2Manu_mode  || !g_Start_flag.Start_Auto_PID )	 //非启动或者非自动
    {
        osdelay_ms(10); 
    }

	
    HmiStationSerialNum++;
    //清空地标
    g_AGV_RFID_ID = 0;
	memset(g_CDH_add_num,0,sizeof(g_CDH_add_num));	//清空磁导航虚拟地标的计数

    //目标地标显示
    HmiNextRfidNum = NowRouteInfor[num][5];								//4x90
	
	//GetRFIDbuff(g_AGV_RFID_ID,g_dispatch_message.Position_Last,g_dispatch_message.Position_Now,g_dispatch_message.Position_next,num);

	//等待目标地标
    while(g_AGV_RFID_ID != NowRouteInfor[num][5])	//扫到地标，是目标值的话则跳出while
    {
        if(!g_AGV_Sta.Car_Auto2Manu_mode)//自动模式下检测地标
        {
			            //地标类型 1:实体 0:虚拟
			if(NowRouteInfor[num][18])			//实体地标
			{
				if(g_AGV_RFID_ID && (g_AGV_RFID_ID != g_AGV_Sta.RFID_buff[0]))			//读到地标值
				{
					if(g_AGV_RFID_ID != NowRouteInfor[num][5])	//不是目标值,跳出循环
					{
						break;
					}

				}
			}			
            //虚拟地标检测	
			else								//虚拟地标
			{
				if(NowRouteInfor[num][15])	//分叉地标
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
				else						//普通地标
				{
					if(NowRouteInfor[num][7] && g_CDH_add_num[1] == NowRouteInfor[num][11] )	//前驱动单元触发
					{
						g_AGV_RFID_ID = NowRouteInfor[num][5];
					}
					

					if(NowRouteInfor[num][9] && g_CDH_add_num[3] == NowRouteInfor[num][13])		//后驱动单元触发
					{
						g_AGV_RFID_ID = NowRouteInfor[num][5];
					}	
					
				}
				if(g_AGV_RFID_ID)			//读到地标值
				{
					if(g_AGV_RFID_ID != NowRouteInfor[num][5])	//不是目标值,跳出循环
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

		Ting_Zhi();						//地标读取出错,停车
		HmiTaskState = 3;				//地标异常
		g_Warning.RFID_err = 1;			//地标出错
		while(1)
		{
			g_AGV_speaker_flag.RFID_READ_err = 1;
			delay_rtos(0,0,0,1500);		
		}
	}
	else								//地标读取正确
	{
		g_Warning.RFID_err = 0;			//地标正常
		g_AGV_Sta.juedui_RFID = g_AGV_RFID_ID;
		HmiRfidNum = g_AGV_RFID_ID;		//监测到地标后更新当前地标				//4x130
		g_shoudong_screen_RFID = g_AGV_Sta.juedui_RFID; //更新当前地标	
		
		GetRFIDbuff(g_AGV_RFID_ID,g_dispatch_message.Position_Last,g_dispatch_message.Position_Now,g_dispatch_message.Position_next,num);

		switch(NowRouteInfor[num][6])	//停止、前进、后退左、后退右、左旋、右旋
		{
			case 0:
				break;	//通过
			case 1:		//停止
			case 2:		//前进	
			case 3:		//后退
				Ting_Zhi();			//到站停止	
				flag_stop = 1;		
				break;
			case 4:		//车头方向
			{
				if(g_AGV_Sta.Car_dir == 1)
				{
					Ting_Zhi();			//到站停止	
					flag_stop = 1;					
				}			
			}
				break;
			case 5:		//车尾方向
			{
				if(g_AGV_Sta.Car_dir == 0)
				{
					Ting_Zhi();			//到站停止	
					flag_stop = 1;					
				}			
			}				
				break;
			default:
				break;
		}

		
		if(flag_stop == 0)  
		{
			//后退的分叉改
			if(NowRouteInfor[num][18])		//实体地标
			{
				switch(NowRouteInfor[num][2])//分叉判断
				{
					case 0:
						break;//保持上次信息
					case 1://左分叉
					{
						Zuo_Fen();	//00111100
					}
					break;
					case 2://右分叉
					{
						You_Fen();
					}
					break;
					case 3://直行
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
			//到站延时
			if(NowRouteInfor[num][1] > 0)
			{
				if(NowRouteInfor[num][1] > 9999)
				{
					NowRouteInfor[num][1] = 9999;
				}
				delay_rtos(0,0,0,NowRouteInfor[num][1]);	//最大9999
			}		
		
		
		}
				
		
		
			
		
	
		
		buff_speed = AGV_SYS.Car_Auto_Speed;			//缓存速度
		switch(NowRouteInfor[num][4])//速度档位判断
		{
			case 0:
				set_speed = buff_speed;
				break;//保持上次信息
			case 1://低速
			{			
				set_speed = HmiDiSu;
			}
			break;
			case 2://中速
			{
				set_speed = HmiZhongSu;
			}
			break;
			case 3://高速
			{
				set_speed = HmiGaoSu;
			}
			break;
			case 4://对接低速
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
		
		switch(NowRouteInfor[num][0])//远程红外
		{
			case 0:
				break;//保持上次信息
			case 1://开
			{
				g_Senser_Enable.IR_qian_yuan = 1;
				g_Senser_Enable.IR_hou_yuan  = 1;
				
	//			speek("远红外打开");
	//			osdelay_ms(g_Speaker_delay);
				
			}
			break;
			case 2://关
			{
				g_Senser_Enable.IR_qian_yuan = 0;
				g_Senser_Enable.IR_hou_yuan  = 0;
				
	//			speek("远红外关闭");
	//			osdelay_ms(g_Speaker_delay);

			}
			break;
		}
		switch(NowRouteInfor[num][19])//近程红外
		{
			case 0:
				break;//保持上次信息
			case 1://开
			{
				g_Senser_Enable.IR_qian_jin = 1;
				g_Senser_Enable.IR_hou_jin  = 1;
	//			
	//			speek("近红外打开");
	//			osdelay_ms(g_Speaker_delay);
			}
			break;
			case 2://关
			{
				g_Senser_Enable.IR_qian_jin = 0;
				g_Senser_Enable.IR_hou_jin  = 0;
				
	//			speek("近红外关闭");
	//			osdelay_ms(g_Speaker_delay);
			}
			break;
		}

		
		GunTong_PLC(num,NowRouteInfor[num][3]); //滚筒动作

	//@@
	//备用接口
	//	
	#if 0
		//判断是否需要延时
		if(NowRouteInfor[num][8]!=0)
			osdelay_s(NowRouteInfor[num][8]);

		switch(NowRouteInfor[num][11])//与机械手设备通信
		{
		case 0:
			//没有请求进入
			PLC2_Data[32] = 0;
			break;//没有与设备交互
		case 1://和一号设备交互
		{
			Ting_Zhi();
			//向设备发送请求进入信号
			PLC2_Data[32] = NowRouteInfor[num][11];
			g_AGV_Status.Car_Speaker_flag = 22; //请求进入语音
			//等待准入信号
			while(PLC2_Data[33] != 1)
			{
				osdelay_ms(10);
			}
			Qi_Dong();
			g_AGV_Status.Car_Speaker_flag = 23; //允许进入语音
			//清除请求进入信号
			PLC2_Data[32] = 0;
			//清空准入信号
			PLC2_Data[33] = 0;
		}
		break;
		case 2://和二号设备交互
		{
			Ting_Zhi();
			//向设备发送请求进入信号
			PLC2_Data[32] = NowRouteInfor[num][11];
			g_AGV_Status.Car_Speaker_flag = 22; //请求进入语音
			//等待准入信号
			while(PLC2_Data[34] != 1)
			{
				osdelay_ms(10);
			}
			Qi_Dong();
			g_AGV_Status.Car_Speaker_flag = 23; //允许进入语音

			//清除请求进入信号
			PLC2_Data[32] = 0;
			//清空准入信号
			PLC2_Data[34] = 0;
		}
		break;
		case 3://和三号设备交互
		{
			Ting_Zhi();
			//向设备发送请求进入信号
			PLC2_Data[32] = NowRouteInfor[num][11];
			g_AGV_Status.Car_Speaker_flag = 22; //请求进入语音
			//等待准入信号
			while(PLC2_Data[35] != 1)
			{
				osdelay_ms(10);
			}
			Qi_Dong();
			g_AGV_Status.Car_Speaker_flag = 23; //允许进入语音

			//清除请求进入信号
			PLC2_Data[32] = 0;
			//清空准入信号
			PLC2_Data[35] = 0;
		}
		break;
		case 4://和四号设备交互
		{
			Ting_Zhi();
			//向设备发送请求进入信号
			PLC2_Data[32] = NowRouteInfor[num][11];
			g_AGV_Status.Car_Speaker_flag = 22; //请求进入语音
			//等待准入信号
			while(PLC2_Data[36] != 1)
			{
				osdelay_ms(10);
			}
			Qi_Dong();
			g_AGV_Status.Car_Speaker_flag = 23; //允许进入语音
			//清除请求进入信号
			PLC2_Data[32] = 0;
			//清空准入信号
			PLC2_Data[36] = 0;
		}
		break;
		}

		switch(NowRouteInfor[num][7])//进入设备工作区
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


		//AGV对电梯的使用情况
		switch(NowRouteInfor[num][10])
		{
		case 0:
			break;//电梯不使用
		case 1://AGV去一楼
		{
			AGV_QuYiLou();
		}
		break;
		case 2://AGV去三楼
		{
			AGV_QuSanLou();
		}
		break;
		}
	#endif
	//
	//备用接口
	//@@	

		switch(NowRouteInfor[num][6])//动作执行再判断	//到站动作	 0：保持	1：停止	2:前进	3：工位对接  4：后退 
		{
			case 0:
				break;//通过
			case 1:
				break;//停止
			case 2://前进
			{
				g_AGV_Sta.Car_dir = g_AGV_Sta.Car_dir;
				//Qi_Dong();			
				
			}
				break;		
			case 3://后退
			{
				g_AGV_Sta.Car_dir = !g_AGV_Sta.Car_dir;
				Qi_Dong();
			}
				break;
			case 4://车头方向
			{
				if(g_AGV_Sta.Car_dir)
				{
					g_AGV_Sta.Car_dir = 0;
					Qi_Dong();				
				}

			}
				break;
			case 5://车尾方向
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
		
		if(flag_stop == 1) //后退
		{
			if(NowRouteInfor[num][18])		//实体地标
			{
				switch(NowRouteInfor[num][2])//分叉判断
				{
					case 0:
						break;//保持上次信息
					case 1://左分叉
					{
						Zuo_Fen();	//00111100
					}
					break;
					case 2://右分叉
					{
						You_Fen();
					}
					break;
					case 3://直行
					{
						ZhiXing();
					}
					break;
				}	
			}		
		
		}
	}	 
}





//执行流程
void ActiveProcess(void)
{
    //保存流程号
    SetOneParameterToSystem(HmiProcessNum, 25);
    SystemParameter[26] = HmiTask;
    //保存任务号
    SetOneParameterToSystem(HmiTask, 26);

    //任务状态为正在运行
    HmiTaskState = 5;

    HmiTask = 2;

    //加载自动界面信息
    HmiAutoReload();

    g_AGV_Sta.Car_dir = AGV_SYS.yuandian_dir; //方向切换到前进

    //跳转到自动界面
    HmiScreenSetGet = ZiDongJieMian;
}



u16 u8_to_u16(u8 *H_Bit,u8 *L_Bit)
{
	u16 temp_out=0;
	temp_out = *H_Bit;
	temp_out = temp_out<<8|*L_Bit;

	return temp_out;
}


u16 g_LastCDH_buff[5];		//上次历史值	   -- 4个磁导航的值
u8  g_CDH_add_num[5];		//磁导航突变累加值 -- 前后两个驱动单元的值 [0]:前驱动 [2]:后驱动
//驱动单元上的两个磁导航同时全亮才算一次突变触发
void CDH_ADD(u16 *last_data,u16 *buff,u8 *cdh_add_num_buff)
{
	u8 temp_i=0;
	for(temp_i=1;temp_i<5;temp_i+=2)
	{
		if(last_data[temp_i] || last_data[temp_i+1])
		{
			if( buff[temp_i] == 0x0000 && buff[temp_i+1] == 0x0000)
			{
				osdelay_ms(10);//延时消抖
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

//1:左分叉  2:右分叉 
//虚拟分叉地标--11:前轮左分叉 12:前轮右分叉  21:后轮左分叉 22:后轮右分叉
//0:前轮 1:后轮
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

void GunTong_PLC(u16 num,u16 type) //0:	//不转  1://左侧操作  2://右侧操作
{
	switch(type)//滚筒动作
	{
		case 0:	//不转
			break;
		case 1://左侧操作
		{
			g_RunSta.roller = 1;	//输送状态
			*g_PLC_message[AGV_SYS.ID-1].StoveID = NowRouteInfor[num][8];	//AGV告诉PLC需要通信的炉子ID 
			*g_PLC_message[AGV_SYS.ID-1].Flag_Position_OK 	= 1;			//AGV告诉PLC到达指定位置
			
			//告诉PLC当前工位任务信息 1:送舟 2:取舟
			if(*g_PLC_message[AGV_SYS.ID-1].StoveID == AGV_SYS.zhongzhuan_ID)		//机械抓手
			{
				if(AGV_SYS.ToPLC_task/10 == 1)
				{
					*g_PLC_message[AGV_SYS.ID-1].TO_PLC_Task_data = 2;		//取舟
				}
				else if(AGV_SYS.ToPLC_task/10 == 2)
				{
					*g_PLC_message[AGV_SYS.ID-1].TO_PLC_Task_data = 1;		//送舟
				}
				
			}
			else
			{
				if(*g_PLC_message[AGV_SYS.ID-1].StoveID==1||*g_PLC_message[AGV_SYS.ID-1].StoveID==2||*g_PLC_message[AGV_SYS.ID-1].StoveID==3||*g_PLC_message[AGV_SYS.ID-1].StoveID==4||NowRouteInfor[num][8]==5)
				{
					*g_PLC_message[AGV_SYS.ID-1].TO_PLC_Task_data = AGV_SYS.ToPLC_task / 10;	//取舟
				}				
			}




			
			
			g_AGV_speaker_flag.Down_L = 1;
			delay_rtos(0,0,0,20);
			GunTong_Trun_L_DOWN();
			
			g_AGV_speaker_flag.UP_L = 1;
			delay_rtos(0,0,0,20);
			GunTong_Trun_L_UP();
			
			*g_PLC_message[AGV_SYS.ID-1].StoveID = 0;						//AGV告诉PLC需要通信的炉子ID 
			*g_PLC_message[AGV_SYS.ID-1].Flag_Position_OK 	 = 0;			//AGV告诉PLC到达指定位置				
			//告诉PLC当前工位任务信息 1:送舟 2:取舟
			*g_PLC_message[AGV_SYS.ID-1].TO_PLC_Task_data    = 0;
			*g_PLC_message[AGV_SYS.ID-1].Flag_RecTray_Ready  = 0;			//AGV告诉PLC接收托盘准备就绪
			*g_PLC_message[AGV_SYS.ID-1].Flag_RecTray_Finish = 0;			//AGV告诉PLC托盘接收完成
			g_RunSta.roller = 0;	//非输送状态
		}
		break;
		case 2://右侧操作
		{
			g_RunSta.roller = 1;	//输送状态
			*g_PLC_message[AGV_SYS.ID-1].StoveID = NowRouteInfor[num][8];	//AGV告诉PLC需要通信的炉子ID 
			*g_PLC_message[AGV_SYS.ID-1].Flag_Position_OK 	= 1;			//AGV告诉PLC到达指定位置
			
			//告诉PLC当前工位任务信息 1:送舟 2:取舟
			if(*g_PLC_message[AGV_SYS.ID-1].StoveID == AGV_SYS.zhongzhuan_ID)		//机械抓手
			{
				if(AGV_SYS.ToPLC_task/10 == 1)
				{
					*g_PLC_message[AGV_SYS.ID-1].TO_PLC_Task_data = 2;		//取舟
				}
				else if(AGV_SYS.ToPLC_task/10 == 2)
				{
					*g_PLC_message[AGV_SYS.ID-1].TO_PLC_Task_data = 1;		//送舟
				}
				
			}
			else
			{
				if(*g_PLC_message[AGV_SYS.ID-1].StoveID==1||*g_PLC_message[AGV_SYS.ID-1].StoveID==2||*g_PLC_message[AGV_SYS.ID-1].StoveID==3||*g_PLC_message[AGV_SYS.ID-1].StoveID==4||NowRouteInfor[num][8]==5)
				{
					*g_PLC_message[AGV_SYS.ID-1].TO_PLC_Task_data = AGV_SYS.ToPLC_task/10;	//取舟
				}			
			}



			
			g_AGV_speaker_flag.Down_R = 1;
			delay_rtos(0,0,0,20);
			GunTong_Trun_R_DOWN();
			g_AGV_speaker_flag.UP_R = 1;
			delay_rtos(0,0,0,20);
			GunTong_Trun_R_UP();
			
			*g_PLC_message[AGV_SYS.ID-1].StoveID = 0;						//AGV告诉PLC需要通信的炉子ID 
			*g_PLC_message[AGV_SYS.ID-1].Flag_Position_OK 	 = 0;			//AGV告诉PLC到达指定位置				
			//告诉PLC当前工位任务信息 1:送舟 2:取舟
			*g_PLC_message[AGV_SYS.ID-1].TO_PLC_Task_data    = 0;				
			*g_PLC_message[AGV_SYS.ID-1].Flag_RecTray_Ready  = 0;			//AGV告诉PLC接收托盘准备就绪
			*g_PLC_message[AGV_SYS.ID-1].Flag_RecTray_Finish = 0;			//AGV告诉PLC托盘接收完成	
			g_RunSta.roller = 0;	//非输送状态				
		}
		break;
		//case 3://左侧装货
		//{
		//	g_AGV_speaker_flag.UP_L = 1;
		//	GunTong_Trun_L_UP();
		//}
		//break;	
		
		//case 4://右侧装货
		//{
		//	g_AGV_speaker_flag.UP_R = 1;
		//	GunTong_Trun_R_UP();
		//}		
		//break;
		default:
			break;

	}
}
void AGV_LED(void)			//AGV行车灯
{
	Car_LED_Blue 	 =1;
	//Car_LED_Yellow =1;
	
	Car_LED_Qian_Enable	 = 0;
	Car_LED_Hou_Enable   = 0;
	while(1)
	{
		if(!AGV_SYS.Key_RGB_LED)
		{
			//行走和停止的状态灯
			if(g_Start_flag.Start_Manu_PID || g_Start_flag.Start_Auto_PID)		
			{
				Car_LED_Blue 	= 1 ;				//亮50ms
				delay_rtos(0,0,0,100);
				Car_LED_Blue 	= 0 ;				//灭2秒
				delay_rtos(0,0,0,100);
				Car_LED_Blue 	= 1 ;				//亮50ms
				delay_rtos(0,0,0,100);
				Car_LED_Blue 	= 0 ;				//灭2秒
				delay_rtos(0,0,0,100);	
				delay_rtos(0,0,0,1500);		

			}
			else		//停止 -- 蓝灯慢闪
			{
				Car_LED_Blue 	= 1 ;				//亮50ms
				delay_rtos(0,0,0,500);
				Car_LED_Blue 	= 0 ;				//灭2秒
				delay_rtos(0,0,0,2000);
			
			}
			
			
			//红外和机械避障的状态灯
			if(!g_Start_flag.Start_IR || !g_Start_flag.button_bizhang_Start)	//停止
			{
				Car_LED_Yellow = 1;			//黄灯闪烁
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


void AGV_Auto_speed(u16* buff_speed,u16 *true_speed,u8 Car_dir)	//参考速度
{
	static u8 flag_i=0;
	if(Car_dir == 0 && g_Senser_InPut.IR_qian_yuan)				//前进方向
	{	
		if(!flag_i)
		{			
			*buff_speed = *true_speed;
			Ruan_jian(*buff_speed,*buff_speed/2,true_speed);
			flag_i = 1;	
		}	
	}
	else if(Car_dir == 1 && g_Senser_InPut.IR_hou_yuan)			//后退方向			
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
void AGV_Manu_speed(u16 now_speed,u16 *true_speed,u8 Car_dir)	//参考速度
{
	u8 temp_vel = 6;	//10
	static u8 flag_i=0;
	if(Car_dir == 0 && g_Senser_InPut.IR_qian_yuan)				//前进方向
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
	else if(Car_dir == 1 && g_Senser_InPut.IR_hou_yuan)			//后退方向			
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


//manu: 0:自动寻找 1:手动放在支路
//返回值: 0:当前站点在支路上,1:当前站点在总路上
u8 zhilu2zonglu(u8 manu,u8 in_or_out,u16 now_id,u16* zonglu_id)
{
	u8 i=0;
	u8 flag_getAGV_in_way=0;
	u8 num_route=0;
	u8 zhilu_id=0;
	u8 flag_zhilu_or_zonglu=0;
	
	if(manu)	//1:手动放在支路
	{
		flag_getAGV_in_way = 0;
	
	}
	else		//0:自动寻找
	{	
		//获取主干道路径的信息
		GetRouteData(main_way_L2R_ID);	
		//检测agv是否在主干道上
		for(i=0;i<RouteStationNum[main_way_L2R_ID-1];i++)
		{
			if(now_id == NowRouteInfor[i][5])
			{
				flag_getAGV_in_way = 1;
			}	
		}		
	}


	//不在主干道,先行驶到主干道上
	if(!flag_getAGV_in_way)
	{
		if(!in_or_out) //0:出,
		{
			zhilu_id = 30+now_id;
		}
		else 			//1:进
		{
			zhilu_id = 40+now_id;
		}
		flag_zhilu_or_zonglu = 0;
		num_route = GetRouteStationNum(zhilu_id); 	//获取当前支路的站点总数
		GetRouteData(zhilu_id);				  		//获取当前支路的站点信息
		
		if(!in_or_out) //0:出,1:进
		{
			zhilu_id = 30+now_id;
			*zonglu_id = NowRouteInfor[num_route-1][5];	//获取当前支路的最后一个站点号		luzi_id/10

		}
		else 
		{
			zhilu_id = 40+now_id;
			*zonglu_id = NowRouteInfor[0][5];	//获取当前支路的第一个站点号		luzi_id/10
			
		}			
	}
	//在主干道上
	else
	{
		flag_zhilu_or_zonglu = 1;
		*zonglu_id = now_id;
	}
	return flag_zhilu_or_zonglu;
}

//__num :末尾数减几,运行至末尾数减几为止
u8 run_path(u8 path_id,u8 start_id,u8 end_id,u8 start_num,u8 __num) 
{
	u8 i=0;
	u8 flag_start=0;
	u8 flag_end=0;
	u8 num_start=0;
	u8 num_end=0;
	u8 flag_return=0;
	
	//选择路径
	HmiRouteNum = path_id;
	//获取路径的信息
	GetRouteData(path_id);
	//检测起点和终点是否在当前路径上
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
		if(!g_Start_flag.Start_Auto_PID) //从停止到启动才切换方向
		{
			//4:车头方向 5:车尾方向
			if(NowRouteInfor[num_start+1][6] == 4) //下一个地标的方向
			{
					g_AGV_Sta.Car_dir = 0; 	//方向切换到前进  						
			}
			else if(NowRouteInfor[num_start+1][6] == 5)
			{
				g_AGV_Sta.Car_dir = 1; 	//方向切换  //这里			
			}
			//给启动信号
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



//十位是动作，个位是位置[出3,进4][炉子实际编号] 
//必须在工位上接收新的任务 1--6

//十位是动作，个位是位置[放舟1,接舟2][炉子实际编号]
//主干道的路径号:8
//start_typ 0:自动寻 1:手动放在之路上
u8 get_path(u16 now_id,u16 luzi_id) //目标:炉子ID
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
	
	//1.确定起点的支路路径:agv是否在主干道上,不在的话先行驶至主干道 
	//2.确定到终点目标id的支路路径 
	//3.根据起点跟终点的坐标确定主干道的路径 
	//4.拼装三条路径,形成一个流程
	
	if(now_id == luzi_id)
	{
		path_1 = 0;
		path_2 = 0;
		path_3 = 40+luzi_id;
		//选择路径
		HmiRouteNum = path_3;
		//获取路径的信息
		GetRouteData(path_3);
		//检测起点和终点是否在当前路径上
		if(NowRouteInfor[RouteStationNum[path_3-1]-1][5] == luzi_id)
		{
			GunTong_PLC(RouteStationNum[path_3-1]-1,NowRouteInfor[RouteStationNum[path_3-1]-1][3]);	
			//到站延时
			if(NowRouteInfor[RouteStationNum[path_3-1]-1][1] > 0)
			{
				if(NowRouteInfor[RouteStationNum[path_3-1]-1][1] > 9999)
				{
					NowRouteInfor[RouteStationNum[path_3-1]-1][1] = 9999;
				}
				delay_rtos(0,0,0,NowRouteInfor[RouteStationNum[path_3-1]-1][1]);	//最大9999
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
		//确定起点坐标
		start_zhilu_or_zonglu = zhilu2zonglu(0,0,now_id,&start_id); 			
		//确定终点坐标							
		end_zhilu_or_zonglu = zhilu2zonglu(0,0,luzi_id,&end_id);		
		//由起点坐标跟终点坐标确定总路的路径号 	
		//从左往右如果先找到起点的坐标并且从右往左先找到终点坐标,
		//说明总路的路径号为38(从左到右),		
		//反之总路的路径号为48(从右往左) 		
		
		

		//获取从左往右的主干道路径的信息
		GetRouteData(main_way_L2R_ID);	
		//检测起点和终点坐标在总路上的第几个位置
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
		//如果起始点都在总路上,起点支路+总路+终点支路
		if(start_num && end_num)
		{
			//起点支路+总路+终点支路
			if(start_num < end_num)
			{
				zonglu_id = main_way_L2R_ID; 	//38
			}
			//起点支路+总路+终点支路
			else if(start_num > end_num) 
			{
				zonglu_id = main_way_R2L_ID; 	//48
			}
			//两条支路有交点,直接两个支路拼接zonglu_id=0
			else if(start_num == end_num) 
			{
				zonglu_id = 0; 
			}		
		}


		//把起点跟终点换成拼接的支路总路路径

		
		
		//起点支路
		if(!start_zhilu_or_zonglu) //0:支路
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
		//总路 + 终点支路
		if(!end_zhilu_or_zonglu) //0:支路
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
		else					//1:终点在总路上
		{
			if(zonglu_id/10 == 3) 	//0:出 3:出
			{
				path_3 = 30+luzi_id;
			}
			else if(zonglu_id/10 == 4)	//1:入	//4:入
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
	//		else		//在当前点 执行任务
	//		{
	//			path_3 = 40+luzi_id;
	//			//选择路径
	//			HmiRouteNum = path_3;
	//			//获取路径的信息
	//			GetRouteData(path_3);
	//			//检测起点和终点是否在当前路径上
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
	

//所有任务执行完毕 延时多久没有新任务 就回原地
//有新任务就原地等待

}
//十位是动作，个位是位置[放舟1,接舟2][炉子实际编号]
//type: 0:PC任务  1:其他单个任务
u8 AGV_run_path(u8 type,u8 path)
{
	u8 flag_goback=0;
	
	if(!type)
	{
		if(path/10 == 1)		//1:放舟
		{
			if(!get_path(g_AGV_Sta.juedui_RFID ,AGV_SYS.zhongzhuan_ID))//炉子   --> 机械抓手ID
			{
				flag_goback = 0;
				return flag_goback;
			}
			
			g_AGV_Sta.flag_fist_zhilu = 0;
			if(!get_path(g_AGV_Sta.juedui_RFID ,path%10))//当前点 --> 炉子ID
			{
				flag_goback = 0;
				return flag_goback;
			}
				
		}
		else if(path/10 == 2)	//2:取舟
		{
			if(!get_path(g_AGV_Sta.juedui_RFID ,path%10))//当前点 --> 炉子ID
			{
				flag_goback = 0;
				return flag_goback;			
			}	
			g_AGV_Sta.flag_fist_zhilu = 0;
			if(!get_path(g_AGV_Sta.juedui_RFID,AGV_SYS.zhongzhuan_ID))//炉子   --> 机械抓手ID
			{
				flag_goback = 0;
				return flag_goback;			
			}
				
		}	
	}
	else 
	{
		if(!get_path(g_AGV_Sta.juedui_RFID ,path))//单个任务
		{
			flag_goback = 0;
			return flag_goback;			
		}
			
		g_AGV_Sta.flag_fist_zhilu = 0;		
	}
	
	flag_goback = 1;
	return flag_goback;		

}




 









