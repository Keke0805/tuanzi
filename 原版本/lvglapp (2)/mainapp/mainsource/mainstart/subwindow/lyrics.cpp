#include "lyrics.h"
#include "math.h"

using namespace std;

Lyrics::Lyrics(lv_obj_t* parent)
{
    mscreen = new LvcppScreen(parent);
    mscreen->set_size(LYRICS_LIST_WEIHT,LYRICS_LIST_HIGH);
    mscreen->set_main_bg_color(lv_color_white(),LV_OPA_0);
    mscreen->align(LV_ALIGN_CENTER,100,0);
    m_parent = mscreen->myobj;
    initial();
}

Lyrics::~Lyrics()
{
    deinitial();
}

void Lyrics::show(bool flag)
{
    if(flag)
    {
        mscreen->clear_flag(LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
        mscreen->add_flag(LV_OBJ_FLAG_HIDDEN);
    }
}

//User starts here
void Lyrics::initial(void)
{
    lvgl_scroll_anim();
    maintimer = startTimer(20,this);
    //read_lyrics_flie("./resource/lyrics/lyrics.txt");
}

void Lyrics::deinitial(void)
{

    if(mscreen != nullptr)
    {
        delete mscreen ;
        mscreen = nullptr;
    }
}

void Lyrics::switch_cartoon_up(char* old_lyrics)
{
    if(scroll_flag!=0)
    {
        return;
    }
    int mid=0,new_image=0;

    mid=(cur_head+LYRICS_NUM/2)%(LYRICS_NUM);

    if((cur_index+LYRICS_NUM/2)<0)
    {
        if((cur_index+LYRICS_NUM/2)%LYRICS_NUM==0)
            mid_image=0;
        else
            mid_image=LYRICS_NUM+((cur_index+LYRICS_NUM/2)%(LYRICS_NUM));
    }
    else
    {
        mid_image = (cur_index+LYRICS_NUM/2)%LYRICS_NUM;
    }

    scroll_flag=-1;
    cur_index--;

    if((cur_index)<0)
    {
        if((cur_index)%LYRICS_NUM==0)
            new_image=0;
        else
            new_image=LYRICS_NUM+((cur_index)%(LYRICS_NUM));
    }
    else
    {
        new_image = (cur_index)%LYRICS_NUM;
    }

    menulist[cur_tail]->add_txt(old_lyrics);
}


void Lyrics::switch_cartoon_down(char* new_lyrics)
{
    if(scroll_flag!=0)
    {
        return;
    }
    int mid=0,new_image=0;

    mid=(cur_head+LYRICS_NUM/2)%(LYRICS_NUM);

    if((cur_index+LYRICS_NUM/2)<0)
    {
        if((cur_index+LYRICS_NUM/2)%LYRICS_NUM==0)
            mid_image=0;
        else
            mid_image=LYRICS_NUM+((cur_index+LYRICS_NUM/2)%(LYRICS_NUM));
    }
    else
    {
        mid_image = (cur_index+LYRICS_NUM/2)%LYRICS_NUM;
    }


    scroll_flag=1;
    cur_index++;

    if((cur_index+LYRICS_NUM-1)<0)
    {
        if((cur_index+LYRICS_NUM-1)%LYRICS_NUM==0)
            new_image=0;
        else
            new_image=LYRICS_NUM+((cur_index+LYRICS_NUM-1)%(LYRICS_NUM));
    }
    else
    {
        new_image = (cur_index+LYRICS_NUM-1)%LYRICS_NUM;
    }
    if(new_lyrics==NULL)
    {
        menulist[cur_head]->add_txt("");
    }
    else
    {
        menulist[cur_head]->add_txt(new_lyrics);
    }
}


void Lyrics::draw_point(void)
{
    memset(point,0,sizeof(point));
    int X = (int)(sqrt(abs((LYRICS_LIST_WEIHT-LYRICS_LIST_WEIHT)*(LYRICS_LIST_WEIHT-LYRICS_LIST_WEIHT))/2));
    int Y = (int)(sqrt(abs((LYRICS_LIST_WEIHT-LYRICS_LIST_WEIHT)*(LYRICS_LIST_WEIHT-LYRICS_LIST_WEIHT))/2));
    //LV_LOG_USER("Center of the circle:X=%d,Y=%d",X,Y);
    for(int i=0;i<LYRICS_LIST_HIGH*LYRICS_NUM+1;i++)
    {
        point[i].x =X;
        point[i].y =Y+i-LYRICS_LIST_HIGH*(LYRICS_NUM/2);
    }
    /*
    LvcppLine* line = new LvcppLine(cont->myobj);
    line->set_points(point,LYRICS_LIST_HIGH);
    lv_obj_set_style_line_color(line->myobj,lv_color_white(),0);
    */
    memset(point_list,0,sizeof(point_list));
    for(int j=0;j< LYRICS_NUM;j++)
    {
        if(j<LYRICS_NUM/2)
        {
            point_list[j].x = point[abs(LYRICS_LIST_HIGH*LYRICS_NUM/(LYRICS_NUM)*j)].x;
            point_list[j].y =point[abs(LYRICS_LIST_HIGH*LYRICS_NUM/(LYRICS_NUM)*j)].y;
        }
        else if(j>LYRICS_NUM/2)
        {
            point_list[j].x = point[abs(LYRICS_LIST_HIGH*LYRICS_NUM/(LYRICS_NUM)*j)].x;
            point_list[j].y =point[abs(LYRICS_LIST_HIGH*LYRICS_NUM/(LYRICS_NUM)*j)].y;
        }
        else
        {
            point_list[j].x = point[abs(LYRICS_LIST_HIGH*LYRICS_NUM/(LYRICS_NUM)*j)].x;
            point_list[j].y =point[abs(LYRICS_LIST_HIGH*LYRICS_NUM/(LYRICS_NUM)*j)].y;
        }
        scroll_len = (int)(LYRICS_LIST_HIGH*LYRICS_NUM/(LYRICS_NUM));
        //point_list[j].x = //X+(int)(sqrt(LYRICS_LIST_WEIHT*LYRICS_LIST_WEIHT-X*X))-(int)(LYRICS_LIST_WEIHT*cos(PI/180*(90*1.0f/(LYRICS_NUM-1))*j));
        //point_list[j].y = //-Y+(int)(LYRICS_LIST_WEIHT*sin(PI/180*(90*1.0f/(LYRICS_NUM-1))*j))-60;
        //LV_LOG_USER("x[%d]=%d,y[%d]=%d",j,point_list[j].x,j,point_list[j].y);
    }

}


void Lyrics::lvgl_scroll_anim(void)
{
    cont = new LvcppScreen(m_parent);
    cont->set_style_radius(0,0);
    cont->set_size(LYRICS_LIST_WEIHT, LYRICS_LIST_HIGH);
    cont->align(LV_ALIGN_BOTTOM_LEFT,0,0);
    cont->set_style_bg_color(lv_color_hex(0xff0000),LV_OPA_0,0);
    cont->set_style_clip_corner(true, 0);
    cont->set_scrollbar_mode( LV_SCROLLBAR_MODE_OFF);
    cont->set_style_pad_row(0,0);
    cont->set_style_pad_column(0,0);
    cont->set_style_pad_all(0,0);

    draw_point();

    memset(menulist,0,sizeof(menulist));
    for(int i = 0; i < LYRICS_NUM; i++) {
        menulist[i] = new LvcppButton(cont->myobj);
        menulist[i]->set_style_pad_all(0,0);
        menulist[i]->set_style_bg_color(lv_color_white(),LV_OPA_0,0);
        menulist[i]->add_txt("");
        menulist[i]->txt_color(lv_color_white());
        menulist[i]->txt_font_size(180,1);
        menulist[i]->set_size(LYRICS_LIST_WEIHT,LYRICS_LIST_HIGH);
        menulist[i]->set_pos(point_list[i].x,point_list[i].y);
        menulist[i]->txt_size(LYRICS_LIST_WEIHT,LYRICS_LIST_HIGH,LV_LABEL_LONG_WRAP);
        menulist[i]->txt_align(LV_ALIGN_TOP_LEFT,0,0);
        lv_obj_set_style_text_align(menulist[i]->myobj,LV_TEXT_ALIGN_LEFT,0);
    }
}


//loop run(must achieve)
void Lyrics::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);
    static int count = 0;//static variable once assign
    static int time_cnt = 0;


    char buf[1024] = {0};
    if(scroll_flag==0)
    {
        time_cnt++;
        if(time_cnt>100)
        {
            if(lyrics_fd.is_open())
            {
                if (lyrics_fd.getline(buf,sizeof(buf))) {
                }
                else
                {
                    lyrics_fd.close();
                }
            }
            else
            {
                read_lyrics_flie("./resource/lyrics/lyrics.txt");
                if (lyrics_fd.getline(buf,sizeof(buf))) {
                }
                else
                {
                    lyrics_fd.close();
                }
            }
            //LV_LOG_USER("buf =%s",buf);
            switch_cartoon_down(buf);
            time_cnt=0;
        }
    }


    if(scroll_flag!=0)
    {
        count++;
        scroll_anim_exe(count);
        if(count>=LYRICS_ANIM_STEP)
        {
            //anim finish
            imagelist_update();
            count = 0;
            scroll_flag=0;
            if(!center_flag)
            {
                switch_cartoon_down(NULL);
                center_flag = true;
            }
            else
            {
                center_flag = false;
            }
        }
    }
}


