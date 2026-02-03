#ifndef _MENU_TBL_H__
#define _MENU_TBL_H__


#include "sysPower.h" 
#include "Osd_Menu.h"
#include "Osd_MenuPage.h"
#include "Osd_MenuKeyInterface.h"
#include "Osd_LogoFontDat.h"
#include "Osd_LogoList.c"


///////////////////////////Power Off Page///////////////////////////////////
MenuItemType CODE  PowerOffMenu_ItemTab[]=
{
   {
   	  "PowerOffMenuItem_PowerOff" ,
	   NULL,NULL,    //xpos ypos
   	   
   	   NULL,//check condition
   	   NULL, //draw style
   	   NULL,  //icon 
   	   NULL, //titel 
   	   NULL,   // ItemValue
   	
   	   NULL,   // adjust 
   	   PowerOffSystem,   // exect    
   	   
   	   NULL,   // key comd map
       NULL, //KEY comd count
   	   osdSel,      // flags
   },
};

MenuPageType CODE PowerOffMenu =
{
			"Osd_PowerOffMenu",
			NULL,NULL, //xpos ypos
			NULL,NULL,  //xsize ysize
			NULL,NULL, //foreColor backColor
			NULL,  //osd block id
			
			Osd_RootMenu,   //PrevPage
			Osd_PowerOffMenu,    //currentPage
			Osd_RootMenu,   //NextPage
			
			NULL,//check conditions
			NULL,//style
			NULL,  //ICON
			NULL,//titel
			PowerOffMenu_ItemTab, //items
			sizeof(PowerOffMenu_ItemTab)/sizeof(MenuItemType), //item count
			NULL,  //exe
			NULL,  //time out
			osdInvisible,//flags
};



///////////////////////////Power On Page///////////////////////////////////
MenuItemType CODE  PowerOnMenu_ItemTab[]=
{
   {
   	  "PowerOnMenuItem_PowerOn" ,
	   NULL,NULL,    //xpos ypos
   	   
   	   NULL,//check condition
   	   NULL, //draw style
   	   NULL,  //icon 
   	   NULL, //titel 
   	   NULL, // ItemValue
   	
   	   NULL,   // adjust 
   	   PowerOnSystem,   // exect    
   	   
   	   NULL,   // key comd map
       NULL, //KEY comd count
   	   osdSel,      // flags
   },
};


MenuPageType CODE PowerOnMenu =
{
			"Osd_PowerOnMenu",
			NULL,NULL, //xpos ypos
			NULL,NULL,  //xsize ysize
			NULL,NULL, //foreColor backColor
			NULL,  //osd block id
			
			Osd_RootMenu,   //PrevPage
			Osd_PowerOnMenu,    //currentPage
			Osd_RootMenu,   //NextPage
			
			PowerOnMenu_CheckCondition,//check conditions
			NULL,//style
			NULL,  //ICON
			NULL,//titel
			PowerOnMenu_ItemTab, //items
			sizeof(PowerOnMenu_ItemTab)/sizeof(MenuItemType), //item count
			NULL,  //exe
			NULL,  //time out
			osdInvisible//flags
};




///////////////////////////Root Page///////////////////////////////////
MenuItemType CODE  RootMenu_ItemTab[]=
{
   {
   	  "RootMenuItem" ,
	   NULL,NULL,    //xpos ypos
   	   
   	   NULL,//check condition
   	   NULL, //draw style
   	   NULL,  //icon 
   	   NULL, //titel 
   	   NULL,   // ItemValue
	
   	   NULL,   // adjust 
   	   NULL,   // exect    
   	   
   	   RootMenuItem_KeyComdMap,   // key comd map
   	   sizeof(RootMenuItem_KeyComdMap)/sizeof(KeyComdInterface), //KEY comd count
   	   osdSel,      // flags
   },
};


