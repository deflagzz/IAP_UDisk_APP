#include "my_include.h"
#include "dbus.h"

//����Щ���ȼ��������UCOSIII��5��ϵͳ�ڲ�����
//���ȼ�0���жϷ������������� OS_IntQTask()
//���ȼ�1��ʱ�ӽ������� OS_TickTask()
//���ȼ�2����ʱ���� OS_TmrTask()
//���ȼ�OS_CFG_PRIO_MAX-2��ͳ������ OS_StatTask()
//���ȼ�OS_CFG_PRIO_MAX-1���������� OS_IdleTask()

//�������ȼ�
#define START_TASK_PRIO		3
//�����ջ��С	
#define START_STK_SIZE 		512
//������ƿ�
OS_TCB StartTaskTCB;
//�����ջ	
CPU_STK START_TASK_STK[START_STK_SIZE];
//������
void start_task(void *p_arg);                       //��ʼ����

//�������ȼ�
#define Transducer_TASK_PRIO		4
//�����ջ��С	
#define Transducer_STK_SIZE 		512
//������ƿ�
OS_TCB TransducerTaskTCB;
//�����ջ	
CPU_STK Transducer_TASK_STK[Transducer_STK_SIZE];
void Transducer_task(void *p_arg);					//���Զ�ת������

//�������ȼ�
#define FLOAT_TASK_PRIO		5
//�����ջ��С
#define FLOAT_STK_SIZE		512
//������ƿ�
OS_TCB	FloatTaskTCB;
//�����ջ
__align(8) CPU_STK	FLOAT_TASK_STK[FLOAT_STK_SIZE];
//������
void float_task(void *p_arg);						//��������


//�������ȼ�
#define MOTEC_TASK_PRIO		6
//�����ջ��С	
#define MOTEC_STK_SIZE 		256
//������ƿ�
OS_TCB MOTECTaskTCB;
//�����ջ	
CPU_STK motec_TASK_STK[MOTEC_STK_SIZE];
//������
void motec_task(void *p_arg);						//��ʼ��Motec����������

//�������ȼ�
#define Auto_TASK_PRIO		7
//�����ջ��С	
#define Auto_STK_SIZE 		512
//������ƿ�
OS_TCB AutoTaskTCB;
//�����ջ	
CPU_STK Auto_TASK_STK[Auto_STK_SIZE];
//������
void Auto_task(void *p_arg);						//�Զ�ģʽ����

//�������ȼ� 
#define PID_TASK_PRIO		8
//�����ջ��С	
#define PID_STK_SIZE 		512
//������ƿ�
OS_TCB PIDTaskTCB;
//�����ջ	
CPU_STK PID_TASK_STK[PID_STK_SIZE];
//������
void PID_task(void *p_arg);							//PID����

//�������ȼ�
#define Manual_TASK_PRIO		9
//�����ջ��С	
#define Manual_STK_SIZE 		512
//������ƿ�
OS_TCB ManualTaskTCB;
//�����ջ	
CPU_STK Manual_TASK_STK[Manual_STK_SIZE];
//������
void Manual_task(void *p_arg);						//�ֶ�ģʽ����



//�������ȼ�
#define Screen_TASK_PRIO		10
//�����ջ��С	
#define Screen_STK_SIZE 		1024
//������ƿ�
OS_TCB ScreenTaskTCB;
//�����ջ	
CPU_STK Screen_TASK_STK[Screen_STK_SIZE];
//������
void Screen_task(void *p_arg);						//��Ļ����



//�������ȼ�
#define Task5_TASK_PRIO		11
//�����ջ��С	
#define Task5_STK_SIZE 		512
//������ƿ�
OS_TCB Task5_TaskTCB;
//�����ջ	
CPU_STK Task5_TASK_STK[Task5_STK_SIZE];
//������
void Task5_task(void *p_arg);						//�Զ�ִ��·��������

//�������ȼ�
#define WIFI_TASK_PRIO		12
//�����ջ��С	
#define WIFI_STK_SIZE 		512
//������ƿ�
OS_TCB WIFITaskTCB;
//�����ջ	
CPU_STK WIFI_TASK_STK[WIFI_STK_SIZE];
//������
void WIFI_task(void *p_arg);						//WIFI����

//�������ȼ�
#define guntong_TASK_PRIO		13
//�����ջ��С	
#define guntong_STK_SIZE 		128
//������ƿ�
OS_TCB guntongTaskTCB;
//�����ջ	
CPU_STK guntong_TASK_STK[guntong_STK_SIZE];
//������
void guntong_task(void *p_arg);						//��Ͳ����

//�������ȼ�
#define DCv_TASK_PRIO		14
//�����ջ��С	
#define DCv_STK_SIZE 		128
//������ƿ�
OS_TCB DCvTaskTCB;
//�����ջ	
CPU_STK DCv_TASK_STK[DCv_STK_SIZE];
//������
void DCv_task(void *p_arg);							//��ѹ�ɼ�

//�������ȼ�
#define OPENBOX_TASK_PRIO		15
//�����ջ��С	
#define OPENBOX_STK_SIZE 		1024
//������ƿ�
OS_TCB OPENBOXTaskTCB;
//�����ջ	
CPU_STK OPENBOX_TASK_STK[OPENBOX_STK_SIZE];
//������
void openbox_task(void *p_arg);						//��վͨ�Ž��������

//�������ȼ�
#define HEARTBEAT_TASK_PRIO		16
//�����ջ��С	
#define HEARTBEAT_STK_SIZE 		128
//������ƿ�
OS_TCB HEARTBEATTaskTCB;
//�����ջ	
CPU_STK HEARTBEAT_TASK_STK[HEARTBEAT_STK_SIZE];
//������
void heartbeat_task(void *p_arg);					//��δ��

//�������ȼ�
#define Task17_TASK_PRIO		17
//�����ջ��С	
#define Task17_STK_SIZE 		128
//������ƿ�
OS_TCB Task17_TaskTCB;
//�����ջ	
CPU_STK Task17_TASK_STK[Task17_STK_SIZE];
//������
void Task17_task(void *p_arg);						//�ŵ�������

//�������ȼ�
#define Task18_TASK_PRIO		18
//�����ջ��С	
#define Task18_STK_SIZE 		128
//������ƿ�
OS_TCB Task18_TaskTCB;
//�����ջ	
CPU_STK Task18_TASK_STK[Task18_STK_SIZE];
//������
void Task18_task(void *p_arg);						//�ŵ�������

//�������ȼ�
#define Task19_TASK_PRIO		19
//�����ջ��С	
#define Task19_STK_SIZE 		128
//������ƿ�
OS_TCB Task19_TaskTCB;
//�����ջ	
CPU_STK Task19_TASK_STK[Task19_STK_SIZE];
//������
void Task19_task(void *p_arg);						//�ŵ�������

//�������ȼ�
#define Task20_TASK_PRIO		20
//�����ջ��С	
#define Task20_STK_SIZE 		512
//������ƿ�
OS_TCB Task20_TaskTCB;
//�����ջ	
CPU_STK Task20_TASK_STK[Task20_STK_SIZE];
//������
void Task20_task(void *p_arg);						//��λ��ͨ��

//�������ȼ�
#define Task21_TASK_PRIO		21
//�����ջ��С	
#define Task21_STK_SIZE 		128
//������ƿ�
OS_TCB Task21_TaskTCB;
//�����ջ	
CPU_STK Task21_TASK_STK[Task21_STK_SIZE];
//������
void Task21_task(void *p_arg);						//��λ��ͨ��

//�������ȼ�
#define Task22_TASK_PRIO		22
//�����ջ��С	
#define Task22_STK_SIZE 		128
//������ƿ�
OS_TCB Task22_TaskTCB;
//�����ջ	
CPU_STK Task22_TASK_STK[Task22_STK_SIZE];
//������
void Task22_task(void *p_arg);						//AGV�г���

//�������ȼ�
#define Task23_TASK_PRIO		23
//�����ջ��С	
#define Task23_STK_SIZE 		128
//������ƿ�
OS_TCB Task23_TaskTCB;
//�����ջ	
CPU_STK Task23_TASK_STK[Task23_STK_SIZE];
//������
void Task23_task(void *p_arg);						//Զ��������Զ��Ӽ���

//�������ȼ�
#define Task24_TASK_PRIO		24
//�����ջ��С	
#define Task24_STK_SIZE 		128
//������ƿ�
OS_TCB Task24_TaskTCB;
//�����ջ	
CPU_STK Task24_TASK_STK[Task24_STK_SIZE];
//������
void Task24_task(void *p_arg);						//��ʱ��:�ͻ��Զ��峬ʱ�������ԭ��

//�������ȼ�
#define Task25_TASK_PRIO		25
//�����ջ��С	
#define Task25_STK_SIZE 		128
//������ƿ�
OS_TCB Task25_TaskTCB;
//�����ջ	
CPU_STK Task25_TASK_STK[Task25_STK_SIZE];
//������
void Task25_task(void *p_arg);						//��ʱ��:�ͻ��Զ��峬ʱ�������ԭ��

int main(void)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	
	IAP_IRQ_Remap_Init(0x8000);		  				//����ƫ����32K=0x8000

	delay_init(168);  	//ʱ�ӳ�ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�жϷ�������

	LED_Init();         //LED��ʼ��
	beep_init();   		//PA3
	rgb_init();
	button_input_init();
	//motor_init();
	guntong_init();
	
	DMA_adc1_Init();    				//��λ��
	//DMA_Uart2_Init();					//��̫��ת����	//@@���ε����ᵼ�µ��ͨ�Ž���ʧ��@@//
	DMA_Uart3_Init();					//﮵��ͨ��	
	DMA_Uart4_Init();					//������		
	
	ADC1_Configuration();				//��λ���ɼ�
	USART1_Configuration(9600); 		//����1 PA9PA10 ���ڻ���������
	USART2_Configuration(115200);		//��̫��ת���ڵĽӿ�
	USART3_Configuration(9600);			//������﮵�ص������Ŀ� -- 232תTTL����
	uart4_init(9600);					//������485
	//USART6_Configuration(115200);		
	

	//DMA_Uart6_Init();
//	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_Normal);//CAN��ʼ������ģʽ,������500Kbps    
//	CAN2_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_Normal);	
	NVIC_Configuration();

	TIM4_PWM_Init(21000-1,4-1);		//  1000,8   21000 000
	PID_Init();
	
	UserConfigInit();				//�û�������ʼ��	

	WIFI_init(AGV_SYS.ID); 
	
	IAP_U_Disk_Init();				//USB��ʼ��
	                                                                                   
	
	
/**************************************************************************************/
	OSInit(&err);			//��ʼ��UCOSIII
	OS_CRITICAL_ENTER();	//�����ٽ���
	//������ʼ����
	OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		//������ƿ�
								 (CPU_CHAR	* )"start task", 			//��������
                 (OS_TASK_PTR )start_task, 			//������
                 (void		* )0,					//���ݸ��������Ĳ���
                 (OS_PRIO	  )START_TASK_PRIO,     //�������ȼ�
                 (CPU_STK   * )&START_TASK_STK[0],	//�����ջ����ַ
                 (CPU_STK_SIZE)START_STK_SIZE/10,	//�����ջ�����λ
                 (CPU_STK_SIZE)START_STK_SIZE,		//�����ջ��С
                 (OS_MSG_QTY  )0,					//�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
                 (OS_TICK	  )0,					//��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
                 (void   	* )0,					//�û�����Ĵ洢��
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //����ѡ��
                 (OS_ERR 	* )&err);				//��Ÿú�������ʱ�ķ���ֵ
	OS_CRITICAL_EXIT();		//�˳��ٽ���	 
	OSStart(&err);  		//����UCOSIII								 
}
/**************************************************************************************/

void start_task(void *p_arg)		//��ʼ������
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//ͳ������                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//���ʹ���˲����жϹر�ʱ��
    CPU_IntDisMeasMaxCurReset();	
#endif

#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //��ʹ��ʱ��Ƭ��ת��ʱ��
	 //ʹ��ʱ��Ƭ��ת���ȹ���,ʱ��Ƭ����Ϊ1��ϵͳʱ�ӽ��ģ���1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif		
	
	OS_CRITICAL_ENTER();	//�����ٽ���
