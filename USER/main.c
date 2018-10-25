#include "my_include.h"
#include "dbus.h"

//将这些优先级分配给了UCOSIII的5个系统内部任务
//优先级0：中断服务服务管理任务 OS_IntQTask()
//优先级1：时钟节拍任务 OS_TickTask()
//优先级2：定时任务 OS_TmrTask()
//优先级OS_CFG_PRIO_MAX-2：统计任务 OS_StatTask()
//优先级OS_CFG_PRIO_MAX-1：空闲任务 OS_IdleTask()

//任务优先级
#define START_TASK_PRIO		3
//任务堆栈大小	
#define START_STK_SIZE 		512
//任务控制块
OS_TCB StartTaskTCB;
//任务堆栈	
CPU_STK START_TASK_STK[START_STK_SIZE];
//任务函数
void start_task(void *p_arg);                       //开始任务

//任务优先级
#define Transducer_TASK_PRIO		4
//任务堆栈大小	
#define Transducer_STK_SIZE 		512
//任务控制块
OS_TCB TransducerTaskTCB;
//任务堆栈	
CPU_STK Transducer_TASK_STK[Transducer_STK_SIZE];
void Transducer_task(void *p_arg);					//手自动转换任务

//任务优先级
#define FLOAT_TASK_PRIO		5
//任务堆栈大小
#define FLOAT_STK_SIZE		512
//任务控制块
OS_TCB	FloatTaskTCB;
//任务堆栈
__align(8) CPU_STK	FLOAT_TASK_STK[FLOAT_STK_SIZE];
//任务函数
void float_task(void *p_arg);						//浮点任务


//任务优先级
#define MOTEC_TASK_PRIO		6
//任务堆栈大小	
#define MOTEC_STK_SIZE 		256
//任务控制块
OS_TCB MOTECTaskTCB;
//任务堆栈	
CPU_STK motec_TASK_STK[MOTEC_STK_SIZE];
//任务函数
void motec_task(void *p_arg);						//初始化Motec驱动器任务

//任务优先级
#define Auto_TASK_PRIO		7
//任务堆栈大小	
#define Auto_STK_SIZE 		512
//任务控制块
OS_TCB AutoTaskTCB;
//任务堆栈	
CPU_STK Auto_TASK_STK[Auto_STK_SIZE];
//任务函数
void Auto_task(void *p_arg);						//自动模式任务

//任务优先级 
#define PID_TASK_PRIO		8
//任务堆栈大小	
#define PID_STK_SIZE 		512
//任务控制块
OS_TCB PIDTaskTCB;
//任务堆栈	
CPU_STK PID_TASK_STK[PID_STK_SIZE];
//任务函数
void PID_task(void *p_arg);							//PID任务

//任务优先级
#define Manual_TASK_PRIO		9
//任务堆栈大小	
#define Manual_STK_SIZE 		512
//任务控制块
OS_TCB ManualTaskTCB;
//任务堆栈	
CPU_STK Manual_TASK_STK[Manual_STK_SIZE];
//任务函数
void Manual_task(void *p_arg);						//手动模式任务



//任务优先级
#define Screen_TASK_PRIO		10
//任务堆栈大小	
#define Screen_STK_SIZE 		1024
//任务控制块
OS_TCB ScreenTaskTCB;
//任务堆栈	
CPU_STK Screen_TASK_STK[Screen_STK_SIZE];
//任务函数
void Screen_task(void *p_arg);						//屏幕任务



//任务优先级
#define Task5_TASK_PRIO		11
//任务堆栈大小	
#define Task5_STK_SIZE 		512
//任务控制块
OS_TCB Task5_TaskTCB;
//任务堆栈	
CPU_STK Task5_TASK_STK[Task5_STK_SIZE];
//任务函数
void Task5_task(void *p_arg);						//自动执行路径或流程

//任务优先级
#define WIFI_TASK_PRIO		12
//任务堆栈大小	
#define WIFI_STK_SIZE 		512
//任务控制块
OS_TCB WIFITaskTCB;
//任务堆栈	
CPU_STK WIFI_TASK_STK[WIFI_STK_SIZE];
//任务函数
void WIFI_task(void *p_arg);						//WIFI任务

//任务优先级
#define guntong_TASK_PRIO		13
//任务堆栈大小	
#define guntong_STK_SIZE 		128
//任务控制块
OS_TCB guntongTaskTCB;
//任务堆栈	
CPU_STK guntong_TASK_STK[guntong_STK_SIZE];
//任务函数
void guntong_task(void *p_arg);						//滚筒任务

//任务优先级
#define DCv_TASK_PRIO		14
//任务堆栈大小	
#define DCv_STK_SIZE 		128
//任务控制块
OS_TCB DCvTaskTCB;
//任务堆栈	
CPU_STK DCv_TASK_STK[DCv_STK_SIZE];
//任务函数
void DCv_task(void *p_arg);							//电压采集

//任务优先级
#define OPENBOX_TASK_PRIO		15
//任务堆栈大小	
#define OPENBOX_STK_SIZE 		1024
//任务控制块
OS_TCB OPENBOXTaskTCB;
//任务堆栈	
CPU_STK OPENBOX_TASK_STK[OPENBOX_STK_SIZE];
//任务函数
void openbox_task(void *p_arg);						//基站通信解包及心跳

//任务优先级
#define HEARTBEAT_TASK_PRIO		16
//任务堆栈大小	
#define HEARTBEAT_STK_SIZE 		128
//任务控制块
OS_TCB HEARTBEATTaskTCB;
//任务堆栈	
CPU_STK HEARTBEAT_TASK_STK[HEARTBEAT_STK_SIZE];
//任务函数
void heartbeat_task(void *p_arg);					//暂未用

//任务优先级
#define Task17_TASK_PRIO		17
//任务堆栈大小	
#define Task17_STK_SIZE 		128
//任务控制块
OS_TCB Task17_TaskTCB;
//任务堆栈	
CPU_STK Task17_TASK_STK[Task17_STK_SIZE];
//任务函数
void Task17_task(void *p_arg);						//磁导航计数

//任务优先级
#define Task18_TASK_PRIO		18
//任务堆栈大小	
#define Task18_STK_SIZE 		128
//任务控制块
OS_TCB Task18_TaskTCB;
//任务堆栈	
CPU_STK Task18_TASK_STK[Task18_STK_SIZE];
//任务函数
void Task18_task(void *p_arg);						//磁导航计数

//任务优先级
#define Task19_TASK_PRIO		19
//任务堆栈大小	
#define Task19_STK_SIZE 		128
//任务控制块
OS_TCB Task19_TaskTCB;
//任务堆栈	
CPU_STK Task19_TASK_STK[Task19_STK_SIZE];
//任务函数
void Task19_task(void *p_arg);						//磁导航计数

//任务优先级
#define Task20_TASK_PRIO		20
//任务堆栈大小	
#define Task20_STK_SIZE 		512
//任务控制块
OS_TCB Task20_TaskTCB;
//任务堆栈	
CPU_STK Task20_TASK_STK[Task20_STK_SIZE];
//任务函数
void Task20_task(void *p_arg);						//上位机通信

//任务优先级
#define Task21_TASK_PRIO		21
//任务堆栈大小	
#define Task21_STK_SIZE 		128
//任务控制块
OS_TCB Task21_TaskTCB;
//任务堆栈	
CPU_STK Task21_TASK_STK[Task21_STK_SIZE];
//任务函数
void Task21_task(void *p_arg);						//上位机通信

//任务优先级
#define Task22_TASK_PRIO		22
//任务堆栈大小	
#define Task22_STK_SIZE 		128
//任务控制块
OS_TCB Task22_TaskTCB;
//任务堆栈	
CPU_STK Task22_TASK_STK[Task22_STK_SIZE];
//任务函数
void Task22_task(void *p_arg);						//AGV行车灯

//任务优先级
#define Task23_TASK_PRIO		23
//任务堆栈大小	
#define Task23_STK_SIZE 		128
//任务控制块
OS_TCB Task23_TaskTCB;
//任务堆栈	
CPU_STK Task23_TASK_STK[Task23_STK_SIZE];
//任务函数
void Task23_task(void *p_arg);						//远距离红外自动加减速

//任务优先级
#define Task24_TASK_PRIO		24
//任务堆栈大小	
#define Task24_STK_SIZE 		128
//任务控制块
OS_TCB Task24_TaskTCB;
//任务堆栈	
CPU_STK Task24_TASK_STK[Task24_STK_SIZE];
//任务函数
void Task24_task(void *p_arg);						//计时器:客户自定义超时无任务回原点

//任务优先级
#define Task25_TASK_PRIO		25
//任务堆栈大小	
#define Task25_STK_SIZE 		128
//任务控制块
OS_TCB Task25_TaskTCB;
//任务堆栈	
CPU_STK Task25_TASK_STK[Task25_STK_SIZE];
//任务函数
void Task25_task(void *p_arg);						//计时器:客户自定义超时无任务回原点

