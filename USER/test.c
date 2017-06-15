#include "lcd.h"
#include "delay.h"
#include "gui.h"
#include "test.h"
#include "touch.h"
#include "key.h"
#include "led.h"
#include "pic.h"
#include "rtc.h"
#include "timer.h"
//////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//测试硬件：单片机STM32F103RBT6,主频72M  单片机工作电压3.3V
//QDtech-TFT液晶驱动 for STM32 IO模拟
//xiao冯@ShenZhen QDtech co.,LTD
//公司网站:www.qdtech.net
//淘宝网站：http://qdtech.taobao.com
//我司提供技术支持，任何技术问题欢迎随时交流学习
//固话(传真) :+86 0755-23594567
//手机:15989313508（冯工）
//邮箱:QDtech2008@gmail.com
//Skype:QDtech2008
//技术交流QQ群:324828016
//创建日期:2013/5/13
//版本：V1.1
//版权所有，盗版必究。
//Copyright(C) 深圳市全动电子技术有限公司 2009-2019
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////
//========================variable==========================//
u16 ColorTab[5] = {BRED, YELLOW, RED, GREEN, BLUE}; //定义颜色数组
//=====================end of variable======================//
SetDef Set[24];
//******************************************************************
//函数名：  DrawTestPage
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    绘制测试界面
//输入参数：str :字符串指针
//返回值：  无
//修改记录：
//******************************************************************
extern MeunDef Meun[MeunNum];
extern unsigned char	MeunFlag;
extern u8 tempbufmin[60];
void LCD_ShowShap(void)
{
    u8 i,j=0;
		u8 ShapValue[61]={0};
    POINT_COLOR = LBBLUE;
    LCD_DrawFillRectangle(10, 30, lcddev.width - 10, lcddev.height - 80);
    POINT_COLOR = WHITE;
    LCD_DrawLine(20, lcddev.height - 90, lcddev.width - 20, lcddev.height - 90);
		for(i=calendar.min;i<60;i++)
		{
			ShapValue[j++]=tempbufmin[i];
		}
		for(i=0;i<calendar.min;i++)
		{
			ShapValue[j++]=tempbufmin[i];
		}
    for(i = 0; i < 60; i++)
    {
        LCD_DrawLine(10 + 5 * i, 140-ShapValue[i], 10 + 5 * (i + 1), 140-ShapValue[i + 1]);
    }
}


