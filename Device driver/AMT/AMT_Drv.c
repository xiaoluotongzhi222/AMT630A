/*******************************************************************************
*Copyright (C) 2005 深圳艾科创新有限公司产品应用一部
* All rights reserved.

*File name: 　 AMT_Drv.c	  
*Version:      1.0
*update:       2011-12-06
*Description:
  		   这个文件是对AMT应用驱动的定义:

  		   
*History:  yshuizhou   2011/12/06    1.0    build  this  moudle
******************************************************************************/
#define _AMT_DRV_C_

#include "Global.h"
#include "AMT_Mcu.h"
#include "AMT_Drv.h"
#include "AMT_Reg.h"
#include "Videoproc.h"
#include "Interrupt.h"
#include "SystemConfig.h"




#ifdef SpiInitPannelEn

/****************************************************************************
*name:   SetSda(void)
*input:  non              
*output: non  

*description: 设置SPI中Sda的状态
*history:   yshuizhou   2013/07/06    1.0    build   this  function
*****************************************************************************/
void SetSpDat(UCHAR Data)
{
	  if(Data)
	  {
	    hw_setDout(1);
	  }
	  else
	  {
	    hw_setDout(0);
	  }
}


/****************************************************************************
*name:   SetScl(void)
*input:  non              
*output: non  

*description: 设置SPI中Scl的状态
*history:   yshuizhou   2013/07/06    1.0    build   this  function
*****************************************************************************/
void SetSpClk(UCHAR Data)
{
	  if(Data)
	  {
	    hw_setClk(1);
	  }
	  else
	  {
	    hw_setClk(0);
	  }
}


/****************************************************************************
*name:   SetCs(void)
*input:  non              
*output: non  

*description: 设置SPI中Cs的状态
*history:   yshuizhou   2013/07/06    1.0    build   this  function
*****************************************************************************/
void SetSpEna(UCHAR Data)
{
	  if(Data)
	  {
	    hw_setCs(1);
	  }
	  else
	  {
	    hw_setCs(0);
	  }
}

/****************************************************************************
*name:   SetReset(void)
*input:  non              
*output: non  

*description: 设置SPI中Reset的状态
*history:   yshuizhou   2013/07/06    1.0    build   this  function
*****************************************************************************/
void SetReset(UCHAR Data)
{
	  if(Data)
	  {
	    hw_setReset(1);
	  }
	  else
	  {
	    hw_setReset(0);
	  }
}

#endif



/****************************************************************************
*name:   SetI2CDebug(void)
*input:  non              
*output: non  

*description: 此函数设置SCL、SDA使能。
*history:   yshuizhou   2014/10/23    1.0    build   this  function
*****************************************************************************/
#ifdef IICPrintfEn  //luo changed
void SetI2CDebug(void)
{
   I2C_SCL();
   I2C_SDA();
}
#endif


/****************************************************************************
*name:   SetUartPrint(void)
*input:  non              
*output: non  

*description: 此函数设置Rxd、Txd使能
*history:   yshuizhou   2014/10/23    1.0    build   this  function
*****************************************************************************/
#ifdef UartPrintfEn  
void SetUartPrint(void)
{
   Uart_RXD();
   //Uart_TXD();
}
#endif


/****************************************************************************
*name:   SetPowerOnDelaytime(UCHAR Delaytime)
*input:  Delaytime              
*output: non  

*description: 设置上电开机背光延迟时间,200ms为基本单位。
*history:   yshuizhou   2013/09/04    1.0    build   this  function
*****************************************************************************/
void SetPowerOnDelaytime(UCHAR Delaytime)
{
   UCHAR XDATA i;

   if(Delaytime)
   {
       for(i = 0;i<Delaytime;i++)
	   {
	      POS_ClearWatchDog();
		  DelayMs(200);
	   }
   }
}


