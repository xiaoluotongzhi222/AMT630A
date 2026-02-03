/*******************************************************************************
*Copyright (C) 2005 深圳艾科创新有限公司产品应用一部
* All rights reserved.

*File name: 　 DianWeiQiKeyPad.c	  
*Version:      0.1
*update:       2012-03-12
*Description:
  		   此文件是对DIANWEIQI 按键的采集与处理。

*History:  yshuizhou   2012/03/12    0.1    build  this  moudle
******************************************************************************/
#define _DIANWEIQI_KEY_PAD_C_

#include "DataType.h"
#include "global.h"
#include "MsgMap.h"
#include "systemConfig.h"
#include "Debug.h"
#include "DianWeiQiKeyPad.h"
#include "AMT_Reg.h"
#include "ConfigLcdPara.h"
#include "AMT_Drv.h"



#ifdef KeyDetectEn 
#if KEY_TYPE == DIANWEIQI_KEY


/*************************************************************************
name:    POS_GetBestDianWeiQiKeyVal(UCHAR* AdcBuf, UCHAR Length)
input:   AdcBuf  //需滤波的数据指针。
         Length  //需滤波的数据长度。
output:	 返回平均数据平均滤波后的数据。
update： 2011-12-07
state：  try out
description: 返回平均数据平均滤波后的数据。

history: yshuizhou   2011/12/20    0.2    build  this  function
*************************************************************************/
UINT POS_GetBestDianWeiQiKeyVal( UINT * AdcBuf, UCHAR Length)
{
	UCHAR XDATA i,j,index;
	UINT XDATA s_offset1 = 0,s_offset2 = 0;
	
	 for(i=0; i<Length; i++)
	 {
	    s_offset1 += Abs(AdcBuf[i], AdcBuf[0]);
	 }
	index = 0;
	for(i=1; i<Length; i++)
	{
	    for(j=0; j<Length;j++)
	    {
	        s_offset2 += Abs(AdcBuf[i], AdcBuf[j]);
	    }
	    if(s_offset1 > s_offset2)
	    {
	        s_offset1 = s_offset2;
		    index = i;
	    }
	    s_offset2 = 0;	
	}	
	return AdcBuf[index];
}


/*************************************************************************
name:    POS_FilterDianWeiQiKeyVal(UINT * AdcValueBuf,UCHAR len)
input:   AdcValueBuf、len。
output:	 返回平均数据平均滤波后的数据。
update： 2011-11-28
state：  try out
description:  这个函数是ADC类型的按键滤波函数，经过限副滤波返回相应的按键值。 

history: yshuizhou   2011/12/20    0.2    build  this  function
*************************************************************************/
UINT POS_FilterDianWeiQiKeyVal(UINT * AdcValueBuf,UCHAR len)
{   

#define  BufferSize 4

	static UCHAR XDATA Index = 0;
	UINT  XDATA TheBetterKey;
	static UINT XDATA KeyBuffer[BufferSize];

	if(Index < BufferSize)
	{  
        KeyBuffer[Index] = POS_GetBestDianWeiQiKeyVal(AdcValueBuf,len);
		Index ++;
		return NULL_KEY;
	}

	Index = 0;
	TheBetterKey = POS_GetBestDianWeiQiKeyVal( KeyBuffer, BufferSize);
	return TheBetterKey;	
}



