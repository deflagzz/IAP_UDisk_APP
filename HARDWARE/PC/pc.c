#include "pc.h"

u16 g_MessageCompare_buff[100];

dispatch_message g_dispatch_message =
{
	&Dbus.Register[1],			//	u16 *Task_ID;			//������	
	&Dbus.Register[2],			//	u16 *Task_Recived;		//�յ�����
	&Dbus.Register[3],			//	u16 *Task_RunStart;		//��ʼִ��
	&Dbus.Register[4],			//	u16 *Task_RunFinish;	//ִ�����
	&Dbus.Register[5],			//	u16 *Position_Last;		//��һ��λ��
	&Dbus.Register[6],			//	u16 *Position_Now;		//��ǰλ��
	&Dbus.Register[7],			//	u16 *Position_next;		//��һ��λ��
	&Dbus.Register[8],			//	u16 *RunCondition;		//����״̬
	&Dbus.Register[9],			//	u16 *Warning;			//������Ϣ
	&Dbus.Register[10],			//  ¯�ܵ�ID
};

//Ĭ��AGV����Ϊ1,��Ӧ¯��Ϊ��ɢ¯,�Ĵ�����ַΪ20��30
//	  AGV����Ϊ2,��Ӧ¯��ΪPE¯  ,�Ĵ�����ַΪ31��41
PLC_message g_PLC_message[2] = 
{
	//��ɢ¯ -- AGV_ID:1 -- [0]
	//PE¯   -- AGV_ID:2 -- [1]
	{
		&Dbus.Register[20],			//u16 *StoveID;						 //��ɢ¯¯��			
		&Dbus.Register[21],			//u16 *Flag_Position_OK;             //AGV��ָ��λ��		
		&Dbus.Register[22],			//u16 *Flag_RecTray_Ready;           //AGV��������׼������	
		&Dbus.Register[23],			//u16 *Flag_RecTray_Finish;          //�������			
		&Dbus.Register[24],			//u16 *AGV2PLC_Heard;			     //AGV��PLC������1-60
		&Dbus.Register[25],			//u16 *TO_PLC_Task_data;			 //��PLC��ǰ��λ������Ϣ
		
		&Dbus.Register[26],			//u16 *Flag_DownTray_allowed;      	 //����AGV������		
		&Dbus.Register[27],			//u16 *Flag_PLCRecTray_Finish;     	 //���������			
		&Dbus.Register[28],			//u16 *Flag_RecTray_start;         	 //�����������		
		&Dbus.Register[29],			//u16 *PLC2AGV_Heard;				 //PLC��AGV������1-60(Ŀǰûʹ��)
	},
	{
		&Dbus.Register[31],			//u16 *StoveID;						 //��ɢ¯¯��			
		&Dbus.Register[32],			//u16 *Flag_Position_OK;             //AGV��ָ��λ��		
		&Dbus.Register[33],			//u16 *Flag_RecTray_Ready;           //AGV��������׼������	
		&Dbus.Register[34],			//u16 *Flag_RecTray_Finish;          //�������			
		&Dbus.Register[35],			//u16 *AGV2PLC_Heard;			     //AGV��PLC������1-60		
		&Dbus.Register[36],			//u16 *TO_PLC_Task_data;			 //��PLC��ǰ��λ������Ϣ			

		&Dbus.Register[37],			//u16 *Flag_DownTray_allowed;      	 //����AGV������		
		&Dbus.Register[38],			//u16 *Flag_PLCRecTray_Finish;     	 //���������			
		&Dbus.Register[39],			//u16 *Flag_RecTray_start;         	 //�����������		
		&Dbus.Register[40],			//u16 *PLC2AGV_Heard;				 //PLC��AGV������1-60(Ŀǰûʹ��)		
	
	}	
};

