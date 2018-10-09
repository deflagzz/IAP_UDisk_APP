#ifndef __ROUTE_H
#define __ROUTE_H
#include "my_include.h"


typedef struct
{
	u16 Station_DiBiao_ID;		//վ��ر��
	u8 	motion;					//��վ����		//6
	u8  speed;					//��վ�ٶ�		//4
	u8  delay;					//��վ��ʱ
	
	u8  fencha;					//�ֲ涯��
	u8  IR_bizhang;				//������Ͽ���
	u8  guntong;				//��Ͳ����

}AGV_station;





//////////////////flash�ڴ����//////////////////////////////////////////////////////////////////

//�����ʵ���������ø����洢�����
//ϵͳ����
#define SystemParaNum 101  //ϵͳ��Ϣ����������0�����ж�flash�Ƿ񱻳�ʼ��������״̬�Ƿ�����
extern u16 SystemParameter[SystemParaNum];//ϵͳ����

//·��: ��500��·����ÿ��·��100��վ�㣬ÿ��վ��20����Ϣ��ÿ����Ϣ2���ֽ�
#define RouteNum 		500  //·������
#define StationNum 		100  //ÿ��·������վ����
#define StaiionInfor 	20 	 //ÿ��վ�������Ϣ��

extern AGV_station agv_routr2station[StationNum];		//·����վ��Ķ�ά����

#define RouteStationNumAdress(n) SystemParaNum+n-1  //ÿ��·������վ������Ϣ��ַ
#define NowRouteInforAdress(n)       RouteStationNumAdress(RouteNum)+1+StationNum*StaiionInfor*(n-1)  //��ǰ·����Ϣ��ַ
#define NowStationInforAdress(m,n)    NowRouteInforAdress(m)+StaiionInfor*(n)//��ǰ·������ǰվ����Ϣ��ַ
extern u16 RouteStationNum[RouteNum]; 		//ÿ��·������վ����
extern u16 NowRouteInfor[StationNum][StaiionInfor];   //��ǰ·����Ϣ
//extern u16 StationInfor[StaiionInfor];          //����վ����Ϣ       




//����: ��500�����̣�ÿ������100����ÿ��5����Ϣ��ÿ����Ϣ2���ֽ�
#define ProcessNum 500  //��������
#define StepNum 100 //ÿ�����̰�������
#define StepInfor 5 //ÿ��������Ϣ��

#define ProcessStepNumAdress(n)   NowRouteInforAdress(RouteNum+1)+n  //ÿ�����̰���������Ϣ��ַ
#define NowProcessInforAdress(n)  ProcessStepNumAdress(ProcessNum)+1+StepNum*StepInfor*(n-1)  //��ǰ������Ϣ��ַ
#define NowStepInforAdress(m,n)  NowProcessInforAdress(m)+StepInfor*(n)  //��ǰ���̡���ǰ������Ϣ��ַ
extern u16 ProcessStepNum[ProcessNum]; 		   //ÿ�����̰�������
extern u16 NowProcessInfor[StepNum][StepInfor];  //��ǰ������Ϣ
//extern u16 NowStepInfor[StepInfor];              //����������Ϣ

extern u16 HmiProcessNumFlag; //��һ�����̺ţ��ж����̱仯��
extern u16 HmiRouteNumFlag; //��һ��·���ţ��ж�·���仯��
extern u16 HmiRouteCopiedNumTemp;//������·������ʱ����
extern u16 HmiProcessCopiedNumTemp;//���������̺���ʱ����


//////////////////////////��������ַӳ���/////////////////////////////////////////////////////////////////////

//PLC_OutPut��
#define P_RUN_LED                       PLC_OutPut[1]//��Ļ����ָʾ��
#define Sys_battery 					PLC_Data[51]	//ϵͳ����
//#define P_                       //��Ļ����ָʾ��
//#define P_                       //��Ļ����ָʾ��
//#define P_                       //��Ļ����ָʾ��
//#define P_                       //��Ļ����ָʾ��
//#define P_                       //��Ļ����ָʾ��
//#define P_                       //��Ļ����ָʾ��


#define g_IR_yuan_CAR_qian 		PLC_OutPut[29]	//��ǰԶ�������
#define g_IR_yuan_CAR_hou		PLC_OutPut[30]	//����Զ�������

#define g_IR_jin_CAR_qian		PLC_OutPut[25]  //��ǰ������ 
#define g_IR_jin_CAR_hou		PLC_OutPut[26]  //��������� 

