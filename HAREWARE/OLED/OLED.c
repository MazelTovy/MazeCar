#ifndef __OLEDFONT_C
#define __OLEDFONT_C
#include "OLED.h"
#include "stdlib.h"
#include "oledfont.h"  	 
#include "delay.h"
u8 OLED_GRAM[128][8];	 
/**********************************************
//IIC Start
**********************************************/
void IIC_Start(void)
{
	OLED_SCLK_Set() ;
	OLED_SDIN_Set();
	OLED_SDIN_Clr();
	OLED_SCLK_Clr();
}


/**********************************************
//IIC Stop
*********************************************/
void IIC_Stop(void)
{
	OLED_SCLK_Set() ;
//	OLED_SCLK_Clr();
OLED_SDIN_Clr();
	OLED_SDIN_Set();
	
}


void IIC_Wait_Ack(void)
{

	OLED_SCLK_Set() ;
	OLED_SCLK_Clr();
}


/**********************************************
// IIC Write byte
**********************************************/

void Write_IIC_Byte(unsigned char IIC_Byte)
{
	unsigned char i;
	unsigned char m,da;
	da=IIC_Byte;
	OLED_SCLK_Clr();
	for(i=0;i<8;i++)		
	{
		m=da;
	 OLED_SCLK_Clr();
		m=m&0x80;
		if(m==0x80)
		{
			OLED_SDIN_Set();
		}
		else OLED_SDIN_Clr();
			da=da<<1;
		OLED_SCLK_Set();
		OLED_SCLK_Clr();
		}
}


/**********************************************
// IIC Write Command
**********************************************/
void Write_IIC_Command(unsigned char IIC_Command)
{
	IIC_Start();
	Write_IIC_Byte(0x78);            //Slave address,SA0=0
	IIC_Wait_Ack();	
	Write_IIC_Byte(0x00);			//write command
	IIC_Wait_Ack();	
	Write_IIC_Byte(IIC_Command); 
	IIC_Wait_Ack();	
	IIC_Stop();
}


/**********************************************
// IIC Write Data
**********************************************/
void Write_IIC_Data(unsigned char IIC_Data)
{
	IIC_Start();
	Write_IIC_Byte(0x78);			//D/C#=0; R/W#=0
	IIC_Wait_Ack();	
	Write_IIC_Byte(0x40);			//write data
	IIC_Wait_Ack();	
	Write_IIC_Byte(IIC_Data);
	IIC_Wait_Ack();	
	IIC_Stop();
}


void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
	if(cmd)
	{
   		Write_IIC_Data(dat);
	}
	else
	{
   		Write_IIC_Command(dat);
	}
}


/********************************************
// fill_Picture
********************************************/
void fill_picture(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		OLED_WR_Byte(0xb0+m,0);		//page0-page1
		OLED_WR_Byte(0x00,0);		//low column start address
		OLED_WR_Byte(0x10,0);		//high column start address
		for(n=0;n<128;n++)
		{
			OLED_WR_Byte(fill_Data,1);
		}
	}
}


/***********************Delay****************************************/
void Delay_50ms(unsigned int Del_50ms)
{
	unsigned int m;
	for(;Del_50ms>0;Del_50ms--)
	for(m=6245;m>0;m--);
}


void Delay_1ms(unsigned int Del_1ms)
{
	unsigned char j;
	while(Del_1ms--)
	{	
		for(j=0;j<123;j++);
	}
}


//????
	void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD); 
}   	

  
//??OLED??    
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC??
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}


//??OLED??     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC??
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 


//????,???,????????!??????!!!	  
void OLED_Clear(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //?????(0~7)
		OLED_WR_Byte (0x00,OLED_CMD);      //??????????
		OLED_WR_Byte (0x10,OLED_CMD);      //??????????   
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	} //????
}


void OLED_On(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //?????(0~7)
		OLED_WR_Byte (0x00,OLED_CMD);      //??????????
		OLED_WR_Byte (0x10,OLED_CMD);      //??????????   
		for(n=0;n<128;n++)OLED_WR_Byte(1,OLED_DATA); 
	} //????
}


