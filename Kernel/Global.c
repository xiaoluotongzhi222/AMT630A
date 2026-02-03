/***********************************************************************
*Copyright (C) 2005 深圳艾科创新有限公司产品应用一部
* All rights reserved.

*File name: 　 Global.c
*Version:    　0.1
*Author:       cjinzong
*update:       2010-05-23

*Description:
             主要包括一些系统初始化函数和一些全局又不好分类的函数。
*History:  

************************************************************************/
#define _GLOBAL_C_

#include "DataType.h"
#include "systemConfig.h"
#include "global.h"
#include "mcu.h"
#include "videoProc.h"
#include "Debug.h"
#include "sysWorkPara.h"
#include "MsgMap.h"
#include "Osd_menu.h"
#include "Flash.h"
#include "E2prom.h"
#include "interrupt.h"
#include "ConfigLcdPara.h"
#include "AMT_Reg.h"
#include "AMT_Mcu.h"
#include "AMT_Drv.h"
#include "ConfigLcdPara.h"




/***********************************************************
*name:       ConfigMcuCtrl(void)
*input:      void
             
*output:     void
*update:     2011-11-27 
*state:      allright

*description:   
          配置为MCU控制模块
*history:
                                
************************************************************/
void ConfigMcuCtrl(void)
{
    ConfigCrtlMode(MCU);
	ENH_PLL = 0X20;
}


/*************************************************************************
name:    Abs(UINT Val1,UINT Val2)
input:   Val1、Val2
output:	 返回当前最大的值。
update： 2011-12-07
state：  allright
description: 返回当前最大的值。

history: yshuizhou   2011/12/20   0.2    build  this  function
*************************************************************************/
UINT Abs(UINT Val1,UINT Val2)
{
   if(Val1 >= Val2)
   {
        return (Val1-Val2);
   }
   else
   {
        return (Val2-Val1);
   }
}


/***********************************************************
*name:       InitGlobalVariables(void)
*input:      void
*output:     void 
*update:     2011-11-27 
*state:      allright

*description:   
           初始化全局变量。
*history:
                                
************************************************************/
void InitGlobalVariables(void)
{      
       UINT XDATA i;

	   for(i = 0; i < 0x800; i++)
	   {
	     XBYTE[i] = 0xff;
	   }
	   
       printfStr("InitGlobalVariables\n");
	   g_ucMenuItemIndex = 0X00;
	   g_ucContBufSecond = 0X00;
	   g_ucContNoSignalSecond = 0X00;
	   g_ucContBLOn = 0X00;
	   g_ucColorSys = 0XFF;
	   g_ucPreColorSys = 0XFF;
	   g_ucStableTime = 0X00;
	   g_ucAdjustBrightnessVal = 0XFF;
	   g_ucAdjustContrastVal = 0XFF;
	   g_ucAdjustSaturationVal = 0XFF;
	   g_ucBatteryAdcLev = BatterAdc_Lev0;
	   g_uiInitDianWeiQiCH0Val = NULL_KEY;
	   g_uiInitDianWeiQiCH1Val = NULL_KEY;
	   g_uiInitDianWeiQiCH2Val = NULL_KEY;
	   g_uiInitDianWeiQiCH3Val = NULL_KEY;
	   g_bKeyRepeatFlg = FALSE;
	   g_bReleaseAdcKeyFlg = FALSE;
	   g_bSignalFlg = FALSE;
	   g_bPreSignalFlg = FALSE;
	   g_bBLCtrlEnFlg = FALSE;
       PreKey.KeyMsg = MSG_NULL;
	   PreKey.PressTime = NULL_TIME;
	   g_ucOsdEixt =  OsdBrightness|OsdContrast|OsdSaturation|OsdBatteryAdc;
       ClrVideoChSelEn();
	   SetMenuIndex(Osd_RootMenu);
}



/***********************************************************
*name:       PrjVersionMsg(void)
*input:      void 
*output:     void
*update:     2011-11-27 
*state:      allright

*description:   
          打印工程信息，主要工程的编译时间和工程名和软件版本号。
*history:
                                
************************************************************/
void PrjVersionMsg(void)
{
    printfStr("\r\nLib Version :\n");
    printfStr(GeLibVersion());
    printfStr("\r\nLib create date :\n");
    printfStr(GetLibCreatDate());
    printfStr("\r\nLib create time :\n");
    printfStr(GetLibCreatTime());
    printfStr("Inital end.\n");
}

/***********************************************************
*name:       InitExtDevices(void)
*input:      void 
*output:     void
*update:     2011-11-27 
*state:      allright

*description:   
        初始化外围设备，例如tuner,声音的控制，电源指示灯的状态。
*history:
                                
************************************************************/
void InitExtDevices(void)
{
    //LED

	//SPI屏
	#ifdef SpiInitPannelEn
    SPI_TM035KDH08_Pannel_Initial(_24BIT_RGB_DEN,0x75);//interface:24BIT_RGB_DEN(default),default VcomVal:0x75
    #endif

	#ifdef CpuInitPannelEn
    CPU_HX8357C_16Bit_Pannel_Initial(AMT_TYPE);
	#endif

    printfStr("InitExtDevices\n");

}




/***********************************************************
*name:       InitSysWorkVariable(void)
*input:      void
*output:     void 
*update:     2011-11-27 
*state:      allright

*description:   
           初始化系统工作变量。
*history:
                                
************************************************************/
void InitSysWorkVariable(void)
{  
     printfStr("**********InitSysWorkVariable*********\n");
     InitGlobalVariables();

	 #ifdef FlashEn
	 AutoDetectFlashType();
	 #endif
	 
     ReadSetting(); 
}


/***********************************************************
*name:       InitSystem(void)
*input:      void
*output:     void 
*update:     2011-11-27 
*state:      allright

*description:   
           初始化系统。
*history:
                                
************************************************************/
void InitSystem(void)
{	
	ConfigMcuCtrl();

	InitMcu();

	InitSysWorkVariable();
	
	InitExtDevices();

	InitARKChip();

	PrjVersionMsg();

}


