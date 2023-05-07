/*******************************************************************************!
 * \file            app_msg.h
 * \brief           Ӧ�ó�����Ϣ����
 *
 * \description     
 *
 * \note            
 *
 * \author   CareyZeng
 * \version 1.0
 * \date  2021/08/24
 *******************************************************************************/
 #ifndef __APP_MSG_H__
#define __APP_MSG_H__

#ifdef __cplusplus
extern "C"{
#endif

#include "app_key.h"

typedef enum{
	MSG_POWER_OFF=0,
	MSG_STANDBY=1,
	MSG_RESUME=2,
	MSG_KEY_INPUT=3,
    MSG_TOUCH_INPUT=4,
	
	MSG_USER_DEFINE=1000,
	MSG_SEND_ID_TO_FRONTLCD,
	MSG_SEND_CMD_TO_R2,
	MSG_SEND_UPG_PRO,
	MSG_SEND_UPG_PRO_FINISH,
	MSG_UPDATE_IDCARD,
    MSG_UPDATE_CANVAS,
    MSG_UPDATE_TEMPLATE,
	MSG_ADD_FONT,
	MSG_ADD_TEMP,
    MSG_CLEAR_ALL_INFO,
	MSG_DOWN_IDCARD_FAIL,
	MSG_R2_INIT_FINISH,
	MSG_R2_SEND_FINISH,
	MSG_START_VOTE,
	MSG_DESKCARD_SURE,
	MSG_UR_RECV_TIMEOUT,
	MSG_RECV_MESSAGE,
	MSG_COPY_FILE_START,
	MSG_COPY_FILE_FINISH,
	MSG_LOW_BAT_SHUTDOWN,
	MSG_LOW_BAT_HIDEWIND,
	MSG_USB_INSERT,
	MSG_USB_EXIT,
	MSG_MOUSE_INSERT,
	MSG_MOUSE_EXIT,
	MSG_DOWN_AGENDA_FILE_PRO,
	MSG_DOWN_CONTENT_FILE_PRO,
}app_msg_type_e;

typedef struct{
	app_msg_type_e type;
	int csize;
	char content[1024];
}msg_apps_t;

/*       input msg          */
typedef enum
{
    /* the max value of key type, it must be less than  MASK_KEY_UP*/
    KEY_TYPE_NULL       = 0x00000000,
    KEY_TYPE_LONG_DOWN  = 0x80000000,
    KEY_TYPE_SHORT_DOWN = 0x40000000,
    KEY_TYPE_DOWN       = 0x20000000,
    KEY_TYPE_LONG       = 0x10000000,
    KEY_TYPE_HOLD       = 0x08000000,
    KEY_TYPE_SHORT_UP   = 0x04000000,
    KEY_TYPE_LONG_UP    = 0x02000000,
    KEY_TYPE_HOLD_UP    = 0x01000000,
    KEY_TYPE_ALL        = 0x3F000000,
}key_type_e;

typedef struct
{
    key_val_e    val;
    key_type_e   type;
}key_event_t;

typedef enum
{
    TP_TYPE_DOWN       = 0x0,
    TP_TYPE_UP         = 0x1,
    TP_TYPE_MOVE       = 0x2,
    TP_TYPE_SHORT,
    TP_TYPE_LONG,
    TP_TYPE_DOUBLE,
    TP_TYPE_NULL,
}tp_type_e;

typedef struct
{
    /*! horizontal coordinate  */
    int x;
    /*! vertical coordinate  */
    int y;
    /*! event type  */
    tp_type_e tp_type;
}tp_event_t;

/*!
*\brief
    �����gui����Ϣ���� */
typedef enum
{
    /*! �������͵���Ϣ */
    INPUT_MSG_KEY,
    /*! ���������͵���Ϣ */
    INPUT_MSG_TOUCH,
}input_msg_type_e;

/*!
*\brief
    �����gui����Ϣ�ṹ�� */
typedef struct
{
    input_msg_type_e type;
    union
    {
        key_event_t kmsg;
        tp_event_t tmsg;
    }data;
}input_msg_t;


#ifdef __cplusplus
}
#endif

#endif