int main(void)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	
	IAP_IRQ_Remap_Init(0x8000);		  				//设置偏移量32K=0x8000

	delay_init(168);  	//时钟初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断分组配置

	LED_Init();         //LED初始化
	beep_init();   		//PA3
	rgb_init();
	button_input_init();
	//motor_init();
	guntong_init();
	
	DMA_adc1_Init();    				//电位器
	//DMA_Uart2_Init();					//以太网转串口	//@@屏蔽掉这句会导致电池通信接收失败@@//
	DMA_Uart3_Init();					//锂电池通信	
	DMA_Uart4_Init();					//触摸屏		
	
	ADC1_Configuration();				//电位器采集
	USART1_Configuration(9600); 		//串口1 PA9PA10 现在换成喇叭线
	USART2_Configuration(115200);		//以太网转串口的接口
	USART3_Configuration(9600);			//现在是锂电池电量检测的口 -- 232转TTL串口
	uart4_init(9600);					//触摸屏485
	//USART6_Configuration(115200);		
	

	//DMA_Uart6_Init();
//	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_Normal);//CAN初始化环回模式,波特率500Kbps    
//	CAN2_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_Normal);	
	NVIC_Configuration();

	TIM4_PWM_Init(21000-1,4-1);		//  1000,8   21000 000
	PID_Init();
	
	UserConfigInit();				//用户参数初始化	

	WIFI_init(AGV_SYS.ID); 
	
	IAP_U_Disk_Init();				//USB初始化
	                                                                                   
	
	
/**************************************************************************************/
	OSInit(&err);			//初始化UCOSIII
	OS_CRITICAL_ENTER();	//进入临界区
	//创建开始任务
	OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		//任务控制块
								 (CPU_CHAR	* )"start task", 			//任务名字
                 (OS_TASK_PTR )start_task, 			//任务函数
                 (void		* )0,					//传递给任务函数的参数
                 (OS_PRIO	  )START_TASK_PRIO,     //任务优先级
                 (CPU_STK   * )&START_TASK_STK[0],	//任务堆栈基地址
                 (CPU_STK_SIZE)START_STK_SIZE/10,	//任务堆栈深度限位
                 (CPU_STK_SIZE)START_STK_SIZE,		//任务堆栈大小
                 (OS_MSG_QTY  )0,					//任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
                 (OS_TICK	  )0,					//当使能时间片轮转时的时间片长度，为0时为默认长度，
                 (void   	* )0,					//用户补充的存储区
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //任务选项
                 (OS_ERR 	* )&err);				//存放该函数错误时的返回值
	OS_CRITICAL_EXIT();		//退出临界区	 
	OSStart(&err);  		//开启UCOSIII								 
}
/**************************************************************************************/

void start_task(void *p_arg)		//开始任务函数
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//统计任务                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//如果使能了测量中断关闭时间
    CPU_IntDisMeasMaxCurReset();	
#endif

#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //当使用时间片轮转的时候
	 //使能时间片轮转调度功能,时间片长度为1个系统时钟节拍，既1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif		
	
	OS_CRITICAL_ENTER();	//进入临界区
///////////////////////////////////////////////////////////////////////////////	
	//创建Transducer任务
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

	//创建浮点测试任务
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

	//创建自动任务
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
				 
	//创建自动任务
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
				 
	//创建手动任务
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
				 
	

	//创建触摸屏任务
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

	//创建路径流程任务
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
				 
	//电压采集		
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
	//磁条上轨及软启动					 		 
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
	
	//创建磁导航计数任务
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
				 
	//前轮磁导航分叉
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
				 
	//后轮磁导航分叉
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
	//上位机通信
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

	//上位机数据发送
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

	//AGV行车灯
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

	//远距离红外自动加减速
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

	//计时器:客户自定义超时无任务回原点
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
	OS_TaskSuspend((OS_TCB*)&StartTaskTCB,&err);		//挂起开始任务			 
	OS_CRITICAL_EXIT();	//退出临界区
								 
}




void Transducer_task(void *p_arg)  	//开关量输入采集及行车灯状态
{
	u8 temp_k=0;
	OS_ERR err;
	p_arg = p_arg;	
	
	while(1)
	{
		//只剩下红外避障的程序跟状态灯
		agv_24V_input(); 	//外部24V输入信号采集
		AGV_Stop2Start();	//启动停止信号的采集,并控制车的停止启动
		Get_Warning_data();	//获取AGV系统的警告信息
		temp_k++;
		if(temp_k > 5)
		{
			temp_k = 0;
			LED2 = !LED2;
		}
		
		
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err); //每10ms检测输入状态
	}
}

void float_task(void *p_arg)		//红外和机械避障
{
	OS_ERR err;
	u8 temp_i=0;
	u8 temp_j=0;

	u8 temp_Tiaojian[] = {0,0,0,0};					//条件
	u8 *temp_Jieguo[]  = {&g_Start_flag.Start_IR,&g_Start_flag.Start_jixie,&g_Start_flag.Start_IR,&g_Start_flag.Start_jixie};//结果
	
	while(1)
	{	
		#if 1
		if(!g_AGV_Sta.Car_Auto2Manu_mode)				//0:自动模式
		{
			if(!g_AGV_Sta.Car_dir)	//0:前进
			{
				temp_j = 0;
			}
			else					//1:后退
			{
				temp_j = 2;
			}	
		}
		else											//1:手动模式
		{
			//0:停止1:前进 2:后退  
			if(g_AGV_yaokong.SD_ir==1)			//前进
			{
				temp_j = 0;		
			}
			else if(g_AGV_yaokong.SD_ir==2)		//1:后退
			{
				temp_j = 2;
			}		
		}
		
		if(temp_j == 0)
		{
			temp_Tiaojian[0] = g_Senser_InPut.IR_qian_jin;			//条件
			temp_Tiaojian[1] = g_Senser_InPut.JiXie_qian;		//条件		
		}
		else if(temp_j == 2)
		{
			temp_Tiaojian[2] = g_Senser_InPut.IR_hou_jin;			//条件
			temp_Tiaojian[3] = g_Senser_InPut.JiXie_hou;		//条件			
		}

		for(temp_i=temp_j;temp_i<temp_j+2;temp_i++)
		{
			if(temp_Tiaojian[temp_i] == 1)				//近红外避障 1触发
			{
//				if(g_Start_flag.Start_Auto_PID || g_AGV_yaokong.SD_Speed)	//停止状态避障不触发
//				{
					*temp_Jieguo[temp_i] = 0;				//0停止	
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
			else										//红外未触发
			{
				if(temp_Tiaojian[temp_i] == 0)			//机械也未触发
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
					if(*temp_Jieguo[temp_i] == 0)		//是从停止状态进来的
					{
						delay_rtos(0,0,2,0);			//等待2秒启动
						*temp_Jieguo[temp_i] = 1;		//1:启动
					}
					else
					{									//直接启动
						*temp_Jieguo[temp_i] = 1;		//1:启动
					}					
				}		
			}					
		}
		#endif 
		
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err); //延时ms
	}
}



void motec_task(void *p_arg)		//初始化Motec驱动器
{
	//OS_ERR err;
	p_arg = p_arg;
	
	g_motec_init.init_delay_val = 150;		//
	g_AGV_Sta.Car_fencha_dir = 1;			//默认分叉方向
	
	while(1)
	{
		check_Motec_init();
		delay_rtos(0,0,0,20);
	}		
}



void Auto_task(void *p_arg)			//自动模式--前轮PID
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
				if(g_Start_flag.Start_Auto_PID)		//1:找到磁条
				{
					PID_AUTO_QianLun(AGV_SYS.Car_Auto_Speed,AGV_SYS.AUTO_Kp,AGV_SYS.AUTO_Ki,AGV_SYS.AUTO_Kd);	//前轮				
				}
				if(stop_num > 100)
				{
					MotoStop(0);//只发送一次,未优化
					stop_num = 0;
				}						
			}
		}
		if(!AGV_SYS.PID_time)
		{
			AGV_SYS.PID_time = 10;
		}
		OSTimeDlyHMSM(0,0,0,AGV_SYS.PID_time,OS_OPT_TIME_HMSM_STRICT,&err); 		//暂定10ms		
		
	}		
}
void PID_task(void *p_arg)			//自动模式--后轮PID
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
				if(g_Start_flag.Start_Auto_PID)				//1:找到磁条
				{				
					PID_AUTO_HouLun(AGV_SYS.Car_Auto_Speed,AGV_SYS.AUTO_Kp,AGV_SYS.AUTO_Ki,AGV_SYS.AUTO_Kd);		//后轮
					//g_CtXunZheng.XunZ_OK_AGV = 0;			//清除磁条上轨标志				
				}
				else
				{
					if(stop_num > 100)
					{
						MotoStop(0);//只发送一次,未优化
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
		OSTimeDlyHMSM(0,0,0,AGV_SYS.PID_time,OS_OPT_TIME_HMSM_STRICT,&err); 		//暂定10ms		
		
	}
}



