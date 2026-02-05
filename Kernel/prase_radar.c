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

uint8 parse_radar(const uint8* raw, uint8 raw_len, RadarFrame* out) 
{
    uint8 XDATA i;
    int8  XDATA result;
    uint32 XDATA k;
    
    uint32 XDATA range_raw;
    int32 XDATA velocity_raw;
    int32 XDATA sin_raw;
    uint32 XDATA power_raw;
    
    uint8 XDATA *ptr; 

    memset(out, 0, sizeof(*out));
    for(i = 0; i < raw_len; i++) 
    {
        result = Radar_TF_AcceptChar(&x_tf, raw[i]);
        if(result == 0 && !x_tf.discard_data) 
        {
            if(x_tf.type == 0x0A10)
            {
                out->user_count = 0;
            }
            else if(x_tf.type == 0x0A06)
            {
                out->user_count = (uint32)x_tf.payload[0] | 
                                  ((uint32)x_tf.payload[1] << 8) | 
                                  ((uint32)x_tf.payload[2] << 16) | 
                                  ((uint32)x_tf.payload[3] << 24);
                
                if(out->user_count > 20) out->user_count = 20;

                ptr = &x_tf.payload[4];

                for(k = 0; k < out->user_count; k++) 
                {

                    range_raw    = (uint32)ptr[0] | ((uint32)ptr[1]<<8) | ((uint32)ptr[2]<<16) | ((uint32)ptr[3]<<24);
                    velocity_raw = (int32)((uint32)ptr[4] | ((uint32)ptr[5]<<8) | ((uint32)ptr[6]<<16) | ((uint32)ptr[7]<<24));
                    sin_raw      = (int32)((uint32)ptr[8] | ((uint32)ptr[9]<<8) | ((uint32)ptr[10]<<16) | ((uint32)ptr[11]<<24));
                    power_raw    = (uint32)ptr[12] | ((uint32)ptr[13]<<8) | ((uint32)ptr[14]<<16) | ((uint32)ptr[15]<<24);


                    if (sin_raw == 0) out->users[k].sin_value = 0.0;
                    else              out->users[k].sin_value = (float)sin_raw / 1000.0f;

                    if (velocity_raw == 0) out->users[k].velocity = 0.0;
                    else                   out->users[k].velocity = (float)velocity_raw / 1000.0f;

                    if (range_raw == 0) out->users[k].range = 0.0;
                    else                out->users[k].range = (float)range_raw / 1000.0f;

                    out->users[k].power = power_raw;

                    ptr += 16;
                }
            }
            return 1;
        }
    }
    return 0; 
}