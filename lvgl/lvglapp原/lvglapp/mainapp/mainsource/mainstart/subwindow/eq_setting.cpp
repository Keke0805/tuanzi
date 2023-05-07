#include "eq_setting.h"
#include "common/common.h"
#include "math.h"

using namespace LVGLOPTAPI;

void EQ_setting::ui_image_decode(void)
{
    int index=0;
    LvcppMemory::memset(&imagelist,0,sizeof(EQimage_t));

    LV_LOG_USER("aaaaaaaaaaaa");
    EQ_CLASSICAL_B_PNG=(void*)parse_image_from_file((char*)EQ_CLASSICALL_B_PNG_PATH);
    EQ_CLASSICAL_S_PNG=(void*)parse_image_from_file((char*)EQ_CLASSICALL_S_PNG_PATH);
    imagelist.big[index]= EQ_CLASSICAL_B_PNG;
    imagelist.small[index]= EQ_CLASSICAL_S_PNG;
    index++;

    EQ_JAZZ_B_PNG=(void*)parse_image_from_file((char*)EQ_JAZZ_B_PNG_PATH);
    EQ_JAZZ_S_PNG=(void*)parse_image_from_file((char*)EQ_JAZZ_S_PNG_PATH);
    imagelist.big[index]= EQ_JAZZ_B_PNG;
    imagelist.small[index]= EQ_JAZZ_S_PNG;
    index++;

    EQ_ROCK_B_PNG=(void*)parse_image_from_file((char*)EQ_ROCK_B_PNG_PATH);
    EQ_ROCK_S_PNG=(void*)parse_image_from_file((char*)EQ_ROCK_S_PNG_PATH);
    imagelist.big[index]= EQ_ROCK_B_PNG;
    imagelist.small[index]= EQ_ROCK_S_PNG;
    index++;

    EQ_STEREO_B_PNG=(void*)parse_image_from_file((char*)EQ_STEREO_B_PNG_PATH);
    EQ_STEREO_S_PNG=(void*)parse_image_from_file((char*)EQ_STEREO_S_PNG_PATH);
    imagelist.big[index]= EQ_STEREO_B_PNG;
    imagelist.small[index]= EQ_STEREO_S_PNG;
    index++;

    EQ_VOCAL_B_PNG=(void*)parse_image_from_file((char*)EQ_VOCAL_B_PNG_PATH);
    EQ_VOCAL_S_PNG=(void*)parse_image_from_file((char*)EQ_VOCAL_S_PNG_PATH);
    imagelist.big[index]= EQ_VOCAL_B_PNG;
    imagelist.small[index]= EQ_VOCAL_S_PNG;
    index++;
}

void EQ_setting::ui_txt_decede(void)
{
    int index=0;
    LvcppMemory::memset(txtlist,0,sizeof(txtlist));

    txtlist[index] = (char *)"Classical";
    index++;

    txtlist[index] = (char *)"Jazz";
    index++;

    txtlist[index] = (char *)"Rock";
    index++;

    txtlist[index] = (char *)"Stereo";
    index++;

    txtlist[index] = (char *)"Vocal";
    index++;


}


EQ_setting::EQ_setting(lv_obj_t* parent)
{
    mscreen = new LvcppScreen(parent);
    mscreen->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    mscreen->set_main_bg_color(lv_color_white(),LV_OPA_100);
    m_parent = mscreen->myobj;
    initial();
}

EQ_setting::~EQ_setting()
{
    deinitial();
    ui_image_free();
}

