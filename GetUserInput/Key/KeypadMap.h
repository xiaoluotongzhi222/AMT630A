/***********************************************************************
*Copyright (C) 2005 深圳艾科创新有限公司产品应用一部
* All rights reserved.

*File name: 　 KeypadMap.h
*Version:    　0.2
*Author:       yshuizhou
*update:      2011-12-30

*Description:
            
*History:
************************************************************************/
#ifndef KEY_PAD_MAP_H__
#define KEY_PAD_MAP_H__


#ifdef KeyDetectEn 
#if(KEY_TYPE == ADC_KEY)

#if hw_upResistance 
#define hw_keyAdcVal(rVal)  ((UINT)(4096*((float)rVal*hw_keyVoltage/(((float)rVal+hw_upResistance)*3.3))))>>4
#endif

#if hw_downResistance
#define hw_keyAdcVal(rVal)  ((UINT)(4096*((float)hw_downResistance*hw_keyVoltage/(((float)rVal+hw_downResistance)*3.3))))>>4
#endif

#endif
#endif


/*
Key 配置:
*/
#ifdef KeyDetectEn 
#if(KEY_TYPE == ADC_KEY)
#if(KEY_PAD_ID == KP_ARK_SDK_V01)
//key val : adcCh + adcVal
#define hw_KEY_LEFT     	makeUint16 (CH1, hw_keyAdcVal(1500))
#define hw_KEY_RIGHT    	makeUint16 (CH1, hw_keyAdcVal(1000))
#define hw_KEY_MENU     	makeUint16 (CH1, hw_keyAdcVal(470))

//Adc Key Cmd Map
KeyCmdMap CODE SysAdcKeyCmdMap[] =
{
	{hw_KEY_LEFT ,	   KEY_LEFT         }, 
	{hw_KEY_RIGHT ,	   KEY_RIGHT        },
	{hw_KEY_MENU,      KEY_MENU         },
};


//Adc Key Msg Map:
KeyMsgMap CODE SysAdcKeyMsgMap[] =
{
	{MSG_UPK_LEFT,  		KEY_LEFT  	},
	{MSG_UPK_RIGHT, 		KEY_RIGHT	},
	{MSG_UPK_MENU, 		    KEY_MENU    },  
};


#endif//#if(KEY_PAD_ID == KP_ARK_SDK_V01)
#endif// #if(KEY_TYPE == ADC_key)
#endif// end KeyDetectEn
#endif// end KEY_PAD_MAP_H__