MenuPageType CODE RootMenu =
{
			"Osd_RootMenu",
			NULL,NULL, //xpos ypos
			NULL,NULL,  //xsize ysize
			NULL,NULL, //foreColor backColor
			NULL,  //osd block id
			
			Osd_RootMenu,   //PrevPage
			Osd_RootMenu,   //currentPage
			Osd_RootMenu,   //NextPage
			
			NULL,//check conditions
			NULL,//style
			NULL,  //ICON
			NULL,//titel
			RootMenu_ItemTab, //items
			sizeof(RootMenu_ItemTab)/sizeof(MenuItemType), //item count
			NULL,  //exe
			NULL,  //time out
			osdInvisible,//flags
};


///////////////////////////BatteryAdc Page///////////////////////////////////
#ifdef LowBaterryDetecEn 
MenuItemType CODE  BatteryAdcMenu_ItemTab[]=
{
   {
   	  "BatteryAdcMenu_ItemTab",
	   NULL,NULL,    //xpos ypos
       NULL,//check condition
   	   NULL, //draw style
   	   NULL,  //icon 
   	   NULL, //titel 
   	   BatteryAdcMenuItemVal_BatteryAdc,   // ItemValue
   	
   	   AdjustBatteryAdc,   // adjust 
   	   NULL,               // exect    
   	   
   	   NULL,           //key comd map
   	   NULL,          //KEY comd count
   	   osdSel,      // flags
   },
};
MenuPageType CODE BatteryAdcMenu =
{
			"Osd_BatteryAdcMenu",
			BATTERYADCMENU_START_X_POS,BATTERYADCMENU_START_Y_POS, //xpos ypos
			0x03,0x01,  //xsize ysize
			GREEN,TRANSPARENCE, //foreColor backColor
			OsdBlock2,  //osd block id
			
			Osd_RootMenu,   //PrevPage
			Osd_BatteryAdcMenu,    //currentPage
			Osd_RootMenu,        //NextPage
			
			BatteryAdcMenu_CheckCondition,//check conditions
			NULL,//style
			NULL,  //ICON
			NULL,//titel
			BatteryAdcMenu_ItemTab, //items
			sizeof(BatteryAdcMenu_ItemTab)/sizeof(MenuItemType), //item count
			NULL,  //exe
			NULL,  //time out
			osdVisible|osdRedraw,//flags
};
#endif


///////////////////////////Logo Page///////////////////////////////////
#ifdef LogoEn
MenuItemType CODE  LogoMenu_ItemTabl[]=
{
   {
   	  "LogoMenuItem_Logo" ,
	   NULL,NULL,    //xpos ypos
   
   	   NULL,//check condition
   	   NULL, //draw style
   	   NULL,  //icon 
   	   NULL, //titel 
   	   NULL,   // ItemValue
   	
   	   NULL,   // adjust 
   	   NULL,   // exect    
   	   
   	   NULL,   // key comd map
   	   NULL, //KEY comd count
   	   osdSel,      // flags
   },
};

MenuPageType CODE LOGO1Menu =
{
		"Osd_Logo1Menu",
		LOGO1MENU_START_X_POS,LOGO1MENU_START_Y_POS, //xpos ypos
		LogoWidth_LOGO1   ,LogoHeighth_LOGO1   , //xsize ysize
		GREEN,TRANSPARENCE, //foreColor backColor
		OsdBlock0,  //osd block id
		
		Osd_RootMenu,   //PrevPage
		Osd_LOGO1Menu, //currentPage
		Osd_RootMenu,   //NextPage
		
		LogoMenu_CheckCondition,//check conditions
		NULL,//style
		LOGO1LogoMenu_IconTab,  //ICON
		NULL,//titel
		LogoMenu_ItemTabl, //items
		sizeof(LogoMenu_ItemTabl)/sizeof(MenuItemType), //item count
		NULL,  //exe
		NULL,  //time out
		osdVisible|osdRedraw,//flags
};


