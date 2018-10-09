#ifndef _AGV_H
#define _AGV_H

#include "my_include.h"

#define main_way_L2R_ID 38	//左到右
#define main_way_R2L_ID 48	//右到左

//车头的连接处竖线  32mm第一条磁条   32cm第二条
//chewei  

typedef struct
{
	u8 SD_Speed_bili;
	//u16 Car_SD_Speed;
	
	u16 ID;
	
	u8  yinliang;			
	u8	Auto_Speed_bili;		//0:低速 1:中速 2:告诉
	u16	Car_Auto_Speed;			
	u8  Key_yuyin;				
	u8  Key_RGB_LED;
	
	u8  Key_IR_jin;	
	u8  Key_IR_yuan;		
	u8  Key_JiXie_qian;		
	u8  Key_JiXie_hou;		
	
	u16 L_speed;
	u16 M_speed;
	u16 H_speed;
	
	u16 duijie_speed;
	
	u16 XZ_MAX_Speed;
	u16 XZ_DWQ_Speed_bili;
	u16 XZ_CiTiao_Speed;
	u16 Motor_MAX_Speed;


	float AUTO_Kp;
	float AUTO_Ki;
	float AUTO_Kd;

	float SD_Kp;
	float SD_Ki;
	float SD_Kd;
	
	u8 PID_time;
	
	u16 GunT_daozhong_time;	//滚筒货物到滚筒中间延时
	
	u8  yuandian_dir;
	
	u16 ToPLC_task;
	
	u16 Manu_speed_my;
	u16 autu_speed_my;
	
	u16 yuandian_ID;
	u16 chongdian_ID;
	u16 zhongzhuan_ID;
	u16 add_time_yuzhi;
	u16 guan_ID; //炉子的管子ID

	
}AGV_System;

	
typedef struct
{
	u8 Car_dir;						//全局唯一//0:前进    1:后退
	
	//1:左分叉  2:右分叉  			//虚拟分叉地标--11:前轮左分叉 12:前轮右分叉  21:后轮左分叉 22:后轮右分叉
	u8 Car_fencha_dir;  			
                                    
	u8 Car_Auto2Manu_mode;          //0:自动  1:手动
	
	u8 Flash_get_OK;				//flash读出数据ok
	
	u8 Car_fencha_dir_qian;  		//前驱动分叉方向 //0:左分叉  1:右分叉
	u8 Car_fencha_dir_hou;  		//后驱动分叉方向 //0:左分叉  1:右分叉
	
	u8 Car_fencha_Start_qian;
	u8 Car_fencha_Start_hou ;
	
	u8 fencha_RFID_qian;
	u8 fencha_RFID_hou;
	
	u8 RunSta;
	u8 warning;
	
	u16 juedui_RFID;	//自动模式下的 绝对地标(包含实体跟虚拟地标)
	u16 shiti_RFID;		//手动模式下的 实体地标
	
	u8 flag_fist_zhilu;
	u16 add_time;
	
	u8 flag_addTIME_OK;
	u8 ok_yuandi;
	u8 type_path;
	u8 flag_set_yuandian;
	u16 RFID_buff[2];
	

	
}AGV_status;

typedef struct
{
	u8 roller;			//输送

	u8 chongdian;		//充电	3
	u16 mode_chongdian;

}AGV_RunState;

typedef struct
{
	u8 jixie_qian;		//机械避障	1 
	u8 jixie_hou;		//机械避障	1 
	u8 chugui;			//出轨		2
	u8 IR_qian;			//红外避障	3
	u8 IR_hou;			//红外避障	3
	u8 Low_battery;		//低电量	4
	u8 Drive_NOPwoer;	//驱动断电  5
	u8 RFID_err;		//地标出错	6
	
	
	
}AGV_Warning;			//按位置一  0(正常)

extern AGV_RunState g_RunSta;
extern AGV_Warning  g_Warning;

extern AGV_System AGV_SYS;

extern AGV_status g_AGV_Sta;
extern u16 g_LastCDH_buff[5];
extern u8  g_CDH_add_num[5];
extern u8 g_flag_i;

void delay_rtos(u32 h,u32 m,u32 s,u32 ms);
void UserConfigInit(void);
//执行站点动作
void StationAction(u16 num);
void ActiveProcess(void);


u16 u8_to_u16(u8 *H_Bit,u8 *L_Bit);

void CDH_ADD(u16 *last_data,u16 *buff,u8 *cdh_add_num_buff);


//1:左分叉  2:右分叉 
//虚拟分叉地标--11:前轮左分叉 12:前轮右分叉  21:后轮左分叉 22:后轮右分叉
void fencha_1to2_qian(u8 fencha_dir,u8 *FC_dir_qian);
void fencha_1to2_hou(u8 fencha_dir,u8 *FC_dir_hou);
void GetRFIDbuff(u16 RFID,u16 *last,u16 *now,u16 *next,u16 num);
	
void AGV_LED(void);			//AGV行车灯

void AGV_Auto_speed(u16 *buff_speed,u16 *true_speed,u8 Car_dir);	//参考速度
void AGV_Manu_speed(u16 now_speed,u16 *true_speed,u8 Car_dir);	//参考速度

u8 get_path(u16 now_id,u16 luzi_id); //目标:炉子ID
u8 AGV_run_path(u8 type,u8 path);
void GunTong_PLC(u16 num,u16 type);




#endif

