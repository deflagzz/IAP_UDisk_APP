#include "YaoKong.h"



//遥控器线 -- 1正2负3H4L

yaokong g_AGV_yaokong;


//摇杆坐标	 g_SD_buff[i]
//X 	--		0	
//Y 	-- 		1
//Z 	-- 		2
//按键 	-- 		3

void YaoKong_control(yaokong *temp_yaokong)			//遥控器是ID:22
{
	u8 temp_dir=0;
	int temp_speed=0;
	int temp_jd=0;
	signed char *CAN_RX_buff=NULL;
	
	CAN_RX_buff = temp_yaokong->g_SD_buff;
	
	if(CAN_RX_buff[1] > 0)				//前进
	{		
		temp_dir = 1;
		if(CAN_RX_buff[1] < g_AGV_yaokong.Start_chufa_val)
		{
			temp_speed = 0;
		}
		else
		{
			temp_speed = CAN_RX_buff[1] - g_AGV_yaokong.Start_chufa_val;
		}
	}
	else if(CAN_RX_buff[1] == 0)			//停止
	{
		temp_dir = 0;
		temp_speed = 0;
	}
	else if(CAN_RX_buff[1] < 0)			//后退
	{
		temp_dir = 2;
		if(-CAN_RX_buff[1] < g_AGV_yaokong.Start_chufa_val)
		{
			temp_speed = 0;
		}
		else
		{
			temp_speed = -CAN_RX_buff[1] - g_AGV_yaokong.Start_chufa_val;
		}		
	}	

	
	//按住按键左转滚筒左转, //按住按键右转滚筒右转
	if(CAN_RX_buff[2] < 0)				//左旋										//-90 -- 0 (+20)					
	{						
		temp_jd = (9 * CAN_RX_buff[2])/10 + (90-temp_yaokong->jiaodu_Max);			//-70 -- 20
		if(temp_jd >= 0)
		{
			temp_yaokong->jiaodu  = 0;
		}
		else
		{
			temp_yaokong->jiaodu = temp_jd;											//-70 -- 0
		}					
	}
	else if(CAN_RX_buff[2] == 0)		//停止
	{
		temp_yaokong->jiaodu = 0;
	}
	else if(CAN_RX_buff[2] > 0)		//右旋											//0 -- 90 (-20)
	{
		temp_jd = (9 * CAN_RX_buff[2])/10 - (90-temp_yaokong->jiaodu_Max);			//-20 -- 70
		if(temp_jd <= 0)
		{
			temp_yaokong->jiaodu  = 0;
		}
		else
		{
			temp_yaokong->jiaodu = temp_jd;											//0   -- 70
		}		
	}	
	
	
	if(!CAN_RX_buff[3])						//0:使能 :摇杆控制滚筒
	{		
		temp_yaokong->GunTong_Enable = 1;
	}
	else if(CAN_RX_buff[3])					//1:关闭使能
	{
		temp_yaokong->GunTong_Enable = 0;
	}			
	
	if(temp_yaokong->GunTong_Enable)		//1:滚筒模式
	{
		if(!temp_dir && !temp_speed)
		{
			if(CAN_RX_buff[2] < -temp_yaokong->GunTong_chufa_val)//滚筒左滚	-100  -- 0			//摇杆左摇到一半位置滚筒左滚
			{
				temp_yaokong->GunTong_dir = 1;
			}	
			else if(CAN_RX_buff[2] > temp_yaokong->GunTong_chufa_val)//滚筒右转	0  -- 100			//摇杆右摇到一半位置滚筒右滚
			{
				temp_yaokong->GunTong_dir = 2;
			}
			else 			//滚筒停止
			{
				temp_yaokong->GunTong_dir = 0;
			}		
		}
		else
		{
			temp_yaokong->GunTong_dir = 0;
		}
	
	}
	else
	{	
		temp_yaokong->GunTong_dir = 0;		//滚筒停止
	}
	
	temp_yaokong->SD_ir 	= temp_dir;	
	//temp_yaokong->SD_Speed  = temp_speed * 20 * AGV_SYS.SD_Speed_bili/10;	//0-100*20//0-2000

	//远红外触发减速使用这个速度:AGV_SYS.Manu_speed_my	
	AGV_SYS.Manu_speed_my   = temp_speed * 20 * AGV_SYS.SD_Speed_bili/10;	
}








