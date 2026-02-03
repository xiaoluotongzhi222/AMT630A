/***********************************************************************
*Copyright (C) 2005 深圳艾科创新有限公司产品应用一部
* All rights reserved.

*File name: 　 	Prj_AMT_43D_SDK_DEMO.h
*Version:    　	0.1
*Author:      	Jordan.chen
*update:      	2013-02-18

*Description:
            
*History:
************************************************************************/
#ifndef AMT6XX_PRJ_CONFIG_H__
#define AMT6XX_PRJ_CONFIG_H__


/*=======================================================
<<<<<<<<<<<<<<<<<<<    项目信息概述>>><<>>>>>>>>>>>>>>>>
========================================================*/
/*
>>客户名称: ARK

>>屏型号:HSD4.3D

>>效果要求:ARK  通用图像效果。

>>OSD风格:ARK  通用OSD风格。

>>软件功能要求: 
    1.支持电位器(支持正反方向调节)，按键调节。
    2.支持OSD 显示使能开关。

>>硬件功能要求:
    1.门铃常规功能硬件需求。

>>特殊功能要求:无。

>>备注:

*/


/*========================================================
<<<<<<<<<<<<<<<<<<<<<   芯片型号配置>>>>>>>>>>>>>>>>>>>>>
=========================================================*/
//[AMT chip type]
#define AMT_TYPE       AMT630A
#define WebSite        "www.arkmicro.com"


/*========================================================
<<<<<<<<<<<<<<<<<< 软件库配置>>>>>>>>>>>>>>>>>
=========================================================*/
#define VdLibCmd         0
#define ConfigUserPara() {/*在此写寄存器可以把lib的对应赋值覆盖*/ }


/*========================================================
<<<<<<<<<<<<<<<<<< 开机延迟时间配置>>>>>>>>>>>>>>>>>
=========================================================*/
#define PowerOnDelay    1  //note:200ms为一个单位


/*========================================================
<<<<<<<<<<<<<<<<<<<<<<   屏显示配置>>>>>>>>>>>>>>>>>>>>>>
=========================================================*/     
//[LCD pannel parameter list]  
#define P_SAT043CM40DMY0_AMT630A_STD_20141202_EN   ENABLE



/*========================================================
<<<<<<<<<<<<<<<<<<<<   图像显示配置>>>>>>>>>>>>>>>>>>>>>
=========================================================*/ 
//[Video channel]
#define  AV                     CVBS1

#if(AV == CVBS1)
#define SelAvChannel()			hw_SelChannelToCVBS1() 
#define SelAvSOGIn()       	hw_SelSOG1In()    
#elif(AV == CVBS3)
#define SelAvChannel()			hw_SelChannelToCVBS3() 
#define SelAvSOGIn()       	hw_SelSOG3In()  
#endif

#define SelNullChannel()      	hw_SelChannelToNULL() 
#define SelSOGNULLIn()			hw_SelSOGNULLIn()

//[PIC display value]
#define BRIGHT_MIN             0X49   //亮度调节最小值
#define	BRIGHT_MAX             0XA9   //亮度调节最大值                                     
#define	CONTRAST_MIN           0X00   //对比度调节最小值           
#define	CONTRAST_MAX           0XB0   //对比度调节最大值                                                   
#define	SATURATION_MIN         0X00  //色度调节最小值
#define	SATURATION_MAX         0X44  //色度调节最大值



/*========================================================
<<<<<<<<<<<<<<<<<<<<<<  OSD 功能配置>>>>>>>>>>>>>>>>>>>>>>
=========================================================*/ 
//[OSD enable]
#define OsdEn                  							//Osd模块显示开关

//[OSD Icon Size And ScalerRatio]
#define ICON_SIZE							SIZE_12X16   //SIZE_16X22

#if(ICON_SIZE == SIZE_12X16)
#define ICON_SIZE_X                       	12     //ICON 水平像素点数
#define ICON_SIZE_Y                       	16    //ICON 垂直行数
#define OsdScalerRatio						2 
#define NoSignalScalerRatio              	4
#elif(ICON_SIZE == SIZE_16X22)
#define ICON_SIZE_X                    	16    //ICON 水平像素点数
#define ICON_SIZE_Y                       	22    //ICON 垂直行数
#define OsdScalerRatio						1 
#define NoSignalScalerRatio              	2
#endif