void Lyrics::scroll_anim_exe(int step)
{
    int step_len=(int)(scroll_len/LYRICS_ANIM_STEP);
    int cnt = 0;

    if(scroll_flag==1)
    {
        for(int i = 0; i < LYRICS_NUM; i++)
        {
            if(i!=cur_head)
            {
                if((i-cur_head)%(LYRICS_NUM)<0)
                {
                    if((i-cur_head)%LYRICS_NUM==0)
                        cnt=0;
                    else
                        cnt=LYRICS_NUM+((i-cur_head)%(LYRICS_NUM));
                }
                else
                {
                    cnt = (i-cur_head)%(LYRICS_NUM);
                }
                menulist[i]->set_pos(point[(int)(abs(LYRICS_LIST_HIGH*LYRICS_NUM/(LYRICS_NUM)*cnt)-step_len*step)].x,point[(int)(abs(LYRICS_LIST_HIGH*LYRICS_NUM/(LYRICS_NUM)*cnt)-step_len*step)].y);
            }
            else
            {
                menulist[i]->set_pos(point[(int)(abs(LYRICS_LIST_HIGH*LYRICS_NUM))].x,point[(int)(abs(LYRICS_LIST_HIGH*LYRICS_NUM))].y);//down
            }
        }
    }
    else if(scroll_flag==-1)
    {
        for(int i = 0; i < LYRICS_NUM; i++)
        {
            if(i!=cur_tail)
            {
                if((i-cur_head)%(LYRICS_NUM)<0)
                {
                    if((i-cur_head)%LYRICS_NUM==0)
                        cnt=0;
                    else
                        cnt=LYRICS_NUM+((i-cur_head)%(LYRICS_NUM));
                }
                else
                {
                    cnt = (i-cur_head)%(LYRICS_NUM);
                }
                menulist[i]->set_pos(point[(int)(abs(LYRICS_LIST_HIGH*LYRICS_NUM/(LYRICS_NUM)*abs(cnt))+step_len*step)].x,point[(int)(abs(LYRICS_LIST_HIGH*LYRICS_NUM/(LYRICS_NUM)*abs(cnt))+step_len*step)].y);
            }
            else
            {
                menulist[i]->set_pos(point[(int)(abs(0))].x,point[(int)(abs(0))].y);//up
            }
        }
    }
}

