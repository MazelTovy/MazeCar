#include "lengt.h"
#include "delay.h"







void TIM3_Init(u16 arr,u16 psc)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef tim5;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	
  
	tim5.TIM_ClockDivision=TIM_CKD_DIV1;//输入捕获
	tim5.TIM_CounterMode =TIM_CounterMode_Up;//计数模式
	tim5.TIM_Period =arr;//预分频系数
	tim5.TIM_Prescaler =psc;//自动重装载值

	TIM_TimeBaseInit(TIM5,&tim5);

	
//别忘了中断优先级分组
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器



  TIM_ClearFlag(TIM5, TIM_FLAG_Update);


}









void Ultrasonic_Config1(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;//Trig
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//Echo
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;

    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

//GPIO口设定



u32 Distance_Calculate(u32 count)
{
    u32 distance = 0;
    distance = (u32)(((float)count / 58) * 100);
    return distance;
}

//距离运算


float Senor_Using(void)
{
  u32 count = 0;
  u32 Distance = 0;
	delay_init();
	Ultrasonic_Config1();

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	TIM3_Init(49998,72);
	
	 
    
        GPIO_ResetBits(GPIOA, GPIO_Pin_6);//预先拉低Trig引脚
        GPIO_SetBits(GPIOA, GPIO_Pin_6);
        delay_us(10);
        GPIO_ResetBits(GPIOA, GPIO_Pin_6);//发出10us的脉冲
        TIM5->CNT = 0;
        while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7) == 0);
        TIM_Cmd(TIM5, ENABLE);
        while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7) == 1);
        TIM_Cmd(TIM5, DISABLE);
        count = TIM5->CNT;
        Distance = Distance_Calculate(count);
				Distance=Distance/100;
	    return Distance;


}

