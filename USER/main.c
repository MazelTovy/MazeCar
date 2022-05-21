#include "stm32f10x.h"
#include "length.h"
#include "delay.h"
#include "usart.h"	
#include "sys.h"
#include "motor.h"
#include "pwm.h"
#include "led.h"
#include "lengt.h"
#include "OLED.h"
#include "PID.h"
/************************************************
 ALIENTEK ��ӢSTM32F103������ʵ��0
 ����ģ��
 ע�⣬�����ֲ��е��½������½�ʹ�õ�main�ļ� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

void sensor_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure_A;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��GPIO����
	GPIO_InitStructure_A.GPIO_Pin = GPIO_Pin_4;//����PA4gpio��
  GPIO_InitStructure_A.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure_A.GPIO_Mode = GPIO_Mode_IPD;//ipd��������
  GPIO_Init(GPIOA, &GPIO_InitStructure_A);//��ʼ��GPIO
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
}

void boot(void)
{ 
    GPIO_InitTypeDef     GPIO_InitStructure;
	
	  //PC5  ��������
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOC,GPIO_Pin_5);
	
  	//PA5  �̵���
//	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	
//    GPIO_Init(GPIOA, &GPIO_InitStructure);
//    GPIO_ResetBits(GPIOA,GPIO_Pin_5);

}

int main(void)
{
	float length=0;
	float length1=0;
	
	Motor_12_Config1();
	SystemInit();  //ϵͳʱ�ӵĳ�ʼ��
	delay_init();//��ʱʱ�ӵĳ�ʼ��
	boot(); //���ؿ��س�ʼ��PC5
	sensor_init();//���Թܳ�ʼ��PA4
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_Init();		  	 	//��ʼ����LED���ӵ�Ӳ���ӿ�
	BEEP_Init(); 
	uart_init(9600);
	
	
	OLED_Init();//��ʼ��OLED���棬��ʾ��Ա����
	OLED_ShowCHinese(0,0,0);//��
	OLED_ShowCHinese(18,0,1);//˼
	OLED_ShowCHinese(36,0,2);//��
	OLED_ShowCHinese(0,2,3);//��
	OLED_ShowCHinese(18,2,4);//��
	OLED_ShowCHinese(36,2,5);//��
	OLED_ShowCHinese(0,4,6);//��
	OLED_ShowCHinese(18,4,7);//��
	
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) == RESET)  //���ؿ�������ʾ׼������
	{
		delay_ms(300);  
	}
	
	OLED_Init();//��ʼ��OLED���棬��ʾ��Ա����
	OLED_ShowCHinese(0,0,8);//��
	OLED_ShowCHinese(18,0,9);//��
	OLED_ShowCHinese(36,0,10);//��
	OLED_ShowCHinese(54,0,11);//��
	OLED_ShowCHinese(72,0,12);//��
	OLED_ShowCHinese(90,0,13);//��
	OLED_ShowCHinese(0,4,14);//׼
	OLED_ShowCHinese(30,4,15);//��
	OLED_ShowCHinese(60,4,16);//��
	OLED_ShowCHinese(90,4,17);//��
	

	
	TIM2_PWM_Init(899,0);  //PWM���ĳ�ʼ��������С��������٣�����899��0��ʹ��PWM��Ƶ��Ϊ10Khz    f=72000000/((899+1)*(0+1))=10000

	while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) == RESET)  //�ȴ�ֱ���������ؼ���
	{
		delay_ms(50);  
	}
	BEEP=0;
	
OLED_Init();
	OLED_ShowCHinese(0,0,18);//ǰ
	OLED_ShowCHinese(18,0,19);//��
	OLED_ShowCHinese(36,0,20);//��
	//OLED_Show_nIntNum(54,0,length1,5);
	OLED_ShowChar(100,1,67,1);//c
	OLED_ShowChar(108,1,77,1);//m
	OLED_ShowCHinese(0,2,21);//��
	OLED_ShowCHinese(18,2,22);//��
	OLED_ShowCHinese(36,2,20);//��
	//OLED_Show_nIntNum(54,2,length,5);
	OLED_ShowChar(100,3,67,1);//c
	OLED_ShowChar(108,3,77,1);//m
while(1)
{

length = Senor_Using();	//���ò�ຯ��
length1= Senor_Using1();

	OLED_Show_nIntNum(54,0,length1,5);
	OLED_Show_nIntNum(54,2,length,5);
	
//	LEFTBACK();//�ҹ�90����
RIGHT();
//	ROTATELEFT();
//	delay_ms(2600);
//	STOP();
//	delay_ms(1000);
//	ROTATELEFT();
//	delay_ms(2200);
//	STOP();
//	delay_ms(1000);
		//��β��������ͣ�²�����
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) != RESET)
	{
//		delay_us(100);
//		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4) == RESET)
//		{
			STOP();
			//delay_ms(100);
			BEEP=1;
			while(1)
			{play_music();
			delay_ms(600);}
//		}
	}
//	else if(length<=10&&length1<=10)
//	{
//		STOP();
//		ROTATELEFT();
//		delay_ms(2600);
//		ROTATERIGHT();
//		delay_ms(2600);
//		
//	}

	else if(length1<5||length1>340)
	{
		BACK();
		delay_ms(800);
		LEFTBACK();
		delay_ms(450);
		RIGHT();
		delay_ms(200);
	}
	else if(length1<=15&&length1>=5)
	{
		BEEP=1;
		if(length<=18)
		{
			LEFTBACK();
			delay_ms(470);
		}
		if(length>18)
		{
			RIGHTBACK();
			delay_ms(470);
		}
	
	}
	else if(length1>15&&length1<=340)
	{
		BEEP=0;
		
		if(length<18)
		{
			
			RIGHT();
		}
		if(length>=18&&length<=50)
		{
			LEFT();
		}
		if(length>50)
		{
			delay_ms(20);
			if(length>50)
			{
				delay_ms(200);
				SHARPRIGHT();
				delay_ms(900);
				RIGHT();
				delay_ms(1300);
			}
			if(length<50)
				continue;
		}

	}

	
}
}

