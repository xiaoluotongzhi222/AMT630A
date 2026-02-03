/*
系统所有的信息定义都在此MAP文件
*/
#ifndef MSG_MAP_H__
#define MSG_MAP_H__

typedef enum _sysMsg
{
//用户按键信息(按键板按键，电位器按键)  UPK: user press key
   MSG_UPK_LEFT,
   MSG_UPK_RIGHT,
   MSG_UPK_MENU,
   MSG_UPK_POWER,
   MSG_UPK_BRIGHTNESS,
   MSG_UPK_CONTRAST,
   MSG_UPK_SATURATION,

   MSG_CONFIG_COLOR_SYS,
   MSG_OSD_EXIT,
   MSG_OSD_STORAGE,

   MSG_SIGNAL_OK,
   MSG_NO_SIGNAL,
   MSG_NOSIGNALPOWEROFF,
   MSG_TURNON_BACKLIGHT,
   MSG_TURNOFF_BACKLIGHT,
   MSG_BATTERYADC,
   MSG_NULL = -1,
}MSG;


typedef enum _MacroKeyVal
{
	KEY_POWER=0,           	
	KEY_LEFT,            	        
	KEY_RIGHT,           	                 	              	
	KEY_MENU,                   
	KEY_BRIGHTNESS,
	KEY_CONTRAST,
	KEY_SATURATION,
	KEY_NULL = -1,               
}MacroKeyVal;

#endif
