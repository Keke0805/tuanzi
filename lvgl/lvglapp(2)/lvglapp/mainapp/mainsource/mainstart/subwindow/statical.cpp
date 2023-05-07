#include "statical.h"
#include "common/common.h"
#include "math.h"


using namespace LVGLOPTAPI;

const char* image_url[STATIC_IMAGE_NUM] = {
    "/mnt/UDISK/wallpaper/static/christmas.jpg",
    "/mnt/UDISK/wallpaper/static/disco.jpg",
    "/mnt/UDISK/wallpaper/static/Butterflies-neon-light.jpg",
    "/mnt/UDISK/wallpaper/static/Classic.jpg",
    "/mnt/UDISK/wallpaper/static/game.jpg",
    "/mnt/UDISK/wallpaper/static/Space-Wallpaper.jpg",
    "/mnt/UDISK/wallpaper/static/Halloween.jpg",
};

void Statical::ui_image_decode(void)
{
    int index=0;
    LvcppMemory::memset(&imagelist,0,sizeof(staticimage_t));

    Statical_Christmas_B_PNG=(void*)parse_image_from_file((char*)STATIACL_CHRISTMAS_B_PNG_PATH);
    Statical_Christmas_S_PNG=(void*)parse_image_from_file((char*)STATIACL_CHRISTMAS_S_PNG_PATH);
    imagelist.big[index]= Statical_Christmas_B_PNG;
    imagelist.small[index]= Statical_Christmas_S_PNG;
    index++;

    Statical_Disco_B_PNG=(void*)parse_image_from_file((char*)STATIACL_DISCO_B_PNG_PATH);
    Statical_Disco_S_PNG=(void*)parse_image_from_file((char*)STATIACL_DISCO_S_PNG_PATH);
    imagelist.big[index]= Statical_Disco_B_PNG;
    imagelist.small[index]= Statical_Disco_S_PNG;
    index++;


    Statical_Butter_B_PNG=(void*)parse_image_from_file((char*)STATIACL_BUTTER_B_PNG_PATH);
    Statical_Butter_S_PNG=(void*)parse_image_from_file((char*)STATIACL_BUTTER_S_PNG_PATH);
    imagelist.big[index]= Statical_Butter_B_PNG;
    imagelist.small[index]= Statical_Butter_S_PNG;
    index++;

    Statical_Classic_B_PNG=(void*)parse_image_from_file((char*)STATIACL_CLASSIC_B_PNG_PATH);
    Statical_Classic_S_PNG=(void*)parse_image_from_file((char*)STATIACL_CLASSIC_S_PNG_PATH);
    imagelist.big[index]= Statical_Classic_B_PNG;
    imagelist.small[index]= Statical_Classic_S_PNG;
    index++;

    Statical_Game_B_PNG=(void*)parse_image_from_file((char*)STATIACL_GAME_B_PNG_PATH);
    Statical_Game_S_PNG=(void*)parse_image_from_file((char*)STATIACL_GAME_S_PNG_PATH);
    imagelist.big[index]= Statical_Game_B_PNG;
    imagelist.small[index]= Statical_Game_S_PNG;
    index++;

    Statical_Space_B_PNG=(void*)parse_image_from_file((char*)STATIACL_SPACE_B_PNG_PATH);
    Statical_Space_S_PNG=(void*)parse_image_from_file((char*)STATIACL_SPACE_S_PNG_PATH);
    imagelist.big[index]= Statical_Space_B_PNG;
    imagelist.small[index]= Statical_Space_S_PNG;
    index++;

    Statical_Halloween_B_PNG=(void*)parse_image_from_file((char*)STATIACL_HALLOWEEN_B_PNG_PATH);
    Statical_Halloween_S_PNG=(void*)parse_image_from_file((char*)STATIACL_HALLOWEEN_S_PNG_PATH);
    imagelist.big[index]= Statical_Halloween_B_PNG;
    imagelist.small[index]= Statical_Halloween_S_PNG;
    index++;
}

void Statical::ui_txt_decede(void)
{
    int index=0;
    LvcppMemory::memset(txtlist,0,sizeof(txtlist));

    txtlist[index] = (char *)"Christmas";
    index++;

    txtlist[index] = (char *)"Disco";
    index++;

    txtlist[index] = (char *)"Butter";
    index++;

    txtlist[index] = (char *)"Classic";
    index++;

    txtlist[index] = (char *)"Game";
    index++;

    txtlist[index] = (char *)"Space";
    index++;

    txtlist[index] = (char *)"Halloween";
    index++;

}

