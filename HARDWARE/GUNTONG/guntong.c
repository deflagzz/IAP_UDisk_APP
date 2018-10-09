#include "guntong.h"


//PC5 -- Run A  --高电平触发 -- 常态下拉
//PC4 -- 反转   --高电平触发
//GND -- Run B
void guntong_init(void) 
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);	//

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4| GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			//输出
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//推挽
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;		//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;			//下拉
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
		guntong_start = 1;						//滚筒启动
		
		g_AGV_speaker_flag.GunT_R = 1;

		delay_rtos(0,0,0,g_Speaker_delay);	
	}
	else
	{
		guntong_start = 0;						//滚筒停止
		g_AGV_speaker_flag.GunT_stop = 1;
		delay_rtos(0,0,0,g_Speaker_delay);
	}
	guntong_fanzhuan = 0;					//滚筒反转	
}

void GunTong_L(u8 enable)
{
	if(enable)
	{
		guntong_start    = 1;	
		guntong_fanzhuan = 1;					//滚筒反转
		g_AGV_speaker_flag.GunT_L = 1;
		delay_rtos(0,0,0,g_Speaker_delay);
	}
	else
	{
		guntong_start = 0;	
		guntong_fanzhuan = 0;					//滚筒停止
		g_AGV_speaker_flag.GunT_stop = 1;
		delay_rtos(0,0,0,g_Speaker_delay);
	}
}


void GunTong_Trun_L_DOWN(void)	//左侧卸货
{

	while(!*g_PLC_message[AGV_SYS.ID-1].Flag_DownTray_allowed)	//等待PLC的允许出托盘信号
	{
		delay_rtos(0,0,0,20); 
	}
	
	GunTong_L(1);
	while(!g_Senser_InPut.gunt_IR_L)	//等待左红外被触发
	{
		delay_rtos(0,0,0,20);
	}
	delay_rtos(0,0,0,100);
	while(!g_Senser_InPut.gunt_IR_L)	//等待左红外被触发
	{
		delay_rtos(0,0,0,20);
	}
	while(g_Senser_InPut.gunt_IR_L)		//等待左红外没有被触发
	{
		delay_rtos(0,0,0,20);
	}
	delay_rtos(0,0,0,100);
	while(g_Senser_InPut.gunt_IR_L)		//等待左红外没有被触发
	{
		delay_rtos(0,0,0,20);
	}		

	while(!*g_PLC_message[AGV_SYS.ID-1].Flag_PLCRecTray_Finish)	//等待PLC接收托盘完成信号
	{
		delay_rtos(0,0,0,20);
	}	

	GunTong_L(0);	
	
	delay_rtos(0,0,1,0);


}
void GunTong_Trun_L_UP(void)	//左侧上货
{
	u8 temp_i = AGV_SYS.GunT_daozhong_time/5;				//对中延时     
		
	while(!*g_PLC_message[AGV_SYS.ID-1].Flag_RecTray_start)		//等PLC的请求信号
	{
		delay_rtos(0,0,0,20);
	}
	
	*g_PLC_message[AGV_SYS.ID-1].Flag_RecTray_Ready = 1;		//AGV告诉PLC接收托盘准备就绪
	
	GunTong_R(1);
	while(!g_Senser_InPut.gunt_IR_L)				//等待左红外被触发
	{
		delay_rtos(0,0,0,20);
	}
	delay_rtos(0,0,0,100);
	while(!g_Senser_InPut.gunt_IR_L)				//等待左红外被触发
	{
		delay_rtos(0,0,0,20);
	}	
	
	while(g_Senser_InPut.gunt_IR_L)					//等待左红外不被触发
	{
		delay_rtos(0,0,0,20);
	}
	delay_rtos(0,0,0,100);
	while(g_Senser_InPut.gunt_IR_L)					//等待左红外不被触发
	{
		delay_rtos(0,0,0,20);
	}
	
	while(!g_Senser_InPut.gunt_IR_R && temp_i--)	//等待右红外触发或者到中间
	{
		delay_rtos(0,0,0,5);		
	}
	while(g_Senser_InPut.gunt_IR_L)					//等待左红外不被触发
	{
		delay_rtos(0,0,0,20);
	}	
	GunTong_R(0);
	
	*g_PLC_message[AGV_SYS.ID-1].Flag_RecTray_Finish = 1;	//AGV告诉PLC托盘接收完成
	
	delay_rtos(0,0,1,0);							//给PLC的1秒检测时间
	
	
	//除了接收完成不清  其他都在这清
//发炉号前清
}
void GunTong_Trun_R_DOWN(void)	//右侧卸货
{
	
	while(!*g_PLC_message[AGV_SYS.ID-1].Flag_DownTray_allowed)	//等待PLC的允许出托盘信号
	{
		delay_rtos(0,0,0,20);
	}
	
	GunTong_R(1);
	while(!g_Senser_InPut.gunt_IR_R)	//等待右红外被触发
	{
		delay_rtos(0,0,0,20);
	}
	delay_rtos(0,0,0,100);
	while(!g_Senser_InPut.gunt_IR_R)	//等待右红外被触发
	{
		delay_rtos(0,0,0,20);
	}
	while(g_Senser_InPut.gunt_IR_R)		//等待右红外没有被触发
	{
		delay_rtos(0,0,0,20);
	}
	delay_rtos(0,0,0,100);
	while(g_Senser_InPut.gunt_IR_R)		//等待右红外没有被触发
	{
		delay_rtos(0,0,0,20);
	}		

	while(!*g_PLC_message[AGV_SYS.ID-1].Flag_PLCRecTray_Finish)	//等待PLC接收托盘完成信号
	{
		delay_rtos(0,0,0,20);
	}	

	GunTong_R(0);	
	
	delay_rtos(0,0,2,0);

}
void GunTong_Trun_R_UP(void)	//右侧上货
{
	u8 temp_i = AGV_SYS.GunT_daozhong_time/5;					//对中延时

	while(!*g_PLC_message[AGV_SYS.ID-1].Flag_RecTray_start)		//等PLC的请求信号
	{
		delay_rtos(0,0,0,20);
	}
	*g_PLC_message[AGV_SYS.ID-1].Flag_RecTray_Ready = 1;		//AGV告诉PLC接收托盘准备就绪

	
	GunTong_L(1);
	while(!g_Senser_InPut.gunt_IR_R)	//等待右被触发
	{
		delay_rtos(0,0,0,20);
	}
	delay_rtos(0,0,0,100);
	while(!g_Senser_InPut.gunt_IR_R)	//等待右被触发
	{
		delay_rtos(0,0,0,20);
	}	
	
	while(g_Senser_InPut.gunt_IR_R)		//等待右不被触发
	{
		delay_rtos(0,0,0,20);
	}
	delay_rtos(0,0,0,100);
	while(g_Senser_InPut.gunt_IR_R)		//等待右不被触发
	{
		delay_rtos(0,0,0,20);
	}	
	
	while(!g_Senser_InPut.gunt_IR_L && temp_i--)
	{
		delay_rtos(0,0,0,5);		
	}
	while(g_Senser_InPut.gunt_IR_R)		//等待右不被触发
	{
		delay_rtos(0,0,0,20);
	}
	GunTong_L(0);				//货物在中间
	
	*g_PLC_message[AGV_SYS.ID-1].Flag_RecTray_Finish = 1;	//AGV告诉PLC托盘接收完成	
	
	delay_rtos(0,0,2,0);
}