void EQ_setting::deinitial(void)
{
    for(int i = 0; i < EQ_IMAGE_NUM; i++) {
        if(menulist[i]!=nullptr)
        {
            delete menulist[i];
            menulist[i] = nullptr;
        }
    }
    memset(menulist,0,sizeof(menulist));
    if(current_position !=nullptr)
    {
        delete  current_position;
        current_position = nullptr;
    }
    if(current_function !=nullptr)
    {
        delete  current_function;
        current_function = nullptr;
    }
    if(mscreen !=nullptr)
    {
        delete  mscreen;
        mscreen = nullptr;
    }

}
void EQ_setting::ui_image_free(void)
{
    if(EQ_CLASSICAL_B_PNG !=NULL)
    {
        free_image(EQ_CLASSICAL_B_PNG);
        EQ_CLASSICAL_B_PNG =NULL;
    }
    if(EQ_CLASSICAL_S_PNG !=NULL)
    {
        free_image(EQ_CLASSICAL_S_PNG);
        EQ_CLASSICAL_S_PNG =NULL;
    }
    if(EQ_JAZZ_B_PNG !=NULL)
    {
        free_image(EQ_JAZZ_B_PNG);
        EQ_JAZZ_B_PNG =NULL;
    }
    if(EQ_JAZZ_S_PNG !=NULL)
    {
        free_image(EQ_JAZZ_S_PNG);
        EQ_JAZZ_S_PNG =NULL;
    }
    if(EQ_ROCK_B_PNG !=NULL)
    {
        free_image(EQ_ROCK_B_PNG);
        EQ_ROCK_B_PNG =NULL;
    }
    if(EQ_ROCK_S_PNG !=NULL)
    {
        free_image(EQ_ROCK_S_PNG);
        EQ_ROCK_S_PNG =NULL;
    }
    if(EQ_STEREO_B_PNG !=NULL)
    {
        free_image(EQ_STEREO_B_PNG);
        EQ_STEREO_B_PNG =NULL;
    }
    if(EQ_STEREO_S_PNG !=NULL)
    {
        free_image(EQ_STEREO_S_PNG);
        EQ_STEREO_S_PNG =NULL;
    }

    if(EQ_VOCAL_B_PNG !=NULL)
    {
        free_image(EQ_VOCAL_B_PNG);
        EQ_VOCAL_B_PNG =NULL;
    }
    if(EQ_VOCAL_S_PNG !=NULL)
    {
        free_image(EQ_VOCAL_S_PNG);
        EQ_VOCAL_S_PNG =NULL;
    }

    LvcppMemory::memset(imagelist.big,0,sizeof(imagelist.big));
    LvcppMemory::memset(imagelist.small,0,sizeof(imagelist.small));
    LvcppMemory::memset(&imagelist,0,sizeof(EQimage_t));
}

void EQ_setting::lvgl_scroll_anim(void)
{
    cont = new LvcppScreen(m_parent);
    cont->set_style_radius(0,0);
    cont->set_size(EQ_LIST_LEN+(int)(EQ_LIST_LEN/(EQ_IMAGE_NUM-1)/2), SOUNDS_LIST_HIGH);
    cont->align(LV_ALIGN_CENTER,16,0);
    cont->set_style_bg_color(lv_color_hex(0xff0000),LV_OPA_0,0);
    cont->set_style_clip_corner(true, 0);
    cont->set_scrollbar_mode( LV_SCROLLBAR_MODE_OFF);
    cont->set_style_pad_row(0,0);
    cont->set_style_pad_column(0,0);
    cont->set_style_pad_all(0,0);
    draw_point();
    memset(menulist,0,sizeof(menulist));
    for(int i = 0; i < EQ_IMAGE_NUM; i++) {
        menulist[i] = new LvcppButton(cont->myobj);
        menulist[i]->set_style_pad_all(0,0);
        menulist[i]->set_style_bg_color(lv_color_white(),LV_OPA_0,0);
        if(i==EQ_IMAGE_NUM/2)
        {
            menulist[i]->set_size(130,130);
            menulist[i]->set_main_bg_img_src(imagelist.big[i]);
            menulist[i]->set_pos(point_list[i].x,point_list[i].y);
        }
        else
        {
            menulist[i]->set_size(78,78);
            menulist[i]->set_pos(point_list[i].x,point_list[i].y);
            menulist[i]->set_main_bg_img_src(imagelist.small[i]);
        }
    }
}
void EQ_setting::initial(void)
{
    ui_image_decode();
    ui_txt_decede();
    lvgl_scroll_anim();
    current_position = new LvcppLabel(m_parent);
    current_position->set_txt("EQ");
    current_position->txt_font_size(100,0);
    current_position->align(LV_ALIGN_CENTER,0,-200);
    current_position->set_size(300,200);
    current_position->txt_align(LV_TEXT_ALIGN_CENTER);


    current_function = new LvcppLabel(m_parent);
    current_function->set_txt("Rock");
    current_function->txt_font_size(30,0);
    current_function->set_size(200,100);
    current_function->align(LV_ALIGN_CENTER,0,180);
    current_function->txt_align(LV_TEXT_ALIGN_CENTER);

    maintimer = startTimer(20,this);
}


