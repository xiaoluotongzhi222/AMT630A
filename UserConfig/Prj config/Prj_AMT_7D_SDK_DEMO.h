/***********************************************************************
*Copyright (C) 2005 ÉîÛÚ°¬¿Æ´´ĞÂÓĞÏŞ¹«Ë¾²úÆ·Ó¦ÓÃÒ»²¿
* All rights reserved.

*File name: ¡¡ 	Prj_AMT_7D_SDK_DEMO.h
*Version:    ¡¡	0.1
*Author:      	Jordan.chen
*update:      	2013-02-18

*Description:
            
*History:
************************************************************************/
#ifndef AMT6XX_PRJ_CONFIG_H__
#define AMT6XX_PRJ_CONFIG_H__


/*=======================================================
<<<<<<<<<<<<<<<<<<<    ÏîÄ¿ĞÅÏ¢¸ÅÊö>>><<>>>>>>>>>>>>>>>>
========================================================*/
/*
>>¿Í»§Ãû³Æ: ARK

>>ÆÁĞÍºÅ:HSD4.3D

>>Ğ§¹ûÒªÇó:ARK  Í¨ÓÃÍ¼ÏñĞ§¹û¡£

>>OSD·ç¸ñ:ARK  Í¨ÓÃOSD·ç¸ñ¡£

>>Èí¼ş¹¦ÄÜÒªÇó: 
    1.Ö§³ÖµçÎ»Æ÷(Ö§³ÖÕı·´·½Ïòµ÷½Ú)£¬°´¼üµ÷½Ú¡£
    2.Ö§³ÖOSD ÏÔÊ¾Ê¹ÄÜ¿ª¹Ø¡£

>>Ó²¼ş¹¦ÄÜÒªÇó:
    1.ÃÅÁå³£¹æ¹¦ÄÜÓ²¼şĞèÇó¡£

>>ÌØÊâ¹¦ÄÜÒªÇó:ÎŞ¡£

>>±¸×¢:

*/


/*========================================================
<<<<<<<<<<<<<<<<<<<<<   Ğ¾Æ¬ĞÍºÅÅäÖÃ>>>>>>>>>>>>>>>>>>>>>
=========================================================*/
//[AMT chip type]
#define AMT_TYPE       AMT630A
#define WebSite        "www.arkmicro.com"



/*========================================================
<<<<<<<<<<<<<<<<<< Èí¼ş¿âÅäÖÃ>>>>>>>>>>>>>>>>>
=========================================================*/
#define VdLibCmd         0
#define ConfigUserPara() {/*ÔÚ´ËĞ´¼Ä´æÆ÷¿ÉÒÔ°ÑlibµÄ¶ÔÓ¦¸³Öµ¸²¸Ç*/ }



/*========================================================
<<<<<<<<<<<<<<<<<< ¿ª»úÑÓ³ÙÊ±¼äÅäÖÃ>>>>>>>>>>>>>>>>>
=========================================================*/
#define PowerOnDelay    1  //note:200msÎªÒ»¸öµ¥Î»



/*========================================================
<<<<<<<<<<<<<<<<<<<<<<   ÆÁÏÔÊ¾ÅäÖÃ>>>>>>>>>>>>>>>>>>>>>>
=========================================================*/  
//[LCD pannel parameter list]  
#define P_AT070TN92_AMT630A_STD_20141202_EN      	DISABLE
#define P_AT070TN92_AMT630A_STD_20141219_EN      	DISABLE
#define P_SAT043CM40DMY0_AMT630A_STD_20141202_EN  ENABLE   // <--- å¼€å¯4.3å¯¸


