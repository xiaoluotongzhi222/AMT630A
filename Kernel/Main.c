/***********************************************************************
*Copyright (C) 2005 深圳艾科创新有限公司产品应用一部
* All rights reserved.

*File name: 　 Main.c
*Version:    　Ver-2.0
*Author:       cjinzong
*update:       2010-05-27

*Description:
               这个是系统的整个运行框架。
*History:  
   
************************************************************************/
#define _MAIN_C_

#include "DataType.h"
#include "SystemConfig.h"
#include "Global.h"
#include "MsgMap.h"
#include "Delay.h"
#include "SysPower.h"
#include "GetSysMsg.h"
#include "EventHandle.h"
#include "Debug.h"
#include "Mcu.h"
#include "Interrupt.h"
#include "Osd_menu.h"
#include "AMT_Reg.h"
#include "AMT_Drv.h"
#include "AMT_Mcu.h"
#include "udsf_tinyframe.h"
#include "prase_radar.h"
#define FONTRAM_PREFIX  '&' 
#define WAVE_START_COL 2  
//#define COL_RED     (0x01|0x30)
//#define COL_YELLOW  (0x04|0x30)
//#define COL_GREEN   (0x02|0x30)
#define COL_RED     (0x01)
#define COL_YELLOW  (0x04)
#define COL_GREEN   (0x02)
#define COL_WHITE   (0x0E)
UCHAR XDATA g_Right_BG_Color = 0x30;
#define RX_BUF_SIZE 128
UCHAR XDATA g_RxBuf[RX_BUF_SIZE];
UCHAR XDATA g_RxCnt = 0;
UCHAR XDATA g_RxTimeoutCnt = 0; 
bit g_FrameReady = 0;
RadarFrame XDATA g_RadarData;
extern void Draw_Big_Number(UCHAR startRow, UCHAR startLine, UCHAR num,UCHAR color) small;
extern void Draw_Radar_Segment(UCHAR row_idx, UCHAR seg_idx, UCHAR color, UCHAR screen_row, UCHAR screen_col_start) small;
extern void Clear_Half_Screen(UCHAR half,UCHAR color) small;
extern void Draw_Big_Dot(UCHAR startRow, UCHAR startLine,UCHAR color) small;
extern void OsdDrawStr(UCHAR x, UCHAR y, UCHAR color, UCHAR code *ptr) small;
UCHAR XDATA g_last_int = 0xFF;
UCHAR XDATA g_last_dec = 0xFF;
void TF_Platform_Send(uart_port_t port, const uint8* buf, uint32 len)
{
    uint32 XDATA i;
    if (port == UART_NUM_0)
    {
        ES = 0; 
        
        for(i = 0; i < len; i++)
        {
            TI = 0; 
            SBUF = buf[i];
            while(!TI);
            TI = 0;
        }
        

        ES = 1; 
    }
}
void Init_Split_Screen(void)
{
    UINT XDATA wcIndexAddr = 0;
    UINT XDATA curAddr = 0;
    UCHAR XDATA row, col;
    

    OsdBlockEnable(1); 
    wcIndexAddr = OsdGetStartIndexAddr();
    
    curAddr = wcIndexAddr;
    for(row = 0; row < 16; row++)
    {
        for(col = 0; col < 32; col++)
        {
            INDEX_RAM_ADD_H = (curAddr >> 8);
            INDEX_RAM_ADD_L = (curAddr & 0xff);
            INDEX_RAM_DATA_H = 0;
            INDEX_RAM_DATA_L = 0;
            curAddr++;
        }
    }

    curAddr = wcIndexAddr;
    for(row = 0; row < 16; row++)
    {
        for(col = 0; col < 32; col++)
        {
            INDEX_RAM_ADD_H = (curAddr >> 8);
            INDEX_RAM_ADD_L = (curAddr & 0xff);
            
            if(col < 16) 
            {

                EACH_ICON_COLOR = 0x30; 
            }
            else 
            {

                EACH_ICON_COLOR = 0x00; 
            }
            
            curAddr++;
        }
    }
}
void Update_Right_Screen_Blue(UCHAR is_blue)
{
    UINT XDATA wcIndexAddr = 0;
    UINT XDATA curAddr = 0;
    UCHAR XDATA row, col;

    OsdBlockEnable(1); 
    wcIndexAddr = OsdGetStartIndexAddr(); 
    
    curAddr = wcIndexAddr; 
    
    for(row = 0; row < 16; row++)
    {
        for(col = 0; col < 32; col++)
        {
            INDEX_RAM_ADD_H = (curAddr >> 8);
            INDEX_RAM_ADD_L = (curAddr & 0xff);
            if(col >= 16) 
            {
                if(is_blue)
                {
                    EACH_ICON_COLOR = 0x30; 
                }
                else
                {
                    EACH_ICON_COLOR = 0x00; 
                }
            }
            curAddr++;
        }
    }
}
void Radar_Set_Segment(UCHAR r, UCHAR s, UCHAR state)
{
    UCHAR XDATA color;
    UCHAR XDATA screen_row;


    if(r > 5 || s > 3) return;


    if(r == 0 || r == 5)      color = COL_RED;
    else if(r == 2 || r == 3) color = COL_RED;
    else                      color = COL_RED;


    if(state == 0)
    {
        color = COL_WHITE; 
    }

    switch(r)
    {

        case 0: screen_row = 0; break; // F3 (Far)
        case 1: screen_row = 1; break; // F2
        case 2: screen_row = 2; break; // F1


        case 3: screen_row = 9;  break; // R1
        case 4: screen_row = 10; break; // R2
        case 5: screen_row = 11; break; // R3
    }


    Draw_Radar_Segment(r, s, color, screen_row, WAVE_START_COL);
}