///////////////////////////////////////////////////////////////////////////////	
	//����Transducer����
	OSTaskCreate((OS_TCB 	* )&TransducerTaskTCB,			//4
				 (CPU_CHAR	* )"Transducer task", 		
                 (OS_TASK_PTR )Transducer_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )Transducer_TASK_PRIO,     
                 (CPU_STK   * )&Transducer_TASK_STK[0],	
                 (CPU_STK_SIZE)Transducer_STK_SIZE/10,	
                 (CPU_STK_SIZE)Transducer_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);								 

	//���������������
	OSTaskCreate((OS_TCB 	* )&FloatTaskTCB,				//5
				 (CPU_CHAR	* )"float test task", 		
                 (OS_TASK_PTR )float_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )FLOAT_TASK_PRIO,     	
                 (CPU_STK   * )&FLOAT_TASK_STK[0],	
                 (CPU_STK_SIZE)FLOAT_STK_SIZE/10,	
                 (CPU_STK_SIZE)FLOAT_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);	

	//�����Զ�����
	OSTaskCreate((OS_TCB 	* )&MOTECTaskTCB,				//6
				 (CPU_CHAR	* )"motec task", 		
                 (OS_TASK_PTR )motec_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )MOTEC_TASK_PRIO,     	
                 (CPU_STK   * )&motec_TASK_STK[0],	
                 (CPU_STK_SIZE)MOTEC_STK_SIZE/10,	
                 (CPU_STK_SIZE)MOTEC_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);
				 
	//�����Զ�����
	OSTaskCreate((OS_TCB 	* )&AutoTaskTCB,				//7
				 (CPU_CHAR	* )"Auto task", 		
                 (OS_TASK_PTR )Auto_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )Auto_TASK_PRIO,     	
                 (CPU_STK   * )&Auto_TASK_STK[0],	
                 (CPU_STK_SIZE)Auto_STK_SIZE/10,	
                 (CPU_STK_SIZE)Auto_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);

	//PID
	OSTaskCreate((OS_TCB 	* )&PIDTaskTCB,					//8
				 (CPU_CHAR	* )"PID task", 		
                 (OS_TASK_PTR )PID_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )PID_TASK_PRIO,     	
                 (CPU_STK   * )&PID_TASK_STK[0],	
                 (CPU_STK_SIZE)PID_STK_SIZE/10,	
                 (CPU_STK_SIZE)PID_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);
				 
	//�����ֶ�����
	OSTaskCreate((OS_TCB 	* )&ManualTaskTCB,				//9
				 (CPU_CHAR	* )"Manual task", 		
                 (OS_TASK_PTR )Manual_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )Manual_TASK_PRIO,     	
                 (CPU_STK   * )&Manual_TASK_STK[0],	
                 (CPU_STK_SIZE)Manual_STK_SIZE/10,	
                 (CPU_STK_SIZE)Manual_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);
				 
	

	//��������������
	OSTaskCreate((OS_TCB 	* )&ScreenTaskTCB,				//10
				 (CPU_CHAR	* )"Screen task", 		
                 (OS_TASK_PTR )Screen_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )Screen_TASK_PRIO,     	
                 (CPU_STK   * )&Screen_TASK_STK[0],	
                 (CPU_STK_SIZE)Screen_STK_SIZE/10,	
                 (CPU_STK_SIZE)Screen_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);	

	//����·����������
	OSTaskCreate((OS_TCB 	* )&Task5_TaskTCB,				//11
				 (CPU_CHAR	* )"Task5 task", 		
				 (OS_TASK_PTR )Task5_task, 			
				 (void		* )0,					
				 (OS_PRIO	  )Task5_TASK_PRIO,     	
				 (CPU_STK   * )&Task5_TASK_STK[0],	
				 (CPU_STK_SIZE)Task5_STK_SIZE/10,	
				 (CPU_STK_SIZE)Task5_STK_SIZE,		
				 (OS_MSG_QTY  )0,					
				 (OS_TICK	  )0,					
				 (void   	* )0,				
				 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
				 (OS_ERR 	* )&err);
				 
	//WIFI
	OSTaskCreate((OS_TCB 	* )&WIFITaskTCB,				//12
				 (CPU_CHAR	* )"WIFI task", 		
                 (OS_TASK_PTR )WIFI_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )WIFI_TASK_PRIO,     	
                 (CPU_STK   * )&WIFI_TASK_STK[0],	
                 (CPU_STK_SIZE)WIFI_STK_SIZE/10,	
                 (CPU_STK_SIZE)WIFI_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);				 
				 
	//WIFI
	OSTaskCreate((OS_TCB 	* )&guntongTaskTCB,				//13
				 (CPU_CHAR	* )"guntong task", 		
                 (OS_TASK_PTR )guntong_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )guntong_TASK_PRIO,     	
                 (CPU_STK   * )&guntong_TASK_STK[0],	
                 (CPU_STK_SIZE)guntong_STK_SIZE/10,	
                 (CPU_STK_SIZE)guntong_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);		
				 
	//��ѹ�ɼ�		
	OSTaskCreate((OS_TCB 	* )&DCvTaskTCB,					//14
				 (CPU_CHAR	* )"DCv task", 		
                 (OS_TASK_PTR )DCv_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )DCv_TASK_PRIO,     	
                 (CPU_STK   * )&DCv_TASK_STK[0],	
                 (CPU_STK_SIZE)DCv_STK_SIZE/10,	
                 (CPU_STK_SIZE)DCv_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);					 
				 

	//Modbus	
	OSTaskCreate((OS_TCB 	* )&OPENBOXTaskTCB,				//15
				 (CPU_CHAR	* )"openbox task", 		
                 (OS_TASK_PTR )openbox_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )OPENBOX_TASK_PRIO,     	
                 (CPU_STK   * )&OPENBOX_TASK_STK[0],	
                 (CPU_STK_SIZE)OPENBOX_STK_SIZE/10,	
                 (CPU_STK_SIZE)OPENBOX_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);	
	//�����Ϲ켰������					 		 
	OSTaskCreate((OS_TCB 	* )&HEARTBEATTaskTCB,			//16 heartbeat
				 (CPU_CHAR	* )"heartbeat task", 		
                 (OS_TASK_PTR )heartbeat_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )HEARTBEAT_TASK_PRIO,     	
                 (CPU_STK   * )&HEARTBEAT_TASK_STK[0],	
                 (CPU_STK_SIZE)HEARTBEAT_STK_SIZE/10,	
                 (CPU_STK_SIZE)HEARTBEAT_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,					
                 (void   	* )0,				
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
                 (OS_ERR 	* )&err);		
	
	//�����ŵ�����������
	OSTaskCreate((OS_TCB 	* )&Task17_TaskTCB,				//17
				 (CPU_CHAR	* )"Task17 task", 		
				 (OS_TASK_PTR )Task17_task, 			
				 (void		* )0,					
				 (OS_PRIO	  )Task17_TASK_PRIO,     	
				 (CPU_STK   * )&Task17_TASK_STK[0],	
				 (CPU_STK_SIZE)Task17_STK_SIZE/10,	
				 (CPU_STK_SIZE)Task17_STK_SIZE,		
				 (OS_MSG_QTY  )0,					
				 (OS_TICK	  )0,					
				 (void   	* )0,				
				 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
				 (OS_ERR 	* )&err);
				 
	//ǰ�ִŵ����ֲ�
	OSTaskCreate((OS_TCB 	* )&Task18_TaskTCB,				//18
				 (CPU_CHAR	* )"Task18 task", 		
				 (OS_TASK_PTR )Task18_task, 			
				 (void		* )0,					
				 (OS_PRIO	  )Task18_TASK_PRIO,     	
				 (CPU_STK   * )&Task18_TASK_STK[0],	
				 (CPU_STK_SIZE)Task18_STK_SIZE/10,	
				 (CPU_STK_SIZE)Task18_STK_SIZE,		
				 (OS_MSG_QTY  )0,					
				 (OS_TICK	  )0,					
				 (void   	* )0,				
				 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
				 (OS_ERR 	* )&err);
				 
	//���ִŵ����ֲ�
	OSTaskCreate((OS_TCB 	* )&Task19_TaskTCB,				//19
				 (CPU_CHAR	* )"Task19 task", 		
				 (OS_TASK_PTR )Task19_task, 			
				 (void		* )0,					
				 (OS_PRIO	  )Task19_TASK_PRIO,     	
				 (CPU_STK   * )&Task19_TASK_STK[0],	
				 (CPU_STK_SIZE)Task19_STK_SIZE/10,	
				 (CPU_STK_SIZE)Task19_STK_SIZE,		
				 (OS_MSG_QTY  )0,					
				 (OS_TICK	  )0,					
				 (void   	* )0,				
				 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
				 (OS_ERR 	* )&err);
	//��λ��ͨ��
	OSTaskCreate((OS_TCB 	* )&Task20_TaskTCB,				//20
				 (CPU_CHAR	* )"Task20 task", 		
				 (OS_TASK_PTR )Task20_task, 			
				 (void		* )0,					
				 (OS_PRIO	  )Task20_TASK_PRIO,     	
				 (CPU_STK   * )&Task20_TASK_STK[0],	
				 (CPU_STK_SIZE)Task20_STK_SIZE/10,	
				 (CPU_STK_SIZE)Task20_STK_SIZE,		
				 (OS_MSG_QTY  )0,					
				 (OS_TICK	  )0,					
				 (void   	* )0,				
				 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
				 (OS_ERR 	* )&err);				 

	//��λ�����ݷ���
	OSTaskCreate((OS_TCB 	* )&Task21_TaskTCB,				//21
				 (CPU_CHAR	* )"Task21 task", 		
				 (OS_TASK_PTR )Task21_task, 			
				 (void		* )0,					
				 (OS_PRIO	  )Task21_TASK_PRIO,     	
				 (CPU_STK   * )&Task21_TASK_STK[0],	
				 (CPU_STK_SIZE)Task21_STK_SIZE/10,	
				 (CPU_STK_SIZE)Task21_STK_SIZE,		
				 (OS_MSG_QTY  )0,					
				 (OS_TICK	  )0,					
				 (void   	* )0,				
				 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
				 (OS_ERR 	* )&err);

	//AGV�г���
	OSTaskCreate((OS_TCB 	* )&Task22_TaskTCB,				//22
				 (CPU_CHAR	* )"Task22 task", 		
				 (OS_TASK_PTR )Task22_task, 			
				 (void		* )0,					
				 (OS_PRIO	  )Task22_TASK_PRIO,     	
				 (CPU_STK   * )&Task22_TASK_STK[0],	
				 (CPU_STK_SIZE)Task22_STK_SIZE/10,	
				 (CPU_STK_SIZE)Task22_STK_SIZE,		
				 (OS_MSG_QTY  )0,					
				 (OS_TICK	  )0,					
				 (void   	* )0,				
				 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
				 (OS_ERR 	* )&err);		

	//Զ��������Զ��Ӽ���
	OSTaskCreate((OS_TCB 	* )&Task23_TaskTCB,				//23
				 (CPU_CHAR	* )"Task23 task", 		
				 (OS_TASK_PTR )Task23_task, 			
				 (void		* )0,					
				 (OS_PRIO	  )Task23_TASK_PRIO,     	
				 (CPU_STK   * )&Task23_TASK_STK[0],	
				 (CPU_STK_SIZE)Task23_STK_SIZE/10,	
				 (CPU_STK_SIZE)Task23_STK_SIZE,		
				 (OS_MSG_QTY  )0,					
				 (OS_TICK	  )0,					
				 (void   	* )0,				
				 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
				 (OS_ERR 	* )&err);	

	//��ʱ��:�ͻ��Զ��峬ʱ�������ԭ��
	OSTaskCreate((OS_TCB 	* )&Task24_TaskTCB,				//24
				 (CPU_CHAR	* )"Task24 task", 		
				 (OS_TASK_PTR )Task24_task, 			
				 (void		* )0,					
				 (OS_PRIO	  )Task24_TASK_PRIO,     	
				 (CPU_STK   * )&Task24_TASK_STK[0],	
				 (CPU_STK_SIZE)Task24_STK_SIZE/10,	
				 (CPU_STK_SIZE)Task24_STK_SIZE,		
				 (OS_MSG_QTY  )0,					
				 (OS_TICK	  )0,					
				 (void   	* )0,				
				 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
				 (OS_ERR 	* )&err);					 

	//USB
	OSTaskCreate((OS_TCB 	* )&Task25_TaskTCB,				//25
				 (CPU_CHAR	* )"Task25 task", 		
				 (OS_TASK_PTR )Task25_task, 			
				 (void		* )0,					
				 (OS_PRIO	  )Task25_TASK_PRIO,     	
				 (CPU_STK   * )&Task25_TASK_STK[0],	
				 (CPU_STK_SIZE)Task25_STK_SIZE/10,	
				 (CPU_STK_SIZE)Task25_STK_SIZE,		
				 (OS_MSG_QTY  )0,					
				 (OS_TICK	  )0,					
				 (void   	* )0,				
				 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
				 (OS_ERR 	* )&err);	
				 
