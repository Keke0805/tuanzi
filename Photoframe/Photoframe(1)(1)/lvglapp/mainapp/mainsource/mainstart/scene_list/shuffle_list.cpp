#include "shuffle_list.h"

shuffle_list::shuffle_list()
{
    memset( &pShuffle, 0, sizeof(shuffle_t));
}
shuffle_list::~shuffle_list(void)
{

}
static void _get_rtc_stdsec(unsigned long * stdsec)
{
    struct tm tm;
    SYSDateTime gettime;
    lvcpp_sys_datetime_t user_time;
    user_time = gettime.current_datetime();

    tm.tm_year = user_time.year - 1900;
    tm.tm_mon = user_time.month - 1;
    tm.tm_mday = user_time.day;
    tm.tm_hour = user_time.hour;
    tm.tm_min = user_time.minute;
    tm.tm_sec = user_time.second;
    tm.tm_wday = 0;
    tm.tm_yday = 0;
    tm.tm_isdst = 0;
    *stdsec = mktime(&tm);
}
/******************************************************************************/
/*!
* \par Description:
*        设置当前组的总文件数为num，
*        num必须小于SHUFFLE_BUFFER_MAX，
*        若num与上一组数目不同时，重新置乱当前组
* \param[in]    num -- total number
* \retval       0 为设置成功， -1为失败
*******************************************************************************/
void shuffle_list::_set_cur_total(int num)
{
    int tmp = pShuffle.cur_total;

    pShuffle.cur_total = num;
    if(tmp != num)
    {
        if(((num % 7) == 0 ) && (num > 0 ))
        {
            num = num - 1;
            pShuffle.shuffle_buf[num] = num;
        }
        for(tmp = 0; tmp < num; tmp++)
        {
            if ( 0 != num )
            {
                pShuffle.shuffle_buf[tmp] = (tmp * 16807) % num;
            }
        }
    }
}

/*****************************************************************************/
/*!
* \par Description:
*        检查本组是否结束，如果结束则换入下一组
* \param[in]    void
* \retval       true: 为设置成功， false: 为失败
*****************************************************************************/
bool shuffle_list::_check_index(void)
{
    if(pShuffle.cur_index < pShuffle.cur_total)
    {
        return true;
    }
    else
    {
        if(pShuffle.total_files < 1)
        {
            return false;
        }

        pShuffle.cur_offset = pShuffle.cur_offset + pShuffle.cur_total;
        if(pShuffle.cur_offset >= pShuffle.total_files)
        {
            pShuffle.cur_offset = 0;
        }
        if((pShuffle.cur_offset == pShuffle.start_offset)&&(pShuffle.shuffle_mod == 0))
        {
            pShuffle.cur_index = pShuffle.cur_total -1;
            return false;
        }

        if((pShuffle.total_files - pShuffle.cur_offset) > SHUFFLE_BUFFER_MAX)
        {
            _set_cur_total(SHUFFLE_BUFFER_MAX);
        }
        else
        {
            _set_cur_total(pShuffle.total_files - pShuffle.cur_offset);
        }

        pShuffle.cur_index = 0;
        pShuffle.per_count = 0;
        return true;
    }
}

/*********************************************************************************************/
/*!
* \par Description:
*        设定当前播放歌曲index
* \param[in]    cur_index -- 为正在播放的index
* \retval       true: 为设置成功， false: 为失败
**********************************************************************************************/
bool shuffle_list::_modify_index(int cur_index)
{
    int counta;
    int tmp;
    int index_tmp = cur_index - pShuffle.cur_offset;

    pShuffle.cur_index = 0;
    pShuffle.per_count = 0;
    if(index_tmp < SHUFFLE_BUFFER_MAX)
    {
        for(counta = 0; counta < pShuffle.cur_total; counta++)
        {
            if(index_tmp == pShuffle.shuffle_buf[counta])
            {
                tmp = pShuffle.shuffle_buf[0];
                pShuffle.shuffle_buf[0] = pShuffle.shuffle_buf[counta];
                pShuffle.shuffle_buf[counta] = tmp;

                return true;
            }
        }
    }
    return false;
}

/*******************************************************************************************/
/*!
* \par Description:
*        功能描述：设置初始值，在Shuffle_Init之后调用或调整了文件总数(total_files)，
*        当前歌曲（cur_index）或Shuffle模式（mode）后调用。
* \param[in]    total_files -- 需要Shuffle的文件总数
* \param[in]    cur_index   -- 当前歌曲index
* \param[in]    mode，Shuffle模式SHUFFLE_MODE或SHUFFLE_REPEAT_MODE
* \retval       正确为true，否则为false
*******************************************************************************************/
bool shuffle_list::shuffle(int total_files, int cur_index, char mode)
{
    pShuffle.total_files = total_files;
    pShuffle.start_offset = (cur_index / SHUFFLE_BUFFER_MAX) * SHUFFLE_BUFFER_MAX;

    if((total_files - pShuffle.start_offset) > SHUFFLE_BUFFER_MAX)
    {
        _set_cur_total(SHUFFLE_BUFFER_MAX);
    }
    else
    {
        _set_cur_total(total_files - pShuffle.start_offset);
    }

    pShuffle.cur_offset = pShuffle.start_offset;

    pShuffle.shuffle_mod = mode;

    return _modify_index(cur_index);
}

/******************************************************************************************/
/*!
* \par Description:
*        shuffle_next,不考虑组的偏移
* \param[in]    void
* \retval       SHUFFLE_MODE下遍历结束返回-1, 其它返回组内偏移
*******************************************************************************************/
int shuffle_list::shuffle_sig_next(void)
{
    int swap_index;
    int tmp;
    int ret;
    unsigned long temp;
    /*如果有回退，先按照回退顺序播放*/
    if((pShuffle.per_count > 0)&&(pShuffle.cur_index >= pShuffle.per_count))
    {
        pShuffle.per_count--;
        return pShuffle.shuffle_buf[pShuffle.cur_index - pShuffle.per_count];
    }
    else
    {
        pShuffle.per_count = 0;
        pShuffle.cur_index++;
    }
    /**检查cur_index，判断是否结束或者需要分组*/
    if( false == _check_index() )
    {
        return -1;
    }

    tmp = pShuffle.cur_total - pShuffle.cur_index - 1;
    if( tmp > 0)
    {
        _get_rtc_stdsec(&temp); // 用当前时间做为随机种子
        srand(temp);
        swap_index = pShuffle.cur_index + 1 + ((unsigned long)rand() % tmp);

        tmp = pShuffle.shuffle_buf[pShuffle.cur_index];
        pShuffle.shuffle_buf[pShuffle.cur_index] = pShuffle.shuffle_buf[swap_index];
        pShuffle.shuffle_buf[swap_index] = tmp;
    }
    ret = pShuffle.shuffle_buf[pShuffle.cur_index];
    return ret;
}

/******************************************************************************************/
/*!
* \par Description:
*        取下一个index
* \param[in]    void
* \retval       正确返回0，错误返回-1，SHUFFLE_MODE下遍历结束也返回-1
*******************************************************************************************/
int shuffle_list::shuffle_next(void)
{
    int ret = 0;

    ret = shuffle_sig_next();
    if(ret < 0)
    {
        return -1;
    }
    //printf("pShuffle.cur_offset is %d \n", pShuffle.cur_offset);
    return pShuffle.cur_offset + ret;
}

/*****************************************************************************************/
/*!
* \par Description:
*        取上一个index
* \param[in]    void
* \retval       正确返回0，错误返回-1，SHUFFLE_MODE下遍历结束返回-1，最多可以记忆3008个
******************************************************************************************/
int shuffle_list::shuffle_prev(void)
{
    int tmp = 0;
    unsigned long temp;
    if(pShuffle.cur_index > pShuffle.per_count)
    {
        pShuffle.per_count++;
        return pShuffle.cur_offset + pShuffle.shuffle_buf[pShuffle.cur_index - pShuffle.per_count];
    }
    else
    {
        if ( 0 != pShuffle.total_files )
        {
            _get_rtc_stdsec(&temp); // 用当前时间做为随机种子
            srand(temp);
            tmp = (unsigned long)rand() % pShuffle.total_files;
        }
        return tmp;
    }
}

/*****************************************************************************************/
/*!
* \par Description:
         删除的歌曲时调用，保证shuffle表和playlist相对应
* \param[in]    del_index -- 要删除的歌曲index
* \retval       返回当前index
*****************************************************************************************/
int shuffle_list::shuffle_del(int del_index)
{
    int tmp;
    int retval;
    int idx;
    int del_id = 0;
    bool is_del_last_index = false;

    /*总数减1*/
    pShuffle.total_files--;
    /*如果删除曲目在本组之前，当然组偏移减1，即本组歌曲左移一首*/
    if(pShuffle.cur_offset > del_index)
    {
        pShuffle.cur_offset--;
    }
    /*如果删除曲目在本组内，则总数减1，当然组偏移减1，即本组歌曲左移一首*/
    else if(del_index < (pShuffle.cur_offset + pShuffle.cur_total))
    {
        idx = del_index - pShuffle.cur_offset;
        for(tmp=0; tmp < pShuffle.cur_total; tmp++)
        {
            //大于del_index的元素减1, 保证和文件对应
            if(idx < pShuffle.shuffle_buf[tmp])
            {
                pShuffle.shuffle_buf[tmp] = pShuffle.shuffle_buf[tmp] - 1;
            }
            else if(idx == pShuffle.shuffle_buf[tmp])
            {
                //找到del_index对应数据的偏移
                del_id = tmp;
            }
            else
            {
            }
        }
        //将数组最后1个元素替换当前元素
        pShuffle.shuffle_buf[del_id] = pShuffle.shuffle_buf[pShuffle.cur_total - 1];
        if( (del_id == (pShuffle.cur_total - 1)) && (pShuffle.shuffle_mod == 0) )
        {
            is_del_last_index = true;
        }

        if(pShuffle.cur_total > 1)
        {
            pShuffle.cur_total--;
            if(pShuffle.cur_index >= pShuffle.cur_total)
            {
                pShuffle.cur_index = pShuffle.cur_total -1;
                if(pShuffle.per_count > 0)
                {
                    pShuffle.per_count--;
                }
            }
        }
        else
        {
            pShuffle.cur_total = 0;
            pShuffle.cur_index = 0;
            pShuffle.per_count = 0;
            if( pShuffle.shuffle_mod == 0 )
            {
                return -1;
            }
            else
            {
                return pShuffle.cur_offset;
            }
        }

    }
    else
    {
    }

    if( is_del_last_index == false )
    {
        retval = pShuffle.cur_offset + pShuffle.shuffle_buf[pShuffle.cur_index - pShuffle.per_count];
    }
    else
    {
        retval = -1;
    }

    return retval;
}

int shuffle_list::shuffle_current(void)
{
    return (pShuffle.cur_offset + pShuffle.shuffle_buf[pShuffle.cur_index - pShuffle.per_count]);
}
