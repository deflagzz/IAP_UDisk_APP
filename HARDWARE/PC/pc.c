#include "pc.h"

u16 g_MessageCompare_buff[100];

dispatch_message g_dispatch_message =
{
	&Dbus.Register[1],			//	u16 *Task_ID;			//任务编号	
	&Dbus.Register[2],			//	u16 *Task_Recived;		//收到任务
	&Dbus.Register[3],			//	u16 *Task_RunStart;		//开始执行
	&Dbus.Register[4],			//	u16 *Task_RunFinish;	//执行完成
	&Dbus.Register[5],			//	u16 *Position_Last;		//上一个位置
	&Dbus.Register[6],			//	u16 *Position_Now;		//当前位置
	&Dbus.Register[7],			//	u16 *Position_next;		//下一个位置
	&Dbus.Register[8],			//	u16 *RunCondition;		//运行状态
	&Dbus.Register[9],			//	u16 *Warning;			//报警信息
	&Dbus.Register[10],			//  炉管的ID
};

//默认AGV车号为1,对应炉子为扩散炉,寄存器地址为20到30
//	  AGV车号为2,对应炉子为PE炉  ,寄存器地址为31到41
PLC_message g_PLC_message[2] = 
{
	//扩散炉 -- AGV_ID:1 -- [0]
	//PE炉   -- AGV_ID:2 -- [1]
	{
		&Dbus.Register[20],			//u16 *StoveID;						 //扩散炉炉号			
		&Dbus.Register[21],			//u16 *Flag_Position_OK;             //AGV到指定位置		
		&Dbus.Register[22],			//u16 *Flag_RecTray_Ready;           //AGV接收托盘准备就绪	
		&Dbus.Register[23],			//u16 *Flag_RecTray_Finish;          //接收完成			
		&Dbus.Register[24],			//u16 *AGV2PLC_Heard;			     //AGV给PLC的心跳1-60
		&Dbus.Register[25],			//u16 *TO_PLC_Task_data;			 //给PLC当前工位任务信息
		
		&Dbus.Register[26],			//u16 *Flag_DownTray_allowed;      	 //允许AGV出托盘		
		&Dbus.Register[27],			//u16 *Flag_PLCRecTray_Finish;     	 //接托盘完成			
		&Dbus.Register[28],			//u16 *Flag_RecTray_start;         	 //请求接收托盘		
		&Dbus.Register[29],			//u16 *PLC2AGV_Heard;				 //PLC给AGV的心跳1-60(目前没使用)
	},
	{
		&Dbus.Register[31],			//u16 *StoveID;						 //扩散炉炉号			
		&Dbus.Register[32],			//u16 *Flag_Position_OK;             //AGV到指定位置		
		&Dbus.Register[33],			//u16 *Flag_RecTray_Ready;           //AGV接收托盘准备就绪	
		&Dbus.Register[34],			//u16 *Flag_RecTray_Finish;          //接收完成			
		&Dbus.Register[35],			//u16 *AGV2PLC_Heard;			     //AGV给PLC的心跳1-60		
		&Dbus.Register[36],			//u16 *TO_PLC_Task_data;			 //给PLC当前工位任务信息			

		&Dbus.Register[37],			//u16 *Flag_DownTray_allowed;      	 //允许AGV出托盘		
		&Dbus.Register[38],			//u16 *Flag_PLCRecTray_Finish;     	 //接托盘完成			
		&Dbus.Register[39],			//u16 *Flag_RecTray_start;         	 //请求接收托盘		
		&Dbus.Register[40],			//u16 *PLC2AGV_Heard;				 //PLC给AGV的心跳1-60(目前没使用)		
	
	}	
};

