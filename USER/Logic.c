#include "include.h"

#define TempSet_difference 5
u16 kaiqixunhuanbenjishi=0;
u8 guanqixunhuanbenjishi=0 ;
u8 guanqixunhuanbendaojishi=0;
u8 autoroundflg=0;						//�Զ�������һȦ   ��־   �������Զ�������תһ�� ��־
unsigned char FP_flg;

unsigned long openfiretimer;
unsigned long closefiredelaytimer;
unsigned int  closewaterpumptimer;
unsigned int 	Freeze_prooftimer;
unsigned char closefiredelayflg;

unsigned char OpenFunctionNum;
unsigned char CloseFunctionNum;
unsigned char AutoFunctionNum;
unsigned char AutoFunctionIndicia[4];//�Զ����ܱ��
unsigned char TempFallFlg = 1;

unsigned char closewaterpumptimerflg;

unsigned char  HandSetFa;
void OpenSolenoid()
{
	
}
void CloseSolenoid()
{
	
}

unsigned char CheckFaFunctionNum(unsigned char code) //code Ϊ������ 0����1���ر�2���Զ�
{
	unsigned char count = 0,num;
	
	for(num = 0;num<4;num++)
	{
		if(FaFunctionSta[num]== code)
		{
			count++;
		}
	}
		return count;	
}

void HandOpenFa(unsigned char num)
{
	if(num == 1)
	{
		OpenFaOne;
	}
	else if(num == 2)
	{
		OpenFaTwo;
	}
	else if (num == 3)
	{
		OpenFaThr;
	}	
	else if(num == 4)
	{
		OpenFaFou;
	}
	else if(num == 5)
	{
		OpenFaOne;
		OpenFaTwo;
		OpenFaThr;
		OpenFaFou;	
	}
}
	

void HandCloseFa(unsigned char num)
{
	if(num == 1)
	{
		CloseFaOne;
	}
	else if(num == 2)
	{
		CloseFaTwo;
	}
	else if (num == 3)
	{
		CloseFaThr;
	}	
	else if(num == 4)
	{
		CloseFaFou;
	}
}

void HandOpenFireBurner(unsigned char num)
{
	if(num == 1)
	{
		Dangwei_ONE_SET ;
	}
	else if(num == 2)
	{
		Dangwei_TWO_SET ;
	}
	else if (num == 3)
	{
		Dangwei_THREE_SET ;
	}	
	else if(num == 4)
	{
		Dangwei_FOUR_SET ;
	}
}
	

void HandCloseFireBurner(unsigned char num)
{
	if(num == 1)
	{
			Dangwei_ONE_RES ;
	
	}
	else if(num == 2)
	{
      Dangwei_TWO_RES ;

	}
	else if (num == 3)
	{
		  Dangwei_THREE_RES ;

	}	
	else if(num == 4)
	{
		  Dangwei_FOUR_RES ;
	}
}