void EQ_setting::switch_cartoon_left(void)
{
    if(scroll_flag!=0)
    {
        return;
    }
    int mid=0,new_image=0;
    char index[32]={0};

    mid=(cur_head+EQ_IMAGE_NUM/2)%(EQ_IMAGE_NUM);

    if((cur_index+EQ_IMAGE_NUM/2)<0)
    {
        if((cur_index+EQ_IMAGE_NUM/2)%EQ_IMAGE_NUM==0)
            mid_image=0;
        else
            mid_image=EQ_IMAGE_NUM+((cur_index+EQ_IMAGE_NUM/2)%(EQ_IMAGE_NUM));
    }
    else
    {
        mid_image = (cur_index+EQ_IMAGE_NUM/2)%EQ_IMAGE_NUM;
    }

    menulist[mid]->set_size(78,78);
    menulist[mid]->set_main_bg_img_src(imagelist.small[mid_image]);
    menulist[mid]->set_pos(point_list[EQ_IMAGE_NUM/2].x+26,point_list[EQ_IMAGE_NUM/2].y+26);

    scroll_flag=-1;
    cur_index--;

    if((cur_index)<0)
    {
        if((cur_index)%EQ_IMAGE_NUM==0)
            new_image=0;
        else
            new_image=EQ_IMAGE_NUM+((cur_index)%(EQ_IMAGE_NUM));
    }
    else
    {
        new_image = (cur_index)%EQ_IMAGE_NUM;
    }
    menulist[cur_tail]->set_main_bg_img_src(imagelist.small[new_image]);

}


void EQ_setting::switch_cartoon_right(void)
{
    if(scroll_flag!=0)
    {
        return;
    }
    int mid=0,new_image=0;
    char index[32]={0};

    mid=(cur_head+EQ_IMAGE_NUM/2)%(EQ_IMAGE_NUM);

    if((cur_index+EQ_IMAGE_NUM/2)<0)
    {
        if((cur_index+EQ_IMAGE_NUM/2)%EQ_IMAGE_NUM==0)
            mid_image=0;
        else
            mid_image=EQ_IMAGE_NUM+((cur_index+EQ_IMAGE_NUM/2)%(EQ_IMAGE_NUM));
    }
    else
    {
        mid_image = (cur_index+EQ_IMAGE_NUM/2)%EQ_IMAGE_NUM;
    }

    menulist[mid]->set_size(78,78);
    menulist[mid]->set_main_bg_img_src(imagelist.small[mid_image]);
    menulist[mid]->set_pos(point_list[EQ_IMAGE_NUM/2].x+26,point_list[EQ_IMAGE_NUM/2].y+26);

    scroll_flag=1;
    cur_index++;

    if((cur_index+EQ_IMAGE_NUM-1)<0)
    {
        if((cur_index+EQ_IMAGE_NUM-1)%EQ_IMAGE_NUM==0)
            new_image=0;
        else
            new_image=EQ_IMAGE_NUM+((cur_index+EQ_IMAGE_NUM-1)%(EQ_IMAGE_NUM));
    }
    else
    {
        new_image = (cur_index+EQ_IMAGE_NUM-1)%EQ_IMAGE_NUM;
    }
    menulist[cur_head]->set_main_bg_img_src(imagelist.small[new_image]);
}


