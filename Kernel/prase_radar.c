#include "prase_radar.h"
#include "udsf_tinyframe.h"
#include <string.h>
#include "Debug.h"
TinyFrame_Radar xdata x_tf;

double XDATA t_sin;
double XDATA t_range;
double XDATA t_y;

void Radar_init_tinyframe(void)
{
    memset(&x_tf, 0, sizeof(TinyFrame_Radar));
    
    x_tf.state = TFState_SOF;

    x_tf.uart_port = UART_NUM_0; 

}

static void extract_radar_payload(const uint8 XDATA *payload, RadarFrame* out)
{
    uint32 XDATA k;
    uint32 XDATA range_raw, power_raw;
    int32 XDATA velocity_raw, sin_raw;
    const uint8 XDATA *ptr; 


    out->user_count = (uint32)payload[0] | 
                      ((uint32)payload[1] << 8) | 
                      ((uint32)payload[2] << 16) | 
                      ((uint32)payload[3] << 24);

    if(out->user_count > 15) out->user_count = 15;

    ptr = &payload[4];

    for(k = 0; k < out->user_count; k++) 
    {
        range_raw    = (uint32)ptr[0] | ((uint32)ptr[1]<<8) | ((uint32)ptr[2]<<16) | ((uint32)ptr[3]<<24);
        velocity_raw = (int32)((uint32)ptr[4] | ((uint32)ptr[5]<<8) | ((uint32)ptr[6]<<16) | ((uint32)ptr[7]<<24));
        sin_raw      = (int32)((uint32)ptr[8] | ((uint32)ptr[9]<<8) | ((uint32)ptr[10]<<16) | ((uint32)ptr[11]<<24));
        power_raw    = (uint32)ptr[12] | ((uint32)ptr[13]<<8) | ((uint32)ptr[14]<<16) | ((uint32)ptr[15]<<24);

        out->users[k].sin_value = (sin_raw == 0) ? 0.0f : ((float)sin_raw / 1000.0f);
        out->users[k].velocity  = (velocity_raw == 0) ? 0.0f : ((float)velocity_raw / 1000.0f);
        out->users[k].range     = (range_raw == 0) ? 0.0f : ((float)range_raw / 1000.0f);
        out->users[k].power     = power_raw;

        ptr += 16;
    }
}


uint8 parse_radar(uint8 rx_byte, RadarFrame* out) 
{
    int8 XDATA result;


    result = Radar_TF_AcceptChar(&x_tf, rx_byte);
    

    if(result == 0 && !x_tf.discard_data) 
    {
        if(x_tf.type == 0x0A10)
        {

            memset(out, 0, sizeof(*out));
            out->user_count = 0;
            return 1;
        }
        else if(x_tf.type == 0x0A06)
        {
            memset(out, 0, sizeof(*out));
            extract_radar_payload(x_tf.payload, out);
            return 1; 
        }
    }
    return 0; 
}