/*************************************************************************
*name:    EnableChipAdc(AdcChannelType ADchanel)
*input:   ADchanel    ADC 通道选择  
*output:  返回当前选中通道的ADC值   
*update:  2011-12-07
*state:   try out

*description:  返回当前选中通道的ADC值   
            
*history:  yshuizhou   2011/12/20    0.2    build  this  function	
**************************************************************************/
UINT POS_EnableChipAdc(AdcChannelType Channel)  
{
	 UINT  XDATA CurrentADC = 0XFFFF;  

	 switch(Channel)
	 {
	   case CH0:
	   	    #if AMT_TYPE == AMT630A
			P0_OEN |=  _BIT0;	
			P0_IEN |=  _BIT0;	
            #endif //AMT_TYPE == AMT630A
            SetAUX0ENA();
			SetAUX0CMD();
            CheckAUX0ValInt();		
			CurrentADC = ADC_CH0_DATA_H;
		    CurrentADC <<= 8;
		    CurrentADC |= ADC_CH0_DATA_L;			
			ClearAUXValInt();				
			break;

	  case CH1:
            #if AMT_TYPE == AMT630A
			P0_OEN |=  _BIT1; 
			P0_IEN |=  _BIT1; 
            #endif //AMT_TYPE == AMT630A
			SetAUX1ENA();
			SetAUX1CMD();
			CheckAUX1ValInt();			
		    CurrentADC = ADC_CH1_DATA_H;
		    CurrentADC <<= 8;
		    CurrentADC |= ADC_CH1_DATA_L;			
			ClearAUXValInt();
			break;

  	  case CH2:
            #if AMT_TYPE == AMT630A
			P0_OEN |=  _BIT2;
			P0_IEN |=  _BIT2;   
            #endif //AMT_TYPE == AMT630A
            SetAUX2ENA();
			SetAUX2CMD();
			CheckAUX2ValInt();						
  	        CurrentADC = ADC_CH2_DATA_H;
	        CurrentADC <<= 8;
	        CurrentADC |= ADC_CH2_DATA_L;
			ClearAUXValInt();
			break;	

#if AMT_TYPE != AMT630A
	   case CH3:
            SetAUX3ENA();
			SetAUX3CMD();
			CheckAUX3ValInt();						
  	        CurrentADC = ADC_CH3_DATA_H;
	        CurrentADC <<= 8;
	        CurrentADC |= ADC_CH3_DATA_L;
			ClearAUXValInt();
			break;
#endif

	  default:
	  	   ClearAUXValInt();
	  	   break;
	 }   	 

	 #if TP0_ADC
	 printf("TP0_ADC >> the ADC Val is = %x\n",CurrentADC);
	 #endif

     return CurrentADC;
}




/****************************************************************************
*name:   SetPWM0(UINT Freq,UCHAR Duty)
*input:  Freq, Duty             
*output: void  

*description:
*history:   yshuizhou   2014/10/25    1.0    build   this  function
*****************************************************************************/
void SetPWM0(ULONG Freq,UCHAR Duty)
{
   ULONG XDATA tmpfreq;
   ULONG XDATA tmpduty;
   UCHAR XDATA tmppercent;
   
   tmpfreq = (UINT) (27000000/Freq);
   tmppercent = (UCHAR)(100/Duty);
   tmpduty = (UINT)(tmpfreq/tmppercent);
   
   PWM_CLK_SRC &=~_BIT6;
   PWM_CLK_SRC |= _BIT3;
   SelPWM0 |= (_BIT0|_BIT1);	 
   SelPWM0 &=~_BIT2;

   PWM_CTRL &=~_BIT4;
   PWM_CTRL |=  _BIT0;
   PWM0_CTRL0 = (UCHAR)(tmpfreq&0xff);
   PWM0_CTRL1 = (UCHAR)(tmpfreq>>8);
   PWM0_DUTY0 = ((UCHAR)(tmpduty&0xff));
   PWM0_DUTY1 = ((UCHAR)(tmpduty>>8));
}



/****************************************************************************
*name:   SetPWM1(UINT Freq,UCHAR Duty)
*input:  Val              
*output: void  

*description:
*history:   yshuizhou   2014/10/25    1.0    build   this  function
*****************************************************************************/
void SetPWM1(ULONG Freq,UCHAR Duty)
{
   ULONG XDATA tmpfreq;
   ULONG XDATA tmpduty;
   UCHAR XDATA tmppercent;
   
   tmpfreq = (UINT) (27000000/Freq);
   tmppercent = (UCHAR)(100/Duty);
   tmpduty = (UINT)(tmpfreq/tmppercent);
   
   PWM_CLK_SRC &=~_BIT6;
   PWM_CLK_SRC |= _BIT3;
   SelPWM1 |= (_BIT4|_BIT5);	 
   SelPWM1 &=~_BIT6;

   PWM_CTRL &=~_BIT5;
   PWM_CTRL |=  _BIT1;
   PWM1_CTRL0 = (UCHAR)(tmpfreq&0xff);
   PWM1_CTRL1 = (UCHAR)(tmpfreq>>8);
   PWM1_DUTY0 = ((UCHAR)(tmpduty&0xff));
   PWM1_DUTY1 = ((UCHAR)(tmpduty>>8));
}