void EQ_setting::draw_point(void)
{
    memset(point,0,sizeof(point));
    int X = (int)(sqrt(abs((EQ_LIST_LEN-EQ_LIST_LEN)*(EQ_LIST_LEN-EQ_LIST_LEN))/2));
    int Y = (int)(sqrt(abs((EQ_LIST_LEN-EQ_LIST_LEN)*(EQ_LIST_LEN-EQ_LIST_LEN))/2));
    //LV_LOG_USER("Center of the circle:X=%d,Y=%d",X,Y);
    for(int i=0;i<EQ_LIST_LEN+1;i++)
    {
        point[i].x =X+i;
        point[i].y =Y+SOUNDS_LIST_HIGH/2;
    }
    /*
    LvcppLine* line = new LvcppLine(cont->myobj);
    line->set_points(point,EQ_LIST_LEN);
    lv_obj_set_style_line_color(line->myobj,lv_color_white(),0);
    */
    memset(point_list,0,sizeof(point_list));
    for(int j=0;j< EQ_IMAGE_NUM;j++)
    {
        if(j<EQ_IMAGE_NUM/2)
        {
            point_list[j].x = point[abs(EQ_LIST_LEN/(EQ_IMAGE_NUM-1)*j-1)].x;
            point_list[j].y =point[abs(EQ_LIST_LEN/(EQ_IMAGE_NUM-1)*j-1)].y;
        }
        else if(j>EQ_IMAGE_NUM/2)
        {
            point_list[j].x = point[abs(EQ_LIST_LEN/(EQ_IMAGE_NUM-1)*j-1)].x;
            point_list[j].y =point[abs(EQ_LIST_LEN/(EQ_IMAGE_NUM-1)*j-1)].y;
        }
        else
        {
            point_list[j].x = point[abs(EQ_LIST_LEN/(EQ_IMAGE_NUM-1)*j-1)].x-26;
            point_list[j].y =point[abs(EQ_LIST_LEN/(EQ_IMAGE_NUM-1)*j-1)].y-26;
        }
        scroll_len = (int)(EQ_LIST_LEN/(EQ_IMAGE_NUM-1));
        //point_list[j].x = //X+(int)(sqrt(EQ_LIST_LEN*EQ_LIST_LEN-X*X))-(int)(EQ_LIST_LEN*cos(PI/180*(90*1.0f/(EQ_IMAGE_NUM-1))*j));
        //point_list[j].y = //-Y+(int)(EQ_LIST_LEN*sin(PI/180*(90*1.0f/(EQ_IMAGE_NUM-1))*j))-60;
        //LV_LOG_USER("x[%d]=%d,y[%d]=%d",j,point_list[j].x,j,point_list[j].y);
    }

}
/*这段代码是用于绘制一个图形界面上的等化器的点阵，其中使用了memset函数对point和point_list
 * 进行了初始化，然后计算出了圆形的中心点坐标X和Y，接着用for循环对point数组进行了赋值，
 * 将每个点的横坐标设置为X+i，纵坐标设置为Y+SOUNDS_LIST_HIGH/2。然后使用for循环
 * 对point_list数组进行了赋值，其中使用了abs函数对EQ_LIST_LEN/(EQ_IMAGE_NUM-1)*j-1进行了
 * 取绝对值的操作，然后根据j的值来设置每个点的横纵坐标，最后计算出了scroll_len的值*/



//loop run(must achieve)
void EQ_setting::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);
    static int count = 0;//static variable once assign

    if(scroll_flag!=0)
    {
        count++;
        scroll_anim_exe(count);
        if(count>=ANIM_STEP)
        {
            //anim finish
            imagelist_update();
            count = 0;
            scroll_flag=0;
        }
    }
}


