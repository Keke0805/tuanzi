#ifndef SHUFFLE_LIST_H
#define SHUFFLE_LIST_H
#include  "lvgl/lvgl.h"
#include  "lv_cpp/lvcpp_class.h"
#include  "lvgl/src/extra/lv_extra.h"
#include  "../include/configCustom.h"
//可以完成 10000 首歌的 shuffle
#define      SHUFFLE_BUFFER_MAX       0x2710

typedef struct
{
    int total_files ;   //shuffle 的最大值，每次输出在 [0，shuffle_range-1]
    int cur_total ;     //当前组的文件总数，最大为SHUFFLE_BUFFER_MAX
    int cur_index ;     //当前shuffle_buf的位置
    int cur_offset ;    //当前组内歌曲的偏移，一般为SHUFFLE_BUFFER_MAX 的整数倍
    int start_offset;   //第一组歌曲的偏移，用于判断一轮shuffle结束
    int per_count ;     //回退的个数，用于回退后继续按之前的顺序播放
    int shuffle_buf[SHUFFLE_BUFFER_MAX];     //存储当前组的歌曲顺序，小于cur_index为已播，大于为未播
    char shuffle_mod;     //0只播一遍，1循环播放
}shuffle_t;

class shuffle_list
{
public:
    shuffle_list();
    ~shuffle_list(void);
    bool shuffle(int total_files, int cur_index, char mode);
    int shuffle_sig_next(void);
    int shuffle_next(void);
    int shuffle_prev(void);
    int shuffle_del(int del_index);
    int shuffle_current(void);

private:
    void _set_cur_total(int num);
    bool _check_index(void);
    bool _modify_index(int cur_index);
    shuffle_t pShuffle;
};

#endif // SHUFFLE_LIST_H