void LCD_ShowSet(unsigned char select)
{
    u8 i, j;
    u16 s;
    Set[12].select = 1;
    Set[15].enable = 1;
    for(j = 0; j < 3; j++)
        for(i = 0; i < 8; i++)
        {
            if(Set[j * 8 + i].enable == 0)
                POINT_COLOR = LBBLUE;
            else
                POINT_COLOR = LITERED;            
            if(select == j * 8 + i)
            {
                //s=POINT_COLOR;
								u16 c;
								
                LCD_DrawRectangle(18 + i * 36, 28 + j * 36, 21 + i * 36 + 30, lcddev.height - 179 + j * 36);
								if(Meun[1].per2!=0)
									LCD_DrawRectangle(19 + i * 36, 29 + j * 36, 20 + i * 36 + 30, lcddev.height - 180 + j * 36);
								else
								{
									c=POINT_COLOR;
									POINT_COLOR=WHITE;
									LCD_DrawRectangle(19 + i * 36, 29 + j * 36, 20 + i * 36 + 30, lcddev.height - 180 + j * 36);									
									POINT_COLOR=c;
								}
                //POINT_COLOR=s;
            }
						if((select == j * 8 + i-1))
            {
                //s=POINT_COLOR;
								u16 c;
								c=POINT_COLOR;
                POINT_COLOR=WHITE;															
                LCD_DrawRectangle(18 + i * 36, 28 + j * 36, 21 + i * 36 + 30, lcddev.height - 179 + j * 36);
                LCD_DrawRectangle(19 + i * 36, 29 + j * 36, 20 + i * 36 + 30, lcddev.height - 180 + j * 36);
								POINT_COLOR=c;
                //POINT_COLOR=s;
            }
						if((select == j * 8 + i+1))
            {
                //s=POINT_COLOR;
								u16 c;
								c=POINT_COLOR;
                POINT_COLOR=WHITE;																
                LCD_DrawRectangle(18 + i * 36, 28 + j * 36, 21 + i * 36 + 30, lcddev.height - 179 + j * 36);
                LCD_DrawRectangle(19 + i * 36, 29 + j * 36, 20 + i * 36 + 30, lcddev.height - 180 + j * 36);
								POINT_COLOR=c;
                //POINT_COLOR=s;
            }
						if(select == 23)
            {
                //s=POINT_COLOR;
								u16 c;
								c=POINT_COLOR;
                POINT_COLOR=WHITE;																
                LCD_DrawRectangle(18, 28, 21+30, lcddev.height - 179 );
                LCD_DrawRectangle(19, 29, 20+30, lcddev.height - 180 );
								POINT_COLOR=c;
                //POINT_COLOR=s;
            }
						if(select == 0)
            {
                //s=POINT_COLOR;
								u16 c;
								c=POINT_COLOR;
                POINT_COLOR=WHITE;																
                LCD_DrawRectangle(270, 100, 303, lcddev.height - 107 );
                LCD_DrawRectangle(271, 101, 304, lcddev.height - 108 );
								POINT_COLOR=c;
                //POINT_COLOR=s;
            }
						LCD_DrawFillRectangle(20 + i * 36, 30 + j * 36, 20 + i * 36 + 30, lcddev.height - 180 + j * 36);
            LCD_ShowNum(27 + i * 36, 37 + j * 36, j * 8 + i, 2, 16);
        }
				if(Meun[1].per2==1)
					Show_Str(20, 150, WHITE, LBBLUE, "设定温度", 16, 0);
				else
					Show_Str(20, 150, LBBLUE, WHITE, "设定温度", 16, 0);
				LCD_ShowNum(100, 150, Set[select].temp, 2, 16);
				if(Meun[1].per2==2)
					Show_Str(216, 150, WHITE, LBBLUE, "状态", 16, 0);
				else
					Show_Str(216, 150, LBBLUE, WHITE, "状态", 16, 0);
				if(Set[select].enable == 1)
				{
					//  LCD_ShowString(272, 150, 16, "TRUE", 4);
					Show_Str(272, 150, LBBLUE, WHITE, "开启", 16, 0);
				}
				else
				{
						Show_Str(272, 150, LBBLUE, WHITE, "关闭", 16, 0);
				}
}
extern u8 TmpNow[8];
float fff = -45;
extern u8 hot;
void LCD_ShowIndex(void)
{
    u8 i,time[19] = {0}; //2015-09-03 12:30:30
		static u8 gongluflag=0;
    
    time[0] = calendar.w_year % 10000 / 1000 + 0x30;
    time[1] = calendar.w_year % 1000 / 100 + 0x30;
    time[2] = calendar.w_year % 100 / 10 + 0x30;
    time[3] = calendar.w_year % 10 / 1 + 0x30;
    time[4] = '-';
    time[5] = calendar.w_month % 100 / 10 + 0x30;
    time[6] = calendar.w_month % 10 / 1 + 0x30;
    time[7] = '-';
    time[8] = calendar.w_date % 100 / 10 + 0x30;
    time[9] = calendar.w_date % 10 / 1 + 0x30;
    time[10] = ' ';
    time[11] = calendar.hour % 100 / 10 + 0x30;
    time[12] = calendar.hour % 10 / 1 + 0x30;
    time[13] = ':';
    time[14] = calendar.min % 100 / 10 + 0x30;
    time[15] = calendar.min % 10 / 1 + 0x30;
    time[16] = ':';
    time[17] = calendar.sec % 100 / 10 + 0x30;
    time[18] = calendar.sec % 10 / 1 + 0x30;
		POINT_COLOR = LBBLUE;
    LCD_ShowString(46, 30, 24, time, 0);

    POINT_COLOR = LITERED;
    LCD_DrawFillRectangle(20, 64, 96, 150);
    POINT_COLOR = WHITE;
    BACK_COLOR = LITERED;
    LCD_ShowNum(34, 70, TmpNow[1], 2, 48);
    Show_Str(26, 134, WHITE, LITERED, "回水温度", 16, 0);
    BACK_COLOR = WHITE;

    POINT_COLOR = LBBLUE;
    LCD_DrawFillRectangle(124, 64, 200, 150);
    POINT_COLOR = WHITE;
    BACK_COLOR = LBBLUE;
    LCD_ShowNum(138, 70, TmpNow[0], 2, 48);
    Show_Str(130, 134, WHITE, LBBLUE, "出水温度", 16, 0);
    BACK_COLOR = WHITE;
    POINT_COLOR = LBBLUE;
		
		POINT_COLOR = LBBLUE;
    LCD_DrawFillRectangle(228, 64, 304, 150);
    POINT_COLOR = WHITE;
    BACK_COLOR = LBBLUE;
    LCD_ShowNum(242, 70, TmpNow[2], 2, 48);
    Show_Str(234, 134, WHITE, LBBLUE, "锅炉水温", 16, 0);
		if(Meun[0].per2==1)
    BACK_COLOR = WHITE;
    POINT_COLOR = LBBLUE;
		//LCD_ShowNum(280, 160, Meun[0].per1, 2, 16);
		if(Meun[0].per2==0)
			Show_Str(20, 160, LBBLUE, WHITE, "回水温差", 16, 0);
		else
			Show_Str(20, 160, WHITE, LBBLUE, "回水温差", 16, 0);
		POINT_COLOR=WHITE;
		if(Meun[0].per3!=gongluflag)
			LCD_DrawFillRectangle(90,160,280,176);
		if(hot==1)
			POINT_COLOR=LITERED;
		else
			POINT_COLOR=LBBLUE;
		LCD_DrawFillRectangle(90, 160, 120, 176);
		for(i=1;i<Meun[0].per3;i++)
		{
			LCD_DrawFillRectangle(90+i*50, 160, 130+i*50-10, 176);
		}
		gongluflag=Meun[0].per3;
		BACK_COLOR = WHITE;
    POINT_COLOR = LBBLUE;
}
void DrawTestPage(u8 *str)
{
    //绘制固定栏up
    LCD_Fill(0, 0, lcddev.width, 20, LITERED);
    //绘制固定栏down
    LCD_Fill(10, lcddev.height - 60, lcddev.width - 10, lcddev.height - 10, LITERED);
	Show_Str(20,200,WHITE,LITERED,"INFO",16,0);
	
	Show_Str(200,200,WHITE,LITERED,"PUMP CLOSE",16,0);
	Show_Str(80,200,WHITE,LITERED,"MOTO CLOSE",16,0);
    POINT_COLOR = WHITE;
    Gui_StrCenter(0, 2, WHITE, BLUE, str, 16, 1); //居中显示
    LCD_ShowIndex();
    //Gui_Drawbmp16(0,0,gImage_A);
}