/*========================================================
<<<<<<<<<<<<<<<<<<<<   Í¼ÏñÏÔÊ¾ÅäÖÃ>>>>>>>>>>>>>>>>>>>>>
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
#define BRIGHT_MIN             0X49   //ÁÁ¶Èµ÷½Ú×îĞ¡Öµ
#define	BRIGHT_MAX             0XA9   //ÁÁ¶Èµ÷½Ú×î´óÖµ                                     
#define	CONTRAST_MIN           0X00   //¶Ô±È¶Èµ÷½Ú×îĞ¡Öµ           
#define	CONTRAST_MAX           0XB0   //¶Ô±È¶Èµ÷½Ú×î´óÖµ                                                   
#define	SATURATION_MIN         0X00  //É«¶Èµ÷½Ú×îĞ¡Öµ
#define	SATURATION_MAX         0X44  //É«¶Èµ÷½Ú×î´óÖµ



/*========================================================
<<<<<<<<<<<<<<<<<<<<<<  OSD ¹¦ÄÜÅäÖÃ>>>>>>>>>>>>>>>>>>>>>>
=========================================================*/ 
//[OSD enable]
#define OsdEn                  				//OsdÄ£¿éÏÔÊ¾¿ª¹Ø

//[OSD Icon Size And ScalerRatio]
#define ICON_SIZE							SIZE_16X22   //SIZE_16X22

#if(ICON_SIZE == SIZE_12X16)
#define ICON_SIZE_X                       	12     //ICON Ë®Æ½ÏñËØµãÊı
#define ICON_SIZE_Y                       	16    //ICON ´¹Ö±ĞĞÊı
#define OsdScalerRatio						2 
#define NoSignalScalerRatio              	4
#elif(ICON_SIZE == SIZE_16X22)
#define ICON_SIZE_X                    	16    //ICON Ë®Æ½ÏñËØµãÊı
#define ICON_SIZE_Y                       	22    //ICON ´¹Ö±ĞĞÊı
#define OsdScalerRatio						1 
#define NoSignalScalerRatio              	2
#endif

//[OSD style]    //ÉèÖÃÏÔÊ¾²Ëµ¥µÄ´óĞ¡¡¢Ç°±³¾°É«
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
#define MAX_VALUE              			30     	    //OSDÏÔÊ¾×î´óÖµÉèÖÃ( 30-100 )


//[OSD menu X Y position]
#define MAINMENU_START_X_POS     0X0080     // è°ƒæ•´ä¸ºé€‚åˆ480å®½åº¦çš„ä½ç½®
#define MAINMENU_START_Y_POS     0X00ED     // è°ƒæ•´ä¸ºé€‚åˆ272é«˜åº¦çš„ä½ç½®

#define SOURCEMENU_START_X_POS   0X01D6
#define SOURCEMENU_START_Y_POS   0X0002

#define SOURCE_43_START_X_SHIFT  0X3F      // åç§»é‡å‡å°

#define NOSIGNALMENU_START_X_POS 0x007E
#define NOSIGNALMENU_START_Y_POS 0x007D

#define BTMENU_START_X_POS       0x0000
#define BTMENU_START_Y_POS       0x000A

#define BTCALLERMENU_START_X_POS 0x0055
#define BTCALLERMENU_START_Y_POS 0x0090

#define BATTERYADCMENU_START_X_POS 0x0015
#define BATTERYADCMENU_START_Y_POS 0x0000

#define MUTEMENU_START_X_POS     0X0018
#define MUTEMENU_START_Y_POS     0X0020
        
#define FACTORYMENU_START_X_POS  0X00AC
#define FACTORYMENU_START_Y_POS  0X008A

//[OSD default language]
#define DEFAULT_LANGUAGE       			ENGLISH  

//[OSD display timeout]
#define OSD_DISP_TIME           			200
#define OSD_STORAGE_TIME           		100  




/*========================================================
<<<<<<<<<<<<<<<<<<<<<<  LOGO ¹¦ÄÜÅäÖÃ>>>>>>>>>>>>>>>>>>>>>>
=========================================================*/ 
//[Logo enable]
//#define LogoEn                    					//LogoÄ£¿é¿ª¹Ø

//[Logo display mode]
#define LOGO_DISP_MODE          			POWER_ON_DISP_LOGO//NOSIGNAL_DISP_LOGO

//[Logo display backcolor]
#define LOGO_DISP_BACKCOLOR               BLUE  		//LOGOÏÔÊ¾±³¾°ÑÕÉ«



