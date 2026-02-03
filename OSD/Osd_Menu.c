#define _OSD_MENU_C

#include "DataType.h"
#include "SystemConfig.h"
#include "Global.h"
#include "MsgMap.h"
#include "SysWorkPara.h"
#include "SysPower.h" 
#include "VideoProc.h"
#include "ConfigLCDPara.h"
#include "Debug.h"
#include "Delay.h"
#include "Mcu.h"
#include "Interrupt.h"
#include "AMT_Reg.h"
#include "AMT_Drv.h"
#include "AMT_Mcu.h"
#include "Osd_Menu.h"
#include "Osd_MenuPage.h"
#include "Osd_MenuTbl.h"


UCHAR KeyMsgProcess(MSG curMsg)
{
     UCHAR ucComd = COMD_Nothing;
	 
     switch(curMsg)
     {
			
	   case MSG_UPK_LEFT:
	   	    printfStr("MSG_UPK_LEFT");
			
			#ifdef LogoEn
			if(g_bLogoDisplayFlag)
	   		{
	   		  return NULL_CMD;
	   		}
			#endif

            SetSaveFlagEn();
	     	break;
			
	   case MSG_UPK_RIGHT:
	   	    printfStr("MSG_UPK_RIGHT");

			#ifdef LogoEn
			if(g_bLogoDisplayFlag)
	   		{
	   		  return NULL_CMD;
	   		}
			#endif

            SetSaveFlagEn();
	     	break;
			
	   case MSG_UPK_MENU:
	   	    printfStr("MSG_UPK_MENU");

			#ifdef LogoEn
			if(g_bLogoDisplayFlag)
	   		{
	   		  return NULL_CMD;
	   		}
			#endif

	     	break;
			
	   case MSG_UPK_POWER:
	   	    printfStr("MSG_UPK_POWER");
            SetSaveFlagEn();
	     	break;

	   case MSG_UPK_BRIGHTNESS:
	   	    printfStr("MSG_UPK_BRIGHTNESS");

			#ifdef LogoEn
			if(g_bLogoDisplayFlag)
	   		{
	   		  return NULL_CMD;
	   		}
			#endif

            SetSaveFlagEn();
	     	break;

	   case MSG_UPK_CONTRAST:
	   	    printfStr("MSG_UPK_CONTRAST");

			#ifdef LogoEn
			if(g_bLogoDisplayFlag)
	   		{
	   		  return NULL_CMD;
	   		}
			#endif

            SetSaveFlagEn();
	     	break;

	   case MSG_UPK_SATURATION:
	   	    printfStr("MSG_UPK_SATURATION");

			#ifdef LogoEn
			if(g_bLogoDisplayFlag)
	   		{
	   		  return NULL_CMD;
	   		}
			#endif

            SetSaveFlagEn();
	     	break;

	   case MSG_BATTERYADC:
	   	    printfStr("MSG_BATTERYADC");
	     	break;
			
		default:
			break;
     }
	 
     //按键OSD处理:
	 ucComd = FindComdInCurMenuItem(curMsg);	 
	 return ucComd;
}

/***********************************************************
*name:     	 FindComdInCurMenuItem(MSG curMsg)
*input:      curMsg
*output:     comd 
*update:     2012-01-13
*state:      allright

*description:   
           从当前的Item 找到相应的输入命令，并返回此命令值.(MSG -> COMD) 

*history:
************************************************************/
UCHAR FindComdInCurMenuItem(MSG curMsg)
{ 
    UCHAR XDATA ucComd = COMD_Nothing;	
    UCHAR XDATA ucIndex;
	
#define CheckInputSource ((CurrentMenuItem.KeyComdMap[ucIndex].Source == g_sysSetting.Video.curSource)||(CurrentMenuItem.KeyComdMap[ucIndex].Source == ALL_INPUT_SOURCE))

FindComdAgain:

	for(ucIndex=0;ucIndex<CurrentMenuItem.ComdCount; ucIndex++)
	{		
	    if((CurrentMenuItem.KeyComdMap[ucIndex].Msg == curMsg)&&CheckInputSource)
	    {   			
			if(CurrentMenuItem.KeyComdMap[ucIndex].cConditions & g_UserInputInfo.Status)
			{
				ucComd = CurrentMenuItem.KeyComdMap[ucIndex].Comd;  
				return ucComd;
			}
			else
			{
			    return COMD_Nothing;	
			}
	    }
	}
    /*表示此按键信息在当前菜单中无效，切换到根菜单*/
	if(FindMenuPageIndex(Osd_RootMenu) != g_ucMenuPageIndex)
	{   		
		g_ucMenuPageIndex = FindMenuPageIndex(Osd_RootMenu);
		g_ucMenuItemIndex = 0; 
		goto FindComdAgain;
	}
	return COMD_Nothing;	
}