//******************************************************************
//函数名：  main_test
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    绘制全动电子综合测试程序主界面
//输入参数：无
//返回值：  无
//修改记录：
//******************************************************************
void main_test(void)
{
    DrawTestPage("河北方矩自动化设备科技有限公司");
}

//******************************************************************
//函数名：  Test_Color
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    颜色填充测试，依次填充白色、黑色、红色、绿色、蓝色
//输入参数：无
//返回值：  无
//修改记录：
//******************************************************************
void Test_Color(void)
{
    DrawTestPage("测试1:纯色填充测试");
    LCD_Fill(0, 20, lcddev.width, lcddev.height - 20, WHITE);
    Show_Str(lcddev.width - 50, 30, BLUE, YELLOW, "White", 16, 1);
    delay_ms(500);
    LCD_Fill(0, 20, lcddev.width, lcddev.height - 20, BLACK);
    Show_Str(lcddev.width - 50, 30, BLUE, YELLOW, "Black", 16, 1);
    delay_ms(500);
    LCD_Fill(0, 20, lcddev.width, lcddev.height - 20, RED);
    Show_Str(lcddev.width - 50, 30, BLUE, YELLOW, "Red", 16, 1);
    delay_ms(500);
    LCD_Fill(0, 20, lcddev.width, lcddev.height - 20, GREEN);
    Show_Str(lcddev.width - 50, 30, BLUE, YELLOW, "Green", 16, 1);
    delay_ms(500);
    LCD_Fill(0, 20, lcddev.width, lcddev.height - 20, BLUE);
    Show_Str(lcddev.width - 50, 30, WHITE, YELLOW, "Blue", 16, 1);
    delay_ms(500);

}

