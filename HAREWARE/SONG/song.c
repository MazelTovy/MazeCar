#include "led.h"
#include "song.h"
#include "delay.h"


 
void Sound(u16 frq)
{
	u32 time;
	if(frq != 1000)
	{
//		time = 500000/((u32)frq);
		time = 100000/((u32)frq);
//		PBeep = 1;
		BEEP=1;//打开蜂鸣器--根据自己的硬件情况调整，通常就是控制蜂鸣器的gpio引脚置1
 
		delay_us(time);
//		PBeep = 0;
		BEEP=0;//关闭蜂鸣器--根据自己的硬件情况调整，通常就是控制蜂鸣器的gpio引脚置0
		delay_us(time);
	}else
		delay_us(1000);
}
void play_music(void)
{
	//             低7  1   2   3   4   5   6   7  高1 高2  高3 高4 高5 不发音
	uc16 tone[] = {247,262,294,330,349,392,440,494,523,587,659,698,784,1000};//音频数据表
 
	//小燕子
		u8 music[]={3,5,8,6,5,13,//音调
	                3,5,6,8,5,13,
	                8,10,9,8,9,8,6,8,5,13,
					3,5,6,5,6,8,9,5,6,13,
					3,2,1,2,13,
					2,2,3,5,5,8,2,3,5,13};
		u8 time[] ={2,2,2,2,6,4,//时间  
				2,2,2,2,6,4,
                6,2,4,4,2,2,2,2,6,4,
				6,2,4,2,2,4,2,2,6,4,
				2,2,4,6,4,
				4,2,2,4,4,4,2,2,6,4};
//	u8 music[]={13,1,2,3,4,5,6,7,8};//测试基础音
//	u8 time[] ={4, 4,4,4,4,4,4,4,4};
 
	u32 yanshi;
	u16 i,e;
	yanshi = 2;//10;  4;  2
	for(i=0;i<sizeof(music)/sizeof(music[0]);i++){
		for(e=0;e<((u16)time[i])*tone[music[i]]/yanshi;e++){
			Sound((u32)tone[music[i]]);
		}	
	}
}
