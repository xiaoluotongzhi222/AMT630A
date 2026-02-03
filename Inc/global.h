/***********************************************************************
*Copyright (C) 2005 深圳艾科创新有限公司产品应用一部
* All rights reserved.

*File name: 　 Global.h
*Version:    　0.1
*Author:       cjinzong
*update:       2010-05-23

*Description:
              系统全局变量的定义和声明,这些全局变量是系统的而不是和某个模块相关。
*History:  

************************************************************************/
#ifndef _GLOBAL_H__
#define _GLOBAL_H__

#include <intrins.h>
#include <stddef.h>

#ifdef _GLOBAL_C_
  #define _GLOBAL_EXTERN_   
#else
  #define _GLOBAL_EXTERN_ extern
#endif


typedef enum _CtrlMode
{
   MCU=0,
   IIC,
}CtrlMode;


typedef enum _InputSourceIDType
{
    INPUT_AV = 0,
	INPUT_AV1,
	INPUT_AV2,
	INPUT_TV,
	INPUT_CAMERA_DoorBell,
	INPUT_CAMERA_Car,
	INPUT_SVIDEO,
	INPUT_ITU656,
	INPUT_FM,	
	INPUT_YPBPR,
	INPUT_VGA,
	MAX_VIDEO_CHANNEL ,
	ALL_INPUT_SOURCE = 0XFF,
}InputSourceType;


typedef enum _ColorSysType
{
    PAL = 0,
	PAL_N,
	PAL_M,
    NTSC,
    SECAM,   
    PAL60,
    AUTO,
	NULL_SYS = -1,
}ColorSysType;


typedef enum _AdcChannelType  
{
    CH0 = 0,
    CH1,
    CH2,
    CH3,
}AdcChannelType;


typedef enum _TimeMsType
{
 TIME_5MS    =   1,
 TIME_10MS   =   2,
 TIME_15MS   =   3,
 TIME_20MS   =   4,
 TIME_25MS   =   5,
 TIME_30MS   =   6,
 TIME_35MS   =   7,
 TIME_40MS   =   8,
 TIME_75MS   =   15,
 TIME_80MS   =   16,
 TIME_100MS  =   20,  
 TIME_110MS  =   22,
 TIME_160MS  =   32, 
 TIME_200MS  =   40,
 TIME_21OMS  =   42,
 TIME_22OMS  =   44,
 TIME_225MS  =   45,
 TIME_23OMS  =   46,
 TIME_320MS  =   64,
 TIME_500MS  =   100,
 TIME_510MS  =   102,
 TIME_640MS  =   128,
 TIME_15S    =   200,
}TimeMsType;



typedef enum _ConfigDisplayMode
{
     DISP_16_9= 0 ,
     DISP_4_3,
     DISP_EXT0,
     DISP_EXT1,
     DISP_EXT2,
     DISP_EXT3,
}ConfigDisplayMode;


typedef enum _LogoID
{
   LOGO1=0,
   LOGO2,
   LOGO3,
   LOGO4,
   LOGO5,
   LogoIDMax = LOGO5,
}LogoID;


typedef enum _VdeOutputType
{
	VDE_CLOSE = 0,             
	VDE_RED,          
	VDE_GREEN,          
	VDE_BLUE ,                    
	VDE_GRAY,     
	VDE_WHITE,     
	VDE_BLACK,
	MAX_VDECOLOR = VDE_BLACK,
} VdeOutputType;


typedef enum _RecProtocolDataType
{
	ProtocolData0 = 0,             
	ProtocolData1,          
	AddressDataH, 
	CommandDataH,
	AddressDataL,
	CommandDataL,
	WriteDataH,     
	WriteDataL,
} RecProtocolDataType;


typedef enum _BatterAdcLevel
{
	BatterAdc_Lev0=0,
	BatterAdc_Lev1,
	BatterAdc_lev2,
	BatterAdc_Lev3,
}BatterAdcLevel;

typedef enum _ConfigPower
{
     POWER_OFF= 0 ,
     POWER_ON,
}ConfigPower;

typedef struct _osdPath
{
   UCHAR pageIndex;
   UCHAR itemIndex;
}OsdPath;