/***********************************************************
*name:     POS_GetDianWeiQiKeyValue(void)
*input:    non
*return:   返回当前通道采集到得电位器电压值。
*update:   2011-12-22
*state:   try out
*description:   
         这个函数获取ADC各个通道的电位器电压值。 

         
*history:yshuizhou   2011/12/20    0.2    build  this  function	
************************************************************/
UINT POS_GetDianWeiQiKeyValue(void)
{   

#define AdcOffSet                  1
#define SwtichWaitTime             5
#define AllChannelInit         	0
#define AllChannelStatic   		1
#define Ad0_Move          			2
#define Ad1_Move          			3
#define Ad2_Move          			4
#define Ad3_Move                	5


	static UCHAR XDATA ChannelStatus = AllChannelInit;
	static UCHAR XDATA Index = 0;	
	static UCHAR XDATA AdcChannel = 0;
	static UCHAR XDATA ChannelWaitTime = 0;
	static UINT  XDATA PreAd0Val = 0XFFFF;
	static UINT  XDATA PreAd1Val = 0XFFFF;
	static UINT  XDATA PreAd2Val = 0XFFFF;
	static UINT  XDATA PreAd3Val = 0XFFFF;
	static UCHAR  CODE  ChannelBuf[] = DianWeiQi_CH_LIST;
    static UINT   XDATA DianWeiQiKeyValBuf[] = {0XFFFF,0XFFFF,0XFFFF,0XFFFF};
	UINT  XDATA CurrentAdcVal= 0XFFFF;

	DianWeiQiKeyValBuf[Index] = (POS_EnableChipAdc(ChannelBuf[AdcChannel])>>4); 
	Index++; 

	if(Index >= (sizeof(DianWeiQiKeyValBuf)/2)) //note:该数组类型为int 
	{   
	    Index = 0; 
       	CurrentAdcVal = POS_FilterDianWeiQiKeyVal(DianWeiQiKeyValBuf,sizeof(DianWeiQiKeyValBuf)/2);

		if(NULL_KEY == CurrentAdcVal)
		{
		    return NULL_KEY;
		}
		else
		{
		  CurrentAdcVal >>=2;  //滤波后取高6位
		  CurrentAdcVal |= (((UINT)(ChannelBuf[AdcChannel]))<<12);//添加通道信息。
		}
	}
	else
	{
	     return NULL_KEY;
	}

	switch(ChannelStatus)
	{           
	    case  AllChannelInit:
		      if(CH0 == ChannelBuf[AdcChannel])
		      {
		           PreAd0Val = CurrentAdcVal;

				   #if TP1_ADC
				   printf("the CH0 PreAd1Val is %x:\r\n",PreAd0Val);
				   #endif
				   
		      }

			  if(CH1 == ChannelBuf[AdcChannel])
		      {
		           PreAd1Val = CurrentAdcVal;

				   #if TP1_ADC
				   printf("the CH1 PreAd1Val is %x:\r\n",PreAd1Val);
				   #endif

		       }

			   if(CH2 == ChannelBuf[AdcChannel])
		       {
		           PreAd2Val = CurrentAdcVal;

				   #if TP1_ADC
				   printf("the CH2 PreAd2Val is %x:\r\n",PreAd2Val);
				   #endif

		       }

			   if(CH3 == ChannelBuf[AdcChannel])
		       {
		           PreAd3Val = CurrentAdcVal;

				   #if TP1_ADC
				   printf("the CH3 PreAd2Val is %x:\r\n",PreAd3Val);
				   #endif

		       }
				
			   AdcChannel++;
	           if(AdcChannel >= (sizeof(ChannelBuf))) 
			   {
				   AdcChannel = 0;
				   ChannelStatus = AllChannelStatic;
			   } 
			  break;
			  
	    case  AllChannelStatic:
               if(CH0 == ChannelBuf[AdcChannel])
               {  
                  if(Abs(CurrentAdcVal &0X00FF,PreAd0Val &0X00FF) >AdcOffSet)
                  {
                     PreAd0Val = CurrentAdcVal;
					 ChannelStatus = Ad0_Move;
					 ChannelWaitTime = 0;
					 return CurrentAdcVal;
                  }
               }  
               if(CH1 == ChannelBuf[AdcChannel])
               {
                  if(Abs(CurrentAdcVal &0X00FF,PreAd1Val &0X00FF) >AdcOffSet)
                  {
                     PreAd1Val = CurrentAdcVal;
					 ChannelStatus = Ad1_Move;
					 ChannelWaitTime = 0;
					 return CurrentAdcVal;
                  }
               }
			   if(CH2 == ChannelBuf[AdcChannel])
               {
                  if(Abs(CurrentAdcVal &0X00FF,PreAd2Val &0X00FF) >AdcOffSet)
                  {
                     PreAd2Val = CurrentAdcVal;
					 ChannelStatus = Ad2_Move;
					 ChannelWaitTime = 0;
					 return CurrentAdcVal;
                  }
               }

			   if(CH3 == ChannelBuf[AdcChannel])
               {
                  if(Abs(CurrentAdcVal &0X00FF,PreAd3Val &0X00FF) >AdcOffSet)
                  {
                     PreAd3Val = CurrentAdcVal;
					 ChannelStatus = Ad3_Move;
					 ChannelWaitTime = 0;
					 return CurrentAdcVal;
                  }
               }
						   
			   AdcChannel++;
   	           if(AdcChannel >= (sizeof(ChannelBuf))) 
			   {
				   AdcChannel = 0;
			   } 
			 break;
			 
		case  Ad0_Move:
              if(Abs(CurrentAdcVal &0X00FF,PreAd0Val &0X00FF) >AdcOffSet)
              {
                  PreAd0Val = CurrentAdcVal;
			      ChannelWaitTime = 0;
				  return CurrentAdcVal;
              }
			 else
			 {
			     if(ChannelWaitTime < SwtichWaitTime)   
			     {
			         if(++ChannelWaitTime == SwtichWaitTime)
			         {   
			             AdcChannel++;
	                     if(AdcChannel >= (sizeof(ChannelBuf))) 
						 {
							AdcChannel = 0;
						 }
                         ChannelStatus = AllChannelStatic;
			         }
			     }
			 }
			 break;
			 
	    case  Ad1_Move:
              if(Abs(CurrentAdcVal &0X00FF,PreAd1Val &0X00FF) >AdcOffSet)
	          {
	              PreAd1Val = CurrentAdcVal;
		          ChannelWaitTime = 0;
				  return CurrentAdcVal;
	          }
			  else
		      {
			     if(ChannelWaitTime < SwtichWaitTime)  
			     {
			         if(++ChannelWaitTime == SwtichWaitTime)
			         {   
			             AdcChannel++;
	                     if(AdcChannel >= (sizeof(ChannelBuf))) 
						 {
							   AdcChannel = 0;
						 }
                         ChannelStatus = AllChannelStatic;
			         }
			     }
		     }
			 break;

		case  Ad2_Move:
              if(Abs(CurrentAdcVal &0X00FF,PreAd2Val &0X00FF) >AdcOffSet)
              {
                  PreAd2Val = CurrentAdcVal;
		          ChannelWaitTime = 0;
				  return CurrentAdcVal;
              }
			 else
			 {
			     if(ChannelWaitTime < SwtichWaitTime)   
			     {
			         if(++ChannelWaitTime == SwtichWaitTime)
			         {   
			             AdcChannel++;
	                     if(AdcChannel >= (sizeof(ChannelBuf))) 
						 {
							   AdcChannel = 0;
						 }
	                     ChannelStatus = AllChannelStatic;
			         }
			     }
			 }
			 break;

		case Ad3_Move:
			 if(Abs(CurrentAdcVal &0X00FF,PreAd3Val &0X00FF) >AdcOffSet)
             {
                  PreAd3Val = CurrentAdcVal;
		          ChannelWaitTime = 0;
				  return CurrentAdcVal;
             }
			 else
			 {
			     if(ChannelWaitTime < SwtichWaitTime)   
			     {
			         if(++ChannelWaitTime == SwtichWaitTime)
			         {   
			             AdcChannel++;
	                     if(AdcChannel >= (sizeof(ChannelBuf))) 
						 {
							   AdcChannel = 0;
						 }
	                     ChannelStatus = AllChannelStatic;
			         }
			     }
			 }
			 break;


		default:
			ChannelStatus = AllChannelInit;
			break;
	}
	return NULL_KEY;
}



