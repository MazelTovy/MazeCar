#include "pwm.h"


//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��

void TIM2_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);// 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);  //ʹ��GPIO����ʱ��ʹ�ܣ�������ȫ���ù��ܵ�PB10.11
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2,ENABLE);//����Ҫ���ܹؼ�����Ҫ����
                                                       	
   //���ø�����Ϊ�����������,���TIM2_CH3��PWM���岨��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //�ܽŶ�Ӧ��ȫ���ù���ΪTIM2_CH3(��ʱ������ͨ����)
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB10
	
	 //���ø�����Ϊ�����������,���TIM2_CH4��PWM���岨��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //TIM2_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB11

	TIM_TimeBaseStructure.TIM_Period = arr;//; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc;//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx����Ӧģʽ����

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse =0; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ��TIM2_CH3


  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse =0; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը� 
	TIM_OC4Init(TIM2, &TIM_OCInitStructure); //����TIM_OCInitStruct��ָ���Ĳ�����ʼ��TIM2_CH4

	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);  //CH3Ԥװ��ʹ��	 
	
	
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);  //CH4Ԥװ��ʹ��	 

	TIM_ARRPreloadConfig(TIM2, ENABLE); //ʹ��TIM2��ARR�ϵ�Ԥװ�ؼĴ���
		
  TIM_Cmd(TIM2, ENABLE);  //����TIM2ʱ��

}//��ʼ�����������˶�״̬��pwm�������



