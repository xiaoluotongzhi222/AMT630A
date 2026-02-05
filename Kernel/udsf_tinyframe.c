/**
 * *****************************************************************
 * @file    udsf_tinyframe.c (Fixed Redefinition & Order)
 * *****************************************************************
 */

#ifndef __TINY_FRAME_C
#define __TINY_FRAME_C

/*------------------------------- include ------------------------------------*/
#include "udsf_tinyframe.h"
#include <stddef.h> 
#include <stdlib.h>

// 全局变量放在 XDATA
static TinyFrame xdata *s_ftRx;
static TinyFrame xdata *s_ftTx;

// 外部发送函数
extern void TF_Platform_Send(uart_port_t port, const uint8* buf, uint32 len);

/*------------------------------- macros -------------------------------------*/
#define COLLECT_NUMBER(dest, type) \
    do { \
        if (tf->rxi == 0) dest = 0; \
        dest |= ((type)c) << (8 * tf->rxi++); \
    } while (0); \
    if (tf->rxi == sizeof(type))
    
#define RADAR_COLLECT_NUMBER(dest, type) dest = (type)(((dest) << 8) | c); \
                                            if (++tf->rxi == sizeof(type))

#define TF_MIN(a, b) ((a)<(b)?(a):(b))
#define TF_TRY(func) do { if(!(func)) return false; } while (0)

#define TF_ID_MASK (TF_ID)(((TF_ID)1 << (sizeof(TF_ID)*8 - 1)) - 1)
#define TF_ID_PEERBIT (TF_ID)((TF_ID)1 << ((sizeof(TF_ID)*8) - 1))

#define WRITENUM_BASE(type, num, xtra) \
    for (si = 0; si < sizeof(type); si++) { \
        b = (uint8_t)((num) >> (si*8) & 0xFF); \
        outbuff[pos++] = b; \
        xtra; \
    }

#define _NOOP()
#define WRITENUM(type, num)       WRITENUM_BASE(type, num, _NOOP())
#define WRITENUM_CKSUM(type, num) WRITENUM_BASE(type, num, CKSUM_ADD(cksum, b))

/*------------------------------ checksums -----------------------------------*/
#if TF_CKSUM_TYPE == TF_CKSUM_NONE
static TF_CKSUM udsf_TF_CksumStart(void) large { return 0; }
static TF_CKSUM udsf_TF_CksumAdd(TF_CKSUM cksum, uint8_t byte) large { return cksum; }
static TF_CKSUM udsf_TF_CksumEnd(TF_CKSUM cksum) large { return cksum; }

#elif TF_CKSUM_TYPE == TF_CKSUM_XOR
static TF_CKSUM udsf_TF_CksumStart(void) large { return 0; }
static TF_CKSUM udsf_TF_CksumAdd(TF_CKSUM cksum, uint8_t byte) large { return cksum ^ byte; }
static TF_CKSUM udsf_TF_CksumEnd(TF_CKSUM cksum) large { return (TF_CKSUM) ~cksum; }

// ... (其他 CRC 类型省略，如果你用了请补上，加上 large 即可) ...
#endif

#define CKSUM_RESET(cksum)     do { (cksum) = udsf_TF_CksumStart(); } while (0)
#define CKSUM_ADD(cksum, byte) do { (cksum) = udsf_TF_CksumAdd((cksum), (byte)); } while (0)
#define CKSUM_FINALIZE(cksum)  do { (cksum) = udsf_TF_CksumEnd((cksum)); } while (0)


/*------------------------------ Static Functions (Forward Implementation) ----*/
// 把所有 static 函数直接实现在这里，这样就不需要额外的声明了，避免冲突

static void udsf_tinyFrameTxInit(TinyFrame *ftTx, TF_Sender_Cb uartsend) large
{
    s_ftTx = ftTx;
    s_ftTx->sender_cb = uartsend;
}