//[OSD style]    //设置显示菜单的大小、前背景色
#define MAINMENU_XSIZE     				0x12
#define MAINMENU_YSIZE      				0x02

#define MAINMENU_FORECOLOR    			RED
#define MAINMENU_BACKCOLOR                GRAY

#define MAINMENU_ITEM_TITELFORECOLOR    	RED
#define MAINMENU_ITEM_TITELBACKCOLOR    	GRAY

#define MAINMENU_ITEM_NUMFORECOLOR      	RED
#define MAINMENU_ITEM_NUMBACKCOLOR     	GRAY

#define MAINMENU_ITEM_GUAGE              	0X0E
#define GUAGE_LENGTH                      	0X10

#define MAINMENU_ITEM_GUAGEFORECOLOR   	RED
#define MAINMENU_ITEM_GUAGEBACKCOLOR    	GRAY


//[Osd bar lenght]
#define MAX_VALUE              			30     	    //OSD显示最大值设置( 30-100 )


//[OSD menu X Y position]
#define MAINMENU_START_X_POS   			0X007C   //MAIN MENU 菜单的X起始位置
#define MAINMENU_START_Y_POS   			0X00E7   //MAIN MENU 菜单的Y起始位置

#define VERSIONMENU_START_X_POS 	    	0X0000   //VERSION MENU 菜单的X起始位置
#define VERSIONMENU_START_Y_POS 			0X0000   //VERSION MENU 菜单的Y起始位置

#define BATTERYADCMENU_START_X_POS 		0X0015   //BATTERYADC MENU 菜单的X起始位置
#define BATTERYADCMENU_START_Y_POS 		0X0000   //BATTERYADC MENU 菜单的Y起始位置

//[OSD default language]
#define DEFAULT_LANGUAGE       			ENGLISH  

//[OSD display timeout]
#define OSD_DISP_TIME           			200
#define OSD_STORAGE_TIME           		100  



/*========================================================
<<<<<<<<<<<<<<<<<<<<<<  LOGO 功能配置>>>>>>>>>>>>>>>>>>>>>>
=========================================================*/ 
//[Logo enable]
//#define LogoEn                    					//Logo模块开关

//[Logo display mode]
#define LOGO_DISP_MODE          			POWER_ON_DISP_LOGO//NOSIGNAL_DISP_LOGO

//[Logo display backcolor]
#define LOGO_DISP_BACKCOLOR               BLUE  		//LOGO显示背景颜色

//[Logo menu X Y position]
#define LOGO1MENU_START_X_POS 		    0X0070   //LOGO1 MENU 菜单的X起始位置
#define LOGO1MENU_START_Y_POS 		    0X0055   //LOGO1 MENU 菜单的Y起始位置

#define LOGO2MENU_START_X_POS 		    0X0070   //LOGO2 MENU 菜单的X起始位置
#define LOGO2MENU_START_Y_POS 		    0X0055   //LOGO2 MENU 菜单的Y起始位置

#define LOGO3MENU_START_X_POS 		    0X0070   //LOGO3 MENU 菜单的X起始位置
#define LOGO3MENU_START_Y_POS 		    0X0055   //LOGO3 MENU 菜单的Y起始位置

#define LOGO4MENU_START_X_POS 		    0X0070   //LOGO4 MENU 菜单的X起始位置
#define LOGO4MENU_START_Y_POS 		    0X0055   //LOGO4 MENU 菜单的Y起始位置

#define LOGO5MENU_START_X_POS 		    0X0070   //LOGO5 MENU 菜单的X起始位置
#define LOGO5MENU_START_Y_POS 		    0X0055   //LOGO5 MENU 菜单的Y起始位置



/*========================================================
<<<<<<<<<<<<<<<<<<<<   背光控制配置>>>>>>>>>>>>>>>>>>>>>
=========================================================*/ 
//[Backlight ctrl]
#define BacklightEn             //背光控制使能开关
#ifdef BacklightEn
#define BACKLIGHT_CTRL_MODE     DC_PWM0_CTRL // DC_PWM0_CTRL、DC_PWM1_CTRL、DC_PWM2_CTRL、DC_PWM3_CTRL、GPIO_CTRL 

