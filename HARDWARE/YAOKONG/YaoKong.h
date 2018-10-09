#ifndef	_YAOKONG_H
#define _YAOKONG_H


#include "my_include.h"


//摇杆坐标	 g_SD_buff[i]
//X 	--		0	
//Y 	-- 		1
//Z 	-- 		2
//按键 	-- 		3
typedef struct
{
	signed char g_SD_buff[8];		//遥控器的CAN接收buff
	u8  ID;
	
	int jiaodu;				 //左右旋:	-64 -- 0 -- 64			//控制AGV转弯 -- 实际角度
	u8  SD_ir;				 //前后推:	0:停止 1:前进 2:后退
	u16 SD_Speed;		 	 //			0 -- 100				//速度
	u8  jiaodu_Max;		 	 //			0 -- 80					//遥控器控制AGV的左右转弯角度极限值 
	u8  GunTong_dir;		 //左右推:  0:停止 1:左滚 2:右滚	//控制滚筒左右滚
	u8	GunTong_chufa_val;	 //			0 -- 100				//按住摇杆按键左右摆动摇杆控制滚筒左右滚 -- 左右触发值
	u8	GunTong_Enable;		 //点按键	0:关闭	1:使能			//使能摇杆控制滚筒
	u8  Start_chufa_val;

}yaokong;



extern yaokong g_AGV_yaokong;



void YaoKong_control(yaokong *temp_yaokong);




























#endif

