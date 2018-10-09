/*
	******************************************************************************
  * @file    dbus.cpp
  * @author  ������
  * @version V1.2
  * @date    2018/02/01
  * @brief   �ֲ�ʽͨ��ϵͳ
  ******************************************************************************
  * @attention
  * �ֲ�ʽͨ��ϵͳ��������ƣ��豸��������ʣ���ֲֻ��Ҫ�ṩһ���������ݷ�������
  * �Ұ��յ�����д��ϵͳ�ṩ�Ľӿں������ɣ����������κ�Ӳ��
  * 
  * 
	*
  * 
  ******************************************************************************
*/



	#ifndef __DBUS_H
	#define	__DBUS_H
		
	#define u8  unsigned char
	#define u16 unsigned short

	/*--- �û����� ---------------------------------------------------------------*/
	//��д�Ĵ�������
	#define DBUS_REGISTER_LENGTH 128
	//��֡����֡��󳤶�
	#define DBUS_MAX_LENGTH 1024
	//���ݽ��ջ���س���
	#define DBUS_MAX_RECIVE_BUF 2048
	//��Ӧ��Ϣ���л���س���
	#define DBUS_MAX_RESPONSE_BUF 10
	//��ʱʱ��(��λ:10ms)
	#define DBUS_TIMEOUT 100
	//�ط�����
	#define DBUS_MAX_REPEAT_NUM 1


    
    
    /*****************Public*****************/
    /*****************Private*****************/
	//��ʼ��
	void Init(u16 Address);
	void Heart(u16 TargetAddress);
	//��������
	void InPut(char c);
	//�������
	void OpenBox(void);
	//��������
	void Analyze(char *buf ,u16 len);
	//��������ж�
    void OutPut_interrupt(void (*callback_fun)(char*,u16));
	//��ʱ�ж�
	void Delay_interrupt(void (*callback_delay)(void));
	//��������
	void Heart(u16 TargetAddress);
	//д�����Ĵ���
	u8 Write_Register(u16 TargetAddress,u16 RegisterAddress,u16 Data);
	//д����Ĵ���
	u8 Write_Multiple_Registers(u16 TargetAddress,u16 RegisterAddress,u16 Num,u16* Data);	
	//�������Ĵ���
	struct _ReturnMsg Read_Register(u16 TargetAddress,u16 RegisterAddress);
	//������Ĵ���
	struct _ReturnMsg Read_Multiple_Registers(u16 TargetAddress,u16 RegisterAddress,u16 Num);	
    
	//д�����Ĵ���
	void Post_Register(u16 TargetAddress,u16 RegisterAddress,u16 Data);
	//д����Ĵ���
	void Post_Multiple_Registers(u16 TargetAddress,u16 RegisterAddress,u16 Num,u16* Data);	
    
	
	//��Ӧ�������Ĵ���
	void Response_Read_Register(char *buf);
	//��Ӧд�����Ĵ���
	void Response_Write_Register(char *buf);
	//��Ӧ������Ĵ���
	void Response_Read_Multiple_Registers(char *buf);
	//��Ӧд����Ĵ���
	void Response_Write_Multiple_Registers(char *buf);
  

	//��Ӧд�����Ĵ���
	void Response_Post_Register(char *buf);
	//��Ӧд����Ĵ���
	void Response_Post_Multiple_Registers(char *buf);

//    extern struct _ReturnMsg ReturnMsg;
    struct _ReturnMsg
    {
        u8 resault;
        u16 Data;
        u16* DataBuf;
    };
    
    struct _Dbus
    {
        //����
        u16 Register[DBUS_REGISTER_LENGTH];
        struct _ReturnMsg ReturnMsg;
        //����
        void (*Init)(u16 Address);
        void (*InPut)(char c);
        void (*OpenBox)(void);
        void (*OutPut_interrupt)(void (*callback_fun)(char*,u16));
        void (*Delay_interrupt)(void (*callback_delay)(void));
        
        void (*Heart)(u16 TargetAddress);
        u8 (*Write_Register)(u16 TargetAddress,u16 RegisterAddress,u16 Data);
        u8 (*Write_Multiple_Registers)(u16 TargetAddress,u16 RegisterAddress,u16 Num,u16* Data);
        struct _ReturnMsg (*Read_Register)(u16 TargetAddress,u16 RegisterAddress);
        struct _ReturnMsg (*Read_Multiple_Registers)(u16 TargetAddress,u16 RegisterAddress,u16 Num);

        //ʵʱ֡������Ӧ��
        void (*Post_Register)(u16 TargetAddress,u16 RegisterAddress,u16 Data);
        void (*Post_Multiple_Registers)(u16 TargetAddress,u16 RegisterAddress,u16 Num,u16* Data);
    };
    extern struct _Dbus Dbus;
#endif
