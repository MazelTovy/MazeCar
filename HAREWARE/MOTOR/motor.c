#include "motor.h"
#include "stm32f10x.h" 
#include "stm32f10x_rcc.h"
#include "delay.h"
#define AABB 400

//void Motor_12_Config(void)
//	{
//		
//	  GPIO_InitTypeDef GPIO_InitStructure;  
//    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE);
//		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3; 
//	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
//	  GPIO_Init(GPIOC, &GPIO_InitStructure);
//		GPIO_ResetBits(GPIOC,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3); 
// }

void Motor_12_Config1(void)//拉低E13 E15电平
{ 
		
  GPIO_InitTypeDef GPIO_InitStructure2;  
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE, ENABLE);
	GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_15; 
  GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure2.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOE, &GPIO_InitStructure2);
	GPIO_ResetBits(GPIOE,GPIO_Pin_13|GPIO_Pin_15); 
}

void Motor_1_STOP(void)//电机1停止
{
//	GPIO_ResetBits(GPIOC,GPIO_Pin_0);
//	GPIO_ResetBits(GPIOC,GPIO_Pin_1);
	GPIO_ResetBits(GPIOB,GPIO_Pin_11);
	GPIO_ResetBits(GPIOE,GPIO_Pin_13);
}

void Motor_1_PRun(void)//电机1正转
{
//	GPIO_SetBits(GPIOC,GPIO_Pin_0);
//	GPIO_ResetBits(GPIOC,GPIO_Pin_1);
	GPIO_SetBits(GPIOB,GPIO_Pin_11);
	GPIO_ResetBits(GPIOE,GPIO_Pin_13);
}

void Motor_1_NRun(void)//电机1反转
{
//	GPIO_SetBits(GPIOC,GPIO_Pin_1);
//	GPIO_ResetBits(GPIOC,GPIO_Pin_0);
	GPIO_SetBits(GPIOE,GPIO_Pin_13);
	GPIO_ResetBits(GPIOB,GPIO_Pin_11);
}

void Motor_2_STOP(void)//电机2停止
{
//	GPIO_ResetBits(GPIOC,GPIO_Pin_2);
//	GPIO_ResetBits(GPIOC,GPIO_Pin_3);
	GPIO_ResetBits(GPIOB,GPIO_Pin_10);
	GPIO_ResetBits(GPIOE,GPIO_Pin_15);
}

void Motor_2_PRun(void)//电机2正转
{
//	GPIO_SetBits(GPIOC,GPIO_Pin_2);
//	GPIO_ResetBits(GPIOC,GPIO_Pin_3);
	GPIO_SetBits(GPIOB,GPIO_Pin_10);
	GPIO_ResetBits(GPIOE,GPIO_Pin_15);
}

void Motor_2_NRun(void)//电机反转
{
//	GPIO_SetBits(GPIOC,GPIO_Pin_3);
//	GPIO_ResetBits(GPIOC,GPIO_Pin_2);
	GPIO_SetBits(GPIOE,GPIO_Pin_15);
	GPIO_ResetBits(GPIOB,GPIO_Pin_10);
}

void STOP(void)
{
		Motor_1_PRun();
		Motor_2_PRun();
		TIM_SetCompare3(TIM2,0);
		TIM_SetCompare4(TIM2,0);
}


void GO(void)
{
		Motor_1_PRun();
		Motor_2_PRun();	
		TIM_SetCompare3(TIM2,AABB);
		TIM_SetCompare4(TIM2,AABB);
}


void BACK(void)
{
		
		Motor_1_NRun();
		Motor_2_NRun();
		TIM_SetCompare3(TIM2,AABB);
		TIM_SetCompare4(TIM2,AABB);
}

void RIGHT(void)
{
		Motor_1_PRun();
		Motor_2_PRun();
		TIM_SetCompare3(TIM2,334);
		TIM_SetCompare4(TIM2,300);
}


void LEFT(void)
{
		Motor_1_PRun();
		Motor_2_PRun();
		TIM_SetCompare4(TIM2,300);
		TIM_SetCompare3(TIM2,297);
}


void SHARPRIGHT(void)
{
		Motor_1_PRun();
		Motor_2_PRun();
		TIM_SetCompare3(TIM2,0);
		TIM_SetCompare4(TIM2,AABB);
}


void SHARPLEFT(void)
{
		Motor_1_PRun();
		Motor_2_PRun();
		TIM_SetCompare4(TIM2,0);
		TIM_SetCompare3(TIM2,AABB);
}

void RIGHTBACK(void)
{
		Motor_2_PRun();
		Motor_1_NRun();
		TIM_SetCompare3(TIM2,AABB);
		TIM_SetCompare4(TIM2,AABB);
}


void LEFTBACK(void)
{
		Motor_2_NRun();
		Motor_1_PRun();
		TIM_SetCompare4(TIM2,AABB);
		TIM_SetCompare3(TIM2,AABB);
}

void ROTATELEFT(void)
{
		Motor_1_PRun();
		TIM_SetCompare3(TIM2,800);
		TIM_SetCompare4(TIM2,0);
}

void ROTATERIGHT(void)
{
		Motor_2_PRun();
		TIM_SetCompare3(TIM2,0);
		TIM_SetCompare4(TIM2,AABB);
}


