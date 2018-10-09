#include "guntong.h"


//PC5 -- Run A  --�ߵ�ƽ���� -- ��̬����
//PC4 -- ��ת   --�ߵ�ƽ����
//GND -- Run B
void guntong_init(void) 
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);	//

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4| GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			//���
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;		//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;			//����
	GPIO_Init(GPIOC, &GPIO_InitStructure);					//
	GPIO_ResetBits(GPIOC,GPIO_Pin_4| GPIO_Pin_5);
		
	
}





u8	sta_gunt=0;

u8  USART2_TX_BUF[100];
void u2_printf(char* fmt,...)  
{  
	u16 i,j;
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)USART2_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART2_TX_BUF);//?????????
	for(j=0;j<i;j++)//??????
	{
	  while(USART_GetFlagStatus(USART6,USART_FLAG_TC)==RESET);  //???????? 
		USART_SendData(USART6,(uint8_t)USART2_TX_BUF[j]); 	 //???????6 
	}
}

	

void GunTong_R(u8 enable)
{
	if(enable)
	{
		guntong_start = 1;						//��Ͳ����
		
		g_AGV_speaker_flag.GunT_R = 1;

		delay_rtos(0,0,0,g_Speaker_delay);	
	}
	else
	{
		guntong_start = 0;						//��Ͳֹͣ
		g_AGV_speaker_flag.GunT_stop = 1;
		delay_rtos(0,0,0,g_Speaker_delay);
	}
	guntong_fanzhuan = 0;					//��Ͳ��ת	
}

void GunTong_L(u8 enable)
{
	if(enable)
	{
		guntong_start    = 1;	
		guntong_fanzhuan = 1;					//��Ͳ��ת
		g_AGV_speaker_flag.GunT_L = 1;
		delay_rtos(0,0,0,g_Speaker_delay);
	}
	else
	{
		guntong_start = 0;	
		guntong_fanzhuan = 0;					//��Ͳֹͣ
		g_AGV_speaker_flag.GunT_stop = 1;
		delay_rtos(0,0,0,g_Speaker_delay);
	}
}


