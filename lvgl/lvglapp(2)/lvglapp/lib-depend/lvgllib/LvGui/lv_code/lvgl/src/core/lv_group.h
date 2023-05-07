/**
 * @file lv_group.h
 *
 */

#ifndef LV_GROUP_H
#define LV_GROUP_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#include "../lv_conf_internal.h"

#include <stdint.h>
#include <stdbool.h>
#include "../misc/lv_ll.h"
#include "../misc/lv_types.h"

/*********************
 *      DEFINES
 *********************/
/*Predefined keys to control the focused object via lv_group_send(group, c)*/

enum {
	LV_KEY_POWER        = 0,  
	LV_KEY_VOLUME_UP    = 13,
	LV_KEY_VOLUME_DOWN	= 14,
	LV_KEY_MENU		    = 15,	
	LV_KEY_OK		    = 16,	
	LV_KEY_UP		    = 17,
	LV_KEY_DOWN		    = 18,	
    LV_KEY_RIGHT        = 19, 
    LV_KEY_LEFT         = 20,  

	LV_KEY_1		    = 1,	
	LV_KEY_2		    = 2,
	LV_KEY_3		    = 3,	
	LV_KEY_4		    = 4,	
	LV_KEY_5		    = 5,	

	LV_KEY_NEXT         = 6, 
    LV_KEY_PREV         = 7,
    
    LV_KEY_ESC          = 8,
    LV_KEY_DEL          = 9, 
     
    LV_KEY_HOME        = 10,
    LV_KEY_ENTER       = 11, 
    LV_KEY_BACK        = 12, 
	LV_KEY_BACKSPACE   = 21,
	LV_KEY_END         = 22,
};

enum {
	LV_IR_KEY_UP,  
	LV_IR_KEY_DOWN, 
	LV_IR_KEY_LEFT, 
	LV_IR_KEY_RIGHT, 
	LV_IR_KEY_OK, 
	LV_IR_KEY_CANCEL, 
	LV_IR_KEY_MENU, 
	LV_IR_KEY_VOL_UP, 
	LV_IR_KEY_VLO_DOWN, 
	LV_IR_KEY_NEXT, 
	LV_IR_KEY_PREV,
};

typedef uint8_t lv_key_t;

/**********************
 *      TYPEDEFS
 **********************/

struct _lv_obj_t;
struct _lv_group_t;

typedef void (*lv_group_focus_cb_t)(struct _lv_group_t *);

/**
 * Groups can be used to logically hold objects so that they can be individually focused.
 * They are NOT for laying out objects on a screen (try layouts for that).
 */
typedef struct _lv_group_t {
    lv_ll_t obj_ll;        /**< Linked list to store the objects in the group*/
    struct _lv_obj_t ** obj_focus; /**< The object in focus*/

    lv_group_focus_cb_t focus_cb;              /**< A function to call when a new object is focused (optional)*/
#if LV_USE_USER_DATA
    void * user_data;
#endif

    uint8_t frozen : 1;         /**< 1: can't focus to new object*/
    uint8_t editing : 1;        /**< 1: Edit mode, 0: Navigate mode*/
    uint8_t refocus_policy : 1; /**< 1: Focus prev if focused on deletion. 0: Focus next if focused on
                                   deletion.*/
    uint8_t wrap : 1;           /**< 1: Focus next/prev can wrap at end of list. 0: Focus next/prev stops at end
                                   of list.*/
} lv_group_t;


typedef enum {
    LV_GROUP_REFOCUS_POLICY_NEXT = 0,
    LV_GROUP_REFOCUS_POLICY_PREV = 1
} lv_group_refocus_policy_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Init. the group module
 * @remarks Internal function, do not call directly.
 */
void _lv_group_init(void);

/**
 * Create a new object group
 * @return          pointer to the new object group
 */
lv_group_t * lv_group_create(void);

/**
 * Delete a group object
 * @param group     pointer to a group
 */
void lv_group_del(lv_group_t * group);