RT_message g_RT_message = 
{
	&Dbus.Register[51],			//u16 *BatteryLevel;					//����			
	&Dbus.Register[52],			//u16 *Voltage;                         //��ѹ			
	&Dbus.Register[53],			//u16 *BatteryCycleTimes;               //���ѭ������	
	&Dbus.Register[54],			//u16 *LowPowerWarningVal;              //�͵���������ֵ	
	&Dbus.Register[55],			//u16 *SpeedClass;                      //��ǰ�ٶȵ�λ	
	&Dbus.Register[56],			//u16 *Run_Mode;                        //��ǰģʽ		
	&Dbus.Register[57],			//u16 *Run_Direction;                   //��ǰ����		
	&Dbus.Register[58],			//u16 *ForkingDirection;                //��ǰ�ֲ淽��	
	&Dbus.Register[59],			//u16 *MagneticNavigation_1;            //�ŵ�������1		
	&Dbus.Register[60],			//u16 *MagneticNavigation_2;            //�ŵ�������2		
	&Dbus.Register[61],			//u16 *MagneticNavigation_3;            //�ŵ�������3		
	&Dbus.Register[62],			//u16 *MagneticNavigation_4;            //�ŵ�������4		
	&Dbus.Register[63],			//u16 *Sta_EmergencyStop;               //��ͣ��ť״̬	
	&Dbus.Register[64],			//u16 *IR_Roller_L;                     //��Ͳ������	
	&Dbus.Register[65],			//u16 *IR_Roller_R;                     // ��Ͳ�Ҳ����
	&Dbus.Register[66],			//u16 *RT_RFID;						    //ʵʱ�ر�
};






//��ȡ��λ��������·����Ϣ��ִ��
void Get_PC_data(u8 type_path,u16 *PC_data)
{
	g_AGV_Sta.type_path = type_path;
	HmiTask = 1;								//ѡ��ִ��·��									
	delay_rtos(0,0,0,10);
	AGV_SYS.ToPLC_task = *PC_data;
//	HmiRouteNum = *PC_data;						//·����
//	delay_rtos(0,0,0,100);
//	HmiAutoReload();							//��ȡ��ǰ·����վ����Ϣ
//	delay_rtos(0,0,0,100);
//	g_AGV_Sta.Car_dir = AGV_SYS.yuandian_dir; 	//�����л���ǰ��  
//	delay_rtos(0,0,0,100);
	HmiScreenSetGet = ZiDongJieMian;			//��ת���Զ�����
	delay_rtos(0,0,0,10);
	g_AGV_Sta.Car_Auto2Manu_mode = 0;			//ѡ���Զ�ģʽ
	delay_rtos(0,0,0,10);
	

}




//����λ��ͨ�ŵĵײ����ݷ��ͺ���
void CompareVal_Send(u8 start_num,u8 end_num)
{
	u8 temp_j=0;
	for(temp_j=start_num;temp_j<end_num+1;temp_j++)
	{
		//��������
			//if(Dbus.Register[temp_j] != g_MessageCompare_buff[temp_j])		//���Ƚ�����Ƚ�,����ͬ�Ļ����Ͳ����±仯ֵ
			//{
			//	if(Write_Register(0,temp_j,Dbus.Register[temp_j]))			//���ͳɹ�:1 ʧ��:0
			//	{
			//		g_MessageCompare_buff[temp_j] = Dbus.Register[temp_j];	//���±仯���Ƚ�����
			//	}
			//}
		//��ʱ����
			Post_Register(0,temp_j,Dbus.Register[temp_j]);
	}
}
//��ȡ��λ����Ҫ�ķ�ʵʱ�Ե�AGV��Ϣ
void Get_PDO_Data(void)
{
	//
	//������λ���ĵ͵�����ֵ���ò�����flash
	//
	//if(*g_RT_message.LowPowerWarningVal != Battery_Warining.Warining_Val_NoBattery)
	//{
	//	Battery_Warining.Warining_Val_NoBattery = *g_RT_message.LowPowerWarningVal;
	//	SystemParameter[70] = Battery_Warining.Warining_Val_NoBattery;
	//	SetOneParameterToSystem(SystemParameter[70], 70);		
	//}
	
	
	*g_RT_message.BatteryLevel 			= 	Sys_battery;							 //�ٷֱ�1-100	
	*g_RT_message.Voltage 				= 	g_battery.dianya;                        //��λ��mV
	*g_RT_message.BatteryCycleTimes 	= 	g_battery.XunHuan_time;                  //��ֵ
	*g_RT_message.LowPowerWarningVal 	= 	Battery_Warining.Warining_Val_NoBattery; //1-100
	*g_RT_message.SpeedClass            =	AGV_SYS.Auto_Speed_bili;                 //���٣����٣����٣��Խ��ٶ�
	*g_RT_message.Run_Mode              =	g_AGV_Sta.Car_Auto2Manu_mode;            //�Զ���0���ֶ���1
	*g_RT_message.Run_Direction         =	g_AGV_Sta.Car_dir;                       //ǰ����0�����ˣ�1
	*g_RT_message.ForkingDirection      =	g_AGV_Sta.Car_fencha_dir;                //1:��� 2:�ҷ� 11:ǰ��� 12:ǰ�ҷ� 21:����� 22:���ҷ�
	*g_RT_message.MagneticNavigation_1  =	g_CT_bit[1];                             //16���㰴λȡ��
	*g_RT_message.MagneticNavigation_2  =	g_u16_val[2];                            //16���㰴λȡ��
	*g_RT_message.MagneticNavigation_3  =	g_CT_bit[3];                             //16���㰴λȡ��
	*g_RT_message.MagneticNavigation_4  =	g_u16_val[4];                            //16���㰴λȡ��
	*g_RT_message.Sta_EmergencyStop     =	!g_motec_init.Init_OK;                   //������0����ͣ��1
	*g_RT_message.IR_Roller_L           =   g_Senser_InPut.gunt_IR_L;                //������0��������1
	*g_RT_message.IR_Roller_R           =   g_Senser_InPut.gunt_IR_R;                //������0��������1
	*g_RT_message.RT_RFID				=   g_Get_RFID_buff[1]<<8|g_Get_RFID_buff[0];
}