void OpenWatePump()
{
	GPIO_SetBits(GPIOB, GPIO_Pin_3);
	WaterPump = 1;
	SetWaterStatus(WaterPump);
	
	closewaterpumptimerflg = 0;//�п�ˮ�õ� ���� ��� ��ˮ�ñ�־
	closewaterpumptimer = 0;			
}
void CloseWatePump()
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_3);
	WaterPump = 0;
	SetWaterStatus(WaterPump);
}
void starthot(u8 level)
{
   if (level == 0)
   {
			Dangwei_ONE_SET ;
      Dangwei_TWO_RES ;
		  Dangwei_THREE_RES ;
		  Dangwei_FOUR_RES ;
   }
	 else if (level == 1)
   {
		  Dangwei_ONE_SET ;
      Dangwei_TWO_SET ; 
      Dangwei_THREE_RES ;		 
      Dangwei_FOUR_RES ;		 
   }
	 else if(level == 2)
	 {
		  Dangwei_ONE_SET ;
      Dangwei_TWO_SET ; 
		  Dangwei_THREE_SET ;
		  Dangwei_FOUR_RES ;
	 }
	 else if(level == 3)
	 {
		  Dangwei_ONE_SET ;
      Dangwei_TWO_SET ; 
		  Dangwei_THREE_SET ;
		  Dangwei_FOUR_SET ;
	 }
		else 
		{
			Dangwei_ONE_RES ;
      Dangwei_TWO_RES ;
		  Dangwei_THREE_RES ;
		  Dangwei_FOUR_RES ;		
		}
}
void OpenFireBurner()
{
	fireStatues=1;
  starthot(Power);
}
void CloseFireBurner()
{
	fireStatues=0;
   starthot(4);
}
unsigned char BEEPFLAG=0;
void OpenBEEP()
{
	LcdOpenBEEP();
}
void CloseBEEP()
{
}
void GetWaterErr()
{
}
void GetBurnerErr()
{

}
void GetWarmAbnormal(void)
{
	if(openfiretimer > OPENFIRE_TIME)
	{
		WringFlag |= Wring_WarmAbnormal;	
		closefiredelaytimer = 1;
	}
}
void GetTempDValue(void)
{
	if((TempNowHigh-TempNow)> 30)
		WringFlag |= Wring_TempDValue;	
}
void GetTempErr()
{
	//if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2))
	//	WringFlag |= Wring_HighTemp;
	if ((TempNowHigh > 85)&&(TempNowHigh<254))
	{
		WringFlag |= Wring_HighTemp;
	} 
}
void GetSensorErr()
{
	if (TempNow == 0xff || TempNow == 0xfe||TempNowHigh == 0xff || TempNowHigh == 0xfe)
		WringFlag |= Wring_SensorErr;
}
unsigned char FirstRun = 0;
unsigned char TimeContralEnable = 0;
unsigned char FaSta=0x00;
unsigned char OpenFaTimeCount=0;
unsigned char CloseFaTimeCount = 0;

void ChackAutoFa(void)
{
  unsigned char i,j;
	j=0;
	for(i=0;i<4;i++)
	{
		if(FaFunctionSta[i] == 2)
		{
			AutoFunctionIndicia[j] = i;
			j++;
		}
	}
	
}

void OpenSetFa(void)
{
	unsigned char flg = 0;			//��⵽��һ�������Զ���־
	if(ControlModel == 1)
	{
	if((FaFunctionSta[0]== 0 )||(FaFunctionSta[0]== 2 ))
	{
		OpenFaOne;
		if((FaFunctionSta[0]== 2 )&& (flg == 0))
		{
			FaSta |= 0x08;
			flg = 1;
		}
		else if(FaFunctionSta[0]== 0 )
		{
			FaSta |= 0x08;
		}
		else
		{
			FaSta &= 0xf7;	
		}
	}
	else
	{
		CloseFaOne;
		FaSta &= 0xf7;
	}
	if((FaFunctionSta[1]== 0 )||(FaFunctionSta[1]== 2 ))	
	{
		OpenFaTwo;
		if((FaFunctionSta[1]== 2 )&& (flg == 0))
		{
			FaSta |= 0x04;
			flg = 1;
		}
		else if(FaFunctionSta[1]== 0 )
		{
			FaSta |= 0x04;
		}
		else
		{
			FaSta &= 0xfb;	
		}
	}	
	else
	{
		CloseFaTwo;
		FaSta &= 0xfb;		
	}
	if((FaFunctionSta[2]== 0 )||(FaFunctionSta[2]== 2 ))	
	{	
		OpenFaThr;
		if((FaFunctionSta[2]== 2 )&& (flg == 0))
		{
			FaSta |= 0x02;
			flg = 1;
		}
		else if(FaFunctionSta[2]== 0 )
		{
			FaSta |= 0x02;
		}
		else
		{
			FaSta &= 0xfd;			
		}
	}
	else
	{
		CloseFaThr;
		FaSta &= 0xfd;	
	}
	if((FaFunctionSta[3]== 0 )||(FaFunctionSta[3]== 2 ))	
	{	
		OpenFaFou;
		if((FaFunctionSta[3]== 2 )&& (flg == 0))
		{
			FaSta |= 0x01;
			flg = 1;
		}
		else if(FaFunctionSta[3]== 0 )
		{
			FaSta |= 0x01;
		}
		else
		{
			FaSta &= 0xfe;			
		}
	}
	else
	{
		CloseFaFou;
		FaSta &= 0xfe;	
	}
}
	else
	{
		OpenFaOne;
		OpenFaTwo;
		OpenFaThr;
		OpenFaFou;	
		FaSta = 0x0f;	
	}
}
	

