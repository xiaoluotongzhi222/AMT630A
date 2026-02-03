#include "DataType.h"
#include "SystemConfig.h"
#include "Global.h"
#include "MsgMap.h"
#include "sysWorkPara.h"
#include "sysPower.h" 
#include "videoProc.h"
#include "configLCDPara.h"
#include "Debug.h"
#include "Delay.h"
#include "AMT_Reg.h"
#include "AMT_Drv.h"
#include "AMT_Mcu.h"
#include "Osd_Menu.h"
#include "Osd_MenuPage.h"
#include "Osd_BitMapFontDat.h"
#include "DianWeiQiKeyPad.h"




/*****************************************************************
                            Text
*****************************************************************/
UCHAR* CODE QuicklyBrightnessMenuStr[]=
{
    "BRIGHT",
};



/*****************************************************************
                            String
*****************************************************************/
UCHAR * CODE QuicklyBrightnessMenu_TitelStr(void)
{
    return QuicklyBrightnessMenuStr[g_sysSetting.Osd.curlanguage];
}


/*****************************************************************
                           Function
*****************************************************************/
AdjustType QuicklyBrightnessMenu_CheckCondition (void)
{
	AdjustType XDATA adjust={0,0,0};
	adjust.Flags |= osdVisible;
	
	printfStr("QuicklyBrightnessMenu_CheckCondition");
	return adjust;
}



BOOL QuicklyBrightnessMenuItem_DrawStyle(void)
{
	//printfStr("QuicklyBrightnessMenuItem_DrawStyle");
	OsdWndClear(0X00, 0X00, 0X00, 0X1E);
	return 0;
}


WORD GetQuicklyBrightnessVal(void)
{
     //printfStr("GetBrightnessVal");
     return g_sysSetting.Video.brigthness;
}


BOOL AdjustQuicklyBrightness(UCHAR opratComd)
{

    if(opratComd == COMD_Brightness)
    {     
          #ifdef KeyDetectEn
		  #if KEY_TYPE == DIANWEIQI_KEY
		  UCHAR XDATA DianWeiQiAdjustVal;
		  UINT XDATA tmpDianWeiQiAdjustVal;
		  
		  if(0<=g_sysSetting.Video.brigthness<=MAX_VALUE)
		  {
			 DianWeiQiAdjustVal = g_ucDianWeiQiVal;			 
			 g_sysSetting.Video.brigthness = DianWeiQiAdjustVal;			 
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
		  } 
		  #else  //  KEY_TYPE == GPIO_KEY
		  g_sysSetting.Video.brigthness++;
		  if(g_sysSetting.Video.brigthness >MAX_VALUE)
		  {
		     g_sysSetting.Video.brigthness = 0;
		  }
		  #endif //  #if KEY_TYPE == DIANWEIQI_KEY
		  #endif //#ifdef KeyDetectEn
		  
		  //printf("brigthness Adjust Value = %d",g_sysSetting.Video.brigthness);
	}
	else 
	{    
	      switch(opratComd)
	      { 
	         case COMD_BrightnessInc:
			 	  if(g_sysSetting.Video.brigthness<MAX_VALUE)
				  {
				      g_sysSetting.Video.brigthness++;
				  }
			 	  break;

			case COMD_BrightnessDec:
				 if(g_sysSetting.Video.brigthness>0)
				 {
				      g_sysSetting.Video.brigthness--;
				 } 
				 break;

			default:
				break;
	      } 
	}
	return 1;
}


BOOL ExectQuicklyBrightness(void)
{
   //printfStr("ExectBrightness");
   while(g_ucAdjustBrightnessVal != g_sysSetting.Video.brigthness)
   {
       if(g_sysSetting.Video.brigthness > g_ucAdjustBrightnessVal)
       {
            g_ucAdjustBrightnessVal++;
       }
       else
       {
	   		g_ucAdjustBrightnessVal--;
       }
       BRIGHT_REG    =  DataCurve(BRIGHT_MIN,g_ucbrightness,BRIGHT_MAX, g_ucAdjustBrightnessVal,MAX_VALUE);	   
       DelayUs(200);
   }
   return 1;
}


/*****************************************************************
                          Item value table
*****************************************************************/
DrawNumberType CODE Number_QuicklyBrightness[]=
{
	{0,MAINMENU_ITEM_GUAGE,MAINMENU_ITEM_NUMFORECOLOR,MAINMENU_ITEM_NUMBACKCOLOR,MAINMENU_ITEM_NUMFORECOLOR,MAINMENU_ITEM_NUMBACKCOLOR, GetQuicklyBrightnessVal,osdDecNum|osdEnd},
};
DrawGuageType CODE Gugae_QuicklyBrightness[]=
{
	{1,1,MAINMENU_ITEM_GUAGEFORECOLOR,MAINMENU_ITEM_GUAGEBACKCOLOR,MAINMENU_ITEM_GUAGEFORECOLOR,MAINMENU_ITEM_GUAGEBACKCOLOR, MAX_VALUE,GetQuicklyBrightnessVal,osdEnd},
};

ItemValueType CODE QuicklyBrightnessMenuItemVal_QuicklyBrightness[]=
{
     {
	      Number_QuicklyBrightness,
	      Gugae_QuicklyBrightness,
	      NULL,   
	      osdEnd,
     },
};


/*****************************************************************
                          Item Icon table
*****************************************************************/



/*****************************************************************
                         Item  Titel table
*****************************************************************/
TitelType CODE QuicklyBrightnessMenuItem_QuicklyBrightnessTitelTab[]=
{
   {0,1,MAINMENU_ITEM_TITELFORECOLOR,MAINMENU_ITEM_TITELBACKCOLOR,MAINMENU_ITEM_TITELFORECOLOR,MAINMENU_ITEM_TITELBACKCOLOR,DWT_Text,QuicklyBrightnessMenu_TitelStr,osdEnd},
};



/*****************************************************************
                          Menu Icon table
*****************************************************************/



/*****************************************************************
                         Menu  Titel table
*****************************************************************/



/*****************************************************************
                           Item table
*****************************************************************/


/*****************************************************************
                           Menu 
*****************************************************************/


