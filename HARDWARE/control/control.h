#ifndef __CONTROL_H
#define __CONTROL_H
#include "my_include.h"

//------------------------------PID----------------------------------//
typedef struct
{
	int moter1_speed;
	int moter2_speed;
	int moter3_speed;
	int moter4_speed;
}PIDspeed;


extern int  g_fencha_yiwei_val ;		//8位磁导航分叉移位值


void PID_AUTO_QianLun(u16 j_speed,float kp,float ki,float kd);
void PID_AUTO_HouLun(u16 j_speed2,float kp2,float ki2,float kd2);	//后轮的PID调节

void PID_SD_Adjust(u16 j_speed,float kp,u16 ki,float kd);
u8 check_CDH_chugui(u8 ID);		//返回0:左出轨 1:右出轨
//------------------------------PID----------------------------------//





//上层的行走方向控制函数
void Zi_Dong(void);
void Shou_Dong(void);
void Qian_Jin(void);
void Hou_Tui(void);
//void Zuo_Xuan(void);
//void You_Xuan(void);
void Ting_Zhi(void);
void Qi_Dong(void);
void Zuo_Fen(void);
void Zhong_Fen(void);
void You_Fen(void);
void ZhiXing(void);						//直行

void Cha_Sheng(void);
void Cha_Jiang(void);


void SD_Trun_L(void);
void SD_Trun_R(void);	
	
void Ruan_Qi_jia(u16 speed_min1,u16 speed_max,u16 * speed_zhi);
void Ruan_jian(u16 speed_max1,u16 speed_min,u16 * speed_TrueVal);	//软减速
void Ruan_Stop(u16 * speed_TrueVal);	


#endif
