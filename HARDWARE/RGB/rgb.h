#ifndef _RGB_H
#define _RGB_H

#include "my_include.h"

//PD4  -- ǰ���� --       (2���Ƶ��źŲ���һ��)
//PD3  -- �󳵵� -- 	  (2���Ƶ��źŲ���һ��)

//PB10 -- ��ɫ -- ����    (2���Ƶ��źŲ���һ��)
//PB0  -- ��ɫ -- �л�	  (2���Ƶ��źŲ���һ��)


#define  Car_LED_Blue 	 PBout(10)   //�ߵ�ƽ����
#define  Car_LED_Yellow	 PBout(0)    //�ߵ�ƽ����

#define  Car_LED_Qian_Enable PDout(4)   //�͵�ƽ����
#define  Car_LED_Hou_Enable	 PDout(3)   //�͵�ƽ����





void rgb_init(void);










#endif