void Update_Radar_Logic(UCHAR dist_val, char angle, UCHAR blink_state)
{
    UCHAR XDATA r, s;
    UCHAR XDATA is_target_row;
    UCHAR XDATA is_target_seg;
    

    for(r = 0; r < 6; r++)
    {

        is_target_row = 0;
        
        if (dist_val > 6) 
        {
            //if (r == 0 || r == 5) is_target_row = 1;
					if (r == 5) is_target_row = 1;
        }
        else if (dist_val >= 2) 
        {
//            if (r == 1 || r == 4) is_target_row = 1;
					if (r == 4) is_target_row = 1;
        }
        else 
        {
            //if (r == 2 || r == 3) is_target_row = 1;
					if (r == 3) is_target_row = 1;
        }


        for(s = 0; s < 4; s++)
        {

            is_target_seg = 0;


            if (angle > 30 &&s == 3)
            {
							is_target_seg = 1;
            }
            else if(angle>0&&angle<=30&&s==2)
            {
							is_target_seg = 1;
            }
            else if(angle<=0&&angle>=-30&&s==1)
            {
							is_target_seg = 1;
            }
						else if(angle<-30&&s==0)
            {
							is_target_seg = 1;
            }
            if (is_target_row && is_target_seg)
            {
                Radar_Set_Segment(r, s, blink_state);
            }
            else
            {
                Radar_Set_Segment(r, s, 0x00);
            }
        }
    }
}



void Update_Radar_Distance(UCHAR dist_int, UCHAR dist_dec,UCHAR color)
{
    UCHAR tens, units;

    tens = dist_int / 10;
    units = dist_int % 10;

    if (dist_int >= 10)
    {
        Draw_Big_Number(0, 12, tens, color);
			
    }
    else
    {
        Draw_Big_Number(0, 12, 0, 0x00); 
    }
    Draw_Big_Number(0, 15, units, color);
    Draw_Big_Dot(2, 17, color);
    Draw_Big_Number(0, 18, dist_dec, color);
}


