#include "1302.h"  
  
struct DS1302DATA ds1302Data = {0,0,0,0,0,0,0};  
u8 ascii_time[7] = {0};     //����ascii��ʽ����  
  
u8 bcd_time[7] = {0};       //����bcd������  
  
static u8 AsciiToBcd(u8 asciiData)  
{  
    u8 bcdData = 0;  
    bcdData = (((asciiData/10)<<4)|((asciiData%10)));  
    return bcdData;  
}  
static u8 BcdToAscii(u8 bcdData)  
{  
    u8 asciiData = 0;  
    asciiData = (((bcdData&0xf0)>>4)*10 + (bcdData&0x0f));  
    return asciiData;  
}  
  
//IO�ڳ�ʼ��  
void Ds1302_Gpio_Init(void)  
{  
    GPIO_InitTypeDef GPIO_InitStructure;  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  
      
    //RST  
      
    //CLK  
    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_10;        
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������  
    GPIO_Init(GPIOB, &GPIO_InitStructure);  
      
    //IO  
    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_11;        
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������  
    GPIO_Init(GPIOB, &GPIO_InitStructure);  
}  
  
//��ȡһ���ֽڵ�ʱ��  
u8 Ds1302_ReadByte(void)  
{  
    u8 i = 0, dat = 0;  
    DS1302_DAT_INPUT();  
    delay_us(5);  
    for(i = 0; i <8; i++)  
    {  
        dat >>= 1;  
        if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11))dat |= 0x80;  
        //DS1302_CLK = 1;  
	GPIO_SetBits(GPIOB,GPIO_Pin_10);
        delay_us(2);  
        //DS1302_CLK = 0;  
        GPIO_ResetBits(GPIOB,GPIO_Pin_10);
        delay_us(2);  
    }  
    return dat;  
}  
  
//д��һ���ֽڵ�ʱ��  
void Ds1302_WriteByte(u8 dat)  
{  
    u8 i = 0, data = dat;  
    DS1302_DAT_OUTPUT();   
    //DS1302_CLK = 0;  
    GPIO_ResetBits(GPIOB,GPIO_Pin_10);
    delay_us(2);  
    for(i = 0; i < 8; i++)  
    {  
        //DS1302_DATOUT = data&0x01;  
	if(data&0x01)
	  GPIO_SetBits(GPIOB,GPIO_Pin_11);
	else
	  GPIO_ResetBits(GPIOB,GPIO_Pin_11);
	delay_us(2);  
        //DS1302_CLK = 1;  
        GPIO_SetBits(GPIOB,GPIO_Pin_10);
	delay_us(2);  
        //DS1302_CLK = 0;  
        GPIO_ResetBits(GPIOB,GPIO_Pin_10);
	data >>= 1;  
    }  
}  
  
//д��һ���Ĵ���  
void Ds1302_Write(u8 address,u8 dat)  
{  
    //DS1302_RST = 0;  
    GPIO_ResetBits(GPIOB,GPIO_Pin_3);
    //DS1302_CLK = 0;  
    GPIO_ResetBits(GPIOB,GPIO_Pin_10);
    //DS1302_RST = 1;  
    GPIO_SetBits(GPIOB,GPIO_Pin_3);
    Ds1302_WriteByte(address);  
    Ds1302_WriteByte(dat);  
    GPIO_SetBits(GPIOB,GPIO_Pin_10);
    //DS1302_CLK = 1;  
    //DS1302_RST = 0; 
     GPIO_ResetBits(GPIOB,GPIO_Pin_3);
}  
  
//����д��ʱ��  
void Ds1302_Write_Time_Singel(u8 address,u8 dat)  
{  
    Ds1302_Write(DS1302_CONTROL_REG,0x00);  //ȡ��д����  
    Ds1302_Write(address,dat);  
    Ds1302_Write(DS1302_CONTROL_REG,0x80);  //��д����  
}  
  
//һ���������ʱ�����  
//start��ǰʱ�����л���ֹͣ  
void Ds1302_Write_Time_All(u8 start)  
{  
    Ds1302_Write(DS1302_CONTROL_REG,0x00);      //ȡ��д����  
    Ds1302_Write(DS1302_SEC_REG,(AsciiToBcd(ds1302Data.sec)|start));  
    Ds1302_Write(DS1302_MIN_REG,AsciiToBcd(ds1302Data.min));  
    Ds1302_Write(DS1302_HR_REG,AsciiToBcd(ds1302Data.hour));  
    Ds1302_Write(DS1302_DATE_REG,AsciiToBcd(ds1302Data.day));  
    Ds1302_Write(DS1302_MONTH_REG,AsciiToBcd(ds1302Data.month));  
    Ds1302_Write(DS1302_DAY_REG,AsciiToBcd(ds1302Data.week));  
    Ds1302_Write(DS1302_YEAR_REG,AsciiToBcd(ds1302Data.year));  
    Ds1302_Write(DS1302_CONTROL_REG,0x80);  //��д����  
}  
  
  
//��ȡһ���ֽ�  
u8 Ds1302_Read(u8 address)  
{  
    u8 data = 0;  
    //DS1302_RST = 0; 
     GPIO_ResetBits(GPIOB,GPIO_Pin_3);
    //DS1302_CLK = 0; 
    GPIO_ResetBits(GPIOB,GPIO_Pin_10);
    //DS1302_RST = 1; 
    GPIO_SetBits(GPIOB,GPIO_Pin_3);
    Ds1302_WriteByte(address|0x01); //��ȡ��ַ��Ҫ��0x01������Ϊ���1  
    data = Ds1302_ReadByte();  
    GPIO_SetBits(GPIOB,GPIO_Pin_10);
    //DS1302_CLK = 1;  
    //DS1302_RST = 0; 
     GPIO_ResetBits(GPIOB,GPIO_Pin_3);
    return data;  
}  
  
//��ȡʱ���ʱ��Ĭ����ʱ��������  
void Ds1302_Readtime(void)  
{  
    ds1302Data.sec = BcdToAscii(Ds1302_Read(DS1302_SEC_REG));  //��  
    ds1302Data.min = BcdToAscii(Ds1302_Read(DS1302_MIN_REG));  //��  
    ds1302Data.hour = BcdToAscii(Ds1302_Read(DS1302_HR_REG));   //Сʱ  
    ds1302Data.day = BcdToAscii(Ds1302_Read(DS1302_DATE_REG)); //��  
    ds1302Data.month = BcdToAscii(Ds1302_Read(DS1302_MONTH_REG)); //��  
    ds1302Data.week = BcdToAscii(Ds1302_Read(DS1302_DAY_REG));  //���ڼ�  
    ds1302Data.year = BcdToAscii(Ds1302_Read(DS1302_YEAR_REG)); //��  
} 