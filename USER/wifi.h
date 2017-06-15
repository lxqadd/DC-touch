#ifndef __WIFI_H
#define __WIFI_H
#include "sys.h"
extern u8 id[4];
extern u8 GetKey;  //�Ƿ�õ���Կ
extern u8 SVN[9];
/**************************************************
���ݷ���
*****************************************************/
#pragma pack(1)     //��С��ģʽ
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
	u8 set_tem;			//�����¶�
	u8 now_tem;			//�����¶�
	u8 power;				//���ʵ�λ
	u8 work;				//����״̬
	u8 state;				//����״̬
	u8 fasta;
	u8 check;		//У�鷽ʽ
	u8 Tail_frame;
}Date_send;
extern Date_send wifi;
#pragma pack()

/**************************************************
wifi���Ƽܹ�
*****************************************************/
#pragma pack(1)     //��С��ģʽ
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
	u8 setaddr;			//���õ�ַ
	u8 data;				//��������
	u8 check;				//У�鷽ʽ
	u8 Tail_frame;
}WifiCon_Get;
#pragma pack()

/**************************************************
���������ͻ�Ӧ����
*****************************************************/
#pragma pack(1)     //��С��ģʽ
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
���������մ�����
*****************************************************/
#pragma pack(1)     //��С��ģʽ
typedef struct 
{
	u8 Frame_head;
	u8 type;
	u8 Secret_Key[4];
	u8 parameter_num;
//	u32 set_tem;			//�����¶�
//	u32 now_tem;			//�����¶�
//	u32 power;				//���ʵ�λ
//	u32 work;					//����״̬
//	u32 state;				//����״̬
	u8 set_tem;			//�����¶�
	u8 now_tem;			//�����¶�
	u8 power;				//���ʵ�λ
	u8 work;				//����״̬
	u8 state;				//����״̬
	u8 fasta;				//��״̬
	u8 check;	
	u8 Tail_frame;
}Date_get;
#pragma pack()
/**************************************************
ע����Ϣ����
*****************************************************/
#pragma pack(1)     //��С��ģʽ
typedef struct 
{
	u8 Frame_head;
	u8 type;
	u32 Vendor_code;//���̴���
	u32 Device_code;//�豸����
	u8 ID[4];       //�豸���
	u8 parameter_num;//��������
	u8 check;
	u8 Tail_frame;
}Send_Register;
#pragma pack()
/**************************************************
ע����Ϣ����
*****************************************************/
#pragma pack(1)     //��С��ģʽ
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
�豸���ͻ�Ӧ����
*****************************************************/
#pragma pack(1)     //��С��ģʽ
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

