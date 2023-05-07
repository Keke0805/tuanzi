#ifndef __FILELIST_H__
#define __FILELIST_H__
#include <sys/types.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include "rat_common.h"
#include "rat.h"
#include "DiskManager.h"

/*!
  * \brief
  *     ??????????
*/
typedef struct file_op_info_s
{
    //item_type_t		type;				//?????????????????
    __u64               total_size;         //???????????????;
    __u64               finish_size;        //?????????????;
    __u32               total_num;          //??????׷??/????????????
    __u32               finish_num;         //??????????????/??????????
    __u32               percent;            //?????/???????????????=?????????/?׷??????????
    __u32				dir_level;			//??????
    void				(*OnDraw)(struct file_op_info_s* op_info);//???????????????
}file_op_info_t;



typedef struct file_item_s
{
        char* name;						//??????????????
        __u32 name_len;					//????????????????????????

        __u8  fatdirattr;			/* FAT only. Contains the "DIR_Attr" field of an entry. */
                                        //??????��??????, ????? = FSYS_ATTR_DIRECTORY
        __u8  status;					//????????????
        struct file_item_s *previous;	//???????????
        struct file_item_s *next;		//???????????
}file_item_t;


typedef struct file_list_s
{
        char  file_path[RAT_MAX_FULL_PATH_LEN];			//????????��??
        __u32 total;					//????????????????(?????????,???,?? "..")

        file_item_t*	item_list;		//????��?????
        file_item_t*	cur_item;		//??????

        struct file_list_s  *parent;	//??????? ???
        struct file_list_s  *child;		//??????? ???

}file_list_t;

#define C_MAX_DIR_SCAN_LEVEL        16

extern __s32 new_file_list(const char *path, file_item_t** pp_item_list, void *ext_para);
extern __s32 delete_file_list(file_item_t  *item_list, __u32 total);

extern __s32 delete_file_item_from_list(file_item_t* item, file_list_t* list);
extern __s32 insert_file_item_to_list(file_item_t* cur_item, file_item_t* item);
extern file_item_t* get_file_list_item(file_list_t* nod, __u32 index);
extern char* get_file_list_item_name(file_list_t* nod, __u32 index);
extern rat_media_type_t  get_file_list_item_file_type(file_item_t* item);

extern file_list_t* new_file_root_list_nod(void* ext_para);
extern file_list_t* new_file_list_nod(const char *path, void* ext_para);
extern __s32 delete_file_list_nod(file_list_t* nod);
extern __s32 delete_file_list_chain(file_list_t* top_nod);
extern __s32 delete_dir(char* dir_name, file_op_info_t *op_info);
extern int FileList_AddFileNod_To_RootList(file_list_t *root_nod, DiskInfo_t *DiskInfo);
extern int FileList_DelFileNod_To_RootList(file_list_t *root_nod, DiskInfo_t *DiskInfo);
extern int FileList_GetItemNum_ByMountPoint(file_list_t *root_nod, char *MountPoint);
#endif
