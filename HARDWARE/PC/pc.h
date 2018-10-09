#ifndef _PC_H
#define _PC_H

#include "my_include.h"

//#define IDID pppp	


typedef struct
{
	u16 *Task_ID;			//任务编号	
	u16 *Task_Recived;		//收到任务
	u16 *Task_RunStart;		//开始执行
	u16 *Task_RunFinish;	//执行完成
	u16 *Position_Last;		//上一个位置
	u16 *Position_Now;		//当前位置
	u16 *Position_next;		//下一个位置
	u16 *RunState;			//运行状态
	u16 *Warning;			//报警信息
	u16 *guan_ID;			//炉管的ID

}dispatch_message;	//调度

typedef struct
{
	u16 *StoveID;						 //扩散炉炉号			
	u16 *Flag_Position_OK;            	 //AGV到指定位置		
	u16 *Flag_RecTray_Ready;          	 //AGV接收托盘准备就绪	
	u16 *Flag_RecTray_Finish;         	 //接收完成			
	u16 *AGV2PLC_Heard;					 //AGV给PLC的心跳1-60
	u16 *TO_PLC_Task_data;				 //给PLC当前工位任务信息

	u16 *Flag_DownTray_allowed;      	 //允许AGV出托盘		
	u16 *Flag_PLCRecTray_Finish;     	 //接托盘完成			
	u16 *Flag_RecTray_start;         	 //请求接收托盘	
	u16 *PLC2AGV_Heard;					 //PLC给AGV的心跳1-60(目前没使用)
	

}PLC_message;		//PLC炉子

typedef struct
{
	u16 *BatteryLevel;					  //电量			
	u16 *Voltage;                         //电压			
	u16 *BatteryCycleTimes;               //电池循环次数	
	u16 *LowPowerWarningVal;              //低电量报警阈值	
	u16 *SpeedClass;                      //当前速度档位	
	u16 *Run_Mode;                        //当前模式		
	u16 *Run_Direction;                   //当前方向		
	u16 *ForkingDirection;                //当前分叉方向	
	u16 *MagneticNavigation_1;            //磁导航数据1		
	u16 *MagneticNavigation_2;            //磁导航数据2		
	u16 *MagneticNavigation_3;            //磁导航数据3		
	u16 *MagneticNavigation_4;            //磁导航数据4		
	u16 *Sta_EmergencyStop;               //急停按钮状态	
	u16 *IR_Roller_L;                     //滚筒左侧红外	
	u16 *IR_Roller_R;                     // 滚筒右侧红外	
	u16 *RT_RFID;						  //实时地标
}RT_message;		//实时消息

extern u16 g_MessageCompare_buff[100];
extern dispatch_message 	g_dispatch_message;
extern PLC_message 			g_PLC_message[2];
extern RT_message 			g_RT_message;


//获取上位机的任务路径信息并执行
void Get_PC_data(u8 type_path,u16 *PC_data);
//跟上位机通信的底层数据发送函数
void CompareVal_Send(u8 start_num,u8 end_num);
//获取上位机需要的非实时性的AGV信息
void Get_PDO_Data(void);

void Get_SDO_Data(void);


//(位)正常0 机械碰撞1 出轨2 红外避障3 电量低4 驱动断电5 
void Get_Warning_data(void);



#endif







