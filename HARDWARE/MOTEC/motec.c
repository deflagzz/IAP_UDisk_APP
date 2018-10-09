#include "motec.h"

wait_CanOpen_init g_motec_init;
//
//������Canopen����
//
static char CanOpen_buff[8];

void AGV_CanOpen_Send(void)		//���� CAN2
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

//�ٶ�
void AGV_CanOpen_Send3(u8 node_id,int speed) 
{
	u16 temp_COB_ID=0;
	
	if(node_id > 127)					//�ڵ�ID���ܳ���127
	{
		node_id = 127;
	}
	temp_COB_ID = 0x200+node_id;		//11λCOB_ID
	
	CanOpen_buff[0] = 0x0f;
	CanOpen_buff[1] = 0;
	CanOpen_buff[2] = speed & 0xff;
	CanOpen_buff[3] = (speed>>8) & 0xff;	
	
	if(CAN2_Send_Msg(temp_COB_ID,CanOpen_buff,4))	//ʧ���ط�һ��
	{
		CAN2_Send_Msg(temp_COB_ID,CanOpen_buff,4);
	}
	
}






void check_Motec_init(void)
{
	g_motec_init.Init_OK = 0;						//����ʹ��ok��־����
	g_Warning.Drive_NOPwoer = 1;
	
	Motec_init();									//AGVϵͳ�ϵ緢�ͳ�ʼ������
	
	while(1)
	{
		//�ж�����ʹ�����
		if(g_motec_init.zijian_enable)				//������ʹ��
		{
			g_motec_init.flag_NoPowerUp = 0;		//�����ϵ�
			g_AGV_speaker_flag.Motec_enable = 1;	//����_����ʹ��
			delay_rtos(0,0,0,20);

			DwqXunZheng_QH();						//��λ��Ѱ��	
			g_motec_init.Init_OK = 1;			
			g_Warning.Drive_NOPwoer = 0;
			
		}
		else
		{		
			g_motec_init.flag_NoPowerUp = 1;		//����δ�ϵ�

			g_motec_init.Init_OK = 0;
			g_Warning.Drive_NOPwoer = 1;
			g_motec_init.zijian_shangdian = 0;
		}
		
		//������ʹ�ܵ�ѭ��
		while(g_motec_init.zijian_enable)			
		{
			g_motec_init.zijian_enable--;			//150
			delay_rtos(0,0,0,20);	
		}
		g_motec_init.zijian_enable = 0;				//�Լ�Ϊ0 -- �����޵�
		
		//�ж�������δ�ϵ绹�Ƕϵ�
		if(g_motec_init.flag_NoPowerUp)				
		{
			g_AGV_speaker_flag.Motec_NoPowerUp = 1;	//����δ�ϵ�
			delay_rtos(0,0,0,20);
		}
		else
		{
			g_AGV_speaker_flag.Motec_off = 1;		//�����ϵ�
			delay_rtos(0,0,0,20);		
		}
		g_motec_init.Init_OK = 0;
		g_Warning.Drive_NOPwoer = 1;
		g_motec_init.zijian_shangdian = 0;
		
		//�����������ѭ��	
		while(!g_motec_init.zijian_shangdian)		//�ȴ��������ϵ� -- 0x7F
		{	
			delay_rtos(0,0,0,20);
		}	
		Motec_init();								//�ϵ緢��ʼ������
		
		delay_rtos(0,0,0,10);
	}
}