void Statical::ui_image_free(void)
{
    if(Statical_Butter_B_PNG !=NULL)
    {
        free_image(Statical_Butter_B_PNG);
        Statical_Butter_B_PNG =NULL;
    }
    if(Statical_Butter_S_PNG !=NULL)
    {
        free_image(Statical_Butter_S_PNG);
        Statical_Butter_S_PNG =NULL;
    }
    if(Statical_Christmas_B_PNG !=NULL)
    {
        free_image(Statical_Christmas_B_PNG);
        Statical_Christmas_B_PNG =NULL;
    }
    if(Statical_Christmas_S_PNG !=NULL)
    {
        free_image(Statical_Christmas_S_PNG);
        Statical_Christmas_S_PNG =NULL;
    }

    if(Statical_Classic_B_PNG !=NULL)
    {
        free_image(Statical_Classic_B_PNG);
        Statical_Classic_B_PNG =NULL;
    }
    if(Statical_Classic_S_PNG !=NULL)
    {
        free_image(Statical_Classic_S_PNG);
        Statical_Classic_S_PNG =NULL;
    }

    if(Statical_Disco_B_PNG !=NULL)
    {
        free_image(Statical_Disco_B_PNG);
        Statical_Disco_B_PNG =NULL;
    }
    if(Statical_Disco_S_PNG !=NULL)
    {
        free_image(Statical_Disco_S_PNG);
        Statical_Disco_S_PNG =NULL;
    }

    if(Statical_Game_B_PNG !=NULL)
    {
        free_image(Statical_Game_B_PNG);
        Statical_Game_B_PNG =NULL;
    }
    if(Statical_Game_S_PNG !=NULL)
    {
        free_image(Statical_Game_S_PNG);
        Statical_Game_S_PNG =NULL;
    }

    if(Statical_Halloween_B_PNG !=NULL)
    {
        free_image(Statical_Halloween_B_PNG);
        Statical_Halloween_B_PNG =NULL;
    }
    if(Statical_Halloween_S_PNG !=NULL)
    {
        free_image(Statical_Halloween_S_PNG);
        Statical_Halloween_S_PNG =NULL;
    }

    if(Statical_Space_B_PNG !=NULL)
    {
        free_image(Statical_Space_B_PNG);
        Statical_Space_B_PNG =NULL;
    }
    if(Statical_Space_S_PNG !=NULL)
    {
        free_image(Statical_Space_S_PNG);
        Statical_Space_S_PNG =NULL;
    }

    LvcppMemory::memset(imagelist.big,0,sizeof(imagelist.big));
    LvcppMemory::memset(imagelist.small,0,sizeof(imagelist.small));
    LvcppMemory::memset(&imagelist,0,sizeof(staticimage_t));
}

Statical::Statical(lv_obj_t* parent)
{
    mscreen = new LvcppScreen(parent);
    mscreen->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    mscreen->set_main_bg_color(lv_color_white(),LV_OPA_0);
    m_parent = mscreen->myobj;
    initial();
}

Statical::~Statical()
{
    deinitial();
    ui_image_free();
}

//User starts here
void Statical::initial(void)
{
    ui_image_decode();
    ui_txt_decede();
    lvgl_scroll_anim();
    current_position = new LvcppLabel(m_parent);
    current_position->set_txt("Statical");
    current_position->txt_font_size(100,0);
    current_position->align(LV_ALIGN_CENTER,0,-200);
    current_position->set_size(400,200);
    current_position->txt_align(LV_TEXT_ALIGN_CENTER);

    current_function = new LvcppLabel(m_parent);
    current_function->set_txt("Classic");
    current_function->txt_font_size(30,0);
    current_function->set_size(200,100);
    current_function->align(LV_ALIGN_CENTER,0,180);
    current_function->txt_align(LV_TEXT_ALIGN_CENTER);

    maintimer = startTimer(20,this);
}