BOOL ExectComd(ComdType OpratComd)
{
    BOOL OpratComdFlg = TRUE;
		
    while(OpratComdFlg)
    {
        OpratComdFlg = FALSE;
		
      	switch (OpratComd)
        {

			case COMD_IncValue:
			case COMD_DecValue:
		        if(CurrentMenuItem.AdjustFunction)
		        {
		             if(CurrentMenuItem.AdjustFunction(OpratComd))
		             {
		                  DrawOsdMenuItemValue(CurrentMenuItem.ItemValue,osdSel); 
		             }
		        }
				if(CurrentMenuItem.ExecFunction)
				{
					CurrentMenuItem.ExecFunction();
				}				
				break;
				  		
			case COMD_NextMenu:
			case COMD_PrevMenu:
				if(OpratComd == COMD_NextMenu)
				{
				      g_ucMenuPageIndex = GetNextMenu();
				}
				else
				{
				 	  g_ucMenuPageIndex = GetPreMenu();
				}
				//printf("prev g_ucMenuPageIndex = %x", g_ucMenuPageIndex);
			case COMD_RedrawMenu:
				if(FindMenuPageIndex(Osd_RootMenu) == g_ucMenuPageIndex)
				{   
				    g_ucMenuPageIndex = FindMenuPageIndex(Osd_BrightnessMenu);
					g_ucMenuItemIndex = 0;
				}
				//printf("g_ucMenuPageIndex = %x", g_ucMenuPageIndex);
				OsdBlockEnable(CurrentBlock);
				OsdConfigScaler(OsdScalerRatio);
				DrawOsdMenu();
				break;

			case COMD_SelPowerOnMode:	
				 if(IsPowerOn())
				 {
				    SetPowerOff();
				 }
				 else if(IsPowerOff())
				 {
				    SetPowerOn();
				 }
				 
			case COMD_Power:
				if(IsPowerOn())
				{
				    //printfStr("Osd_PowerOffMenu");
				    SetMenuIndex(Osd_PowerOffMenu);
				}
				else
				{
				    //printfStr("Osd_PowerOnMenu");
				    SetMenuIndex(Osd_PowerOnMenu);
				}

				if(CurrentMenuItem.ExecFunction)
				{   
				    CurrentMenuItem.ExecFunction();
				}

				#ifdef LogoEn 
				#if (LOGO_DISP_MODE == POWER_ON_DISP_LOGO)
				if(IsPowerOn())
				{   
					printfStr("Osd_LogoMenu");
					SetVDETestSwitch(LOGO_DISP_BACKCOLOR);
						   
					switch(g_sysSetting.Logo.logoID)
					{
						  case LOGO1:
						  	   printfStr("Osd_Logo1Menu");
						  	   SetMenuIndex(Osd_LOGO1Menu);
						  	   break;
							   
						  case LOGO2:
						  	   printfStr("Osd_Logo2Menu");
						  	   SetMenuIndex(Osd_LOGO2Menu);
						  	   break;
							   
						  case LOGO3:
						  	   printfStr("Osd_Logo3Menu");
						  	   SetMenuIndex(Osd_LOGO3Menu);
						  	   break;

						  case LOGO4:
						  	   printfStr("Osd_Logo4Menu");
						  	   SetMenuIndex(Osd_LOGO4Menu);
						  	   break;
							   
						 case LOGO5:
						  	   printfStr("Osd_Logo5Menu");
						  	   SetMenuIndex(Osd_LOGO5Menu);
						  	   break;	
							   
						 default:
						  	  printfStr("default Osd_Logo1Menu");
						  	  SetMenuIndex(Osd_LOGO1Menu);
						  	  break;
					}
					InitLogoMenuDat();
					OsdBlockEnable(CurrentBlock);
					OsdConfigScaler(OsdScalerRatio);
					DrawOsdMenu();	
					//TurnOnBackLight(); 
					POS_ClearWatchDog();
					DelayMs(4000);
					HideMenu();
					SetVDETestSwitch(VDE_CLOSE);
					ResetMenuIndex();
					InitOSD();			 
					SetMenuIndex(Osd_PowerOnMenu);
				}
				#elif(LOGO_DISP_MODE == NOSIGNAL_DISP_LOGO)
				//TurnOnBackLight();
				#endif
                #endif				 

				OsdBlockEnable(CurrentBlock);
				OsdConfigScaler(OsdScalerRatio);
				DrawOsdMenu();
				SetMenuIndex(Osd_RootMenu);
				break;

			case COMD_TurnOnBackLight:
				 //printfStr("COMD_TurnOnBackLight");
				 if(!g_bBackLightFlg)
				 {
                     #ifdef NoSignalBLOffEn 
					 ConfigVideoInputSource(g_sysSetting.Video.curSource);
					 ExitLowPowerMode();
					 POS_ClearWatchDog();
		             DelayMs(200);
					 POS_ClearWatchDog();
		             DelayMs(200);
					 POS_ClearWatchDog();
		             DelayMs(200);
                     #endif

				     TurnOnBackLight();
				 }
				 break;

			case COMD_TurnOffBackLight:
				//printfStr("COMD_TurnOffBackLight");
//				 if(g_bBackLightFlg)
//				 {
//					TurnOffBackLight(); 
//					SaveSetting();
//				 }
//				 #ifdef NoSignalBLOffEn 
//				 EnterLowPowerMode();
//                 #endif
				 break;

			case COMD_OvpBackLight:
				 if(g_bBackLightFlg)
				  {
				   TurnOffBackLight();
				  }	
				  break;

			case COMD_BrightnessInc:
			case COMD_BrightnessDec:
			case COMD_Brightness:
				//printfStr("COMD_Brightness");
				SetMenuIndex(Osd_QuicklyBrightnessMenu);	
				
				#ifdef OsdEn
				if(g_ucOsdEixt & OsdBrightness)
				{
					OsdBlockEnable(CurrentBlock);
					OsdConfigScaler(OsdScalerRatio);
					DrawOsdMenu();
					g_ucOsdEixt &= ~OsdBrightness;
					g_ucOsdEixt |= OsdContrast;
					g_ucOsdEixt |= OsdSaturation;
				}
				#endif
				
				if(CurrentMenuItem.AdjustFunction)
				{
				   if(CurrentMenuItem.AdjustFunction(OpratComd))
				   {
				      #ifdef OsdEn
					  DrawOsdMenuItemValue(CurrentMenuItem.ItemValue,osdSel); 
					  #endif
				   }
				}
				if(CurrentMenuItem.ExecFunction)
				{
					CurrentMenuItem.ExecFunction();
				}
				break;
				
            case COMD_ContrastInc:
			case COMD_ContrastDec:
			case COMD_Contrast:
				//printfStr("COMD_Contrast");
				SetMenuIndex(Osd_QuicklyContrastMenu);
				
				#ifdef OsdEn
				if(g_ucOsdEixt & OsdContrast)
				{
					OsdBlockEnable(CurrentBlock);
					OsdConfigScaler(OsdScalerRatio);
					DrawOsdMenu();
					g_ucOsdEixt |= OsdBrightness;
					g_ucOsdEixt &= ~OsdContrast;
					g_ucOsdEixt |= OsdSaturation;
				}
				#endif
				
				if(CurrentMenuItem.AdjustFunction)
				{
				   if(CurrentMenuItem.AdjustFunction(OpratComd))
				   {
				      #ifdef OsdEn
					  DrawOsdMenuItemValue(CurrentMenuItem.ItemValue,osdSel); 
					  #endif
				   }
				}
				if(CurrentMenuItem.ExecFunction)
				{
					CurrentMenuItem.ExecFunction();
				}
				break;

			case COMD_SaturationInc:
			case COMD_SaturationDec:
			case COMD_Saturation:
				//printfStr("COMD_Saturation");
				SetMenuIndex(Osd_QuicklySaturationMenu);
				
				#ifdef OsdEn
				if(g_ucOsdEixt & OsdSaturation)
				{
					OsdBlockEnable(CurrentBlock);
					OsdConfigScaler(OsdScalerRatio);
					DrawOsdMenu();
					g_ucOsdEixt |= OsdBrightness;
					g_ucOsdEixt |= OsdContrast;
					g_ucOsdEixt &= ~OsdSaturation;
				}
				#endif
				
				if(CurrentMenuItem.AdjustFunction)
				{
				   if(CurrentMenuItem.AdjustFunction(OpratComd))
				   {
				      #ifdef OsdEn
					  DrawOsdMenuItemValue(CurrentMenuItem.ItemValue,osdSel);
					  #endif
				   }
				}
				if(CurrentMenuItem.ExecFunction)
				{
					CurrentMenuItem.ExecFunction();
				}
				break;

		    case COMD_BatteryAdc:
				 //printfStr("COMD_BatteryAdc");
				 #ifdef LowBaterryDetecEn 
				 SetMenuIndex(Osd_BatteryAdcMenu);
				 if(g_ucOsdEixt & OsdBatteryAdc)
				 {
					OsdBlockEnable(CurrentBlock);
					OsdConfigScaler(OsdScalerRatio);
					DrawOsdMenu();
					g_ucOsdEixt &= ~OsdBatteryAdc;
				 }
				 if(CurrentMenuItem.AdjustFunction)
				 {
				    if(CurrentMenuItem.AdjustFunction(OpratComd))
				    {
				       DrawOsdMenuItemValue(CurrentMenuItem.ItemValue,osdSel);
				    }
				 }
				 #endif
				 break;

			case COMD_RedrawLogo:
				 printfStr("COMD_RedrawLogo");
				 SetVDETestSwitch(LOGO_DISP_BACKCOLOR);
				 switch(g_sysSetting.Logo.logoID)
				 {
						case LOGO1:
							   printfStr("Osd_Logo1Menu");
							   SetMenuIndex(Osd_LOGO1Menu);
							   break;
						   
						case LOGO2:
							   printfStr("Osd_Logo2Menu");
							   SetMenuIndex(Osd_LOGO2Menu);
							   break;
						   
						case LOGO3:
							   printfStr("Osd_Logo3Menu");
							   SetMenuIndex(Osd_LOGO3Menu);
							   break;

						case LOGO4:
							   printfStr("Osd_Logo4Menu");
							   SetMenuIndex(Osd_LOGO4Menu);
							   break;
						   
						case LOGO5:
							   printfStr("Osd_Logo5Menu");
							   SetMenuIndex(Osd_LOGO5Menu);
							   break;	
						   
						default:
							  printfStr("default Osd_Logo1Menu");
							  SetMenuIndex(Osd_LOGO1Menu);
							  break;
				  }
				 
				  #ifdef LogoEn
				  InitLogoMenuDat(); 
				  #endif
				  
				 OsdBlockEnable(CurrentBlock);
				 OsdConfigScaler(OsdScalerRatio);
				 DrawOsdMenu();	
				 break;

			case COMD_ClearLogo:
				 //printfStr("COMD_ClearLogo");
				 HideMenu();
				 SetVDETestSwitch(VDE_CLOSE);
				 ResetMenuIndex();
				 g_ucOsdEixt |= OsdBatteryAdc;
				 InitOSD();	
				 break;
				 
			case COMD_OsdExit:
				HideMenu();
				ResetMenuIndex();
				SaveSetting();				
				return FALSE;
				break;

		    case COMD_OsdStorage:
				printfStr("COMD_OsdStorage");
		        SaveSetting();
				break;
				
	  	    default:
	            return FALSE;
	      	    break;
        }
    }
	return 1;
}