MenuPageType CODE LOGO2Menu =
{
		"Osd_Logo2Menu",
		LOGO2MENU_START_X_POS,LOGO2MENU_START_Y_POS, //xpos ypos
		LogoWidth_LOGO2   ,LogoHeighth_LOGO2   , //xsize ysize
		GREEN,TRANSPARENCE, //foreColor backColor
		OsdBlock0,  //osd block id
		
		Osd_RootMenu,   //PrevPage
		Osd_LOGO2Menu, //currentPage
		Osd_RootMenu,   //NextPage
		
		LogoMenu_CheckCondition,//check conditions
		NULL,//style
		LOGO2LogoMenu_IconTab,  //ICON
		NULL,//titel
		LogoMenu_ItemTabl, //items
		sizeof(LogoMenu_ItemTabl)/sizeof(MenuItemType), //item count
		NULL,  //exe
		NULL,  //time out
		osdVisible|osdRedraw,//flags
};

MenuPageType CODE LOGO3Menu =
{
		"Osd_Logo3Menu",
		LOGO3MENU_START_X_POS,LOGO3MENU_START_Y_POS, //xpos ypos
		LogoWidth_LOGO3   ,LogoHeighth_LOGO3   , //xsize ysize
		GREEN,TRANSPARENCE, //foreColor backColor
		OsdBlock0,  //osd block id
		
		Osd_RootMenu,   //PrevPage
		Osd_LOGO3Menu, //currentPage
		Osd_RootMenu,   //NextPage
		
		LogoMenu_CheckCondition,//check conditions
		NULL,//style
		LOGO3LogoMenu_IconTab,  //ICON
		NULL,//titel
		LogoMenu_ItemTabl, //items
		sizeof(LogoMenu_ItemTabl)/sizeof(MenuItemType), //item count
		NULL,  //exe
		NULL,  //time out
		osdVisible|osdRedraw,//flags
};


MenuPageType CODE LOGO4Menu =
{
		"Osd_Logo4Menu",
		LOGO4MENU_START_X_POS,LOGO4MENU_START_Y_POS, //xpos ypos
		LogoWidth_LOGO4   ,LogoHeighth_LOGO4   , //xsize ysize
		GREEN,TRANSPARENCE, //foreColor backColor
		OsdBlock0,  //osd block id
		
		Osd_RootMenu,   //PrevPage
		Osd_LOGO4Menu, //currentPage
		Osd_RootMenu,   //NextPage
		
		LogoMenu_CheckCondition,//check conditions
		NULL,//style
		LOGO4LogoMenu_IconTab,  //ICON
		NULL,//titel
		LogoMenu_ItemTabl, //items
		sizeof(LogoMenu_ItemTabl)/sizeof(MenuItemType), //item count
		NULL,  //exe
		NULL,  //time out
		osdVisible|osdRedraw,//flags
};

MenuPageType CODE LOGO5Menu =
{
		"Osd_Logo5Menu",
		LOGO5MENU_START_X_POS,LOGO5MENU_START_Y_POS, //xpos ypos
		LogoWidth_LOGO5   ,LogoHeighth_LOGO5   , //xsize ysize
		GREEN,TRANSPARENCE, //foreColor backColor
		OsdBlock0,  //osd block id
		
		Osd_RootMenu,   //PrevPage
		Osd_LOGO5Menu, //currentPage
		Osd_RootMenu,   //NextPage
		
		LogoMenu_CheckCondition,//check conditions
		NULL,//style
		LOGO5LogoMenu_IconTab,  //ICON
		NULL,//titel
		LogoMenu_ItemTabl, //items
		sizeof(LogoMenu_ItemTabl)/sizeof(MenuItemType), //item count
		NULL,  //exe
		NULL,  //time out
		osdVisible|osdRedraw,//flags
};
#endif