/***********************************************************
*name:     POS_InitDianWeiQiKey(void)
*input:    non
*return:   non
*update:   2011-12-22
*state:   try out
*description:   
         这个函数初始化ADC各个通道的电位器电压值。 

         
*history:yshuizhou   2012/05/31    0.2    build  this  function	
************************************************************/
void POS_InitDianWeiQiKey(void)
{
  static UCHAR  CODE  ChannelBuf[] = DianWeiQi_CH_LIST;
  static UCHAR XDATA AdcChannel = 0;
  static UINT   XDATA DianWeiQiKeyValBuf[] = {0XFFFF,0XFFFF,0XFFFF,0XFFFF};
  static UCHAR XDATA Index = 0;	
  UINT  XDATA CurrentAdcVal= 0XFFFF;

  while(1) 
  {
     DianWeiQiKeyValBuf[Index] = (POS_EnableChipAdc(ChannelBuf[AdcChannel])>>4); 
	 Index++;

	if(Index >= (sizeof(DianWeiQiKeyValBuf)/2)) //note:该数组类型为int 
	{
	  	Index = 0; 
       	CurrentAdcVal = POS_FilterDianWeiQiKeyVal(DianWeiQiKeyValBuf,sizeof(DianWeiQiKeyValBuf)/2);

		if(NULL_KEY != CurrentAdcVal)
		{
		   CurrentAdcVal >>=2;  //滤波后取高6位
		   CurrentAdcVal |= (((UINT)(ChannelBuf[AdcChannel]))<<12);//添加通道信息。

		   if(CH0 == ChannelBuf[AdcChannel])
		   {
		     g_uiInitDianWeiQiCH0Val = CurrentAdcVal; 

			 #if TP1_ADC
			 printf("the g_uiInitDianWeiQiCH0Val is %x:\r\n",g_uiInitDianWeiQiCH0Val);
			 #endif

		   }

		   if(CH1 == ChannelBuf[AdcChannel])
		   {
		      g_uiInitDianWeiQiCH1Val = CurrentAdcVal; 

			 #if TP1_ADC
			 printf("the g_uiInitDianWeiQiCH1Val is %x:\r\n",g_uiInitDianWeiQiCH1Val);
			 #endif

		   }

		   if(CH2 == ChannelBuf[AdcChannel])
		   {
		      g_uiInitDianWeiQiCH2Val = CurrentAdcVal; 

			 #if TP1_ADC
			 printf("the g_uiInitDianWeiQiCH2Val is %x:\r\n",g_uiInitDianWeiQiCH2Val);
			 #endif

		   }

		   if(CH3 == ChannelBuf[AdcChannel])
		   {
		      g_uiInitDianWeiQiCH3Val = CurrentAdcVal; 

			 #if TP1_ADC
			 printf("the g_uiInitDianWeiQiCH3Val is %x:\r\n",g_uiInitDianWeiQiCH3Val);
			 #endif

		   }

		   AdcChannel++;
		   if(AdcChannel >= (sizeof(ChannelBuf))) 
		   {
			   AdcChannel = 0;
			   break;
		   } 
		}
	}
  }
}






