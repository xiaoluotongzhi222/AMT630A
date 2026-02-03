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
UCHAR* CODE QuicklySaturationMenuStr[]=
{
    "COLOR",
};



/*****************************************************************
                            String
*****************************************************************/
UCHAR * QuicklySaturationMenu_TitelStr(void)
{
    return QuicklySaturationMenuStr[g_sysSetting.Osd.curlanguage];
}



/*****************************************************************
                           Function
*****************************************************************/
AdjustType QuicklySaturationMenu_CheckCondition(void)
{
    AdjustType XDATA adjust ={0,0,0};
	adjust.Flags |= osdVisible;
	
	printfStr("QuicklySaturationMenu_CheckCondition");
	return adjust;
}



BOOL QuicklySaturationMenuItem_DrawStyle(void)
{
    printfStr("SaturationMenuItem_DrawStyle");
	OsdWndClear(0X00, 0X00, 0X00, 0X1E);
    return 0;
}



WORD GetQuicklySaturationVal(void)
{
     //printfStr("GetSaturationVal");
     return g_sysSetting.Video.saturation;
}


BOOL AdjustQuicklySaturation(UCHAR opratComd)
{         	
    if(opratComd == COMD_Saturation) 
    {     
		  #ifdef KeyDetectEn
		  #if KEY_TYPE == DIANWEIQI_KEY
		  UCHAR XDATA DianWeiQiAdjustVal;
		  UINT XDATA tmpDianWeiQiAdjustVal;
		  if(0<=g_sysSetting.Video.saturation<=MAX_VALUE) 
		  {
			 DianWeiQiAdjustVal = g_ucDianWeiQiVal;
			 g_sysSetting.Video.saturation = DianWeiQiAdjustVal;

			 if(g_sysSetting.Video.saturation > DianWeiQiAdjMaxStep)
			 {
			    g_sysSetting.Video.saturation = DianWeiQiAdjMaxStep;
			 }
			tmpDianWeiQiAdjustVal = g_sysSetting.Video.saturation;
			tmpDianWeiQiAdjustVal*=MAX_VALUE;

			#if DianWeiQiAdjDir == ForwardAdj
			g_sysSetting.Video.saturation = (UCHAR)(tmpDianWeiQiAdjustVal/DianWeiQiAdjMaxStep);
			#elif DianWeiQiAdjDir == ReverseAdj
			g_sysSetting.Video.saturation = MAX_VALUE - (UCHAR)(tmpDianWeiQiAdjustVal/DianWeiQiAdjMaxStep);
			#endif
		  } 
		  #else  //#if KEY_TYPE == GPIO_KEY
		  g_sysSetting.Video.saturation++;
		  if(g_sysSetting.Video.saturation >MAX_VALUE)
		  {
		     g_sysSetting.Video.saturation = 0;
		  }
		  #endif  //#if KEY_TYPE == DIANWEIQI_KEY
		  #endif // #ifdef KeyDetectEn
		  
		  //printf("saturation Adjust Value = %d",g_sysSetting.Video.saturation);
    }
	else
	{    
	      switch(opratComd)
	      { 
	         case COMD_SaturationInc:
			 	  if(g_sysSetting.Video.saturation<MAX_VALUE)
				  {
				      g_sysSetting.Video.saturation++;
				  }
			 	  break;

			case COMD_SaturationDec:
				 if(g_sysSetting.Video.saturation>0)
				 {
				      g_sysSetting.Video.saturation--;
				 } 
				 break;

			default:
				break;
	      } 
	}
	return 1;
}


BOOL ExectQuicklySaturation(void)
{
   //printfStr("ExectSaturation");
    while(g_ucAdjustSaturationVal != g_sysSetting.Video.saturation)
   {
       if(g_sysSetting.Video.saturation > g_ucAdjustSaturationVal)
       {
           g_ucAdjustSaturationVal++;
       }
	   else
	   {
	      g_ucAdjustSaturationVal--;
	   }
       SATURATION_REG=  DataCurve(SATURATION_MIN,g_ucSaturation,SATURATION_MAX, g_ucAdjustSaturationVal,MAX_VALUE);
	   DelayUs(200);
   }   
   return 1;
}


/*****************************************************************
                          Item value table
*****************************************************************/
DrawNumberType CODE Number_QuicklySaturation[]=
{   
	{0,MAINMENU_ITEM_GUAGE,MAINMENU_ITEM_NUMFORECOLOR,MAINMENU_ITEM_NUMBACKCOLOR,MAINMENU_ITEM_NUMFORECOLOR,MAINMENU_ITEM_NUMBACKCOLOR, GetQuicklySaturationVal,osdDecNum|osdEnd},
};
DrawGuageType CODE Gugae_QuicklySaturation[]=
{   
    {1,1,MAINMENU_ITEM_GUAGEFORECOLOR,MAINMENU_ITEM_GUAGEBACKCOLOR,MAINMENU_ITEM_GUAGEFORECOLOR,MAINMENU_ITEM_GUAGEBACKCOLOR, MAX_VALUE,GetQuicklySaturationVal,osdEnd},
};

ItemValueType CODE QuicklySaturationMenuItemVal_QuicklySaturation[]=
{
     {
	      Number_QuicklySaturation,
	      Gugae_QuicklySaturation,
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
TitelType CODE QuicklySaturationMenuItem_QuicklySaturationTitelTab[]=
{
   {0,1,MAINMENU_ITEM_TITELFORECOLOR,MAINMENU_ITEM_TITELBACKCOLOR,MAINMENU_ITEM_TITELFORECOLOR,MAINMENU_ITEM_TITELBACKCOLOR,DWT_Text,QuicklySaturationMenu_TitelStr,osdEnd},
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

