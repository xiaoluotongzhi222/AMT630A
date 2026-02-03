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
UCHAR* CODE ContrastMenuStr[]=
{
    "CONTRAST   ",
};



/*****************************************************************
                            String
*****************************************************************/
UCHAR * CODE ContrastMenu_TitelStr(void)
{
    return ContrastMenuStr[g_sysSetting.Osd.curlanguage];
}



/*****************************************************************
                           Function
*****************************************************************/
AdjustType ContrastMenu_CheckCondition(void)
{
    AdjustType XDATA adjust ={0,0,0};
	
	adjust.Flags |= osdVisible;
	
	//printfStr("ContrastMenu_CheckCondition");
	return adjust;
}



BOOL ContrastMenuItem_DrawStyle(void)
{
    //printfStr("ContrastMenuItem_DrawStyle");
    OsdWndClear(0X00, 0X00, 0X00, 0X1E);
    return 0;
}


WORD GetContrastVal(void)
{
     //printfStr("GetContrastVal");
     return g_sysSetting.Video.contrast;
}


BOOL AdjustContrast(UCHAR opratComd)
{
    if(opratComd == COMD_IncValue)
    {
        
		  if(g_sysSetting.Video.contrast<MAX_VALUE)
		  {
		      g_sysSetting.Video.contrast++;
		  } 
		  //printf("Inc Value ++ = %d",g_sysSetting.Video.contrast);
    }
	if(opratComd == COMD_DecValue)
	{
	    
		  if(g_sysSetting.Video.contrast>0)
		  {
		      g_sysSetting.Video.contrast--;
		  } 
		 //printf("Dec Value -- =%d",g_sysSetting.Video.contrast);
	}
	return 1;
}


BOOL ExectContrast(void)
{
   //printfStr("ExectContrast");
   CONTRAST_REG  =  DataCurve(CONTRAST_MIN,g_ucContrast,CONTRAST_MAX, g_sysSetting.Video.contrast,MAX_VALUE);
   return 1;
}


/*****************************************************************
                          Item value table
*****************************************************************/
DrawNumberType CODE Number_Contrast[]=
{
    {0,MAINMENU_ITEM_GUAGE,MAINMENU_ITEM_NUMFORECOLOR,MAINMENU_ITEM_NUMBACKCOLOR,MAINMENU_ITEM_NUMFORECOLOR,MAINMENU_ITEM_NUMBACKCOLOR, GetContrastVal,osdDecNum|osdEnd},
};
DrawGuageType CODE Gugae_Contrast[]=
{
    {1,1,MAINMENU_ITEM_GUAGEFORECOLOR,MAINMENU_ITEM_GUAGEBACKCOLOR,MAINMENU_ITEM_GUAGEFORECOLOR,MAINMENU_ITEM_GUAGEBACKCOLOR, MAX_VALUE,GetContrastVal,osdEnd},
};

ItemValueType CODE ContrastMenuItemVal_Contrast[]=
{
     {
	      Number_Contrast,
	      Gugae_Contrast,
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
TitelType CODE ContrastMenuItem_ContrastTitelTab[]=
{
   {0,1,MAINMENU_ITEM_TITELFORECOLOR,MAINMENU_ITEM_TITELBACKCOLOR,MAINMENU_ITEM_TITELFORECOLOR,MAINMENU_ITEM_TITELBACKCOLOR,DWT_Text,ContrastMenu_TitelStr,osdEnd},
};



/*****************************************************************
                          Menu Icon table
*****************************************************************/



/*****************************************************************
                         Menu  Titel table
*****************************************************************/


