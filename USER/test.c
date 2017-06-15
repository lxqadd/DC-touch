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
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//����Ӳ������Ƭ��STM32F103RBT6,��Ƶ72M  ��Ƭ��������ѹ3.3V
//QDtech-TFTҺ������ for STM32 IOģ��
//xiao��@ShenZhen QDtech co.,LTD
//��˾��վ:www.qdtech.net
//�Ա���վ��http://qdtech.taobao.com
//��˾�ṩ����֧�֣��κμ������⻶ӭ��ʱ����ѧϰ
//�̻�(����) :+86 0755-23594567
//�ֻ�:15989313508���빤��
//����:QDtech2008@gmail.com
//Skype:QDtech2008
//��������QQȺ:324828016
//��������:2013/5/13
//�汾��V1.1
//��Ȩ���У�����ؾ���
//Copyright(C) ������ȫ�����Ӽ������޹�˾ 2009-2019
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////
//========================variable==========================//
u16 ColorTab[5] = {BRED, YELLOW, RED, GREEN, BLUE}; //������ɫ����
//=====================end of variable======================//
SetDef Set[24];
//******************************************************************
//��������  DrawTestPage
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    ���Ʋ��Խ���
//���������str :�ַ���ָ��
//����ֵ��  ��
//�޸ļ�¼��
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
					Show_Str(20, 150, WHITE, LBBLUE, "�趨�¶�", 16, 0);
				else
					Show_Str(20, 150, LBBLUE, WHITE, "�趨�¶�", 16, 0);
				LCD_ShowNum(100, 150, Set[select].temp, 2, 16);
				if(Meun[1].per2==2)
					Show_Str(216, 150, WHITE, LBBLUE, "״̬", 16, 0);
				else
					Show_Str(216, 150, LBBLUE, WHITE, "״̬", 16, 0);
				if(Set[select].enable == 1)
				{
					//  LCD_ShowString(272, 150, 16, "TRUE", 4);
					Show_Str(272, 150, LBBLUE, WHITE, "����", 16, 0);
				}
				else
				{
						Show_Str(272, 150, LBBLUE, WHITE, "�ر�", 16, 0);
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
    Show_Str(26, 134, WHITE, LITERED, "��ˮ�¶�", 16, 0);
    BACK_COLOR = WHITE;

    POINT_COLOR = LBBLUE;
    LCD_DrawFillRectangle(124, 64, 200, 150);
    POINT_COLOR = WHITE;
    BACK_COLOR = LBBLUE;
    LCD_ShowNum(138, 70, TmpNow[0], 2, 48);
    Show_Str(130, 134, WHITE, LBBLUE, "��ˮ�¶�", 16, 0);
    BACK_COLOR = WHITE;
    POINT_COLOR = LBBLUE;
		
		POINT_COLOR = LBBLUE;
    LCD_DrawFillRectangle(228, 64, 304, 150);
    POINT_COLOR = WHITE;
    BACK_COLOR = LBBLUE;
    LCD_ShowNum(242, 70, TmpNow[2], 2, 48);
    Show_Str(234, 134, WHITE, LBBLUE, "��¯ˮ��", 16, 0);
		if(Meun[0].per2==1)
    BACK_COLOR = WHITE;
    POINT_COLOR = LBBLUE;
		//LCD_ShowNum(280, 160, Meun[0].per1, 2, 16);
		if(Meun[0].per2==0)
			Show_Str(20, 160, LBBLUE, WHITE, "��ˮ�²�", 16, 0);
		else
			Show_Str(20, 160, WHITE, LBBLUE, "��ˮ�²�", 16, 0);
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
    //���ƹ̶���up
    LCD_Fill(0, 0, lcddev.width, 20, LITERED);
    //���ƹ̶���down
    LCD_Fill(10, lcddev.height - 60, lcddev.width - 10, lcddev.height - 10, LITERED);
	Show_Str(20,200,WHITE,LITERED,"INFO",16,0);
	
	Show_Str(200,200,WHITE,LITERED,"PUMP CLOSE",16,0);
	Show_Str(80,200,WHITE,LITERED,"MOTO CLOSE",16,0);
    POINT_COLOR = WHITE;
    Gui_StrCenter(0, 2, WHITE, BLUE, str, 16, 1); //������ʾ
    LCD_ShowIndex();
    //Gui_Drawbmp16(0,0,gImage_A);
}

//******************************************************************
//��������  main_test
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    ����ȫ�������ۺϲ��Գ���������
//�����������
//����ֵ��  ��
//�޸ļ�¼��
//******************************************************************
void main_test(void)
{
    DrawTestPage("�ӱ������Զ����豸�Ƽ����޹�˾");
}