void Draw_All_Radar_Demo(void)
{
    UCHAR XDATA r, s;
    UCHAR XDATA color;
    UCHAR XDATA screen_row;


    for(r = 0; r < 6; r++)
    {
//        if(r == 0 || r == 5)      color = COL_GREEN; 
//        else if(r == 2 || r == 3) color = COL_RED;
//        else                      color = COL_YELLOW;
        if(r == 0 || r == 5)      color = COL_WHITE; 
        else if(r == 2 || r == 3) color = COL_WHITE;
        else                      color = COL_WHITE;
        switch(r)
        {
            case 0: screen_row = 0; break; 
            case 1: screen_row = 1; break; 
            case 2: screen_row = 2; break; 
            case 3: screen_row = 9; break; 
            case 4: screen_row = 10; break; 
            case 5: screen_row = 11; break; 
        }

        for(s = 0; s < 4; s++)
        {
            Draw_Radar_Segment(r, s, color, screen_row, WAVE_START_COL);
        }
    }
}
UCHAR code STR_DIST_00[] = "DIST 0m  ";
UCHAR code STR_DIST_10[] = "DIST 1.0m  ";
UCHAR code STR_DIST_15[] = "DIST 1.5m  ";
UCHAR code STR_DIST_20[] = "DIST 2.0m  ";

UCHAR code STR_WIDTH_2M[] = "WIDTH 2m   "; 
UCHAR code STR_WIDTH_4M[] = "WIDTH 4m   ";
UCHAR code STR_WIDTH_6M[] = "WIDTH 6m   ";
UCHAR code STR_WIDTH_8M[] = "WIDTH 8m   ";

UCHAR code STR_BUZ_ON[]  = "BUZZER ON  "; 
UCHAR code STR_BUZ_OFF[] = "BUZZER OFF ";
UCHAR code STR_CLEAR[] = "           "; 
UCHAR code * code dist_strs[4]  = {STR_DIST_00, STR_DIST_10, STR_DIST_15, STR_DIST_20};
UCHAR code * code width_strs[4] = {STR_WIDTH_2M, STR_WIDTH_4M, STR_WIDTH_6M, STR_WIDTH_8M};
UCHAR code * code buz_strs[2]   = {STR_BUZ_OFF, STR_BUZ_ON};

void ShowRadarDemo(void)
{
		TurnOffBackLight(); 
    SetVDETestSwitch(VDE_BLACK);
		XBYTE[0xFB5A] = 0x00; 
    XBYTE[0xFB5B] = 0x00;
    XBYTE[0xFB06] &= ~0x40;
    OSD_MIRROR_SET = 0x00; 
    OsdBlockEnable(1); 
    OsdConfigWndSize(32, 16); 
    OsdConfigWndPosition(10, 12); 
    OsdBlockClear(1); 
		//Init_Split_Screen();
    XBYTE[0xFB76] = 16;
    XBYTE[0xFB77] = 22;
    
    {
        //car
				UCHAR code R1[] = {'&', 0x00, '&', 0x01, '&', 0x02, '&', 0x03, '&', 0x04, '&', 0x05, 0x00};
        UCHAR code R2[] = {'&', 0x06, '&', 0x07, '&', 0x08, '&', 0x09, '&', 0x0A, '&', 0x0B, 0x00};
        UCHAR code R3[] = {'&', 0x0C, '&', 0x0D, '&', 0x0E, '&', 0x0F, '&', 0x10, '&', 0x11, 0x00};
        UCHAR code R4[] = {'&', 0x12, '&', 0x13, '&', 0x14, '&', 0x15, '&', 0x16, '&', 0x17, 0x00};
        UCHAR code R5[] = {'&', 0x18, '&', 0x19, '&', 0x1A, '&', 0x1B, '&', 0x1C, '&', 0x1D, 0x00};
        UCHAR code R6[] = {'&', 0x1E, '&', 0x1F, '&', 0x20, '&', 0x21, '&', 0x22, '&', 0x23, 0x00};
			  OsdDrawStr(3, 3, COL_WHITE, R1);
        OsdDrawStr(4, 3, COL_WHITE  ,R2);
        OsdDrawStr(5, 3, COL_WHITE , R3);
        OsdDrawStr(6, 3, COL_WHITE, R4);
        OsdDrawStr(7, 3, COL_WHITE, R5);
        OsdDrawStr(8, 3, COL_WHITE, R6);
        Draw_All_Radar_Demo();
        OsdBlockShow(1); 
        DelayMs(50);
        TurnOnBackLight(); 
    }
}



