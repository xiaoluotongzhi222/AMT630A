#define _OSD_SATURATION_MENU_C_



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
UCHAR* CODE SaturationMenuStr[]=
{
    "COLOR",
};


/*****************************************************************
                            String
*****************************************************************/
UCHAR * SaturationMenu_TitelStr(void)
{
    return SaturationMenuStr[g_sysSetting.Osd.curlanguage];
}



/*****************************************************************
                           Function
*****************************************************************/
AdjustType SaturationMenu_CheckCondition(void)
{
    AdjustType XDATA adjust ={0,0,0};
	
	adjust.Flags |= osdVisible;
	
	//printfStr("SaturationMenu_CheckCondition");
	return adjust;
}



BOOL SaturationMenuItem_DrawStyle(void)
{
    //printfStr("SaturationMenuItem_DrawStyle");
	OsdWndClear(0X00, 0X00, 0X00, 0X1E);
    return 0;
}


WORD GetSaturationVal(void)
{
     //printfStr("GetSaturationVal");
     return g_sysSetting.Video.saturation;
}


BOOL AdjustSaturation(UCHAR opratComd)
{
    if(opratComd == COMD_IncValue)
    {
        
		  if(g_sysSetting.Video.saturation<MAX_VALUE)
		  {
		      g_sysSetting.Video.saturation++;
		  } 
		  //printf("Inc Value ++ = %d",g_sysSetting.Video.contrast);
    }
	if(opratComd == COMD_DecValue)
	{
	    
		  if(g_sysSetting.Video.saturation>0)
		  {
		      g_sysSetting.Video.saturation--;
		  } 
		 //printf("Dec Value -- =%d",g_sysSetting.Video.contrast);
	}
	return 1;
}


BOOL ExectSaturation(void)
{
   //printfStr("ExectSaturation");
   SATURATION_REG=  DataCurve(SATURATION_MIN,g_ucSaturation,SATURATION_MAX, g_sysSetting.Video.saturation,MAX_VALUE);
   return 1;
}


/*****************************************************************
                          Item value table
*****************************************************************/
DrawNumberType CODE Number_Saturation[]=
{
	{0,MAINMENU_ITEM_GUAGE,MAINMENU_ITEM_NUMFORECOLOR,MAINMENU_ITEM_NUMBACKCOLOR,MAINMENU_ITEM_NUMFORECOLOR,MAINMENU_ITEM_NUMBACKCOLOR, GetSaturationVal,osdDecNum|osdEnd},
};
DrawGuageType CODE Gugae_Saturation[]=
{
    {1,1,MAINMENU_ITEM_GUAGEFORECOLOR,MAINMENU_ITEM_GUAGEBACKCOLOR,MAINMENU_ITEM_GUAGEFORECOLOR,MAINMENU_ITEM_GUAGEBACKCOLOR, MAX_VALUE,GetSaturationVal,osdEnd},
};

ItemValueType CODE SaturationMenuItemVal_Saturation[]=
{
     {
	      Number_Saturation,
	      Gugae_Saturation,
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
TitelType CODE SaturationMenuItem_SaturationTitelTab[]=
{
   {0,1,MAINMENU_ITEM_TITELFORECOLOR,MAINMENU_ITEM_TITELBACKCOLOR,MAINMENU_ITEM_TITELFORECOLOR,MAINMENU_ITEM_TITELBACKCOLOR,DWT_Text,SaturationMenu_TitelStr,osdEnd},
};



/*****************************************************************
                          Menu Icon table
*****************************************************************/



/*****************************************************************
                         Menu  Titel table
*****************************************************************/