#if BACKLIGHT_CTRL_MODE == GPIO_CTRL  
#define hw_setBacklight()    SetP3_5(1)
#define hw_clrBacklight()    SetP3_5(0)
#define hw_setBIASEn()    	
#define hw_clrBIASEn()  
#endif

#if BACKLIGHT_CTRL_MODE == DC_PWM0_CTRL
#define hw_setBacklight() (PWM_CTRL |= _BIT0)
#define hw_clrBacklight() (PWM_CTRL &= ~_BIT0)
#define hw_setBIASEn()    	
#define hw_clrBIASEn()  
#endif

#if BACKLIGHT_CTRL_MODE == DC_PWM1_CTRL
#define hw_setBacklight() (PWM_CTRL |= _BIT1)
#define hw_clrBacklight() (PWM_CTRL &= ~_BIT1)
#define hw_setBIASEn()    	
#define hw_clrBIASEn()  
#endif

#if BACKLIGHT_CTRL_MODE == DC_PWM2_CTRL
#define hw_setBacklight() (PWM_CTRL |= _BIT2)
#define hw_clrBacklight() (PWM_CTRL &= ~_BIT2)
#define hw_setBIASEn()    	
#define hw_clrBIASEn()  
#endif

#if BACKLIGHT_CTRL_MODE == DC_PWM3_CTRL
#define hw_setBacklight() (PWM_CTRL |= _BIT3)
#define hw_clrBacklight() (PWM_CTRL &= ~_BIT3)
#define hw_setBIASEn()    	
#define hw_clrBIASEn()  
#endif

#endif



/*========================================================
<<<<<<<<<<<<<<<<<<<<   按键功能配置>>>>>>>>>>>>>>>>>>>>>
=========================================================*/ 
//[Key detect ctrl]
//#define KeyDetectEn            //按键检测使能开关
#ifdef KeyDetectEn 

#define KEY_TYPE             DIANWEIQI_KEY//DIANWEIQI_KEY、ADC_KEY、GPIO_KEY

#if(KEY_TYPE == ADC_KEY)
#define hw_upResistance      1000     //上拉电阻值  12k
#define hw_downResistance    0        // 0:表示无下拉电阻
#define hw_keyVoltage        3.3  
#define ADC_CH_LIST          {CH1} //{CH0,CH1,CH2,Ch3} //通道列表     
#define KEY_PAD_ID            KP_ARK_SDK_V01   
#define KEY_OFFSET            0X05            //按键的偏移量
#define RepeatTime            0X07       //连续按键响应时间
#endif// #if(KEY_TYPE == ADC_key)                  

#if(KEY_TYPE == DIANWEIQI_KEY) 
#define ForwardAdj                 0              //电位器正向调节
#define ReverseAdj                 1              //电位器反向调节

#define DianWeiQiAdjDir            ForwardAdj   //电位器正向调节
#define DianWeiQi_CH_LIST         {CH0,CH1}    //通道列表     
#define BrightnessChannel          CH0   		//亮度ADC通道
#define ContrastChannel            CH2   		//对比度ADC通道
#define SaturationChannel          CH1   		//色度ADC通道
#endif //#if(KEY_TYPE == DIANWEIQI_KEY)


#if(KEY_TYPE == GPIO_KEY)
#define GPIO_KEY_COUNT              3             //GPIO KEY 按键个数
#define GPIO_KEY_VALID              0             //GPIO KEY 按键有效状态
#define RepeatTime                  0X07        //连续GPIO KEY 响应时间

#define GPIO_KEY0                   GetP1_0()      //KEY0 对应的GPIO口
#define GPIO_KEY0_CMD               KEY_MENU  //KEY0对应的功能

#define GPIO_KEY1                   GetP1_1()  //KEY1 对应的GPIO口
#define GPIO_KEY1_CMD               KEY_LEFT     //KEY1对应的功能

#define GPIO_KEY2                   GetP1_2()     //KEY2 对应的GPIO口
#define GPIO_KEY2_CMD               KEY_RIGHT     //KEY2对应的功能
#endif  //#if(KEY_TYPE == GPIO_KEY)

#endif//#ifdef KeyDetectEn 



/*========================================================
<<<<<<<<<<<<<<<<<<<<   屏SPI 初始化配置>>>>>>>>>>>>>>>>>>>
=========================================================*/ 
//[SPI inital pannel]
//#define SpiInitPannelEn       //SPI 屏初始化使能开关