///////////////////////////Brightness Page///////////////////////////////////
MenuItemType CODE  BrightnessMenu_ItemTab[]=
{
   {
   	  "BrightnessMenuItem_Brightness" ,
	   NULL,NULL,    //xpos ypos
   	   
   	   NULL,//check condition
   	   BrightnessMenuItem_DrawStyle, //draw style
   	   NULL,  //icon 
   	   BrightnessMenuItem_BrightnessTitelTab, //titel 
   	   BrightnessMenuItemVal_Brightness,   // ItemValue
   	
   	   AdjustBrightness,// adjust 
   	   ExectBrightness,// exect    
   	   
   	   BrightnessMenuItem_KeyComdMap,   // key comd map
   	   sizeof(BrightnessMenuItem_KeyComdMap)/sizeof(KeyComdInterface),//KEY comd count
   	   osdSel,   // flags
   },
};


MenuPageType CODE BrightnessMenu =
{
			"Osd_BrightnessMenu",
			MAINMENU_START_X_POS,MAINMENU_START_Y_POS, //xpos ypos
			MAINMENU_XSIZE,MAINMENU_YSIZE,  //xsize ysize
			MAINMENU_FORECOLOR,MAINMENU_BACKCOLOR, //foreColor backColor
			OsdBlock0,  //osd block id
			
			Osd_RootMenu,   //PrevPage
			Osd_BrightnessMenu,    //currentPage
			Osd_ContrastMenu,   //NextPage
			
			BrightnessMenu_CheckCondition,//check conditions
			NULL,//style
			NULL,  //ICON
			NULL,//titel
			BrightnessMenu_ItemTab, //items
			sizeof(BrightnessMenu_ItemTab)/sizeof(MenuItemType), //item count
			NULL,  //exe
			OSD_DISP_TIME,  //time out
			osdVisible|osdRedraw,//flags
};




///////////////////////////Quickly Brightness Page///////////////////////////////////
MenuItemType CODE  QuicklyBrightnessMenu_ItemTab[]=
{
   {
   	  "QuicklyBrightnessMenuItem_QuicklyBrightness" ,
	   NULL,NULL,    //xpos ypos
   	   
   	   NULL,//check condition
   	   QuicklyBrightnessMenuItem_DrawStyle, //draw style
   	   NULL,  //icon 
   	   QuicklyBrightnessMenuItem_QuicklyBrightnessTitelTab, //titel 
   	   QuicklyBrightnessMenuItemVal_QuicklyBrightness,   // ItemValue
   	
   	   AdjustQuicklyBrightness,   // adjust 
   	   ExectQuicklyBrightness,   // exect    
   	   
   	   RootMenuItem_KeyComdMap,   // key comd map
   	   sizeof(RootMenuItem_KeyComdMap)/sizeof(KeyComdInterface), //KEY comd count
   	   osdSel,      // flags
   },
};


MenuPageType CODE QuicklyBrightnessMenu =
{
			"Osd_QuicklyBrightnessMenu",
			MAINMENU_START_X_POS,MAINMENU_START_Y_POS, //xpos ypos
			MAINMENU_XSIZE,MAINMENU_YSIZE,  //xsize ysize
			MAINMENU_FORECOLOR,MAINMENU_BACKCOLOR, //foreColor backColor
			OsdBlock0,  //osd block id
			
			Osd_RootMenu,   //PrevPage
			Osd_QuicklyBrightnessMenu,    //currentPage
			Osd_RootMenu,   //NextPage
			
			QuicklyBrightnessMenu_CheckCondition,//check conditions
			NULL,//style
			NULL,  //ICON
			NULL,//titel
			QuicklyBrightnessMenu_ItemTab, //items
			sizeof(QuicklyBrightnessMenu_ItemTab)/sizeof(MenuItemType), //item count
			NULL,  //exe
			OSD_DISP_TIME,  //time out
			osdVisible|osdRedraw,//flags
};


