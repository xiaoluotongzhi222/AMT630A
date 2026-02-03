/***********************************************************************
*Copyright (C) 2005 深圳艾科创新有限公司产品应用一部
* All rights reserved.

*File name: 　 ArkRun.c
*Version:    　0.1
*Author:       cjinzong
*update:       2011-11-26

*Description:
              系统各模块运行逻辑。
*History:  

************************************************************************/
#define _EVENT_HANDLE_C_

/* include head file s*/
#include "DataType.h"
#include "SystemConfig.h"
#include "Global.h"
#include "MsgMap.h"
#include "Osd_Menu.h"
#include "configLcdPara.h"
#include "EventHandle.h"
#include "Debug.h"
#include "Delay.h"
#include "VideoProc.h"
#include "sysPower.h" 
#include "AMT_Reg.h"
#include "AMT_Drv.h"
#include "AMT_Mcu.h"



/***********************************************************
*name:       OsdMsgHandle(MSG curMsg)
*input:      curMsg
*output:     void 

*update:     2011-11-27 
*state:      allright

*description:   
          处理用户消息，主要是按键和遥控器。
          需要考虑此处是OSD的接口，并且可以实现OSD的风格切换。
*history:
                                
************************************************************/
void  OsdMsgHandle(MSG curMsg)
{
    UCHAR ucComd= COMD_Nothing;
	
    ucComd = KeyMsgProcess(curMsg);	

	if(ucComd!= COMD_Nothing)
	{
	  g_ucContNoSignalSecond = 0X00;
      g_sysSetting.Osd.storageTime = 0X00;
	}
	
    MenuProcessKey(ucComd);
}


/***********************************************************
*name:       SignalMsgHandle(MSG curMsg)
*input:      curMsg
*output:     void 

*update:     2011-11-27 
*state:      allright

*description:   
          处理信号的消息，主要有从无信号到有信号，从有信号到无信号
          产生的消息，信号优先级消息 等等。。
*history:
                                
************************************************************/
void  SignalMsgHandle(MSG curMsg)
{

     if(curMsg == MSG_SIGNAL_OK)
     {
        printfStr("MSG_SIGNAL_OK");
		
        #ifdef NoSignalBLOffEn
	    ExectComd(COMD_TurnOnBackLight); 
		#endif

		#ifdef LogoEn 
		g_bLogoDisplayFlag = 0;
		
		#if (LOGO_DISP_MODE == NOSIGNAL_DISP_LOGO)
		ExectComd(COMD_ClearLogo); 
		#endif
		
		#endif

     }

	 if(curMsg == MSG_NO_SIGNAL)
	 {  
	    printfStr("MSG_NO_SIGNAL");

	    #ifdef NoSignalBLOffEn
	    ExectComd(COMD_TurnOffBackLight);
		#endif

		#ifdef LogoEn 
		g_bLogoDisplayFlag = 1;
		
		#if (LOGO_DISP_MODE == NOSIGNAL_DISP_LOGO)
		ExectComd(COMD_RedrawLogo); 
		#endif
		
		#endif
	 }
}
/***********************************************************
*name:       ColorSysMsgHandle(MSG curMsg)
*input:      curMsg
*output:     void 

*update:     2011-11-27 
*state:      allright

*description:   
         处理图像效果消息，主要是根据当前通道的图像制式来配置
         相应的图像参数。 
*history:
                                
************************************************************/
void  ColorSysMsgHandle(MSG curMsg)
{
     if(curMsg == MSG_CONFIG_COLOR_SYS)
     {   
		ConfigColorSysDynPara(g_sysSetting.Video.colorSys); 
     }
}

/***********************************************************
*name:       TimeMsgHandle(MSG curMsg)
*input:      curMsg
*output:     void 

*update:     2011-11-27 
*state:      allright

*description:   
         处理系统设置时间消息，主要有定时开关机，定时睡眠模式。
         
*history:
                                
************************************************************/
void  TimeMsgHandle(MSG curMsg)
{
			
    if(MSG_OSD_EXIT == curMsg) 
    {
        printfStr("MSG_OSD_EXIT");
        MenuProcessKey(COMD_OsdExit);
    }

	if(MSG_OSD_STORAGE == curMsg) 
    {   
        printfStr("MSG_OSD_STORAGE");
        MenuProcessKey(COMD_OsdStorage);
    }
		
	if(MSG_NOSIGNALPOWEROFF == curMsg) 
    {   
        printfStr("MSG_NOSIGNALPOWEROFF");
		MenuProcessKey(COMD_Power);
    }
}


/***********************************************************
*name:       BatteryAdcMsgHandle(MSG curMsg)
*input:      curMsg
*output:     void 

*update:     2011-11-27 
*state:      allright

*description:   
         处理系统电池的实时电压消息。
         
*history:
                                
************************************************************/
void  BatteryAdcMsgHandle(MSG curMsg)
{
    if(MSG_BATTERYADC == curMsg) 
    {
        printfStr("MSG_BATTERYADC");
        MenuProcessKey(COMD_BatteryAdc);
    }
}



/***********************************************************
*name:       UserDefinedMsgHandle(MSG curMsg)
*input:      curMsg
*output:     void 

*update:     2011-11-27 
*state:      allright

*description:   
        处理用户自定义消息
         
*history:
                                
************************************************************/
void  UserDefinedMsgHandle(MSG curMsg)
{

	if(MSG_TURNON_BACKLIGHT == curMsg) 
    {   
        printfStr("MSG_TURNON_BACKLIGHT");
        ExectComd(COMD_TurnOnBackLight);
    }
		
    if(MSG_TURNOFF_BACKLIGHT == curMsg) 
    {   
        printfStr("MSG_TURNOFF_BACKLIGHT");
        ExectComd(COMD_TurnOffBackLight);
    }    
}

