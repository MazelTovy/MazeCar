#ifndef __MOTOR1_H
#define __MOTOR1_H

#include"stm32f10x.h"
#include"stm32f10x_gpio.h"



void Motor_12_Config1(void);

void Motor_1_STOP(void);

void Motor_1_PRun(void);

void Motor_1_NRun(void);

void Motor_2_STOP(void);

void Motor_2_PRun(void);

void Motor_2_NRun(void);

void GO(void);

void BACK(void);

void LEFT(void);

void RIGHT(void);

void SHARPLEFT(void);

void SHARPRIGHT(void);

void LEFTBACK(void);

void RIGHTBACK(void);

void STOP(void);

void ROTATERIGHT(void);

void ROTATELEFT(void);


#endif
