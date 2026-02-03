/*******************************************************************************
*Copyright (C) 2005 深圳艾科创新有限公司产品应用一部
* All rights reserved.

*File name: 　 DianWeiQiKeyPad.h  
*Version:      0.1
*update:       2012-03-12
*Description:
  		   此文件是对DIANWEIQI 按键的采集与处理头文件。

*History:  yshuizhou   2012/03/12    0.1    build  this  moudle
******************************************************************************/
#ifndef  _DIANWEIQI_KEY_PAD_H__
#define  _DIANWEIQI_KEY_PAD_H__

#ifdef KeyDetectEn 
#if KEY_TYPE == DIANWEIQI_KEY

#ifdef _DIANWEIQI_KEY_PAD_C_
#define _DIANWEIQI_KP_EXTERN_ 
#else
#define _DIANWEIQI_KP_EXTERN_ extern
#endif


#define DianWeiQiChannelBit           (_BIT12|_BIT13) //电位器通道信息
#define DianWeiQiAdjMaxStep           60    //采集电位器ADC实际调节阶数，此值不能随意修改。


_DIANWEIQI_KP_EXTERN_ UINT POS_GetBestDianWeiQiKeyVal(UINT* AdcBuf, UCHAR Length);
_DIANWEIQI_KP_EXTERN_ UINT  POS_FilterDianWeiQiKeyVal(UINT * AdcValueBuf,UCHAR len);
_DIANWEIQI_KP_EXTERN_ UINT  POS_GetDianWeiQiKeyValue(void);
_DIANWEIQI_KP_EXTERN_ void POS_InitDianWeiQiKey(void);
_DIANWEIQI_KP_EXTERN_ UINT SelDianWeiQiChannelVal(UCHAR Channel);
_DIANWEIQI_KP_EXTERN_ void UpdataDianWeiQiInitPara(UCHAR curChannel);
_DIANWEIQI_KP_EXTERN_ KeyInfor POS_TransferDianWeiQiKeyMsg(UINT KeyVal);
_DIANWEIQI_KP_EXTERN_ void POS_InitDianWeiQiKeyMsg(void);

#endif  //#if KEY_TYPE == ADC_KEY
#endif   //#ifdef KeyDetectEn 
#endif   // #ifndef  _ADC_KEY_PAD_H__