void Statical::deinitial(void)
{
    for(int i = 0; i < STATIC_IMAGE_NUM; i++) {
        if(menulist[i]!=nullptr)
        {
            delete menulist[i];
            menulist[i] = nullptr;
        }
    }
    memset(menulist,0,sizeof(menulist));

    if(cont!=nullptr)
    {
        delete cont;
        cont = nullptr;
    }
    if(current_position!=nullptr)
    {
        delete current_position;
        current_position = nullptr;
    }
    if(current_function!=nullptr)
    {
        delete current_function;
        current_function = nullptr;
    }
    if(mscreen!=nullptr)
    {
        delete mscreen;
        mscreen = nullptr;
    }
}



void Statical::switch_cartoon_left(void)
{
    if(scroll_flag!=0)
    {
        return;
    }
    int mid=0,new_image=0;
    char index[32]={0};

    mid=(cur_head+STATIC_IMAGE_NUM/2)%(STATIC_IMAGE_NUM);

    if((cur_index+STATIC_IMAGE_NUM/2)<0)
    {
        if((cur_index+STATIC_IMAGE_NUM/2)%STATIC_IMAGE_NUM==0)
            mid_image=0;
        else
            mid_image=STATIC_IMAGE_NUM+((cur_index+STATIC_IMAGE_NUM/2)%(STATIC_IMAGE_NUM));
    }
    else
    {
        mid_image = (cur_index+STATIC_IMAGE_NUM/2)%STATIC_IMAGE_NUM;
    }

    menulist[mid]->set_size(78,78);
    menulist[mid]->set_main_bg_img_src(imagelist.small[mid_image]);
    menulist[mid]->set_pos(point_list[STATIC_IMAGE_NUM/2].x+26,point_list[STATIC_IMAGE_NUM/2].y+26);

    scroll_flag=-1;
    cur_index--;

    if((cur_index)<0)
    {
        if((cur_index)%STATIC_IMAGE_NUM==0)
            new_image=0;
        else
            new_image=STATIC_IMAGE_NUM+((cur_index)%(STATIC_IMAGE_NUM));
    }
    else
    {
        new_image = (cur_index)%STATIC_IMAGE_NUM;
    }
    menulist[cur_tail]->set_main_bg_img_src(imagelist.small[new_image]);

}


void Statical::switch_cartoon_right(void)
{
    if(scroll_flag!=0)
    {
        return;
    }
    int mid=0,new_image=0;
    char index[32]={0};

    mid=(cur_head+STATIC_IMAGE_NUM/2)%(STATIC_IMAGE_NUM);

    if((cur_index+STATIC_IMAGE_NUM/2)<0)
    {
        if((cur_index+STATIC_IMAGE_NUM/2)%STATIC_IMAGE_NUM==0)
            mid_image=0;
        else
            mid_image=STATIC_IMAGE_NUM+((cur_index+STATIC_IMAGE_NUM/2)%(STATIC_IMAGE_NUM));
    }
    else
    {
        mid_image = (cur_index+STATIC_IMAGE_NUM/2)%STATIC_IMAGE_NUM;
    }

    menulist[mid]->set_size(78,78);
    menulist[mid]->set_main_bg_img_src(imagelist.small[mid_image]);
    menulist[mid]->set_pos(point_list[STATIC_IMAGE_NUM/2].x+26,point_list[STATIC_IMAGE_NUM/2].y+26);

    scroll_flag=1;
    cur_index++;

    if((cur_index+STATIC_IMAGE_NUM-1)<0)
    {
        if((cur_index+STATIC_IMAGE_NUM-1)%STATIC_IMAGE_NUM==0)
            new_image=0;
        else
            new_image=STATIC_IMAGE_NUM+((cur_index+STATIC_IMAGE_NUM-1)%(STATIC_IMAGE_NUM));
    }
    else
    {
        new_image = (cur_index+STATIC_IMAGE_NUM-1)%STATIC_IMAGE_NUM;
    }
    menulist[cur_head]->set_main_bg_img_src(imagelist.small[new_image]);
}