static void udsf_TF_ResetParser(TinyFrame *tf) large { tf->state = TFState_SOF; }
static void RADAR_TF_ResetParser(TinyFrame_Radar *tf) large { tf->state = TFState_SOF; }

static void udsf_pars_begin_frame(TinyFrame *tf) large {
    CKSUM_RESET(tf->cksum);
#if TF_USE_SOF_BYTE
    CKSUM_ADD(tf->cksum, TF_SOF_BYTE);
#endif
    tf->discard_data = false;
    tf->state = TFState_ADDR;
    tf->rxi = 0;
}

static void RADAR_pars_begin_frame(TinyFrame_Radar *tf) large {
    CKSUM_RESET(tf->cksum);
#if RADAR_TF_USE_SOF_BYTE
    CKSUM_ADD(tf->cksum, TF_SOF_BYTE);
#endif
    tf->discard_data = false;
    tf->state = TFState_ID;
    tf->rxi = 0;
}

static uint32_t udsf_TF_ComposeHead(TinyFrame *tf, uint8_t *outbuff, TF_Msg *msg) large {
    int8_t si       = 0;
    uint8_t b       = 0;
    TF_ID id        = 0;
    TF_CKSUM cksum  = 0;
    uint32_t pos    = 0;
    (void)cksum; 
    CKSUM_RESET(cksum);
    if (msg->is_response) { id = msg->frame_id; } 
    else {
        tf->next_id += 1;
        id = (TF_ID)(tf->next_id & TF_ID_MASK);
        if (tf->peer_bit) { id |= TF_ID_PEERBIT; }
    }
    msg->frame_id = id;
    CKSUM_RESET(cksum);
#if TF_USE_SOF_BYTE
    outbuff[pos++] = TF_SOF_BYTE;
    CKSUM_ADD(cksum, TF_SOF_BYTE);
#endif
    WRITENUM_CKSUM(TF_ADDR,   msg->addr);
    WRITENUM_CKSUM(TF_ID,   id);
    WRITENUM_CKSUM(TF_LEN,  msg->len);
    WRITENUM_CKSUM(TF_TYPE, msg->type);
#if TF_CKSUM_TYPE != TF_CKSUM_NONE
    CKSUM_FINALIZE(cksum);
    WRITENUM(TF_CKSUM, cksum);
#endif
    return pos;
}

static uint32_t udsf_TF_ComposeBody(uint8_t *outbuff, const uint8_t *pData, TF_LEN data_len, TF_CKSUM *cksum) large {
    TF_LEN i        = 0;
    uint8_t b       = 0;
    uint32_t pos    = 0;
    for (i = 0; i < data_len; i++) {
        b = pData[i];
        outbuff[pos++] = b;
        CKSUM_ADD(*cksum, b);
    }
    return pos;
}

static uint32_t udsf_TF_ComposeTail(uint8_t *outbuff, TF_CKSUM *cksum) large {
    int8_t si = 0; 
    uint8_t b = 0;
    uint32_t pos = 0;
#if TF_CKSUM_TYPE != TF_CKSUM_NONE
    CKSUM_FINALIZE(*cksum);
    WRITENUM(TF_CKSUM, *cksum);
#endif
    return pos;
}

static void udsf_TF_WriteImpl(TinyFrame *tf, const uint8_t *buff, uint32_t len) large {
    TF_Platform_Send(tf->uart_port, buff, len);
}

#if !TF_USE_MUTEX
static bool udsf_TF_ClaimTx(TinyFrame *tf) large {
    if (tf->soft_lock) { TF_Error("TF already locked for tx!"); return false; }
    tf->soft_lock = true;
    return true;
}
static void udsf_TF_ReleaseTx(TinyFrame *tf) large {
    tf->soft_lock = false;
}
#endif

