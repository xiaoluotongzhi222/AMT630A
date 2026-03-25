/*******************************************************************************
*Copyright (C) 2005 深圳艾科创新有限公司产品应用一部
* All rights reserved.

*File name: 　 Interrupt.c	  
*Version:      0.1
*update:       2011-12-10
*Description:
  		   系统中断处理。
  		   
*History:  jordan.chen  2011/12/10    0.1    build  this  moudle
******************************************************************************/
#define _INTERRUPT_C_

#include "DataType.h"
#include "systemConfig.h"
#include "global.h"
#include "Debug.h"
#include "mcu.h"
#include "MsgMap.h"
#include "AMT_Mcu.h"
#include "AMT_Drv.h"
#include "AMT_Reg.h"
#include "ConfigLcdPara.h"
#include "Interrupt.h"
extern UCHAR XDATA g_RxBuf[];
extern UCHAR volatile XDATA g_RxHead;
extern UCHAR volatile XDATA g_RxTail;  
UCHAR XDATA next_head;
#define RX_BUF_SIZE 256

void POS_IrqServerRec(void) interrupt 4  //Uart Receive interrupt
{
    if (RI)
    {
        RI = 0;
        next_head = (UCHAR)(g_RxHead + 1) % RX_BUF_SIZE; 
        if (next_head != g_RxTail) 
        {
            g_RxBuf[g_RxHead] = SBUF; 
            g_RxHead = next_head; 
        }
			
        else
        {
        }
    }
    
    if (TI)
    {
        TI = 0;
    }
   #ifdef SpiInitPannelEn
   #ifdef SpiAdjRegEn
   POS_RecUartSpiInfor();
   #endif
   #endif
}


