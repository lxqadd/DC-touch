#ifndef __WIFI_H
#define __WIFI_H
#include "sys.h"
extern u8 id[4];
extern u8 GetKey;  //是否得到秘钥
extern u8 SVN[9];
/**************************************************
数据发送
*****************************************************/
#pragma pack(1)     //大小端模式
typedef struct 
{
	u8 Frame_head;
	u8 type;
	u8 Secret_Key[4];
	u8 parameter_num;
//	u32 set_tem;
//	u32 now_tem;
//	u32 power;
//	u32 work;
//	u32 state;
	u8 set_tem;			//设置温度
	u8 now_tem;			//现在温度
	u8 power;				//功率档位
	u8 work;				//工作状态
	u8 state;				//故障状态
	u8 fasta;
	u8 check;		//校验方式
	u8 Tail_frame;
}Date_send;
extern Date_send wifi;
#pragma pack()

/**************************************************
wifi控制架构
*****************************************************/
#pragma pack(1)     //大小端模式
typedef struct 
{
	u8 Frame_head;
	u8 type;
	u8 Secret_Key[4];
	u8 parameter_num;
//	u32 set_tem;
//	u32 now_tem;
//	u32 power;
//	u32 work;
//	u32 state;
	u8 setaddr;			//设置地址
	u8 data;				//设置数据
	u8 check;				//校验方式
	u8 Tail_frame;
}WifiCon_Get;
#pragma pack()

/**************************************************
服务器发送回应处理
*****************************************************/
#pragma pack(1)     //大小端模式
typedef struct 
{
	u8 Frame_head;
	u8 type;
	u8 result;
	u8 check;	
	u8 Tail_frame;
}Server;
#pragma pack()
extern Server ServerRev;

/**************************************************
服务器接收处理函数
*****************************************************/
#pragma pack(1)     //大小端模式
typedef struct 
{
	u8 Frame_head;
	u8 type;
	u8 Secret_Key[4];
	u8 parameter_num;
//	u32 set_tem;			//设置温度
//	u32 now_tem;			//现在温度
//	u32 power;				//功率档位
//	u32 work;					//工作状态
//	u32 state;				//故障状态
	u8 set_tem;			//设置温度
	u8 now_tem;			//现在温度
	u8 power;				//功率档位
	u8 work;				//工作状态
	u8 state;				//故障状态
	u8 fasta;				//阀状态
	u8 check;	
	u8 Tail_frame;
}Date_get;
#pragma pack()
/**************************************************
注册信息发送
*****************************************************/
#pragma pack(1)     //大小端模式
typedef struct 
{
	u8 Frame_head;
	u8 type;
	u32 Vendor_code;//厂商代码
	u32 Device_code;//设备代码
	u8 ID[4];       //设备编号
	u8 parameter_num;//参数个数
	u8 check;
	u8 Tail_frame;
}Send_Register;
#pragma pack()
/**************************************************
注册信息接收
*****************************************************/
#pragma pack(1)     //大小端模式
typedef struct 
{
	u8 Frame_head;
	u8 type;
//	u8 result;
	u8 registration_key[4];
	u8 check;
	u8 Tail_frame;
}Rev_Register;
#pragma pack()
/**************************************************
设备发送回应处理
*****************************************************/
#pragma pack(1)     //大小端模式
typedef struct 
{
	u8 Frame_head;
	u8 type;
	u8 result;
	u8 check;	
	u8 Tail_frame;
}Client;
#pragma pack()
extern Client ClientRev;

void sent_date(void);
void ClientDeal(void);
void over_rev(void);
void send_Register(void);
void rev_Register(void);
void ServerDeal(void);
void rev_date_deal(unsigned char *s,unsigned short l);
void TIM_Wifi(void);
void State_query(void);
void RstWifi(void);
void Creat_SVN(void);
#endif

