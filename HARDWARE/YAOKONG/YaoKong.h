#ifndef	_YAOKONG_H
#define _YAOKONG_H


#include "my_include.h"


//ҡ������	 g_SD_buff[i]
//X 	--		0	
//Y 	-- 		1
//Z 	-- 		2
//���� 	-- 		3
typedef struct
{
	signed char g_SD_buff[8];		//ң������CAN����buff
	u8  ID;
	
	int jiaodu;				 //������:	-64 -- 0 -- 64			//����AGVת�� -- ʵ�ʽǶ�
	u8  SD_ir;				 //ǰ����:	0:ֹͣ 1:ǰ�� 2:����
	u16 SD_Speed;		 	 //			0 -- 100				//�ٶ�
	u8  jiaodu_Max;		 	 //			0 -- 80					//ң��������AGV������ת��Ƕȼ���ֵ 
	u8  GunTong_dir;		 //������:  0:ֹͣ 1:��� 2:�ҹ�	//���ƹ�Ͳ���ҹ�
	u8	GunTong_chufa_val;	 //			0 -- 100				//��סҡ�˰������Ұڶ�ҡ�˿��ƹ�Ͳ���ҹ� -- ���Ҵ���ֵ
	u8	GunTong_Enable;		 //�㰴��	0:�ر�	1:ʹ��			//ʹ��ҡ�˿��ƹ�Ͳ
	u8  Start_chufa_val;

}yaokong;



extern yaokong g_AGV_yaokong;



void YaoKong_control(yaokong *temp_yaokong);




























#endif

