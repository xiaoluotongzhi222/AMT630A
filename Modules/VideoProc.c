/*******************************************************************************
*Copyright (C) 2005 深圳艾科创新有限公司产品应用一部
* All rights reserved.

*File name: 　 VideoProc.c	  
*Version:      0.1
*update:       2011-12-16
*Description:
  		   视频处理文件
  		  
*History:  Jordan.chen   2011/12/16    0.1    build  this  moudle
******************************************************************************/
#define _VIDEO_CHIP_C_

#include "DataType.h"
#include "systemConfig.h"
#include "global.h"
#include "configlcdpara.h"
#include "Videoproc.h"
#include "Debug.h"
#include "AMT_Mcu.h"
#include "Mcu.h"
#include "interrupt.h"
#include "Delay.h"
#include "MsgMap.h"
#include "Osd_Menu.h"
#include "Osd_MenuPage.h"
#include "AMT_Drv.h"
#include "AMT_Reg.h"




/****************************************************************************
*name:   ConfigVideoInputSource(InputSourceType curSource)
*input:  curSource      
*output: void

*description:
      此函数选择视频通道。

*history: yshuizhou   2011/12/06    0.1    buil   this  function
*****************************************************************************/
void ConfigVideoInputSource(InputSourceType curSource)
{
   	switch(curSource)
   	{
   	   case INPUT_AV:
	   	    SelSOGNULLIn();
	   	    SelAvChannel();
			break;

	   default:
	  	    break;
   	}
}


/****************************************************************************
*name:  CheckColorSys(void)
*input:   void      
*output: void

*description:

*history: Jordan.chen   2011/12/06    0.1    buil   this  function
*****************************************************************************/
BOOL CheckColorSys(void)
{
    UCHAR XDATA i;
	
    g_ucColorSys = 0XFF;
    g_ucStableTime = 0X00;
	
	for(i=0;i<40;i++) 
	{   
	    DelayMs(20);
		if(g_ucColorSys != 0XFF)
		{  
			return TRUE;
			break;
		}
		
	}
	return FALSE;
}



/****************************************************************************
*name:   InitARKChip(void)
*input:  void      
*output: void

*description:
      初始化ARK CHIP 函数。

*history: Jordan.chen   2011/12/07    0.1    buil   this  function
*****************************************************************************/	
void InitARKChip(void)
{
	printfStr("**********InitARKChip*********\n");
	
	InitGlobalPara();

	MainInterruptEn();
	
	SetVideoChSelEn();
	
	InitOsdBlock();
	
	InitOSD();

	InitAdc();	

	#ifdef NoSignalBLOffEn
	InitNoSignalBLOff();
	#endif
}



