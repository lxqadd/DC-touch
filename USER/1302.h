#ifndef __DS1302_H  
#define __DS1302_H  
#include "stm32f10x.h"  
#include "delay.h"  
  
extern u8 ascii_time[7];     //����ascii��ʽ����  
  
extern u8 bcd_time[7];       //����bcd������  
  
typedef struct DS1302DATA  
{  
    u8 year;    //��  
    u8 month;   //��  
    u8 day;     //��  
    u8 hour;    //ʱ  
    u8 min;     //��  
    u8 sec;     //��  
    u8 week;    //��  
}DS1302DATA;  
  
extern struct DS1302DATA ds1302Data;  
  
 
  
#define DS1302_DAT_INPUT()     {GPIOB->CRH &= 0XFFFF0FFF;GPIOB->CRH|=8<<12;}  
#define DS1302_DAT_OUTPUT()    {GPIOB->CRH &= 0XFFFF0FFF;GPIOB->CRH|=3<<12;}  
  
//оƬ�Ĵ�����ַ���� �����д��ַ������Ҫ+1  
#define DS1302_SEC_REG          0x80        //�����ݵ�ַ  
#define DS1302_MIN_REG          0x82        //�����ݵ�ַ  
#define DS1302_HR_REG           0x84        //ʱ���ݵ�ַ  
#define DS1302_DATE_REG         0x86        //�����ݵ�ַ  
#define DS1302_MONTH_REG        0x88        //�����ݵ�ַ  
#define DS1302_DAY_REG          0x8a        //���ڼ����ݵ�ַ  
#define DS1302_YEAR_REG         0x8c        //�����ݵ�ַ  
#define DS1302_CONTROL_REG      0x8e        //д�����Ĵ�����ַ  
#define DS1302_CHARGER_REG      0x90        //������Ĵ���              
#define DS1302_CLKBURST_REG     0xbe             //���崮�Ĵ���  
#define DS1302_RAM_BASE                 0X30            //RAM������ַ  
  
#define CLOCKSTOP       0X80  
#define CLOCKSTART      0X00  
  
  
void Ds1302_Gpio_Init(void);  
void Ds1302_Write_Time_All(u8 start);  
void Ds1302_Readtime(void);  
  
  
  
  
#endif 