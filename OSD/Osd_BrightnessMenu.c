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



/*****************************************************************
                            Text
*****************************************************************/
UCHAR* CODE BrightnessMenuStr[]=
{
    "BRIGHT",
};



/*****************************************************************
                            String
*****************************************************************/
UCHAR * CODE BrightnessMenu_TitelStr(void)
{
    return BrightnessMenuStr[g_sysSetting.Osd.curlanguage];
}



/*****************************************************************
                           Function
*****************************************************************/
AdjustType BrightnessMenu_CheckCondition (void)
{
    AdjustType XDATA adjust={0,0,0};
	adjust.Flags |= osdVisible;
	printfStr("BrightnessMenu_CheckCondition");
	return adjust;
}




BOOL BrightnessMenuItem_DrawStyle(void)
{

	//printfStr("BrightnessMenuItem_DrawStyle");
	OsdWndClear(0X00, 0X00, 0X00, 0X1E);
	return 0;
}


WORD GetBrightnessVal(void)
{
     //printfStr("GetBrightnessVal");
     return g_sysSetting.Video.brigthness;
}


BOOL AdjustBrightness(UCHAR opratComd)
{
    if(opratComd == COMD_IncValue)
    {
		  if(g_sysSetting.Video.brigthness<MAX_VALUE)
		  {
		      g_sysSetting.Video.brigthness++;
		  } 
		  //printf("brigthness Inc Value ++ = %d",g_sysSetting.Video.brigthness);
    }
	if(opratComd == COMD_DecValue)
	{
	    
		  if(g_sysSetting.Video.brigthness>0)
		  {
		      g_sysSetting.Video.brigthness--;
		  } 
		 //printf("brigthness Dec Value -- =%d",g_sysSetting.Video.brigthness);
	}
	return 1;
}


BOOL ExectBrightness(void)
{
   //printfStr("ExectBrightness");
   BRIGHT_REG    =  DataCurve(BRIGHT_MIN,g_ucbrightness,BRIGHT_MAX,  g_sysSetting.Video.brigthness,MAX_VALUE);
   return 1;
}


/*****************************************************************
                          Item value table
*****************************************************************/
DrawNumberType CODE Number_Brightness[]=
{
	{0,MAINMENU_ITEM_GUAGE,MAINMENU_ITEM_NUMFORECOLOR,MAINMENU_ITEM_NUMBACKCOLOR,MAINMENU_ITEM_NUMFORECOLOR,MAINMENU_ITEM_NUMBACKCOLOR, GetBrightnessVal,osdDecNum|osdEnd},
};
DrawGuageType CODE Gugae_Brightness[]=
{
	{1,1,MAINMENU_ITEM_GUAGEFORECOLOR,MAINMENU_ITEM_GUAGEBACKCOLOR,MAINMENU_ITEM_GUAGEFORECOLOR,MAINMENU_ITEM_GUAGEBACKCOLOR, MAX_VALUE,GetBrightnessVal,osdEnd},
};


ItemValueType CODE BrightnessMenuItemVal_Brightness[]=
{
     {
	      Number_Brightness,
	      Gugae_Brightness,
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
TitelType CODE BrightnessMenuItem_BrightnessTitelTab[]=
{
   {0,1,MAINMENU_ITEM_TITELFORECOLOR,MAINMENU_ITEM_TITELBACKCOLOR,MAINMENU_ITEM_TITELFORECOLOR,MAINMENU_ITEM_TITELBACKCOLOR,DWT_Text,BrightnessMenu_TitelStr,osdEnd},
};



/*****************************************************************
                          Menu Icon table
*****************************************************************/



/*****************************************************************
                         Menu  Titel table
*****************************************************************/