// 这些函数需要先定义，因为 SendFrame 会用到
static void udsf_TF_SendFrame_Chunk(TinyFrame *tf, const uint8_t *buff, uint32_t length) large {
    uint32_t remain;
    uint32_t chunk;
    uint32_t sent = 0;
    remain = length;
    while (remain > 0) {
        chunk = TF_MIN(TF_SENDBUF_LEN - tf->tx_pos, remain);
        tf->tx_pos += udsf_TF_ComposeBody(tf->sendbuf + tf->tx_pos, buff + sent, (TF_LEN) chunk, &tf->tx_cksum);
        remain  -= chunk;
        sent    += chunk;
        if (tf->tx_pos == TF_SENDBUF_LEN) {
            udsf_TF_WriteImpl(tf, (const uint8_t *)tf->sendbuf, tf->tx_pos);
            tf->tx_pos = 0;
        }
    }
}

static void udsf_TF_SendFrame_End(TinyFrame *tf) large {
    if (tf->tx_len > 0) {
        if ((TF_SENDBUF_LEN - tf->tx_pos) < sizeof(TF_CKSUM)) {
            udsf_TF_WriteImpl(tf, (const uint8_t *) tf->sendbuf, tf->tx_pos);
            tf->tx_pos = 0;
        }
        tf->tx_pos += udsf_TF_ComposeTail((tf->sendbuf + tf->tx_pos), &tf->tx_cksum);
    }
    udsf_TF_WriteImpl(tf, (const uint8_t *) tf->sendbuf, tf->tx_pos);
    udsf_TF_ReleaseTx(tf);
}

static bool udsf_TF_SendFrame_Begin(TinyFrame *tf, TF_Msg *msg, TF_TICKS timeout) large {
    TF_TRY(udsf_TF_ClaimTx(tf));
    tf->tx_pos = (uint32_t) udsf_TF_ComposeHead(tf, tf->sendbuf, msg); 
    tf->tx_len = msg->len;
    CKSUM_RESET(tf->tx_cksum);
    return true;
}

static bool udsf_TF_SendFrame(TinyFrame *tf, TF_Msg *msg, TF_TICKS timeout) large {
    TF_TRY(udsf_TF_SendFrame_Begin(tf, msg, timeout));
    if ((msg->len == 0) || (msg->pData != NULL)) {
       udsf_TF_SendFrame_Chunk(tf, msg->pData, msg->len);
       udsf_TF_SendFrame_End(tf);
    }
    return true;
}


/*------------------------------ Public Functions (Implemented) --------------*/