////////////////////////////////////////////////////////////////////////////////////				 
	OS_TaskSuspend((OS_TCB*)&StartTaskTCB,&err);		//����ʼ����			 
	OS_CRITICAL_EXIT();	//�˳��ٽ���
								 
}




void Transducer_task(void *p_arg)  	//����������ɼ����г���״̬
{
	u8 temp_k=0;
	OS_ERR err;
	p_arg = p_arg;	
	
	while(1)
	{
		//ֻʣ�º�����ϵĳ����״̬��
		agv_24V_input(); 	//�ⲿ24V�����źŲɼ�
		AGV_Stop2Start();	//����ֹͣ�źŵĲɼ�,�����Ƴ���ֹͣ����
		Get_Warning_data();	//��ȡAGVϵͳ�ľ�����Ϣ
		temp_k++;
		if(temp_k > 5)
		{
			temp_k = 0;
			LED2 = !LED2;
		}
		
		
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err); //ÿ10ms�������״̬
	}
}

void float_task(void *p_arg)		//����ͻ�е����
{
	OS_ERR err;
	u8 temp_i=0;
	u8 temp_j=0;

	u8 temp_Tiaojian[] = {0,0,0,0};					//����
	u8 *temp_Jieguo[]  = {&g_Start_flag.Start_IR,&g_Start_flag.Start_jixie,&g_Start_flag.Start_IR,&g_Start_flag.Start_jixie};//���
	
	while(1)
	{	
		#if 1
		if(!g_AGV_Sta.Car_Auto2Manu_mode)				//0:�Զ�ģʽ
		{
			if(!g_AGV_Sta.Car_dir)	//0:ǰ��
			{
				temp_j = 0;
			}
			else					//1:����
			{
				temp_j = 2;
			}	
		}
		else											//1:�ֶ�ģʽ
		{
			//0:ֹͣ1:ǰ�� 2:����  
			if(g_AGV_yaokong.SD_ir==1)			//ǰ��
			{
				temp_j = 0;		
			}
			else if(g_AGV_yaokong.SD_ir==2)		//1:����
			{
				temp_j = 2;
			}		
		}
		
		if(temp_j == 0)
		{
			temp_Tiaojian[0] = g_Senser_InPut.IR_qian_jin;			//����
			temp_Tiaojian[1] = g_Senser_InPut.JiXie_qian;		//����		
		}
		else if(temp_j == 2)
		{
			temp_Tiaojian[2] = g_Senser_InPut.IR_hou_jin;			//����
			temp_Tiaojian[3] = g_Senser_InPut.JiXie_hou;		//����			
		}

		for(temp_i=temp_j;temp_i<temp_j+2;temp_i++)
		{
			if(temp_Tiaojian[temp_i] == 1)				//��������� 1����
			{
//				if(g_Start_flag.Start_Auto_PID || g_AGV_yaokong.SD_Speed)	//ֹͣ״̬���ϲ�����
//				{
					*temp_Jieguo[temp_i] = 0;				//0ֹͣ	
					if(temp_i%2 == 0)
					{
						g_AGV_speaker_flag.IR = 1;
						delay_rtos(0,0,0,20);				
					}
					else
					{
						g_AGV_speaker_flag.JiXie = 1;
						delay_rtos(0,0,0,20);				
					}				
//				}
			}	
			else										//����δ����
			{
				if(temp_Tiaojian[temp_i] == 0)			//��еҲδ����
				{
					if(temp_i%2 == 0)
					{
						g_AGV_speaker_flag.IR = 0;		
						delay_rtos(0,0,0,20);				
					}
					else
					{
						g_AGV_speaker_flag.JiXie = 0;
						delay_rtos(0,0,0,20);				
					}					
					if(*temp_Jieguo[temp_i] == 0)		//�Ǵ�ֹͣ״̬������
					{
						delay_rtos(0,0,2,0);			//�ȴ�2������
						*temp_Jieguo[temp_i] = 1;		//1:����
					}
					else
					{									//ֱ������
						*temp_Jieguo[temp_i] = 1;		//1:����
					}					
				}		
			}					
		}
		#endif 
		
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱms
	}
}



void motec_task(void *p_arg)		//��ʼ��Motec������
{
	//OS_ERR err;
	p_arg = p_arg;
	
	g_motec_init.init_delay_val = 150;		//
	g_AGV_Sta.Car_fencha_dir = 1;			//Ĭ�Ϸֲ淽��
	
	while(1)
	{
		check_Motec_init();
		delay_rtos(0,0,0,20);
	}		
}



void Auto_task(void *p_arg)			//�Զ�ģʽ--ǰ��PID
{
	OS_ERR err;
	u16 stop_num=0;
	p_arg = p_arg;

	while(1)
	{
		if(g_motec_init.Init_OK)
		{
			if(AGV_SYS.Car_Auto_Speed>0 && g_AGV_Sta.Car_Auto2Manu_mode == 0) 
			{
				if(g_Start_flag.Start_Auto_PID)		//1:�ҵ�����
				{
					PID_AUTO_QianLun(AGV_SYS.Car_Auto_Speed,AGV_SYS.AUTO_Kp,AGV_SYS.AUTO_Ki,AGV_SYS.AUTO_Kd);	//ǰ��				
				}
				if(stop_num > 100)
				{
					MotoStop(0);//ֻ����һ��,δ�Ż�
					stop_num = 0;
				}						
			}
		}
		if(!AGV_SYS.PID_time)
		{
			AGV_SYS.PID_time = 10;
		}
		OSTimeDlyHMSM(0,0,0,AGV_SYS.PID_time,OS_OPT_TIME_HMSM_STRICT,&err); 		//�ݶ�10ms		
		
	}		
}
void PID_task(void *p_arg)			//�Զ�ģʽ--����PID
{
	OS_ERR err;
	u16 stop_num=0;
	p_arg = p_arg;
	
	while(1)
	{
		if(g_motec_init.Init_OK)
		{
			if(AGV_SYS.Car_Auto_Speed>0 && g_AGV_Sta.Car_Auto2Manu_mode == 0) 
			{
				if(g_Start_flag.Start_Auto_PID)				//1:�ҵ�����
				{				
					PID_AUTO_HouLun(AGV_SYS.Car_Auto_Speed,AGV_SYS.AUTO_Kp,AGV_SYS.AUTO_Ki,AGV_SYS.AUTO_Kd);		//����
					//g_CtXunZheng.XunZ_OK_AGV = 0;			//��������Ϲ��־				
				}
				else
				{
					if(stop_num > 100)
					{
						MotoStop(0);//ֻ����һ��,δ�Ż�
						stop_num = 0;
					}
					
				}				
			}
		}
		if(!AGV_SYS.PID_time)
		{
			AGV_SYS.PID_time = 10;
		}
		stop_num++;
		OSTimeDlyHMSM(0,0,0,AGV_SYS.PID_time,OS_OPT_TIME_HMSM_STRICT,&err); 		//�ݶ�10ms		
		
	}
}



void Manual_task(void *p_arg)  		//�ֶ�����
{
	p_arg = p_arg;
	
	while(1)
	{
		
		if(g_motec_init.Init_OK)
		{
			//ǰ������ת -- ���ִ�ֱ,ǰ�ָ���ת��
			//��������ת -- ǰ�ִ�ֱ,���ָ���ת��
			
			if(g_AGV_Sta.Car_Auto2Manu_mode) 					//1://�ֶ�ģʽ
			{	
				if(g_AGV_yaokong.SD_Speed > 50 && g_AGV_yaokong.SD_ir!=0) 	
				{
					if(g_Start_flag.Start_Manu_PID)				//1:����
					{
						g_XZ_Ok = 0;
						PID_SD_Adjust(g_AGV_yaokong.SD_Speed,AGV_SYS.SD_Kp,AGV_SYS.SD_Ki,AGV_SYS.SD_Kd);	//��ʱ������
						
					}		
					else										//0:ֹͣ
					{
						MotoStop(0);
						if(!g_XZ_Ok)
						{
							DwqXunZheng_QH();					//��λ��Ѱ��	
						}					
					}
				}		
				else 
				{
					MotoStop(0);								//��������,��һֱ����				
					if(!g_XZ_Ok)
					{
						DwqXunZheng_QH();						//��λ��Ѱ��	
					}	
					if(g_Start_flag.button_bizhang_Start==0)
					{
						g_Start_flag.Start_Manu_PID = 0;		//�����ֶ�PID	
					}
					else
					{
						g_Start_flag.Start_Manu_PID = 1;		//�����ֶ�PID	
					}									
				}					
			}			
		}
		if(!AGV_SYS.PID_time)
		{
			AGV_SYS.PID_time = 10;
		}
		delay_rtos(0,0,0,AGV_SYS.PID_time); 					//10ms,��Ļ������
	}
}