void GunTong_Trun_L_DOWN(void)	//���ж��
{

	while(!*g_PLC_message[AGV_SYS.ID-1].Flag_DownTray_allowed)	//�ȴ�PLC������������ź�
	{
		delay_rtos(0,0,0,20); 
	}
	
	GunTong_L(1);
	while(!g_Senser_InPut.gunt_IR_L)	//�ȴ�����ⱻ����
	{
		delay_rtos(0,0,0,20);
	}
	delay_rtos(0,0,0,100);
	while(!g_Senser_InPut.gunt_IR_L)	//�ȴ�����ⱻ����
	{
		delay_rtos(0,0,0,20);
	}
	while(g_Senser_InPut.gunt_IR_L)		//�ȴ������û�б�����
	{
		delay_rtos(0,0,0,20);
	}
	delay_rtos(0,0,0,100);
	while(g_Senser_InPut.gunt_IR_L)		//�ȴ������û�б�����
	{
		delay_rtos(0,0,0,20);
	}		

	while(!*g_PLC_message[AGV_SYS.ID-1].Flag_PLCRecTray_Finish)	//�ȴ�PLC������������ź�
	{
		delay_rtos(0,0,0,20);
	}	

	GunTong_L(0);	
	
	delay_rtos(0,0,1,0);


}
void GunTong_Trun_L_UP(void)	//����ϻ�
{
	u8 temp_i = AGV_SYS.GunT_daozhong_time/5;				//������ʱ     
		
	while(!*g_PLC_message[AGV_SYS.ID-1].Flag_RecTray_start)		//��PLC�������ź�
	{
		delay_rtos(0,0,0,20);
	}
	
	*g_PLC_message[AGV_SYS.ID-1].Flag_RecTray_Ready = 1;		//AGV����PLC��������׼������
	
	GunTong_R(1);
	while(!g_Senser_InPut.gunt_IR_L)				//�ȴ�����ⱻ����
	{
		delay_rtos(0,0,0,20);
	}
	delay_rtos(0,0,0,100);
	while(!g_Senser_InPut.gunt_IR_L)				//�ȴ�����ⱻ����
	{
		delay_rtos(0,0,0,20);
	}	
	
	while(g_Senser_InPut.gunt_IR_L)					//�ȴ�����ⲻ������
	{
		delay_rtos(0,0,0,20);
	}
	delay_rtos(0,0,0,100);
	while(g_Senser_InPut.gunt_IR_L)					//�ȴ�����ⲻ������
	{
		delay_rtos(0,0,0,20);
	}
	
	while(!g_Senser_InPut.gunt_IR_R && temp_i--)	//�ȴ��Һ��ⴥ�����ߵ��м�
	{
		delay_rtos(0,0,0,5);		
	}
	while(g_Senser_InPut.gunt_IR_L)					//�ȴ�����ⲻ������
	{
		delay_rtos(0,0,0,20);
	}	
	GunTong_R(0);
	
	*g_PLC_message[AGV_SYS.ID-1].Flag_RecTray_Finish = 1;	//AGV����PLC���̽������
	
	delay_rtos(0,0,1,0);							//��PLC��1����ʱ��
	
	
	//���˽�����ɲ���  ������������
//��¯��ǰ��
}
void GunTong_Trun_R_DOWN(void)	//�Ҳ�ж��
{
	
	while(!*g_PLC_message[AGV_SYS.ID-1].Flag_DownTray_allowed)	//�ȴ�PLC������������ź�
	{
		delay_rtos(0,0,0,20);
	}
	
	GunTong_R(1);
	while(!g_Senser_InPut.gunt_IR_R)	//�ȴ��Һ��ⱻ����
	{
		delay_rtos(0,0,0,20);
	}
	delay_rtos(0,0,0,100);
	while(!g_Senser_InPut.gunt_IR_R)	//�ȴ��Һ��ⱻ����
	{
		delay_rtos(0,0,0,20);
	}
	while(g_Senser_InPut.gunt_IR_R)		//�ȴ��Һ���û�б�����
	{
		delay_rtos(0,0,0,20);
	}
	delay_rtos(0,0,0,100);
	while(g_Senser_InPut.gunt_IR_R)		//�ȴ��Һ���û�б�����
	{
		delay_rtos(0,0,0,20);
	}		

	while(!*g_PLC_message[AGV_SYS.ID-1].Flag_PLCRecTray_Finish)	//�ȴ�PLC������������ź�
	{
		delay_rtos(0,0,0,20);
	}	

	GunTong_R(0);	
	
	delay_rtos(0,0,2,0);

}
void GunTong_Trun_R_UP(void)	//�Ҳ��ϻ�
{
	u8 temp_i = AGV_SYS.GunT_daozhong_time/5;					//������ʱ

	while(!*g_PLC_message[AGV_SYS.ID-1].Flag_RecTray_start)		//��PLC�������ź�
	{
		delay_rtos(0,0,0,20);
	}
	*g_PLC_message[AGV_SYS.ID-1].Flag_RecTray_Ready = 1;		//AGV����PLC��������׼������

	
	GunTong_L(1);
	while(!g_Senser_InPut.gunt_IR_R)	//�ȴ��ұ�����
	{
		delay_rtos(0,0,0,20);
	}
	delay_rtos(0,0,0,100);
	while(!g_Senser_InPut.gunt_IR_R)	//�ȴ��ұ�����
	{
		delay_rtos(0,0,0,20);
	}	
	
	while(g_Senser_InPut.gunt_IR_R)		//�ȴ��Ҳ�������
	{
		delay_rtos(0,0,0,20);
	}
	delay_rtos(0,0,0,100);
	while(g_Senser_InPut.gunt_IR_R)		//�ȴ��Ҳ�������
	{
		delay_rtos(0,0,0,20);
	}	
	
	while(!g_Senser_InPut.gunt_IR_L && temp_i--)
	{
		delay_rtos(0,0,0,5);		
	}
	while(g_Senser_InPut.gunt_IR_R)		//�ȴ��Ҳ�������
	{
		delay_rtos(0,0,0,20);
	}
	GunTong_L(0);				//�������м�
	
	*g_PLC_message[AGV_SYS.ID-1].Flag_RecTray_Finish = 1;	//AGV����PLC���̽������	
	
	delay_rtos(0,0,2,0);
}


u8  g_GunTong_Flag_stop = 1;			//�ֶ����ƹ�Ͳ��ֹͣ״̬��־	1:ֹͣ�� 0:������
void SD_GunTong(void)
{
	if(g_AGV_Sta.Car_Auto2Manu_mode) 					//1:�ֶ�ģʽ
	{
		if(g_AGV_yaokong.GunTong_Enable == 1)			//ҡ�˰�������ʹ��
		{
			if(g_AGV_yaokong.GunTong_dir == 1 && g_GunTong_Flag_stop)		//ҡ�����--��Ͳ��ת
			{
				g_GunTong_Flag_stop = 0;
				GunTong_L(1);				
			}
			else if(g_AGV_yaokong.GunTong_dir == 2 && g_GunTong_Flag_stop)		//ҡ���Ұ�--��Ͳ��ת
			{
				g_GunTong_Flag_stop = 0;
				GunTong_R(1);
			}	
			else if(g_AGV_yaokong.GunTong_dir == 0)		//��Ͳֹͣ
			{
				if(!g_GunTong_Flag_stop)
				{
					GunTong_L(0);								//����ͣ
					g_GunTong_Flag_stop = 1;		
				}
			}				
		}
		else if(g_AGV_yaokong.GunTong_Enable == 0)	
		{
			if(!g_GunTong_Flag_stop)
			{
				GunTong_L(0);								//����ͣ
				g_GunTong_Flag_stop = 1;		
			}
		}
	}
	else if(!g_AGV_Sta.Car_Auto2Manu_mode) 				//���ֶ��л����Զ���ȷ����ȫͣ����
	{
		if(!g_GunTong_Flag_stop)
		{
			GunTong_L(0);								//����ͣ
			g_GunTong_Flag_stop = 1;		
		}
		
	}
}