void MenuProcessKey(BYTE OpratComd)
{
  	if (OpratComd)
  	{
		if(IsPowerOff())
		{
			if (OpratComd!=COMD_Power)
			{
			   	OpratComd=COMD_Nothing;
			}
		}
		if (ExectComd(OpratComd))
		{ 
			g_sysSetting.Osd.dispTime= CurrentMenu->TimeOut;
		}
  	}
}




//========================================================
//               Draw Menu functions
//========================================================

void InitOsdBlock(void)
{
    ConfigOsdBlockStarIndexAddr();
}

void InitOSD(void)
{  
    printfStr("InitOSD\n");
	OsdHide();
	OsdClear();
	OsdCofigPalette();
	OsdIconSize(ICON_SIZE_X,ICON_SIZE_Y);
	OsdConfigAlpha(ENABLE,OSD_BACK_BLENDING,5);
	OsdConfigBitmapStarIndex(ICONBITMAP_SATRT_INDEX);	
	OsdConfigBright(7);
	#if(ICON_SIZE == SIZE_12X16)
	DMALoadFontRam((ULONG)AMT630FontLib&0X000FFFF,0<<4,5440);  // 170
	LoadMulCharToFontram(170,4,AMT630Font_Char);
	#elif(ICON_SIZE == SIZE_16X22)
	LoadMulCharToFontram(0,180,FontRam_Char);
	#endif
}