//[Logo menu X Y position]
#define LOGO1MENU_START_X_POS 		    0X0070   //LOGO1 MENU ²Ëµ¥µÄXÆğÊ¼Î»ÖÃ
#define LOGO1MENU_START_Y_POS 		    0X0055   //LOGO1 MENU ²Ëµ¥µÄYÆğÊ¼Î»ÖÃ

#define LOGO2MENU_START_X_POS 		    0X0070   //LOGO2 MENU ²Ëµ¥µÄXÆğÊ¼Î»ÖÃ
#define LOGO2MENU_START_Y_POS 		    0X0055   //LOGO2 MENU ²Ëµ¥µÄYÆğÊ¼Î»ÖÃ

#define LOGO3MENU_START_X_POS 		    0X0070   //LOGO3 MENU ²Ëµ¥µÄXÆğÊ¼Î»ÖÃ
#define LOGO3MENU_START_Y_POS 		    0X0055   //LOGO3 MENU ²Ëµ¥µÄYÆğÊ¼Î»ÖÃ

#define LOGO4MENU_START_X_POS 		    0X0070   //LOGO4 MENU ²Ëµ¥µÄXÆğÊ¼Î»ÖÃ
#define LOGO4MENU_START_Y_POS 		    0X0055   //LOGO4 MENU ²Ëµ¥µÄYÆğÊ¼Î»ÖÃ

#define LOGO5MENU_START_X_POS 		    0X0070   //LOGO5 MENU ²Ëµ¥µÄXÆğÊ¼Î»ÖÃ
#define LOGO5MENU_START_Y_POS 		    0X0055   //LOGO5 MENU ²Ëµ¥µÄYÆğÊ¼Î»ÖÃ



/*========================================================
<<<<<<<<<<<<<<<<<<<<   ±³¹â¿ØÖÆÅäÖÃ>>>>>>>>>>>>>>>>>>>>>
=========================================================*/ 
//[Backlight ctrl]
#define BacklightEn             //±³¹â¿ØÖÆÊ¹ÄÜ¿ª¹Ø
#ifdef BacklightEn
#define BACKLIGHT_CTRL_MODE     DC_PWM0_CTRL // DC_PWM0_CTRL¡¢DC_PWM1_CTRL¡¢DC_PWM2_CTRL¡¢DC_PWM3_CTRL¡¢GPIO_CTRL 

#if BACKLIGHT_CTRL_MODE == GPIO_CTRL  
#define hw_setBacklight()    	SetP3_5(1)
#define hw_clrBacklight()    	SetP3_5(0)
#define hw_setBIASEn()    	   	SetP3_6(1)
#define hw_clrBIASEn()			SetP3_6(0)
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
<<<<<<<<<<<<<<<<<<<<   °´¼ü¹¦ÄÜÅäÖÃ>>>>>>>>>>>>>>>>>>>>>
=========================================================*/ 
//[Key detect ctrl]
//#define KeyDetectEn            //°´¼ü¼ì²âÊ¹ÄÜ¿ª¹Ø
#ifdef KeyDetectEn 

#define KEY_TYPE             DIANWEIQI_KEY//DIANWEIQI_KEY¡¢ADC_KEY¡¢GPIO_KEY

#if(KEY_TYPE == ADC_KEY)
#define hw_upResistance      1000     //ÉÏÀ­µç×èÖµ  12k
#define hw_downResistance    0        // 0:±íÊ¾ÎŞÏÂÀ­µç×è
#define hw_keyVoltage        3.3  
#define ADC_CH_LIST          {CH1} //{CH0,CH1,CH2,Ch3} //Í¨µÀÁĞ±í     
#define KEY_PAD_ID            KP_ARK_SDK_V01   
#define KEY_OFFSET            0X05            //°´¼üµÄÆ«ÒÆÁ¿
#define RepeatTime            0X07       //Á¬Ğø°´¼üÏìÓ¦Ê±¼ä
#endif// #if(KEY_TYPE == ADC_key)                  

#if(KEY_TYPE == DIANWEIQI_KEY) 
#define ForwardAdj                 0              //µçÎ»Æ÷ÕıÏòµ÷½Ú
#define ReverseAdj                 1              //µçÎ»Æ÷·´Ïòµ÷½Ú

