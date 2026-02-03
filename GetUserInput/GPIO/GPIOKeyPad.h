/*******************************************************************************
*Copyright (C) 2005 深圳艾科创新有限公司产品应用一部
* All rights reserved.

*File name: 　 GPIOKeyPad.h  
*Version:      0.1
*update:       2012-03-12
*Description:
  		   此文件是对GPIO 按键的采集与处理头文件。

*History:  yshuizhou   2012/05/31    0.1    build  this  moudle
******************************************************************************/
#ifndef  _GPIO_KEY_PAD_H__
#define  _GPIO_KEY_PAD_H__

#ifdef KeyDetectEn 
#if KEY_TYPE == GPIO_KEY

#ifdef _GPIO_KEY_PAD_C_
#define _GPIO_KP_EXTERN_ 
#else
#define _GPIO_KP_EXTERN_ extern
#endif



_GPIO_KP_EXTERN_ UCHAR POS_GetGPIOKeyCmd(void);
_GPIO_KP_EXTERN_ KeyInfor POS_TransferGPIOKeyMsg(UCHAR GpioKeyCmd);


#endif  //#if KEY_TYPE == GPIO_KEY
#endif   //#ifdef KeyDetectEn 
#endif   // #ifndef  _GPIO_KEY_PAD_H__