#ifdef SpiInitPannelEn

//#define SpiAdjRegEn  //串口调试屏SPI寄存器使能开关

#define hw_setCs(x)    SetP1_7(x)
#define hw_setClk(x)   SetP0_6(x) 
#define hw_setDout(x)  SetP1_6(x)
#define hw_setReset(x) SetGPIO12(x)

#endif



/*========================================================
<<<<<<<<<<<<<<<<<<<<   CPU 屏初始化配置>>>>>>>>>>>>>>>>>>>
=========================================================*/ 
//#define CpuInitPannelEn          //Cpu 屏初始化使能开关



/*========================================================
<<<<<<<<<<<<<<<<<<<<   程序存储配置>>>>>>>>>>>>>>>>>>>>>>
=========================================================*/ 
#define FlashEn 

//#define E2promEn      
#ifdef E2promEn
#define hw_E2p_getSDA_input()     GetGPIO11()
#define hw_E2p_setSDA_output(x)   SetGPIO11(x)
#define hw_E2p_setSCL_output(x)   SetGPIO8(x)
#endif



/*========================================================
<<<<<<<<<<<<<<<<<<   电源LED 指示配置>>>>>>>>>>>>>>>>>>>>
=========================================================*/ 
//[Power LED]
//#define PowerLedEn             //电源指示灯使能开关 
#ifdef PowerLedEn
#define hw_setRedLEDOn()             SetGPIO6(1) 
#define hw_setRedLEDOff()            SetGPIO6(0) 

#define hw_setGreenLEDOn()           SetP2_6(1)
#define hw_setGreenLEDOff()          SetP2_6(0)
#endif



/*========================================================
<<<<<<<<<<<<<<<<<<   背光过压保护配置>>>>>>>>>>>>>>>>>>>
=========================================================*/        
//#define BL_OvpSoftProtecEn     //背光过压软件保护    
#ifdef BL_OvpSoftProtecEn 
#define ADC_DETEC_CH           CH0
#define ProtecVolte            2.0
#define ProtecVolteAdcVal(x)  (4096*x)/3.3
#endif



/*========================================================
<<<<<<<<<<<<<<<<<<   电池电量检测配置>>>>>>>>>>>>>>>>>>>
=========================================================*/ 
//#define LowBaterryDetecEn     //电池电量不足
#ifdef LowBaterryDetecEn 
#define BATTER_DETEC_CH      	CH2
#define BatterLowVolte       	1.7   
#define BatterMidVolte         
#define BatterMaxVolte 
#define BatterVolteAdcVal(x) 	(64*x)/3.3
#endif





/*========================================================
<<<<<<<<<<<<<<<<<<<<<<  软件功能配置>>>>>>>>>>>>>>>>>>>>
=========================================================*/
//[Software function enable]
//#define NoSignalBLOffEn          //无信号关背光开关
//#define NoSignalPowerOffEn      //无信号一段时间自动关机开关
//#define QuickParaSaveEn       //快速参数保存开关
//#define KillColorEn           //强制关闭色彩
//#define DithingEn             //Dithing使能开关
#define Clk_AdjustEn          //时钟调节使能开关
#define Same_Color_AdjustEn  //纯色调节使能开关
//#define GrayBar_DetectEn     //灰阶检测使能开关
#define SignalChangeBLOffEn  //信号变化关背光开关

/*========================================================
<<<<<<<<<<<<<<<<<<<     系统测试点(TP)   >>>>>>>>>>>>>>>>>>>>
==========================================================*/
/*TP: Test Point，测试点都是通过串口打印来监测相应测试变量，
所以需要使能串口打印测试才能有效。
*/
#define  TP0_ADC    DISABLE   /*ADC 底层采样值(不经过滤波)*/
#define  TP1_ADC    DISABLE   /*ADC 经过滤波处理后的值*/
#define  TP2_ADC    DISABLE   /*ADC Key 返回给应用层的按键值*/
#define  TP3_ADC    DISABLE   /*ADC Key 返回给应用层对应的命令值*/
#define  TP1_KEY    DISABLE   /*Key 返回给应用层对应的消息*/

#endif//AMT6XX_PRJ_CONFIG_H__ 

