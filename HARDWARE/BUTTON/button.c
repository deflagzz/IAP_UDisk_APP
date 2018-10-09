#include "button.h"


Senser_InPut  g_Senser_InPut;
Senser_Enable g_Senser_Enable = 
{
	1,
	1,
	1,
	1,
	1,
	1
}
;









//PF4 -- 停止
//PF5 -- 启动
//PF6 -- 左_滚筒红外对射 	-- (原急停)

//PF14-- 前_红外避障 		-- (牵引杆开入2)   远
//PF10-- 后_红外避障 		-- (牵引杆开入1)	远

//PF9 -- 前红外---近
//PF8 -- 后红外--近

//PA6 -- 前防撞
//PA7 -- 后防撞

//PF7 -- 右_滚筒红外对射 	-- (备用开入1) 


//外部中断初始化程序
void button_input_init(void)//上拉输入,低电平触发
{	
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
		
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7| GPIO_Pin_8| GPIO_Pin_9|
	GPIO_Pin_10| GPIO_Pin_14; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
}



u8 AGV_input_24V_buff[16];
u8 g_stop_button_down;
u8 g_start_button_down;
void agv_24V_input(void)	//未做按键消抖,后面做
{
	//按钮一直按可以被触发很多次,但是只能语音报一声
	if(!g_button_stop)								//面板停止按钮	0:触发	//g_jixieKEy_stop
	{
		g_Senser_InPut.button_Stop = 1;				//1置位
	}
	else
	{
		g_Senser_InPut.button_Stop = 0;
		g_stop_button_down = 0;						//按下标志复位
	}
		
	if(!g_button_start)								//面板启动按钮	g_jixieKEY_start
	{
		g_Senser_InPut.button_Start = 1;
	}
	else
	{
		g_start_button_down = 0;
		g_Senser_InPut.button_Start = 0;			//按下标志复位
	}		
	
	if(g_Senser_Enable.IR_qian_yuan) //AGV_SYS.Key_IR_jin
	{
		if(!g_flag_IR_qian_yuan)					//前远红外  	//g_IR_yuan_CAR_qian
		{
			g_Senser_InPut.IR_qian_yuan =  1;		//1:置位
		}
		else
		{
			g_Senser_InPut.IR_qian_yuan =  0;
		}		
	}
	else
	{
		g_Senser_InPut.IR_qian_yuan =  0;					
	}


	if(g_Senser_Enable.IR_hou_yuan)
	{
		if(!g_flag_IR_hou_yuan)						//后远红外		//g_IR_yuan_CAR_hou
		{
			g_Senser_InPut.IR_hou_yuan = 1;
		}
		else
		{
			g_Senser_InPut.IR_hou_yuan = 0;
		}			
	}	
	else
	{
			g_Senser_InPut.IR_hou_yuan = 0;
		
	}	

	if(g_Senser_Enable.IR_qian_jin)
	{
		if(!g_flag_IR_qian_jin)						//前近红外  	//g_IR_jin_CAR_qian
		{
			g_Senser_InPut.IR_qian_jin = 1;
			g_Warning.IR_qian = 1;
		}
		else
		{
			g_Senser_InPut.IR_qian_jin= 0;
			g_Warning.IR_qian = 0;
		}		
	}	
	else
	{
			g_Senser_InPut.IR_qian_jin= 0;
			g_Warning.IR_qian = 0;
	}	
	
	if(g_Senser_Enable.IR_hou_jin)
	{
		if(!g_flag_IR_hou_jin)						//后近红外  	//g_IR_jin_CAR_hou
		{
			g_Senser_InPut.IR_hou_jin = 1;
			g_Warning.IR_hou = 1;
		}
		else
		{
			g_Senser_InPut.IR_hou_jin =  0;
			g_Warning.IR_hou = 0;
		}	
	}
	else
	{
			g_Senser_InPut.IR_hou_jin =  0;
			g_Warning.IR_hou = 0;
	}	
	
	if(g_Senser_Enable.jixie_qian)
	{	
		if(!g_flag_fangzhuang_qian)					//机械前		g_jiexie_qian
		{
			g_Senser_InPut.JiXie_qian = 1;
			g_Warning.jixie_qian = 1;
		}
		else
		{
			g_Senser_InPut.JiXie_qian = 0;
			g_Warning.jixie_qian = 0;
		}		
	}
	else
	{
			g_Senser_InPut.JiXie_qian = 0;
			g_Warning.jixie_qian = 0;
	}

	if(g_Senser_Enable.jixie_qian)
	{
		if(!g_flag_fangzhuang_hou)					//机械后		g_jiexie_hou
		{
			g_Senser_InPut.JiXie_hou = 1;
			g_Warning.jixie_hou = 1;
		}
		else
		{
			g_Senser_InPut.JiXie_hou = 0;
			g_Warning.jixie_hou = 0;
		}		
	}
	else
	{
			g_Senser_InPut.JiXie_hou = 0;
			g_Warning.jixie_hou = 0;
	}
		
	
	
	if(!g_flag_guntong_zuo)				//g_IR_guntong_left
	{
		g_Senser_InPut.gunt_IR_L = 1;		
	}
	else
	{
		g_Senser_InPut.gunt_IR_L = 0; 
	}	
	
	if(!g_flag_guntong_you)				//g_IR_guntong_right
	{
		g_Senser_InPut.gunt_IR_R = 1;
	}
	else
	{
		g_Senser_InPut.gunt_IR_R = 0;
	}	
	
	







}
u8 g_temp_i[4];
void SD2ZD_check_UP(void)
{

	
	if(g_shoudong_manual == 1 && !g_temp_i[0])						//屏幕的手动按键按下时
	{
		Shou_Dong();							//切到手动程序	
		g_temp_i[0] = 1;			 
	}
	else if(g_shoudong_auto == 1 && !g_temp_i[0])					//屏幕的自动按键按下时
	{
		Zi_Dong();								//切到自动程序		
		g_temp_i[0] = 1;		
	}
	else if(g_shoudong_manual == 0 && g_shoudong_auto == 0)
	{
		g_temp_i[0] = 0;		
	}
}