#define g_jiexie_qian			PLC_OutPut[46]	//ǰ��е����
#define g_jiexie_hou			PLC_OutPut[47]	//���е����

#define g_IR_guntong_left		PLC_OutPut[27]	//��Ͳ�����
#define g_IR_guntong_right		PLC_OutPut[28]  //��Ͳ�Һ���

//#define g_IR_qian	 = ZZBZ2; //��ת���״����2
#define g_jixieKEY_start		PLC_OutPut[50]  //����������� -- ����������
#define g_jixieKEy_stop			PLC_OutPut[49]  //���ֹͣ���� -- ����������





//�����������
#define HmiScreenSetGet                 PLC_Data[32]   //���û�ȡ�����������
#define YongHuShouYeJieMian           	27   //�û���ҳ���� 	                                        
#define ShouDongJieMian           	 	3    //�ֶ���������	                                            
#define ChuanGanQiJieMian           	22   //���������� 	
#define JiBenShuJuJieMian           	23   //�������ݽ��� 	
#define ChaBiShuJuJieMian				24   //������ݽ���	 	
#define LeiDaShuJuJieMian				25   //�״����ݽ���	 	
#define DianTiTiaoShiJieMian			26  //��Ͳ���ݽ���		                                             
#define XiTongCanShuJieMian				8    //ϵͳ��������	
//·���滮����ƵĽ���κ궨��
#define LuJingSheZhiJieMian           	9    //·�����ý���
#define LuJingGuiHuaJieMian        		4    //·���滮���� 
#define FuZhiLuJingTanChuJieMian        11   //·�����Ƶ�������  
#define QueDingChaRuZhanDianJieMian     12   //ȷ������վ�����
#define QueDingShanChuZhanDianJieMian   13   //ȷ��ɾ��վ�����
#define XvNiDiBiaoJieMian        		14   //����ر����
//���̹滮����ƵĽ���κ궨��
#define LiuChengSheZhiJieMian           10   //�������ý���
#define LiuChengGuiHuaJieMian           5    //���̹滮����
#define FuZhiLiuChengTanChuJieMian      15   //�������̵�������
#define QueDingChaRuLiuChengJieMian     16   //ȷ���������̽���
#define QueDingShanChuLiuChengJieMian   17   //ȷ��ɾ�����̽���
//����ִ�н���κ궨��
#define ZhiXingLuJingJieMian            18   //ִ��·������
#define ZhiXingLiuChengJieMian          19   //ִ�����̽���
#define ZiDongJieMian                   20   //�Զ����н���
#define QuXiaoRenWuJieMian              21   //ȡ���������
//#define QiDongTiShiJieMian              46   //������ʾ����






#define HmiScreenControlMode PLC_Data[95]   //����ģʽ
#define HmiScreenRunState    PLC_Data[96]   //����״̬  ������ֹͣ
#define HmiCarLocation       PLC_Data[38]   //AGV��ǰλ��


//ϵͳ����
//#define HmiDianTiDiBiao1      //һ¥������ݵĵر�
//#define HmiDianTiDiBiao3      //��¥������ݵĵر�
//#define HmiChuDianTiDiBiao    //�����ݵر�


 	       




#define XZ_Speed40       	 PLC_Data[46] 		//Ѱ������ٶ�
#define XZ_Speed41        	 PLC_Data[48] 		//��λ��Ѱ���ٶȱ�
#define XZ_Speed42       	 PLC_Data[49] 		//����Ѱ���ٶ�
#define XZ_Speed43       	 PLC_Data[50] 		//�������ٶ�


#define path_1          PLC_Data[151] //
#define path_2          PLC_Data[152] //
#define path_3          PLC_Data[153] //


/*
//·���滮
*/
#define HmiRouteNum          PLC_Data[24] //·����
#define HmiStationSerialNum  PLC_Data[29] //վ�����
#define HmiStationNum        PLC_Data[28] //վ����

#define HmiRfidNum           HmiRoadData5 //�ر��



//վ�㶯��
#define HmiRoadData5         PLC_Data[130] 	//�ر�	

#define HmiRoadData6         PLC_Data[36] 	//��վ����	 0��ֹͣ	1��ֹͣ	2:ǰ��	3���Խ�  4������
#define HmiRoadData4         PLC_Data[27] 	//��վ�ٶ� ��λĬ��ѡ������ 0������ 1������ 2������ 3������  
#define HmiRoadData1         PLC_Data[26] 	//��վ��ʱ