void Screen_task(void *p_arg)    	//�������������  		//�Կ�����ַ:4x32  
{
	u16 i=0;
	u16 j=0;
	u16 temp_user_task=0;

	OS_ERR err;
	p_arg = p_arg;	
	


	while(1)
	{

		#if 1
		
	    switch(HmiScreenSetGet)
        {

			//�����߽�������
			case ShouDongJieMian: 		//--3					//3//�ֶ���������
			{
				while(HmiScreenSetGet == ShouDongJieMian)		
				{
					 if(g_AGV_Sta.Car_Auto2Manu_mode)
					 {
							g_Manu2Auto_flag = 1;
					 }
					 else
					 {
							g_Manu2Auto_flag = 0;	
					 }
					
					 SD2ZD_check_UP();			//���Զ��л�

					 if(g_AGV_Sta.Car_Auto2Manu_mode == 0)				//0:�Զ�ģʽ 1:�Զ�ģʽ
					 {
							*g_dispatch_message.RunState = 0;					//�л����Ǿ���ģʽ
							ZD_check_UP();		//�Զ�ģʽ����
					 }
					 else
					 {		
							*g_dispatch_message.RunState = 0;					//�л����Ǿ���ģʽ
						 	SD_check_UP();		//�ֶ�ģʽ����	 
					 }

					 AGV_SYS.SD_Speed_bili = g_shoudong_screen_speed;	//PLC_Data[3]				//������Ļ���ٶ���ʾֵ

					 SystemParameter[3] = AGV_SYS.SD_Speed_bili;		//�ֶ��ٶȱ���:  x/10
					 g_shoudong_screen_RFID = g_AGV_Sta.juedui_RFID; //���µ�ǰ�ر�
					 g_AGV_Sta.flag_set_yuandian	= 0;
					 
					 if(!g_AGV_Sta.Car_Auto2Manu_mode)
					 {
						g_prtf_autu_speed = AGV_SYS.Car_Auto_Speed;
					 }else
					 {
						g_prtf_autu_speed = g_AGV_yaokong.SD_Speed;
					 }
					 
					osdelay_ms(10);
				}
				SetOneParameterToSystem(SystemParameter[3], 3);
			}
			break;
			//·���滮�ν���	
			case LuJingSheZhiJieMian: 				//9//·�����ý��棨��һ��ѡ��滮·��ʱ�Ľ��棩
			{
				//���·����Ϊ�㣬����һ
				if(HmiRouteNum == 0)
				{
					 HmiRouteNum = 2;
				}
			}
			break;
			case LuJingGuiHuaJieMian:					//4·���滮����
			case FuZhiLuJingTanChuJieMian:				//11����·������
			case QueDingChaRuZhanDianJieMian: 			//12����վ�����
			case QueDingShanChuZhanDianJieMian:			//13ɾ��վ�����
			case XvNiDiBiaoJieMian:  					//14����ر����
			{
				while(HmiScreenSetGet == LuJingGuiHuaJieMian || HmiScreenSetGet == FuZhiLuJingTanChuJieMian ||
						HmiScreenSetGet == QueDingChaRuZhanDianJieMian || HmiScreenSetGet == QueDingShanChuZhanDianJieMian ||
						HmiScreenSetGet == XvNiDiBiaoJieMian)
				{
					 //����·��
					 if(HmiScreenSetGet == FuZhiLuJingTanChuJieMian)
					 {
							//������·���ų�ʼ��Ϊ1
							HmiRouteCopiedNum = 1;
							while(HmiScreenSetGet == FuZhiLuJingTanChuJieMian) //���ڸ���·������
							{
								//������·����Ϊ��ʱ��1
								if(HmiRouteCopiedNum == 0)
									 HmiRouteCopiedNum = 1;
								if(HmiRouteCopiedNum > RouteNum)
								{
									 HmiRouteCopiedNum = 1;
								}

								//����ı�����·���ű仯ʱ����
								if(HmiRouteCopiedNumTemp != HmiRouteCopiedNum)
									 HmiRouteCopiedCount = GetRouteStationNum(HmiRouteCopiedNum);


								//ȷ������
								if(HmiRoutemode == 1)
								{
									 //��ȡ��������Ϣ����ǰ
									 GetRouteData(HmiRouteCopiedNum);

									 //���沢���±�������Ϣ
									 SetRouteData(HmiRouteNum);

									 UpdataStationToHmi();

									 //���õ�ǰվ��Ϊ1
									 if(HmiStationNum != 0)
											HmiStationSerialNum = 1;

									 //�˳�����ģʽ
									 HmiRoutemode = 0;
								}
								osdelay_ms(10);
							}
					 }

					 //���վ��
					 if(HmiRoutemode == 2)	//4x41ȷ��������ģʽ���鿴0������1�����2������3������4��ɾ��5
					 {
							//վ������һ
							HmiStationNum ++;
							//վ��ŵ���վ����
							HmiStationSerialNum = HmiStationNum;

							//�ر������
							g_AGV_RFID_ID = 0;

							ClearStationToHmi();
					 
							while(HmiRoutemode == 2)
							{
								//��������ر꣬���µ���ʾ��
								if(g_AGV_RFID_ID != 0)
								{
									 HmiRfidNum = g_AGV_RFID_ID;//ˢ�µر��
									 g_AGV_RFID_ID = 0;
								}

								//ȷ��
								if(HmiRouteEnter == 1)
								{
									 HmiRouteEnter = 0;
									 //����վ�����ݵ���ǰ����
									 UpdataStationToNow();
									
									 //����·������վ����
									 SetRouteStationNum();
									 //����վ����Ϣ,num:·����,nվ���
									 SetStationData(HmiRouteNum,HmiStationSerialNum);
									
									 //�˳����ģʽ
									 HmiRoutemode =	0;
								}
								else
								 //ȡ��
								 if(HmiRouteEnter == 2)
								 {
										HmiRouteEnter = 0;
										//վ������һ
										HmiStationNum--;
										//վ��ŵ���վ����
										HmiStationSerialNum = HmiStationNum;
										//�˳����ģʽ
										HmiRoutemode =	0;
								 }
								osdelay_ms(10);
							}
					 }
					 //����վ��
					 if(HmiRoutemode == 3)
					 {
							//վ������һ
							HmiStationNum ++;
							//վ���Ϊ��ʱ��һ
							if(HmiStationNum == 0)
								HmiStationSerialNum = 1;

							//�ر������
							g_AGV_RFID_ID = 0;

							ClearStationToHmi();

							while(HmiRoutemode == 3)
							{
								//��������ر꣬���µ���ʾ��
								if(g_AGV_RFID_ID != 0)
								{
									 HmiRfidNum = g_AGV_RFID_ID;//ˢ�µر��
									 g_AGV_RFID_ID = 0;
								}

								//ȷ��
								if(HmiRouteEnter == 1)
								{
									 HmiRouteEnter = 0;

									 //վ����Ϣ����ƶ�һ��λ�ã������뵱ǰվ����Ϣ
									 for(i = HmiStationNum; i >= HmiStationSerialNum; i--)
									 {
											for(j = 0; j < StaiionInfor; j++)
											{
												NowRouteInfor[i][j] = NowRouteInfor[i - 1][j];
											}
									 }

									 //����վ����Ϣ����ǰ
									 UpdataStationToNow();

									 //����·����Ϣ
									 SetRouteData(HmiRouteNum);

									 //�˳����ģʽ
									 HmiRoutemode =	0;
								}
								else
									 //ȡ��
									 if(HmiRouteEnter == 2)
									 {
											HmiRouteEnter = 0;
											//վ������һ
											HmiStationNum--;
											//վ���Ϊ1ʱ����
											if(HmiStationSerialNum == 1)
												HmiStationSerialNum = 0;
											//�˳����ģʽ
											HmiRoutemode =	0;
									 }

								osdelay_ms(10);
							}

					 }
					 //����վ��
					 if(HmiRoutemode == 4)
					 {
							g_AGV_RFID_ID = 0;
							while(HmiRoutemode == 4)
							{
								//��������ر꣬���µ���ʾ��
								if(g_AGV_RFID_ID != 0)
								{
									 HmiRfidNum = g_AGV_RFID_ID;//ˢ�µر��
									 g_AGV_RFID_ID = 0;
								}

								//ȷ��
								if(HmiRouteEnter == 1)
								{
									 HmiRouteEnter = 0;
									 //����վ�����ݵ���ǰ����
									 UpdataStationToNow();
									 //����·������վ����
									 SetRouteStationNum();
									 //����վ����Ϣ,num:·����,nվ���
									 SetStationData(HmiRouteNum,HmiStationSerialNum);
									 //�˳����ģʽ
									 HmiRoutemode =	0;
								}
								else
									 //ȡ��
									 if(HmiRouteEnter == 2)
									 {
											HmiRouteEnter = 0;
											//���µ�����
											UpdataStationToHmi();
											//�˳����ģʽ
											HmiRoutemode =	0;
									 }
								osdelay_ms(10);
							}
					 }

					 //ɾ��վ��
					 if(HmiRoutemode == 5)
					 {
							if(HmiStationNum > 0)
							{
								//��������������ǰ�ƶ�һλ
								if((HmiStationNum > 0) && ((HmiStationNum) != HmiStationSerialNum))
								{
									 //վ����Ϣ��ǰ�ƶ�һ��λ��
									 for(i = HmiStationSerialNum; i < HmiStationNum; i++)
									 {
											for(j = 0; j < StaiionInfor; j++)
											{
												NowRouteInfor[i - 1][j] = NowRouteInfor[i][j];
											}
									 }
								}

								HmiStationNum--;
								if(HmiStationNum == 0)
									 HmiStationSerialNum = 0;
								else if((HmiStationNum + 1) == HmiStationSerialNum)
									 HmiStationSerialNum--;
								//����·����Ϣ
								SetRouteData(HmiRouteNum);

								//���½���
								UpdataStationToHmi();
							}
							HmiRoutemode = 0;
					 }

					 //��ѯվ��
					 if(HmiRoutemode == 0)
					 {
							//��·��վ��������0���������Ϊ0ʱ���������Ϊ1����������ʾ����
							if((HmiStationNum > 0) && (HmiStationSerialNum == 0))
							{
								HmiStationSerialNum = 1;
								//���µ�����
								UpdataStationToHmi();
							}
							else if(HmiStationNum == 0)
							{
								HmiStationSerialNum = 0;
							}

							//·���ű仯ʱ�����½���
							if(HmiRouteNumFlag != HmiRouteNum)
							{
								HmiRouteNumFlag = HmiRouteNum;
								//��ȡ·����Ϣ
								GetRouteData(HmiRouteNum);
								if(HmiStationNum > 0)
									 HmiStationSerialNum = 1;
								//���µ�����
								UpdataStationToHmi();
							}

							//��һ��
							if(HmiStationLast == 1)
							{
								HmiStationLast = 0;
								if(HmiStationSerialNum > 1)
									 HmiStationSerialNum--;
								else
									 HmiStationSerialNum = HmiStationNum;
							}
							//��һ��
							if(HmiStationNext == 2)
							{
								HmiStationNext = 0;
								if(HmiStationSerialNum < HmiStationNum)
									 HmiStationSerialNum++;
								else if(HmiStationSerialNum != 0)
									 HmiStationSerialNum = 1;
							}

							if(HmiStationNum == 0)		//û��վ��
							{
								//���վ����Ϣ
								ClearStationToHmi();
							}
							else
							{
								//����վ����Ϣ
								UpdataStationToHmi();
							}
					 }
					osdelay_ms(10);
				}
			}
			break;
			//���̹滮�ν���
			case LiuChengSheZhiJieMian: 			//10//�������ý��棨��һ��ѡ��滮����ʱ�Ľ��棩
			{
				//������̺�Ϊ�㣬����һ
				if(HmiProcessNum == 0)
				{
					 HmiProcessNum = 1;
				}
			}
			break;
			case LiuChengGuiHuaJieMian:				//���̹滮����
			case FuZhiLiuChengTanChuJieMian:		//�������̽���
			case QueDingChaRuLiuChengJieMian:   	//�������̽���
			case QueDingShanChuLiuChengJieMian: 	//ɾ�����̽���
			{
				while(HmiScreenSetGet == LiuChengGuiHuaJieMian || HmiScreenSetGet == FuZhiLiuChengTanChuJieMian || HmiScreenSetGet == QueDingChaRuLiuChengJieMian || HmiScreenSetGet == QueDingShanChuLiuChengJieMian)
				{
					 //�鿴ģʽ
					 if(HmiProcessMode == 0)
					 {
							//��ǰ���̲�������0�����ҽ������Ϊ0ʱ���������Ϊ1����������ʾ����
							if((HmiStepNum > 0) && (HmiProcessSerialNum == 0))
							{
								HmiProcessSerialNum = 1;
								GetProcessData();
							}
							else if(HmiStepNum == 0)
							{
								HmiProcessSerialNum = 0;
								HmiProcessStartNum = 0;
								HmiProcessStopNum = 0;
								HmiProcessAction = 0;
							}

							//���̺ű仯ʱ�����½���
							if(HmiProcessNumFlag != HmiProcessNum)
							{
								HmiProcessNumFlag = HmiProcessNum;
								GetProcessData();
							}

							if(HmiProcessLast == 1) //��һ��
							{
								HmiProcessLast = 0;
								if(HmiProcessSerialNum > 1)
									 HmiProcessSerialNum--;
								else
									 HmiProcessSerialNum = HmiStepNum;
							}
							else if(HmiProcessNext == 2) //��һ��
							{
								HmiProcessNext = 0;
								if(HmiProcessSerialNum < HmiStepNum)
									 HmiProcessSerialNum++;
								else if(HmiProcessSerialNum != 0)
									 HmiProcessSerialNum = 1;
							}

							if(HmiStepNum == 0)
							{
								ClearStepToHmi();
							}
							else
							{
								UpdataProcessToHmi();
							}
					 }
					 //��������
					 if(HmiScreenSetGet == FuZhiLiuChengTanChuJieMian)
					 {
							//��ʼ����������Ϊ1
							HmiProcessCopiedNum = 1;
							while(HmiScreenSetGet == FuZhiLiuChengTanChuJieMian)
							{
								//���������̺�Ϊ��ʱ��1
								if(HmiProcessCopiedNum == 0)
									 HmiProcessCopiedNum = 1;
								if(HmiProcessCopiedNum > ProcessNum)
									 HmiProcessCopiedNum = 1;

								//����ı��������̺ű仯ʱ����
								if(HmiProcessCopiedNumTemp != HmiProcessCopiedNum)
									 HmiProcessCopiedCount = GetProcessStepNum(HmiProcessCopiedNum);

								//ȷ������
								if(HmiProcessMode == 1)
								{
									 //��ȡ��������Ϣ����ǰ
									 GetProcessDataFrom(HmiProcessCopiedNum);
									 //���汻������Ϣ
									 SetProcessData();

									 //���õ�ǰ���Ϊ1
									 if(HmiStepNum != 0)
											HmiProcessSerialNum = 1;

									 //�˳�����ģʽ
									 HmiProcessMode = 0;
								}
								osdelay_ms(10);
							}
					 }

					 //�������
					 if(HmiProcessMode == 2)
					 {
							//���̲�����һ
							HmiStepNum++;
							//��ŵ���������
							HmiProcessSerialNum = HmiStepNum;

							ClearStepToHmi();

							while(HmiProcessMode == 2)
							{
								switch(HmiProcessAction)
								{
								case 0://����ִ��
									 break;
								case 1://˳��ִ�е�
									 if(HmiProcessStopNum <= HmiProcessStartNum)
									 {
											if(HmiProcessStartNum == ProcessNum)
												HmiProcessStopNum = HmiProcessStartNum;
											else
												HmiProcessStopNum = HmiProcessStartNum + 1;
									 }
									 break;
								case 2://����ִ��
									 if(HmiProcessStopNum >= HmiProcessStartNum)
									 {
											if(HmiProcessStartNum == 1)
												HmiProcessStopNum = HmiProcessStartNum;
											else
												HmiProcessStopNum = HmiProcessStartNum - 1;
									 }
									 break;
								case 3://ѭ��ִ��
									 if(HmiProcessStopNum == 0)
									 {
											HmiProcessStopNum = 1;
									 }
									 break;
								default:
									 break;
								}

								//ȷ��
								if(HmiProcessEnter == 1)
								{
									 HmiProcessEnter = 0;
									 //���沢��������
									 SetProcessData();

									 //�˳����ģʽ
									 HmiProcessMode = 0;
								}
								//ȡ��
								else if(HmiProcessEnter == 2)
								{
									 HmiProcessEnter = 0;

									 //���̲�����һ
									 HmiStepNum--;
									 //��ŵ���������
									 HmiProcessSerialNum = HmiStepNum;

									 //�˳����ģʽ
									 HmiProcessMode = 0;
								}
								osdelay_ms(10);
							}
					 }


					 //��������
					 if(HmiProcessMode == 3)
					 {
							//���̲�����һ
							HmiStepNum++;
							//���Ϊ��ʱ��һ
							if(HmiProcessSerialNum == 0)
								HmiProcessSerialNum = 1;

							ClearStepToHmi();

							while(HmiProcessMode == 3)
							{
								switch(HmiProcessAction)
								{
								case 0://����ִ��
									 break;
								case 1://˳��ִ�е�
									 if(HmiProcessStopNum <= HmiProcessStartNum)
									 {
											if(HmiProcessStartNum == ProcessNum)
												HmiProcessStopNum = HmiProcessStartNum;
											else
												HmiProcessStopNum = HmiProcessStartNum + 1;
									 }
									 break;
								case 2://����ִ��
									 if(HmiProcessStopNum >= HmiProcessStartNum)
									 {
											if(HmiProcessStartNum == 1)
												HmiProcessStopNum = HmiProcessStartNum;
											else
												HmiProcessStopNum = HmiProcessStartNum - 1;
									 }
									 break;
								case 3://ѭ��ִִ��
									 if(HmiProcessStopNum == 0)
									 {
											HmiProcessStopNum = 1;
									 }
									 break;
								default:
									 break;
								}

								//ȷ��
								if(HmiProcessEnter == 1)
								{
									 HmiProcessEnter = 0;

									 //���沢��������
									 InsertProcessData();

									 //�˳�����ģʽ
									 HmiProcessMode = 0;
								}
								//ȡ��
								else if(HmiProcessEnter == 2)
								{
									 HmiProcessEnter = 0;

									 //���̲�����һ
									 HmiStepNum--;
									 //���Ϊ1ʱ��һ
									 if(HmiProcessSerialNum == 1)
											HmiProcessSerialNum = 0;

									 //�˳����ģʽ
									 HmiProcessMode = 0;
								}
								osdelay_ms(10);
							}
					 }

					 //��������
					 if(HmiProcessMode == 4)
					 {
							while(HmiProcessMode == 4)
							{
								switch(HmiProcessAction)
								{
								case 0://����ִ��
									 break;
								case 1://˳��ִ�е�
									 if(HmiProcessStopNum <= HmiProcessStartNum)
									 {
											if(HmiProcessStartNum == ProcessNum)
												HmiProcessStopNum = HmiProcessStartNum;
											else
												HmiProcessStopNum = HmiProcessStartNum + 1;
									 }
									 break;
								case 2://����ִ��
									 if(HmiProcessStopNum >= HmiProcessStartNum)
									 {
											if(HmiProcessStartNum == 1)
												HmiProcessStopNum = HmiProcessStartNum;
											else
												HmiProcessStopNum = HmiProcessStartNum - 1;
									 }
									 break;
								case 3://ѭ��ִ��
									 if(HmiProcessStopNum == 0)
									 {
											HmiProcessStopNum = 1;
									 }
									 break;
								default:
									 break;
								}

								//ȷ��
								if(HmiProcessEnter == 1)
								{
									 HmiProcessEnter = 0;
									 //���沢��������
									 SetProcessData();

									 //�˳�����ģʽ
									 HmiProcessMode = 0;
								}
								//ȡ��
								else if(HmiProcessEnter == 2)
								{
									 HmiProcessEnter = 0;

									 //�˳����ģʽ
									 HmiProcessMode = 0;
								}
								osdelay_ms(10);
							}
					 }

					 //ɾ������
					 if(HmiProcessMode == 5)
					 {
							DeleteProcessData();
							//�˳�ɾ��ģʽ
							HmiProcessMode = 0;
					 }

					 osdelay_ms(10);
				}
			}
			break;
			//ִ������ν���
			case ZhiXingLuJingJieMian: 				//18//ִ��·������
			{
				while(HmiScreenSetGet == ZhiXingLuJingJieMian)
				{
					 if(ZhiXingLuJingQueDing == 1)
					 {
							//����·����
							SetOneParameterToSystem(HmiRouteNum, 24);
							SystemParameter[26] = HmiTask;
							//���������
							SetOneParameterToSystem(HmiTask, 26);
							ZhiXingLuJingQueDing = 0;

							//�����Զ�������Ϣ
							HmiAutoReload();

							HmiTask = 1;

							g_AGV_Sta.Car_dir = AGV_SYS.yuandian_dir; //�����л���ǰ��  

							//��ת���Զ�����
							HmiScreenSetGet = ZiDongJieMian;
					 }
					 osdelay_ms(10);
				}
			}
			break;
			case ZhiXingLiuChengJieMian:  			//ִ�����̽���
			{
				while(HmiScreenSetGet == ZhiXingLiuChengJieMian)
				{
					 if(ZhiXingLiuChengQueDing == 1)
					 {
							ActiveProcess();  
							ZhiXingLiuChengQueDing = 0;
					 }
					 osdelay_ms(10);
				}
			}
			break;
			case ZiDongJieMian: 					//20�Զ����н���
			{
				while(HmiScreenSetGet == ZiDongJieMian)
				{
					 //SD2ZD_check_UP();
					 g_luluzi_ID 	  = AGV_SYS.ToPLC_task%10;
					 g_guan_ID 		  = AGV_SYS.guan_ID;
					 g_quzhoufangzhou = AGV_SYS.ToPLC_task/10; //1:���� 2:ȡ
					 g_prtf_autu_speed = AGV_SYS.Car_Auto_Speed;
					
					 if(g_AGV_Sta.Car_Auto2Manu_mode == 0)				//0:�Զ�ģʽ 1:�ֶ�ģʽ
					 {	
						ZD_check_UP_AUTO();
					 }
					 osdelay_ms(10);		//ʱ��̵Ļ���һ�»���������,���Ļ��ᷴӦ�ٶ�,50ms�պ�
				}
				
			}
			break;
			case QuXiaoRenWuJieMian: 				//ȡ���������
			{
				while(HmiScreenSetGet == QuXiaoRenWuJieMian)
				{
					 if(QuXiaoRenWuQueDing == 1)
					 {
							QuXiaoRenWuQueDing = 0;
							HmiTask = 0;		//0:������ 1:ִ��·�� 2;ִ������
							//����״̬Ϊ����
							HmiTaskState = 0;
							//ͣ��
							Ting_Zhi(); 

							//�л������ʶΪǰ��
							g_AGV_Sta.Car_dir = AGV_SYS.yuandian_dir;

						 							//��������źű�־				
							AGV_SYS.ToPLC_task = 0;							//��PLC��������Ϣ����
							AGV_SYS.guan_ID = 0;
							g_AGV_Sta.flag_set_yuandian	= 0;
							g_AGV_Sta.flag_fist_zhilu = 0;
							g_AGV_Sta.add_time = 0;
							HmiScreenSetGet = 2;				//��ת���ֶ�����									
							
											
							*g_dispatch_message.Task_RunFinish = 0;			//���������ɱ�־												
							*g_dispatch_message.Task_Recived   = 0;			//�յ�����
							*g_dispatch_message.Task_RunStart  = 0;			//��ʼִ������	
							*g_dispatch_message.RunState = 0;				//�л���δ����״̬												

							*g_PLC_message[AGV_SYS.ID-1].StoveID = 0;						//AGV����PLC��Ҫͨ�ŵ�¯��ID 
							*g_PLC_message[AGV_SYS.ID-1].Flag_Position_OK 	 = 0;			//AGV����PLC����ָ��λ��				
							//����PLC��ǰ��λ������Ϣ 1:���� 2:ȡ��
							*g_PLC_message[AGV_SYS.ID-1].TO_PLC_Task_data    = 0;			
							*g_PLC_message[AGV_SYS.ID-1].Flag_RecTray_Ready  = 0;			//AGV����PLC��������׼������
							*g_PLC_message[AGV_SYS.ID-1].Flag_RecTray_Finish = 0;			//AGV����PLC���̽������
							g_RunSta.roller = 0;											//������״̬		
							AGV_SYS.Car_Auto_Speed 	= AGV_SYS.M_speed;						//1:����
							GunTong_L(0);
							//ɾ������
							OSTaskDel((OS_TCB*)&Task5_TaskTCB, &err);
							//���´�������
							OSTaskCreate((OS_TCB 	* )&Task5_TaskTCB,
											(CPU_CHAR	* )"Task5 task",
											(OS_TASK_PTR )Task5_task,
											(void		* )0,
											(OS_PRIO	  )Task5_TASK_PRIO,
											(CPU_STK   * )&Task5_TASK_STK[0],
											(CPU_STK_SIZE)Task5_STK_SIZE / 10,
											(CPU_STK_SIZE)Task5_STK_SIZE,
											(OS_MSG_QTY  )0,
											(OS_TICK	  )0,
											(void   	* )0,
											(OS_OPT      )OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
											(OS_ERR 	* )&err);
											

							//NVIC_SystemReset();		//��λ
											
					 }
					 osdelay_ms(10);
				}
			}
			break;
			//���ݵ��Լ�ϵͳ��������γ���
			case ChuanGanQiJieMian:					//22//���������Ը�����������״̬���µ���Ļ��
			{
				while(HmiScreenSetGet == ChuanGanQiJieMian)
				{
					g_IR_yuan_CAR_qian 	= 	g_Senser_InPut.IR_qian_yuan;	//#define g_IR_yuan_CAR_qian 		PLC_OutPut[25]	//��ǰԶ�������
					g_IR_yuan_CAR_hou	=	g_Senser_InPut.IR_hou_yuan;		//#define g_IR_yuan_CAR_hou		PLC_OutPut[26]	//����Զ�������
                    
					g_IR_jin_CAR_qian	=	g_Senser_InPut.IR_qian_jin;		//#define g_IR_jin_CAR_qian		PLC_OutPut[29] //��ǰ������
					g_IR_jin_CAR_hou	=	g_Senser_InPut.IR_hou_jin;		//#define g_IR_jin_CAR_hou		PLC_OutPut[30] //���������
                    
					g_jiexie_qian		=	g_Senser_InPut.JiXie_qian;		//#define g_jiexie_qian			PLC_OutPut[46]	//ǰ��е����
					g_jiexie_hou		=	g_Senser_InPut.JiXie_hou;		//#define g_jiexie_hou			PLC_OutPut[47]	//���е����
                    
					g_IR_guntong_left	=	g_Senser_InPut.gunt_IR_L;			//#define g_IR_guntong_left		PLC_OutPut[27]	//��Ͳ�����
					g_IR_guntong_right	=	g_Senser_InPut.gunt_IR_R;			//#define g_IR_guntong_right		PLC_OutPut[28]  //��Ͳ�Һ���
					
					g_jixieKEY_start	=	g_Senser_InPut.button_Start;	//g_button_start;
					g_jixieKEy_stop		=	g_Senser_InPut.button_Stop;		//g_button_stop;
					
					osdelay_ms(10);
				}
			}
			break;
			case JiBenShuJuJieMian:					//23//�������ݲ��Խ���
			{
				while(HmiScreenSetGet == JiBenShuJuJieMian)
				{
					
					
					 g_screen_qianCDH1 = g_CT_bit[1];
					 g_screen_qianCDH2 = g_u16_val[2];
					 g_screen_houCDH1  = g_CT_bit[3];
					 g_screen_houCDH2  = g_u16_val[4];
					
					 g_screen_qianlun_jiaodu   	= g_After_filter[1];
					 g_screen_houlun_jiaodu 	= g_After_filter[2];
					
					 AGV_SYS.AUTO_Kp = g_screen_Auto_Kp;		           //�����Զ�Kp
					 AGV_SYS.AUTO_Ki = g_screen_Auto_Ki;                 //�����Զ�ki
					 AGV_SYS.AUTO_Kd = g_screen_Auto_Kd;                 //�����Զ�kd

					 AGV_SYS.SD_Kp = g_screen_Manu_Kp;	          	  //�����ֶ�kp
					 AGV_SYS.SD_Ki = g_screen_Manu_Ki;               	  //�����ֶ�ki
					 AGV_SYS.SD_Kd = g_screen_Manu_Kd;              	  //�����ֶ�kd

					 AGV_SYS.PID_time  = g_screen_control_TIME;						//����ǰ����PID��������
					
					 AGV_SYS.add_time_yuzhi = g_add_time;
					
					 g_DWQ.qianlun_L_val 	 = g_screen_qianlun_ZuoZhi;					//ǰ������
					 g_DWQ.qianlun_zhong_val = g_screen_qianlun_ZhongZhi;					//ǰ����ֵ
					 g_DWQ.qianlun_R_val 	 = g_screen_qianlun_YouZhi;					//ǰ���Ҽ���
					
					 g_DWQ.houlun_L_val 	 = g_screen_houlun_ZuoZhi;					//��������
					 g_DWQ.houlun_zhong_val  = g_screen_houlun_ZhongZhi;					//������ֵ
					 g_DWQ.houlun_R_val 	 = g_screen_houlun_YouZhi;					//�����Ҽ���					
				
					 AGV_SYS.add_time_yuzhi  = g_add_time;		//��ʱ��
					 AGV_SYS.yuandian_ID 	 = g_yuandi_ID;         //ԭ��ID
					 AGV_SYS.chongdian_ID    = g_chongdian_ID;    //���ID
					 AGV_SYS.zhongzhuan_ID   = g_zhongzhuan_ID; 	//��ת̨ID





					 SystemParameter[50] = g_screen_Auto_Kp;
					 SystemParameter[51] = g_screen_Auto_Ki;
					 SystemParameter[52]= g_screen_Auto_Kd;
					 
					 SystemParameter[53] = g_screen_Manu_Kp;
					 SystemParameter[54] = g_screen_Manu_Ki;
					 SystemParameter[55] = g_screen_Manu_Kd;	
					 
					 SystemParameter[56]= g_screen_control_TIME;
					 					 
					 
					 SystemParameter[57]= g_screen_qianlun_ZuoZhi;
					 SystemParameter[58]= g_screen_qianlun_ZhongZhi;
					 SystemParameter[59]= g_screen_qianlun_YouZhi;
					 
					 SystemParameter[60] = g_screen_houlun_ZuoZhi;
					 SystemParameter[61] = g_screen_houlun_ZhongZhi; 	
					 SystemParameter[62] = g_screen_houlun_YouZhi; 
					 SystemParameter[63] = g_add_time;
					 SystemParameter[64] = g_yuandi_ID;
					 SystemParameter[65] = g_chongdian_ID;
					 SystemParameter[66] = g_zhongzhuan_ID; //��ת̨����
					 
					 osdelay_ms(20);
				}

				W25QXX_Write_16(SystemParameter+50, 50, 17);			//����ǰ��Ļ����д�뵽flash��
			}
			break;
			case ChaBiShuJuJieMian:					//24//Ԥ�����ݵ���
			{
				while(HmiScreenSetGet == ChaBiShuJuJieMian)
				{
					//#define XZ_Speed40       	 PLC_Data[46] 		//Ѱ������ٶ�
					//#define XZ_Speed41        	 PLC_Data[48] 		//��λ��Ѱ���ٶȱ�
					//#define XZ_Speed42       	 PLC_Data[49] 		//����Ѱ���ٶ�
					//#define XZ_Speed43       	 PLC_Data[50] 		//�������ٶ�


					
					AGV_SYS.XZ_MAX_Speed 		= SystemParameter[40] 		= 	XZ_Speed40;
					AGV_SYS.XZ_DWQ_Speed_bili 	= SystemParameter[41] 		= 	XZ_Speed41;
					AGV_SYS.XZ_CiTiao_Speed 	= SystemParameter[42] 		= 	XZ_Speed42;
					AGV_SYS.Motor_MAX_Speed 	= SystemParameter[43] 		= 	XZ_Speed43;
					

					osdelay_ms(20); 
				}
				W25QXX_Write_16(SystemParameter+40, 40, 4);			//����ǰ��Ļ����д�뵽flash��
			}
			break;
			case LeiDaShuJuJieMian:					//25//���ԭʼ���� 
			{
				while(HmiScreenSetGet == LeiDaShuJuJieMian)
				{
					Li_dianya 				=	g_battery.dianya*10;		
					Li_Realy_mah	        =	g_battery.Realy_mah*10;	
					Li_Std_mah 		        =	g_battery.Std_mah*10;		
					Li_XunHuan_time	        =	g_battery.XunHuan_time;
//		
					if(Li_Warning_val_NoBattery < 100)	//�͵�������ֵ
					{
						Battery_Warining.Warining_Val_NoBattery = Li_Warning_val_NoBattery;//PLC_Data[128]
						
						SystemParameter[70] = Battery_Warining.Warining_Val_NoBattery;					
					}
					else
					{
						Battery_Warining.Warining_Val_NoBattery = 99;//PLC_Data[128]
						
						SystemParameter[70] = Battery_Warining.Warining_Val_NoBattery;						
					}

					 osdelay_ms(20);
				}
				SetOneParameterToSystem(SystemParameter[70], 70);
			}
			break;
			case DianTiTiaoShiJieMian:				//26//��Ͳ���Խ���
			{
				while(HmiScreenSetGet == DianTiTiaoShiJieMian)
				{
					
					
					AGV_SYS.GunT_daozhong_time = GunT_zhong_time;
					
					if(GunT_shanghuo_L == 1) 	//����ϻ�
					{
						 g_AGV_speaker_flag.UP_L = 1;
						osdelay_ms(50);
						 GunTong_Trun_L_UP();
					}
					else if(GunT_shanghuo_R == 1) //�Ҳ��ϻ�
					{
						 g_AGV_speaker_flag.UP_R = 1;
						osdelay_ms(50);
						 GunTong_Trun_R_UP();
					}
					SystemParameter[75] = AGV_SYS.GunT_daozhong_time;
					
					osdelay_ms(50);
				}
				SetOneParameterToSystem(SystemParameter[75], 75);
			}
			break;
			case XiTongCanShuJieMian:				//8//ϵͳ�������棬�ٶȵĵ�λ���á�
			{
				while(HmiScreenSetGet == XiTongCanShuJieMian)
				{
					//30��ʼ				
					AGV_SYS.ID 				 = 		g_AGV_ID; 				//����	  
					AGV_SYS.yinliang		 = 		g_AGV_speaker_val;     	//ϵͳ����      
					AGV_SYS.Auto_Speed_bili	 = 		g_sys_set_agvSPEED;    	//AGV���� -- ���и� 
					AGV_SYS.Key_yuyin 		 = 		g_AGV_speaker_key ;	  	//ϵͳ��������     
					AGV_SYS.Key_RGB_LED 	 = 		g_AGV_LED_car_state ;  	//����״̬��    
					AGV_SYS.L_speed 		 = 		HmiDiSu ;      			//����    
					AGV_SYS.M_speed 		 = 		HmiZhongSu;     		//����    
					AGV_SYS.H_speed 		 = 		HmiGaoSu  ;    			//����
					AGV_SYS.duijie_speed 	 =		g_AGV_speed_duijie;		//��λ�Խ��ٶ�
					AGV_SYS.Key_IR_jin		 =		g_AGV_Enable_IR_jin; 	
					AGV_SYS.Key_IR_yuan      =      g_AGV_Enable_IR_yuan; 	
					AGV_SYS.Key_JiXie_qian   =      g_AGV_Enable_JiXie_qian;
                    AGV_SYS.Key_JiXie_hou    =      g_AGV_Enable_JiXie_hou; 
                    AGV_SYS.yuandian_dir     =      g_AGV_yuandian_dir; 
					
					
					SystemParameter[30]		 = 		g_AGV_ID; 				//����	  
					SystemParameter[31] 	 = 		g_AGV_speaker_val;     	//ϵͳ����      
					SystemParameter[32] 	 = 		g_sys_set_agvSPEED;    	//AGV���� -- ���и� 
					SystemParameter[33]	 	 = 		g_AGV_speaker_key ;	  	//ϵͳ��������     
					SystemParameter[34] 	 = 		g_AGV_LED_car_state ;  	//����״̬��    
					SystemParameter[35] 	 = 		HmiDiSu ;      			//����    
					SystemParameter[36] 	 = 		HmiZhongSu;     		//����    
					SystemParameter[37] 	 = 		HmiGaoSu  ;    			//����
					SystemParameter[38] 	 = 		g_AGV_speed_duijie;		//��λ�Խ��ٶ�
					
					SystemParameter[80]      =		g_AGV_Enable_IR_jin; 	
					SystemParameter[81]      =      g_AGV_Enable_IR_yuan; 	
					SystemParameter[82]      =      g_AGV_Enable_JiXie_qian;
                    SystemParameter[83]      =      g_AGV_Enable_JiXie_hou; 	
					SystemParameter[84]      =      g_AGV_yuandian_dir; 					
					
					switch(AGV_SYS.Auto_Speed_bili)
					{
						case 0:
								AGV_SYS.Car_Auto_Speed 	= AGV_SYS.L_speed;
							break;
						case 1:
								AGV_SYS.Car_Auto_Speed 	= AGV_SYS.M_speed;
							break;	
						case 2:
								AGV_SYS.Car_Auto_Speed 	= AGV_SYS.H_speed;
							break;	
						default :
							break;	
					}	

					g_Senser_Enable.IR_qian_jin  = g_Senser_Enable.IR_hou_jin  = AGV_SYS.Key_IR_jin; 
					g_Senser_Enable.IR_qian_yuan = g_Senser_Enable.IR_hou_yuan = AGV_SYS.Key_IR_yuan; 
					g_Senser_Enable.jixie_qian   = AGV_SYS.Key_JiXie_qian;
                    g_Senser_Enable.jixie_hou    = AGV_SYS.Key_JiXie_hou;

					
					osdelay_ms(20);
				}

				W25QXX_Write_16(SystemParameter+30, 30, 9);	//����ǰ��Ļ����д�뵽flash��
				W25QXX_Write_16(SystemParameter+80, 80, 5);	//����ǰ��Ļ����д�뵽flash��
				Dbus.Init(AGV_SYS.ID);						//���޸ĵ�ϵͳID���͸���վ������
				yinling(AGV_SYS.yinliang);
			}
			break; 
			//�û���������
			case YongHuShouYeJieMian:				//27//�û���ҳ
			{
				temp_user_task = 0;
				user_task_luzi = 0;
				while(HmiScreenSetGet == YongHuShouYeJieMian)
				{
					g_shoudong_screen_RFID = g_AGV_Sta.juedui_RFID;
					if(g_AGV_Sta.flag_set_yuandian && g_AGV_Sta.juedui_RFID)
					{
						temp_user_task = user_task_luzi;
						if(temp_user_task)
						{
							g_AGV_speaker_flag.user_luzi = 1;
							if(temp_user_task/10 == 1)
							{
								sprintf(g_user_luzi,"%d��¯�ӷ���",temp_user_task%10);		
							}
							else if(temp_user_task/10 == 2)
							{
								sprintf(g_user_luzi,"%d��¯��ȡ��",temp_user_task%10);		
							}	
							delay_rtos(0,0,1,0);
							//ִ���û�ȡ���۲���
							AGV_SYS.ToPLC_task = temp_user_task;
							Get_PC_data(0,&AGV_SYS.ToPLC_task);
							user_task_luzi = 0;
							temp_user_task = 0;
						}						
					}						
					osdelay_ms(50);
				}
			}
			break;
			
			default:
			break;
        }		

		#endif

			
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err);
	}	
}

