#ifndef __ENCODER_H
#define __ENCODER_H
#include "sys.h"


void Encoder_Init_L(void);

void Encoder_Init_R(void);

void TIM2_IRQHandler(void);

void TIM4_IRQHandler(void);

void readEncoder(void);


#endif