/***********************************************************
*name:       IrqServerTimer1(void)
*input:      non
*output:     对系统的实时事件进行检测.
*update:     2011-12-23 
*state:      try out

*description:  
         对系统的实时事件进行检测，并置事件标志。
*NOTE:
         这个计数器可以从0-255分频
*history:
************************************************************/
UINT XDATA s_ucSysTimer = 0;
void POS_IrqServerTimer1(void) interrupt 3	   //timer 1
{  


	#ifdef LargeSignalEn
	static UCHAR ucContAgcStable = 0;
	#endif

    TR1  = OFF;
	SetTimer1(_ms(5));
	TR1  = ON;

	s_ucSysTimer++;	
    POS_VideoProcess(VdLibCmd);

	#ifdef Clk_AdjustEn
	if(IsSignalOk())
    { 
	    UINT XDATA wcNoiseLevel = 0;
		static XDATA UCHAR s_ucNoiseLevelBuf[10] ={0,0,0,0,0,0,0,0,0,0};
	    static XDATA UCHAR s_ucIndex = 0;
		static XDATA UINT minWcNoiseLevel = 0xff;
		static XDATA UCHAR contClkChange = 0;
		
        s_ucNoiseLevelBuf[s_ucIndex] = NOISE_LEVEL;
		
		if(++s_ucIndex >= 10)
		{
			 wcNoiseLevel +=s_ucNoiseLevelBuf[0]; 
			 wcNoiseLevel +=s_ucNoiseLevelBuf[1]; 
			 wcNoiseLevel +=s_ucNoiseLevelBuf[2]; 
			 wcNoiseLevel +=s_ucNoiseLevelBuf[3]; 
			 wcNoiseLevel +=s_ucNoiseLevelBuf[4]; 
			 wcNoiseLevel +=s_ucNoiseLevelBuf[5]; 
			 wcNoiseLevel +=s_ucNoiseLevelBuf[6]; 
			 wcNoiseLevel +=s_ucNoiseLevelBuf[7]; 
			 wcNoiseLevel +=s_ucNoiseLevelBuf[8]; 
			 wcNoiseLevel +=s_ucNoiseLevelBuf[9]; 

		     wcNoiseLevel = wcNoiseLevel/10;
			 //IrqPrintf("current NoiseLevel = %x\n", wcNoiseLevel);

			 if(contClkChange<=10)
			 {
			       contClkChange++;
                   if(minWcNoiseLevel>wcNoiseLevel)
                   {
                        minWcNoiseLevel = wcNoiseLevel ;
						//IrqPrintf("*****************current minWcNoiseLevel = %x\n", minWcNoiseLevel);
				   }	   
				   if(IsPAL())
				   {
	                   ANA_DIVA = g_ucPalPllClkDefVal+1;
					   _nop_();
					   _nop_();
					   _nop_();
					   ANA_DIVA = g_ucPalPllClkDefVal;
				   }
				   else
				   {
                       ANA_DIVA = g_ucNtscPllClkDefVal+1;
					   _nop_();
					   _nop_();
					   _nop_();
					   ANA_DIVA = g_ucNtscPllClkDefVal;
				   }
				  
			 }
			 else
			 {
				 if(wcNoiseLevel> (minWcNoiseLevel+1)) 
				 {
                       if(IsPAL())
					   {
		                   ANA_DIVA = g_ucPalPllClkDefVal+1;
						   _nop_();
						   _nop_();
						   _nop_();
						   ANA_DIVA = g_ucPalPllClkDefVal;
					   }
					   else
					   {
	                       ANA_DIVA = g_ucNtscPllClkDefVal+1;
						   _nop_();
						   _nop_();
						   _nop_();
						   ANA_DIVA = g_ucNtscPllClkDefVal;
					   }

					   if(contClkChange<=30)
					   {
                            contClkChange++; //调整切换时钟。 
                            //IrqPutstr("************  adj\n");
					   }
					   else
					   {
                            contClkChange = 0;//表示信号存在变化从新复位计算最小Noiselevel
							minWcNoiseLevel=wcNoiseLevel;
							//IrqPutstr("************  reset\n");
					   }
				 }
			 }
			 s_ucIndex =0;	 
		}
	}
	
    /*实时监测时钟*/
	if(IsPAL())
	{
		if(ANA_DIVA != g_ucPalPllClkDefVal)
		{
			ANA_DIVA = g_ucPalPllClkDefVal;
		}
	}
	else
	{
	    if(ANA_DIVA != g_ucNtscPllClkDefVal)
		{
			ANA_DIVA = g_ucNtscPllClkDefVal;
		}	
	}
	#endif
	
	#ifdef GrayBar_DetectEn
    /*灰阶*/
	if(XBYTE[0XFED0]&_BIT4)
	{
         XBYTE[0XFFB9]=0X3F;
		 XBYTE[0XFFBA]=0X00;
	}
	else
	{
         XBYTE[0XFFB9]=0X22;
		 XBYTE[0XFFBA]=0X20;
	}
	#endif

	#ifdef Same_Color_AdjustEn
    if(Is100ms(s_ucSysTimer))
    { 
         static XDATA UCHAR contSame = 0 ;
		 
         if(XBYTE[0XFED0] & _BIT6)
         {
              if(++contSame>10)
              {
                   contSame = 0;
                   XBYTE[0XFE45] = 0X70;
			  }  
		 }
		 else
		 {
              contSame = 0; 
			  XBYTE[0XFE45] = 0X80;
		 }
	}
	#endif

	if(Is5ms(s_ucSysTimer))
	{
	    HFZ_LR_BLANK_WR = 0X00;
	    g_bGetSignalFlg = 1;  
	    g_bGetUserInputFlg = 1;
		g_bGetBatteryAdcFlg = 1;
	}
		
	if(Is20ms(s_ucSysTimer))
	{
	    g_bGetColorSysFlg = 1;
	}
	if(Is30ms(s_ucSysTimer))
	{
	    g_bGetTimeFlg = 1;
	    g_bGetUserDefFlg = 1;
	}

	/**********图像制式消息处理*********/
	if(g_bGetColorSysFlg)
	{
        #define StableTimes   20

		static UCHAR  s_ucPreSys = PAL;
		UCHAR  ucCurSys;
	
	    if(IsSignalOk()||(0XFF == g_ucColorSys))
		{
		   ucCurSys = GetSignalSys();
		   if(ucCurSys != s_ucPreSys)
	       {
	          s_ucPreSys = ucCurSys;
	          g_ucStableTime = 0;
	       }
		   else
		   {
		       if(g_ucStableTime < StableTimes)
			   {
	               if(++g_ucStableTime == StableTimes)
	               {
	                  switch(ucCurSys)
	                  {
	                      case 0X00:
						  	 ucCurSys = NTSC;
							 break;

						  case 0X01:
						  	 ucCurSys = PAL;
						  	 break;

						  default:
						  	 ucCurSys = PAL;
						  	 break;
	                  }
					 g_ucColorSys = ucCurSys;
	               }
		       }
		   }
		}
		else
		{
		   g_ucStableTime = 0X00;
		}
	}

	#ifdef SignalChangeBLOffEn
	#define ContBackLightOff   	  	15
	#define ContSyncStableTimes     	10

	if(g_bBLCtrlEnFlg)
	{
	    static UCHAR ucContSignal = 0xff;

		if(g_bPreSignalFlg)
		{
		    if(g_bBackLightFlg)
            {
				if((!IsHlockOk()) || (!IsVlockOk()))
				{
				    VDE_REG = 0X54; 
					ucContSignal = 0;
					hw_clrBacklight();
					g_bBackLightFlg = OFF;
					//IrqPutstr("quickly test pic");
				}
			}
		}
		
		if(g_bPreSignalFlg != IsSignalOk())
	    {
	        ucContSignal = 0;
			g_bPreSignalFlg = !g_bPreSignalFlg;
	    }
		else
		{
		    if(ucContSignal < ContSyncStableTimes)
		    {
                if(++ucContSignal == ContSyncStableTimes)
                {
                      g_bSignalFlg = g_bPreSignalFlg;
					  //黑屏信号
					  VDE_REG = 0X54;        
					  g_ucContBLOn = ContBackLightOff;     
					  hw_clrBacklight();
					  g_bBackLightFlg = OFF;
					
					 if(!g_bPreSignalFlg)
					 {
					     //可靠无信号出测试图蓝屏。
                         VDE_REG = 0X52;
					 }
					 else
					 {
					     //可靠有信号配置为无信号黑屏
                         VP_EN_REG = 0X27;
					 }
				}
			}
		}
	}
	#endif
	
	#ifdef NoSignalBLOffEn
	if((!IsHlockOk()) || (!IsVlockOk()))
    {
        if(g_bBackLightFlg)
        {
	        //IrqPutstr("bl off2\n");
	        #ifdef BacklightEn
//			hw_clrBacklight(); 
//			g_bBackLightFlg = OFF; 
	        #endif
        }
	}
	#endif
}


