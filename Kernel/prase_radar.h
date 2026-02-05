#ifndef __PRASE_RADAR_H__
#define __PRASE_RADAR_H__

#include "DataType.h" 

#include "udsf_tinyframe.h" 


typedef struct {
    float range;
    float velocity;
    float sin_value;
    uint32 power; 
} RadarUserData;

// ????????
typedef struct {
    uint32 user_count;
    RadarUserData users[5];
} RadarFrame;


extern TinyFrame_Radar XDATA x_tf; 

void Radar_init_tinyframe(void);
uint8 parse_radar(const uint8* raw, uint8 raw_len, RadarFrame* out);

#endif