/****************************************************************************
*name:   SetPWM2(UINT Val)
*input:  Val              
*output: void  

*description:
*history:   yshuizhou   2014/10/25    1.0    build   this  function
*****************************************************************************/
void SetPWM2(ULONG Freq,UCHAR Duty)
{
   ULONG XDATA tmpfreq;
   ULONG XDATA tmpduty;
   UCHAR XDATA tmppercent;
   
   tmpfreq = (UINT) (27000000/Freq);
   tmppercent = (UCHAR)(100/Duty);
   tmpduty = (UINT)(tmpfreq/tmppercent);
   
   PWM_CLK_SRC &=~_BIT6;
   PWM_CLK_SRC |= _BIT3;
   SelPWM2 |= (_BIT0|_BIT1);	 
   SelPWM2 &=~_BIT2;

   PWM_CTRL &=~_BIT6;
   PWM_CTRL |=  _BIT2;
   PWM2_CTRL0 = (UCHAR)(tmpfreq&0xff);
   PWM2_CTRL1 = (UCHAR)(tmpfreq>>8);
   PWM2_DUTY0 = ((UCHAR)(tmpduty&0xff));
   PWM2_DUTY1 = ((UCHAR)(tmpduty>>8));
}




/****************************************************************************
*name:   SetPWM3(UINT Val)
*input:  Val              
*output: void  

*description:
*history:   yshuizhou   2014/10/25    1.0    build   this  function
*****************************************************************************/
void SetPWM3(ULONG Freq,UCHAR Duty)
{
   ULONG XDATA tmpfreq;
   ULONG XDATA tmpduty;
   UCHAR XDATA tmppercent;
   
   tmpfreq = (UINT) (27000000/Freq);
   tmppercent = (UCHAR)(100/Duty);
   tmpduty = (UINT)(tmpfreq/tmppercent);
   
   PWM_CLK_SRC &=~_BIT6;
   PWM_CLK_SRC |= _BIT3;
   SelPWM3 |= (_BIT4|_BIT5);	 
   SelPWM3 &=~_BIT6;

   PWM_CTRL &=~_BIT7;
   PWM_CTRL |=  _BIT3;
   PWM3_CTRL0 = (UCHAR)(tmpfreq&0xff);
   PWM3_CTRL1 = (UCHAR)(tmpfreq>>8);
   PWM3_DUTY0 = ((UCHAR)(tmpduty&0xff));
   PWM3_DUTY1 = ((UCHAR)(tmpduty>>8));
}



/****************************************************************************
*name:   SysTimeDriver(void)
*input:  void            
*output: 

*description:
            这个函数是系统时间驱动，计算系统时间。 
*history:   yshuizhou   2012/07/16    1.0    build   this  function
*****************************************************************************/
#ifdef NoSignalPowerOffEn
BOOL POS_SysTimeDriver(void)
{
   static UINT XDATA currenTime3Cont = 0;
   static UINT XDATA preTime3Cont = 0;
   UINT   XDATA tempValBuf;
   
   /**********读T3的高低位****************/
   currenTime3Cont = T3_CNTH;
   currenTime3Cont <<= 8;
   currenTime3Cont |= T3_CNTL;

   if(currenTime3Cont > preTime3Cont)
   {
        tempValBuf = currenTime3Cont - preTime3Cont;
        if(tempValBuf >= 0x5b91)                   // 1s ->0x5b91 理论值
        {
            tempValBuf =tempValBuf - 0x5b91;
            currenTime3Cont -= tempValBuf;
            preTime3Cont =  currenTime3Cont;    //更新
            //这里就要对时钟加一秒
            if(++g_ucContBufSecond >=60)
            {
               return TRUE;
            }
        }
    }
    else
    {
        tempValBuf = 0xffff - preTime3Cont;
        tempValBuf += currenTime3Cont;
        if(tempValBuf >= 0x5b91)
        {
            tempValBuf = tempValBuf - 0x5b91;
            currenTime3Cont -= tempValBuf;
            preTime3Cont =  currenTime3Cont;       //更新
            //这里就要对时钟加一秒
            if(++g_ucContBufSecond >=60)
            {
               return TRUE;
            }
        }
    }
	return FALSE;
}
#endif

