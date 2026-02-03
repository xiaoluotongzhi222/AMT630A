/***********************************************************************
*Copyright (C) 2005 深圳艾科创新有限公司产品应用一部
* All rights reserved.

*File name: 　 SysWorkPara.c
*Version:    　0.1
*Author:       Jordan.chen
*update:       2011-12-19

*Description:
            主要是系统配置参数的管理。
*History:  

************************************************************************/
#define _SYS_WORK_PARA_C_
#include "DataType.h"
#include "systemConfig.h"
#include "global.h"
#include "Debug.h"
#include "Delay.h"
#include "Flash.h"
#include "E2prom.h"
#include "MsgMap.h"
#include "SysPower.h"
#include "Osd_Menu.h"
#include "Osd_MenuPage.h"
#include "sysWorkPara.h"
#include "ConfigLcdPara.h"



UCHAR ContSysCheckSum(UCHAR *pSysPara, UINT numOper)
{
    UINT XDATA i;
	UCHAR  XDATA tmpCheckSum = 0x00;
	 
	for(i = 0; i < numOper; i++)
	{
	    tmpCheckSum ^= pSysPara[i];
	}
	return(tmpCheckSum);  
}

/************************************************************************
*name:    CheckSetting(void)
*input:   non   
*output:  non  

*description:   
     	 这个函数用来检测系统参数的临界值,如果一旦发现有出错的数据，就会
		 把这个错误的数据恢复为默认值。 
*history:  
*************************************************************************/
void CheckSetting(void)
{
	//printfStr("CheckSetting");
	if(g_sysSetting.Video.curSource >= MAX_VIDEO_CHANNEL)
	{
	     g_sysSetting.Video.curSource  = INPUT_AV; 
	}
	if(g_sysSetting.Video.brigthness>MAX_VALUE)
	{
	     g_sysSetting.Video.brigthness = MAX_VALUE;
	}
	if(g_sysSetting.Video.saturation>MAX_VALUE)
	{
	     g_sysSetting.Video.saturation = MAX_VALUE;
	}
	if(g_sysSetting.Video.contrast>MAX_VALUE)
	{
	     g_sysSetting.Video.contrast = MAX_VALUE;
	}
	if(g_sysSetting.Osd.curlanguage>MAX_LANG)
	{
	   g_sysSetting.Osd.curlanguage = MIN_LAG;
	}
	if(g_sysSetting.Power.status>POWER_ON)
	{
	   g_sysSetting.Power.status = POWER_ON;
	}
	if(g_sysSetting.Logo.logoID>LogoIDMax)
	{
	   g_sysSetting.Logo.logoID = LogoIDMax;
	}
    if(g_sysSetting.Video.ScreeSw > MAX_VDECOLOR)
	{
		g_sysSetting.Video.ScreeSw = MAX_VDECOLOR;
	}
}
/***********************************************************
*name:       VerifySetting(void)
*input:      void
*output:     void 
*update:     2011-11-27 
*state:      allright

*description:   
           校验系统配置。
*history:
                                
************************************************************/
BOOL VerifySetting(UCHAR *pSysPara, UINT numOper, UCHAR sysCheckSum)
{
    
    UINT XDATA i;
	UCHAR XDATA tmpCheckSum = 0x00;
	
    //printfStr("VerifySetting");
	 
    if((g_sysSetting.OX55 == 0x55) && (g_sysSetting.OXAA == 0xaa))
    {
		for(i = 0; i < numOper; i++)
		{
		 	tmpCheckSum ^= pSysPara[i];
		}

		if(sysCheckSum == tmpCheckSum)
		{
			return(1);
		}
		else
		{
			return(0);
		}
    }
	else
	{
	    return(0);
	}
	
	
}


