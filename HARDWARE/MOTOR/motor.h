#ifndef _MOTOR_H
#define _MOTOR_H

#include "my_include.h"




typedef struct
{
	u8 XunZ_OK_qian_1;
	u8 XunZ_OK_qian_2;	

	u8 XunZ_OK_hou_1;
	u8 XunZ_OK_hou_2;	
	
	u8 XunZ_OK_go_on_Both;
	u8 XunZ_OK_go_back_Both;
	
	u8 XunZ_OK_AGV;
	
	u8 XunZ_Start;
	
}AGV_CtXunZheng;

typedef struct
{
//	u8 button_Car;				//�������
//	u8 button_Screen;			//������
//	u8 button_network_PC;		//��λ��
//	u8 button_yaokong_youxian;	//����ң��
	
	u8 Start_AGV_SysCode;		//����--ϵͳ�������
	u8 Stop_AGV_SysCode;		//ֹͣ--ϵͳ�������
	
	u8 Start_IR;				//�������
	u8 Start_jixie;				//��е����
	
	u8 button_bizhang_Start;			//���ϴ�����--�ܿ���		
	
	u8 Start_Auto_PID;			//�ײ�PID�����Ŀ���--�Զ�
	u8 Start_Manu_PID;			//�ײ�PID�����Ŀ���--�ֶ�
	
	u8 Start_button_Car;		//����--�ܿ���
	u8 Stop_button_Car;			//ֹͣ--�ܿ���
	

}AGV_Start_flag;








extern float g_qianlun_L2R_val[2] ;		//ǰ������ת����ֵ
extern float g_houlun_L2R_val[2]  ;		//��������ת����ֵ


extern AGV_CtXunZheng g_CtXunZheng;
extern AGV_Start_flag g_Start_flag;

extern u8 g_XZ_Ok;
extern u8 g_XZ_Beep;




void motor_init(void);

void QJ(void);
void HT(void);
void ZY(void);
void YY(void);
void stop(void);


void Motor_Zzhuan(u8 Motor,u32 PWM);           //���ǵ�������ڵĿ��ƴ�
void Motor_Fzhuan(u8 Motor,u32 PWM);
void MotoStop(u8 num);
void Moter_EnableAll(void);

void DWQ_XZ_qian(void);
void DWQ_XZ_hou(void);

void DwqXunZheng_QH(void);
void CtXunZheng_qian(u8 cidaohang_id,u8 XZ_dir,u16 xunzheng_speed0);
void CtXunZheng_hou(u8 cidaohang_id,u8 XZ_dir,u16 xunzheng_speed);
void check_CtXunZ_OK(u16 XunZ_speed);
void AGV_System_Start(void);
void AGV_System_Stop(void);
void AGV_Stop2Start(void);

void motec_pulse(u8 speed);	//0~100
void IO_moni_pulse(u16 tem_delay);
void motec_pulse(u8 speed);	//0~100




void LunZi_Go(u8 ID,u16 temp_speed);
void LunZi_Back(u8 ID,u16 temp_speed);
	











#endif