/******************************************************************
*Name: void DrawOsdTitel(TitelType *pTitel)
*input:  pTitel  标题指针
         status     状态: 画状态， 选择状态， 
*output: void
      
*Description: 画标题函数。

*history: 1.Jordan.chen   2012/02/21    0.1    buil   this  function
*******************************************************************/
void DrawOsdTitel(TitelType *pTitel,UINT status)
{
    UCHAR XDATA ucForeColor,ucBackColor;
	
    //printfStr("DrawOsdTitel");
    while(1)
    {
         if(pTitel == NULL)
         {
            break;
         }
		 if(status&osdDraw)
		 {
			 ucForeColor = pTitel->ForeColor;
			 ucBackColor = pTitel->BackColor;
		 }
		 if(status&osdSel)
		 {
			 ucForeColor = pTitel->SelForeColor;
			 ucBackColor = pTitel->SelBackColor;
		 }
		 
	    if(pTitel->DisplayText)
	    {
	         OsdDrawStr(pTitel->XPos, pTitel->YPos,COLOR(ucForeColor,ucBackColor),pTitel->DisplayText());
	    }
		if(pTitel->Flags & osdEnd)
		{
		      break;
		}
		pTitel++;
    }
   
}

/******************************************************************
*Name: void DrawOsdIcon(IconType* pIcon,UCHAR status)
*input:  pIcon  画ICON 指针
         status     状态: 画状态， 选择状态， 
*output: void
      
*Description: 画icon函数。

*history: 1.Jordan.chen   2012/02/21    0.1    buil   this  function
*******************************************************************/
void DrawOsdIcon(IconType* pIcon,UINT status)
{
    UCHAR XDATA ucBackColor;
	
    //printfStr("DrawOsdIcon");
    while(1)
    { 
         if(pIcon == NULL)
         {
             break;
         }
		 
		 if(status&osdDraw)
		 {
			 ucBackColor = pIcon->BackColor;
		 }
		 if(status&osdSel)
		 {
			 ucBackColor = pIcon->SelBackColor;
		 }
	    if(pIcon->DispalyIcon)
	    {   
	        OsdDrawIcon(pIcon->XPos, pIcon->YPos,pIcon->XSize, pIcon->YSize,ucBackColor, pIcon->DispalyIcon());
	    }  
		
		if(pIcon->Flags & osdEnd)
		{
		      break;
		}
		pIcon++;
		
    }

	
}