void OpenFa(unsigned char w)
{
	OpenFaTimeCount++;
	if(w&0x08)
	{
		OpenFaOne;
	}
	else
	{
		CloseFaOne;
	}
	if(w&0x04)
	{
		OpenFaTwo;
	}	
	else
	{
		CloseFaTwo;	
	}
	if(w&0x02)
	{
		OpenFaThr;
	}	
	else
	{
		CloseFaThr;
	}
	if(w&0x01)
	{
		OpenFaFou;
	}	
	else
	{
		CloseFaFou;
	}		
//	if((FaFunctionSta[0]== 0 )||((FaFunctionSta[0]== 2 )&&(w & 0x01)))
//	{
//		OpenFaOne;
//		if(FaFunctionSta[0]== 0)
//		{
//			FaSta |= 0x01;
//			TempFallFlg = 1;
//		}
//	}
//	else
//	{
//		CloseFaOne;
//		FaSta &= 0xfe;
//		TempFallFlg = 1;//��������Ϊ������ �������һ�����
//	}
//	if((FaFunctionSta[1]== 0 )||((FaFunctionSta[1]== 2 )&&(w & 0x02)))
//	{
//		OpenFaTwo;
//		if(FaFunctionSta[1]== 0)
//		{
//			FaSta |= 0x02;
//			TempFallFlg = 1;
//		}
//	}
//	else
//	{
//		CloseFaTwo;
//		FaSta &= 0xfd;
//		TempFallFlg = 1;//��������Ϊ������ �������һ�����
//	}
//	if((FaFunctionSta[2]== 0 )||((FaFunctionSta[2]== 2 )&&(w & 0x04)))
//	{
//		OpenFaThr;
//		if(FaFunctionSta[2]== 0)
//		{
//			FaSta |= 0x04;
//			TempFallFlg = 1;
//		}
//	}
//	else
//	{
//		CloseFaThr;
//		FaSta &= 0xfb;
//		TempFallFlg = 1;//��������Ϊ������ �������һ�����
//	}
//	if((FaFunctionSta[3]== 0 )||((FaFunctionSta[3]== 2 )&&(w & 0x08)))
//	{
//		OpenFaFou;
//		if(FaFunctionSta[3]== 0)
//		{
//			FaSta |= 0x08;
//			TempFallFlg = 1;
//		}
//	}
//	else
//	{
//		CloseFaFou;
//		FaSta &= 0xf7;
//		TempFallFlg = 1;//��������Ϊ������ �������һ�����
//	}
}
#ifdef MODE_Boiler
unsigned char MainrunTmp;
void MainRun(void)
{
	unsigned char *p;
	unsigned char i;
	p = &AutoFunctionIndicia[0];
	GetTempErr();  					//���±��� B0���¿���  ���вɼ��¶�>85
	GetSensorErr();					//�������쳣
	GetTempDValue();				//����¶Ȳ�ֵ��澯
	GetWarmAbnormal();			//�������쳣�澯
	if(OutsideFlg == 0)
	{
	if(RunFlag != 1)
	{
	  if ( ((TempNow <= 5)||( FP_flg == 1)) && LowTemp == 0)
	  {	
		 OpenWatePump();	
			HandOpenFa(5);
     if (kaiqixunhuanbenjishi++ > 50)
     {
			 LowTemp = 1;
			 fireStatues = 1; 
       starthot(3);
       kaiqixunhuanbenjishi = 51;	
			 Freeze_prooftimer = 1;
     } 
		 			 FP_flg = 1;
	  }
	  else if ((LowTemp == 1) && (Freeze_prooftimer == 0))
	  {
		 LowTemp = 0;
		 CloseWatePump();
		 CloseFireBurner();
		 fireStatues = 0;
		 FP_flg = 0;
		 kaiqixunhuanbenjishi = 0;	
	  }
//		else
//		{
//		 CloseWatePump();
//		 CloseFireBurner();
//		 kaiqixunhuanbenjishi = 0;	
//		}
		else if(LowTemp == 0)
		{
//		  FirstRun = 0;
			autoroundflg = 0;
		if (HandMode == 1)//�����ֶ�ģʽ�� ϵͳ����ֹͣ
		{
//				if(HandFireBurner==0)
//				{
//				 CloseFireBurner();
//				}
//				else
//				{
//				 starthot(Power);
//				}
			//���Լ��Ȱ� �̵���
					if(HandFireBurner & 0x08)
					{
						HandOpenFireBurner(1);
					}
					else if(!(HandFireBurner & 0x08))
					{
						HandCloseFireBurner(1);
					}
					if(HandFireBurner & 0x04)
					{
						HandOpenFireBurner(2);
					}
					else if(!(HandFireBurner & 0x04))
					{
						HandCloseFireBurner(2);					
					}
					if(HandFireBurner & 0x02)
					{
						HandOpenFireBurner(3);
					}
					else if(!(HandFireBurner & 0x02))
					{
						HandCloseFireBurner(3);								
					}
					if(HandFireBurner & 0x01)
					{
						HandOpenFireBurner(4);
					}
					else if(!(HandFireBurner & 0x01))
					{
						HandCloseFireBurner(4);								
					}
			//����ˮ�ü̵���
				if (HandWaterPump == 0)
				{
					CloseWatePump();
				}
				else
				{
					OpenWatePump();
				}
				//���Է�״̬
					if(HandSetFa & 0x08)
					{
						HandOpenFa(1);
					}
					else if(!(HandSetFa & 0x08))
					{
						HandCloseFa(1);
					}
					if(HandSetFa & 0x04)
					{
						HandOpenFa(2);
					}
					else if(!(HandSetFa & 0x04))
					{
						HandCloseFa(2);					
					}
					if(HandSetFa & 0x02)
					{
						HandOpenFa(3);
					}
					else if(!(HandSetFa & 0x02))
					{
						HandCloseFa(3);								
					}
					if(HandSetFa & 0x01)
					{
						HandOpenFa(4);
					}
					else if(!(HandSetFa & 0x01))
					{
						HandCloseFa(4);								
					}
				}
		    else if(closefiredelayflg == 1)
				{
				
				}
				else
				{	
					kaiqixunhuanbenjishi = 0;
					OpenFaTimeCount=0;
					CloseFireBurner();			
					CloseWatePump();
				}
		}					
  }
	//��ʼ����
	if (RunFlag == 1)
	{
//		GetTempErr();  					//���±��� B0���¿���  ���вɼ��¶�>85
//		GetSensorErr();					//�������쳣
//		GetTempDValue();				//����¶Ȳ�ֵ��澯
//		GetWarmAbnormal();			//�������쳣�澯
		
	
		TimeContral = 0;
		for (i = 0; i < 4; i++)
		{
			if (TimeSetBegain[i] != TimeSetEnd[i])
			{
				TimeContralEnable = 1;
				if (TimeHourNow >= TimeSetBegain[i] && TimeHourNow <= TimeSetEnd[i])
				{
					TempSetUseIng=TimeTepSet[i];
					TimeContral++;
					break;
				}				
			}
		}
		if (WringFlag == 0)
		{
			if (TimeContralEnable == 1)
			{
				if (TimeContral > 0)
				{
					if(ControlModel == 0)//0:���� 1:����
				{
					if (FirstRun == 0)
				  {						
					if (TempNow < TempSetUseIng) //��������
          {
						OpenWatePump();		
            if (kaiqixunhuanbenjishi++ > 100)
            {
            OpenFireBurner();
            kaiqixunhuanbenjishi = 101;
						FirstRun = 1;		
            }  	
          }
						else
							FirstRun = 1;	
				  }
				 if (TempNow > TempSetUseIng )   //�رռ���
         {
         CloseFireBurner();
         kaiqixunhuanbenjishi = 0;
				 //CloseWatePump();
				 if(closewaterpumptimerflg == 0)
						closewaterpumptimer = 1;
				 closewaterpumptimerflg = 1;

         }
         else if (TempNow < (TempSetUseIng - TempSet_difference) ) //��������   
         { 
          OpenWatePump();						
				  if (kaiqixunhuanbenjishi++ > 100)
            {
            OpenFireBurner();
            kaiqixunhuanbenjishi = 101;					
            }			 
         }
				 }
//				else
//				{
//					OpenFa(FaSta);

//					if(OpenFaTimeCount > 100)
//					{
//						OpenFaTimeCount=101;
//						if (FirstRun == 0)
//						{						
//							if (TempNow < TempSetUseIng) //��������
//							{
//								OpenWatePump();		
//								if (kaiqixunhuanbenjishi++ > 100)
//								{
//								OpenFireBurner();
//								kaiqixunhuanbenjishi = 101;
//								FirstRun = 1;		
//								}  		 
//							}
//						}
//					if ((TempNow > TempSetUseIng ) && (TempFallFlg == 1))  //�رռ���
//						{
//							CloseFireBurner();				
//							kaiqixunhuanbenjishi = 0;

//							
////							if(closewaterpumptimerflg == 0)
////								closewaterpumptimer = 1;
////							closewaterpumptimerflg = 1;
////							CloseWatePump();
//				      if((guanqixunhuanbendaojishi++)>50)
//							{
//								CloseWatePump();
//								guanqixunhuanbendaojishi = 51;
//								if((guanqixunhuanbenjishi++)>50)
//								{    guanqixunhuanbenjishi = 51;
//										if(AutoFunctionNum == 1)  //
//										{
//										}
//										else
//										{
//											if(FaFunctionSta[MainrunTmp] == 2)  //�رյ�ǰ�Զ����ķ���
//											{
//												FaSta &=(~(0x08>>MainrunTmp));	
//											}
//											MainrunTmp ++;
//											if((autoroundflg ==0)&&(MainrunTmp > 3))
//												autoroundflg = 1;
//											MainrunTmp &= 0x03; 
//											
//											if(FaFunctionSta[MainrunTmp] == 2)  //����һ���Զ����ķ���
//											{
//												FaSta |=(0x08>>MainrunTmp);	
//												TempFallFlg = 0;
//												guanqixunhuanbendaojishi = 0;
//												guanqixunhuanbenjishi = 0;
//											  OpenFaTimeCount=0;
//											}
//											else if(FaFunctionSta[MainrunTmp] == 0)//��   �򿪵ķ���
//											{
//												FaSta |=(0x08>>MainrunTmp);									
//											}
//											else
//											{
//												FaSta &=(~(0x08>>MainrunTmp));	
//											}
//										}									
//								}
//							}		
//						}
//						else if(TempFallFlg == 0)
//						{
//							if(OpenFaTimeCount>100)
//							{
//								OpenFaTimeCount = 101;
//								if(closewaterpumptimerflg == 0)
//								   OpenWatePump();	
//								if(TempNow < (TempSetUseIng - TempSet_difference))
//								{ 
//									OpenWatePump();	
//						
//									if (kaiqixunhuanbenjishi++ > 100)
//										{
//										OpenFireBurner();
//										kaiqixunhuanbenjishi = 101;	
//										TempFallFlg = 1 ;												
//										}			 
//								}
//								else
//								{
//									if(autoroundflg == 1)
//									{
//										if(closewaterpumptimerflg == 0)
//											closewaterpumptimer = 1;
//										closewaterpumptimerflg = 1;							
//									}
//							 }
//						}						
//						}
//					}
//				}
				else
				{
					OpenFa(FaSta);

					if(OpenFaTimeCount > 100)
					{
						OpenFaTimeCount=101;
						if (FirstRun == 0)
						{						
							if (TempNow < TempSetUseIng) //��������
							{
								OpenWatePump();		
								if (kaiqixunhuanbenjishi++ > 80)
								{
								OpenFireBurner();
								kaiqixunhuanbenjishi = 81;
								FirstRun = 1;		
								}  		 
							}
							else 
								FirstRun = 1;
						}
						if ((TempNow > TempSetUseIng ) && (TempFallFlg == 1) )  //�رռ���
						{
							CloseFireBurner();				
							kaiqixunhuanbenjishi = 0;

						if(closewaterpumptimerflg == 0)
							closewaterpumptimer = 1;
							closewaterpumptimerflg = 1;
							OpenFaTimeCount=0;
							if(AutoFunctionNum == 1)
							{
							}
							else
							{
									FaSta &=(~(0x08>>(*(p+MainrunTmp))));	 //�رյ�ǰ�Զ����ķ���
									MainrunTmp ++;
									if(MainrunTmp == AutoFunctionNum)
									{
										MainrunTmp = 0;										
									}
									if(MainrunTmp < AutoFunctionNum)
									{
										FaSta |=(0x08>>(*(p+MainrunTmp)));	
										TempFallFlg = 0;
									}	
									else 
									{
										MainrunTmp = 0;	
									}
								
//								if(FaFunctionSta[MainrunTmp] == 2)  //�رյ�ǰ�Զ����ķ���
//								{
//									FaSta &=(~(0x08>>MainrunTmp));	
//								}
//								MainrunTmp ++;
//								MainrunTmp &= 0x03; 
//								
//								if(FaFunctionSta[MainrunTmp] == 2)  //�Զ�
//								{
//									FaSta |=(0x08>>MainrunTmp);	
//									TempFallFlg = 0;
//								}
//								else if(FaFunctionSta[MainrunTmp] == 0)
//								{
//									FaSta |=(0x08>>MainrunTmp);									
//								}
//								else
//								{
//									FaSta &=(~(0x08>>MainrunTmp));	
//								}
							}
						}
						else if (TempNow < (TempSetUseIng - TempSet_difference) ) //��������
						{ 
							OpenWatePump();		
							TempFallFlg = 1;
							if (kaiqixunhuanbenjishi++ > 100)
								{
								OpenFireBurner();
								kaiqixunhuanbenjishi = 101;					
								}			 
						}
					}
				}

				}
				else
				{
					FirstRun = 0;
					TempFallFlg = 1 ;
          TimeContralEnable=0;
					CloseFireBurner();
					CloseWatePump();
				}
			}
			else
			{
				TempSetUseIng=TempSetMain;
				if(ControlModel == 0)
				{
				if (FirstRun == 0)
				{						
					if (TempNow < TempSetUseIng) //��������
          {
						OpenWatePump();		
            if (kaiqixunhuanbenjishi++ > 80)
            {
            OpenFireBurner();
            kaiqixunhuanbenjishi = 81;
						FirstRun = 1;		
            }  		 
          }
					else
						FirstRun = 1;
				}
				 if (TempNow > TempSetUseIng )   //�رռ���
        {
         CloseFireBurner();	
				 if(closewaterpumptimerflg == 0)					
						closewaterpumptimer = 1;
				 closewaterpumptimerflg	= 1;			 
         kaiqixunhuanbenjishi = 0;
        }
        else if (TempNow < (TempSetUseIng - TempSet_difference) ) //��������
        { 
					
          OpenWatePump();					
				  if (kaiqixunhuanbenjishi++ > 100)
            {
            OpenFireBurner();
            kaiqixunhuanbenjishi = 101;					
            }			 
        }
				}
//				else
//				{
//					OpenFa(FaSta);

//					if(OpenFaTimeCount > 100)
//					{
//						OpenFaTimeCount=101;
//						if (FirstRun == 0)
//						{						
//							if (TempNow < TempSetUseIng) //��������
//							{
//								OpenWatePump();		
//								if (kaiqixunhuanbenjishi++ > 80)
//								{
//								OpenFireBurner();
//								kaiqixunhuanbenjishi = 81;
//								FirstRun = 1;		
//								}  		 
//							}
//						}
//					if ((TempNow > TempSetUseIng ) && (TempFallFlg == 1))  //�رռ���
//						{
//							CloseFireBurner();				
//							kaiqixunhuanbenjishi = 0;

//							
////							if(closewaterpumptimerflg == 0)
////								closewaterpumptimer = 1;
////							closewaterpumptimerflg = 1;
////							CloseWatePump();
//				      if((guanqixunhuanbendaojishi++)>50)
//							{
//								CloseWatePump();
//								guanqixunhuanbendaojishi = 51;
//								if((guanqixunhuanbenjishi++)>50)
//								{
//									guanqixunhuanbenjishi = 51;
//										if(AutoFunctionNum == 1)  //
//										{
//										}
//										else
//										{
//											if(FaFunctionSta[MainrunTmp] == 2)  //�رյ�ǰ�Զ����ķ���
//											{
//												FaSta &=(~(0x08>>MainrunTmp));	
//											}
//											MainrunTmp ++;
//											if((autoroundflg ==0)&&(MainrunTmp > 3))
//												autoroundflg = 1;
//											MainrunTmp &= 0x03; 
//											
//											if(FaFunctionSta[MainrunTmp] == 2)  //����һ���Զ����ķ���
//											{
//												FaSta |=(0x08>>MainrunTmp);	
//												TempFallFlg = 0;
//												guanqixunhuanbendaojishi = 0;
//												guanqixunhuanbenjishi = 0;
//											  OpenFaTimeCount=0;
//											}
//											else if(FaFunctionSta[MainrunTmp] == 0)//��   �򿪵ķ���
//											{
//												FaSta |=(0x08>>MainrunTmp);									
//											}
//											else
//											{
//												FaSta &=(~(0x08>>MainrunTmp));	
//											}
//										}									
//								}
//							}		
//						}
//						else if(TempFallFlg == 0)
//						{
//							if(OpenFaTimeCount>100)
//							{
//								OpenFaTimeCount = 101;
//								if(closewaterpumptimerflg == 0)
//								   OpenWatePump();	
//								if(TempNow < (TempSetUseIng - TempSet_difference))
//								{ 	
//									OpenWatePump();										
//									if (kaiqixunhuanbenjishi++ > 100)
//										{
//										OpenFireBurner();
//										kaiqixunhuanbenjishi = 101;	
//										TempFallFlg = 1 ;												
//										}			 
//								}
//								else
//								{
//									if(autoroundflg == 1)
//									{
//										if(closewaterpumptimerflg == 0)
//											closewaterpumptimer = 1;
//										closewaterpumptimerflg = 1;							
//									}
//							 }
//						}						
//						}

//					}
//				}

				else
				{
					OpenFa(FaSta);

					if(OpenFaTimeCount > 100)
					{
						OpenFaTimeCount=101;
						if (FirstRun == 0)
						{						
							if (TempNow < TempSetUseIng) //��������
							{
								OpenWatePump();		
								if (kaiqixunhuanbenjishi++ > 80)
								{
								OpenFireBurner();
								kaiqixunhuanbenjishi = 81;
								FirstRun = 1;		
								}  		 
							}
							else
								FirstRun = 1;
						}
						if ((TempNow > TempSetUseIng ) && (TempFallFlg == 1) )  //�رռ���
						{
							CloseFireBurner();				
							kaiqixunhuanbenjishi = 0;

						if(closewaterpumptimerflg == 0)
							closewaterpumptimer = 1;
							closewaterpumptimerflg = 1;
							OpenFaTimeCount=0;
							if(AutoFunctionNum == 1)
							{
							}
							else
							{
								
//								if(FaFunctionSta[MainrunTmp] == 2)  //�رյ�ǰ�Զ����ķ���
//								{
									FaSta &=(~(0x08>>(*(p+MainrunTmp))));	 //�رյ�ǰ�Զ����ķ���
									MainrunTmp ++;
									if(MainrunTmp == AutoFunctionNum)
									{
										MainrunTmp = 0;										
									}
									if(MainrunTmp < AutoFunctionNum)
									{
										FaSta |=(0x08>>(*(p+MainrunTmp)));	
										TempFallFlg = 0;
									}	
									else 
									{
										MainrunTmp = 0;	
									}

//								}
//								MainrunTmp ++;
//								MainrunTmp &= 0x03; 
//								
//								if(FaFunctionSta[MainrunTmp] == 2)  //�Զ�
//								{
//									FaSta |=(0x08>>MainrunTmp);	
//									TempFallFlg = 0;
//								}
//								else if(FaFunctionSta[MainrunTmp] == 0)
//								{
//									FaSta |=(0x08>>MainrunTmp);									
//								}
//								else
//								{
//									FaSta &=(~(0x08>>MainrunTmp));	
//								}
							}
						}
						else if (TempNow < (TempSetUseIng - TempSet_difference) ) //��������
						{ 
							OpenWatePump();		
							TempFallFlg = 1;
							if (kaiqixunhuanbenjishi++ > 100)
								{
								OpenFireBurner();
								kaiqixunhuanbenjishi = 101;					
								}			 
						}
					}
				}
			}
		}
		else
		{
			OpenBEEP();//���ϱ���
			
			if(WringFlag & 0x08)//���±���  ��ʱ3min�ر�ˮ�� 
			{
				if(closewaterpumptimerflg == 0)
					closewaterpumptimer = 1;
				closewaterpumptimerflg = 1;
			}
			else if(WringFlag & 0x02)
			{
				closefiredelayflg = 1;  //��ʱ����ȣ�12H�� ��ʱ1min�ؼ���
			}
			else
			{
				CloseWatePump();
				CloseFireBurner();
			}
		}
	}
	
	if(closefiredelayflg == 1)
	{
		openfiretimer = 0;
		if(closefiredelaytimer == 0)
			{	
				CloseWatePump();
				CloseFireBurner();
				closefiredelayflg = 0;
				kaiqixunhuanbenjishi = 0;
				autoroundflg = 0;
			}			
	}
}
else if(OutsideFlg == 1)
{
	  if ( ((TempNow <= 5)||(FP_flg == 1)) && LowTemp == 0)//ֻҪ��⵽�¶�С�ڵ���24
	  {	
		 OpenWatePump();	
			HandOpenFa(5);			
     if (kaiqixunhuanbenjishi++ > 50)
     {
			 LowTemp = 1;
			 fireStatues = 1; 
       starthot(3);
       kaiqixunhuanbenjishi = 51;	
			 Freeze_prooftimer = 1;
     } 
			 FP_flg = 1;
	  }
	  else if ((LowTemp == 1) && (Freeze_prooftimer == 0))
	  {
		 LowTemp = 0;
		 CloseWatePump();
		 CloseFireBurner();
		 fireStatues = 0;
		 FP_flg = 0;
		 kaiqixunhuanbenjishi = 0;	
	  }
}
//	else
//	{
//		FirstRun = 0;
//		if (HandMode == 1)//�����ֶ�ģʽ�� ϵͳ����ֹͣ
//		{
////				if(HandFireBurner==0)
////				{
////				 CloseFireBurner();
////				}
////				else
////				{
////				 starthot(Power);
////				}
//			//���Լ��Ȱ� �̵���
//					if(HandFireBurner & 0x08)
//					{
//						HandOpenFireBurner(1);
//					}
//					else if(!(HandFireBurner & 0x08))
//					{
//						HandCloseFireBurner(1);
//					}
//					if(HandFireBurner & 0x04)
//					{
//						HandOpenFireBurner(2);
//					}
//					else if(!(HandFireBurner & 0x04))
//					{
//						HandCloseFireBurner(2);					
//					}
//					if(HandFireBurner & 0x02)
//					{
//						HandOpenFireBurner(3);
//					}
//					else if(!(HandFireBurner & 0x02))
//					{
//						HandCloseFireBurner(3);								
//					}
//					if(HandFireBurner & 0x01)
//					{
//						HandOpenFireBurner(4);
//					}
//					else if(!(HandFireBurner & 0x01))
//					{
//						HandCloseFireBurner(4);								
//					}
//			//����ˮ�ü̵���
//				if (HandWaterPump == 0)
//				{
//					CloseWatePump();
//				}
//				else
//				{
//					OpenWatePump();
//				}
//				//���Է�״̬
//					if(HandSetFa & 0x08)
//					{
//						HandOpenFa(1);
//					}
//					else if(!(HandSetFa & 0x08))
//					{
//						HandCloseFa(1);
//					}
//					if(HandSetFa & 0x04)
//					{
//						HandOpenFa(2);
//					}
//					else if(!(HandSetFa & 0x04))
//					{
//						HandCloseFa(2);					
//					}
//					if(HandSetFa & 0x02)
//					{
//						HandOpenFa(3);
//					}
//					else if(!(HandSetFa & 0x02))
//					{
//						HandCloseFa(3);								
//					}
//					if(HandSetFa & 0x01)
//					{
//						HandOpenFa(4);
//					}
//					else if(!(HandSetFa & 0x01))
//					{
//						HandCloseFa(4);								
//					}

//		}
//		else
//		{	
//      kaiqixunhuanbenjishi = 0;
//			OpenFaTimeCount=0;
//			CloseFireBurner();			
//			CloseWatePump();
//		}
//	}
}
#endif	