#define DianWeiQiAdjDir            ForwardAdj   //µçÎ»Æ÷ÕıÏòµ÷½Ú
#define DianWeiQi_CH_LIST         {CH2,CH3}    //Í¨µÀÁĞ±í     
#define BrightnessChannel          CH3   		//ÁÁ¶ÈADCÍ¨µÀ
#define ContrastChannel            CH1   		//¶Ô±È¶ÈADCÍ¨µÀ
#define SaturationChannel          CH2   		//É«¶ÈADCÍ¨µÀ
#endif //#if(KEY_TYPE == DIANWEIQI_KEY)


#if(KEY_TYPE == GPIO_KEY)
#define GPIO_KEY_COUNT              3             //GPIO KEY °´¼ü¸öÊı
#define GPIO_KEY_VALID              0             //GPIO KEY °´¼üÓĞĞ§×´Ì¬
#define RepeatTime                  0X07        //Á¬ĞøGPIO KEY ÏìÓ¦Ê±¼ä

#define GPIO_KEY0                   GetP1_0()      //KEY0 ¶ÔÓ¦µÄGPIO¿Ú
#define GPIO_KEY0_CMD               KEY_MENU  //KEY0¶ÔÓ¦µÄ¹¦ÄÜ

#define GPIO_KEY1                   GetP1_1()  //KEY1 ¶ÔÓ¦µÄGPIO¿Ú
#define GPIO_KEY1_CMD               KEY_LEFT     //KEY1¶ÔÓ¦µÄ¹¦ÄÜ

#define GPIO_KEY2                   GetP1_2()     //KEY2 ¶ÔÓ¦µÄGPIO¿Ú
#define GPIO_KEY2_CMD               KEY_RIGHT     //KEY2¶ÔÓ¦µÄ¹¦ÄÜ
#endif  //#if(KEY_TYPE == GPIO_KEY)

#endif//#ifdef KeyDetectEn 



/*========================================================
<<<<<<<<<<<<<<<<<<<<   ÆÁSPI ³õÊ¼»¯ÅäÖÃ>>>>>>>>>>>>>>>>>>>
=========================================================*/ 
//[SPI inital pannel]
//#define SpiInitPannelEn       //SPI ÆÁ³õÊ¼»¯Ê¹ÄÜ¿ª¹Ø

#ifdef SpiInitPannelEn

//#define SpiAdjRegEn  //´®¿Úµ÷ÊÔÆÁSPI¼Ä´æÆ÷Ê¹ÄÜ¿ª¹Ø

#define hw_setCs(x)    SetP1_7(x)
#define hw_setClk(x)   SetP0_6(x) 
#define hw_setDout(x)  SetP1_6(x)
#define hw_setReset(x) SetGPIO12(x)

#endif



/*========================================================
<<<<<<<<<<<<<<<<<<<<   CPU ÆÁ³õÊ¼»¯ÅäÖÃ>>>>>>>>>>>>>>>>>>>
=========================================================*/ 
//#define CpuInitPannelEn          //Cpu ÆÁ³õÊ¼»¯Ê¹ÄÜ¿ª¹Ø



/*========================================================
<<<<<<<<<<<<<<<<<<<<   ³ÌĞò´æ´¢ÅäÖÃ>>>>>>>>>>>>>>>>>>>>>>
=========================================================*/ 
#define FlashEn 

//#define E2promEn      
#ifdef E2promEn
#define hw_E2p_getSDA_input()     GetGPIO11()
#define hw_E2p_setSDA_output(x)   SetGPIO11(x)
#define hw_E2p_setSCL_output(x)   SetGPIO8(x)
#endif



/*========================================================
<<<<<<<<<<<<<<<<<<   µçÔ´LED Ö¸Ê¾ÅäÖÃ>>>>>>>>>>>>>>>>>>>>
=========================================================*/ 
//[Power LED]
//#define PowerLedEn             //µçÔ´Ö¸Ê¾µÆÊ¹ÄÜ¿ª¹Ø 
#ifdef PowerLedEn
#define hw_setRedLEDOn()             SetGPIO6(1) 
#define hw_setRedLEDOff()            SetGPIO6(0) 