void Manual_task(void *p_arg)  		//手动任务
{
	p_arg = p_arg;
	
	while(1)
	{
		
		if(g_motec_init.Init_OK)
		{
			//前进左右转 -- 后轮打直,前轮负责转向
			//后退左右转 -- 前轮打直,后轮负责转向
			
			if(g_AGV_Sta.Car_Auto2Manu_mode) 					//1://手动模式
			{	
				if(g_AGV_yaokong.SD_Speed > 50 && g_AGV_yaokong.SD_ir!=0) 	
				{
					if(g_Start_flag.Start_Manu_PID)				//1:启动
					{
						g_XZ_Ok = 0;
						PID_SD_Adjust(g_AGV_yaokong.SD_Speed,AGV_SYS.SD_Kp,AGV_SYS.SD_Ki,AGV_SYS.SD_Kd);	//延时在里面
						
					}		
					else										//0:停止
					{
						MotoStop(0);
						if(!g_XZ_Ok)
						{
							DwqXunZheng_QH();					//电位器寻正	
						}					
					}
				}		
				else 
				{
					MotoStop(0);								//后续更新,不一直发送				
					if(!g_XZ_Ok)
					{
						DwqXunZheng_QH();						//电位器寻正	
					}	
					if(g_Start_flag.button_bizhang_Start==0)
					{
						g_Start_flag.Start_Manu_PID = 0;		//允许手动PID	
					}
					else
					{
						g_Start_flag.Start_Manu_PID = 1;		//允许手动PID	
					}									
				}					
			}			
		}
		if(!AGV_SYS.PID_time)
		{
			AGV_SYS.PID_time = 10;
		}
		delay_rtos(0,0,0,AGV_SYS.PID_time); 					//10ms,屏幕上设置
	}
}