void main(void)
{
    UCHAR XDATA last_rx_cnt = 0;
    UCHAR XDATA idle_cnt = 0;
    UCHAR XDATA current_has_signal = 1; 
    UCHAR XDATA last_has_signal = 2;
    UINT  XDATA signal_debounce_cnt = 0;
    UINT  XDATA blink_timer = 0;
    UCHAR XDATA is_red_phase = 1;
    UINT  XDATA timer_limted = 200;
    float current_range = 0.0;
    float current_sin_val = 0.0;
    UCHAR has_target = 0;
    UCHAR show_int, show_dec, color, seg_state;
    
    UCHAR XDATA current_btn_state = 0;
    UCHAR XDATA last_btn_state = 0;
    UINT XDATA target_timeout_cnt = 0;
    
    float lat_dist, fwd_dist_sq; 
    float current_half_width, current_shield_dist;
    UINT XDATA setting_show_timer = 0;
        
    UINT  adc_debug_val = 0;
    UCHAR d3, d2, d1, d0;
    bit   need_draw = 0; 
    UCHAR XDATA i;
    UCHAR XDATA valid_target_count = 0;
    float min_range = 999.0;
    float min_sin = 0.0;

    DisableWatchdog();
    InitSystem();
    Radar_init_tinyframe();
    MenuProcessKey(COMD_SelPowerOnMode);
    ShowRadarDemo();
    
    g_RxCnt = 0;
    g_FrameReady = 0;
    ES = 1;
    EA = 1;
    SetP0_5(1);
    SetUartPrint();

    while(1)
    {
        adc_debug_val = POS_EnableChipAdc(0); 
        if (adc_debug_val > 1800 && adc_debug_val < 2250) {
            current_btn_state = 1; 
        } else if (adc_debug_val > 2600 && adc_debug_val < 3100) {
            current_btn_state = 2; 
        } else if (adc_debug_val > 1100 && adc_debug_val < 1600) {
            current_btn_state = 3; 
        } else {
            current_btn_state = 0; 
        }

        if (current_btn_state != 0 && last_btn_state == 0) {
            setting_show_timer = 500;
            if (current_btn_state == 1) {
                g_sysSetting.shield_dist_idx++; if (g_sysSetting.shield_dist_idx > 3) g_sysSetting.shield_dist_idx = 0;
                OsdDrawStr(10, 12, COL_GREEN, dist_strs[g_sysSetting.shield_dist_idx]);
            } else if (current_btn_state == 2) {
                g_sysSetting.width_limit_idx++; if (g_sysSetting.width_limit_idx > 3) g_sysSetting.width_limit_idx = 0;
                OsdDrawStr(10, 12, COL_GREEN, width_strs[g_sysSetting.width_limit_idx]);
            } else if (current_btn_state == 3) {
                g_sysSetting.buzzer_en = !g_sysSetting.buzzer_en;
							if(g_sysSetting.buzzer_en)
							{
								OsdDrawStr(10, 12, COL_GREEN, buz_strs[g_sysSetting.buzzer_en]);
							}
							else
							{
								OsdDrawStr(10, 12, COL_WHITE, buz_strs[g_sysSetting.buzzer_en]);
							}
                
            }
        }
        last_btn_state = current_btn_state;
        
        if (setting_show_timer > 0) {
            setting_show_timer--;
            if (setting_show_timer == 0) {
                OsdDrawStr(10, 12, COL_WHITE, STR_CLEAR);
                SetSaveFlagEn();
                SaveSetting();
            }
        }
        
        blink_timer++;
        if(blink_timer > timer_limted) 
        {
            blink_timer = 0;
            is_red_phase = !is_red_phase; 
            if(has_target) need_draw = 1;
        }

        if (g_RxCnt > 0)
        {
            if (g_RxCnt == last_rx_cnt)
            {
                idle_cnt++;
                if (idle_cnt > 20)
                {
                    if(parse_radar(g_RxBuf, g_RxCnt, &g_RadarData))
                    {
                        if(g_RadarData.user_count > 0)
                        {
                            valid_target_count = 0;
                            min_range = 999.0;
                            min_sin = 0.0;

                            current_half_width = (g_sysSetting.width_limit_idx + 1) * 1.0; 
                            if(g_sysSetting.shield_dist_idx == 0) {
                                current_shield_dist = 0;
                            } else {
                                current_shield_dist = (g_sysSetting.shield_dist_idx + 1) * 0.5;
                            }

                            for(i = 0; i < g_RadarData.user_count; i++) 
                            {
                                float rng = g_RadarData.users[i].range;
                                float sin_v = g_RadarData.users[i].sin_value;

                                lat_dist = rng * sin_v;
                                if (lat_dist < 0) lat_dist = -lat_dist;
                                fwd_dist_sq = (rng * rng) - (lat_dist * lat_dist);

                                if (!(lat_dist > current_half_width || fwd_dist_sq < (current_shield_dist * current_shield_dist))) 
                                {
                                    valid_target_count++;
                                    
                                    if (rng < min_range) {
                                        min_range = rng;
                                        min_sin = sin_v;
                                    }
                                }
                            }

                            if (valid_target_count > 0) 
                            {
                                has_target = 1;
                                target_timeout_cnt = 0;
                                
                                current_range = min_range; 
                                current_sin_val = min_sin;

                                if(current_range < 1.0){
                                   timer_limted = 50;
                                }else if(current_range > 1.0){
                                   timer_limted = 150;
                                }
                            }
                            else 
                            {
                                has_target = 0;
                                current_range = 0.0;
                            }
                        }
                        else
                        {
                            has_target = 0;
                            current_range = 0.0;
                        }
                        need_draw = 1;
                    }
                    g_RxCnt = 0; last_rx_cnt = 0; idle_cnt = 0;
                }
            }
            else { last_rx_cnt = g_RxCnt; idle_cnt = 0; }
        }
        
        if (has_target) {
            target_timeout_cnt++;
            if (target_timeout_cnt > 600) {
                has_target = 0; 
                current_range = 0.0;
                need_draw = 1; 
                target_timeout_cnt = 0;
            }
        }
        
        if(need_draw)
        {
            need_draw = 0;

            if(has_target)
            {
                show_int = (UCHAR)current_range;
                show_dec = (UCHAR)((current_range - show_int) * 10);
                if(show_int > 99) show_int=99; if(show_dec > 9) show_dec=9;

                if(current_range < (2.0 + current_shield_dist))
                {
                    if(current_range<(0.4 + current_shield_dist))
                    {
                      if (g_sysSetting.buzzer_en) SetP0_4(1); else SetP0_4(0);											
											if(is_red_phase) 
                        {
                            color = COL_RED;
                            seg_state = 1;
                        }
                        else
                        {
                            color = COL_GREEN;
                            seg_state = 0;
                        }

                    }
                    else{
                        if(is_red_phase) 
                        {
                            color = COL_RED;
                            if (g_sysSetting.buzzer_en) SetP0_4(1); else SetP0_4(0);
                            seg_state = 1;
                        }
                        else
                        {
                            color = COL_GREEN; 
                            SetP0_4(0); 
                            seg_state = 0;
                        }
                    }
                }
                else
                {
                    if(is_red_phase){ 
                        color = COL_GREEN;
                        SetP0_4(0);
                        seg_state = 1;
                    }else{
                        color = COL_GREEN;
                        SetP0_4(0);
                        seg_state = 0;
                    }
                }

                Update_Radar_Distance(show_int, show_dec, color);
                
                {
                    char angle_cmd = 0;
                    if (current_sin_val > 0.5)      angle_cmd = 40;
                    else if (current_sin_val > 0)   angle_cmd = 15;
                    else if (current_sin_val >= -0.5) angle_cmd = -15;
                    else                            angle_cmd = -40;
                    Update_Radar_Logic(show_int, angle_cmd, seg_state);
                }
            }
            else
            {
                Update_Radar_Distance(0, 0, COL_GREEN);
                Update_Radar_Logic(0, 0, 0);
                SetP0_4(0);
            }
        }
        
        if(IsHlockOk()) { if(signal_debounce_cnt < 6000) signal_debounce_cnt++; } 
        else { signal_debounce_cnt = 0; }
        if(signal_debounce_cnt >= 6000) current_has_signal = 1; else current_has_signal = 0;
        if(current_has_signal != last_has_signal) {
            if(current_has_signal == 1) SetVDETestSwitch(VDE_CLOSE); 
            else SetVDETestSwitch(VDE_BLACK); 
            last_has_signal = current_has_signal;
        }

        DelayMs(1);
    }
}