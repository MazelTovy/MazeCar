#ifndef __LED_H
#define __LED_H

#include"stm32f10x.h"
#include"stm32f10x_gpio.h"


#define LED0 PBout(5)// PB5
#define LED1 PEout(5)// PE5	

#define BEEP PBout(8)	// BEEP,�������ӿ�		   

void BEEP_Init(void);	//��ʼ��

void LED_Init(void);//��ʼ��

		 				    
#endif