void Task5_task(void *p_arg)		//ִ��·����ִ������ -- Ӧ�ò��������
{									
	u16 i=0;						
	u16 j=0; 						
	u16 k=0;						
	
	OS_ERR err;						
	p_arg = p_arg;

	while(1)
    {
        if(g_AGV_Sta.Car_Auto2Manu_mode == 0 ) //�Զ�ģʽ��������
        {
            //ִ��·��
            if(HmiTask == 1)							//������ 0:������ 1:ִ��·�� 2:ִ������
            {
				*g_dispatch_message.Task_RunStart = 1;	//��ʼִ������
				
                HmiRfidNum = 0; 						//�����ǰ�ر�
                HmiStationSerialNum = 0;				//վ�������0
				
                //������ѡ·����ִ����Ӧ����
				if(!AGV_run_path(g_AGV_Sta.type_path,AGV_SYS.ToPLC_task))
				{
					g_AGV_speaker_flag.path = 1;
					delay_rtos(0,0,0,100);
				}
				
				
				//ִ����һ����������������			
				g_AGV_Sta.add_time = 0;

				

				
				
                HmiTask = 0;
				if(HmiTask == 0)
				{
					Ting_Zhi();
				}
				g_AGV_speaker_flag.LuJing_ok = 1;
				AGV_SYS.ToPLC_task = 0;
				AGV_SYS.guan_ID = 0;
				g_AGV_Sta.flag_fist_zhilu = 0;
				g_AGV_Sta.add_time = 0;
				*g_dispatch_message.Task_RunFinish = 1;			//����ִ�����
				HmiScreenSetGet = YongHuShouYeJieMian;			//��ת���û�����
				delay_rtos(0,0,1,0);
				
				
				
				if(g_RunSta.mode_chongdian == 3)				//���ȥ
				{
					*g_dispatch_message.RunState = 3;			//�л������ģʽ			
				}
				else if(*g_dispatch_message.RunState == 1)		//����ģʽ
				{
					*g_dispatch_message.RunState = 2;			//�л�������ģʽ
					g_AGV_speaker_flag.AGV_readyed = 1;
					delay_rtos(0,0,0,20);
				}

				
				*g_dispatch_message.Task_Recived   = 0;			//�յ�����
				
				*g_dispatch_message.Task_RunStart  = 0;			//��ʼִ������
				
				if(g_AGV_Sta.flag_addTIME_OK == 3) //����������ĳ�ʱ��ԭ��
				{
					g_AGV_Sta.flag_addTIME_OK= 0;
					g_AGV_Sta.add_time = 0;		
				}
				
            }
			//ִ������
			else if(HmiTask == 2)
			{
				HmiRfidNum = 0;						//�����ǰ�ر�
				HmiProcessSerialNum = 0;			//���������0
				
				for(i = 0; i < HmiStepNum; i++)
				{
					HmiProcessSerialNum++;			//��������Լ�
					switch(NowProcessInfor[i][1])
					{
						case 0://����ִ��
							//����·����
							HmiRouteNum = NowProcessInfor[i][0];
							//��ȡ·������վ����
							GetRouteStationNum(HmiRouteNum);
							//��ȡ��ǰ·����Ϣ
							GetRouteData(HmiRouteNum);

							HmiStationSerialNum = 0;
							//������ѡ·����ִ����Ӧ����
							for(j = 0; j < HmiStationNum; j++)
							{
								StationAction(j);
							}
							break;
						case 1://˳��ִ��
							for(k = NowProcessInfor[i][0]; k <= NowProcessInfor[i][2]; k++)
							{
								//����·����
								HmiRouteNum = k;
								//��ȡ·������վ����
								GetRouteStationNum(HmiRouteNum);
								//��ȡ��ǰ·����Ϣ
								GetRouteData(HmiRouteNum);

								HmiStationSerialNum = 0;
								//������ѡ·����ִ����Ӧ����
								for(j = 0; j < HmiStationNum; j++)
								{
									StationAction(j);
								}
							}
							break;
						case 2://����ִ��
							for(k = NowProcessInfor[i][0]; k >= NowProcessInfor[i][2]; k--)
							{
								//����·����
								HmiRouteNum = k;
								//��ȡ·������վ����
								GetRouteStationNum(HmiRouteNum);
								//��ȡ��ǰ·����Ϣ
								GetRouteData(HmiRouteNum);

								HmiStationSerialNum = 0;
								//������ѡ·����ִ����Ӧ����
								for(j = 0; j < HmiStationNum; j++)
								{
									StationAction(j);
								}
							}
							break;
						case 3://ѭ��ִ��
							//����·����
							HmiRouteNum = NowProcessInfor[i][0];
							//��ȡ·������վ����
							GetRouteStationNum(HmiRouteNum);
							//��ȡ��ǰ·����Ϣ
							GetRouteData(HmiRouteNum);
							for(k = 0; k < NowProcessInfor[i][2]; k++)
							{
								HmiStationSerialNum = 0;
								//������ѡ·����ִ����Ӧ����
								for(j = 0; j < HmiStationNum; j++)
								{
									StationAction(j);
								}
							}
							break;
						default:
							break;
					}
				}
				HmiTask = 0;
				if(HmiTask == 0)
				{
					Ting_Zhi();
				}
				
				g_AGV_speaker_flag.LiuCheng_ok = 1;
				delay_rtos(0,0,0,10);
			}
            
	
        }
        OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱnms
    }	
	
}