void Statical::draw_point(void)
{
    memset(point,0,sizeof(point));
    int X = (int)(sqrt(abs((STATICAL_LIST_LEN-STATICAL_LIST_LEN)*(STATICAL_LIST_LEN-STATICAL_LIST_LEN))/2));
    int Y = (int)(sqrt(abs((STATICAL_LIST_LEN-STATICAL_LIST_LEN)*(STATICAL_LIST_LEN-STATICAL_LIST_LEN))/2));
    //LV_LOG_USER("Center of the circle:X=%d,Y=%d",X,Y);
    for(int i=0;i<STATICAL_LIST_LEN+1;i++)
    {
        point[i].x =X+i;
        point[i].y =Y+SOUNDS_LIST_HIGH/2;
    }
    /*
    LvcppLine* line = new LvcppLine(cont->myobj);
    line->set_points(point,STATICAL_LIST_LEN);
    lv_obj_set_style_line_color(line->myobj,lv_color_white(),0);
    */
    memset(point_list,0,sizeof(point_list));
    for(int j=0;j< STATIC_IMAGE_NUM;j++)
    {
        if(j<STATIC_IMAGE_NUM/2)
        {
            point_list[j].x = point[abs(STATICAL_LIST_LEN/(STATIC_IMAGE_NUM-1)*j)].x;
            point_list[j].y =point[abs(STATICAL_LIST_LEN/(STATIC_IMAGE_NUM-1)*j)].y;
        }
        else if(j>STATIC_IMAGE_NUM/2)
        {
            point_list[j].x = point[abs(STATICAL_LIST_LEN/(STATIC_IMAGE_NUM-1)*j)].x;
            point_list[j].y =point[abs(STATICAL_LIST_LEN/(STATIC_IMAGE_NUM-1)*j)].y;
        }
        else
        {
            point_list[j].x = point[abs(STATICAL_LIST_LEN/(STATIC_IMAGE_NUM-1)*j)].x-26;
            point_list[j].y =point[abs(STATICAL_LIST_LEN/(STATIC_IMAGE_NUM-1)*j)].y-26;
        }
        scroll_len = (int)(STATICAL_LIST_LEN/(STATIC_IMAGE_NUM-1));
    }

}


