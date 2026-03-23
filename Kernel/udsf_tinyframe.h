/**
 * *****************************************************************
 * @file    udsf_tinyframe.h (Fixed: Added 'large' to prototypes)
 * *****************************************************************
 */
#ifndef __TINY_FRAME_H
#define __TINY_FRAME_H

/*------------------------------- include ------------------------------------*/
#include <stddef.h>  
#include <string.h> 
#include "DataType.h" 

/*------------------------------- Type Definitions for C51 -------------------*/
typedef signed char         int8_t;
typedef signed int          int16_t;
typedef signed long         int32_t;
typedef unsigned char       uint8_t;
typedef unsigned int        uint16_t;
typedef unsigned long       uint32_t;

#ifndef bool
    typedef unsigned char bool;
    #define true  1
    #define false 0
#endif

typedef int8_t   int8;
typedef int16_t  int16;
typedef int32_t  int32;
typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;

/* UART Enum Definition */
typedef enum {
    UART_NUM_0,             /*!< UART port 0 */
    UART_NUM_1,             /*!< UART port 1 */
    UART_NUM_2,             /*!< UART port 2 */
    UART_NUM_3,             /*!< UART port 3 */
    LP_UART_NUM_0,          /*!< LP UART port 0 */
    UART_NUM_MAX            /*!< UART port max */
} uart_port_t;

/* MT message definitions */
#define MSG_CFG_MIN_DETECT_POWER            (0x0100)
#define MSG_CFG_MIN_DETECT_VELOCITY         (0x0103)
#define MSG_CFG_MAX_DETECT_RANGE            (0x0104)
#define MSG_CFG_PWM_HOLD_TIME               (0x0107)
#define MSG_CFG_LUX_THRESHOLD               (0x0108)
#define MSG_CFG_OPTION_REMOVE_STATIC        (0x0109)
#define MSG_MEASUREMENT_REQUEST             (0x010A)
#define MSG_HUMAN_REPORT_FILTER_REQUEST     (0x010B)
#define MSG_HUMAN_CONFIG_SRC_REQUEST        (0x010C)
#define MSG_EXPERIMENTALL_MODEL             (0x010D)
#define MSG_PRINTF_TF_ENABLE                (0x010E)
#define MSG_NOISE_FLOOR_REQUEST             (0x0110)
#define MSG_VERSION_REQUEST                 (0x0111)
#define MSG_UPDATE_CONFIG_REQUEST           (0x0112)
#define MSG_FIRMWARE_STATUS_REQUEST         (0xFFFF)
#define MSG_HUMAN_CONFIG_STATUS_REQUEST     (0x2110)
#define MSG_OTA_REQUEST                     (0x3000)

/* MO message definitions */
#define MSG_IND_RESOLUTION_RES              (0x0A00)
#define MSG_IND_USER_PROTOCAL               (0x0A01)
#define MSG_IND_BREATH_POSITION_RES         (0x0A02)
#define MSG_IND_BREATH_RATE_RES             (0x0A03)
#define MSG_IND_HEART_RATE_RES              (0x0A04)
#define MSG_IND_VIBRATE_WEIGHT_RES          (0x0A05)
#define MSG_IND_PEOPLE_COUNTING_TARGET_RES  (0x0A06)
#define MSG_IND_PEOPLE_COUNTING_CLOUD_RES   (0x0A08)
#define MSG_IND_HUMAN_DETECTION_RES         (0x0A10)
#define MSG_IND_GESTURE_RES                 (0x1000)
#define MSG_IND_TEST_RES                    (0x0A11)
#define MSG_IND_CLOUD_3D                    (0x0A12)
#define MSG_IND_NOISEFLOOR_RES              (0x0A14)
#define MSG_IND_VERSION_RES                 (0x0A15)
#define MSG_IND_UPDATE_CONFIG_RES           (0x0A16)
#define MSG_IND_ADC0_IQ                     (0x0B04)
#define MSG_IND_ADC1_IQ                     (0x0B05)
#define MSG_IND_RANGE_FFT_0                 (0x0C00)
#define MSG_IND_RANGE_FFT_1                 (0x0D00)
#define MSG_WRAP_PRINTF                     (0x0100)

/* Structures */
#define TARGET_NUM 128
typedef struct targetInfo
{
    uint32 rng;
    int32 vel;
    int32 ang;
    uint32 power;
} OneTargetInfoStrTypedef;