/***********************************************************
*name:     	 POS_TransferDianWeiQiKeyMsg(UINT KeyVal)
*input:      AdcKeyVal
*output:     返回对应电位器通道的消息
*update:     2012-03-12

*description:   
         这个函数是返回对应电位器通道的消息。
*history:yshuizhou   2012/03/12    0.2    build  this  function	
************************************************************/
KeyInfor POS_TransferDianWeiQiKeyMsg(UINT KeyVal)
{    
	UCHAR  XDATA curChannel;
    KeyInfor XDATA Key ={MSG_NULL,NULL_TIME};
    curChannel = (UCHAR)(readFlg(KeyVal,DianWeiQiChannelBit)>>12);

	switch(curChannel)
	{
      case BrightnessChannel:      // 亮度调节电位器
	  	   Key.KeyMsg = MSG_UPK_BRIGHTNESS;
		   g_UserInputInfo.Status = inputPress;
		   g_ucDianWeiQiVal = KeyVal & 0X00FF;
	  	   break;
		   
	  case ContrastChannel:      // 对比度调节电位器
	       Key.KeyMsg = MSG_UPK_CONTRAST;
		   g_UserInputInfo.Status = inputPress;
		   g_ucDianWeiQiVal = KeyVal & 0X00FF;
	  	   break;
		   
	  case SaturationChannel:      // 色度调节电位器
	       	Key.KeyMsg = MSG_UPK_SATURATION;
			g_UserInputInfo.Status = inputPress;
			g_ucDianWeiQiVal = KeyVal & 0X00FF;
	  	   break;

	   default:
	   	   break;
			   
	}

	#if TP1_KEY
    printf("TP1_KEY >> the KeyMsg is %x:\r\n",Key.KeyMsg);				 
	#endif

	return Key;
}