#define HmiRoadData2         PLC_Data[30] 	//��·����ֲ� 0������1����ֲ� 2���ҷֲ�
#define HmiRoadData0         PLC_Data[25] 	//Զ�̺��� Ĭ��Ϊ0 0������1����2����
#define HmiRoadData19        PLC_Data[44]   //���̺��� Ĭ��Ϊ0 0������1����2����
#define HmiRoadData3         PLC_Data[31] 	//��Ͳ 0������ 1����ת 2����ת

#define HmiRoadData18        PLC_OutPut[51]	//�ر����� 1:ʵ��ر� 0:����ر�

#define HmiRoadData8         PLC_Data[67] //����¯��		




//����ر�
#define HmiRoadData15		 PLC_OutPut[66]	//0:��ͨ����ر� 1:�ֲ�����ر�
//�ֲ�����ر�
#define HmiRoadData16        PLC_OutPut[53] //�Ƿ񴥷�	//0:������ 1:����
#define HmiRoadData17        PLC_Data[45] 	//��������  
//��ͨ����ر�
#define HmiRoadData7         PLC_OutPut[60] 	//ǰ������Ԫ�Ƿ񴥷�

#define HmiRoadData9         PLC_OutPut[62]		//��������Ԫ
#define HmiRoadData10        PLC_OutPut[63] 		//δʹ��

#define HmiRoadData11        PLC_Data[60]		//ǰ������Ԫ��������
#define HmiRoadData12        PLC_Data[61]			//δʹ��
#define HmiRoadData13        PLC_Data[62]		//��������Ԫ
#define HmiRoadData14        PLC_Data[63] 			//δʹ��




#define HmiRouteEnter        PLC_Data[37] 	//��һ����һ�����¸��ǵ�ȷ������ ȷ��1��ȡ��2

#define HmiStationLast       PLC_Data[35] 	//��һ�� ����:1
#define HmiStationNext       PLC_Data[35] 	//��һ�� ����:2

#define HmiRoutemode         PLC_Data[41] 	//ȷ��������ģʽ���鿴0������1�����2������3������4��ɾ��5
#define HmiRouteCopiedNum    PLC_Data[53] 	//������·����
#define HmiRouteCopiedCount  PLC_Data[55] 	//������վ����
#define HmiNextRfidNum       PLC_Data[90] 	//��һ���ر�
#define ZhiXingLuJingQueDing PLC_Data[94] 	//ִ��·��ȷ����ť



//////���̹滮
#define HmiProcessNum          PLC_Data[77] //���̺�
#define HmiStepNum             PLC_Data[78] //���̲���
#define HmiProcessSerialNum    PLC_Data[79] //�������
#define HmiProcessStartNum     PLC_Data[80] //��ʼ·����
#define HmiProcessAction       PLC_Data[81] //���̶���
#define HmiProcessStopNum      PLC_Data[82] //ѭ���ͽ�������

#define HmiProcessEnter        PLC_Data[83] //ȷ��1��ȡ��2

#define HmiProcessLast         PLC_Data[84] //��һ��
#define HmiProcessNext         PLC_Data[84] //��һ��

#define HmiProcessMode         PLC_Data[85] //ģʽ���鿴0������1�����2������3������4��ɾ��5

#define HmiProcessCopiedNum    PLC_Data[86] //���������̺�
#define HmiProcessCopiedCount  PLC_Data[87] //���������̲���

#define HmiProcessMessage      PLC_Data[88] //���̹滮������ʾ��Ϣ

#define HmiTask                PLC_Data[89] //ִ������ ������0 ִ��·��1 ִ������2

//HmiTaskState���Զ����н��� 	//0:���� 1:��ͣ 2:ǰ���ϰ� 3:�ر��쳣 4:ֹͣ 5:�������� 6:����
#define HmiTaskState           PLC_Data[91] //����״̬	

#define ZhiXingLiuChengQueDing PLC_Data[93] //ִ������ȷ����ť
#define QuXiaoRenWuQueDing     PLC_Data[92] //ȡ������ȷ����ť


#define g_luluzi_ID  	 		PLC_Data[155]	//¯��ID
#define g_guan_ID  	 		    PLC_Data[156]	//����
#define g_quzhoufangzhou  	 	PLC_Data[157]	//����ID
#define g_zhongzhuan_ID  	 	PLC_Data[170]	//��ת̨

