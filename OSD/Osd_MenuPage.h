#ifndef _MENU_PAGE_H__
#define _MENU_PAGE_H__


/*
系统所有的菜单页及相关的资源
*/
#define _MENU_PAGE_ extern


/*
常用字符
*/
_MENU_PAGE_ UCHAR CODE AMT630FontLib[];
_MENU_PAGE_ UCHAR CODE AMT630Font_Char[];
_MENU_PAGE_ UCHAR CODE FontRam_Char[];

/*
关机页
*/
_MENU_PAGE_ MenuPageType CODE PowerOffMenu;


/*
开机页
*/
_MENU_PAGE_ MenuPageType CODE PowerOnMenu;
_MENU_PAGE_ AdjustType PowerOnMenu_CheckCondition (void);



/*
系统页
*/
_MENU_PAGE_ MenuPageType CODE RootMenu;


/*BatteryAdc页
*/
_MENU_PAGE_ ItemValueType CODE BatteryAdcMenuItemVal_BatteryAdc[];
_MENU_PAGE_ MenuPageType CODE BatteryAdcMenu;
_MENU_PAGE_ AdjustType BatteryAdcMenu_CheckCondition (void);
_MENU_PAGE_ BOOL AdjustBatteryAdc(UCHAR opratComd);


/*
Logo页
*/
_MENU_PAGE_ void InitLogoMenuDat(void);
_MENU_PAGE_ void LogoMenuBlending(void);
_MENU_PAGE_ AdjustType LogoMenu_CheckCondition (void);
_MENU_PAGE_ BOOL LogoMenu_DrawStyle(void);



/*
亮度页
*/
_MENU_PAGE_ TitelType CODE BrightnessMenuItem_BrightnessTitelTab[];
_MENU_PAGE_ TitelType CODE QuicklyBrightnessMenuItem_QuicklyBrightnessTitelTab[];
_MENU_PAGE_ ItemValueType CODE BrightnessMenuItemVal_Brightness[];
_MENU_PAGE_ ItemValueType CODE QuicklyBrightnessMenuItemVal_QuicklyBrightness[];
_MENU_PAGE_ MenuPageType CODE BrightnessMenu;
_MENU_PAGE_ MenuPageType CODE QuicklyBrightnessMenu;

_MENU_PAGE_ AdjustType BrightnessMenu_CheckCondition (void);
_MENU_PAGE_ AdjustType QuicklyBrightnessMenu_CheckCondition (void);
_MENU_PAGE_ BOOL BrightnessMenuItem_DrawStyle(void);
_MENU_PAGE_ BOOL QuicklyBrightnessMenuItem_DrawStyle(void);
_MENU_PAGE_ BOOL AdjustBrightness(UCHAR opratComd);
_MENU_PAGE_ BOOL AdjustQuicklyBrightness(UCHAR opratComd);
_MENU_PAGE_ BOOL ExectBrightness(void);
_MENU_PAGE_ BOOL ExectQuicklyBrightness(void);


/*
对比度页
*/
_MENU_PAGE_ TitelType CODE ContrastMenuItem_ContrastTitelTab[];
_MENU_PAGE_ TitelType CODE QuicklyContrastMenuItem_QuicklyContrastTitelTab[];
_MENU_PAGE_ ItemValueType CODE ContrastMenuItemVal_Contrast[];
_MENU_PAGE_ ItemValueType CODE QuicklyContrastMenuItemVal_QuicklyContrast[];
_MENU_PAGE_ MenuPageType CODE ContrastMenu;
_MENU_PAGE_ MenuPageType CODE QuicklyContrastMenu;

_MENU_PAGE_ AdjustType ContrastMenu_CheckCondition(void);
_MENU_PAGE_ AdjustType QuicklyContrastMenu_CheckCondition(void);
_MENU_PAGE_ BOOL ContrastMenuItem_DrawStyle(void);
_MENU_PAGE_ BOOL QuicklyContrastMenuItem_DrawStyle(void);
_MENU_PAGE_ BOOL AdjustContrast(UCHAR opratComd);
_MENU_PAGE_ BOOL AdjustQuicklyContrast(UCHAR opratComd);
_MENU_PAGE_ BOOL ExectContrast(void);
_MENU_PAGE_ BOOL ExectQuicklyContrast(void);


/*
色度页
*/
_MENU_PAGE_ TitelType CODE SaturationMenuItem_SaturationTitelTab[];
_MENU_PAGE_ TitelType CODE QuicklySaturationMenuItem_QuicklySaturationTitelTab[];
_MENU_PAGE_ ItemValueType CODE SaturationMenuItemVal_Saturation[];
_MENU_PAGE_ ItemValueType CODE QuicklySaturationMenuItemVal_QuicklySaturation[];
_MENU_PAGE_ MenuPageType CODE SaturationMenu;
_MENU_PAGE_ MenuPageType CODE QuicklySaturationMenu;

_MENU_PAGE_ AdjustType SaturationMenu_CheckCondition(void);
_MENU_PAGE_ AdjustType QuicklySaturationMenu_CheckCondition(void);
_MENU_PAGE_ BOOL SaturationMenuItem_DrawStyle(void);
_MENU_PAGE_ BOOL QuicklySaturationMenuItem_DrawStyle(void);
_MENU_PAGE_ BOOL AdjustSaturation(UCHAR opratComd);
_MENU_PAGE_ BOOL AdjustQuicklySaturation(UCHAR opratComd);
_MENU_PAGE_ BOOL ExectSaturation(void);
_MENU_PAGE_ BOOL ExectQuicklySaturation(void);



extern MenuPageType* CODE tblMenus[];
#define CurrentMenu		     tblMenus[g_ucMenuPageIndex]
#define PrevMenuPage		 CurrentMenu->PrevPage
#define CurrentMenuItems	 CurrentMenu->MenuItems
#define CurrentMenuItemCount CurrentMenu->ItemCount
#define CurrentMenuItem		 CurrentMenu->MenuItems[g_ucMenuItemIndex]
#define CurrentBlock         CurrentMenu->OsdBlockId
#define CurrentMenuTimeOut	 CurrentMenu->TimeOut


#define NextMenuPage		 CurrentMenuItem.NextPage
#define CurrentMenuItemFunc  CurrentMenuItem.KeyFunction
#endif