void ZD_check_UP(void)
{
	
	if(g_shoudong_start == 1 && !g_temp_i[1])			//启动
	{
		HmiTaskState = 5;				//正在运行
		g_AGV_speaker_flag.start = 1;		//自动模式下:启动的语音播报
		delay_rtos(0,0,0,g_Speaker_delay);		
		g_temp_i[1] = 1;		
	}

	else if(g_shoudong_stop == 1 && !g_temp_i[1])		 	//停止
	{
		HmiTaskState = 4;					//停止
		g_AGV_speaker_flag.stop = 1;
		delay_rtos(0,0,0,g_Speaker_delay);	
		g_temp_i[1] = 1;	
	}
	else if(g_shoudong_goto == 1 && !g_temp_i[1])		//自动模式下,设置行走方向
	{
		Qian_Jin();		
		g_temp_i[1] = 1;	
	}
	else if(g_shoudong_goback == 1 && !g_temp_i[1]) 	//自动模式下,设置行走方向
	{
		Hou_Tui();	
		g_temp_i[1] = 1;	
	}
	else if(g_Manu_L_FenCha == 1 && !g_temp_i[1]) 		//自动模式下,设置分叉方向-左
	{
		Zuo_Fen();
		g_temp_i[1] = 1;	
	}	
	else if(g_Manu_R_FenCha == 1 && !g_temp_i[1]) 		//自动模式下,设置分叉方向-右
	{
		You_Fen();
		g_temp_i[1] = 1;	
	}	
	else if(g_shoudong_start == 0&&g_shoudong_stop == 0&&g_shoudong_goto == 0&&g_shoudong_goback == 0&&g_Manu_L_FenCha == 0&&g_Manu_R_FenCha == 0)
	{
		g_temp_i[1] = 0;	

	}
}


void SD_check_UP(void)
{

	
	if(g_shoudong_guntong_youzhuan == 1 && !g_temp_i[2])				//辊筒右转
	 {
	//		g_AGV_speaker_flag.GunT_R = 1;
	//		delay_rtos(0,0,0,10);
	//	 
	//		guntong_start = 1;
	//		guntong_fanzhuan = 1;
			GunTong_R(1);
			g_temp_i[2] = 1;	
	 }
	//else if(g_shoudong_guntong_youzhuan == 0 && !temp_i)
	//{
	//	g_AGV_speaker_flag.GunT_stop = 1;
	//	delay_rtos(0,0,0,10);
	// 
	//	guntong_start = 0;
	//	guntong_fanzhuan = 0;
	//	temp_i = 1;	
	//}
	 else if(g_shoudong_guntong_zuozhuan == 1 && !g_temp_i[2])				//辊筒左转
	 {
	//		g_AGV_speaker_flag.GunT_L = 1;
	//		delay_rtos(0,0,0,10);
	//		guntong_start = 1;	
		 
			GunTong_L(1);
		 
			g_temp_i[2] = 1;	
	 }	
	 else if(g_shoudong_guntong_youzhuan == 0&&g_shoudong_guntong_zuozhuan == 0&&g_temp_i[2])
	 {
			GunTong_L(0);
			g_temp_i[2] = 0;		
	 }	

}


void ZD_check_UP_AUTO(void)								//自动行走界面
{

	if(g_shoudong_start == 1 && !g_temp_i[3])			//启动
	{
		HmiTaskState = 5;				//正在运行
		g_AGV_speaker_flag.start = 1;		//自动模式下:启动的语音播报
		delay_rtos(0,0,0,g_Speaker_delay);		
				
		g_temp_i[3] = 1;		
	}

	else if(g_shoudong_stop == 1 && !g_temp_i[3])		 	//停止
	{
		HmiTaskState = 4;					//停止
		g_AGV_speaker_flag.stop = 1;
		delay_rtos(0,0,0,g_Speaker_delay);	
		g_temp_i[3] = 1;	
	}

	else if(g_shoudong_start == 0&&g_shoudong_stop == 0)
	{
		g_temp_i[3] = 0;	

	}
}

u16 Last_speed_AGV;
void IR_yuan(u16 *last_speed,u16 *agv_spped)
{
	
	if(g_Senser_InPut.IR_hou_yuan)	//远红外触发
	{
		if(!last_speed)
		{
			*last_speed = *agv_spped;
		}
		
		*agv_spped = *last_speed/2;
	}
	else
	{
		*agv_spped = *last_speed;
		*last_speed = 0;
	}






}











	

