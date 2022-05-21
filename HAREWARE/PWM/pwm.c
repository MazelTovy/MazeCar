#include "pwm.h"


//arr：自动重装值
//psc：时钟预分频数

void TIM2_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);// 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);  //使能GPIO外设时钟使能，开启完全复用功能到PB10.11
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2,ENABLE);//很重要，很关键，很要命。
                                                       	
   //设置该引脚为复用输出功能,输出TIM2_CH3的PWM脉冲波形
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //管脚对应完全复用功能为TIM2_CH3(定时器二的通道三)
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB10
	
	 //设置该引脚为复用输出功能,输出TIM2_CH4的PWM脉冲波形
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //TIM2_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB11

	TIM_TimeBaseStructure.TIM_Period = arr;//; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc;//设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的相应模式配置

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse =0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化TIM2_CH3


  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse =0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高 
	TIM_OC4Init(TIM2, &TIM_OCInitStructure); //根据TIM_OCInitStruct中指定的参数初始化TIM2_CH4

	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);  //CH3预装载使能	 
	
	
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);  //CH4预装载使能	 

	TIM_ARRPreloadConfig(TIM2, ENABLE); //使能TIM2在ARR上的预装载寄存器
		
  TIM_Cmd(TIM2, ENABLE);  //开启TIM2时钟

}//初始化控制轮子运动状态的pwm输出引脚



