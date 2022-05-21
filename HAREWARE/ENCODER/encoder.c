#include "Encoder.h"

short Encoder_Left,Encoder_Right;
/**************************************************************************
�������ܣ��ұ�������ʼ��
**************************************************************************/

void Encoder_Init_R(void)
{
 TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
 TIM_ICInitTypeDef TIM_ICInitStructure;
 GPIO_InitTypeDef GPIO_InitStructure;

 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//TIM3ʱ��ʹ��
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��PORTBʱ��
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 |GPIO_Pin_5;//PB4,PB5
 GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IN_FLOATING;//��������
 GPIO_Init(GPIOB, &GPIO_InitStructure);
 
 
 TIM_DeInit(TIM3);//���½�Timer�Ĵ�������Ϊȱʡֵ 
 TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);//��TIM_TimeBaseInitStruct �е�ÿһ��������ȱʡֵ����
 
 TIM_TimeBaseStructure.TIM_Prescaler = 0x0;    // ����Ƶ
 TIM_TimeBaseStructure.TIM_Period =0xFFFF; 
 TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1;//ѡ��ʱ�ӷ�Ƶ������Ƶ
 TIM_TimeBaseStructure.TIM_CounterMode =TIM_CounterMode_Up; //���ϼ���ģʽ 
                                                            //(������Ϊ�������ģʽ���߱�����ģʽʱ����λֻ��)
  TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
 
 TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,
 TIM_ICPolarity_BothEdge, TIM_ICPolarity_BothEdge);//TI1��TI2��������������غ��½�����Ч
											//ѡ��ģʽ ������������ٶȺͷ���
 TIM_ICStructInit(&TIM_ICInitStructure); // ��TIM_ICInitStruct �е�ÿһ��������ȱʡֵ����
 TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;//ѡ��ͨ��1
 TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;////ӳ�䵽 TI1 ��
 TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;//����Ƶ
 TIM_ICInitStructure.TIM_ICFilter = 0x03;//0011 ��Ӧ8���¼����һ������
 
 TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;//ѡ��ͨ��2
 TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;//ӳ�䵽 TI2 ��
 TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;//����Ƶ
 TIM_ICInitStructure.TIM_ICFilter = 0x03;//0011 ��Ӧ8���¼����һ������
 
 TIM_ICInit(TIM3,&TIM_ICInitStructure);
 
 TIM_SetCounter(TIM3,0);  
 
 TIM_Cmd(TIM3, ENABLE); 
 
 }
 /**************************************************************************
�������ܣ����������ʼ��
**************************************************************************/
void Encoder_Init_L(void)
{
 TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
 TIM_ICInitTypeDef TIM_ICInitStructure;
 GPIO_InitTypeDef GPIO_InitStructure;

	
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);//TIM2ʱ��ʹ��
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��PORTAʱ��

 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 |GPIO_Pin_9;//PB8,PB9
 GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IN_FLOATING;//��������
 GPIO_Init(GPIOB, &GPIO_InitStructure);
 
 
 
 TIM_DeInit(TIM4);//���½�Timer����Ϊȱʡֵ 
 TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
 
 TIM_TimeBaseStructure.TIM_Prescaler = 0x0;  // ����Ƶ
 
 TIM_TimeBaseStructure.TIM_Period =0xFFFF; 
 TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1;//ѡ��ʱ�ӷ�Ƶ������Ƶ
 TIM_TimeBaseStructure.TIM_CounterMode =TIM_CounterMode_Up; //���ϼ���ģʽ 
                                                        //(������Ϊ�������ģʽ���߱�����ģʽʱ����λֻ��)
 TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
 
 TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,
 TIM_ICPolarity_BothEdge, TIM_ICPolarity_BothEdge);//TI1��TI2��������������غ��½�����Ч
											//ѡ��ģʽ ������������ٶȺͷ���
 TIM_ICStructInit(&TIM_ICInitStructure); 
 TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;//ѡ��ͨ��3
 TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
 TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
 TIM_ICInitStructure.TIM_ICFilter = 0x03;//0011 ��Ӧ8���¼����һ������
 
 TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;//ѡ��ͨ��4
 TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;//ӳ�䵽 TI2 ��
 TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
 TIM_ICInitStructure.TIM_ICFilter = 0x03;
 
 TIM_ICInit(TIM4,&TIM_ICInitStructure);
 
 TIM_SetCounter(TIM4,0); 
 TIM_Cmd(TIM4, ENABLE); 
 
 } 

uint16_t Encoder_L,Encoder_R; 
/**************************************************************************
�������ܣ���ȡ�����������ݲ�������������ת��
**************************************************************************/
void readEncoder(void)
{    
	
	      //===���ұ��������������
		Encoder_R = TIM_GetCounter(TIM3);       //===��ȡ��������1����	
	  TIM_SetCounter(TIM3,0);                 //===����������  
	  Encoder_L= TIM_GetCounter(TIM4);        //===��ȡ��������2����	
	  TIM_SetCounter(TIM4,0);              //===���������� 
		Encoder_Left=(short) Encoder_L;
	  Encoder_Right=(short)Encoder_R;
	  Encoder_Left=-Encoder_Left;//����ȡ������Ϊ��ƽ��С���������������ת��180�Ȱ�װ�ģ�Ϊ�˱�֤ǰ������ʱ��ı��������ݷ���һ��
}