void Statical::lvgl_scroll_anim(void)
{
    cont = new LvcppScreen(m_parent);
    cont->set_style_radius(0,0);
    cont->set_size(STATICAL_LIST_LEN+(int)(STATICAL_LIST_LEN/(STATIC_IMAGE_NUM-1)/2), SOUNDS_LIST_HIGH);
    cont->align(LV_ALIGN_CENTER,0,0);
    cont->set_style_bg_color(lv_color_hex(0xff0000),LV_OPA_0,0);
    cont->set_style_clip_corner(true, 0);
    cont->set_scrollbar_mode( LV_SCROLLBAR_MODE_OFF);
    cont->set_style_pad_row(0,0);
    cont->set_style_pad_column(0,0);
    cont->set_style_pad_all(0,0);

    draw_point();

    memset(menulist,0,sizeof(menulist));
    for(int i = 0; i < STATIC_IMAGE_NUM; i++) {
        menulist[i] = new LvcppButton(cont->myobj);
        menulist[i]->set_style_pad_all(0,0);
        menulist[i]->set_style_bg_color(lv_color_white(),LV_OPA_0,0);
        if(i==STATIC_IMAGE_NUM/2)
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


//loop run(must achieve)
void Statical::TimerCB(lv_timer_t * tmr)
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


void Statical::scroll_anim_exe(int step)
{
    int step_len=(int)(scroll_len/ANIM_STEP);
    int cnt = 0;

    if(scroll_flag==1)
    {
        for(int i = 0; i < STATIC_IMAGE_NUM; i++)
        {
            if(i!=cur_head)
            {
                if((i-cur_head)%(STATIC_IMAGE_NUM)<0)
                {
                    if((i-cur_head)%STATIC_IMAGE_NUM==0)
                        cnt=0;
                    else
                        cnt=STATIC_IMAGE_NUM+((i-cur_head)%(STATIC_IMAGE_NUM));
                }
                else
                {
                    cnt = (i-cur_head)%(STATIC_IMAGE_NUM);
                }
                menulist[i]->set_pos(point[(int)(abs(STATICAL_LIST_LEN/(STATIC_IMAGE_NUM-1)*cnt)-step_len*step)].x,point[(int)(abs(STATICAL_LIST_LEN/(STATIC_IMAGE_NUM-1)*cnt)-step_len*step)].y);
            }
            else
            {
                menulist[i]->set_pos(point[(int)(abs(STATICAL_LIST_LEN))].x,point[(int)(abs(STATICAL_LIST_LEN))].y);
            }
        }
    }
    else if(scroll_flag==-1)
    {
        for(int i = 0; i < STATIC_IMAGE_NUM; i++)
        {
            if(i!=cur_tail)
            {
                if((i-cur_head)%(STATIC_IMAGE_NUM)<0)
                {
                    if((i-cur_head)%STATIC_IMAGE_NUM==0)
                        cnt=0;
                    else
                        cnt=STATIC_IMAGE_NUM+((i-cur_head)%(STATIC_IMAGE_NUM));
                }
                else
                {
                    cnt = (i-cur_head)%(STATIC_IMAGE_NUM);
                }
                menulist[i]->set_pos(point[(int)(abs(STATICAL_LIST_LEN/(STATIC_IMAGE_NUM-1)*abs(cnt))+step_len*step)].x,point[(int)(abs(STATICAL_LIST_LEN/(STATIC_IMAGE_NUM-1)*abs(cnt))+step_len*step)].y);
            }
            else
            {
                menulist[i]->set_pos(point[(int)(abs(0))].x,point[(int)(abs(0))].y);
            }
        }
    }
}

void Statical::imagelist_update(void)
{
    int cnt=0,mid=0;
    if(cur_index<0)
    {
        if(cur_index%STATIC_IMAGE_NUM==0)
            cur_head=0;
        else
            cur_head=STATIC_IMAGE_NUM+(cur_index%(STATIC_IMAGE_NUM));
    }
    else
    {
        cur_head=cur_index%(STATIC_IMAGE_NUM);
    }

    mid=(cur_head+STATIC_IMAGE_NUM/2)%(STATIC_IMAGE_NUM);
    cur_tail=(cur_head+STATIC_IMAGE_NUM-1)%(STATIC_IMAGE_NUM);
    //LV_LOG_USER("cur_head=%d",cur_head);
    //LV_LOG_USER("cur_tail=%d",cur_tail);

    if((cur_index+STATIC_IMAGE_NUM/2)<0)
    {
        if((cur_index+STATIC_IMAGE_NUM/2)%STATIC_IMAGE_NUM==0)
            mid_image=0;
        else
            mid_image=STATIC_IMAGE_NUM+((cur_index+STATIC_IMAGE_NUM/2)%(STATIC_IMAGE_NUM));
    }
    else
    {
        mid_image = (cur_index+STATIC_IMAGE_NUM/2)%STATIC_IMAGE_NUM;
    }

    //update list
    for(int i = 0; i < STATIC_IMAGE_NUM; i++)
    {
        if((i-cur_head)%(STATIC_IMAGE_NUM)<0)
        {
            if((i-cur_head)%STATIC_IMAGE_NUM==0)
                cnt=0;
            else
                cnt=STATIC_IMAGE_NUM+((i-cur_head)%(STATIC_IMAGE_NUM));
        }
        else
        {
            cnt = (i-cur_head)%(STATIC_IMAGE_NUM);
        }

        if(i==mid)
        {
            menulist[i]->set_size(130,130);
            menulist[i]->set_pos(point_list[STATIC_IMAGE_NUM/2].x,point_list[STATIC_IMAGE_NUM/2].y);
            menulist[i]->set_main_bg_img_src(imagelist.big[mid_image]);
            if(current_function != NULL)
            {
                current_function->set_txt(txtlist[mid_image]);
                image_player_to_play(image_url[mid_image]);
            }
        }
        else
        {
            menulist[i]->set_size(78,78);
            menulist[i]->set_pos(point_list[cnt].x,point_list[cnt].y);
        }
    }
}

void Statical::image_player_initial(void)
{
    //photo play
    #if QTSIM_PLATFORM==0
    usleep(500000);
    image_init();
    #endif
}

void Statical::image_player_deinitial(void)
{
    #if QTSIM_PLATFORM==0
    image_exit();
    #endif
}

void Statical::image_player_to_play(const char* path)
{
    #if QTSIM_PLATFORM==0
    image_disp_cache_enable(1);
    image_show(path, IMAGE_SHOW_MODE_NORMAL);
    image_disp_cache_enable(0);
    #endif
}

void Statical::wallpaper_initial(int cur_type)
{
    if(cur_type!=0)
    {
        image_player_initial();
    }
    image_player_to_play(image_url[mid_image]);
}