u8  g_GunTong_Flag_stop = 1;			//手动控制滚筒的停止状态标志	1:停止中 0:运行中
void SD_GunTong(void)
{
	if(g_AGV_Sta.Car_Auto2Manu_mode) 					//1:手动模式
	{
		if(g_AGV_yaokong.GunTong_Enable == 1)			//摇杆按键按下使能
		{
			if(g_AGV_yaokong.GunTong_dir == 1 && g_GunTong_Flag_stop)		//摇杆左摆--滚筒左转
			{
				g_GunTong_Flag_stop = 0;
				GunTong_L(1);				
			}
			else if(g_AGV_yaokong.GunTong_dir == 2 && g_GunTong_Flag_stop)		//摇杆右摆--滚筒右转
			{
				g_GunTong_Flag_stop = 0;
				GunTong_R(1);
			}	
			else if(g_AGV_yaokong.GunTong_dir == 0)		//滚筒停止
			{
				if(!g_GunTong_Flag_stop)
				{
					GunTong_L(0);								//左右停
					g_GunTong_Flag_stop = 1;		
				}
			}				
		}
		else if(g_AGV_yaokong.GunTong_Enable == 0)	
		{
			if(!g_GunTong_Flag_stop)
			{
				GunTong_L(0);								//左右停
				g_GunTong_Flag_stop = 1;		
			}
		}
	}
	else if(!g_AGV_Sta.Car_Auto2Manu_mode) 				//从手动切换到自动后确保完全停下来
	{
		if(!g_GunTong_Flag_stop)
		{
			GunTong_L(0);								//左右停
			g_GunTong_Flag_stop = 1;		
		}
		
	}
}