/***********************************************************
*name:     	 SelDianWeiQiChannelVal(UCHAR Channel)
*input:      Channel
*output:     当前电位器通道的ADC电压值。
*update:     2012-05-31

*description:   
        这个函数返回当前电位器通道的电压值。
*history:yshuizhou   2012/05/31    0.2    build  this  function	
************************************************************/
UINT SelDianWeiQiChannelVal(UCHAR Channel)
{
    UINT XDATA curChannelVal;
	
	switch(Channel)
	{
	  case CH0:
	  	   curChannelVal= g_uiInitDianWeiQiCH0Val;
	  	   break;
		   
	  case CH1:
	  	   curChannelVal= g_uiInitDianWeiQiCH1Val;
	  	   break;
		   
	  case CH2:
	  	   curChannelVal= g_uiInitDianWeiQiCH2Val;
	  	   break;
			
	  case CH3:
	  	   curChannelVal= g_uiInitDianWeiQiCH3Val;
	  	   break;
		   
	  default:
	  	  break;
	}
	return curChannelVal;
}

/***********************************************************
*name:     	 UpdataDianWeiQiInitPara(UCHAR Channel)
*input:      non
*output:     non
*update:     2012-05-31

*description:   
         这个函数是初始化电位器效果参数。
*history:yshuizhou   2012/05/31    0.2    build  this  function	
************************************************************/
void UpdataDianWeiQiInitPara(UCHAR curChannel)
{

    UINT XDATA tmpDianWeiQiAdjustVal;
	
    switch(curChannel)
    {
       case BrightnessChannel:      // 亮度调节电位器
             g_sysSetting.Video.brigthness = SelDianWeiQiChannelVal(BrightnessChannel)>>1;
			 if(g_sysSetting.Video.brigthness > DianWeiQiAdjMaxStep)
			 {
			    g_sysSetting.Video.brigthness = DianWeiQiAdjMaxStep;
			 }
			 tmpDianWeiQiAdjustVal = g_sysSetting.Video.brigthness;
			 tmpDianWeiQiAdjustVal*=MAX_VALUE;
			 
			 #if DianWeiQiAdjDir == ForwardAdj
			 g_sysSetting.Video.brigthness = (UCHAR)(tmpDianWeiQiAdjustVal/DianWeiQiAdjMaxStep);
			 #elif DianWeiQiAdjDir == ReverseAdj
			 g_sysSetting.Video.brigthness = MAX_VALUE - (UCHAR)(tmpDianWeiQiAdjustVal/DianWeiQiAdjMaxStep);
			 #endif
			 
			 UpdataPicPara(); 
			 //printfStr("UpdataDianWeiQiInitPara-BrightnessChannel");
            break;

	   case ContrastChannel:      // 对比度调节电位器
	        g_sysSetting.Video.contrast = SelDianWeiQiChannelVal(ContrastChannel)>>1;
			if(g_sysSetting.Video.contrast > DianWeiQiAdjMaxStep)
			{
			   g_sysSetting.Video.contrast = DianWeiQiAdjMaxStep;
			}
			tmpDianWeiQiAdjustVal = g_sysSetting.Video.contrast;
			tmpDianWeiQiAdjustVal*=MAX_VALUE;

			#if DianWeiQiAdjDir == ForwardAdj
			g_sysSetting.Video.contrast = (UCHAR)(tmpDianWeiQiAdjustVal/DianWeiQiAdjMaxStep);
			#elif DianWeiQiAdjDir == ReverseAdj
			g_sysSetting.Video.contrast = MAX_VALUE - (UCHAR)(tmpDianWeiQiAdjustVal/DianWeiQiAdjMaxStep);
			#endif
			
			UpdataPicPara(); 
			//printfStr("UpdataDianWeiQiInitPara-ContrastChannel");
	        break;

	   case SaturationChannel:      // 色度调节电位器
	        g_sysSetting.Video.saturation = SelDianWeiQiChannelVal(SaturationChannel)>>1;
			if(g_sysSetting.Video.saturation > DianWeiQiAdjMaxStep)
			{
			   g_sysSetting.Video.saturation = DianWeiQiAdjMaxStep;
			}
			tmpDianWeiQiAdjustVal = g_sysSetting.Video.saturation;
			tmpDianWeiQiAdjustVal*=MAX_VALUE;
			
			#if DianWeiQiAdjDir == ForwardAdj
			g_sysSetting.Video.saturation = (UCHAR)(tmpDianWeiQiAdjustVal/DianWeiQiAdjMaxStep);
			#elif DianWeiQiAdjDir == ReverseAdj
			g_sysSetting.Video.saturation =  MAX_VALUE - (UCHAR)(tmpDianWeiQiAdjustVal/DianWeiQiAdjMaxStep);
			#endif
			
			UpdataPicPara(); 
			//printfStr("UpdataDianWeiQiInitPara-SaturationChannel");
	        break;
    }
}