/******************************************************************
*Name: void DrawOsdMenuItemNumber(DrawNumberType *pNumberItem,UCHAR status)
*input:  pNumberItem  画数字指针
         status     状态: 画状态， 选择状态， 
*output: void
      
*Description: 画数字

*history: 1.Jordan.chen   2012/02/21    0.1    buil   this  function
*******************************************************************/
void DrawOsdMenuItemNumber(DrawNumberType *pNumberItem,UINT status)
{
    UCHAR XDATA ucForeColor,ucBackColor;
	
    //printfStr("DrawOsdMenuItemNumber");
	if(pNumberItem!=NULL)
	{
	     if(status&osdDraw)
		 {
			 ucForeColor = pNumberItem->ForeColor;
			 ucBackColor = pNumberItem->BackColor;
		 }
		 if(status&osdSel)
		 {
			 ucForeColor = pNumberItem->SelForeColor;
			 ucBackColor = pNumberItem->SelBackColor;
		 }
		 
	     if(pNumberItem->Flags & osdDecNum)
	     {
	          OsdDrawNum(pNumberItem->XPos,pNumberItem->YPos,COLOR(ucForeColor,ucBackColor),pNumberItem->GetValue());
	     }
		 if(pNumberItem->Flags & osdHexNum)
		 {
		      OsdDrawHex(pNumberItem->XPos,pNumberItem->YPos,COLOR(ucForeColor,ucBackColor),pNumberItem->GetValue());
		 }
	}
}

