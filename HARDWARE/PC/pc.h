#ifndef _PC_H
#define _PC_H

#include "my_include.h"

//#define IDID pppp	


typedef struct
{
	u16 *Task_ID;			//������	
	u16 *Task_Recived;		//�յ�����
	u16 *Task_RunStart;		//��ʼִ��
	u16 *Task_RunFinish;	//ִ�����
	u16 *Position_Last;		//��һ��λ��
	u16 *Position_Now;		//��ǰλ��
	u16 *Position_next;		//��һ��λ��
	u16 *RunState;			//����״̬
	u16 *Warning;			//������Ϣ
	u16 *guan_ID;			//¯�ܵ�ID

}dispatch_message;	//����

typedef struct
{
	u16 *StoveID;						 //��ɢ¯¯��			
	u16 *Flag_Position_OK;            	 //AGV��ָ��λ��		
	u16 *Flag_RecTray_Ready;          	 //AGV��������׼������	
	u16 *Flag_RecTray_Finish;         	 //�������			
	u16 *AGV2PLC_Heard;					 //AGV��PLC������1-60
	u16 *TO_PLC_Task_data;				 //��PLC��ǰ��λ������Ϣ

	u16 *Flag_DownTray_allowed;      	 //����AGV������		
	u16 *Flag_PLCRecTray_Finish;     	 //���������			
	u16 *Flag_RecTray_start;         	 //�����������	
	u16 *PLC2AGV_Heard;					 //PLC��AGV������1-60(Ŀǰûʹ��)
	

}PLC_message;		//PLC¯��

typedef struct
{
	u16 *BatteryLevel;					  //����			
	u16 *Voltage;                         //��ѹ			
	u16 *BatteryCycleTimes;               //���ѭ������	
	u16 *LowPowerWarningVal;              //�͵���������ֵ	
	u16 *SpeedClass;                      //��ǰ�ٶȵ�λ	
	u16 *Run_Mode;                        //��ǰģʽ		
	u16 *Run_Direction;                   //��ǰ����		
	u16 *ForkingDirection;                //��ǰ�ֲ淽��	
	u16 *MagneticNavigation_1;            //�ŵ�������1		
	u16 *MagneticNavigation_2;            //�ŵ�������2		
	u16 *MagneticNavigation_3;            //�ŵ�������3		
	u16 *MagneticNavigation_4;            //�ŵ�������4		
	u16 *Sta_EmergencyStop;               //��ͣ��ť״̬	
	u16 *IR_Roller_L;                     //��Ͳ������	
	u16 *IR_Roller_R;                     // ��Ͳ�Ҳ����	
	u16 *RT_RFID;						  //ʵʱ�ر�
}RT_message;		//ʵʱ��Ϣ

extern u16 g_MessageCompare_buff[100];
extern dispatch_message 	g_dispatch_message;
extern PLC_message 			g_PLC_message[2];
extern RT_message 			g_RT_message;


//��ȡ��λ��������·����Ϣ��ִ��
void Get_PC_data(u8 type_path,u16 *PC_data);
//����λ��ͨ�ŵĵײ����ݷ��ͺ���
void CompareVal_Send(u8 start_num,u8 end_num);
//��ȡ��λ����Ҫ�ķ�ʵʱ�Ե�AGV��Ϣ
void Get_PDO_Data(void);

void Get_SDO_Data(void);


//(λ)����0 ��е��ײ1 ����2 �������3 ������4 �����ϵ�5 
void Get_Warning_data(void);



#endif