/***********************************************************
*name:       SaveSetting(void)
*input:      void
*output:     void 
*update:     2011-11-27 
*state:      allright

*description:   
           保寸系统设置参数
*history:
                                
************************************************************/
void SaveSetting(void)
{

    printfStr("SaveSetting");
	/*注意：只是需要对系统工作参数进行校验*/
	CheckSetting();

	/*数据标志*/
	g_sysSetting.OX55 = 0x55;
	g_sysSetting.OXAA = 0xaa;
	g_sysSetting.xorSum = ContSysCheckSum((UCHAR *)&g_sysSetting, (sizeof(SysWorkParaType) - sizeof(UCHAR))); 

    #ifdef FlashEn
	if(ReadSaveFlagEn())
	{ 
	    printfStr("Come to into Flash Save");
		ClrSaveFlagEn();
		WriteFlashSysPara(FLASH_DAT_ADDR, (UCHAR *)&g_sysSetting, sizeof(SysWorkParaType));
		DelayMs(100);
		WriteFlashSysPara(FLASH_COPY_ADDR,(UCHAR *)&g_sysSetting, sizeof(SysWorkParaType));   
	}
    #endif 	

	#ifdef E2promEn
	if(ReadSaveFlagEn())
	{ 
	    ClrSaveFlagEn();
		WriteE2promMultByte(E2P_DAT_ADDR, (UCHAR *)&g_sysSetting, sizeof(SysWorkParaType));
		DelayMs(100);
		WriteE2promMultByte(E2P_COPY_ADDR,(UCHAR *)&g_sysSetting, sizeof(SysWorkParaType));   
	}
    #endif 	

}


/***********************************************************
*name:       ResetSetting(void)
*input:      void
*output:     void 
*update:     2011-11-27 
*state:      allright

*description:   
           设置默认设置参数。
*history:
                                
************************************************************/
void ResetSetting(void)
{   
   //printfStr("set default setting \n");

    g_sysSetting.Video.curSource = INPUT_AV;
	g_sysSetting.Video.brigthness = MAX_VALUE/2;
	g_sysSetting.Video.saturation= MAX_VALUE/2;
	g_sysSetting.Video.contrast= MAX_VALUE/2;
	g_sysSetting.Video.colorSys= PAL;
	g_sysSetting.Disp.zoomMode = DISP_16_9;
	g_sysSetting.Osd.curlanguage = DEFAULT_LANGUAGE;
	g_sysSetting.Osd.dispTime  = 0;
	g_sysSetting.Video.ScreeSw = VDE_CLOSE;
	g_sysSetting.Logo.logoID  = LOGO1;	
	SetPowerOn();
}


/***********************************************************
*name:       ReadSetting(void)
*input:      void
*output:     BOOL 
*update:     2011-11-27 
*state:      allright

*description:   
           读取系统设置参数
*history:
                                
************************************************************/
BOOL ReadSetting(void)
{

    #ifdef FlashEn
	VerifyFlashDate(FLASH_DAT_ADDR);
    #endif

	#ifdef E2promEn
	VerifyE2promDate(E2P_DAT_ADDR);
	#endif
	
    if(VerifySetting((UCHAR *)&g_sysSetting, (sizeof(SysWorkParaType) - sizeof(UCHAR)), g_sysSetting.xorSum)) 
    {
        CheckSetting();
		return 1;
    }
	else
	{
		#ifdef FlashEn
		VerifyFlashDate(FLASH_COPY_ADDR);
	    #endif

		#ifdef E2promEn
		VerifyE2promDate(E2P_COPY_ADDR);
		#endif
		
		if(VerifySetting((UCHAR *)&g_sysSetting, (sizeof(SysWorkParaType) - sizeof(UCHAR)), g_sysSetting.xorSum)) 
		{
			CheckSetting();
			return 1;
		}
		else
		{  
		    ResetSetting();

			#ifdef FlashEn
			g_sysSetting.Flash.erase4kComd = Flash_comd[g_ucFlashTpye].FLASH_ERASE_4K;
            g_sysSetting.Flash.unprotectedComd = Flash_comd[g_ucFlashTpye].FLASH_UNPROTECTED_EN;
			#endif
			
			SetSaveFlagEn();
		    SaveSetting();
			return 0;
		}
	}
}