/******************************************************************
*Name: void DrawOsdMenuItemGuage(DrawGuageType *pGaugeItem,UCHAR status)
*input:  pNumberItem  画进度条
         status     状态: 画状态， 选择状态， 
*output: void
      
*Description: 画进度条

*history: 1.Jordan.chen   2012/02/21    0.1    buil   this  function
*******************************************************************/
void DrawOsdMenuItemGuage(DrawGuageType *pGaugeItem,UINT status)
{
    UCHAR XDATA ucForeColor,ucBackColor;
	
 	//printfStr("DrawOsdMenuItemGuage"); 
	if(pGaugeItem != NULL)
	{  
	     if(status&osdDraw)
		 {
			 ucForeColor = pGaugeItem->ForeColor;
			 ucBackColor = pGaugeItem->BackColor;
		 }
		 if(status&osdSel)
		 {
			 ucForeColor = pGaugeItem->SelForeColor;
			 ucBackColor = pGaugeItem->SelBackColor;
		 }
	    if(pGaugeItem->GetValue)
	    { 
	        OsdDrawGuage(pGaugeItem->XPos, pGaugeItem->YPos, pGaugeItem->Length, COLOR(ucForeColor,ucBackColor),pGaugeItem->GetValue());
	    }	
	}
}
  
/******************************************************************
*Name: void DrawOsdMenuItemOption(DrawOptionType *radioItem,UCHAR status)
*input:  pNumberItem  画选项(text)
         status     状态: 画状态， 选择状态， 
*output: void
      
*Description: 画选项(text)

*history: 1.Jordan.chen   2012/02/21    0.1    buil   this  function
*******************************************************************/
void DrawOsdMenuItemOption(DrawOptionType *pOptionItem,UINT status)
{

    UCHAR XDATA ucForeColor,ucBackColor;
	
	//printfStr("DrawOsdMenuItemOption");
	if(pOptionItem != NULL)
	{
	     if(status&osdDraw)
		 {
			 ucForeColor = pOptionItem->ForeColor;
			 ucBackColor = pOptionItem->BackColor;
		 }
		 if(status&osdSel)
		 {
			 ucForeColor = pOptionItem->SelForeColor;
			 ucBackColor = pOptionItem->SelBackColor;
		 }
		 if(pOptionItem->DisplayText)
		 {   
		 	 OsdDrawStr(pOptionItem->XPos, pOptionItem->YPos, COLOR(ucForeColor,ucBackColor),pOptionItem->DisplayText());
		 }
	}
}
/******************************************************************
*Name: void DrawOsdMenuItemValue(ItemValueType* pItemValue,UINT status)
*input:  pItemValue  画ITEM 的值 包括: 数字，进度条 ，选项
         status     状态: 画状态， 选择状态， 
*output: void
      
*Description: 画ITEM 的值 包括: 数字，进度条 ，选项

*history: 1.Jordan.chen   2012/02/21    0.1    buil   this  function
*******************************************************************/
void DrawOsdMenuItemValue(ItemValueType* pItemValue,UINT status)
{
    if(pItemValue == NULL)
    {
         return;
    }
		
    while(1)
    {
        if(pItemValue->DrawNumber)
        {
            DrawOsdMenuItemNumber(pItemValue->DrawNumber,status);
        }
        if(pItemValue->DrawGuage)
        {    
            DrawOsdMenuItemGuage(pItemValue->DrawGuage,status);
        }
        if(pItemValue->DrawOption)
        {
            DrawOsdMenuItemOption(pItemValue->DrawOption,status);
        }
        if(pItemValue->Flags&osdEnd)
        {
        	break;
        }    
        pItemValue++;
    }
}
/******************************************************************
*Name: DrawOsdMenuItem(MenuItemType *pMenuItem,UINT status)
*input:  pMenuItem  菜单条目指针，
         status     状态: 画状态， 选择状态， 
*output: void
      
*Description: 画菜单条目

*history: 1.Jordan.chen   2012/02/21    0.1    buil   this  function
*******************************************************************/
void DrawOsdMenuItem(MenuItemType *pMenuItem,UINT status) reentrant
{
    AdjustType  wcDrawItemCdtion;

	//首先判断画此菜单的条件。
    if(pMenuItem->CheckCondition)
    {
        wcDrawItemCdtion = pMenuItem->CheckCondition();
    }

    //判断是否有个性风格
	if(pMenuItem->DrawItemStyle)
	{
	    pMenuItem->DrawItemStyle();
	}

    if(pMenuItem->ItemIcons)
    {   
    	DrawOsdIcon(pMenuItem->ItemIcons,status);
    }
	if(pMenuItem->ItemTitels)
	{
		DrawOsdTitel(pMenuItem->ItemTitels,status);
	}	
    DrawOsdMenuItemValue(pMenuItem->ItemValue,status);
	
}

