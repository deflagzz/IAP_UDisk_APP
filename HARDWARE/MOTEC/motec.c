#include "motec.h"

wait_CanOpen_init g_motec_init;
//
//驱动器Canopen命令
//
static char CanOpen_buff[8];

void AGV_CanOpen_Send(void)		//换到 CAN2
{
	CanOpen_buff[0] = 1;
	CanOpen_buff[1] = 0;
	
	CAN2_Send_Msg(0,CanOpen_buff,2);
}

void AGV_CanOpen_Send1(void)
{
	CanOpen_buff[0] = 6;
	CanOpen_buff[1] = 0;
	CanOpen_buff[2] = 0;
	CanOpen_buff[3] = 0;	
	CanOpen_buff[4] = 0;
	CanOpen_buff[5] = 0;	

	CAN2_Send_Msg(0x201,CanOpen_buff,6);
	CAN2_Send_Msg(0x202,CanOpen_buff,6);
	CAN2_Send_Msg(0x203,CanOpen_buff,6);
	CAN2_Send_Msg(0x204,CanOpen_buff,6);
}

void AGV_CanOpen_Send2(void)
{
	CanOpen_buff[0] = 7;
	CanOpen_buff[1] = 0;
	CanOpen_buff[2] = 0;
	CanOpen_buff[3] = 0;	
	CanOpen_buff[4] = 0;
	CanOpen_buff[5] = 0;	

	CAN2_Send_Msg(0x201,CanOpen_buff,6);
	CAN2_Send_Msg(0x202,CanOpen_buff,6);
	CAN2_Send_Msg(0x203,CanOpen_buff,6);
	CAN2_Send_Msg(0x204,CanOpen_buff,6);
}
void Motec_init(void)		
{
	delay_rtos(0,0,1,500);
	AGV_CanOpen_Send();
	AGV_CanOpen_Send1();
	AGV_CanOpen_Send2();
	delay_rtos(0,0,1,500);
}

//速度
void AGV_CanOpen_Send3(u8 node_id,int speed) 
{
	u16 temp_COB_ID=0;
	
	if(node_id > 127)					//节点ID不能超过127
	{
		node_id = 127;
	}
	temp_COB_ID = 0x200+node_id;		//11位COB_ID
	
	CanOpen_buff[0] = 0x0f;
	CanOpen_buff[1] = 0;
	CanOpen_buff[2] = speed & 0xff;
	CanOpen_buff[3] = (speed>>8) & 0xff;	
	
	if(CAN2_Send_Msg(temp_COB_ID,CanOpen_buff,4))	//失败重发一次
	{
		CAN2_Send_Msg(temp_COB_ID,CanOpen_buff,4);
	}
	
}






void check_Motec_init(void)
{
	g_motec_init.Init_OK = 0;						//驱动使能ok标志清零
	g_Warning.Drive_NOPwoer = 1;
	
	Motec_init();									//AGV系统上电发送初始化命令
	
	while(1)
	{
		//判断驱动使能与否
		if(g_motec_init.zijian_enable)				//驱动器使能
		{
			g_motec_init.flag_NoPowerUp = 0;		//驱动上电
			g_AGV_speaker_flag.Motec_enable = 1;	//语音_驱动使能
			delay_rtos(0,0,0,20);

			DwqXunZheng_QH();						//电位器寻正	
			g_motec_init.Init_OK = 1;			
			g_Warning.Drive_NOPwoer = 0;
			
		}
		else
		{		
			g_motec_init.flag_NoPowerUp = 1;		//驱动未上电

			g_motec_init.Init_OK = 0;
			g_Warning.Drive_NOPwoer = 1;
			g_motec_init.zijian_shangdian = 0;
		}
		
		//驱动器使能的循环
		while(g_motec_init.zijian_enable)			
		{
			g_motec_init.zijian_enable--;			//150
			delay_rtos(0,0,0,20);	
		}
		g_motec_init.zijian_enable = 0;				//自减为0 -- 驱动无电
		
		//判断驱动是未上电还是断电
		if(g_motec_init.flag_NoPowerUp)				
		{
			g_AGV_speaker_flag.Motec_NoPowerUp = 1;	//驱动未上电
			delay_rtos(0,0,0,20);
		}
		else
		{
			g_AGV_speaker_flag.Motec_off = 1;		//驱动断电
			delay_rtos(0,0,0,20);		
		}
		g_motec_init.Init_OK = 0;
		g_Warning.Drive_NOPwoer = 1;
		g_motec_init.zijian_shangdian = 0;
		
		//驱动器掉电的循环	
		while(!g_motec_init.zijian_shangdian)		//等待驱动器上电 -- 0x7F
		{	
			delay_rtos(0,0,0,20);
		}	
		Motec_init();								//上电发初始化命令
		
		delay_rtos(0,0,0,10);
	}
}































