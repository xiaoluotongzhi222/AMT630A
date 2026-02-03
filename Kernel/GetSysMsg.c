/***********************************************************************
*Copyright (C) 2005 深圳艾科创新有限公司产品应用一部
* All rights reserved.

*File name: 　 GetSysMsg.c
*Version:    　0.1
*Author:       cjinzong
*update:       2011-12-09

*Description:
             此文件是系统采集信息，系统所有的信息发出都由此文件发出。
*History:  

************************************************************************/
#define _GET_MSG_C_

#include "DataType.h"
#include "systemConfig.h"
#include "global.h"
#include "MsgMap.h"
#include "debug.h"
#include "mcu.h"
#include "GetUserInputMsg.h"
#include "GetSysMsg.h"
#include "ConfigLcdPara.h"
#include "interrupt.h"
#include "delay.h"
#include "Osd_Menu.h"
#include "Osd_MenuPage.h"
#include "AMT_Reg.h"
#include "AMT_Drv.h"
#include "AMT_Mcu.h"
#include "SysPower.h"
#include "BatteryAdc.h"



/***********************************************************
*name:       POS_GetUserInputMsg(void)
*input:      timeflg  //定时时间标志
*output:     void 
*update:     2011-11-27 
*state:      allright

*description:   
          获取用户输入信息，主要有按键和遥控两种信息。
          
*history:

************************************************************/
MSG POS_GetUserInputMsg(void)
{
    MSG XDATA curInputMsg = MSG_NULL;

    #ifdef KeyDetectEn
	curInputMsg = POS_GetKeyPadMsg();
	
	if(curInputMsg != MSG_NULL)
	{  			
	   return curInputMsg;
	}
    #endif
	
	return curInputMsg;
}



/***********************************************************
*name:       POS_GetSignalMsg(timeflg)
*input:      timeflg  //定时时间标志
*output:     void 
*update:     2011-11-27 
*state:      allright

*description:   
          获取信号状态消息。主要是检测信号有无，信号强弱等状态。
          
*history:

************************************************************/
MSG POS_GetSignalMsg(FLAG timer)
{
#define DetecTimes   20

	static UCHAR XDATA ucCont = 0;
	static FLAG   bSignalFlg = FALSE;
	
	if(timer)
	{
	    g_bGetSignalFlg = 0;

		#ifndef NoSignalBLOffEn
        //有无信号检测
		if(bSignalFlg == ((COLOR_SYS_TV_ACTIVE&_BIT1)>>1))
		{   
			if(ucCont<DetecTimes)
			{
			    ucCont++; 
				if(ucCont == DetecTimes)
				{
				     if(bSignalFlg)
				     {   
				         return MSG_SIGNAL_OK; //可靠有信号
				     }
					 else
					 {   
					     return MSG_NO_SIGNAL;//无信号
					 }
				}
			}
		}
		else
		{
		    ucCont = 0; 
		    bSignalFlg = (COLOR_SYS_TV_ACTIVE&_BIT1)>>1;
		}
        #else
		if(!IsSignalOk())
		{
	        SelAvSOGIn();
	        SelNullChannel();
			if(bSignalFlg == ((COMPHV_DETECT & _BIT6)>>6))
			{
			   	if(ucCont<DetecTimes)
				{
				    ucCont++; 
					if(ucCont == DetecTimes)
					{
					     if(bSignalFlg)
					     {   
					         return MSG_SIGNAL_OK; //可靠有信号
					     }
						 else
						 {   
						     return MSG_NO_SIGNAL;//无信号
						 }
					}
				}
			}
			else
			{
			    ucCont = 0; 
			    bSignalFlg = (COMPHV_DETECT&_BIT6)>>6;
			}
		}
		#endif
	}
	return MSG_NULL;
}

/***********************************************************
*name:       POS_GetColorSysMsg(timeflg)
*input:      timeflg  //定时时间标志
*output:     void 
*update:     2011-11-27 
*state:      allright

*description:   
          获取图像制式信息，例如PAL/NTSC/SECAM的切换，配置图像效果。
          
*history:

************************************************************/
MSG POS_GetColorSysMsg(FLAG timer)
{
	if(timer)
	{
		g_bGetColorSysFlg = 0;
		
	    if((g_ucColorSys != g_ucPreColorSys))
	    {
	        g_ucPreColorSys = g_ucColorSys;
			if(g_ucColorSys != NULL_SYS)  
	        {
	        	g_sysSetting.Video.colorSys = g_ucColorSys;
				//printf("g_sysSetting.Video.colorSys =%x", g_sysSetting.Video.colorSys);
				if(g_sysSetting.Video.colorSys < AUTO)
				{
				     return MSG_CONFIG_COLOR_SYS; 
	            }
				else
				{
				     return MSG_NULL;
				}
	        }
	    }
	}
	return MSG_NULL;    
}



