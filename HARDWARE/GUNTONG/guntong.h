#ifndef  _GUNTONG_H
#define _GUNTONG_H
#include "my_include.h"



#define guntong_start    PCout(5)   //滚筒启动 -- 高电平触发
#define guntong_fanzhuan PCout(4) 	//滚筒反转 -- 高电平触发




extern u16 StationData[16]; 
extern u8 stopflag,startflag;
//运动控制线程
extern u8  startAsk,stopAsk,zyAsk,yyAsk;
extern u16 DstSpeed;


void guntong_init(void);
void guntong1(void);

void GunTong_L(u8 enable);
void GunTong_R(u8 enable);

void GunTong_Trun_L_DOWN(void);	//左转卸货

void GunTong_Trun_L_UP(void);	//左转上货

void GunTong_Trun_R_DOWN(void);	//右转卸货

void GunTong_Trun_R_UP(void);	//右转上货

void SD_GunTong(void);









#endif