typedef struct
{
    uint32 targetNum;
    OneTargetInfoStrTypedef multTargetStr[TARGET_NUM];
} multTargetInfoStrTypedef;

typedef struct
{
     uint32 REG_DATA; 
     uint32 STATE;
     uint32 CTRL;
     uint32 INTSTATUS;
     uint32 BAUDDIV;
} UartTypeDef;

/*------------------------------- define -------------------------------------*/
#define TF_CKSUM_NONE   0   
#define TF_CKSUM_XOR    8   
#define TF_CKSUM_CRC8   9   
#define TF_CKSUM_CRC16  16  
#define TF_CKSUM_CRC32  32  
#define TF_CKSUM_CUSTOM8  1 
#define TF_CKSUM_CUSTOM16 2 
#define TF_CKSUM_CUSTOM32 3 

#define TF_ID_BYTES     2
#define TF_LEN_BYTES    2
#define TF_TYPE_BYTES   2
#define TF_CKSUM_TYPE TF_CKSUM_XOR
#define TF_USE_SOF_BYTE 0
#define RADAR_TF_USE_SOF_BYTE 1
#define TF_SOF_BYTE      0x01

typedef uint16_t TF_TICKS;
typedef uint8_t TF_COUNT;
#define TF_MAX_PAYLOAD_RX 256  
#define TF_SENDBUF_LEN 64     
#define TF_MAX_ID_LST   2
#define TF_MAX_TYPE_LST 2
#define TF_MAX_GEN_LST  2
#define TF_PARSER_TIMEOUT_TICKS 60

#define TF_Error(x) 

#if TF_LEN_BYTES == 1
    typedef uint8_t TF_LEN;
#elif TF_LEN_BYTES == 2
    typedef uint16_t TF_LEN;
#elif TF_LEN_BYTES == 4
    typedef uint32_t TF_LEN;
#else
    #error Bad value of TF_LEN_BYTES
#endif

#if TF_TYPE_BYTES == 1
    typedef uint8_t TF_TYPE;
    typedef uint16_t Radar_TF_TYPE;
#elif TF_TYPE_BYTES == 2
    typedef uint16_t TF_TYPE;
    typedef uint16_t Radar_TF_TYPE;
#elif TF_TYPE_BYTES == 4
    typedef uint32_t TF_TYPE;
#else
    #error Bad value of TF_TYPE_BYTES
#endif

#if TF_ID_BYTES == 1
    typedef uint8_t TF_ID;
#elif TF_ID_BYTES == 2
    typedef uint16_t TF_ID;
#elif TF_ID_BYTES == 4
    typedef uint32_t TF_ID;
#else
    #error Bad value of TF_ID_BYTES
#endif

typedef uint8_t TF_ADDR;

#if (TF_CKSUM_TYPE == TF_CKSUM_XOR) || (TF_CKSUM_TYPE == TF_CKSUM_NONE) || (TF_CKSUM_TYPE == TF_CKSUM_CUSTOM8) || (TF_CKSUM_TYPE == TF_CKSUM_CRC8)
    typedef uint8_t TF_CKSUM;
#elif (TF_CKSUM_TYPE == TF_CKSUM_CRC16) || (TF_CKSUM_TYPE == TF_CKSUM_CUSTOM16)
    typedef uint16_t TF_CKSUM;
#elif (TF_CKSUM_TYPE == TF_CKSUM_CRC32) || (TF_CKSUM_TYPE == TF_CKSUM_CUSTOM32)
    typedef uint32_t TF_CKSUM;
#else
    #error Bad value for TF_CKSUM_TYPE
#endif

/*------------------------------- Typedef ------------------------------------*/
typedef enum
{
    TF_SLAVE    = 0,
    TF_MASTER   = 1,
} TF_Peer;

typedef enum
{
    TF_NEXT     = 0,  
    TF_STAY     = 1,   
    TF_RENEW    = 2,    
    TF_CLOSE    = 3,    
} TF_Result;

enum TF_State_ {
    TFState_SOF = 0,      
    TFState_ADDR,          
    TFState_LEN,          
    TFState_ID,            
    TFState_TYPE,          
    TFState_HEAD_CKSUM,   
    TFState_DATA,          
    TFState_DATA_CKSUM    
};