typedef struct	_OsdSettingInfo	              //OSD参数
{
    UCHAR defLanguage;
	UCHAR curlanguage;		    //OSD语言
	UINT  dispTime;         //OSD消失时间
   	UINT  storageTime;      //OSD记忆数据时间
	UCHAR alph;             //OSD透明度 
	UCHAR xPos;	            //OSD菜单水平偏移
	UCHAR yPos;             //OSD菜单垂直偏移
}OsdInfoType;

typedef struct	_VideoSettingInfo	              //OSD参数
{
	UCHAR curSource; //AV TV DVD CAMERA ...
	UCHAR videoType; //cvbs / yc / itu656 / ypbpr / rgb ...
	UCHAR colorSys;	
	
	UCHAR brigthness;
	UCHAR contrast;
	UCHAR saturation;	
	UCHAR tint;
	UCHAR nosiceSw;
	UCHAR ScreeSw;
}VideoInfoType;


typedef struct _FlashSettingInfo
{
    UCHAR type;
    UCHAR unprotectedComd;
	UCHAR erase4kComd;
}FlashInfoType;


typedef struct _DispSettingInfo
{
    UCHAR zoomMode;
	UCHAR flipMode;
	UCHAR udAdj;
	UCHAR lrAdj;
}DispInfoType;


typedef struct _PowerSettingInfo
{
    UCHAR mode;
	UCHAR status;
}PowerInfoType;

typedef struct _LogoSettingInfo
{
	UCHAR logoID;
	UCHAR ColorMode;
	UINT  FontRamNum;
	ULONG StarAddr;
}LogoInfoType;


typedef struct _KeyInfor
{
    UCHAR  KeyMsg;
	UCHAR  PressTime;
}KeyInfor;


typedef struct _KeyMsgMap
{
   UCHAR KeyMsg;
   UCHAR KeyCmd;
}KeyMsgMap;


typedef struct _KeyCmdMap
{
   UINT   KeyVal;
   UCHAR  KeyCmd;
}KeyCmdMap;


typedef struct _UserInput
{
    UCHAR Type;
	UCHAR Val;
	UCHAR Status;
}UserInputType;


typedef  struct _sysWorkPara
{
	UCHAR           OXAA;
	
	PowerInfoType   Power;
    FlashInfoType   Flash;
	VideoInfoType   Video;
	OsdInfoType     Osd;		       //OSD参数  
	DispInfoType    Disp;
	LogoInfoType    Logo;
    UCHAR           OX55;
	UCHAR           xorSum;            //系统参数校验和 
}SysWorkParaType;


typedef struct	_VideoPDF	              //OSD参数
{
	UCHAR ADDR_0xfd33; 
	UCHAR ADDR_0xfd34; 
	UCHAR ADDR_0xfd35;	
}VideoPDF;



/********************globle**************************/
_GLOBAL_EXTERN_ SysWorkParaType XDATA g_sysSetting;
_GLOBAL_EXTERN_ UserInputType   XDATA g_UserInputInfo;

_GLOBAL_EXTERN_ UCHAR XDATA g_ucDianWeiQiVal;
_GLOBAL_EXTERN_ UINT  XDATA g_uiInitDianWeiQiCH0Val;
_GLOBAL_EXTERN_ UINT  XDATA g_uiInitDianWeiQiCH1Val;
_GLOBAL_EXTERN_ UINT  XDATA g_uiInitDianWeiQiCH2Val;
_GLOBAL_EXTERN_ UINT  XDATA g_uiInitDianWeiQiCH3Val;
_GLOBAL_EXTERN_ UCHAR XDATA g_ucBatteryAdcVal;
_GLOBAL_EXTERN_ UCHAR XDATA g_ucBatteryAdcLev;
_GLOBAL_EXTERN_ UCHAR g_ucOsdEixt;
_GLOBAL_EXTERN_ KeyInfor XDATA PreKey;	
_GLOBAL_EXTERN_ BOOL  g_bKeyRepeatFlg;  
_GLOBAL_EXTERN_ BOOL  g_bSaveFlag;
_GLOBAL_EXTERN_ BOOL  g_bBackLightFlg;
_GLOBAL_EXTERN_ BOOL  g_bReleaseAdcKeyFlg;
_GLOBAL_EXTERN_ BOOL  g_bLogoDisplayFlag;  
_GLOBAL_EXTERN_ BOOL  g_bSignalFlg;
_GLOBAL_EXTERN_ BOOL  g_bPreSignalFlg;
_GLOBAL_EXTERN_ BOOL  g_bBLCtrlEnFlg;
_GLOBAL_EXTERN_ UCHAR XDATA g_ucContBLOn;
_GLOBAL_EXTERN_ UCHAR XDATA g_ucContBufSecond; 
_GLOBAL_EXTERN_ UCHAR XDATA g_ucContNoSignalSecond; 
_GLOBAL_EXTERN_ UCHAR XDATA g_ucStableTime;