int8 udsf_TF_AcceptChar(TinyFrame *tf, unsigned char c) large
{
    int32 result = -100;
    {
        if (tf->parser_timeout_ticks >= TF_PARSER_TIMEOUT_TICKS)
        {
            if (tf->state != TFState_SOF)
            {
                udsf_TF_ResetParser(tf);
                TF_Error("Parser timeout");
            }
        }
        tf->parser_timeout_ticks = 0;

    #if !TF_USE_SOF_BYTE
        if (tf->state == TFState_SOF)
        {
            udsf_pars_begin_frame(tf);
        }
    #endif

        switch (tf->state)
        {
        case TFState_SOF:
            if (c == TF_SOF_BYTE) { udsf_pars_begin_frame(tf); result = 1; }
            else { result = -1; }
            break;
        case TFState_ADDR:
            CKSUM_ADD(tf->cksum, c);
            COLLECT_NUMBER(tf->addr, TF_ADDR) {
                tf->state = TFState_ID; tf->rxi = 0; result = 9;
            } else { result = -9; }
            break;
        case TFState_ID:
            CKSUM_ADD(tf->cksum, c);
            COLLECT_NUMBER(tf->id, TF_ID) {
                tf->state = TFState_LEN; tf->rxi = 0; result = 2;
            } else { result = -2; }
            break;
        case TFState_LEN:
            CKSUM_ADD(tf->cksum, c);
            COLLECT_NUMBER(tf->len, TF_LEN) {
                tf->state = TFState_TYPE; tf->rxi = 0; result = 3;
            } else { result = -3; }
            break;
        case TFState_TYPE:
            CKSUM_ADD(tf->cksum, c);
            COLLECT_NUMBER(tf->type, TF_TYPE) {
            #if TF_CKSUM_TYPE == TF_CKSUM_NONE
                tf->state = TFState_DATA; tf->rxi = 0;
            #else
                tf->state = TFState_HEAD_CKSUM; tf->rxi = 0; tf->ref_cksum = 0;
            #endif
                result = 4;
            } else { result = -4; }
            break;
        case TFState_HEAD_CKSUM:
            COLLECT_NUMBER(tf->ref_cksum, TF_CKSUM) {
                CKSUM_FINALIZE(tf->cksum);
                if (tf->cksum != tf->ref_cksum) {
                    TF_Error("Rx head cksum mismatch");
                    udsf_TF_ResetParser(tf);
                    result = -8;
                } else if (tf->len == 0) {
                    udsf_TF_ResetParser(tf);
                    result = 0;
                } else {
                    result = 5;
                    tf->state = TFState_DATA; tf->rxi = 0;
                    CKSUM_RESET(tf->cksum); 
                }
                if (tf->len > TF_MAX_PAYLOAD_RX) {
                    tf->discard_data = true; result = -9;
                }
            } else { result = -5; }
            break;
        case TFState_DATA:
            if (tf->discard_data) {
                tf->rxi++; result = -6;
            } else {
                CKSUM_ADD(tf->cksum, c);
                tf->payload[tf->rxi++] = c;
                result = 6;
            }
            if (tf->rxi == tf->len) {
            #if TF_CKSUM_TYPE == TF_CKSUM_NONE
                result = 0; udsf_TF_ResetParser(tf);
            #else
                tf->state = TFState_DATA_CKSUM; tf->rxi = 0; tf->ref_cksum = 0;
            #endif
            }
            break;
        case TFState_DATA_CKSUM:
            COLLECT_NUMBER(tf->ref_cksum, TF_CKSUM) {
                CKSUM_FINALIZE(tf->cksum);
                if (!tf->discard_data) {
                    if (tf->cksum == tf->ref_cksum) result = 0;
                    else { TF_Error("Body cksum mismatch"); result = -10; }
                }
                udsf_TF_ResetParser(tf);
            } else { result = -7; }
            break;
        }
    }
    return result;
}