typedef struct TF_Msg_ {
    TF_ID frame_id;       
    bool is_response;     
    TF_TYPE type;         
    TF_ADDR addr;
    const uint8_t *pData; 
    TF_LEN len; 
    void *userdata;
    void *userdata2;
} TF_Msg;

// ??????
typedef void (*TF_Sender_Cb)(uart_port_t UartX, const uint8* buf, uint32 len);

/** Frame parser internal state. */
struct TinyFrame_ {
    void *userdata;
    uint32_t usertag;

    TF_Peer peer_bit;       
    TF_ID next_id;          

    enum TF_State_ state;
    TF_TICKS parser_timeout_ticks;
    TF_ADDR addr;
    TF_ID id;               
    TF_LEN len;             
    
    uint8_t payload[TF_MAX_PAYLOAD_RX]; 
    
    TF_LEN rxi;             
    TF_CKSUM cksum;         
    TF_CKSUM ref_cksum;     
    TF_TYPE type;           
    bool discard_data;      

    /* Tx state */
    uint8_t sendbuf[TF_SENDBUF_LEN]; 
    uint32_t tx_pos;        
    uint32_t tx_len;        
    TF_CKSUM tx_cksum;      

#if !TF_USE_MUTEX
    bool soft_lock;         
#endif

    TF_Sender_Cb   sender_cb;
    uart_port_t    uart_port;

    TF_COUNT count_id_lst;
    TF_COUNT count_type_lst;
    TF_COUNT count_generic_lst;
};

struct TinyFrame_Radar_ {
    void *userdata;
    uint32_t usertag;

    TF_Peer peer_bit;     
    TF_ID next_id;        

    enum TF_State_ state;
    TF_TICKS parser_timeout_ticks;
    TF_ID id;             
    TF_LEN len;           
    
    uint8_t payload[TF_MAX_PAYLOAD_RX]; 
    
    TF_LEN rxi;           
    TF_CKSUM cksum;       
    TF_CKSUM ref_cksum;   
    Radar_TF_TYPE type;   
    bool discard_data;    

    uint8_t sendbuf[TF_SENDBUF_LEN]; 
    uint32_t tx_pos;      
    uint32_t tx_len;      
    TF_CKSUM tx_cksum;    

#if !TF_USE_MUTEX
    bool soft_lock;       
#endif

    TF_Sender_Cb   sender_cb;
    uart_port_t    uart_port;

    TF_COUNT count_id_lst;
    TF_COUNT count_type_lst;
    TF_COUNT count_generic_lst;
};

typedef struct TinyFrame_ TinyFrame;
typedef struct TinyFrame_Radar_ TinyFrame_Radar;

/*------------------------------ function ------------------------------------*/
/* * ?????? 
 * ?????????? large ???,
 * ????? .c ????????!
 */

int8 udsf_TF_AcceptChar(TinyFrame *tf, unsigned char c) large;
int8 Radar_TF_AcceptChar(TinyFrame_Radar *tf, unsigned char c) large;

bool udsf_TF_SendSimple(TinyFrame *tf, TF_TYPE type, const uint8_t *pData, TF_LEN len) large;
bool udsf_TF_Send(TinyFrame *tf, TF_Msg *msg) large;
bool udsf_TF_QuerySimple(TinyFrame *tf, TF_TYPE type, const uint8_t *pData, TF_LEN len, TF_TICKS timeout) large;
bool udsf_TF_Query(TinyFrame *tf, TF_Msg *msg, TF_TICKS timeout) large;
bool udsf_TF_Respond(TinyFrame *tf, TF_Msg *msg) large;
void udsf_TF_ClearMsg(TF_Msg *msg) large;

#if TF_USE_MUTEX
    extern bool udsf_TF_ClaimTx(TinyFrame *tf) large;
    extern void udsf_TF_ReleaseTx(TinyFrame *tf) large;
#endif

#if (TF_CKSUM_TYPE == TF_CKSUM_CUSTOM8) || (TF_CKSUM_TYPE == TF_CKSUM_CUSTOM16) || (TF_CKSUM_TYPE == TF_CKSUM_CUSTOM32)
    extern TF_CKSUM udsf_TF_CksumStart(void) large;
    extern TF_CKSUM udsf_TF_CksumAdd(TF_CKSUM cksum, uint8_t byte) large;
    extern TF_CKSUM udsf_TF_CksumEnd(TF_CKSUM cksum) large;
#endif

#endif