void Screen_task(void *p_arg)    	//触摸屏界面操作  		//显控屏地址:4x32  
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

			//开发者界面程序段
			case ShouDongJieMian: 		//--3					//3//手动操作界面
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
					
					 SD2ZD_check_UP();			//手自动切换

					 if(g_AGV_Sta.Car_Auto2Manu_mode == 0)				//0:自动模式 1:自动模式
					 {
							*g_dispatch_message.RunState = 0;					//切换到非就绪模式
							ZD_check_UP();		//自动模式操作
					 }
					 else
					 {		
							*g_dispatch_message.RunState = 0;					//切换到非就绪模式
						 	SD_check_UP();		//手动模式操作	 
					 }

					 AGV_SYS.SD_Speed_bili = g_shoudong_screen_speed;	//PLC_Data[3]				//更新屏幕的速度显示值

					 SystemParameter[3] = AGV_SYS.SD_Speed_bili;		//手动速度比例:  x/10
					 g_shoudong_screen_RFID = g_AGV_Sta.juedui_RFID; //更新当前地标
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
			//路径规划段界面	
			case LuJingSheZhiJieMian: 				//9//路径设置界面（第一次选择规划路径时的界面）
			{
				//如果路径号为零，则置一
				if(HmiRouteNum == 0)
				{
					 HmiRouteNum = 2;
				}
			}
			break;
			case LuJingGuiHuaJieMian:					//4路径规划界面
			case FuZhiLuJingTanChuJieMian:				//11复制路径界面
			case QueDingChaRuZhanDianJieMian: 			//12插入站点界面
			case QueDingShanChuZhanDianJieMian:			//13删除站点界面
			case XvNiDiBiaoJieMian:  					//14虚拟地标界面
			{
				while(HmiScreenSetGet == LuJingGuiHuaJieMian || HmiScreenSetGet == FuZhiLuJingTanChuJieMian ||
						HmiScreenSetGet == QueDingChaRuZhanDianJieMian || HmiScreenSetGet == QueDingShanChuZhanDianJieMian ||
						HmiScreenSetGet == XvNiDiBiaoJieMian)
				{
					 //复制路径
					 if(HmiScreenSetGet == FuZhiLuJingTanChuJieMian)
					 {
							//被复制路径号初始化为1
							HmiRouteCopiedNum = 1;
							while(HmiScreenSetGet == FuZhiLuJingTanChuJieMian) //处于复制路径界面
							{
								//被复制路径号为零时置1
								if(HmiRouteCopiedNum == 0)
									 HmiRouteCopiedNum = 1;
								if(HmiRouteCopiedNum > RouteNum)
								{
									 HmiRouteCopiedNum = 1;
								}

								//输入的被复制路径号变化时更新
								if(HmiRouteCopiedNumTemp != HmiRouteCopiedNum)
									 HmiRouteCopiedCount = GetRouteStationNum(HmiRouteCopiedNum);


								//确定复制
								if(HmiRoutemode == 1)
								{
									 //读取被复制信息到当前
									 GetRouteData(HmiRouteCopiedNum);

									 //保存并更新被复制信息
									 SetRouteData(HmiRouteNum);

									 UpdataStationToHmi();

									 //设置当前站点为1
									 if(HmiStationNum != 0)
											HmiStationSerialNum = 1;

									 //退出复制模式
									 HmiRoutemode = 0;
								}
								osdelay_ms(10);
							}
					 }

					 //添加站点
					 if(HmiRoutemode == 2)	//4x41确定按键的模式，查看0，复制1，添加2，插入3，更改4，删除5
					 {
							//站点数加一
							HmiStationNum ++;
							//站点号等于站点数
							HmiStationSerialNum = HmiStationNum;

							//地标号清零
							g_AGV_RFID_ID = 0;

							ClearStationToHmi();
					 
							while(HmiRoutemode == 2)
							{
								//如果读到地标，更新到显示器
								if(g_AGV_RFID_ID != 0)
								{
									 HmiRfidNum = g_AGV_RFID_ID;//刷新地标号
									 g_AGV_RFID_ID = 0;
								}

								//确定
								if(HmiRouteEnter == 1)
								{
									 HmiRouteEnter = 0;
									 //更新站点数据到当前数据
									 UpdataStationToNow();
									
									 //保存路径包含站点数
									 SetRouteStationNum();
									 //保存站点信息,num:路径号,n站点号
									 SetStationData(HmiRouteNum,HmiStationSerialNum);
									
									 //退出添加模式
									 HmiRoutemode =	0;
								}
								else
								 //取消
								 if(HmiRouteEnter == 2)
								 {
										HmiRouteEnter = 0;
										//站点数减一
										HmiStationNum--;
										//站点号等于站点数
										HmiStationSerialNum = HmiStationNum;
										//退出添加模式
										HmiRoutemode =	0;
								 }
								osdelay_ms(10);
							}
					 }
					 //插入站点
					 if(HmiRoutemode == 3)
					 {
							//站点数加一
							HmiStationNum ++;
							//站点号为零时加一
							if(HmiStationNum == 0)
								HmiStationSerialNum = 1;

							//地标号清零
							g_AGV_RFID_ID = 0;

							ClearStationToHmi();

							while(HmiRoutemode == 3)
							{
								//如果读到地标，更新到显示器
								if(g_AGV_RFID_ID != 0)
								{
									 HmiRfidNum = g_AGV_RFID_ID;//刷新地标号
									 g_AGV_RFID_ID = 0;
								}

								//确定
								if(HmiRouteEnter == 1)
								{
									 HmiRouteEnter = 0;

									 //站点信息向后移动一个位置，并插入当前站点信息
									 for(i = HmiStationNum; i >= HmiStationSerialNum; i--)
									 {
											for(j = 0; j < StaiionInfor; j++)
											{
												NowRouteInfor[i][j] = NowRouteInfor[i - 1][j];
											}
									 }

									 //更新站点信息到当前
									 UpdataStationToNow();

									 //保存路径信息
									 SetRouteData(HmiRouteNum);

									 //退出添加模式
									 HmiRoutemode =	0;
								}
								else
									 //取消
									 if(HmiRouteEnter == 2)
									 {
											HmiRouteEnter = 0;
											//站点数减一
											HmiStationNum--;
											//站点号为1时置零
											if(HmiStationSerialNum == 1)
												HmiStationSerialNum = 0;
											//退出添加模式
											HmiRoutemode =	0;
									 }

								osdelay_ms(10);
							}

					 }
					 //更改站点
					 if(HmiRoutemode == 4)
					 {
							g_AGV_RFID_ID = 0;
							while(HmiRoutemode == 4)
							{
								//如果读到地标，更新到显示器
								if(g_AGV_RFID_ID != 0)
								{
									 HmiRfidNum = g_AGV_RFID_ID;//刷新地标号
									 g_AGV_RFID_ID = 0;
								}

								//确定
								if(HmiRouteEnter == 1)
								{
									 HmiRouteEnter = 0;
									 //更新站点数据到当前数据
									 UpdataStationToNow();
									 //保存路径包含站点数
									 SetRouteStationNum();
									 //保存站点信息,num:路径号,n站点号
									 SetStationData(HmiRouteNum,HmiStationSerialNum);
									 //退出添加模式
									 HmiRoutemode =	0;
								}
								else
									 //取消
									 if(HmiRouteEnter == 2)
									 {
											HmiRouteEnter = 0;
											//更新到界面
											UpdataStationToHmi();
											//退出添加模式
											HmiRoutemode =	0;
									 }
								osdelay_ms(10);
							}
					 }

					 //删除站点
					 if(HmiRoutemode == 5)
					 {
							if(HmiStationNum > 0)
							{
								//将后面所数据向前移动一位
								if((HmiStationNum > 0) && ((HmiStationNum) != HmiStationSerialNum))
								{
									 //站点信息向前移动一个位置
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
								//保存路径信息
								SetRouteData(HmiRouteNum);

								//更新界面
								UpdataStationToHmi();
							}
							HmiRoutemode = 0;
					 }

					 //查询站点
					 if(HmiRoutemode == 0)
					 {
							//当路径站点数大于0，并且序号为0时，设置序号为1，并更新显示内容
							if((HmiStationNum > 0) && (HmiStationSerialNum == 0))
							{
								HmiStationSerialNum = 1;
								//更新到界面
								UpdataStationToHmi();
							}
							else if(HmiStationNum == 0)
							{
								HmiStationSerialNum = 0;
							}

							//路径号变化时，更新界面
							if(HmiRouteNumFlag != HmiRouteNum)
							{
								HmiRouteNumFlag = HmiRouteNum;
								//获取路径信息
								GetRouteData(HmiRouteNum);
								if(HmiStationNum > 0)
									 HmiStationSerialNum = 1;
								//更新到界面
								UpdataStationToHmi();
							}

							//上一个
							if(HmiStationLast == 1)
							{
								HmiStationLast = 0;
								if(HmiStationSerialNum > 1)
									 HmiStationSerialNum--;
								else
									 HmiStationSerialNum = HmiStationNum;
							}
							//下一个
							if(HmiStationNext == 2)
							{
								HmiStationNext = 0;
								if(HmiStationSerialNum < HmiStationNum)
									 HmiStationSerialNum++;
								else if(HmiStationSerialNum != 0)
									 HmiStationSerialNum = 1;
							}

							if(HmiStationNum == 0)		//没有站点
							{
								//清除站点信息
								ClearStationToHmi();
							}
							else
							{
								//更新站点信息
								UpdataStationToHmi();
							}
					 }
					osdelay_ms(10);
				}
			}
			break;
			//流程规划段界面
			case LiuChengSheZhiJieMian: 			//10//流程设置界面（第一次选择规划流程时的界面）
			{
				//如果流程号为零，则置一
				if(HmiProcessNum == 0)
				{
					 HmiProcessNum = 1;
				}
			}
			break;
			case LiuChengGuiHuaJieMian:				//流程规划界面
			case FuZhiLiuChengTanChuJieMian:		//复制流程界面
			case QueDingChaRuLiuChengJieMian:   	//插入流程界面
			case QueDingShanChuLiuChengJieMian: 	//删除流程界面
			{
				while(HmiScreenSetGet == LiuChengGuiHuaJieMian || HmiScreenSetGet == FuZhiLiuChengTanChuJieMian || HmiScreenSetGet == QueDingChaRuLiuChengJieMian || HmiScreenSetGet == QueDingShanChuLiuChengJieMian)
				{
					 //查看模式
					 if(HmiProcessMode == 0)
					 {
							//当前流程步数大于0，并且界面序号为0时，设置序号为1，并更新显示内容
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

							//流程号变化时，更新界面
							if(HmiProcessNumFlag != HmiProcessNum)
							{
								HmiProcessNumFlag = HmiProcessNum;
								GetProcessData();
							}

							if(HmiProcessLast == 1) //上一个
							{
								HmiProcessLast = 0;
								if(HmiProcessSerialNum > 1)
									 HmiProcessSerialNum--;
								else
									 HmiProcessSerialNum = HmiStepNum;
							}
							else if(HmiProcessNext == 2) //下一个
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
					 //复制流程
					 if(HmiScreenSetGet == FuZhiLiuChengTanChuJieMian)
					 {
							//初始化别复制流程为1
							HmiProcessCopiedNum = 1;
							while(HmiScreenSetGet == FuZhiLiuChengTanChuJieMian)
							{
								//被复制流程号为零时置1
								if(HmiProcessCopiedNum == 0)
									 HmiProcessCopiedNum = 1;
								if(HmiProcessCopiedNum > ProcessNum)
									 HmiProcessCopiedNum = 1;

								//输入的被复制流程号变化时更新
								if(HmiProcessCopiedNumTemp != HmiProcessCopiedNum)
									 HmiProcessCopiedCount = GetProcessStepNum(HmiProcessCopiedNum);

								//确定复制
								if(HmiProcessMode == 1)
								{
									 //读取被复制信息到当前
									 GetProcessDataFrom(HmiProcessCopiedNum);
									 //保存被复制信息
									 SetProcessData();

									 //设置当前序号为1
									 if(HmiStepNum != 0)
											HmiProcessSerialNum = 1;

									 //退出复制模式
									 HmiProcessMode = 0;
								}
								osdelay_ms(10);
							}
					 }

					 //添加流程
					 if(HmiProcessMode == 2)
					 {
							//流程步数加一
							HmiStepNum++;
							//序号等于流程数
							HmiProcessSerialNum = HmiStepNum;

							ClearStepToHmi();

							while(HmiProcessMode == 2)
							{
								switch(HmiProcessAction)
								{
								case 0://单次执行
									 break;
								case 1://顺序执行到
									 if(HmiProcessStopNum <= HmiProcessStartNum)
									 {
											if(HmiProcessStartNum == ProcessNum)
												HmiProcessStopNum = HmiProcessStartNum;
											else
												HmiProcessStopNum = HmiProcessStartNum + 1;
									 }
									 break;
								case 2://倒序执行
									 if(HmiProcessStopNum >= HmiProcessStartNum)
									 {
											if(HmiProcessStartNum == 1)
												HmiProcessStopNum = HmiProcessStartNum;
											else
												HmiProcessStopNum = HmiProcessStartNum - 1;
									 }
									 break;
								case 3://循环执行
									 if(HmiProcessStopNum == 0)
									 {
											HmiProcessStopNum = 1;
									 }
									 break;
								default:
									 break;
								}

								//确定
								if(HmiProcessEnter == 1)
								{
									 HmiProcessEnter = 0;
									 //保存并更新数据
									 SetProcessData();

									 //退出添加模式
									 HmiProcessMode = 0;
								}
								//取消
								else if(HmiProcessEnter == 2)
								{
									 HmiProcessEnter = 0;

									 //流程步数减一
									 HmiStepNum--;
									 //序号等于流程数
									 HmiProcessSerialNum = HmiStepNum;

									 //退出添加模式
									 HmiProcessMode = 0;
								}
								osdelay_ms(10);
							}
					 }


					 //插入流程
					 if(HmiProcessMode == 3)
					 {
							//流程步数加一
							HmiStepNum++;
							//序号为零时加一
							if(HmiProcessSerialNum == 0)
								HmiProcessSerialNum = 1;

							ClearStepToHmi();

							while(HmiProcessMode == 3)
							{
								switch(HmiProcessAction)
								{
								case 0://单次执行
									 break;
								case 1://顺序执行到
									 if(HmiProcessStopNum <= HmiProcessStartNum)
									 {
											if(HmiProcessStartNum == ProcessNum)
												HmiProcessStopNum = HmiProcessStartNum;
											else
												HmiProcessStopNum = HmiProcessStartNum + 1;
									 }
									 break;
								case 2://倒序执行
									 if(HmiProcessStopNum >= HmiProcessStartNum)
									 {
											if(HmiProcessStartNum == 1)
												HmiProcessStopNum = HmiProcessStartNum;
											else
												HmiProcessStopNum = HmiProcessStartNum - 1;
									 }
									 break;
								case 3://循环执执行
									 if(HmiProcessStopNum == 0)
									 {
											HmiProcessStopNum = 1;
									 }
									 break;
								default:
									 break;
								}

								//确定
								if(HmiProcessEnter == 1)
								{
									 HmiProcessEnter = 0;

									 //保存并更新数据
									 InsertProcessData();

									 //退出插入模式
									 HmiProcessMode = 0;
								}
								//取消
								else if(HmiProcessEnter == 2)
								{
									 HmiProcessEnter = 0;

									 //流程步数减一
									 HmiStepNum--;
									 //序号为1时减一
									 if(HmiProcessSerialNum == 1)
											HmiProcessSerialNum = 0;

									 //退出添加模式
									 HmiProcessMode = 0;
								}
								osdelay_ms(10);
							}
					 }

					 //更改流程
					 if(HmiProcessMode == 4)
					 {
							while(HmiProcessMode == 4)
							{
								switch(HmiProcessAction)
								{
								case 0://单次执行
									 break;
								case 1://顺序执行到
									 if(HmiProcessStopNum <= HmiProcessStartNum)
									 {
											if(HmiProcessStartNum == ProcessNum)
												HmiProcessStopNum = HmiProcessStartNum;
											else
												HmiProcessStopNum = HmiProcessStartNum + 1;
									 }
									 break;
								case 2://倒序执行
									 if(HmiProcessStopNum >= HmiProcessStartNum)
									 {
											if(HmiProcessStartNum == 1)
												HmiProcessStopNum = HmiProcessStartNum;
											else
												HmiProcessStopNum = HmiProcessStartNum - 1;
									 }
									 break;
								case 3://循环执行
									 if(HmiProcessStopNum == 0)
									 {
											HmiProcessStopNum = 1;
									 }
									 break;
								default:
									 break;
								}

								//确定
								if(HmiProcessEnter == 1)
								{
									 HmiProcessEnter = 0;
									 //保存并更新数据
									 SetProcessData();

									 //退出更改模式
									 HmiProcessMode = 0;
								}
								//取消
								else if(HmiProcessEnter == 2)
								{
									 HmiProcessEnter = 0;

									 //退出添加模式
									 HmiProcessMode = 0;
								}
								osdelay_ms(10);
							}
					 }

					 //删除流程
					 if(HmiProcessMode == 5)
					 {
							DeleteProcessData();
							//退出删除模式
							HmiProcessMode = 0;
					 }

					 osdelay_ms(10);
				}
			}
			break;
			//执行任务段界面
			case ZhiXingLuJingJieMian: 				//18//执行路径界面
			{
				while(HmiScreenSetGet == ZhiXingLuJingJieMian)
				{
					 if(ZhiXingLuJingQueDing == 1)
					 {
							//保存路径号
							SetOneParameterToSystem(HmiRouteNum, 24);
							SystemParameter[26] = HmiTask;
							//保存任务号
							SetOneParameterToSystem(HmiTask, 26);
							ZhiXingLuJingQueDing = 0;

							//加载自动界面信息
							HmiAutoReload();

							HmiTask = 1;

							g_AGV_Sta.Car_dir = AGV_SYS.yuandian_dir; //方向切换到前进  

							//跳转到自动界面
							HmiScreenSetGet = ZiDongJieMian;
					 }
					 osdelay_ms(10);
				}
			}
			break;
			case ZhiXingLiuChengJieMian:  			//执行流程界面
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
			case ZiDongJieMian: 					//20自动运行界面
			{
				while(HmiScreenSetGet == ZiDongJieMian)
				{
					 //SD2ZD_check_UP();
					 g_luluzi_ID 	  = AGV_SYS.ToPLC_task%10;
					 g_guan_ID 		  = AGV_SYS.guan_ID;
					 g_quzhoufangzhou = AGV_SYS.ToPLC_task/10; //1:放舟 2:取
					 g_prtf_autu_speed = AGV_SYS.Car_Auto_Speed;
					
					 if(g_AGV_Sta.Car_Auto2Manu_mode == 0)				//0:自动模式 1:手动模式
					 {	
						ZD_check_UP_AUTO();
					 }
					 osdelay_ms(10);		//时间短的话点一下会连读两次,长的话会反应迟钝,50ms刚好
				}
				
			}
			break;
			case QuXiaoRenWuJieMian: 				//取消任务界面
			{
				while(HmiScreenSetGet == QuXiaoRenWuJieMian)
				{
					 if(QuXiaoRenWuQueDing == 1)
					 {
							QuXiaoRenWuQueDing = 0;
							HmiTask = 0;		//0:无任务 1:执行路径 2;执行流程
							//任务状态为空闲
							HmiTaskState = 0;
							//停车
							Ting_Zhi(); 

							//切换方向标识为前进
							g_AGV_Sta.Car_dir = AGV_SYS.yuandian_dir;

						 							//清除各个信号标志				
							AGV_SYS.ToPLC_task = 0;							//给PLC的任务信息清零
							AGV_SYS.guan_ID = 0;
							g_AGV_Sta.flag_set_yuandian	= 0;
							g_AGV_Sta.flag_fist_zhilu = 0;
							g_AGV_Sta.add_time = 0;
							HmiScreenSetGet = 2;				//跳转到手动界面									
							
											
							*g_dispatch_message.Task_RunFinish = 0;			//清除任务完成标志												
							*g_dispatch_message.Task_Recived   = 0;			//收到任务
							*g_dispatch_message.Task_RunStart  = 0;			//开始执行任务	
							*g_dispatch_message.RunState = 0;				//切换到未就绪状态												

							*g_PLC_message[AGV_SYS.ID-1].StoveID = 0;						//AGV告诉PLC需要通信的炉子ID 
							*g_PLC_message[AGV_SYS.ID-1].Flag_Position_OK 	 = 0;			//AGV告诉PLC到达指定位置				
							//告诉PLC当前工位任务信息 1:送舟 2:取舟
							*g_PLC_message[AGV_SYS.ID-1].TO_PLC_Task_data    = 0;			
							*g_PLC_message[AGV_SYS.ID-1].Flag_RecTray_Ready  = 0;			//AGV告诉PLC接收托盘准备就绪
							*g_PLC_message[AGV_SYS.ID-1].Flag_RecTray_Finish = 0;			//AGV告诉PLC托盘接收完成
							g_RunSta.roller = 0;											//非输送状态		
							AGV_SYS.Car_Auto_Speed 	= AGV_SYS.M_speed;						//1:中速
							GunTong_L(0);
							//删除任务
							OSTaskDel((OS_TCB*)&Task5_TaskTCB, &err);
							//重新创建任务
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
											

							//NVIC_SystemReset();		//软复位
											
					 }
					 osdelay_ms(10);
				}
			}
			break;
			//数据调试及系统参数界面段程序
			case ChuanGanQiJieMian:					//22//传感器调试各个传感器的状态更新到屏幕上
			{
				while(HmiScreenSetGet == ChuanGanQiJieMian)
				{
					g_IR_yuan_CAR_qian 	= 	g_Senser_InPut.IR_qian_yuan;	//#define g_IR_yuan_CAR_qian 		PLC_OutPut[25]	//车前远红外避障
					g_IR_yuan_CAR_hou	=	g_Senser_InPut.IR_hou_yuan;		//#define g_IR_yuan_CAR_hou		PLC_OutPut[26]	//车后远红外避障
                    
					g_IR_jin_CAR_qian	=	g_Senser_InPut.IR_qian_jin;		//#define g_IR_jin_CAR_qian		PLC_OutPut[29] //车前近红外
					g_IR_jin_CAR_hou	=	g_Senser_InPut.IR_hou_jin;		//#define g_IR_jin_CAR_hou		PLC_OutPut[30] //车后近红外
                    
					g_jiexie_qian		=	g_Senser_InPut.JiXie_qian;		//#define g_jiexie_qian			PLC_OutPut[46]	//前机械避障
					g_jiexie_hou		=	g_Senser_InPut.JiXie_hou;		//#define g_jiexie_hou			PLC_OutPut[47]	//后机械避障
                    
					g_IR_guntong_left	=	g_Senser_InPut.gunt_IR_L;			//#define g_IR_guntong_left		PLC_OutPut[27]	//辊筒左红外
					g_IR_guntong_right	=	g_Senser_InPut.gunt_IR_R;			//#define g_IR_guntong_right		PLC_OutPut[28]  //辊筒右红外
					
					g_jixieKEY_start	=	g_Senser_InPut.button_Start;	//g_button_start;
					g_jixieKEy_stop		=	g_Senser_InPut.button_Stop;		//g_button_stop;
					
					osdelay_ms(10);
				}
			}
			break;
			case JiBenShuJuJieMian:					//23//基本数据测试界面
			{
				while(HmiScreenSetGet == JiBenShuJuJieMian)
				{
					
					
					 g_screen_qianCDH1 = g_CT_bit[1];
					 g_screen_qianCDH2 = g_u16_val[2];
					 g_screen_houCDH1  = g_CT_bit[3];
					 g_screen_houCDH2  = g_u16_val[4];
					
					 g_screen_qianlun_jiaodu   	= g_After_filter[1];
					 g_screen_houlun_jiaodu 	= g_After_filter[2];
					
					 AGV_SYS.AUTO_Kp = g_screen_Auto_Kp;		           //更新自动Kp
					 AGV_SYS.AUTO_Ki = g_screen_Auto_Ki;                 //更新自动ki
					 AGV_SYS.AUTO_Kd = g_screen_Auto_Kd;                 //更新自动kd

					 AGV_SYS.SD_Kp = g_screen_Manu_Kp;	          	  //更新手动kp
					 AGV_SYS.SD_Ki = g_screen_Manu_Ki;               	  //更新手动ki
					 AGV_SYS.SD_Kd = g_screen_Manu_Kd;              	  //更新手动kd

					 AGV_SYS.PID_time  = g_screen_control_TIME;						//测试前进的PID控制周期
					
					 AGV_SYS.add_time_yuzhi = g_add_time;
					
					 g_DWQ.qianlun_L_val 	 = g_screen_qianlun_ZuoZhi;					//前轮左极限
					 g_DWQ.qianlun_zhong_val = g_screen_qianlun_ZhongZhi;					//前轮中值
					 g_DWQ.qianlun_R_val 	 = g_screen_qianlun_YouZhi;					//前轮右极限
					
					 g_DWQ.houlun_L_val 	 = g_screen_houlun_ZuoZhi;					//后轮左极限
					 g_DWQ.houlun_zhong_val  = g_screen_houlun_ZhongZhi;					//后轮中值
					 g_DWQ.houlun_R_val 	 = g_screen_houlun_YouZhi;					//后轮右极限					
				
					 AGV_SYS.add_time_yuzhi  = g_add_time;		//计时器
					 AGV_SYS.yuandian_ID 	 = g_yuandi_ID;         //原点ID
					 AGV_SYS.chongdian_ID    = g_chongdian_ID;    //充电ID
					 AGV_SYS.zhongzhuan_ID   = g_zhongzhuan_ID; 	//中转台ID





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
					 SystemParameter[66] = g_zhongzhuan_ID; //中转台坐标
					 
					 osdelay_ms(20);
				}

				W25QXX_Write_16(SystemParameter+50, 50, 17);			//将当前屏幕参数写入到flash中
			}
			break;
			case ChaBiShuJuJieMian:					//24//预留数据调试
			{
				while(HmiScreenSetGet == ChaBiShuJuJieMian)
				{
					//#define XZ_Speed40       	 PLC_Data[46] 		//寻正最大速度
					//#define XZ_Speed41        	 PLC_Data[48] 		//电位器寻正速度比
					//#define XZ_Speed42       	 PLC_Data[49] 		//磁条寻轨速度
					//#define XZ_Speed43       	 PLC_Data[50] 		//电机最大速度


					
					AGV_SYS.XZ_MAX_Speed 		= SystemParameter[40] 		= 	XZ_Speed40;
					AGV_SYS.XZ_DWQ_Speed_bili 	= SystemParameter[41] 		= 	XZ_Speed41;
					AGV_SYS.XZ_CiTiao_Speed 	= SystemParameter[42] 		= 	XZ_Speed42;
					AGV_SYS.Motor_MAX_Speed 	= SystemParameter[43] 		= 	XZ_Speed43;
					

					osdelay_ms(20); 
				}
				W25QXX_Write_16(SystemParameter+40, 40, 4);			//将当前屏幕参数写入到flash中
			}
			break;
			case LeiDaShuJuJieMian:					//25//电池原始数据 
			{
				while(HmiScreenSetGet == LeiDaShuJuJieMian)
				{
					Li_dianya 				=	g_battery.dianya*10;		
					Li_Realy_mah	        =	g_battery.Realy_mah*10;	
					Li_Std_mah 		        =	g_battery.Std_mah*10;		
					Li_XunHuan_time	        =	g_battery.XunHuan_time;
//		
					if(Li_Warning_val_NoBattery < 100)	//低电量报警值
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
			case DianTiTiaoShiJieMian:				//26//辊筒调试界面
			{
				while(HmiScreenSetGet == DianTiTiaoShiJieMian)
				{
					
					
					AGV_SYS.GunT_daozhong_time = GunT_zhong_time;
					
					if(GunT_shanghuo_L == 1) 	//左侧上货
					{
						 g_AGV_speaker_flag.UP_L = 1;
						osdelay_ms(50);
						 GunTong_Trun_L_UP();
					}
					else if(GunT_shanghuo_R == 1) //右侧上货
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
			case XiTongCanShuJieMian:				//8//系统参数界面，速度的档位设置、
			{
				while(HmiScreenSetGet == XiTongCanShuJieMian)
				{
					//30开始				
					AGV_SYS.ID 				 = 		g_AGV_ID; 				//车号	  
					AGV_SYS.yinliang		 = 		g_AGV_speaker_val;     	//系统音量      
					AGV_SYS.Auto_Speed_bili	 = 		g_sys_set_agvSPEED;    	//AGV车速 -- 低中高 
					AGV_SYS.Key_yuyin 		 = 		g_AGV_speaker_key ;	  	//系统语音开关     
					AGV_SYS.Key_RGB_LED 	 = 		g_AGV_LED_car_state ;  	//车身状态灯    
					AGV_SYS.L_speed 		 = 		HmiDiSu ;      			//低速    
					AGV_SYS.M_speed 		 = 		HmiZhongSu;     		//中速    
					AGV_SYS.H_speed 		 = 		HmiGaoSu  ;    			//高速
					AGV_SYS.duijie_speed 	 =		g_AGV_speed_duijie;		//工位对接速度
					AGV_SYS.Key_IR_jin		 =		g_AGV_Enable_IR_jin; 	
					AGV_SYS.Key_IR_yuan      =      g_AGV_Enable_IR_yuan; 	
					AGV_SYS.Key_JiXie_qian   =      g_AGV_Enable_JiXie_qian;
                    AGV_SYS.Key_JiXie_hou    =      g_AGV_Enable_JiXie_hou; 
                    AGV_SYS.yuandian_dir     =      g_AGV_yuandian_dir; 
					
					
					SystemParameter[30]		 = 		g_AGV_ID; 				//车号	  
					SystemParameter[31] 	 = 		g_AGV_speaker_val;     	//系统音量      
					SystemParameter[32] 	 = 		g_sys_set_agvSPEED;    	//AGV车速 -- 低中高 
					SystemParameter[33]	 	 = 		g_AGV_speaker_key ;	  	//系统语音开关     
					SystemParameter[34] 	 = 		g_AGV_LED_car_state ;  	//车身状态灯    
					SystemParameter[35] 	 = 		HmiDiSu ;      			//低速    
					SystemParameter[36] 	 = 		HmiZhongSu;     		//中速    
					SystemParameter[37] 	 = 		HmiGaoSu  ;    			//高速
					SystemParameter[38] 	 = 		g_AGV_speed_duijie;		//工位对接速度
					
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

				W25QXX_Write_16(SystemParameter+30, 30, 9);	//将当前屏幕参数写入到flash中
				W25QXX_Write_16(SystemParameter+80, 80, 5);	//将当前屏幕参数写入到flash中
				Dbus.Init(AGV_SYS.ID);						//把修改的系统ID发送给基站服务器
				yinling(AGV_SYS.yinliang);
			}
			break; 
			//用户界面程序段
			case YongHuShouYeJieMian:				//27//用户首页
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
								sprintf(g_user_luzi,"%d号炉子放舟",temp_user_task%10);		
							}
							else if(temp_user_task/10 == 2)
							{
								sprintf(g_user_luzi,"%d号炉子取舟",temp_user_task%10);		
							}	
							delay_rtos(0,0,1,0);
							//执行用户取放舟操作
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

void Task5_task(void *p_arg)		//执行路径或执行流程 -- 应用层控制任务
{									
	u16 i=0;						
	u16 j=0; 						
	u16 k=0;						
	
	OS_ERR err;						
	p_arg = p_arg;

	while(1)
    {
        if(g_AGV_Sta.Car_Auto2Manu_mode == 0 ) //自动模式并且启动
        {
            //执行路径
            if(HmiTask == 1)							//任务动作 0:无任务 1:执行路径 2:执行流程
            {
				*g_dispatch_message.Task_RunStart = 1;	//开始执行任务
				
                HmiRfidNum = 0; 						//清除当前地标
                HmiStationSerialNum = 0;				//站点序号清0
				
                //根据所选路径，执行相应动作
				if(!AGV_run_path(g_AGV_Sta.type_path,AGV_SYS.ToPLC_task))
				{
					g_AGV_speaker_flag.path = 1;
					delay_rtos(0,0,0,100);
				}
				
				
				//执行完一次任务后清零计数器			
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
				*g_dispatch_message.Task_RunFinish = 1;			//任务执行完毕
				HmiScreenSetGet = YongHuShouYeJieMian;			//跳转到用户界面
				delay_rtos(0,0,1,0);
				
				
				
				if(g_RunSta.mode_chongdian == 3)				//充电去
				{
					*g_dispatch_message.RunState = 3;			//切换到充电模式			
				}
				else if(*g_dispatch_message.RunState == 1)		//运行模式
				{
					*g_dispatch_message.RunState = 2;			//切换到待命模式
					g_AGV_speaker_flag.AGV_readyed = 1;
					delay_rtos(0,0,0,20);
				}

				
				*g_dispatch_message.Task_Recived   = 0;			//收到任务
				
				*g_dispatch_message.Task_RunStart  = 0;			//开始执行任务
				
				if(g_AGV_Sta.flag_addTIME_OK == 3) //真正无任务的超时回原点
				{
					g_AGV_Sta.flag_addTIME_OK= 0;
					g_AGV_Sta.add_time = 0;		
				}
				
            }
			//执行流程
			else if(HmiTask == 2)
			{
				HmiRfidNum = 0;						//清除当前地标
				HmiProcessSerialNum = 0;			//流程序号清0
				
				for(i = 0; i < HmiStepNum; i++)
				{
					HmiProcessSerialNum++;			//流程序号自加
					switch(NowProcessInfor[i][1])
					{
						case 0://单次执行
							//更新路径号
							HmiRouteNum = NowProcessInfor[i][0];
							//获取路径包含站点数
							GetRouteStationNum(HmiRouteNum);
							//获取当前路径信息
							GetRouteData(HmiRouteNum);

							HmiStationSerialNum = 0;
							//根据所选路径，执行相应动作
							for(j = 0; j < HmiStationNum; j++)
							{
								StationAction(j);
							}
							break;
						case 1://顺序执行
							for(k = NowProcessInfor[i][0]; k <= NowProcessInfor[i][2]; k++)
							{
								//更新路径号
								HmiRouteNum = k;
								//获取路径包含站点数
								GetRouteStationNum(HmiRouteNum);
								//获取当前路径信息
								GetRouteData(HmiRouteNum);

								HmiStationSerialNum = 0;
								//根据所选路径，执行相应动作
								for(j = 0; j < HmiStationNum; j++)
								{
									StationAction(j);
								}
							}
							break;
						case 2://倒序执行
							for(k = NowProcessInfor[i][0]; k >= NowProcessInfor[i][2]; k--)
							{
								//更新路径号
								HmiRouteNum = k;
								//获取路径包含站点数
								GetRouteStationNum(HmiRouteNum);
								//获取当前路径信息
								GetRouteData(HmiRouteNum);

								HmiStationSerialNum = 0;
								//根据所选路径，执行相应动作
								for(j = 0; j < HmiStationNum; j++)
								{
									StationAction(j);
								}
							}
							break;
						case 3://循环执行
							//更新路径号
							HmiRouteNum = NowProcessInfor[i][0];
							//获取路径包含站点数
							GetRouteStationNum(HmiRouteNum);
							//获取当前路径信息
							GetRouteData(HmiRouteNum);
							for(k = 0; k < NowProcessInfor[i][2]; k++)
							{
								HmiStationSerialNum = 0;
								//根据所选路径，执行相应动作
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
        OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err); //延时nms
    }	
	
}



void WIFI_task(void *p_arg)			//语音
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
	PrintCom(YIN_SU5,9);osdelay_ms(10);		//语速5
	PrintCom(YIN_DIAO5,9);osdelay_ms(10);	//语调5		
	BEEP = 0;
	
	while(1)
	{
		speak_once("路径错误",1000,&g_AGV_speaker_flag.path);
		speak_once("辊筒右转",1000,&g_AGV_speaker_flag.GunT_R);
		speak_once("辊筒[=tong3]左[=zuo2]转",1000,&g_AGV_speaker_flag.GunT_L);

		
		speak_once("前进方向",1000,&g_AGV_speaker_flag.dir_Go);
		speak_once("后退方向",1000,&g_AGV_speaker_flag.dir_Back);
		speak_once("左分叉",800,&g_AGV_speaker_flag.FenCha_L);
		speak_once("右分叉",800,&g_AGV_speaker_flag.FenCha_R);
		
		speak_once("流程执行完毕",1500,&g_AGV_speaker_flag.LiuCheng_ok);
		speak_once("路径执行完毕",1500,&g_AGV_speaker_flag.LuJing_ok);
		
		speak_once("驱动使能",1000,&g_AGV_speaker_flag.Motec_enable);
		speak_once("驱动断电",1000,&g_AGV_speaker_flag.Motec_off);
		speak_once("驱动未[=wei4]上电",1000,&g_AGV_speaker_flag.Motec_NoPowerUp);
		
		
		speak_once("左侧卸货",1000,&g_AGV_speaker_flag.Down_L);
		speak_once("左侧装货",1000,&g_AGV_speaker_flag.UP_L);
		speak_once("右侧卸货",1000,&g_AGV_speaker_flag.Down_R);
		speak_once("右侧装货",1000,&g_AGV_speaker_flag.UP_R);	

		speak_once("机械避障",1000,&g_AGV_speaker_flag.JiXie);
		speak_once("红外避障",1000,&g_AGV_speaker_flag.IR);	
		
		speak_once("前一",500,&g_AGV_speaker_flag.DOWN_gui_qian1);
		speak_once("前二未上轨",500,&g_AGV_speaker_flag.DOWN_gui_qian2);
		speak_once("后一",500,&g_AGV_speaker_flag.DOWN_gui_hou1);
		speak_once("后二",500,&g_AGV_speaker_flag.DOWN_gui_hou2);	

		speak_once("地标读取出错",1000,&g_AGV_speaker_flag.RFID_READ_err);
		
		//用户界面的操作语音
		speak_once(g_user_luzi,1000,&g_AGV_speaker_flag.user_luzi);				//用户炉子操作

		speak_once("准备去充电",1500,&g_AGV_speaker_flag.chongdian_goto);			//去充电
		speak_once("充电完毕回原点",1800,&g_AGV_speaker_flag.chongdian_over);	//充电完毕
		speak_once("诶[=ei1]鸡喂[=wei1]就绪",1500,&g_AGV_speaker_flag.AGV_readyed);				//AGV就绪
		
		
		speak_once("启动",500,&g_AGV_speaker_flag.start);
		speak_once("软起",500,&g_AGV_speaker_flag.Ruan_Qi);
		speak_once("辊筒停止",1000,&g_AGV_speaker_flag.GunT_stop);		
		speak_once("停止",500,&g_AGV_speaker_flag.stop);	

		speak_once("自动",500,&g_AGV_speaker_flag.Auto);
		speak_once("手动",500,&g_AGV_speaker_flag.Manu);		

		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err);
	}
}

void guntong_task(void *p_arg)		//手动控制滚筒
{
	OS_ERR err;
	p_arg = p_arg;

	while(1)
	{
		SD_GunTong();

		OSTimeDlyHMSM(0,0,0,20,OS_OPT_TIME_HMSM_STRICT,&err);
	}
}


void DCv_task(void *p_arg)			//电压采集
{
	u16 temp_i=0;
	u16 temp_j=0;
	u16 temp_k=0;
	u16 temp_p=0;
	u16 temp_m=0;
	
	OS_ERR err;
	p_arg = p_arg;
	
	GET_Battery();	//获取电池信息
	
	while(1)
	{		
		temp_k++;

		if(temp_k > 500)							//每1s获取电池信息
		{
			GET_Battery();					

			temp_k = 0;				
		}			
		//低电量报警
		if(Sys_battery <= Battery_Warining.Warining_Val_NoBattery)		
		{
			g_Warning.Low_battery = 1;
			sprintf(g_warning,"电量少于百分之%d,请及时充电",Battery_Warining.Warining_Val_NoBattery);		
			
			temp_p++;
			if(temp_p > 500)				//每5s语音警报一次
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

		//读到地标响蜂鸣器							//叫250ms
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


		//触摸屏通信指示灯和板子运行指示灯LED1		//500ms闪烁
		temp_i++;
		if(temp_i == 50)
		{
			LED1 = 0;
			P_RUN_LED = 1;							//屏幕运行指示灯
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


void openbox_task(void *p_arg)		//Dbus基站通讯
{
	u8 temp_i=0;
	p_arg = p_arg;
	
	delay_rtos(0,0,2,0);			//等待通信模块初始化
	//Heart(1);
	while(1)	
	{
		temp_i++;
        //收到结束符触发解包函 
        Dbus.OpenBox();
		if(temp_i > 100)		//1秒心跳
		{
			Dbus.Heart(0);
			temp_i = 0;
		}
		delay_ms(10);
	}
}

void heartbeat_task(void *p_arg)	//磁条寻正任务
{
	p_arg = p_arg;

	while(1)
	{
		if(g_CtXunZheng.XunZ_Start)	//启动磁条寻正
		{
			check_CtXunZ_OK(AGV_SYS.XZ_CiTiao_Speed);		//g_Start_flag.Start_Auto_PID在这里置一;						
			g_CtXunZheng.XunZ_Start = 0;					//寻正结束
		}

		delay_rtos(0,0,0,20);			
	}
}

void Task17_task(void *p_arg)		//磁导航计数
{
	p_arg = p_arg;
	
	while(1)
	{
		if(!g_AGV_Sta.Car_Auto2Manu_mode) //自动模式下才检测突变
		{
			CDH_ADD(g_LastCDH_buff,g_u16_val,g_CDH_add_num);		
		}
		delay_rtos(0,0,0,5);
	}
}

void Task18_task(void *p_arg)		//前驱动磁导航分叉
{
	u8 temp_j_L=0;
	u8 temp_j_R=0;
	p_arg = p_arg;
	
	while(1)
	{
		if(g_AGV_Sta.Car_fencha_Start_qian )
		{
			if(!g_AGV_Sta.Car_dir)	//前进方向
			{
				temp_j_L = 11;
				temp_j_R = 12;
			}
			else	//后退方向
			{
				temp_j_L = 12;
				temp_j_R = 11;				
			}	
			
			if(NowRouteInfor[g_AGV_Sta.fencha_RFID_qian][16] && g_CDH_add_num[1] == NowRouteInfor[g_AGV_Sta.fencha_RFID_qian][17])	//1触发
			{
				switch(NowRouteInfor[g_AGV_Sta.fencha_RFID_qian][2])//分叉判断
				{
					case 0:
						break;//保持上次信息
					case 1://左分叉
					{
						g_AGV_Sta.Car_fencha_dir = temp_j_L;
					}
					break;
					case 2://右分叉
					{
						g_AGV_Sta.Car_fencha_dir = temp_j_R;
					}
					break;
					case 3://直行
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
void Task19_task(void *p_arg)		//后驱动磁导航分叉
{
	u8 temp_j_L=0;
	u8 temp_j_R=0;
	p_arg = p_arg;
	
	while(1)
	{
		if(g_AGV_Sta.Car_fencha_Start_hou)
		{
			if(!g_AGV_Sta.Car_dir)	//前进方向
			{
				temp_j_L = 21;
				temp_j_R = 22;
			}
			else	//后退方向
			{
				temp_j_L = 22;
				temp_j_R = 21;				
			}		
			
			if(NowRouteInfor[g_AGV_Sta.fencha_RFID_hou][16] && g_CDH_add_num[3] == NowRouteInfor[g_AGV_Sta.fencha_RFID_hou][17])	//1触发
			{
				switch(NowRouteInfor[g_AGV_Sta.fencha_RFID_hou][2])//分叉判断
				{
					case 0:
						break;//保持上次信息
					case 1://左分叉
					{
						g_AGV_Sta.Car_fencha_dir = temp_j_L;
					}
					break;
					case 2://右分叉
					{
						g_AGV_Sta.Car_fencha_dir = temp_j_R;
					}
					break;
					case 3://直行
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

void Task20_task(void *p_arg)		//上位机通信
{
	u16 temp_val=0;
	
	g_user_readyed = 0;				//默认就绪状态0:未就绪 1:就绪,手动或者去充电会切换到非就绪状态
	p_arg = p_arg;
	
	
	while(1)
	{
		if(!User2Auto_mode)						//0:MES调度模式
		{
			if(*g_dispatch_message.RunState == 0)			//未就绪模式:0
			{
				if(g_AGV_Sta.flag_set_yuandian)
				{
					g_AGV_Sta.flag_set_yuandian = 0;
				}
				
				//报警没有异常且屏幕手动确认到原点才可以切到待命状态
				if(g_user_readyed)
				{
					if(!User2Auto_mode)						//0:用户自动模式
					{
						//清出轨跟地标出错标志
						g_Warning.chugui   = 0;	
						g_Warning.RFID_err = 0;
						g_AGV_Sta.juedui_RFID = AGV_SYS.yuandian_ID;
						g_AGV_Sta.RFID_buff[0] = 0;
						g_AGV_Sta.RFID_buff[1] = 0;
					
						if(g_Warning.Low_battery)
						{
							temp_val = *g_dispatch_message.Warning & (~(1<<4));	//清0低电量位					
						}
						else
						{
							temp_val = *g_dispatch_message.Warning;	
						}
						
						if(!temp_val)	//报警非0进入
						{
							//给定起点坐标
							g_AGV_Sta.flag_set_yuandian	= 1;
							*g_dispatch_message.RunState = 2;	
							g_AGV_speaker_flag.AGV_readyed = 1;
							delay_rtos(0,0,0,20);
	
						}					
					
					}	
				}


				
			}
			else if(*g_dispatch_message.RunState == 1)			//运行模式:1
			{
				//未上轨,仅报警
				//运行模式下,出轨及地标读取出错,报警并切换到未就绪
				if(g_Warning.chugui || g_Warning.RFID_err)
				{
					Ting_Zhi();	
					*g_dispatch_message.RunState = 0;			//切换到未就绪状态
				
				}	
			}		
			else if(*g_dispatch_message.RunState == 2)		//待命模式:2
			{
				if(g_Warning.Low_battery)
				{		
					//未就绪0,运行1，待命2，充电3
					*g_dispatch_message.Task_RunFinish = 0;				//清除任务完成标志
					*g_dispatch_message.RunState = 3;	
	
					Get_PC_data(1,&AGV_SYS.chongdian_ID); 				//
				}
				else if(*g_dispatch_message.Task_ID && *g_dispatch_message.guan_ID)		//接收到上位机任务
				{		
					*g_dispatch_message.Task_RunFinish = 0;				//清除任务完成标志
					
					AGV_SYS.ToPLC_task = *g_dispatch_message.Task_ID;	//缓存任务
					AGV_SYS.guan_ID  = *g_dispatch_message.guan_ID;	//缓存炉管号									

					*g_dispatch_message.Task_Recived   = 1;				//收到任务
					*g_dispatch_message.RunState = 1;		
					g_AGV_Sta.flag_addTIME_OK = 3;					
					Get_PC_data(0,&AGV_SYS.ToPLC_task); 			//接收上位机路径信息并执行
				}				
				else if(g_AGV_Sta.flag_addTIME_OK == 1)
				{
					*g_dispatch_message.Task_RunFinish = 0;				//清除任务完成标志
					*g_dispatch_message.RunState = 1;						
					
					g_AGV_Sta.flag_addTIME_OK = 2;
					Get_PC_data(1,&AGV_SYS.yuandian_ID);//执行回原点动作
				
				
				}				
	
				
	
										
				

			}
			else if(*g_dispatch_message.RunState == 3)		//充电模式:3 -->就绪模式:0
			{
				
					g_AGV_speaker_flag.chongdian_goto = 1;				//加个充电的语音
					delay_rtos(0,0,2,0);
				
				
				#if 0
				if(*g_dispatch_message.Task_RunFinish)					//任务执行完毕
				{				
					if(g_user_chongdian) //回原点
					{
						
						g_AGV_Sta.juedui_RFID = AGV_SYS.chongdian_ID;
						g_AGV_speaker_flag.chongdian_over = 1;
						delay_rtos(0,0,0,20);
						g_RunSta.chongdian = 0;
						SystemParameter[5] = g_RunSta.chongdian;			//充电模式
						SetOneParameterToSystem(SystemParameter[5], 5);		//存入flash		
						g_RunSta.mode_chongdian = 4;						//3:充电路径 4:充电返回路径
						Get_PC_data(1,&AGV_SYS.yuandian_ID); 				//接收上位机路径信息并执行		//后面改为手动返回
						
					}				
				}	
				#endif				
			}			
		}
		else									//1:人工模式
		{	

		    *g_dispatch_message.RunState = 0;	//切换到调度模式的未就绪
						
			if(g_user_readyed)
			{
				//给定起点坐标
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


void Task21_task(void *p_arg)		//AGV给上位机发送数据任务
{
	u8 temo_j=0;
	u8 temp_k=0;
	p_arg = p_arg;

	delay_rtos(0,0,2,0);			//等待通信模块初始化
	while(1)
	{
		//定时发
		temo_j++;
		if(temo_j>50)					//每1秒发送一次SDO
		{
			temp_k++;					//给PLC的心跳信号1-60,每秒加一
			if(temp_k>60)
			{
				temp_k = 1;
			}
			*g_PLC_message[0].AGV2PLC_Heard = temp_k;	//扩散炉心跳
			*g_PLC_message[1].AGV2PLC_Heard = temp_k;	//PE炉心跳
					
			CompareVal_Send( 2, 9);		//AGV_CanOpen_Send -> Sever
			CompareVal_Send(20,25);		//AGV_CanOpen_Send -> PLC(扩散炉)	
			CompareVal_Send(31,36);		//AGV_CanOpen_Send -> PLC(PE炉)	
			
			Get_PDO_Data();				//获取AGV信息
			Post_Multiple_Registers(0,51,16,g_RT_message.BatteryLevel);	
			
			temo_j = 0;			
		}

		delay_rtos(0,0,0,20);
	}
}

void Task22_task(void *p_arg)		//AGV行车灯
{
	p_arg = p_arg;
	
	while(1)
	{
		AGV_LED();
		
		delay_rtos(0,0,0,10);
	}
	
}


void Task23_task(void *p_arg)		//远距离红外自动加减速
{
	u16 temp_speedd=0;
	u8 temp_dir=0;
	p_arg = p_arg;
	
	while(1)
	{	
		#if 0
		if(g_Start_flag.Start_Auto_PID && g_AGV_Sta.Car_Auto2Manu_mode == 0)	//自动模式
		{
			AGV_Auto_speed(&AGV_SYS.autu_speed_my,&AGV_SYS.Car_Auto_Speed,g_AGV_Sta.Car_dir);
		}
		#endif
		if(g_Start_flag.Start_Manu_PID && g_AGV_Sta.Car_Auto2Manu_mode == 1)	//手动模式
		{
														
			temp_dir = g_AGV_yaokong.SD_ir - 1;									//手动方向 前进:1 后退:2
			AGV_Manu_speed(AGV_SYS.Manu_speed_my,&g_AGV_yaokong.SD_Speed,temp_dir);
		}		
		
		delay_rtos(0,0,0,10);
	}
}
void Task24_task(void *p_arg)		//计时器:客户自定义超时无任务回原点
{
	p_arg = p_arg;
	
	while(1)
	{	
		
		if(*g_dispatch_message.RunState == 2) //AGV待命模式下才会执行
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










