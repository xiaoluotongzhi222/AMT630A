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
#include "channels.h"
#include "Draw_osd.h"
#include "ConfigLcdPara.h"
#include "Buzzer.h"

#define FONTRAM_PREFIX  '&' 
#define WAVE_START_COL 4  
#define COL_RED     0x01
#define COL_YELLOW  0x04
#define COL_GREEN   0x02


extern void Draw_Big_Number(UCHAR startRow, UCHAR startLine, UCHAR num,UCHAR color);
extern void Draw_Radar_Segment(UCHAR row_idx, UCHAR seg_idx, UCHAR color, UCHAR screen_row, UCHAR screen_col_start);
extern void Clear_Half_Screen(UCHAR half,UCHAR color);
extern void Draw_Big_Dot(UCHAR startRow, UCHAR startLine,UCHAR color);

UCHAR g_last_int = 0xFF;
UCHAR g_last_dec = 0xFF;

void Radar_Set_Segment(UCHAR r, UCHAR s, UCHAR state)
{
    UCHAR color;
    UCHAR screen_row;


    if(r > 5 || s > 3) return;


    if(r == 0 || r == 5)      color = COL_GREEN;
    else if(r == 2 || r == 3) color = COL_RED;
    else                      color = COL_YELLOW;


    if(state == 0)
    {
        color = 0x00; 
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
    UCHAR r, s;
    UCHAR is_target_row;
    UCHAR is_target_seg;
    

    for(r = 0; r < 6; r++)
    {

        is_target_row = 0;
        
        if (dist_val > 6) 
        {
            if (r == 0 || r == 5) is_target_row = 1;
        }
        else if (dist_val >= 2) 
        {
            if (r == 1 || r == 4) is_target_row = 1;
        }
        else 
        {
            if (r == 2 || r == 3) is_target_row = 1;
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
                Radar_Set_Segment(r, s, 1);
            }
        }
    }
}



void Update_Radar_Distance(UCHAR dist_int, UCHAR dist_dec,UCHAR color)
{

        Draw_Big_Number(4, 20, dist_int,color);
				Draw_Big_Dot(6, 22,color);
        Draw_Big_Number(4, 23, dist_dec,color);
}


void Draw_All_Radar_Demo(void)
{
    UCHAR r, s;
    UCHAR color;
    UCHAR screen_row;


    for(r = 0; r < 6; r++)
    {
        if(r == 0 || r == 5)      color = COL_GREEN; 
        else if(r == 2 || r == 3) color = COL_RED;
        else                      color = COL_YELLOW;

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

void ShowRadarDemo(void)
{
    OSD_MIRROR_SET = 0x00; 
    OsdBlockEnable(1); 
    OsdConfigWndSize(32, 16); 
    OsdConfigWndPosition(0, 12); 
    OsdBlockClear(1); 
    XBYTE[0xFB76] = 16;
    XBYTE[0xFB77] = 22;
    
    {
        //car
        UCHAR R1[] = {'&', 0x00, '&', 0x01, '&', 0x02, '&', 0x03, '&', 0x04, '&', 0x05, 0x00};
        UCHAR R2[] = {'&', 0x06, '&', 0x07, '&', 0x08, '&', 0x09, '&', 0x0A, '&', 0x0B, 0x00};
        UCHAR R3[] = {'&', 0x0C, '&', 0x0D, '&', 0x0E, '&', 0x0F, '&', 0x10, '&', 0x11, 0x00};
        UCHAR R4[] = {'&', 0x12, '&', 0x13, '&', 0x14, '&', 0x15, '&', 0x16, '&', 0x17, 0x00};
        UCHAR R5[] = {'&', 0x18, '&', 0x19, '&', 0x1A, '&', 0x1B, '&', 0x1C, '&', 0x1D, 0x00};
        UCHAR R6[] = {'&', 0x1E, '&', 0x1F, '&', 0x20, '&', 0x21, '&', 0x22, '&', 0x23, 0x00};
        OsdDrawStr(3, 5, 0x01, R1);
        OsdDrawStr(4, 5, 0x01 ,R2);
        OsdDrawStr(5, 5, 0x01, R3);
        OsdDrawStr(6, 5, 0x01, R4);
        OsdDrawStr(7, 5, 0x01, R5);
        OsdDrawStr(8, 5, 0x01, R6);
        Draw_All_Radar_Demo();
        OsdBlockShow(1); 
    }
}


void main(void)
{
    UINT i = 0;
	  UINT j = 0;
    char sim_angle = 0;
    char angle_dir = 1; 
    UCHAR blink = 0;
    UCHAR time_slice = 0; 
    UCHAR is_alarm = 0;
    DisableWatchdog();
		InitSystem(); 
    XBYTE[0xFD00] = 0x00;
    XBYTE[0xFD0D] = 0xE0; 
    CHAR_SIZE_X = 16;
    CHAR_SIZE_Y = 22; 
    InitOSD(); 
    
    ShowRadarDemo(); 
    SetP0_4(0);
    while(1) { 
        WDT_CLR = 0xbb; 
        WDT_CLR = 0x44;
        WDT_CLR = 0x00;

				is_alarm = (j < 2) ? 1 : 0; 
        if(is_alarm && blink == 0) 
        {

            Update_Radar_Distance(j, i,0x01); 
					   Update_Radar_Logic(j, sim_angle, blink);
					    SetP0_4(1);
        }
        else 
        {
            Update_Radar_Distance(j, i,0x06); 
					    SetP0_4(0);
            Update_Radar_Logic(j, sim_angle, blink);
        }

        DelayMs(100); 

        blink = !blink;

        time_slice++;
        if(time_slice >= 6)
        {
            time_slice = 0;

            i++;
            if(i > 9) 
						{
							i = 0;
							j++;
							if(j>9)
							{
								j=0;
							}
						}

            sim_angle += (angle_dir * 20);
            if(sim_angle >= 60) {
                sim_angle = 60;
                angle_dir = -1; 
            }
            else if(sim_angle <= -60) {
                sim_angle = -60;
                angle_dir = 1; 
            }
        }
    }
}