/**
 * Set a default group. New object are added to this group if it's enabled in their class with `add_to_def_group = true`
 * @param group     pointer to a group (can be `NULL`)
 */
void lv_group_set_default(lv_group_t * group);

/**
 * Get the default group
 * @return          pointer to the default group
 */
lv_group_t * lv_group_get_default(void);

/**
 * Add an object to a group
 * @param group     pointer to a group
 * @param obj       pointer to an object to add
 */
void lv_group_add_obj(lv_group_t * group, struct _lv_obj_t * obj);

/**
 * Swap 2 object in a group. The object must be in the same group
 * @param obj1  pointer to an object
 * @param obj2  pointer to an other object
 */
void lv_group_swap_obj(struct _lv_obj_t * obj1, struct _lv_obj_t * obj2);

/**
 * Remove an object from its group
 * @param obj       pointer to an object to remove
 */
void lv_group_remove_obj(struct _lv_obj_t * obj);

/**
 * Remove all objects from a group
 * @param group     pointer to a group
 */
void lv_group_remove_all_objs(lv_group_t * group);

/**
 * Focus on an object (defocus the current)
 * @param obj       pointer to an object to focus on
 */
void lv_group_focus_obj(struct _lv_obj_t * obj);

/**
 * Focus the next object in a group (defocus the current)
 * @param group     pointer to a group
 */
void lv_group_focus_next(lv_group_t * group);

/**
 * Focus the previous object in a group (defocus the current)
 * @param group     pointer to a group
 */
void lv_group_focus_prev(lv_group_t * group);

/**
 * Do not let to change the focus from the current object
 * @param group     pointer to a group
 * @param en        true: freeze, false: release freezing (normal mode)
 */
void lv_group_focus_freeze(lv_group_t * group, bool en);

/**
 * Send a control character to the focuses object of a group
 * @param group     pointer to a group
 * @param c         a character (use LV_KEY_.. to navigate)
 * @return          result of focused object in group.
 */
lv_res_t lv_group_send_data(lv_group_t * group, uint32_t c);

/**
 * Set a function for a group which will be called when a new object is focused
 * @param group         pointer to a group
 * @param focus_cb      the call back function or NULL if unused
 */
void lv_group_set_focus_cb(lv_group_t * group, lv_group_focus_cb_t focus_cb);

/**
 * Set whether the next or previous item in a group is focused if the currently focused obj is
 * deleted.
 * @param group         pointer to a group
 * @param policy        new refocus policy enum
 */
void lv_group_set_refocus_policy(lv_group_t * group, lv_group_refocus_policy_t policy);

/**
 * Manually set the current mode (edit or navigate).
 * @param group         pointer to group
 * @param edit          true: edit mode; false: navigate mode
 */
void lv_group_set_editing(lv_group_t * group, bool edit);

/**
 * Set whether focus next/prev will allow wrapping from first->last or last->first object.
 * @param group         pointer to group
 * @param               en true: wrapping enabled; false: wrapping disabled
 */
void lv_group_set_wrap(lv_group_t * group, bool en);

/**
 * Get the focused object or NULL if there isn't one
 * @param group         pointer to a group
 * @return              pointer to the focused object
 */
struct _lv_obj_t * lv_group_get_focused(const lv_group_t * group);

/**
 * Get the focus callback function of a group
 * @param group pointer to a group
 * @return the call back function or NULL if not set
 */
lv_group_focus_cb_t lv_group_get_focus_cb(const lv_group_t * group);

/**
 * Get the current mode (edit or navigate).
 * @param group         pointer to group
 * @return              true: edit mode; false: navigate mode
 */
bool lv_group_get_editing(const lv_group_t * group);

/**
 * Get whether focus next/prev will allow wrapping from first->last or last->first object.
 * @param group         pointer to group
 * @param               en true: wrapping enabled; false: wrapping disabled
 */
bool lv_group_get_wrap(lv_group_t * group);

/**
 * Get the number of object in the group
 * @param group         pointer to a group
 * @return              number of objects in the group
 */
uint32_t lv_group_get_obj_count(lv_group_t * group);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_GROUP_H*/
