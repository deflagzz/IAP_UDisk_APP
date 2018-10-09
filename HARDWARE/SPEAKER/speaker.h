#ifndef _SPEAKER_H
#define _SPEAKER_H

#include "my_include.h"


typedef struct
{
	u8 start;
	u8 stop;
	u8 GunT_L;
	u8 GunT_R;
	u8 GunT_stop;
	u8 Manu;
	u8 Auto;
	u8 dir_Go;
	u8 dir_Back;
	u8 FenCha_L;
	u8 FenCha_R;
	
	u8 LuJing_ok;
	u8 LiuCheng_ok;
	
	u8 Motec_enable;
	u8 Motec_off;
	u8 Motec_NoPowerUp;
	
	u8 UP_L;
	u8 UP_R;
	u8 Down_L;
	u8 Down_R;
	
	u8 JiXie;
	u8 IR;
	
	u8 Ruan_Qi;
	u8 UP_gui_qian_hou;
	u8 DOWN_gui_qian1;
	u8 DOWN_gui_qian2;
	u8 DOWN_gui_hou1;
	u8 DOWN_gui_hou2;
	
	u8 RFID_READ_err;
	
	u8 user_luzi;
	
	u8 chongdian_goto;
	u8 chongdian_over;
	u8 AGV_readyed;
	u8 path;
	
	

}speaker_flag;


extern speaker_flag g_AGV_speaker_flag;

extern char g_user_luzi[256];

extern u16 g_Speaker_delay;



void speak_once(char *buff,u16 delay,u8 *flag);

void USART1_Configuration(u32 bound);







#endif