RT_message g_RT_message = 
{
	&Dbus.Register[51],			//u16 *BatteryLevel;					//电量			
	&Dbus.Register[52],			//u16 *Voltage;                         //电压			
	&Dbus.Register[53],			//u16 *BatteryCycleTimes;               //电池循环次数	
	&Dbus.Register[54],			//u16 *LowPowerWarningVal;              //低电量报警阈值	
	&Dbus.Register[55],			//u16 *SpeedClass;                      //当前速度档位	
	&Dbus.Register[56],			//u16 *Run_Mode;                        //当前模式		
	&Dbus.Register[57],			//u16 *Run_Direction;                   //当前方向		
	&Dbus.Register[58],			//u16 *ForkingDirection;                //当前分叉方向	
	&Dbus.Register[59],			//u16 *MagneticNavigation_1;            //磁导航数据1		
	&Dbus.Register[60],			//u16 *MagneticNavigation_2;            //磁导航数据2		
	&Dbus.Register[61],			//u16 *MagneticNavigation_3;            //磁导航数据3		
	&Dbus.Register[62],			//u16 *MagneticNavigation_4;            //磁导航数据4		
	&Dbus.Register[63],			//u16 *Sta_EmergencyStop;               //急停按钮状态	
	&Dbus.Register[64],			//u16 *IR_Roller_L;                     //滚筒左侧红外	
	&Dbus.Register[65],			//u16 *IR_Roller_R;                     // 滚筒右侧红外
	&Dbus.Register[66],			//u16 *RT_RFID;						    //实时地标
};






//获取上位机的任务路径信息并执行
void Get_PC_data(u8 type_path,u16 *PC_data)
{
	g_AGV_Sta.type_path = type_path;
	HmiTask = 1;								//选择执行路径									
	delay_rtos(0,0,0,10);
	AGV_SYS.ToPLC_task = *PC_data;
//	HmiRouteNum = *PC_data;						//路径号
//	delay_rtos(0,0,0,100);
//	HmiAutoReload();							//获取当前路径的站点信息
//	delay_rtos(0,0,0,100);
//	g_AGV_Sta.Car_dir = AGV_SYS.yuandian_dir; 	//方向切换到前进  
//	delay_rtos(0,0,0,100);
	HmiScreenSetGet = ZiDongJieMian;			//跳转到自动界面
	delay_rtos(0,0,0,10);
	g_AGV_Sta.Car_Auto2Manu_mode = 0;			//选择自动模式
	delay_rtos(0,0,0,10);
	

}




//跟上位机通信的底层数据发送函数
void CompareVal_Send(u8 start_num,u8 end_num)
{
	u8 temp_j=0;
	for(temp_j=start_num;temp_j<end_num+1;temp_j++)
	{
		//有区别发送
			//if(Dbus.Register[temp_j] != g_MessageCompare_buff[temp_j])		//跟比较数组比较,不相同的话发送并更新变化值
			//{
			//	if(Write_Register(0,temp_j,Dbus.Register[temp_j]))			//发送成功:1 失败:0
			//	{
			//		g_MessageCompare_buff[temp_j] = Dbus.Register[temp_j];	//更新变化到比较数组
			//	}
			//}
		//定时发送
			Post_Register(0,temp_j,Dbus.Register[temp_j]);
	}
}
//获取上位机需要的非实时性的AGV信息
void Get_PDO_Data(void)
{
	//
	//接收上位机的低电量阈值设置并存入flash
	//
	//if(*g_RT_message.LowPowerWarningVal != Battery_Warining.Warining_Val_NoBattery)
	//{
	//	Battery_Warining.Warining_Val_NoBattery = *g_RT_message.LowPowerWarningVal;
	//	SystemParameter[70] = Battery_Warining.Warining_Val_NoBattery;
	//	SetOneParameterToSystem(SystemParameter[70], 70);		
	//}
	
	
	*g_RT_message.BatteryLevel 			= 	Sys_battery;							 //百分比1-100	
	*g_RT_message.Voltage 				= 	g_battery.dianya;                        //单位：mV
	*g_RT_message.BatteryCycleTimes 	= 	g_battery.XunHuan_time;                  //数值
	*g_RT_message.LowPowerWarningVal 	= 	Battery_Warining.Warining_Val_NoBattery; //1-100
	*g_RT_message.SpeedClass            =	AGV_SYS.Auto_Speed_bili;                 //高速，中速，低速，对接速度
	*g_RT_message.Run_Mode              =	g_AGV_Sta.Car_Auto2Manu_mode;            //自动：0，手动：1
	*g_RT_message.Run_Direction         =	g_AGV_Sta.Car_dir;                       //前进：0，后退：1
	*g_RT_message.ForkingDirection      =	g_AGV_Sta.Car_fencha_dir;                //1:左分 2:右分 11:前左分 12:前右分 21:后左分 22:后右分
	*g_RT_message.MagneticNavigation_1  =	g_CT_bit[1];                             //16个点按位取点
	*g_RT_message.MagneticNavigation_2  =	g_u16_val[2];                            //16个点按位取点
	*g_RT_message.MagneticNavigation_3  =	g_CT_bit[3];                             //16个点按位取点
	*g_RT_message.MagneticNavigation_4  =	g_u16_val[4];                            //16个点按位取点
	*g_RT_message.Sta_EmergencyStop     =	!g_motec_init.Init_OK;                   //正常：0，急停：1
	*g_RT_message.IR_Roller_L           =   g_Senser_InPut.gunt_IR_L;                //正常：0，触发：1
	*g_RT_message.IR_Roller_R           =   g_Senser_InPut.gunt_IR_R;                //正常：0，触发：1
	*g_RT_message.RT_RFID				=   g_Get_RFID_buff[1]<<8|g_Get_RFID_buff[0];
}

