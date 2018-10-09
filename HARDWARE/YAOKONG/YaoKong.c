#include "YaoKong.h"



//ң������ -- 1��2��3H4L

yaokong g_AGV_yaokong;


//ҡ������	 g_SD_buff[i]
//X 	--		0	
//Y 	-- 		1
//Z 	-- 		2
//���� 	-- 		3

void YaoKong_control(yaokong *temp_yaokong)			//ң������ID:22
{
	u8 temp_dir=0;
	int temp_speed=0;
	int temp_jd=0;
	signed char *CAN_RX_buff=NULL;
	
	CAN_RX_buff = temp_yaokong->g_SD_buff;
	
	if(CAN_RX_buff[1] > 0)				//ǰ��
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
	else if(CAN_RX_buff[1] == 0)			//ֹͣ
	{
		temp_dir = 0;
		temp_speed = 0;
	}
	else if(CAN_RX_buff[1] < 0)			//����
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

	
	//��ס������ת��Ͳ��ת, //��ס������ת��Ͳ��ת
	if(CAN_RX_buff[2] < 0)				//����										//-90 -- 0 (+20)					
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
	else if(CAN_RX_buff[2] == 0)		//ֹͣ
	{
		temp_yaokong->jiaodu = 0;
	}
	else if(CAN_RX_buff[2] > 0)		//����											//0 -- 90 (-20)
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
	
	
	if(!CAN_RX_buff[3])						//0:ʹ�� :ҡ�˿��ƹ�Ͳ
	{		
		temp_yaokong->GunTong_Enable = 1;
	}
	else if(CAN_RX_buff[3])					//1:�ر�ʹ��
	{
		temp_yaokong->GunTong_Enable = 0;
	}			
	
	if(temp_yaokong->GunTong_Enable)		//1:��Ͳģʽ
	{
		if(!temp_dir && !temp_speed)
		{
			if(CAN_RX_buff[2] < -temp_yaokong->GunTong_chufa_val)//��Ͳ���	-100  -- 0			//ҡ����ҡ��һ��λ�ù�Ͳ���
			{
				temp_yaokong->GunTong_dir = 1;
			}	
			else if(CAN_RX_buff[2] > temp_yaokong->GunTong_chufa_val)//��Ͳ��ת	0  -- 100			//ҡ����ҡ��һ��λ�ù�Ͳ�ҹ�
			{
				temp_yaokong->GunTong_dir = 2;
			}
			else 			//��Ͳֹͣ
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
		temp_yaokong->GunTong_dir = 0;		//��Ͳֹͣ
	}
	
	temp_yaokong->SD_ir 	= temp_dir;	
	//temp_yaokong->SD_Speed  = temp_speed * 20 * AGV_SYS.SD_Speed_bili/10;	//0-100*20//0-2000

	//Զ���ⴥ������ʹ������ٶ�:AGV_SYS.Manu_speed_my	
	AGV_SYS.Manu_speed_my   = temp_speed * 20 * AGV_SYS.SD_Speed_bili/10;	
}