void WIFI_task(void *p_arg)			//����
{
	
	//u8 temp_i=0;
	
	OS_ERR err;
	p_arg = p_arg;
	
	do
	{
		delay_rtos(0,0,1,0); 
		BEEP = !BEEP; 
	}while(!g_AGV_Sta.Flash_get_OK);
	
	yinling(AGV_SYS.yinliang);
	PrintCom(YIN_SU5,9);osdelay_ms(10);		//����5
	PrintCom(YIN_DIAO5,9);osdelay_ms(10);	//���5		
	BEEP = 0;
	
	while(1)
	{
		speak_once("·������",1000,&g_AGV_speaker_flag.path);
		speak_once("��Ͳ��ת",1000,&g_AGV_speaker_flag.GunT_R);
		speak_once("��Ͳ[=tong3]��[=zuo2]ת",1000,&g_AGV_speaker_flag.GunT_L);

		
		speak_once("ǰ������",1000,&g_AGV_speaker_flag.dir_Go);
		speak_once("���˷���",1000,&g_AGV_speaker_flag.dir_Back);
		speak_once("��ֲ�",800,&g_AGV_speaker_flag.FenCha_L);
		speak_once("�ҷֲ�",800,&g_AGV_speaker_flag.FenCha_R);
		
		speak_once("����ִ�����",1500,&g_AGV_speaker_flag.LiuCheng_ok);
		speak_once("·��ִ�����",1500,&g_AGV_speaker_flag.LuJing_ok);
		
		speak_once("����ʹ��",1000,&g_AGV_speaker_flag.Motec_enable);
		speak_once("�����ϵ�",1000,&g_AGV_speaker_flag.Motec_off);
		speak_once("����δ[=wei4]�ϵ�",1000,&g_AGV_speaker_flag.Motec_NoPowerUp);
		
		
		speak_once("���ж��",1000,&g_AGV_speaker_flag.Down_L);
		speak_once("���װ��",1000,&g_AGV_speaker_flag.UP_L);
		speak_once("�Ҳ�ж��",1000,&g_AGV_speaker_flag.Down_R);
		speak_once("�Ҳ�װ��",1000,&g_AGV_speaker_flag.UP_R);	

		speak_once("��е����",1000,&g_AGV_speaker_flag.JiXie);
		speak_once("�������",1000,&g_AGV_speaker_flag.IR);	
		
		speak_once("ǰһ",500,&g_AGV_speaker_flag.DOWN_gui_qian1);
		speak_once("ǰ��δ�Ϲ�",500,&g_AGV_speaker_flag.DOWN_gui_qian2);
		speak_once("��һ",500,&g_AGV_speaker_flag.DOWN_gui_hou1);
		speak_once("���",500,&g_AGV_speaker_flag.DOWN_gui_hou2);	

		speak_once("�ر��ȡ����",1000,&g_AGV_speaker_flag.RFID_READ_err);
		
		//�û�����Ĳ�������
		speak_once(g_user_luzi,1000,&g_AGV_speaker_flag.user_luzi);				//�û�¯�Ӳ���

		speak_once("׼��ȥ���",1500,&g_AGV_speaker_flag.chongdian_goto);			//ȥ���
		speak_once("�����ϻ�ԭ��",1800,&g_AGV_speaker_flag.chongdian_over);	//������
		speak_once("��[=ei1]��ι[=wei1]����",1500,&g_AGV_speaker_flag.AGV_readyed);				//AGV����
		
		
		speak_once("����",500,&g_AGV_speaker_flag.start);
		speak_once("����",500,&g_AGV_speaker_flag.Ruan_Qi);
		speak_once("��Ͳֹͣ",1000,&g_AGV_speaker_flag.GunT_stop);		
		speak_once("ֹͣ",500,&g_AGV_speaker_flag.stop);	

		speak_once("�Զ�",500,&g_AGV_speaker_flag.Auto);
		speak_once("�ֶ�",500,&g_AGV_speaker_flag.Manu);		

		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err);
	}
}

