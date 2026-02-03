#ifndef _GET_USER_INPUT_MSG_H__
#define _GET_USER_INPUT_MSG_H__

#ifdef _GET_USER_MSG_C_
#define _GET_USER_MSG_EXTERN_ 
#else
#define _GET_USER_MSG_EXTERN_ extern
#endif


_GET_USER_MSG_EXTERN_ MSG POS_GetKeyPadMsg(void);
#endif

