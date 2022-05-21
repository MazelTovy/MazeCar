#include "Encoder.h"

short Encoder_Left,Encoder_Right;
/**************************************************************************
函数功能：右编码器初始化
**************************************************************************/

void Encoder_Init_R(void)
{
 TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
 TIM_ICInitTypeDef TIM_ICInitStructure;
 GPIO_InitTypeDef GPIO_InitStructure;

 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//TIM3时钟使能
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能PORTB时钟
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 |GPIO_Pin_5;//PB4,PB5
 GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IN_FLOATING;//浮空输入
 GPIO_Init(GPIOB, &GPIO_InitStructure);
 
 
 TIM_DeInit(TIM3);//重新将Timer寄存器设置为缺省值 
 TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);//把TIM_TimeBaseInitStruct 中的每一个参数按缺省值填入
 
 TIM_TimeBaseStructure.TIM_Prescaler = 0x0;    // 不分频
 TIM_TimeBaseStructure.TIM_Period =0xFFFF; 
 TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1;//选择时钟分频：不分频
 TIM_TimeBaseStructure.TIM_CounterMode =TIM_CounterMode_Up; //向上计数模式 
                                                            //(当配置为中央对齐模式或者编码器模式时，此位只读)
  TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
 
 TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,
 TIM_ICPolarity_BothEdge, TIM_ICPolarity_BothEdge);//TI1和TI2的输入均在上升沿和下降沿有效
											//选择模式 ：两相计数（速度和方向）
 TIM_ICStructInit(&TIM_ICInitStructure); // 把TIM_ICInitStruct 中的每一个参数按缺省值填入
 TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;//选择通道1
 TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;////映射到 TI1 上
 TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;//不分频
 TIM_ICInitStructure.TIM_ICFilter = 0x03;//0011 对应8个事件输出一个跳变
 
 TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;//选择通道2
 TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;//映射到 TI2 上
 TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;//不分频
 TIM_ICInitStructure.TIM_ICFilter = 0x03;//0011 对应8个事件输出一个跳变
 
 TIM_ICInit(TIM3,&TIM_ICInitStructure);
 
 TIM_SetCounter(TIM3,0);  
 
 TIM_Cmd(TIM3, ENABLE); 
 
 }
 /**************************************************************************
函数功能：左编码器初始化
**************************************************************************/
void Encoder_Init_L(void)
{
 TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
 TIM_ICInitTypeDef TIM_ICInitStructure;
 GPIO_InitTypeDef GPIO_InitStructure;

	
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);//TIM2时钟使能
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能PORTA时钟

 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 |GPIO_Pin_9;//PB8,PB9
 GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IN_FLOATING;//浮空输入
 GPIO_Init(GPIOB, &GPIO_InitStructure);
 
 
 
 TIM_DeInit(TIM4);//重新将Timer设置为缺省值 
 TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
 
 TIM_TimeBaseStructure.TIM_Prescaler = 0x0;  // 不分频
 
 TIM_TimeBaseStructure.TIM_Period =0xFFFF; 
 TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1;//选择时钟分频：不分频
 TIM_TimeBaseStructure.TIM_CounterMode =TIM_CounterMode_Up; //向上计数模式 
                                                        //(当配置为中央对齐模式或者编码器模式时，此位只读)
 TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
 
 TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,
 TIM_ICPolarity_BothEdge, TIM_ICPolarity_BothEdge);//TI1和TI2的输入均在上升沿和下降沿有效
											//选择模式 ：两相计数（速度和方向）
 TIM_ICStructInit(&TIM_ICInitStructure); 
 TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;//选择通道3
 TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
 TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
 TIM_ICInitStructure.TIM_ICFilter = 0x03;//0011 对应8个事件输出一个跳变
 
 TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;//选择通道4
 TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;//映射到 TI2 上
 TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
 TIM_ICInitStructure.TIM_ICFilter = 0x03;
 
 TIM_ICInit(TIM4,&TIM_ICInitStructure);
 
 TIM_SetCounter(TIM4,0); 
 TIM_Cmd(TIM4, ENABLE); 
 
 } 

uint16_t Encoder_L,Encoder_R; 
/**************************************************************************
函数功能：读取编码器的数据并进行数据类型转换
**************************************************************************/
void readEncoder(void)
{    
	
	      //===左右编码器的脉冲计数
		Encoder_R = TIM_GetCounter(TIM3);       //===获取正交解码1数据	
	  TIM_SetCounter(TIM3,0);                 //===计数器清零  
	  Encoder_L= TIM_GetCounter(TIM4);        //===获取正交解码2数据	
	  TIM_SetCounter(TIM4,0);              //===计数器清零 
		Encoder_Left=(short) Encoder_L;
	  Encoder_Right=(short)Encoder_R;
	  Encoder_Left=-Encoder_Left;//这里取反是因为，平衡小车的两个电机是旋转了180度安装的，为了保证前进后退时候的编码器数据符号一致
}