#define hw_setGreenLEDOn()           SetP2_6(1)
#define hw_setGreenLEDOff()          SetP2_6(0)
#endif



/*========================================================
<<<<<<<<<<<<<<<<<<   ±³¹â¹ıÑ¹±£»¤ÅäÖÃ>>>>>>>>>>>>>>>>>>>
=========================================================*/        
//#define BL_OvpSoftProtecEn     //±³¹â¹ıÑ¹Èí¼ş±£»¤    
#ifdef BL_OvpSoftProtecEn 
#define ADC_DETEC_CH           CH0
#define ProtecVolte            2.0
#define ProtecVolteAdcVal(x)  (4096*x)/3.3
#endif



/*========================================================
<<<<<<<<<<<<<<<<<<   µç³ØµçÁ¿¼ì²âÅäÖÃ>>>>>>>>>>>>>>>>>>>
=========================================================*/ 
//#define LowBaterryDetecEn     //µç³ØµçÁ¿²»×ã
#ifdef LowBaterryDetecEn 
#define BATTER_DETEC_CH      	CH2
#define BatterLowVolte       	1.7   
#define BatterMidVolte         
#define BatterMaxVolte 
#define BatterVolteAdcVal(x) 	(64*x)/3.3
#endif




/*========================================================
<<<<<<<<<<<<<<<<<<<<<<  Èí¼ş¹¦ÄÜÅäÖÃ>>>>>>>>>>>>>>>>>>>>
=========================================================*/
//[Software function enable]
//#define NoSignalBLOffEn          //ÎŞĞÅºÅ¹Ø±³¹â¿ª¹Ø
//#define NoSignalPowerOffEn      //ÎŞĞÅºÅÒ»¶ÎÊ±¼ä×Ô¶¯¹Ø»ú¿ª¹Ø
//#define QuickParaSaveEn       //¿ìËÙ²ÎÊı±£´æ¿ª¹Ø
//#define KillColorEn           //Ç¿ÖÆ¹Ø±ÕÉ«²Ê
//#define DithingEn             //DithingÊ¹ÄÜ¿ª¹Ø
//#define Clk_AdjustEn          //Ê±ÖÓµ÷½ÚÊ¹ÄÜ¿ª¹Ø
//#define Same_Color_AdjustEn  //´¿É«µ÷½ÚÊ¹ÄÜ¿ª¹Ø
//#define GrayBar_DetectEn     //»Ò½×¼ì²âÊ¹ÄÜ¿ª¹Ø
//#define SignalChangeBLOffEn  //ĞÅºÅ±ä»¯¹Ø±³¹â¿ª¹Ø

/*========================================================
<<<<<<<<<<<<<<<<<<<     ÏµÍ³²âÊÔµã(TP)   >>>>>>>>>>>>>>>>>>>>
==========================================================*/
/*TP: Test Point£¬²âÊÔµã¶¼ÊÇÍ¨¹ı´®¿Ú´òÓ¡À´¼à²âÏàÓ¦²âÊÔ±äÁ¿£¬
ËùÒÔĞèÒªÊ¹ÄÜ´®¿Ú´òÓ¡²âÊÔ²ÅÄÜÓĞĞ§¡£
*/
#define  TP0_ADC    DISABLE   /*ADC µ×²ã²ÉÑùÖµ(²»¾­¹ıÂË²¨)*/
#define  TP1_ADC    DISABLE   /*ADC ¾­¹ıÂË²¨´¦ÀíºóµÄÖµ*/
#define  TP2_ADC    DISABLE   /*ADC Key ·µ»Ø¸øÓ¦ÓÃ²ãµÄ°´¼üÖµ*/
#define  TP3_ADC    DISABLE   /*ADC Key ·µ»Ø¸øÓ¦ÓÃ²ã¶ÔÓ¦µÄÃüÁîÖµ*/
#define  TP1_KEY    DISABLE   /*Key ·µ»Ø¸øÓ¦ÓÃ²ã¶ÔÓ¦µÄÏûÏ¢*/

#endif//AMT6XX_PRJ_CONFIG_H__ 

