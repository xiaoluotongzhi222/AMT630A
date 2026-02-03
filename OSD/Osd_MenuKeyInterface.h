#ifndef _MENUKEY_INTERFACE_H__
#define _MENUKEY_INTERFACE_H__


/*
系统所有的菜单页能够响应的CMD
*/

/*
关机页
*/


/*
开机页
*/


/*
系统页
*/
KeyComdInterface CODE RootMenuItem_KeyComdMap[]=
{ 
//       Conditions              Quickly Comd         Msg                      Source
        {inputPress,             COMD_RedrawMenu,     MSG_UPK_MENU,          ALL_INPUT_SOURCE},
        {inputPress          ,   COMD_Power,          MSG_UPK_POWER,         ALL_INPUT_SOURCE},
        {inputHold|inputPress,   COMD_Brightness,     MSG_UPK_BRIGHTNESS,    ALL_INPUT_SOURCE},
        {inputHold|inputPress,   COMD_Contrast,       MSG_UPK_CONTRAST,      ALL_INPUT_SOURCE},
        {inputHold|inputPress,   COMD_Saturation,     MSG_UPK_SATURATION,    ALL_INPUT_SOURCE},
};



/*
Logo页
*/


/*
No Signal页
*/



/*
亮度页
*/
KeyComdInterface CODE BrightnessMenuItem_KeyComdMap[]=
{ 
//       Conditions                  Comd              Msg            Source
        {inputHold|inputPress ,  COMD_IncValue,   MSG_UPK_RIGHT,     ALL_INPUT_SOURCE},
        {inputHold|inputPress,   COMD_DecValue,   MSG_UPK_LEFT,      ALL_INPUT_SOURCE},
        {inputPress ,            COMD_NextMenu,   MSG_UPK_MENU,      ALL_INPUT_SOURCE},
};


/*
对比度页
*/
KeyComdInterface CODE ContrastMenuItem_KeyComdMap[]=
{ 
//       Conditions                  Comd              Msg            Source
        {inputHold|inputPress ,  COMD_IncValue,   MSG_UPK_RIGHT,     ALL_INPUT_SOURCE},
        {inputHold|inputPress,   COMD_DecValue,   MSG_UPK_LEFT,      ALL_INPUT_SOURCE},
        {inputPress ,            COMD_NextMenu,   MSG_UPK_MENU,      ALL_INPUT_SOURCE},
};


/*
色度页
*/
KeyComdInterface CODE SaturationMenuItem_KeyComdMap[]=
{ 
//       Conditions                  Comd              Msg            Source
        {inputHold|inputPress ,  COMD_IncValue,   MSG_UPK_RIGHT,     ALL_INPUT_SOURCE},
        {inputHold|inputPress,   COMD_DecValue,   MSG_UPK_LEFT,      ALL_INPUT_SOURCE},
        {inputPress,             COMD_OsdExit,    MSG_UPK_MENU,      ALL_INPUT_SOURCE},
};



#endif