/******************************************************************
*Name: void DrawOsdMenu(void)
*input:  void
*output: void
      
*Description: 画菜单

*history: 1.Jordan.chen   2012/02/21    0.1    buil   this  function
*******************************************************************/
void DrawOsdMenu(void)
{
    AdjustType  XDATA wcDrawMenuCdtion;
	UCHAR XDATA i;

	printfStr(CurrentMenu->MenuName);

	//首先判断画此菜单的条件。
    if(CurrentMenu->CheckCondition)
    {
        wcDrawMenuCdtion = CurrentMenu->CheckCondition();
	}
	
    //判断是否需要隐藏。
	if(CurrentMenu->Flags & osdInvisible)
	{
	    HideMenu();
		//printfStr("hide osd\n");
	}
	else
	{
	    //判断是否需要初始化:重新设定大小等。。
	    if((CurrentMenu->Flags & osdRedraw)&&(wcDrawMenuCdtion.Flags & osdVisible))
	    {  
	        printfStr("redraw osd menu");			
		    HideMenu();
			OsdBlockClear(CurrentBlock);	
			OsdConfigWndSize(CurrentMenu->XSize,CurrentMenu->YSize);
			OsdConfigWndPosition(CurrentMenu->XPos, CurrentMenu->YPos);
			OsdConfigBlockColor(COLOR(CurrentMenu->ForeColor,CurrentMenu->BackColor));
			if(CurrentMenu->DrawMenuStyle)
			{
	     		 CurrentMenu->DrawMenuStyle(); //画个性风格
			}
	    }	
		
		if(CurrentMenu->MenuIcons)
		{   
			DrawOsdIcon(CurrentMenu->MenuIcons,osdDraw);
		}
	    if(CurrentMenu->MenuTitels)
	    {
	    	DrawOsdTitel(CurrentMenu->MenuTitels,osdDraw);
	    }
		for(i=0; i<CurrentMenuItemCount; i++)
		{   
		    DrawOsdMenuItem(&CurrentMenu->MenuItems[i],osdDraw);
		}
		OsdBlockShow(CurrentBlock);
	}
}


UCHAR GetNextMenu(void)
{
    UCHAR XDATA ucNextPage, ucIndex;
	
	ucNextPage = CurrentMenu->NextPage;
	ucIndex = g_ucMenuPageIndex;

	//printf("ucIndex = %x", ucIndex);
	//printf("MenuCount = %x", (MenuCount));
			 
    while(1)
    {
         if(g_ucMenuPageIndex<(MenuCount))
         {
             g_ucMenuPageIndex++;
         }
		 else
		 {
		     g_ucMenuPageIndex = 0;
		 }		
		 if(CurrentMenu->CurrentPage == ucNextPage)
		 { 
			if(CurrentMenu->Flags & osdVisible)
			{	
				if(CurrentMenu->CheckCondition)
				{
					if(CurrentMenu->CheckCondition().Flags & osdVisible)
					{
					     return g_ucMenuPageIndex;
					} 
					else
					{
					     ucNextPage = CurrentMenu->NextPage;
					}
				}
				else
				{
					return g_ucMenuPageIndex;
				}
			}
		 }	 
		 if(g_ucMenuPageIndex == ucIndex)
		 {   
		     break;
		 }
    }
	return g_ucMenuPageIndex;
}

UCHAR GetPreMenu(void)
{
    UCHAR XDATA ucPrePage, ucIndex;
	
	ucPrePage = CurrentMenu->PrevPage;
	ucIndex = g_ucMenuPageIndex;
    while(1)
    {
         if(g_ucMenuPageIndex>0)
         {
             g_ucMenuPageIndex--;
         }
		 else
		 {
		     g_ucMenuPageIndex = (MenuCount-1);
		 }
		 if(CurrentMenu->CurrentPage == ucPrePage)
		 {
			 if(CurrentMenu->Flags & osdVisible)
			 {	
				if(CurrentMenu->CheckCondition)
				{
					if(CurrentMenu->CheckCondition().Flags & osdVisible)
					{
						return g_ucMenuPageIndex;
					} 
					else
					{
					     ucPrePage = CurrentMenu->PrevPage;
					}
				}
				else
				{
				    return g_ucMenuPageIndex;
				}
			 }
		 }
		 
		 if(g_ucMenuPageIndex == ucIndex)
		 {
		     break;
		 }
    }
	return g_ucMenuPageIndex;
}

