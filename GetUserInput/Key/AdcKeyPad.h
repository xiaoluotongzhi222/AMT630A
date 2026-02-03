/*******************************************************************************
*Copyright (C) 2005 深圳艾科创新有限公司产品应用一部
* All rights reserved.

*File name: 　 AdcKeyPad.h  
*Version:      0.1
*update:       2011-12-08
*Description:
  		   此文件是对ADC 按键的采集与处理头文件。

*History:  Jordan.chen   2011/12/08    0.1    build  this  moudle
******************************************************************************/
#ifndef  _ADC_KEY_PAD_H__
#define  _ADC_KEY_PAD_H__

#ifdef KeyDetectEn 
#if KEY_TYPE == ADC_KEY

#ifdef _ADC_KEY_PAD_C_
#define _ADC_KP_EXTERN_ 
#else
#define _ADC_KP_EXTERN_ extern
#endif


#define KeyOkFlg                _BIT15  //按键OK标志
#define AdcChannelBit           (_BIT12|_BIT13) //按键通道标志


_ADC_KP_EXTERN_ UINT  POS_GetBestAdcKeyVal(UINT* AdcBuf, UCHAR Length);
_ADC_KP_EXTERN_ UINT  POS_FilterAdcKeyVal(UINT * AdcValueBuf,UCHAR len);
_ADC_KP_EXTERN_ UINT  POS_ReleaseAdcKey(UINT AdcKeyVal);
_ADC_KP_EXTERN_ UINT  POS_GetAdcKeyValue(void);
_ADC_KP_EXTERN_ UCHAR POS_TransferAdcKeyCmd(UINT KeyVal);
_ADC_KP_EXTERN_ KeyInfor POS_TransferAdcKeyMsg(UCHAR KeyCmd);


#endif  //#if KEY_TYPE == ADC_KEY
#endif   //#ifdef KeyDetectEn 
#endif   // #ifndef  _ADC_KEY_PAD_H__