void Lyrics::imagelist_update(void)
{
    int cnt=0,mid=0;
    if(cur_index<0)
    {
        if(cur_index%LYRICS_NUM==0)
            cur_head=0;
        else
            cur_head=LYRICS_NUM+(cur_index%(LYRICS_NUM));
    }
    else
    {
        cur_head=cur_index%(LYRICS_NUM);
    }

    mid=(cur_head+LYRICS_NUM/2)%(LYRICS_NUM);
    cur_tail=(cur_head+LYRICS_NUM-1)%(LYRICS_NUM);
    //LV_LOG_USER("cur_head=%d",cur_head);
    //LV_LOG_USER("cur_tail=%d",cur_tail);

    if((cur_index+LYRICS_NUM/2)<0)
    {
        if((cur_index+LYRICS_NUM/2)%LYRICS_NUM==0)
            mid_image=0;
        else
            mid_image=LYRICS_NUM+((cur_index+LYRICS_NUM/2)%(LYRICS_NUM));
    }
    else
    {
        mid_image = (cur_index+LYRICS_NUM/2)%LYRICS_NUM;
    }

    //update list
    for(int i = 0; i < LYRICS_NUM; i++)
    {
        if((i-cur_head)%(LYRICS_NUM)<0)
        {
            if((i-cur_head)%LYRICS_NUM==0)
                cnt=0;
            else
                cnt=LYRICS_NUM+((i-cur_head)%(LYRICS_NUM));
        }
        else
        {
            cnt = (i-cur_head)%(LYRICS_NUM);
        }

        if(i==mid)
        {
            menulist[i]->set_pos(point_list[LYRICS_NUM/2].x,point_list[LYRICS_NUM/2].y);
        }
        else
        {
            menulist[i]->set_pos(point_list[cnt].x,point_list[cnt].y);
        }
    }
}



void Lyrics::read_lyrics_flie(const char * name)
{
    lyrics_fd.open(name,ios::in) ;
    if (!lyrics_fd.is_open()) {
        cout << "open file failed" << endl;
        return;
    }
}