//******************************************************************
//函数名：  Test_FillRec
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    矩形框显示和填充测试，依次显示粉红色、黄色、红色、绿色、蓝色矩形框，
//       	延时1500毫秒后，依次按照粉红色、黄色、红色、绿色、蓝色填充矩形框
//输入参数：无
//返回值：  无
//修改记录：
//******************************************************************
void Test_FillRec(void)
{
    u8 i = 0;
    DrawTestPage("测试2:GUI矩形填充测试");
    LCD_Fill(0, 20, lcddev.width, lcddev.height - 20, WHITE);
    for (i = 0; i < 5; i++)
    {
        LCD_DrawRectangle(lcddev.width / 2 - 80 + (i * 15), lcddev.height / 2 - 80 + (i * 15), lcddev.width / 2 - 80 + (i * 15) + 60, lcddev.height / 2 - 80 + (i * 15) + 60);
        POINT_COLOR = ColorTab[i];
    }
    delay_ms(1500);
    LCD_Fill(0, 20, lcddev.width, lcddev.height - 20, WHITE);
    for (i = 0; i < 5; i++)
    {
        LCD_DrawFillRectangle(lcddev.width / 2 - 80 + (i * 15), lcddev.height / 2 - 80 + (i * 15), lcddev.width / 2 - 80 + (i * 15) + 60, lcddev.height / 2 - 80 + (i * 15) + 60);
        POINT_COLOR = ColorTab[i];
    }
    delay_ms(1500);
}

//******************************************************************
//函数名：  Test_FillRec
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    圆形框显示和填充测试，依次显示粉红色、黄色、红色、绿色、蓝色圆形框，
//       	延时1500毫秒后，依次按照粉红色、黄色、红色、绿色、蓝色填充圆形框
//输入参数：无
//返回值：  无
//修改记录：
//******************************************************************
void Test_Circle(void)
{
    u8 i = 0;
    DrawTestPage("测试3:GUI画圆填充测试");
    LCD_Fill(0, 20, lcddev.width, lcddev.height - 20, WHITE);
    for (i = 0; i < 5; i++)
        gui_circle(lcddev.width / 2 - 80 + (i * 25), lcddev.height / 2 - 50 + (i * 25), ColorTab[i], 30, 0);
    delay_ms(1500);
    LCD_Fill(0, 20, lcddev.width, lcddev.height - 20, WHITE);
    for (i = 0; i < 5; i++)
        gui_circle(lcddev.width / 2 - 80 + (i * 25), lcddev.height / 2 - 50 + (i * 25), ColorTab[i], 30, 1);
    delay_ms(1500);
}

//******************************************************************
//函数名：  English_Font_test
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    英文显示测试
//输入参数：无
//返回值：  无
//修改记录：
//******************************************************************
void English_Font_test(void)
{
    DrawTestPage("测试4:英文显示测试");
    POINT_COLOR = RED;
    BACK_COLOR = BLUE;
    LCD_ShowString(10, 30, 12, "6X12:abcdefghijklmnopqrstuvwxyz0123456789", 0);
    LCD_ShowString(10, 45, 12, "6X12:ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", 1);
    LCD_ShowString(10, 60, 12, "6X12:~!@#$%^&*()_+{}:<>?/|-+.", 0);
    LCD_ShowString(10, 80, 16, "8X16:abcdefghijklmnopqrstuvwxyz0123456789", 0);
    LCD_ShowString(10, 100, 16, "8X16:ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", 1);
    LCD_ShowString(10, 120, 16, "8X16:~!@#$%^&*()_+{}:<>?/|-+.", 0);
    delay_ms(1200);
}