//******************************************************************
//��������  Test_Color
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    ��ɫ�����ԣ���������ɫ����ɫ����ɫ����ɫ����ɫ
//�����������
//����ֵ��  ��
//�޸ļ�¼��
//******************************************************************
void Test_Color(void)
{
    DrawTestPage("����1:��ɫ������");
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
//��������  Test_FillRec
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    ���ο���ʾ�������ԣ�������ʾ�ۺ�ɫ����ɫ����ɫ����ɫ����ɫ���ο�
//       	��ʱ1500��������ΰ��շۺ�ɫ����ɫ����ɫ����ɫ����ɫ�����ο�
//�����������
//����ֵ��  ��
//�޸ļ�¼��
//******************************************************************
void Test_FillRec(void)
{
    u8 i = 0;
    DrawTestPage("����2:GUI����������");
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
//��������  Test_FillRec
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    Բ�ο���ʾ�������ԣ�������ʾ�ۺ�ɫ����ɫ����ɫ����ɫ����ɫԲ�ο�
//       	��ʱ1500��������ΰ��շۺ�ɫ����ɫ����ɫ����ɫ����ɫ���Բ�ο�
//�����������
//����ֵ��  ��
//�޸ļ�¼��
//******************************************************************
void Test_Circle(void)
{
    u8 i = 0;
    DrawTestPage("����3:GUI��Բ������");
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
//��������  English_Font_test
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    Ӣ����ʾ����
//�����������
//����ֵ��  ��
//�޸ļ�¼��
//******************************************************************
void English_Font_test(void)
{
    DrawTestPage("����4:Ӣ����ʾ����");
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
//��������  Chinese_Font_test
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    ������ʾ����
//�����������
//����ֵ��  ��
//�޸ļ�¼��
//******************************************************************
void Chinese_Font_test(void)
{
    DrawTestPage("����5:������ʾ����");
    Show_Str(10, 30, BLUE, YELLOW, "16X16:ȫ�����Ӽ������޹�˾��ӭ��", 16, 0);
    Show_Str(10, 50, BLUE, YELLOW, "16X16:Welcomeȫ������", 16, 1);
    Show_Str(10, 70, BLUE, YELLOW, "24X24:���������Ĳ���", 24, 1);
    Show_Str(10, 100, BLUE, YELLOW, "32X32:�������", 32, 1);
    delay_ms(1200);
}

//******************************************************************
//��������  Pic_test
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    ͼƬ��ʾ���ԣ�������ʾ����40X40 QQͼ��
//�����������
//����ֵ��  ��
//�޸ļ�¼��
//******************************************************************


//******************************************************************
//��������  Touch_Test
//���ߣ�    xiao��@ȫ������
//���ڣ�    2013-02-22
//���ܣ�    ������д����
//�����������
//����ֵ��  ��
//�޸ļ�¼��
//******************************************************************
void Touch_Test(void)
{
    u8 key;
    u8 i = 0;
    u16 j = 0;
    u16 colorTemp = 0;
    TP_Init();
    KEY_Init();
    //TP_Adjust();  		//ǿ��ִ��һ����ĻУ׼ (������û��IIC�洢�����������û�)
    DrawTestPage("����7:Touch����");
    LCD_ShowString(lcddev.width - 24, 0, 16, "RST", 1); //��ʾ��������
    LCD_Fill(lcddev.width - 52, 2, lcddev.width - 50 + 20, 18, RED);
    POINT_COLOR = RED;
    while(1)
    {
        key = KEY_Scan();
        tp_dev.scan(0);
        if(tp_dev.sta & TP_PRES_DOWN)			//������������
        {
            if(tp_dev.x < lcddev.width && tp_dev.y < lcddev.height)
            {
                if(tp_dev.x > (lcddev.width - 24) && tp_dev.y < 16)
                {
                    DrawTestPage("����7:Touch����");//���
                    LCD_ShowString(lcddev.width - 24, 0, 16, "RST", 1); //��ʾ��������
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

                else TP_Draw_Big_Point(tp_dev.x, tp_dev.y, POINT_COLOR);		//��ͼ
            }
        }
        else delay_ms(10);	//û�а������µ�ʱ��
        if(key == 1)	//KEY_RIGHT����,��ִ��У׼����
        {

            LCD_Clear(WHITE);//����
            TP_Adjust();  //��ĻУ׼
            TP_Save_Adjdata();
            DrawTestPage("����7:Touch����");
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




