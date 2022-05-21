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
 ALIENTEK 精英STM32F103开发板实验0
 工程模板
 注意，这是手册中的新建工程章节使用的main文件 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

void sensor_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure_A;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能GPIO外设
	GPIO_InitStructure_A.GPIO_Pin = GPIO_Pin_4;//定义PA4gpio口
  GPIO_InitStructure_A.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure_A.GPIO_Mode = GPIO_Mode_IPD;//ipd下拉输入
  GPIO_Init(GPIOA, &GPIO_InitStructure_A);//初始化GPIO
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
}

void boot(void)
{ 
    GPIO_InitTypeDef     GPIO_InitStructure;
	
	  //PC5  触摸开关
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOC,GPIO_Pin_5);
	
  	//PA5  继电器
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
	SystemInit();  //系统时钟的初始化
	delay_init();//延时时钟的初始化
	boot(); //触控开关初始化PC5
	sensor_init();//光电对管初始化PA4
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_Init();		  	 	//初始化与LED连接的硬件接口
	BEEP_Init(); 
	uart_init(9600);
	
	
	OLED_Init();//初始化OLED界面，显示成员名字
	OLED_ShowCHinese(0,0,0);//徐
	OLED_ShowCHinese(18,0,1);//思
	OLED_ShowCHinese(36,0,2);//喆
	OLED_ShowCHinese(0,2,3);//王
	OLED_ShowCHinese(18,2,4);//青
	OLED_ShowCHinese(36,2,5);//雨
	OLED_ShowCHinese(0,4,6);//李
	OLED_ShowCHinese(18,4,7);//榕
	
		while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) == RESET)  //开关开启后显示准备界面
	{
		delay_ms(300);  
	}
	
	OLED_Init();//初始化OLED界面，显示成员名字
	OLED_ShowCHinese(0,0,8);//铁
	OLED_ShowCHinese(18,0,9);//锅
	OLED_ShowCHinese(36,0,10);//炖
	OLED_ShowCHinese(54,0,11);//大
	OLED_ShowCHinese(72,0,12);//鹅
	OLED_ShowCHinese(90,0,13);//队
	OLED_ShowCHinese(0,4,14);//准
	OLED_ShowCHinese(30,4,15);//备
	OLED_ShowCHinese(60,4,16);//起
	OLED_ShowCHinese(90,4,17);//航
	

	
	TIM2_PWM_Init(899,0);  //PWM波的初始化，用于小车电机调速，传入899和0，使得PWM的频率为10Khz    f=72000000/((899+1)*(0+1))=10000

	while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) == RESET)  //等待直至触摸开关激活
	{
		delay_ms(50);  
	}
	BEEP=0;
	
OLED_Init();
	OLED_ShowCHinese(0,0,18);//前
	OLED_ShowCHinese(18,0,19);//端
	OLED_ShowCHinese(36,0,20);//：
	//OLED_Show_nIntNum(54,0,length1,5);
	OLED_ShowChar(100,1,67,1);//c
	OLED_ShowChar(108,1,77,1);//m
	OLED_ShowCHinese(0,2,21);//左
	OLED_ShowCHinese(18,2,22);//侧
	OLED_ShowCHinese(36,2,20);//：
	//OLED_Show_nIntNum(54,2,length,5);
	OLED_ShowChar(100,3,67,1);//c
	OLED_ShowChar(108,3,77,1);//m
while(1)
{

length = Senor_Using();	//调用测距函数
length1= Senor_Using1();

	OLED_Show_nIntNum(54,0,length1,5);
	OLED_Show_nIntNum(54,2,length,5);
	
//	LEFTBACK();//右拐90度整
RIGHT();
//	ROTATELEFT();
//	delay_ms(2600);
//	STOP();
//	delay_ms(1000);
//	ROTATELEFT();
//	delay_ms(2200);
//	STOP();
//	delay_ms(1000);
		//结尾碰到黑线停下并鸣笛
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