//******************************************************************
//函数名：  Chinese_Font_test
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    中文显示测试
//输入参数：无
//返回值：  无
//修改记录：
//******************************************************************
void Chinese_Font_test(void)
{
    DrawTestPage("测试5:中文显示测试");
    Show_Str(10, 30, BLUE, YELLOW, "16X16:全动电子技术有限公司欢迎您", 16, 0);
    Show_Str(10, 50, BLUE, YELLOW, "16X16:Welcome全动电子", 16, 1);
    Show_Str(10, 70, BLUE, YELLOW, "24X24:深圳市中文测试", 24, 1);
    Show_Str(10, 100, BLUE, YELLOW, "32X32:字体测试", 32, 1);
    delay_ms(1200);
}

//******************************************************************
//函数名：  Pic_test
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    图片显示测试，依次显示三幅40X40 QQ图像
//输入参数：无
//返回值：  无
//修改记录：
//******************************************************************


//******************************************************************
//函数名：  Touch_Test
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    触摸手写测试
//输入参数：无
//返回值：  无
//修改记录：
//******************************************************************
void Touch_Test(void)
{
    u8 key;
    u8 i = 0;
    u16 j = 0;
    u16 colorTemp = 0;
    TP_Init();
    KEY_Init();
    //TP_Adjust();  		//强制执行一次屏幕校准 (适用于没有IIC存储触摸参数的用户)
    DrawTestPage("测试7:Touch测试");
    LCD_ShowString(lcddev.width - 24, 0, 16, "RST", 1); //显示清屏区域
    LCD_Fill(lcddev.width - 52, 2, lcddev.width - 50 + 20, 18, RED);
    POINT_COLOR = RED;
    while(1)
    {
        key = KEY_Scan();
        tp_dev.scan(0);
        if(tp_dev.sta & TP_PRES_DOWN)			//触摸屏被按下
        {
            if(tp_dev.x < lcddev.width && tp_dev.y < lcddev.height)
            {
                if(tp_dev.x > (lcddev.width - 24) && tp_dev.y < 16)
                {
                    DrawTestPage("测试7:Touch测试");//清除
                    LCD_ShowString(lcddev.width - 24, 0, 16, "RST", 1); //显示清屏区域
                    POINT_COLOR = colorTemp;
                    LCD_Fill(lcddev.width - 52, 2, lcddev.width - 50 + 20, 18, POINT_COLOR);
                }
                else if((tp_dev.x > (lcddev.width - 60) && tp_dev.x < (lcddev.width - 50 + 20)) && tp_dev.y < 20)
                {
                    LCD_Fill(lcddev.width - 52, 2, lcddev.width - 50 + 20, 18, ColorTab[j % 5]);
                    POINT_COLOR = ColorTab[(j++) % 5];
                    colorTemp = POINT_COLOR;
                    delay_ms(10);
                }

                else TP_Draw_Big_Point(tp_dev.x, tp_dev.y, POINT_COLOR);		//画图
            }
        }
        else delay_ms(10);	//没有按键按下的时候
        if(key == 1)	//KEY_RIGHT按下,则执行校准程序
        {

            LCD_Clear(WHITE);//清屏
            TP_Adjust();  //屏幕校准
            TP_Save_Adjdata();
            DrawTestPage("测试7:Touch测试");
        }
        i++;
        if(i == 20)
        {
            i = 0;
            j++;
            LED0 = !LED0;
        }
        if(j > 100)
        {
            j = 0;
            break;
        }
    }
}