//???????????,??????
//x:0~127
//y:0~63
//mode:0,????;1,????				 
//size:???? 16/12 
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size)
{      	
	unsigned char c=0,i=0;	
	c=chr-' ';//???????			
	if(x>Max_Column-1){x=0;y=y+2;}
	if(Char_Size ==16)
	{
		OLED_Set_Pos(x,y);	
		for(i=0;i<8;i++)
		OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
		OLED_Set_Pos(x,y+1);
		for(i=0;i<8;i++)
		OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
	}
	else
	{	
		OLED_Set_Pos(x,y);
		for(i=0;i<6;i++)
		OLED_WR_Byte(F6x8[c][i],OLED_DATA);
	}
}


//m^n??
u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}	

			  
//??2???
//x,y :????	 
//len :?????
//size:????
//mode:??	0,????;1,????
//num:??(0~4294967295);	 		  
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;
			}else enshow=1; 
		}
	 	OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2); 
	}
} 

void OLED_Show_nIntNum(uint8_t x,uint8_t y,uint32_t m,uint8_t i)		//nλ������� ##########��
{
  uint32_t n,j,k;
	k=i;
	for(j=1;k>1;k--)
	{
		j*=10;
	}
	while(i)
	{
//	switch(i)
//	{
//	 case 10:n=m/j;break;
//	 case 9:n=m/j;break;
//	 case 8:n=m/j;break;		
//	 case 7:n=m/j;break;
//	 case 6:n=m/j;break;
//	 case 5:n=m/j;break;			
//	 case 4:n=m/j;break;
//	 case 3:n=m/j;break;
//	 case 2:n=m/j;break;
//	 default:n=m%10;break;
//	}
	n=m/j%10;
		
	switch(n)
	{case 0: OLED_ShowChar(x,y,'0',16);x+=8;
	      if(x>120){x=0;y+=16;};break;
	 case 1: OLED_ShowChar(x,y,'1',16);x+=8;
	      if(x>120){x=0;y+=16;};break;     
	 case 2: OLED_ShowChar(x,y,'2',16);x+=8;
	      if(x>120){x=0;y+=16;};break;   
	 case 3: OLED_ShowChar(x,y,'3',16);x+=8;
	      if(x>120){x=0;y+=16;};break;    
	 case 4: OLED_ShowChar(x,y,'4',16);x+=8;
	      if(x>120){x=0;y+=16;};break;
	 case 5: OLED_ShowChar(x,y,'5',16);x+=8;
	      if(x>120){x=0;y+=16;};break;
	 case 6: OLED_ShowChar(x,y,'6',16);x+=8;
	      if(x>120){x=0;y+=16;};break;
	 case 7: OLED_ShowChar(x,y,'7',16);x+=8;
	      if(x>120){x=0;y+=16;};break;
	 case 8: OLED_ShowChar(x,y,'8',16);x+=8;
	      if(x>120){x=0;y+=16;};break;
	 default:OLED_ShowChar(x,y,'9',16);x+=8;
	      if(x>120){x=0;y+=16;};break;
	}
	i--;
	j/=10;
	}
}


//????????
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j],Char_Size);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}

void OLED_ShowCHinese(u8 x,u8 y,u8 no)
{      			    
	u8 t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++)
		{
				OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
				adder+=1;
     }	
		OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
			{	
				OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
				adder+=1;
      }					
}

//void OLED_Showlength1()

/***********????:????BMP??128?4?????(x,y),x???0~127,y?????0~7*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
	    }
	}
} 
void OLED_Refresh(void)
{
	u8 i,n;
	for(i=0;i<8;i++)
	{
	   OLED_WR_Byte(0xb0+i,OLED_CMD); //��������ʼ��ַ
	   OLED_WR_Byte(0x00,OLED_CMD);   //���õ�����ʼ��ַ
	   OLED_WR_Byte(0x10,OLED_CMD);   //���ø�����ʼ��ַ
	   for(n=0;n<128;n++)
		 OLED_WR_Byte(OLED_GRAM[n][i],OLED_DATA);
  }
}

//???SSD1306					    
void OLED_Init(void)
{ 	
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //??A????
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	 //PB6 SCL PB7 SDA
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //????
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//??50MHz
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //???GPIOD3,6
 	GPIO_SetBits(GPIOB,GPIO_Pin_6|GPIO_Pin_7);	


	delay_ms(800);
OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	OLED_WR_Byte(0xCF,OLED_CMD);// Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
	OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00,OLED_CMD);//-not offset
	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
	OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
	OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
	OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02,OLED_CMD);//
	OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_WR_Byte(0xAF,OLED_CMD);
	OLED_Clear();
}  

#endif