/****************************************************************************
*name:   ConfigCrtlMode(UCHAR CtrlMode)
*input:  CtrlMode              
*output: void  

*description:
      MCU: 表示MCU控制视频模块,ARKchip 为Mater模式.
      IIC: 表示IIC控制，ARKchip为Slave模式。

*history: Jordan.chen   2012/01/03    1.0    transplant   this  function
*****************************************************************************/
void ConfigCrtlMode(UCHAR CtrlMode)
{   
	if(CtrlMode == MCU)
	{
		MCU_CFG_REG  |= _BIT7; 
	}
	if(CtrlMode == IIC)
	{
		MCU_CFG_REG  &= (~_BIT7);
	}
}

/****************************************************************************
*name:   TurnOffBackLight(void)
*input:  void              
*output: void  

*description:
      关闭背光函数。

*history: Jordan.chen   2011/12/16    1.0    transplant   this  function
*****************************************************************************/
void TurnOffBackLight(void)
{
    printfStr("TurnOffBackLight");
	
	#ifdef BacklightEn
    hw_clrBacklight();
	#endif

	DelayMs(100);
	
	#ifdef BacklightEn
	hw_clrBIASEn();
    #endif

	g_bBackLightFlg = OFF;
}


/****************************************************************************
*name:   TurnOnBackLight(void)
*input:  void              
*output: void  

*description:
      打开背光函数。

*history: Jordan.chen	2011/12/16	  1.0	 transplant   this	function
*****************************************************************************/
void TurnOnBackLight(void)
{
    printfStr("TurnOnBackLight");

	#ifdef BacklightEn
	hw_setBIASEn();
    #endif

	DelayMs(100);	
	
	#ifdef BacklightEn
    hw_setBacklight();
	#endif
	
	g_bBackLightFlg = ON;
}


/****************************************************************************
*name:   EnterLowPowerMode(void)
*input:  void              
*output: void  

*description:
      待机低功耗函数

*history: Jordan.chen   2011/12/16    1.0    transplant   this  function
*****************************************************************************/
void EnterLowPowerMode(void)
{
    printfStr("EnterLowPowerMode\n");
    #if 0
    CLK_GATE0_EN &=~(_BIT7|_BIT6|_BIT5);
	CLK_GATE1_EN &=~(_BIT7|_BIT6|_BIT5|_BIT2|_BIT1|_BIT0);
	CLK_GATE2_EN &=~(_BIT7|_BIT6|_BIT5|_BIT4|_BIT3|_BIT2|_BIT1|_BIT0);
	ENH_PLL &=~(_BIT3|_BIT2);
	VIDEO_SOG_EN &=~(_BIT1|_BIT0);
    #endif
}


/****************************************************************************
*name:   ExitLowPowerMode(void)
*input:  void              
*output: void  

*description:
      退出待机低功耗函数

*history: Jordan.chen   2011/12/16    1.0    transplant   this  function
*****************************************************************************/
void ExitLowPowerMode(void)
{
	printfStr("ExitLowPowerMode\n");
    #if 0
    CLK_GATE0_EN |=(_BIT7|_BIT6|_BIT5);
	CLK_GATE1_EN |=(_BIT7|_BIT6|_BIT5|_BIT2|_BIT1|_BIT0);
	CLK_GATE2_EN |=(_BIT7|_BIT6|_BIT5|_BIT4|_BIT3|_BIT2|_BIT1|_BIT0);
	ENH_PLL |=(_BIT3|_BIT2);
	VIDEO_SOG_EN |=(_BIT1|_BIT0);
	DelayMs(200);
	DECODER_RST |=_BIT0;
	DelayMs(10); 
	DECODER_RST &=~_BIT0;
	#endif
}


/****************************************************************************
*name:   SetNosiceSwitch(FLAG nosiceSw)
*input:  nosiceSw              
*output: void  

*description:
      降噪开关
      
*history: Jordan.chen   2011/12/16    1.0    transplant   this  function
*****************************************************************************/
void SetNosiceSwitch(FLAG nosiceSw)
{
	 nosiceSw = nosiceSw;
}