void Get_SDO_Data(void)
{
	//if(g_RunSta.Run)
	//{
	//	*g_dispatch_message.RunState = 1;
	//}
	//if(g_RunSta.readyed)
	//{
	//	*g_dispatch_message.RunState = 2;
	//}
//	if(g_RunSta.chongdian)
//	{
//		*g_dispatch_message.RunState = 3;
//	}
//	if(!*g_dispatch_message.Warning)
//	{
//	
//	
//	}



}

void Bit2U16(u16 *warning,u8 bit_num,u8 set_val)
{
	if(set_val)
	{
		*warning |= (0x0001 << bit_num);
	}
	else
	{
		*warning &= ~(0x0001 << bit_num);
	}
}




//(位)正常0 机械碰撞1 出轨2 红外避障3 电量低4 驱动断电5 
void Get_Warning_data(void)			//获取AGV系统的警告信息--优先级尽量高
{
	//机械避障1
	if(g_Warning.jixie_qian || g_Warning.jixie_hou)
	{
		Bit2U16(g_dispatch_message.Warning,1,1);
		HmiTaskState = 2;					//前方障碍
	}
	else
	{
		Bit2U16(g_dispatch_message.Warning,1,0);
	}
	//磁条出轨2
	if(g_Warning.chugui)
	{
		Bit2U16(g_dispatch_message.Warning,2,1);
		HmiTaskState = 6;		
	}
	else
	{
		Bit2U16(g_dispatch_message.Warning,2,0);
	}
	//红外避障3
	if(g_Warning.IR_qian || g_Warning.IR_hou)
	{
		Bit2U16(g_dispatch_message.Warning,3,1);
		HmiTaskState = 2;					//前方障碍
	}
	else
	{
		Bit2U16(g_dispatch_message.Warning,3,0);
	}
	//电量低4
	if(g_Warning.Low_battery)
	{
		Bit2U16(g_dispatch_message.Warning,4,1);
	}
	else
	{
		Bit2U16(g_dispatch_message.Warning,4,0);
	}
	//驱动断电5
	if(g_Warning.Drive_NOPwoer)
	{
		Bit2U16(g_dispatch_message.Warning,5,1);
		g_user_stop_buttun = 1;
		HmiTaskState = 1;					
	}
	else
	{
		Bit2U16(g_dispatch_message.Warning,5,0);
		g_user_stop_buttun = 0;
	}
	//地标出错6
	if(g_Warning.RFID_err)
	{
		Bit2U16(g_dispatch_message.Warning,6,1);
		HmiTaskState = 3;
	}
	else
	{
		Bit2U16(g_dispatch_message.Warning,6,0);
	}

}