void guntong_task(void *p_arg)		//�ֶ����ƹ�Ͳ
{
	OS_ERR err;
	p_arg = p_arg;

	while(1)
	{
		SD_GunTong();

		OSTimeDlyHMSM(0,0,0,20,OS_OPT_TIME_HMSM_STRICT,&err);
	}
}


void DCv_task(void *p_arg)			//��ѹ�ɼ�
{
	u16 temp_i=0;
	u16 temp_j=0;
	u16 temp_k=0;
	u16 temp_p=0;
	u16 temp_m=0;
	
	OS_ERR err;
	p_arg = p_arg;
	
	GET_Battery();	//��ȡ�����Ϣ
	
	while(1)
	{		
		temp_k++;

		if(temp_k > 500)							//ÿ1s��ȡ�����Ϣ
		{
			GET_Battery();					

			temp_k = 0;				
		}			
		//�͵�������
		if(Sys_battery <= Battery_Warining.Warining_Val_NoBattery)		
		{
			g_Warning.Low_battery = 1;
			sprintf(g_warning,"�������ڰٷ�֮%d,�뼰ʱ���",Battery_Warining.Warining_Val_NoBattery);		
			
			temp_p++;
			if(temp_p > 500)				//ÿ5s��������һ��
			{
				if(!AGV_SYS.Key_yuyin)
				{
					speek(g_warning);
				}
				temp_p = 0;
			}
		}
		else
		{
			g_Warning.Low_battery = 0;	
		}

		//�����ر��������							//��250ms
		if(g_flag_RFID_beep)
		{
			BEEP = 1;
			temp_j++;
			if(temp_j == 25)
			{
				BEEP = 0;
				g_flag_RFID_beep = 0;	
				temp_j = 0;				
			}

		}


		//������ͨ��ָʾ�ƺͰ�������ָʾ��LED1		//500ms��˸
		temp_i++;
		if(temp_i == 50)
		{
			LED1 = 0;
			P_RUN_LED = 1;							//��Ļ����ָʾ��
		}
		if(temp_i == 100)
		{
			LED1 = 1;
			P_RUN_LED = 0;
			temp_i = 0;
		}
		
		
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err);	
	}
}


void openbox_task(void *p_arg)		//Dbus��վͨѶ
{
	u8 temp_i=0;
	p_arg = p_arg;
	
	delay_rtos(0,0,2,0);			//�ȴ�ͨ��ģ���ʼ��
	//Heart(1);
	while(1)	
	{
		temp_i++;
        //�յ���������������� 
        Dbus.OpenBox();
		if(temp_i > 100)		//1������
		{
			Dbus.Heart(0);
			temp_i = 0;
		}
		delay_ms(10);
	}
}

void heartbeat_task(void *p_arg)	//����Ѱ������
{
	p_arg = p_arg;

	while(1)
	{
		if(g_CtXunZheng.XunZ_Start)	//��������Ѱ��
		{
			check_CtXunZ_OK(AGV_SYS.XZ_CiTiao_Speed);		//g_Start_flag.Start_Auto_PID��������һ;						
			g_CtXunZheng.XunZ_Start = 0;					//Ѱ������
		}

		delay_rtos(0,0,0,20);			
	}
}