/****************************************************************************
*name:   SetVDETestSwitch(UCHAR blueScreeSw)
*input:  blueScreeSw               
*output: void  

*description:
      蓝屏开关

*history: Jordan.chen   2011/12/16    1.0    transplant   this  function
*****************************************************************************/	
void SetVDETestSwitch(UCHAR ScreeSw)
{    
     switch(ScreeSw)
	 {
	   case VDE_RED:
	   	    VDE_REG = 0X50;
	   	    break;

	   case VDE_GREEN:
	   	    VDE_REG = 0X51;
	   	    break;

	   case VDE_BLUE:
	   	    VDE_REG = 0X52;
	   	    break;

	   case VDE_GRAY:
	   	    VDE_REG = 0X53;
	   	    break;
			
	   case VDE_BLACK:
	   	    VDE_REG = 0X54;
	   	    break;

	   case VDE_WHITE:
	   	    VDE_REG = 0X55;
	   	    break;
			
       case VDE_CLOSE:
	   	    VDE_REG = 0X4F;
	   	    break;
			 
	   default:
	   	   break;
	 }
	 DelayMs(100);
}



/****************************************************************************
*name:   InitAdc(void)
*input:  void              
*output: void  

*description:
      初始化ADC 

*history: 
   1.Jordan.chen   2012/01/06    0.1    buil   this  function
*****************************************************************************/
void InitAdc(void)
{
    //adc clock:
    ADC_CLOCK = 0x06;//0x18 -> 1Mhz,0x0B  -> 2Mhz,0x08 -> 3Mhz,0x06 -> 4Mhz,0x04 -> 6Mhz
    
	//adc mode:
	ADC_CTRL_H = 0X20; 
	ADC_CTRL_M = 0X0F;
	ADC_CTRL_L = 0X00;
	
	//adc config
	ADC_CFG_L = 0X22;
	ADC_CFG_H = 0X37;
	
	//adc debounce counter
	ADC_DBNCE_CNT_L =0XFF;
	ADC_DBNCE_CNT_M = 0X0F;
	ADC_DBNCE_CNT_H = 0X00;

	//adc transform interval
	ADC_INTER_TIME_L=0xFF;
	ADC_INTER_TIME_H=0x0F; 

	//adc status
	ADC_INT_STATUS_L =0X00;
    ADC_INT_STATUS_H =0X00 ;
	
   	//adc interupt mask
	ADC_INT_M_L = 0XFF; 
	ADC_INT_M_H = 0XFF;   
}


/****************************************************************************
*name:   InitNoSignalBLOff(void)
*input:    void              
*output:  void  

*description:
        初始化低功耗无信号关背光。

*history: 
   1.Jordan.chen   2011/12/19    1.0    buil   this  function
*****************************************************************************/
#ifdef NoSignalBLOffEn
void InitNoSignalBLOff(void)
{
	VIDEO_SOG_EN |=(_BIT4|_BIT2); 
	VIDEO_SOG_EN |=_BIT3; 
	TRIM_VT_SOG |=(_BIT4|_BIT3|_BIT1|_BIT0);
	TRIM_VT_SOG &=~(_BIT5|_BIT2);
	TRIM_VIN2_SOG &=~(_BIT5|_BIT4);
	TRIM_VIN2_SOG |=_BIT6;
	TRIM_VREF1_SOG &=~_BIT7; 
	COMPHV_DETECT_EN = 0X14;
	COMPHV_EXIT_THR = 0X50;
	COMPHV_HDIFF = 0X20;
}
#endif


/****************************************************************************
*name:   InitGlobalPara(void)
*input:  void              
*output: void  

*description:
      ARK 初始化模块时钟。

*history: 
   1.Jordan.chen   2011/12/19    0.1    buil   this  function
*****************************************************************************/
void InitGlobalPara()
{
    printfStr("InitGlobalPara\n");

	InitAMT(); 
	ConfigPadMuxPara();
	ConfigStaticPara(g_sysSetting.Video.curSource); 
	ConfigDispZoomDynPara(DISP_16_9);
	ConfigColorSysDynPara(PAL);
	ConfigVideoInputSource(g_sysSetting.Video.curSource);
	ConfigUserParaSetting();
	ENH_PLL = 0X2C;   
	DelayMs(100);
	DECODER_RST |=_BIT0;
	DelayMs(10); 
	DECODER_RST &=~_BIT0;
}

