#include "length.h"
#include "sys.h"

#include "delay.h"







void TIM5_Init(u16 arr,u16 psc)
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
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM5中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器



  TIM_ClearFlag(TIM5, TIM_FLAG_Update);


}










u32 Distance_Calculate1(u32 count)
{
    u32 distance1 = 0;
    distance1 = (u32)(((float)count / 58) * 100);
    return distance1;
}

//距离运算







void Ultrasonic_Config2(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//Trig
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//Echo
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;

    GPIO_Init(GPIOA, &GPIO_InitStructure);
}





float Senor_Using1(void)
{
  u32 count1 = 0;
  u32 Distance1 = 0;
	delay_init();
	Ultrasonic_Config2();
	TIM5_Init(49999,71);
	
	 
    
        GPIO_ResetBits(GPIOA, GPIO_Pin_0);//预先拉低Trig引脚
        GPIO_SetBits(GPIOA, GPIO_Pin_0);
        delay_us(10);
        GPIO_ResetBits(GPIOA, GPIO_Pin_0);//发出10us的脉冲
        TIM5->CNT = 0;
        while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0);
        TIM_Cmd(TIM5, ENABLE);
        while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 1);
        TIM_Cmd(TIM5, DISABLE);
        count1 = TIM5->CNT;
        Distance1 = Distance_Calculate1(count1);
Distance1=Distance1/100;
	    return Distance1;
}