//ϵͳ����
#define g_AGV_ID 					PLC_Data[52] 	//����
#define g_sys_set_agvSPEED  		PLC_Data[59] 	//AGV���� -- ���и�	
#define g_AGV_speaker_val     		PLC_Data[98] 	//ϵͳ����
#define g_AGV_LED_car_state 		PLC_OutPut[17]	//����״̬��
#define g_AGV_speaker_key 			PLC_OutPut[24]	//ϵͳ��������

#define HmiDiSu       				PLC_Data[39] 	//����
#define HmiZhongSu     				PLC_Data[19] 	//����
#define HmiGaoSu      				PLC_Data[20] 	//����
#define g_AGV_speed_duijie			PLC_Data[99] 	//��λ�Խ��ٶ�

#define g_AGV_Enable_IR_jin 		PLC_OutPut[34]	//��_����Ŀ��� 
#define g_AGV_Enable_IR_yuan 		PLC_OutPut[40]	//Զ_����Ŀ��� 
#define g_AGV_Enable_JiXie_qian		PLC_OutPut[44]	//ǰ��е�Ŀ���
#define g_AGV_Enable_JiXie_hou  	PLC_OutPut[48]	//���е�Ŀ���

#define g_AGV_yuandian_dir  	    PLC_OutPut[61]	//ԭ���ʼ����
#define g_add_time  	 		    PLC_Data[97]	//�ͻ���ʱ
#define g_yuandi_ID  	 		    PLC_Data[154]	//ԭ��ID
#define g_chongdian_ID  	 		PLC_Data[158]	//ID

//﮵����ϸ��Ϣ
#define Li_dianya 					PLC_Data[123]	//��ѹ
#define Li_Realy_mah				PLC_Data[124]	//ʵʱ����
#define Li_Std_mah 					PLC_Data[125] 	//�������
#define Li_XunHuan_time				PLC_Data[126] 	//ѭ������

#define Li_Warning_val_NoBattery 	PLC_Data[128]	//û�籨��ֵ


#define GunT_zhong_time 			PLC_Data[56] 	//������ʱ
#define GunT_shanghuo_L				PLC_OutPut[31] 	//����ϻ�
#define GunT_shanghuo_R				PLC_OutPut[32] 	//�Ҳ��ϻ�
// = SystemParameter[36];  //
//PLC_Data[129] = SystemParameter[37];  //
// = SystemParameter[38];  //



//�ֶ�����

#define g_shoudong_guntong_zuozhuan 	PLC_OutPut[9]
#define g_shoudong_guntong_youzhuan 	PLC_OutPut[10]
#define g_shoudong_manual				PLC_OutPut[4]
#define g_shoudong_auto					PLC_OutPut[5]
#define g_shoudong_start				PLC_OutPut[11]
#define g_shoudong_stop					PLC_OutPut[12]
#define g_shoudong_goto					PLC_OutPut[6]
#define g_shoudong_goback				PLC_OutPut[8]

#define g_shoudong_turn_right			PLC_OutPut[14]

#define g_shoudong_screen_RFID          PLC_Data[150] //�ر��

#define g_shoudong_screen_speed  		PLC_Data[3]	 //

#define g_Manu2Auto_flag		    	PLC_OutPut[13]

#define g_Manu_L_FenCha					PLC_OutPut[2]  	//��ֲ�
#define g_Manu_R_FenCha					PLC_OutPut[3]	//�ҷֲ�



#define g_Mode_chongdian				PLC_OutPut[57]//���ģʽ�ı�־




//�������ݵ���


#define g_screen_qianCDH1 	 			PLC_Data[4]		//ǰ�ŵ���1
#define g_screen_qianCDH2 				PLC_Data[5]		//ǰ�ŵ���2
#define g_screen_houCDH1 				PLC_Data[140]	//��ŵ���1
#define g_screen_houCDH2 				PLC_Data[139]	//��ŵ���2



#define g_screen_Auto_Kp 	 			PLC_Data[8]		//�Զ�Kp
#define g_screen_Auto_Ki				PLC_Data[9]		//�Զ�Ki
#define g_screen_Auto_Kd				PLC_Data[10]	//�Զ�Kd

#define g_screen_Manu_Kp 	 			PLC_Data[16]	//�ֶ�Kp
#define g_screen_Manu_Ki				PLC_Data[17]	//�ֶ�Ki
#define g_screen_Manu_Kd				PLC_Data[18]	//�ֶ�Kd