///////////////////////////Contrast Page///////////////////////////////////
MenuItemType CODE  ContrastMenu_ItemTab[]=
{
   {
   	  "ContrastMenuItem_Contrast" ,
	   NULL,NULL,    //xpos ypos
   	   
   	   NULL,//check condition
   	   ContrastMenuItem_DrawStyle, //draw style
   	   NULL,  //icon 
   	   ContrastMenuItem_ContrastTitelTab, //titel 
   	   ContrastMenuItemVal_Contrast,   // ItemValue
   	
   	   AdjustContrast,   // adjust 
   	   ExectContrast,   // exect    
   	   
   	   ContrastMenuItem_KeyComdMap,   // key comd map
   	   sizeof(ContrastMenuItem_KeyComdMap)/sizeof(KeyComdInterface), //KEY comd count
   	   osdSel,      // flags
   },
};



MenuPageType CODE ContrastMenu =
{
			"Osd_ContrastMenu",
			NULL,NULL, //xpos ypos
			NULL,NULL,  //xsize ysize
			MAINMENU_FORECOLOR,MAINMENU_BACKCOLOR, //foreColor backColor
			OsdBlock0,  //osd block id
			
			Osd_BrightnessMenu,   //PrevPage
			Osd_ContrastMenu,    //currentPage
			Osd_SaturationMenu,   //NextPage
			
			ContrastMenu_CheckCondition,//check conditions
			NULL,  //style
			NULL,  //ICON
			NULL,//titel
			ContrastMenu_ItemTab, //items
			sizeof(ContrastMenu_ItemTab)/sizeof(MenuItemType), //item count
			NULL,  //exe
			OSD_DISP_TIME,  //time out
			osdVisible,   //flags
};




///////////////////////////Quickly Contrast Page///////////////////////////////////
MenuItemType CODE  QuicklyContrastMenu_ItemTab[]=
{
   {
   	  "QuicklyContrastMenuItem_QuicklyContrast" ,
	   NULL,NULL,    //xpos ypos
   	   
   	   NULL,//check condition
   	   QuicklyContrastMenuItem_DrawStyle, //draw style
   	   NULL, //icon 
   	   QuicklyContrastMenuItem_QuicklyContrastTitelTab, //titel 
   	   QuicklyContrastMenuItemVal_QuicklyContrast,   // ItemValue
   	
   	   AdjustQuicklyContrast,   // adjust 
   	   ExectQuicklyContrast,   // exect    
   	   
   	   RootMenuItem_KeyComdMap,   // key comd map
   	   sizeof(RootMenuItem_KeyComdMap)/sizeof(KeyComdInterface), //KEY comd count
   	   osdSel,      // flags
   },
};



MenuPageType CODE QuicklyContrastMenu =
{
			"Osd_QuicklyContrastMenu",
			MAINMENU_START_X_POS,MAINMENU_START_Y_POS, //xpos ypos
			MAINMENU_XSIZE,MAINMENU_YSIZE,  //xsize ysize
			MAINMENU_FORECOLOR,MAINMENU_BACKCOLOR, //foreColor backColor
			OsdBlock0,  //osd block id
			
			Osd_RootMenu,   //PrevPage
			Osd_QuicklyContrastMenu,    //currentPage
			Osd_RootMenu,//Osd_RootMenu,   //NextPage
			
			QuicklyContrastMenu_CheckCondition,//check conditions
			NULL,//style
			NULL,  //ICON
			NULL,//titel
			QuicklyContrastMenu_ItemTab, //items
			sizeof(QuicklyContrastMenu_ItemTab)/sizeof(MenuItemType), //item count
			NULL,  //exe
			OSD_DISP_TIME,  //time out
			osdVisible|osdRedraw,//flags
};



/////////////////////////// Saturation Page///////////////////////////////////
MenuItemType CODE  SaturationMenu_ItemTab[]=
{
   {
   	  "SaturationMenuItem_Saturation" ,
	   NULL,NULL,    //xpos ypos
   	   
   	   NULL,//check condition
   	   SaturationMenuItem_DrawStyle, //draw style
   	   NULL,  //icon 
   	   SaturationMenuItem_SaturationTitelTab, //titel 
   	   SaturationMenuItemVal_Saturation,   // ItemValue
   	
   	   AdjustSaturation,   // adjust 
   	   ExectSaturation,   // exect    
   	   
   	   SaturationMenuItem_KeyComdMap,   // key comd map
   	   sizeof(SaturationMenuItem_KeyComdMap)/sizeof(KeyComdInterface), //KEY comd count
   	   osdSel,      // flags
   },
};


