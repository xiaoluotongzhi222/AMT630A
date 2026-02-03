/*******************************************************************************
*Copyright (C) 2005 深圳艾科创新有限公司产品应用一部
* All rights reserved.

*File name: 　 GPIOKeyPad.c	  
*Version:      0.1
*update:       2012-05-31
*Description:
  		   此文件是对GPIO 按键的采集与处理。

*History:  yshuizhou   2012/05/31   0.1    build  this  moudle
******************************************************************************/
#define _GPIO_KEY_PAD_C_

#include "DataType.h"
#include "global.h"
#include "MsgMap.h"
#include "systemConfig.h"
#include "Debug.h"
#include "GPIOKeyPad.h"
#include "AMT_Reg.h"
#include "AMT_Drv.h"
#include "Delay.h"



#ifdef KeyDetectEn 
#if KEY_TYPE == GPIO_KEY


/***********************************************************
*name:     POS_GetGPIOKeyCmd(void)
*input:    non
*return:   返回当前GPIO KEY 按键的宏命令
*update:   2011-12-22
*state:    allright
*description:   
         这个函数获取GPIO KEY 按键按下返回的相关的宏命令。

         
*history:yshuizhou   2012/05/31   0.2    build  this  function	
************************************************************/
UCHAR POS_GetGPIOKeyCmd(void)
{

   static UCHAR XDATA ScanGPIO = 0;
   UINT  XDATA CurrentCmd = NULL_CMD;  
   
   switch(ScanGPIO%GPIO_KEY_COUNT)
   {
      case 0:
	  	    if(GPIO_KEY0 == GPIO_KEY_VALID)
	  	    {
	  	       DelayMs(50);  //消抖动
			   if(GPIO_KEY0 == GPIO_KEY_VALID)
			   {
			      CurrentCmd =  GPIO_KEY0_CMD;
			   }
			   else
			   {
			      ScanGPIO++;
				  g_bKeyRepeatFlg = FALSE;
				  PreKey.PressTime = NULL_TIME;
	              PreKey.KeyMsg = MSG_NULL;
			   }
	  	    }
			else
			{
			      ScanGPIO++;
				  g_bKeyRepeatFlg = FALSE;
				  PreKey.PressTime = NULL_TIME;
	              PreKey.KeyMsg = MSG_NULL;
			}
	        break;
			
	  case 1:
	  	    if(GPIO_KEY1 == GPIO_KEY_VALID)
	  	    {
	  	       DelayMs(50);  //消抖动
			   if(GPIO_KEY1 == GPIO_KEY_VALID)
			   {
			      CurrentCmd =  GPIO_KEY1_CMD;
			   }
			   else
			   {
			      ScanGPIO++;
				  g_bKeyRepeatFlg = FALSE;
				  PreKey.PressTime = NULL_TIME;
	              PreKey.KeyMsg = MSG_NULL;
			   }
	  	    }
			else
			{
			      ScanGPIO++;
				  g_bKeyRepeatFlg = FALSE;
				  PreKey.PressTime = NULL_TIME;
	              PreKey.KeyMsg = MSG_NULL;
			}
	  	    break;
			
	  case 2:
	  	    if(GPIO_KEY2 == GPIO_KEY_VALID)
	  	    {
	  	       DelayMs(50);  //消抖动
			   if(GPIO_KEY2 == GPIO_KEY_VALID)
			   {
			      CurrentCmd =  GPIO_KEY1_CMD;
			   }
			   else
			   {
			      ScanGPIO++;
				  g_bKeyRepeatFlg = FALSE;
				  PreKey.PressTime = NULL_TIME;
	              PreKey.KeyMsg = MSG_NULL;
			   }
	  	    }
			else
			{
			      ScanGPIO++;
				  g_bKeyRepeatFlg = FALSE;
				  PreKey.PressTime = NULL_TIME;
	              PreKey.KeyMsg = MSG_NULL;
			}
	  	    break;

      default:
	  	    break;	
   }

   #if TP3_ADC
   printf("TP3_GPIO >> GPIO Key Macro val = %x", CurrentCmd);
   #endif

   return CurrentCmd;
}



