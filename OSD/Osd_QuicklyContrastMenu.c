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
UCHAR* CODE QuicklyContrastMenuStr[]=
{
    "CONTRAST   ",
};



/*****************************************************************
                            String
*****************************************************************/
UCHAR * CODE QuicklyContrastMenu_TitelStr(void)
{
    return QuicklyContrastMenuStr[g_sysSetting.Osd.curlanguage];
}



/*****************************************************************
                           Function
*****************************************************************/
AdjustType QuicklyContrastMenu_CheckCondition(void)
{
    AdjustType XDATA adjust={0,0,0};
	adjust.Flags |= osdVisible;
	
	//printfStr("QuicklyContrastMenu_CheckCondition");
	return adjust;
}





BOOL QuicklyContrastMenuItem_DrawStyle(void)
{
    //printfStr("QuicklyContrastMenuItem_DrawStyle");
    OsdWndClear(0X00, 0X00, 0X00, 0X1E);
    return 0;
}



WORD GetQuicklyContrastVal(void)
{
     //printfStr("GetContrastVal");
     return g_sysSetting.Video.contrast;
}


BOOL AdjustQuicklyContrast(UCHAR opratComd)
{   
 
    if(opratComd == COMD_Contrast)  
    {     
          #ifdef KeyDetectEn
		  #if KEY_TYPE == DIANWEIQI_KEY
		  UCHAR XDATA DianWeiQiAdjustVal;
		  UINT XDATA tmpDianWeiQiAdjustVal;
		  if(0<=g_sysSetting.Video.contrast<=MAX_VALUE)
		  {
			 DianWeiQiAdjustVal = g_ucDianWeiQiVal;
			 g_sysSetting.Video.contrast = DianWeiQiAdjustVal;

			 if(g_sysSetting.Video.contrast > DianWeiQiAdjMaxStep)
			 {
			    g_sysSetting.Video.contrast = DianWeiQiAdjMaxStep;
			 }
			tmpDianWeiQiAdjustVal = g_sysSetting.Video.contrast;
			tmpDianWeiQiAdjustVal*=MAX_VALUE;
			
			#if DianWeiQiAdjDir == ForwardAdj
			g_sysSetting.Video.contrast = (UCHAR)(tmpDianWeiQiAdjustVal/DianWeiQiAdjMaxStep);
			#elif DianWeiQiAdjDir == ReverseAdj
			g_sysSetting.Video.contrast = MAX_VALUE - (UCHAR)(tmpDianWeiQiAdjustVal/DianWeiQiAdjMaxStep);
			#endif
		  } 
		  #else  // #if KEY_TYPE = GPIO_KEY
		  g_sysSetting.Video.contrast++;
		  if(g_sysSetting.Video.contrast >MAX_VALUE)
		  {
		     g_sysSetting.Video.contrast = 0;
		  }
		  #endif  //  #if KEY_TYPE == DIANWEIQI_KEY
		  #endif  // #ifdef KeyDetectEn

		  //printf("contrast Adjust Value = %d",g_sysSetting.Video.contrast);
    }
	else 
	{    
	      switch(opratComd)
	      { 
	         case COMD_ContrastInc:
			 	  if(g_sysSetting.Video.contrast<MAX_VALUE)
				  {
				      g_sysSetting.Video.contrast++;
				  }
			 	  break;

			case COMD_ContrastDec:
				 if(g_sysSetting.Video.contrast>0)
				 {
				      g_sysSetting.Video.contrast--;
				 } 
				 break;

			default:
				break;
	      } 
	}
	return 1;
}


BOOL ExectQuicklyContrast(void)
{
   //printfStr("ExectContrast");
   while(g_ucAdjustContrastVal != g_sysSetting.Video.contrast)
   {
       if(g_sysSetting.Video.contrast > g_ucAdjustContrastVal)
       {
           g_ucAdjustContrastVal++;
       }
	   else
	   {
	      g_ucAdjustContrastVal--;
	   }
       CONTRAST_REG  =  DataCurve(CONTRAST_MIN,g_ucContrast,CONTRAST_MAX, g_ucAdjustContrastVal,MAX_VALUE);
	   DelayUs(200);
   }   
   return 1;
}


/*****************************************************************
                          Item value table
*****************************************************************/
DrawNumberType CODE Number_QuicklyContrast[]=
{
    {0,MAINMENU_ITEM_GUAGE,MAINMENU_ITEM_NUMFORECOLOR,MAINMENU_ITEM_NUMBACKCOLOR,MAINMENU_ITEM_NUMFORECOLOR,MAINMENU_ITEM_NUMBACKCOLOR, GetQuicklyContrastVal,osdDecNum|osdEnd},
};

DrawGuageType CODE Gugae_QuicklyContrast[]=
{
    {1,1,MAINMENU_ITEM_GUAGEFORECOLOR,MAINMENU_ITEM_GUAGEBACKCOLOR,MAINMENU_ITEM_GUAGEFORECOLOR,MAINMENU_ITEM_GUAGEBACKCOLOR, MAX_VALUE,GetQuicklyContrastVal,osdEnd},
};


ItemValueType CODE QuicklyContrastMenuItemVal_QuicklyContrast[]=
{
     {
	      Number_QuicklyContrast,
	      Gugae_QuicklyContrast,
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
TitelType CODE QuicklyContrastMenuItem_QuicklyContrastTitelTab[]=
{
   {0,1,MAINMENU_ITEM_TITELFORECOLOR,MAINMENU_ITEM_TITELBACKCOLOR,MAINMENU_ITEM_TITELFORECOLOR,MAINMENU_ITEM_TITELBACKCOLOR,DWT_Text,QuicklyContrastMenu_TitelStr,osdEnd},
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