int8 Radar_TF_AcceptChar(TinyFrame_Radar *tf, unsigned char c) large
{
    int32 result = -100;
    {
        if (tf->parser_timeout_ticks >= TF_PARSER_TIMEOUT_TICKS) {
            if (tf->state != TFState_SOF) {
                RADAR_TF_ResetParser(tf);
                TF_Error("Parser timeout");
            }
        }
        tf->parser_timeout_ticks = 0;

    #if !RADAR_TF_USE_SOF_BYTE
        if (tf->state == TFState_SOF) udsf_pars_begin_frame(tf);
    #endif

        switch (tf->state ) {
        case TFState_SOF:
            if (c == TF_SOF_BYTE) { RADAR_pars_begin_frame(tf); result = 1; }
            else { result = -1; }
            break;
        case TFState_ID:
            CKSUM_ADD(tf->cksum, c);
            RADAR_COLLECT_NUMBER(tf->id, TF_ID) {
                tf->state = TFState_LEN; tf->rxi = 0; result = 2;
            } else { result = -2; }
            break;
        case TFState_LEN:
            CKSUM_ADD(tf->cksum, c);
            RADAR_COLLECT_NUMBER(tf->len, TF_LEN) {
                tf->state = TFState_TYPE; tf->rxi = 0; result = 3;
            } else { result = -3; }
            break;
        case TFState_TYPE:
            CKSUM_ADD(tf->cksum, c);
            RADAR_COLLECT_NUMBER(tf->type, Radar_TF_TYPE) {
            #if TF_CKSUM_TYPE == TF_CKSUM_NONE
                tf->state = TFState_DATA; tf->rxi = 0;
            #else
                tf->state = TFState_HEAD_CKSUM; tf->rxi = 0; tf->ref_cksum = 0;
            #endif
                result = 4;
            } else { result = -4; }
            break;
        case TFState_HEAD_CKSUM:
            RADAR_COLLECT_NUMBER(tf->ref_cksum, TF_CKSUM) {
                CKSUM_FINALIZE(tf->cksum);
                if (tf->cksum != tf->ref_cksum) {
                    TF_Error("Rx head cksum mismatch");
                    RADAR_TF_ResetParser(tf);
                    result = 10;
                } else if (tf->len == 0) {
                    RADAR_TF_ResetParser(tf);
                    result = 0;
                } else {
                    result = 5;
                    tf->state = TFState_DATA; tf->rxi = 0;
                    CKSUM_RESET(tf->cksum); 
                }
                if (tf->len > TF_MAX_PAYLOAD_RX) {
                    tf->discard_data = true; result = -9;
                }
            } else { result = -5; }
            break;
        case TFState_DATA:
            if (tf->discard_data) {
                tf->rxi++; result = -6;
            } else {
                CKSUM_ADD(tf->cksum, c);
                tf->payload[tf->rxi++] = c;
                result = 6;
            }
            if (tf->rxi == tf->len) {
            #if TF_CKSUM_TYPE == TF_CKSUM_NONE
                result = 0; RADAR_TF_ResetParser(tf);
            #else
                tf->state = TFState_DATA_CKSUM; tf->rxi = 0; tf->ref_cksum = 0;
            #endif
            }
            break;
        case TFState_DATA_CKSUM:
            RADAR_COLLECT_NUMBER(tf->ref_cksum, TF_CKSUM) {
                CKSUM_FINALIZE(tf->cksum);
                if (!tf->discard_data) {
                    if (tf->cksum == tf->ref_cksum) result = 0;
                    else { TF_Error("Body cksum mismatch"); result = -10; }
                }
                RADAR_TF_ResetParser(tf);
            } else { result = -7; }
            break;
        case TFState_ADDR: 
            result = 12; break;
        }
    }
    return result;
}

void udsf_TF_ClearMsg(TF_Msg *msg) large {
    memset(msg, 0, sizeof(TF_Msg));
}

bool udsf_TF_SendSimple(TinyFrame *tf, TF_TYPE type, const uint8_t *pData, TF_LEN len) large {
    TF_Msg msg;
    udsf_TF_ClearMsg(&msg);
    msg.type    = type;
    msg.pData   = pData;
    msg.len     = len;
    return udsf_TF_Send(tf, &msg);
}

bool udsf_TF_Send(TinyFrame *tf, TF_Msg *msg) large {
    return udsf_TF_SendFrame(tf, msg, 0);
}

bool udsf_TF_QuerySimple(TinyFrame *tf, TF_TYPE type, const uint8_t *pData, TF_LEN len, TF_TICKS timeout) large {
    TF_Msg msg;
    udsf_TF_ClearMsg(&msg);
    msg.type    = type;
    msg.pData   = pData;
    msg.len     = len;
    return udsf_TF_SendFrame(tf, &msg, timeout);
}

bool udsf_TF_Query(TinyFrame *tf, TF_Msg *msg, TF_TICKS timeout) large {
    return udsf_TF_SendFrame(tf, msg, timeout);
}

bool udsf_TF_Respond(TinyFrame *tf, TF_Msg *msg) large {
    msg->is_response = true;
    return udsf_TF_Send(tf, msg);
}

static void udsf_tinyFramefTx(TF_TYPE type, uint8 *pData, TF_LEN len) large {
    udsf_TF_SendSimple(s_ftTx, type, pData, len);
}

#endif