/***********************************************************
*name:     	 POS_TransferGPIOKeyMsg(UCHAR GpioKeyCmd)
*input:      AdcKeyVal
*output:     返回对应按键值的消息
*update:     2012-03-12

*description:   
         这个函数是根据当前按键值在SysKeyCmdMap映射表中查找相应的按键命令。
*history:yshuizhou   2012/03/12    0.2    build  this  function	
************************************************************/
KeyInfor POS_TransferGPIOKeyMsg(UCHAR GpioKeyCmd)
{    
    KeyInfor XDATA Key ={MSG_NULL,NULL_TIME};

	switch(GpioKeyCmd)
	{
      case KEY_MENU:      
	  	   Key.KeyMsg = MSG_UPK_MENU;
		   g_UserInputInfo.Status = inputPress;
	  	   break;
		   
	  case KEY_LEFT:      
	       Key.KeyMsg = MSG_UPK_LEFT;
		   if(PreKey.KeyMsg !=Key.KeyMsg)
		   {
		       PreKey.KeyMsg = Key.KeyMsg;
			   g_UserInputInfo.Status = inputPress;
		   }
		   else
		   {    
		        if(g_bKeyRepeatFlg)
		        {
				   g_UserInputInfo.Status = inputHold;
		        }
                else
                {
	                if(++PreKey.PressTime == RepeatTime)
			        {
			            g_bKeyRepeatFlg = TRUE;
			        }
					Key.KeyMsg = MSG_NULL;
                }
		   }
	  	   break;
		   
	  case KEY_RIGHT:      
	        Key.KeyMsg = MSG_UPK_RIGHT;
		   	if(PreKey.KeyMsg !=Key.KeyMsg)
		    {
		       PreKey.KeyMsg = Key.KeyMsg;
			   g_UserInputInfo.Status = inputPress;
		    }
		    else
		    {    
		        if(g_bKeyRepeatFlg)
		        {
				   g_UserInputInfo.Status = inputHold;
		        }
                else
                {
	                if(++PreKey.PressTime == RepeatTime)
			        {
			            g_bKeyRepeatFlg = TRUE;
			        }
					Key.KeyMsg = MSG_NULL;
                }
		   }
	  	    break;

	  case KEY_BRIGHTNESS:      
	       Key.KeyMsg = MSG_UPK_BRIGHTNESS;
		   if(PreKey.KeyMsg !=Key.KeyMsg)
		   {
		       PreKey.KeyMsg = Key.KeyMsg;
			   g_UserInputInfo.Status = inputPress;
		   }
		   else
		   {    
		        if(g_bKeyRepeatFlg)
		        {
				   g_UserInputInfo.Status = inputHold;
		        }
                else
                {
	                if(++PreKey.PressTime == RepeatTime)
			        {
			            g_bKeyRepeatFlg = TRUE;
			        }
					Key.KeyMsg = MSG_NULL;
                }
		   }
	  	   break;

	  case KEY_CONTRAST:      
	       Key.KeyMsg = MSG_UPK_CONTRAST;
		   if(PreKey.KeyMsg !=Key.KeyMsg)
		   {
		       PreKey.KeyMsg = Key.KeyMsg;
			   g_UserInputInfo.Status = inputPress;
		   }
		   else
		   {    
		        if(g_bKeyRepeatFlg)
		        {
				   g_UserInputInfo.Status = inputHold;
		        }
                else
                {
	                if(++PreKey.PressTime == RepeatTime)
			        {
			            g_bKeyRepeatFlg = TRUE;
			        }
					Key.KeyMsg = MSG_NULL;
                }
		   }
	  	   break;

	  case KEY_SATURATION:      
	       Key.KeyMsg = MSG_UPK_SATURATION;
		   if(PreKey.KeyMsg !=Key.KeyMsg)
		   {
		       PreKey.KeyMsg = Key.KeyMsg;
			   g_UserInputInfo.Status = inputPress;
		   }
		   else
		   {    
		        if(g_bKeyRepeatFlg)
		        {
				   g_UserInputInfo.Status = inputHold;
		        }
                else
                {
	                if(++PreKey.PressTime == RepeatTime)
			        {
			            g_bKeyRepeatFlg = TRUE;
			        }
					Key.KeyMsg = MSG_NULL;
                }
		   }
	  	   break;
		   
	   default:
	   	   break;
			   
	}

	#if TP1_KEY
    printf("TP1_KEY >> the KeyMsg is %x:\r\n",Key.KeyMsg);				 
	#endif

	return Key;
}


#endif   //#if KEY_TYPE == DIANWEIQI_KEY
#endif   //#ifdef KeyDetectEn 