MenuPageType CODE SaturationMenu =
{
			"Osd_SaturationMenu",
			NULL,NULL, //xpos ypos
			NULL,NULL,  //xsize ysize
			MAINMENU_FORECOLOR,MAINMENU_BACKCOLOR, //foreColor backColor
			OsdBlock0,  //osd block id
			
			Osd_ContrastMenu,   //PrevPage
			Osd_SaturationMenu,    //currentPage
			Osd_RootMenu,       //NextPage
			
			SaturationMenu_CheckCondition,//check conditions
			NULL,//style
			NULL,  //ICON
			NULL,//titel
			SaturationMenu_ItemTab, //items
			sizeof(SaturationMenu_ItemTab)/sizeof(MenuItemType), //item count
			NULL,  //exe
			OSD_DISP_TIME,  //time out
			osdVisible,   //flags
};




///////////////////////////Quickly Saturation Page///////////////////////////////////
MenuItemType CODE  QuicklySaturationMenu_ItemTab[]=
{
   {
   	  "QuicklySaturationMenuItem_QuicklySaturation" ,
	   NULL,NULL,    //xpos ypos
   	   
   	   NULL,//check condition
   	   QuicklySaturationMenuItem_DrawStyle, //draw style
   	   NULL,  //icon 
   	   QuicklySaturationMenuItem_QuicklySaturationTitelTab, //titel 
   	   QuicklySaturationMenuItemVal_QuicklySaturation,   // ItemValue
   	
   	   AdjustQuicklySaturation,   // adjust 
   	   ExectQuicklySaturation,   // exect    
   	   
   	   RootMenuItem_KeyComdMap,   // key comd map
   	   sizeof(RootMenuItem_KeyComdMap)/sizeof(KeyComdInterface), //KEY comd count
   	   osdSel,      // flags
   },
};



MenuPageType CODE QuicklySaturationMenu =
{
			"Osd_QuicklySaturationMenu",
			MAINMENU_START_X_POS,MAINMENU_START_Y_POS, //xpos ypos
			MAINMENU_XSIZE,MAINMENU_YSIZE,  //xsize ysize
			MAINMENU_FORECOLOR,MAINMENU_BACKCOLOR, //foreColor backColor
			OsdBlock0,  //osd block id
			
			Osd_RootMenu,   //PrevPage
			Osd_QuicklySaturationMenu,    //currentPage
			Osd_RootMenu,        //NextPage
			
			QuicklySaturationMenu_CheckCondition,//check conditions
			NULL,//style
			NULL,  //ICON
			NULL,//titel
			QuicklySaturationMenu_ItemTab, //items
			sizeof(QuicklySaturationMenu_ItemTab)/sizeof(MenuItemType), //item count
			NULL,  //exe
			OSD_DISP_TIME,  //time out
			osdVisible|osdRedraw,//flags
};



MenuPageType* CODE tblMenus[]=
{
       	&PowerOffMenu,
	    &PowerOnMenu,
        &RootMenu,

		#ifdef LowBaterryDetecEn 
		&BatteryAdcMenu,
		#endif

        #ifdef LogoEn
		&LOGO1Menu,
		&LOGO2Menu,
		&LOGO3Menu,
		&LOGO4Menu,
		&LOGO5Menu,
		#endif
		
		&BrightnessMenu,
		&ContrastMenu,
		&SaturationMenu,
		&QuicklyBrightnessMenu,
		&QuicklyContrastMenu,
		&QuicklySaturationMenu,
};


#define MenuCount sizeof(tblMenus)/sizeof(MenuPageType*)
#endif
