/*******************************************************************************
*Copyright (C) 2005 深圳艾科创新有限公司产品应用一部
* All rights reserved.

*File name: 　 Delay.c	  
*Version:      0.1
*update:       2011-12-16
*Description:
  		    延时时间函数的定义。
  		  
*History:  Jordan.chen   2011/12/16    0.1    build  this  moudle
******************************************************************************/
#define _DELAY_C_

#include "DataType.h"
#include "systemConfig.h"
#include "global.h"


void DelayUs(UINT cont_time)
{
    while(cont_time--)
	{
	  _nop_();
	}
}

void DelayMs(UINT contTime)
{
	while(contTime--)
	{
	   DelayUs(400);
	}
}


