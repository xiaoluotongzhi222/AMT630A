/***********************************************************************
*Copyright (C) 2005 深圳艾科创新有限公司产品应用一部
* All rights reserved.

*File name: 　 GetUserIputMsg.c
*Version:    　0.1
*Author:       cjinzong
*update:       2011-12-09

*Description:
            此文件用来获取按键板和遥控信息。
*History:  

************************************************************************/
#define _GET_USER_MSG_C_


#include "DataType.h"
#include "global.h"
#include "MsgMap.h"
#include "systemConfig.h"
#include "debug.h"
#include "interrupt.h"
#include "GetUserInputMsg.h"
#include "AdcKeyPad.h"
#include "DianWeiQiKeyPad.h"
#include "GPIOKeyPad.h"

/***********************************************************
*name:       GetKeyPadMsg(void)
*input:      void
*output:     void 
*update:     2011-11-27 
*state:      allright

*description:   
           获取按键板的按键值。
*history:
                                
************************************************************/
#ifdef KeyDetectEn
MSG POS_GetKeyPadMsg(void)
{
    UINT  XDATA curKeyVal = NULL_KEY;
	UCHAR curKeyCmd  = NULL_CMD;
	KeyInfor curKey = {MSG_NULL,NULL_TIME}; 
	MSG XDATA curKeyMsg;


	#if KEY_TYPE == ADC_KEY
	if(g_bGetUserInputFlg)
	{
        g_bGetUserInputFlg = 0;
		
		//ADC按键采集到的实际的按键值
		 curKeyVal = POS_GetAdcKeyValue();

		//转出宏命令
		if(NULL_KEY != curKeyVal)
		{
		  g_bReleaseAdcKeyFlg = FALSE;
		  curKeyCmd = POS_TransferAdcKeyCmd(curKeyVal);
		}
		else
		{
		   g_bReleaseAdcKeyFlg = TRUE;
		}

		//转换为应用层的消息
		if(NULL_CMD != curKeyCmd)
		{   
		   curKey  = POS_TransferAdcKeyMsg(curKeyCmd); 
		}
	}
	#endif

    #if KEY_TYPE == GPIO_KEY
	if(g_bGetUserInputFlg)
	{
	    g_bGetUserInputFlg = 0;
		
		//GPIO按键采集到的实际的按键值
		curKeyCmd = POS_GetGPIOKeyCmd();

		if(NULL_CMD != curKeyCmd)
		{   
		   curKey  = POS_TransferGPIOKeyMsg(curKeyCmd); 
		}
	}
    #endif


	#if KEY_TYPE == DIANWEIQI_KEY
	//DianWeiQi按键采集到的实际的按键值
    curKeyVal = POS_GetDianWeiQiKeyValue();

	//转换为应用层的消息
	if(NULL_KEY != curKeyVal)
	{   
	    g_bReleaseAdcKeyFlg = FALSE;
	   	curKey  = POS_TransferDianWeiQiKeyMsg(curKeyVal); 
	}
	else
	{
	    g_bReleaseAdcKeyFlg = TRUE;
	}
	#endif

	curKeyMsg = curKey.KeyMsg;
	return curKeyMsg;
}
#endif

