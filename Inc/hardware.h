/***********************************************************************
*Copyright (C) 2005 深圳艾科创新有限公司产品应用一部
* All rights reserved.

*File name: 　 if_hardware.h
*Version:    　0.1
*Author:       cjinzong
*update:       20100128

*Description:
           这个文件是用来定义本软件可以支持的硬件资源。
*History:
************************************************************************/
#ifndef _IF_HARDWARE_H__
#define _IF_HARDWARE_H__



/*<<<<<<<<<<<<<<<<<<<<< AMT CHIP >>>>>>>>>>>>>>>>>>>>>*/
#define AMT630A                       	0



/*<<<<<<<<<<<<<<<<<<<<< video channel define >>>>>>>>>>>>>>>>>>>>>*/
#define CVBS1               			0
#define CVBS3                          	1


/*<<<<<<<<<<<<<<<<<<<<< icon size define >>>>>>>>>>>>>>>>>>>>>*/
#define SIZE_12X16             		0
#define SIZE_16X22              		1


/*<<<<<<<<<<<<<<<<<<<<<<<<< E2p define>>>>>>>>>>>>>>>>>>>>>*/
#define _NULL_E2PROM_                 	0
#define _E2P_24C02_                   	1
#define _E2P_24C04_                   	2
#define _E2P_24C08_                   	3
#define _E2P_24C16_                   	4
#define _E2P_24C32_                   	5


/*<<<<<<<<<<<<<<<<<<<<<<<<<RGB data format define>>>>>>>>>>>>>>*/
#define CCIR656          				0
#define CCIR656_640RGB   				1
#define CCIR656_720RGB  				2
#define CCIR601          				3
#define _8BIT_RGB_HV   				4
#define _8BIT_RGB_DEN  				5
#define _18BIT_RGB_HV     				6
#define _18BIT_RGB_DEN    				7
#define _24BIT_RGB_HV     				8
#define _24BIT_RGB_DEN    				9


/*<<<<<<<<<<<<<<<<<<<<<<<<Key type define >>>>>>>>>>>>>>>>*/
#define ADC_KEY                  		1
#define DIANWEIQI_KEY           		2
#define GPIO_KEY                   	3


/*<<<<<<<<<<<<<<<<<<<<<<<<KeyPad define>>>>>>>>>>>>>>>>>>*/
#define KP_ARK_SDK_V01            		1
#define KP_XXXX                   		2




/*<<<<<<<<<<<<<<<<<<<<<<Battery define>>>>>>>>>>>>>>>>>>>>*/
#define _NULL_BATTERY_             	0
#define BATTERY_CHANGE              	1




/*<<<<<<<<<<<<<<<<<<<<<<<<Back Light>>>>>>>>>>>>>>>>>>>>>>*/
#define _NULL_BL_                   	0
#define DC_PWM0_CTRL                 	1
#define DC_PWM1_CTRL                 	2
#define DC_PWM2_CTRL                	3
#define DC_PWM3_CTRL                	4
#define GPIO_CTRL                 		5


/*<<<<<<<<<<<<<<<<<<<<<<LOGO disp mode >>>>>>>>>>>>>>>>>>>*/
#define POWER_ON_DISP_LOGO     		1
#define NOSIGNAL_DISP_LOGO     		0


#endif