/*********globle macro**********/
#define inputPress   		_BIT0
#define inputHold    		_BIT1

#define OsdBrightness   	_BIT0
#define OsdContrast     	_BIT1
#define OsdSaturation   	_BIT2
#define OsdBatteryAdc   	_BIT3

#define SetSaveFlagEn()   			g_bSaveFlag = ENABLE;
#define ClrSaveFlagEn()   			g_bSaveFlag = DISABLE;
#define ReadSaveFlagEn() 			(g_bSaveFlag == ENABLE)
#define SetVideoChSelEn() 			g_bVideoChSelOk = ENABLE;
#define ClrVideoChSelEn() 			g_bVideoChSelOk = DISABLE;

#define IsSignalOk()   			((COLOR_SYS_TV_ACTIVE &_BIT1)>>1)
#define IsHlockOk()     			((COLOR_SYS_TV_ACTIVE &_BIT1)>>1)
#define IsVlockOk()     			((COLOR_SYS_TV_ACTIVE &_BIT2)>>2)
#define GetSignalSys()      		((VIDEO_LINE_625_525 & _BIT2)>>2)
#define IsPAL()                    	(VIDEO_LINE_625_525 & _BIT2)
#define Uart_RXD()             	{SelBOOTUART &=~(_BIT4|_BIT3);SelRXD &= ~(_BIT6|_BIT5);SelRXD|= _BIT4;}     
#define Uart_TXD()             	{SelTXD &= ~(_BIT2|_BIT1);SelTXD|= _BIT0;}
#define I2C_SCL()              		{SelRXD &= ~(_BIT6|_BIT4);SelRXD|= _BIT5;}
#define I2C_SDA()              		{SelTXD &= ~(_BIT2|_BIT0);SelTXD|= _BIT1;}

#define hw_SelChannelToCVBS1()   	{VIDEO_CH_D0 &=(~_BIT5);VIDEO_CH_D0 &=(~_BIT4);}          
#define hw_SelChannelToCVBS2()   	{VIDEO_CH_D0 &=(~_BIT5);VIDEO_CH_D0 |=(_BIT4); }
#define hw_SelChannelToCVBS3()   	{VIDEO_CH_D0 |=(_BIT5); VIDEO_CH_D0 &=(~_BIT4);}
#define hw_SelChannelToNULL()    	{VIDEO_CH_D0 |=(_BIT5); VIDEO_CH_D0 |=(_BIT4); }
#define hw_SelSOG1In()    			{VIDEO_SOG_EN &=~(_BIT3|_BIT4);VIDEO_SOG_SEL &=~(_BIT6|_BIT7);VIDEO_SOG_EN |=(_BIT3|_BIT4);}
#define hw_SelSOG2In()     		{VIDEO_SOG_EN &=~(_BIT3|_BIT4);VIDEO_SOG_SEL &=(~_BIT7);VIDEO_SOG_SEL |=(_BIT6); VIDEO_SOG_EN |=(_BIT3|_BIT4);}
#define hw_SelSOG3In()     		{VIDEO_SOG_EN &=~(_BIT3|_BIT4);VIDEO_SOG_SEL |=(_BIT7); VIDEO_SOG_SEL &=(~_BIT6);VIDEO_SOG_EN |=(_BIT3|_BIT4);}
#define hw_SelSOGNULLIn()     		{VIDEO_SOG_EN &=~(_BIT3|_BIT4);VIDEO_SOG_SEL |=(_BIT6|_BIT7); VIDEO_SOG_EN |=(_BIT3|_BIT4);}


/*********key  macro**********/
#define NULL_CMD                	0XFF  //空命令
#define NULL_TIME               	0X00  //计时为0
#define NULL_KEY            		0XFFFF  //无效键
#define NULL_BATTERYADC        	0XFFFF  //无效


_GLOBAL_EXTERN_ void InitSystem(void);
_GLOBAL_EXTERN_ UINT Abs(UINT Val1,UINT Val2);

#endif