void Get_SDO_Data(void)
{
	//if(g_RunSta.Run)
	//{
	//	*g_dispatch_message.RunState = 1;
	//}
	//if(g_RunSta.readyed)
	//{
	//	*g_dispatch_message.RunState = 2;
	//}
//	if(g_RunSta.chongdian)
//	{
//		*g_dispatch_message.RunState = 3;
//	}
//	if(!*g_dispatch_message.Warning)
//	{
//	
//	
//	}



}

void Bit2U16(u16 *warning,u8 bit_num,u8 set_val)
{
	if(set_val)
	{
		*warning |= (0x0001 << bit_num);
	}
	else
	{
		*warning &= ~(0x0001 << bit_num);
	}
}




//(λ)����0 ��е��ײ1 ����2 �������3 ������4 �����ϵ�5 
void Get_Warning_data(void)			//��ȡAGVϵͳ�ľ�����Ϣ--���ȼ�������
{
	//��е����1
	if(g_Warning.jixie_qian || g_Warning.jixie_hou)
	{
		Bit2U16(g_dispatch_message.Warning,1,1);
		HmiTaskState = 2;					//ǰ���ϰ�
	}
	else
	{
		Bit2U16(g_dispatch_message.Warning,1,0);
	}
	//��������2
	if(g_Warning.chugui)
	{
		Bit2U16(g_dispatch_message.Warning,2,1);
		HmiTaskState = 6;		
	}
	else
	{
		Bit2U16(g_dispatch_message.Warning,2,0);
	}
	//�������3
	if(g_Warning.IR_qian || g_Warning.IR_hou)
	{
		Bit2U16(g_dispatch_message.Warning,3,1);
		HmiTaskState = 2;					//ǰ���ϰ�
	}
	else
	{
		Bit2U16(g_dispatch_message.Warning,3,0);
	}
	//������4
	if(g_Warning.Low_battery)
	{
		Bit2U16(g_dispatch_message.Warning,4,1);
	}
	else
	{
		Bit2U16(g_dispatch_message.Warning,4,0);
	}
	//�����ϵ�5
	if(g_Warning.Drive_NOPwoer)
	{
		Bit2U16(g_dispatch_message.Warning,5,1);
		g_user_stop_buttun = 1;
		HmiTaskState = 1;					
	}
	else
	{
		Bit2U16(g_dispatch_message.Warning,5,0);
		g_user_stop_buttun = 0;
	}
	//�ر����6
	if(g_Warning.RFID_err)
	{
		Bit2U16(g_dispatch_message.Warning,6,1);
		HmiTaskState = 3;
	}
	else
	{
		Bit2U16(g_dispatch_message.Warning,6,0);
	}

}