UCHAR FindMenuPageIndex(UCHAR menuPage)
{
    UCHAR XDATA i=0;
	
    //printf("menu count = %x", (MenuCount));
    
	for(i=0;i<MenuCount;i++)
	{
	      if((tblMenus[i]->CurrentPage) == menuPage)
	      {
	           return i;
	      }
	}
	return 0;
}

void ConfigOsdBlockStarIndexAddr(void)
{
     UCHAR XDATA i;
	 UINT  XDATA Block0MaxSize=0;
	 UINT  XDATA Block1MaxSize=0;
	 UINT  XDATA Block2MaxSize=0;
	 UINT  XDATA Block3MaxSize=0;
	 UINT  XDATA Block4MaxSize=0;
	 
     for(i=0;i<MenuCount;i++)
     {
          switch(tblMenus[i]->OsdBlockId)
          {
                case OsdBlock0:
					if(Block0MaxSize<(tblMenus[i]->XSize*tblMenus[i]->YSize))
					{
					    Block0MaxSize = tblMenus[i]->XSize*tblMenus[i]->YSize;
					}
					break;
				case OsdBlock1:
					if(Block1MaxSize<(tblMenus[i]->XSize*tblMenus[i]->YSize))
					{
					    Block1MaxSize = tblMenus[i]->XSize*tblMenus[i]->YSize;
					}
					break;
				case OsdBlock2:
					if(Block2MaxSize<(tblMenus[i]->XSize*tblMenus[i]->YSize))
					{
					    Block2MaxSize = tblMenus[i]->XSize*tblMenus[i]->YSize;
					}
					break;
				case OsdBlock3:
					if(Block3MaxSize<(tblMenus[i]->XSize*tblMenus[i]->YSize))
					{
					    Block3MaxSize = tblMenus[i]->XSize*tblMenus[i]->YSize;
					}
					break;
				case OsdBlock4:
					if(Block4MaxSize<(tblMenus[i]->XSize*tblMenus[i]->YSize))
					{
					    Block4MaxSize = tblMenus[i]->XSize*tblMenus[i]->YSize;
					}
					break;
					
				default:
					break;
          }
     }
	 if((Block0MaxSize+Block1MaxSize+Block2MaxSize+Block3MaxSize+Block4MaxSize)<OsdIndexRamSize)
	 {
		 g_OsdContrller.block0Size = Block0MaxSize;
		 g_OsdContrller.block1Size = Block1MaxSize;
		 g_OsdContrller.block2Size = Block2MaxSize;
		 g_OsdContrller.block3Size = Block3MaxSize;
		 g_OsdContrller.block4Size = Block4MaxSize;

		//printf("g_OsdContrller.block0Size = %d", g_OsdContrller.block0Size);
		//printf("g_OsdContrller.block1Size = %d", g_OsdContrller.block1Size);
		//printf("g_OsdContrller.block2Size = %d", g_OsdContrller.block2Size);
		//printf("g_OsdContrller.block3Size = %d", g_OsdContrller.block3Size);
	    //printf("g_OsdContrller.block4Size = %d", g_OsdContrller.block4Size);
		 
	     OsdConfigBlockIndexStarAddr(OsdBlock1,Block0MaxSize);
		 OsdConfigBlockIndexStarAddr(OsdBlock2,Block0MaxSize+Block1MaxSize);
		 OsdConfigBlockIndexStarAddr(OsdBlock3,Block0MaxSize+Block1MaxSize+Block2MaxSize);
		 OsdConfigBlockIndexStarAddr(OsdBlock4,Block0MaxSize+Block1MaxSize+Block2MaxSize+Block3MaxSize);
     }
	 else
	 {
	     printfStr("Osd Block Size Error!!!!");
		 printfStr("block all size add < 512");
	 }
	
	 
}

void HideMenu(void)
{
    OsdHide();
	OsdColorChangeSwitch(OFF);
}

void ResetMenuIndex(void)
{
    SetMenuIndex(Osd_RootMenu);
	g_ucMenuPageIndex = 0;
    g_ucOsdEixt =  OsdBrightness|OsdContrast|OsdSaturation|OsdBatteryAdc;
}


void SetMenuIndex(UCHAR menuPage)
{
	if(FindMenuPageIndex(menuPage) != g_ucMenuPageIndex) 
	{   
		g_ucMenuPageIndex = FindMenuPageIndex(menuPage);
		g_ucMenuItemIndex = 0;
	}
}