void EQ_setting::scroll_anim_exe(int step)
{
    int step_len=(int)(scroll_len/ANIM_STEP);
    int cnt = 0;

    if(scroll_flag==1)
    {
        for(int i = 0; i < EQ_IMAGE_NUM; i++)
        {
            if(i!=cur_head)
            {
                if((i-cur_head)%(EQ_IMAGE_NUM)<0)
                {
                    if((i-cur_head)%EQ_IMAGE_NUM==0)
                        cnt=0;
                    else
                        cnt=EQ_IMAGE_NUM+((i-cur_head)%(EQ_IMAGE_NUM));
                }
                else
                {
                    cnt = (i-cur_head)%(EQ_IMAGE_NUM);
                }
                menulist[i]->set_pos(point[(int)(abs(EQ_LIST_LEN/(EQ_IMAGE_NUM-1)*cnt)-step_len*step)].x,point[(int)(abs(EQ_LIST_LEN/(EQ_IMAGE_NUM-1)*cnt)-step_len*step)].y);
            }
            else
            {
                menulist[i]->set_pos(point[(int)(abs(EQ_LIST_LEN))].x,point[(int)(abs(EQ_LIST_LEN))].y);
            }
        }
    }
    else if(scroll_flag==-1)
    {
        for(int i = 0; i < EQ_IMAGE_NUM; i++)
        {
            if(i!=cur_tail)
            {
                if((i-cur_head)%(EQ_IMAGE_NUM)<0)
                {
                    if((i-cur_head)%EQ_IMAGE_NUM==0)
                        cnt=0;
                    else
                        cnt=EQ_IMAGE_NUM+((i-cur_head)%(EQ_IMAGE_NUM));
                }
                else
                {
                    cnt = (i-cur_head)%(EQ_IMAGE_NUM);
                }
                menulist[i]->set_pos(point[(int)(abs(EQ_LIST_LEN/(EQ_IMAGE_NUM-1)*abs(cnt)-1)+step_len*step)].x,point[(int)(abs(EQ_LIST_LEN/(EQ_IMAGE_NUM-1)*abs(cnt)-1)+step_len*step)].y);
            }
            else
            {
                menulist[i]->set_pos(point[(int)(abs(0))].x,point[(int)(abs(0))].y);
            }
        }
    }
}

void EQ_setting::imagelist_update(void)
{
    int cnt=0,mid=0;
    if(cur_index<0)
    {
        if(cur_index%EQ_IMAGE_NUM==0)
            cur_head=0;
        else
            cur_head=EQ_IMAGE_NUM+(cur_index%(EQ_IMAGE_NUM));
    }
    else
    {
        cur_head=cur_index%(EQ_IMAGE_NUM);
    }

    mid=(cur_head+EQ_IMAGE_NUM/2)%(EQ_IMAGE_NUM);
    cur_tail=(cur_head+EQ_IMAGE_NUM-1)%(EQ_IMAGE_NUM);
    //LV_LOG_USER("cur_head=%d",cur_head);
    //LV_LOG_USER("cur_tail=%d",cur_tail);

    if((cur_index+EQ_IMAGE_NUM/2)<0)
    {
        if((cur_index+EQ_IMAGE_NUM/2)%EQ_IMAGE_NUM==0)
            mid_image=0;
        else
            mid_image=EQ_IMAGE_NUM+((cur_index+EQ_IMAGE_NUM/2)%(EQ_IMAGE_NUM));
    }
    else
    {
        mid_image = (cur_index+EQ_IMAGE_NUM/2)%EQ_IMAGE_NUM;
    }

    //update list
    for(int i = 0; i < EQ_IMAGE_NUM; i++)
    {
        if((i-cur_head)%(EQ_IMAGE_NUM)<0)
        {
            if((i-cur_head)%EQ_IMAGE_NUM==0)
                cnt=0;
            else
                cnt=EQ_IMAGE_NUM+((i-cur_head)%(EQ_IMAGE_NUM));
        }
        else
        {
            cnt = (i-cur_head)%(EQ_IMAGE_NUM);
        }

        if(i==mid)
        {
            menulist[i]->set_size(130,130);
            menulist[i]->set_pos(point_list[EQ_IMAGE_NUM/2].x,point_list[EQ_IMAGE_NUM/2].y);
            menulist[i]->set_main_bg_img_src(imagelist.big[mid_image]);
            if(current_function != NULL)
            {
                current_function->set_txt(txtlist[mid_image]);
            }
        }
        else
        {
            menulist[i]->set_size(78,78);
            menulist[i]->set_pos(point_list[cnt].x,point_list[cnt].y);
        }
    }
}