/***********************************************************
*name:     	 POS_InitDianWeiQiKeyMsg(UINT AdcKeyVal)
*input:      non
*output:     non
*update:     2012-05-31

*description: 
*history:yshuizhou   2012/05/31    0.2    build  this  function	
************************************************************/
void POS_InitDianWeiQiKeyMsg(void)
{
   UCHAR  XDATA curChannel0 = 0XFF,curChannel1 = 0XFF,curChannel2 = 0XFF,curChannel3 = 0XFF;

   if(NULL_KEY != g_uiInitDianWeiQiCH0Val)
   {
      curChannel0 = (UCHAR)(readFlg(g_uiInitDianWeiQiCH0Val,DianWeiQiChannelBit)>>12);
	  UpdataDianWeiQiInitPara(curChannel0);
   }

   if(NULL_KEY != g_uiInitDianWeiQiCH1Val)
   {
      curChannel1 = (UCHAR)(readFlg(g_uiInitDianWeiQiCH1Val,DianWeiQiChannelBit)>>12);
      UpdataDianWeiQiInitPara(curChannel1);
   }

   if(NULL_KEY != g_uiInitDianWeiQiCH2Val)
   {
     curChannel2 = (UCHAR)(readFlg(g_uiInitDianWeiQiCH2Val,DianWeiQiChannelBit)>>12);
     UpdataDianWeiQiInitPara(curChannel2);
   }

   if(NULL_KEY != g_uiInitDianWeiQiCH3Val)
   {
     curChannel3 = (UCHAR)(readFlg(g_uiInitDianWeiQiCH3Val,DianWeiQiChannelBit)>>12);
     UpdataDianWeiQiInitPara(curChannel3);
   }
}


#endif   //#if KEY_TYPE == DIANWEIQI_KEY
#endif   //#ifdef KeyDetectEn 