#define g_screen_control_TIME 			PLC_Data[21]	//pid����ʱ��

#define g_screen_qianlun_jiaodu 		PLC_Data[1]		//ǰ�ֵ�λ���Ƕ�
#define g_screen_houlun_jiaodu 			PLC_Data[2]		//���ֵ�λ���Ƕ�

#define g_screen_qianlun_ZuoZhi			PLC_Data[14]	//ǰ������
#define g_screen_qianlun_ZhongZhi 		PLC_Data[12]	//ǰ����ֵ
#define g_screen_qianlun_YouZhi 		PLC_Data[15]	//ǰ���Ҽ���

#define g_screen_houlun_ZuoZhi			PLC_Data[6]		//��������
#define g_screen_houlun_ZhongZhi 		PLC_Data[13]	//������ֵ
#define g_screen_houlun_YouZhi 			PLC_Data[7]		//��������

//PLC_Data[23] //δʹ��

//
//�û�����
//
#define g_user_chongdian				PLC_OutPut[7]	//����	//1:��Ч
#define g_user_readyed      			PLC_OutPut[58]	//����		//1:��Ч
#define g_user_stop_buttun     			PLC_OutPut[92]	//��ͣ����

//�û���������
#define user_task_luzi 					PLC_Data[107]
//#define task_1_down						PLC_OutPut[80]	//����
//#define task_1_up						PLC_OutPut[81]	//ȡ��
//#define task_2_down						PLC_OutPut[82]	
//#define task_2_up						PLC_OutPut[83]
//#define task_3_down						PLC_OutPut[84]
//#define task_3_up						PLC_OutPut[85]
//#define task_4_down						PLC_OutPut[86]
//#define task_4_up						PLC_OutPut[87]
//#define task_5_down						PLC_OutPut[88]
//#define task_5_up						PLC_OutPut[89]

#define User2Auto_mode					PLC_OutPut[90]	//0:�û������Զ�ģʽ 1:�û������ֶ�ģʽ

#define g_prtf_autu_speed  	 		    PLC_Data[159]	//
#define g_user_read  	 		  	    PLC_OutPut[160]	//



//---------------ϵͳ------------//
//��ϵͳ��ȡһ������ num:����λ��
extern u16 GetOneParameterFromSystem(u16 num);

//��ȡ����ϵͳ������������Ĭ������SystemParameter
extern void GetAllParameterFromSystem(void);

//����һ��������ϵͳ value:����ֵ num:�������
extern void SetOneParameterToSystem(u16 value,u16 num);

//�������в�����ϵͳ ��SystemParameter��������ݴ���Flash
extern void SetAllParameterToSystem(void);

//---------------·��------------//
//��ȡ·������վ���� num:·����
extern u16 GetRouteStationNum(u16 num);

//��������·��������վ����
extern void SetAllStationNum(void);

//��ȡ·����Ϣ,num:·����
extern void GetRouteData(u16 num);

//����·������վ����
extern void SetRouteStationNum(void);

//����վ����Ϣ,num:·����,nվ���
extern void SetStationData(u16 num,u16 n);

//����·����Ϣ,num:·����
extern void SetRouteData(u16 num);


//����·��վ�����ݵ�����
extern void UpdataStationToHmi(void);

//����·��վ�����ݵ���ǰ(��ǰ����)
void UpdataStationToNow(void);

//����·��վ�����ݵ�����
extern void ClearStationToHmi(void);

//---------------����------------//

//���漰�����������ݣ���ǰ������������Ϣ��
extern void	SetProcessData(void);

//��ȡ���̰�������
extern u16	GetProcessStepNum(u16 num);

//�����������̰�������
extern void SetAllStepNum(void);

//��ȡ�������������ݣ���ǰ������������Ϣ��
extern void	GetProcessData(void);

//��ȡ������ָ���������ݣ�ָ����������Ϣ��
extern void	GetProcessDataFrom(u16 num);

//�����������ݵ�����
extern void ClearStepToHmi(void);

//�����������ݵ�����
extern void UpdataProcessToHmi(void);

//���뼰�����������ݣ���ǰ������������Ϣ��
extern void	InsertProcessData(void);

//ɾ���������������ݣ���ǰ������������Ϣ��
extern void	DeleteProcessData(void);

//�Զ�������ʾ��Ϣ����
extern void HmiAutoReload(void);







#endif