/***********************************************************
*name:       POS_GetTimeMsg(timeflg)
*input:      timeflg  //定时时间标志
*output:     void 
*update:     2011-11-27 
*state:      allright

*description:   
          获取系统时间消息。例如定时任务。
          
*history:

************************************************************/
MSG POS_GetTimeMsg(FLAG timer)
{
	if(timer)
	{  
		g_bGetTimeFlg = 0;
		if(g_sysSetting.Osd.dispTime>0)
		{   
		    if(--g_sysSetting.Osd.dispTime == 0)
		    {    
		         /*在此判断是否需要退出OSD 还是需要显示LOGO或其他菜单*/
                 return MSG_OSD_EXIT;
		    }
		}

	    #ifdef QuickParaSaveEn 
        if(g_sysSetting.Osd.storageTime < OSD_STORAGE_TIME)  
        {
			if(++g_sysSetting.Osd.storageTime == OSD_STORAGE_TIME)
            {
                /*在此判断是否需要快速记忆OSD数据*/
                return(MSG_OSD_STORAGE);
            }
        }
		#endif
		
		#ifdef NoSignalPowerOffEn
		#define NoSignalSecond          2
		if(IsPowerOn()&&!IsSignalOk())
		{
			if(POS_SysTimeDriver())
			{
			    if(g_ucContBufSecond >= 60)
			    {
			        g_ucContBufSecond -= 60;
					g_ucContNoSignalSecond++;

				    if(g_ucContNoSignalSecond >= NoSignalSecond)
					{
					    return MSG_NOSIGNALPOWEROFF;
					}
			    }
			}
		}
		else
		{
		    g_ucContNoSignalSecond = 0X00;
		}
		#endif
	}
	return MSG_NULL;       
}



/***********************************************************
*name:       POS_GetBatteryAdcMsg(timeflg)
*input:      timeflg  //定时时间标志
*output:     void 
*update:     2011-11-27 
*state:      allright

*description:   
          获取系统电池的实时电压消息。
          
*history:

************************************************************/
MSG POS_GetBatteryAdcMsg(FLAG timer)
{

	UINT  XDATA curBatteryAdcVal = NULL_BATTERYADC;

    if(timer)
    {
        g_bGetBatteryAdcFlg = 0;

		#ifdef LowBaterryDetecEn 
		curBatteryAdcVal = POS_GetBatteryAdcValue();
		if(NULL_BATTERYADC != curBatteryAdcVal)
		{
             g_ucBatteryAdcVal = curBatteryAdcVal & 0X00FF; 
             return MSG_BATTERYADC;
		}
		#endif
    }
    return MSG_NULL;  
}



/***********************************************************
*name:       POS_GetUserDefinedMsg(timeflg)
*input:      timeflg  //定时时间标志
*output:     void 
*update:     2011-11-27 
*state:      allright

*description:   
         获取用户自定义消息，例如一些IO的状态 等等实时采样消息。
          
*history:

************************************************************/
MSG POS_GetUserDefinedMsg(FLAG timer)
{

	if(timer)
	{
		g_bGetUserDefFlg = 0;

		#ifdef SignalChangeBLOffEn
		//在正常开机情况下，信号变化时出测试黑屏到一定时间后打开
		if(g_ucContBLOn > 0)
		{   
	        g_ucContBLOn--;
			if(g_ucContBLOn == 0)
			{
	             if(g_bSignalFlg)
				 {
				     //等待Thlen 自动调整完成
				     while(XBYTE[0XFCE7]&_BIT3);
                     SetVDETestSwitch(VDE_CLOSE);
				 }
				 else
				 {
                     SetVDETestSwitch(VDE_BLUE);
				 }
				 TurnOnBackLight(); 			
			}
		}
		#endif

		
		#ifdef BL_OvpSoftProtecEn 
		if(g_bReleaseAdcKeyFlg)
		{
		    #define BLOvpSofProtec    3
		    static UCHAR XDATA BLOvpSofProtecStateCnt = 0;
			
		    if(POS_EnableChipAdc(ADC_DETEC_CH) > ProtecVolteAdcVal(ProtecVolte))
			{
			    BLOvpSofProtecStateCnt++;
			}
			else
			{
			   BLOvpSofProtecStateCnt = 0;
			}
            if(BLOvpSofProtecStateCnt >= BLOvpSofProtec)
            {
               return MSG_TURNOFF_BACKLIGHT;
            }
		}
		#endif

	}
	return MSG_NULL;  
}
