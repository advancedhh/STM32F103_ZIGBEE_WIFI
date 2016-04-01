#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "myiic.h"
#include "24cxx.h"
#include "rtc.h"
#include "spi.h"
#include "flash.h"
#include "touch.h"
#include "mmc_sd.h"
#include "ff.h"
#include "integer.h"
#include "diskio.h"
#include "text.h"
#include "fontupd.h"
#include "stdio.h"
#include "string.h"
//#include "picdecoder.h"

#include "rtc.h" 
#include "bmp180.h"


const u8 *COMPILED_DATE=__DATE__;//获得编译日期
const u8 *COMPILED_TIME=__TIME__;//获得编译时间
const u8* Week[7]={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};


extern const unsigned char gImage_1[38400];
extern const unsigned char gImage_2[38400];
extern const unsigned char gImage_3[38400];
extern const unsigned char gImage_4[38400];


void Load_Drow_Dialog(void)
{
	LCD_Clear(WHITE);//清屏   
 	POINT_COLOR=BLUE;//设置字体为蓝色 
	LCD_ShowString(216,0,"RST");//显示清屏区域
  POINT_COLOR=RED;//设置画笔蓝色 
}


int main(void)
{
	u32 fontcnt;		  
	u8 i,j;
	FATFS fs;
	u8 fontx[2];//gbk码
	u32 sector_size;
	u8 key;
	u8 t=0;	
	const char filedir[]="0:/PICTURE";
	
	SystemInit();
	delay_init(72);	     //延时初始化
	NVIC_Configuration();
	uart_init(9600);
 	LED_Init();
	LCD_Init();
	RTC_Init();
	AT24CXX_Init();		//IIC初始化
	SPI_Flash_Init();   //SPI FLASH 初始化 
	f_mount(0, &fs); //初始化必须mount
	POINT_COLOR=RED;
  
	LCD_ShowString(70,50,"SY-HMI-3.0TP");	 
  
	//SPI_Flash_Write_Page(gImage_1, 0, 38400);	
	//SPI_Flash_Write_Page(gImage_2, 38400, 38400);		
	//SPI_Flash_Write_Page(gImage_3, 38400 * 2, 38400);	
	//SPI_Flash_Write_Page(gImage_4, 38400 * 3, 38400);		
	
	//LCD_ShowPic();
	UART1_SendString(" bbbb!", 6);	
	
	
	delay_ms(1000);		
		BMP180_Test();		
	
	  UART1_SendString(" bbbb!", 6);		

	    	 			    	 
	
	POINT_COLOR=RED;
 	POINT_COLOR=BLUE;  

	while(1) //遍历GBK子库
	{	 
		fontcnt=0;
		for(i=0x81;i<0xff;i++)
		{		
			fontx[0]=i;
			POINT_COLOR=BLACK;
			//LCD_ShowNum(138,150,i,3,16);//显示内码高字节    
			for(j=0x40;j<0xfe;j++)
			{
				if(j==0x7f)continue;
				fontcnt++;
			 	fontx[1]=j;
				//Show_Font(138,190,fontx,16,0);	  
				t=200;
				while(t--)//延时,同时扫描按键
				{										  
					delay_ms(1);
				}
				
		if(t!=timer.sec)
		{
			t=timer.sec;
			LCD_ShowNum(50,230,timer.w_year,4,16);									  
			LCD_ShowNum(90,230,timer.w_month,2,16);									  
			LCD_ShowNum(114,230,timer.w_date,2,16);	 
			switch(timer.week)
			{
				case 0:
					LCD_ShowString(50,288,"Sunday   ");
					break;
				case 1:
					LCD_ShowString(50,288,"Monday   ");
					break;
				case 2:
					LCD_ShowString(50,288,"Tuesday  ");
					break;
				case 3:
					LCD_ShowString(50,288,"Wednesday");
					break;
				case 4:
					LCD_ShowString(50,288,"Thursday ");
					break;
				case 5:
					LCD_ShowString(50,288,"Friday   ");
					break;
				case 6:
					LCD_ShowString(50,288,"Saturday ");
					break;  
			}
			LCD_ShowNum(50,262,timer.hour,2,16);									  
			LCD_ShowNum(74,262,timer.min,2,16);									  
			LCD_ShowNum(98,262,timer.sec,2,16);
			LED=!LED;
			}   
		}			 		   
	}
}
	
	/*Touch_Init();
	delay_ms(1500);
	Load_Drow_Dialog();	
	
	while(1)
	{	
		if(Pen_Point.Key_Sta==Key_Down)//触摸屏被按下
		{
			Pen_Int_Set(0);//关闭中断
			do
			{
				Convert_Pos();
				Pen_Point.Key_Sta=Key_Up;
				if(Pen_Point.X0>216&&Pen_Point.Y0<16)Load_Drow_Dialog();//清除
				else 
				{
					Draw_Big_Point(Pen_Point.X0,Pen_Point.Y0);//画图	    
					GPIOA->ODR|=1<<0;    //PA0 上拉	   
				}
			}while(PEN==0);//如果PEN一直有效,则一直执行
			Pen_Int_Set(1);//开启中断
		}else delay_ms(10);
		if(key==1)//KEY0按下,则执行校准程序
		{
			LCD_Clear(WHITE);//清屏
		  Touch_Adjust();  //屏幕校准 
			Save_Adjdata();	 
			Load_Drow_Dialog();
		}
		i++;
		if(i==20)
		{
			i=0;
			LED=!LED;
		}
	}*/
}

