/***********************************************************************
*Copyright (C) 2005 深圳艾科创新有限公司产品应用一部
* All rights reserved.

*File name: 　 SysPower.C
*Version:    　0.1
*Author:       Jordan.chen
*update:       2011-12-07

*Description:
           此文件为系统电源管理模块。
*History:  

************************************************************************/
#define _POWER_C_

#include "DataType.h"
#include "global.h"
#include "systemConfig.h"
#include "configlcdpara.h"
#include "Debug.h"
#include "sysWorkPara.h"
#include "Videoproc.h"
#include "Delay.h"
#include "AMT_Reg.h"
#include "AMT_Drv.h"
#include "SysPower.h"
#include "MsgMap.h"
#include "Osd_Menu.h"
#include "interrupt.h"
#include "DianWeiQiKeyPad.h"


/****************************************************************************
*name:   PowerOnSystem(void)
*input:  void              
*output: void  

*description:
      系统开机函数，执行此函数后代表系统已经进入开机状态，并显示正常。

*history: Jordan.chen   2011/12/16    0.1    transplant   this  function
*****************************************************************************/
BOOL PowerOnSystem(void)
{ 
    printfStr("PowerOnSystem\n");

	#ifdef PowerLedEn
	hw_setGreenLEDOn();
	hw_setRedLEDOff();
	#endif

    SetPowerOn();
	
	ExitLowPowerMode();
	
    SetNosiceSwitch(g_sysSetting.Video.nosiceSw);
	
	DelayMs(100);
	
    if(CheckColorSys())
    {
        g_ucPreColorSys = g_ucColorSys;
      	ConfigColorSysDynPara(g_ucColorSys);    
    }
	
	#ifdef KeyDetectEn 
    #if KEY_TYPE == DIANWEIQI_KEY
	POS_InitDianWeiQiKey();
	POS_InitDianWeiQiKeyMsg();
	g_ucAdjustBrightnessVal = g_sysSetting.Video.brigthness;
	g_ucAdjustContrastVal = g_sysSetting.Video.contrast;
	g_ucAdjustSaturationVal = g_sysSetting.Video.saturation;
	#endif
	#endif

	SetPowerOnDelaytime(PowerOnDelay);
	
	#ifndef LogoEn 
	#ifdef NoSignalBLOffEn
	if(IsSignalOk())
	{   
	   //TurnOnBackLight();
	}
	else
	{
		//TurnOffBackLight(); 
		//SaveSetting();
		//EnterLowPowerMode();
	}
	#else  //#ifndef NoSignalBLOffEn
    //TurnOnBackLight();
	#endif  //	#ifdef NoSignalBLOffEn
	#endif  //	#ifndef LogoEn 
	
	g_bSignalFlg = IsSignalOk();
	g_bPreSignalFlg = g_bSignalFlg;
    g_bBLCtrlEnFlg = TRUE;
	
	return 1;
}

/****************************************************************************
*name:   PowerOffSystem(void)
*input:  void              
*output: void  

*description:
      系统关机函数，表示关机时需要执行动作。

*history: Jordan.chen   2011/12/16    0.1    transplant   this  function
*****************************************************************************/
BOOL PowerOffSystem(void)
{	 
    printfStr("PowerOffSystem\n");

	#ifdef PowerLedEn
	hw_setRedLEDOn();
	hw_setGreenLEDOff();
	#endif

	SetPowerOff();
	
	TurnOffBackLight(); 
	SaveSetting();
	EnterLowPowerMode();

    return 1;
}