void Task17_task(void *p_arg)		//�ŵ�������
{
	p_arg = p_arg;
	
	while(1)
	{
		if(!g_AGV_Sta.Car_Auto2Manu_mode) //�Զ�ģʽ�²ż��ͻ��
		{
			CDH_ADD(g_LastCDH_buff,g_u16_val,g_CDH_add_num);		
		}
		delay_rtos(0,0,0,5);
	}
}

void Task18_task(void *p_arg)		//ǰ�����ŵ����ֲ�
{
	u8 temp_j_L=0;
	u8 temp_j_R=0;
	p_arg = p_arg;
	
	while(1)
	{
		if(g_AGV_Sta.Car_fencha_Start_qian )
		{
			if(!g_AGV_Sta.Car_dir)	//ǰ������
			{
				temp_j_L = 11;
				temp_j_R = 12;
			}
			else	//���˷���
			{
				temp_j_L = 12;
				temp_j_R = 11;				
			}	
			
			if(NowRouteInfor[g_AGV_Sta.fencha_RFID_qian][16] && g_CDH_add_num[1] == NowRouteInfor[g_AGV_Sta.fencha_RFID_qian][17])	//1����
			{
				switch(NowRouteInfor[g_AGV_Sta.fencha_RFID_qian][2])//�ֲ��ж�
				{
					case 0:
						break;//�����ϴ���Ϣ
					case 1://��ֲ�
					{
						g_AGV_Sta.Car_fencha_dir = temp_j_L;
					}
					break;
					case 2://�ҷֲ�
					{
						g_AGV_Sta.Car_fencha_dir = temp_j_R;
					}
					break;
					case 3://ֱ��
					{
						//ZhiXing();
					}
					break;
				}					

				g_AGV_RFID_ID = NowRouteInfor[g_AGV_Sta.fencha_RFID_qian][5];					
				g_AGV_Sta.Car_fencha_Start_qian = 0;
			}	
		}
									
		delay_rtos(0,0,0,20);
	}
}
void Task19_task(void *p_arg)		//�������ŵ����ֲ�
{
	u8 temp_j_L=0;
	u8 temp_j_R=0;
	p_arg = p_arg;
	
	while(1)
	{
		if(g_AGV_Sta.Car_fencha_Start_hou)
		{
			if(!g_AGV_Sta.Car_dir)	//ǰ������
			{
				temp_j_L = 21;
				temp_j_R = 22;
			}
			else	//���˷���
			{
				temp_j_L = 22;
				temp_j_R = 21;				
			}		
			
			if(NowRouteInfor[g_AGV_Sta.fencha_RFID_hou][16] && g_CDH_add_num[3] == NowRouteInfor[g_AGV_Sta.fencha_RFID_hou][17])	//1����
			{
				switch(NowRouteInfor[g_AGV_Sta.fencha_RFID_hou][2])//�ֲ��ж�
				{
					case 0:
						break;//�����ϴ���Ϣ
					case 1://��ֲ�
					{
						g_AGV_Sta.Car_fencha_dir = temp_j_L;
					}
					break;
					case 2://�ҷֲ�
					{
						g_AGV_Sta.Car_fencha_dir = temp_j_R;
					}
					break;
					case 3://ֱ��
					{
						//ZhiXing();
					}
					break;
				}									
				g_AGV_Sta.Car_fencha_Start_hou = 0;							
			
			}							
		
		}		
		delay_rtos(0,0,0,20);
	}
}

void Task20_task(void *p_arg)		//��λ��ͨ��
{
	u16 temp_val=0;
	
	g_user_readyed = 0;				//Ĭ�Ͼ���״̬0:δ���� 1:����,�ֶ�����ȥ�����л����Ǿ���״̬
	p_arg = p_arg;
	
	
	while(1)
	{
		if(!User2Auto_mode)						//0:MES����ģʽ
		{
			if(*g_dispatch_message.RunState == 0)			//δ����ģʽ:0
			{
				if(g_AGV_Sta.flag_set_yuandian)
				{
					g_AGV_Sta.flag_set_yuandian = 0;
				}
				
				//����û���쳣����Ļ�ֶ�ȷ�ϵ�ԭ��ſ����е�����״̬
				if(g_user_readyed)
				{
					if(!User2Auto_mode)						//0:�û��Զ�ģʽ
					{
						//�������ر�����־
						g_Warning.chugui   = 0;	
						g_Warning.RFID_err = 0;
						g_AGV_Sta.juedui_RFID = AGV_SYS.yuandian_ID;
						g_AGV_Sta.RFID_buff[0] = 0;
						g_AGV_Sta.RFID_buff[1] = 0;
					
						if(g_Warning.Low_battery)
						{
							temp_val = *g_dispatch_message.Warning & (~(1<<4));	//��0�͵���λ					
						}
						else
						{
							temp_val = *g_dispatch_message.Warning;	
						}
						
						if(!temp_val)	//������0����
						{
							//�����������
							g_AGV_Sta.flag_set_yuandian	= 1;
							*g_dispatch_message.RunState = 2;	
							g_AGV_speaker_flag.AGV_readyed = 1;
							delay_rtos(0,0,0,20);
	
						}					
					
					}	
				}


				
			}
			else if(*g_dispatch_message.RunState == 1)			//����ģʽ:1
			{
				//δ�Ϲ�,������
				//����ģʽ��,���켰�ر��ȡ����,�������л���δ����
				if(g_Warning.chugui || g_Warning.RFID_err)
				{
					Ting_Zhi();	
					*g_dispatch_message.RunState = 0;			//�л���δ����״̬
				
				}	
			}		
			else if(*g_dispatch_message.RunState == 2)		//����ģʽ:2
			{
				if(g_Warning.Low_battery)
				{		
					//δ����0,����1������2�����3
					*g_dispatch_message.Task_RunFinish = 0;				//���������ɱ�־
					*g_dispatch_message.RunState = 3;	
	
					Get_PC_data(1,&AGV_SYS.chongdian_ID); 				//
				}
				else if(*g_dispatch_message.Task_ID && *g_dispatch_message.guan_ID)		//���յ���λ������
				{		
					*g_dispatch_message.Task_RunFinish = 0;				//���������ɱ�־
					
					AGV_SYS.ToPLC_task = *g_dispatch_message.Task_ID;	//��������
					AGV_SYS.guan_ID  = *g_dispatch_message.guan_ID;	//����¯�ܺ�									

					*g_dispatch_message.Task_Recived   = 1;				//�յ�����
					*g_dispatch_message.RunState = 1;		
					g_AGV_Sta.flag_addTIME_OK = 3;					
					Get_PC_data(0,&AGV_SYS.ToPLC_task); 			//������λ��·����Ϣ��ִ��
				}				
				else if(g_AGV_Sta.flag_addTIME_OK == 1)
				{
					*g_dispatch_message.Task_RunFinish = 0;				//���������ɱ�־
					*g_dispatch_message.RunState = 1;						
					
					g_AGV_Sta.flag_addTIME_OK = 2;
					Get_PC_data(1,&AGV_SYS.yuandian_ID);//ִ�л�ԭ�㶯��
				
				
				}				
	
				
	
										
				

			}
			else if(*g_dispatch_message.RunState == 3)		//���ģʽ:3 -->����ģʽ:0
			{
				
					g_AGV_speaker_flag.chongdian_goto = 1;				//�Ӹ���������
					delay_rtos(0,0,2,0);
				
				
				#if 0
				if(*g_dispatch_message.Task_RunFinish)					//����ִ�����
				{				
					if(g_user_chongdian) //��ԭ��
					{
						
						g_AGV_Sta.juedui_RFID = AGV_SYS.chongdian_ID;
						g_AGV_speaker_flag.chongdian_over = 1;
						delay_rtos(0,0,0,20);
						g_RunSta.chongdian = 0;
						SystemParameter[5] = g_RunSta.chongdian;			//���ģʽ
						SetOneParameterToSystem(SystemParameter[5], 5);		//����flash		
						g_RunSta.mode_chongdian = 4;						//3:���·�� 4:��緵��·��
						Get_PC_data(1,&AGV_SYS.yuandian_ID); 				//������λ��·����Ϣ��ִ��		//�����Ϊ�ֶ�����
						
					}				
				}	
				#endif				
			}			
		}
		else									//1:�˹�ģʽ
		{	

		    *g_dispatch_message.RunState = 0;	//�л�������ģʽ��δ����
						
			if(g_user_readyed)
			{
				//�����������
				g_AGV_Sta.juedui_RFID = AGV_SYS.yuandian_ID;
				g_AGV_Sta.flag_set_yuandian	= 1;	
				g_AGV_Sta.RFID_buff[0] = 0;
				g_AGV_Sta.RFID_buff[1] = 0;
				g_AGV_speaker_flag.AGV_readyed = 1;
				delay_rtos(0,0,0,100);				
			}
					
		}
		g_user_read = g_AGV_Sta.flag_set_yuandian;	

		delay_rtos(0,0,0,20);
	}
}


void Task21_task(void *p_arg)		//AGV����λ��������������
{
	u8 temo_j=0;
	u8 temp_k=0;
	p_arg = p_arg;

	delay_rtos(0,0,2,0);			//�ȴ�ͨ��ģ���ʼ��
	while(1)
	{
		//��ʱ��
		temo_j++;
		if(temo_j>50)					//ÿ1�뷢��һ��SDO
		{
			temp_k++;					//��PLC�������ź�1-60,ÿ���һ
			if(temp_k>60)
			{
				temp_k = 1;
			}
			*g_PLC_message[0].AGV2PLC_Heard = temp_k;	//��ɢ¯����
			*g_PLC_message[1].AGV2PLC_Heard = temp_k;	//PE¯����
					
			CompareVal_Send( 2, 9);		//AGV_CanOpen_Send -> Sever
			CompareVal_Send(20,25);		//AGV_CanOpen_Send -> PLC(��ɢ¯)	
			CompareVal_Send(31,36);		//AGV_CanOpen_Send -> PLC(PE¯)	
			
			Get_PDO_Data();				//��ȡAGV��Ϣ
			Post_Multiple_Registers(0,51,16,g_RT_message.BatteryLevel);	
			
			temo_j = 0;			
		}

		delay_rtos(0,0,0,20);
	}
}

void Task22_task(void *p_arg)		//AGV�г���
{
	p_arg = p_arg;
	
	while(1)
	{
		AGV_LED();
		
		delay_rtos(0,0,0,10);
	}
	
}


void Task23_task(void *p_arg)		//Զ��������Զ��Ӽ���
{
	u16 temp_speedd=0;
	u8 temp_dir=0;
	p_arg = p_arg;
	
	while(1)
	{	
		#if 0
		if(g_Start_flag.Start_Auto_PID && g_AGV_Sta.Car_Auto2Manu_mode == 0)	//�Զ�ģʽ
		{
			AGV_Auto_speed(&AGV_SYS.autu_speed_my,&AGV_SYS.Car_Auto_Speed,g_AGV_Sta.Car_dir);
		}
		#endif
		if(g_Start_flag.Start_Manu_PID && g_AGV_Sta.Car_Auto2Manu_mode == 1)	//�ֶ�ģʽ
		{
														
			temp_dir = g_AGV_yaokong.SD_ir - 1;									//�ֶ����� ǰ��:1 ����:2
			AGV_Manu_speed(AGV_SYS.Manu_speed_my,&g_AGV_yaokong.SD_Speed,temp_dir);
		}		
		
		delay_rtos(0,0,0,10);
	}
}
void Task24_task(void *p_arg)		//��ʱ��:�ͻ��Զ��峬ʱ�������ԭ��
{
	p_arg = p_arg;
	
	while(1)
	{	
		
		if(*g_dispatch_message.RunState == 2) //AGV����ģʽ�²Ż�ִ��
		{
			if(g_AGV_Sta.add_time < AGV_SYS.add_time_yuzhi && g_AGV_Sta.flag_addTIME_OK == 0)
			{
				g_AGV_Sta.add_time++;	
			}
			if(g_AGV_Sta.add_time >= AGV_SYS.add_time_yuzhi)
			{
				g_AGV_Sta.flag_addTIME_OK= 1;

				g_AGV_Sta.add_time = 0;
			
			}		
		}

			
		
		delay_rtos(0,0,1,0);
	}
}

void Task25_task(void *p_arg)		//USB
{
	p_arg = p_arg;
	
	while(1)
	{	
		IAP_U_Disk_UpData();
		
	}
}










