#include "dynamic.h"
#include "common/common.h"
#include "math.h"

using namespace LVGLOPTAPI;

const char* video_url[DYNAMIC_IMAGE_NUM] = {
    "/mnt/UDISK/wallpaper/dynamic/Snow.mp4",
    "/mnt/UDISK/wallpaper/dynamic/Rain.mp4",
    "/mnt/UDISK/wallpaper/dynamic/Fireworks.mp4",
    "/mnt/UDISK/wallpaper/dynamic/Beat.mp4",
    "/mnt/UDISK/wallpaper/dynamic/City.mp4",
    "/mnt/UDISK/wallpaper/dynamic/Fireplace.mp4",
    "/mnt/UDISK/wallpaper/dynamic/Space.mp4",
    "/mnt/UDISK/wallpaper/dynamic/Jellyfish.mp4",
    "/mnt/UDISK/wallpaper/dynamic/seabed.mp4"
};

void Dynamic::ui_image_decode(void)
{
    int index=0;
    LvcppMemory::memset(&imagelist,0,sizeof(Dynamicimage_t));

    Dynamic_Snow_B_PNG=(void*)parse_image_from_file((char*)DYNAMIC_SNOW_B_PNG_PATH);
    Dynamic_Snow_S_PNG=(void*)parse_image_from_file((char*)DYNAMIC_SNOW_S_PNG_PATH);
    imagelist.big[index]= Dynamic_Snow_B_PNG;
    imagelist.small[index]= Dynamic_Snow_S_PNG;
    index++;

    Dynamic_Rain_B_PNG=(void*)parse_image_from_file((char*)DYNAMIC_RAIN_B_PNG_PATH);
    Dynamic_Rain_S_PNG=(void*)parse_image_from_file((char*)DYNAMIC_RAIN_S_PNG_PATH);
    imagelist.big[index]= Dynamic_Rain_B_PNG;
    imagelist.small[index]= Dynamic_Rain_S_PNG;
    index++;

    Dynamic_Fireworks_B_PNG=(void*)parse_image_from_file((char*)DYNAMIC_FIREWORKS_B_PNG_PATH);
    Dynamic_Fireworks_S_PNG=(void*)parse_image_from_file((char*)DYNAMIC_FIREWORKS_S_PNG_PATH);
    imagelist.big[index]= Dynamic_Fireworks_B_PNG;
    imagelist.small[index]= Dynamic_Fireworks_S_PNG;
    index++;


    Dynamic_Beat_B_PNG=(void*)parse_image_from_file((char*)DYNAMIC_BEAT_B_PNG_PATH);
    Dynamic_Beat_S_PNG=(void*)parse_image_from_file((char*)DYNAMIC_BEAT_S_PNG_PATH);
    imagelist.big[index]= Dynamic_Beat_B_PNG;
    imagelist.small[index]= Dynamic_Beat_S_PNG;
    index++;

    Dynamic_City_B_PNG=(void*)parse_image_from_file((char*)DYNAMIC_CITY_B_PNG_PATH);
    Dynamic_City_S_PNG=(void*)parse_image_from_file((char*)DYNAMIC_CITY_S_PNG_PATH);
    imagelist.big[index]= Dynamic_City_B_PNG;
    imagelist.small[index]= Dynamic_City_S_PNG;
    index++;

    Dynamic_Fireplace_B_PNG=(void*)parse_image_from_file((char*)DYNAMIC_FIREPLACE_B_PNG_PATH);
    Dynamic_Fireplace_S_PNG=(void*)parse_image_from_file((char*)DYNAMIC_FIREPLACE_S_PNG_PATH);
    imagelist.big[index]= Dynamic_Fireplace_B_PNG;
    imagelist.small[index]= Dynamic_Fireplace_S_PNG;
    index++;

    Dynamic_Space_B_PNG=(void*)parse_image_from_file((char*)DYNAMIC_SPACE_B_PNG_PATH);
    Dynamic_Space_S_PNG=(void*)parse_image_from_file((char*)DYNAMIC_SPACE_S_PNG_PATH);
    imagelist.big[index]= Dynamic_Space_B_PNG;
    imagelist.small[index]= Dynamic_Space_S_PNG;
    index++;


    Dynamic_Jellyfish_B_PNG=(void*)parse_image_from_file((char*)DYNAMIC_JELLYFISH_B_PNG_PATH);
    Dynamic_Jellyfish_S_PNG=(void*)parse_image_from_file((char*)DYNAMIC_JELLYFISH_S_PNG_PATH);
    imagelist.big[index]= Dynamic_Jellyfish_B_PNG;
    imagelist.small[index]= Dynamic_Jellyfish_S_PNG;
    index++;


    Dynamic_Seabed_B_PNG=(void*)parse_image_from_file((char*)DYNAMIC_SEABED_B_PNG_PATH);
    Dynamic_Seabed_S_PNG=(void*)parse_image_from_file((char*)DYNAMIC_SEABED_S_PNG_PATH);
    imagelist.big[index]= Dynamic_Seabed_B_PNG;
    imagelist.small[index]= Dynamic_Seabed_S_PNG;
    index++;

}

void Dynamic::ui_txt_decede(void)
{
    int index=0;
    LvcppMemory::memset(txtlist,0,sizeof(txtlist));


    txtlist[index] = (char *)"Snow";
    index++;


    txtlist[index] = (char *)"Rain";
    index++;

    txtlist[index] = (char *)"Fireworks";
    index++;

    txtlist[index] = (char *)"Beat";
    index++;

    txtlist[index] = (char *)"City";
    index++;

    txtlist[index] = (char *)"Fireplace";
    index++;

    txtlist[index] = (char *)"Space";
    index++;

    txtlist[index] = (char *)"Jellyfish";
    index++;

    txtlist[index] = (char *)"Seabed";
    index++;
}

void Dynamic::ui_image_free(void)
{
    if(Dynamic_Beat_B_PNG !=NULL)
    {
        free_image(Dynamic_Beat_B_PNG);
        Dynamic_Beat_B_PNG =NULL;
    }
    if(Dynamic_Beat_S_PNG !=NULL)
    {
        free_image(Dynamic_Beat_S_PNG);
        Dynamic_Beat_S_PNG =NULL;
    }

    if(Dynamic_City_B_PNG !=NULL)
    {
        free_image(Dynamic_City_B_PNG);
        Dynamic_City_B_PNG =NULL;
    }
    if(Dynamic_City_S_PNG !=NULL)
    {
        free_image(Dynamic_City_S_PNG);
        Dynamic_City_S_PNG =NULL;
    }

    if(Dynamic_Fireplace_B_PNG !=NULL)
    {
        free_image(Dynamic_Fireplace_B_PNG);
        Dynamic_Fireplace_B_PNG =NULL;
    }
    if(Dynamic_Fireplace_S_PNG !=NULL)
    {
        free_image(Dynamic_Fireplace_S_PNG);
        Dynamic_Fireplace_S_PNG =NULL;
    }

    if(Dynamic_Fireworks_B_PNG !=NULL)
    {
        free_image(Dynamic_Fireworks_B_PNG);
        Dynamic_Fireworks_B_PNG =NULL;
    }
    if(Dynamic_Fireworks_S_PNG !=NULL)
    {
        free_image(Dynamic_Fireworks_S_PNG);
        Dynamic_Fireworks_S_PNG =NULL;
    }

    if(Dynamic_Jellyfish_B_PNG !=NULL)
    {
        free_image(Dynamic_Jellyfish_B_PNG);
        Dynamic_Jellyfish_B_PNG =NULL;
    }
    if(Dynamic_Jellyfish_S_PNG !=NULL)
    {
        free_image(Dynamic_Jellyfish_S_PNG);
        Dynamic_Jellyfish_S_PNG =NULL;
    }

    if(Dynamic_Rain_B_PNG !=NULL)
    {
        free_image(Dynamic_Rain_B_PNG);
        Dynamic_Rain_B_PNG =NULL;
    }
    if(Dynamic_Rain_S_PNG !=NULL)
    {
        free_image(Dynamic_Rain_S_PNG);
        Dynamic_Rain_S_PNG =NULL;
    }

    if(Dynamic_Seabed_B_PNG !=NULL)
    {
        free_image(Dynamic_Seabed_B_PNG);
        Dynamic_Seabed_B_PNG =NULL;
    }
    if(Dynamic_Seabed_S_PNG !=NULL)
    {
        free_image(Dynamic_Seabed_S_PNG);
        Dynamic_Seabed_S_PNG =NULL;
    }

    if(Dynamic_Snow_B_PNG !=NULL)
    {
        free_image(Dynamic_Snow_B_PNG);
        Dynamic_Snow_B_PNG =NULL;
    }
    if(Dynamic_Snow_S_PNG !=NULL)
    {
        free_image(Dynamic_Snow_S_PNG);
        Dynamic_Snow_S_PNG =NULL;
    }

    if(Dynamic_Space_B_PNG !=NULL)
    {
        free_image(Dynamic_Space_B_PNG);
        Dynamic_Space_B_PNG =NULL;
    }
    if(Dynamic_Space_S_PNG !=NULL)
    {
        free_image(Dynamic_Space_S_PNG);
        Dynamic_Space_S_PNG =NULL;
    }

    LvcppMemory::memset(imagelist.big,0,sizeof(imagelist.big));
    LvcppMemory::memset(imagelist.small,0,sizeof(imagelist.small));
    LvcppMemory::memset(&imagelist,0,sizeof(Dynamicimage_t));
}

Dynamic::Dynamic(lv_obj_t* parent)
{
    mscreen = new LvcppScreen(parent);
    mscreen->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    mscreen->set_main_bg_color(lv_color_white(),LV_OPA_0);
    m_parent = mscreen->myobj;
    initial();
}

Dynamic::~Dynamic()
{
    deinitial();
    ui_image_free();
}

//User starts here
void Dynamic::initial(void)
{
    ui_image_decode();
    ui_txt_decede();
    lvgl_scroll_anim();
    current_position = new LvcppLabel(m_parent);
    current_position->set_txt("Dynamic");
    current_position->txt_font_size(100,0);
    current_position->align(LV_ALIGN_CENTER,0,-200);
    current_position->set_size(350,200);
    current_position->txt_align(LV_TEXT_ALIGN_CENTER);


    current_function = new LvcppLabel(m_parent);
    current_function->set_txt("City");
    current_function->txt_font_size(30,0);
    current_function->set_size(200,100);
    current_function->align(LV_ALIGN_CENTER,0,180);
    current_function->txt_align(LV_TEXT_ALIGN_CENTER);

    maintimer = startTimer(20,this);
}

void Dynamic::deinitial(void)
{
    for(int i = 0; i < DYNAMIC_IMAGE_NUM; i++) {
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



void Dynamic::switch_cartoon_left(void)
{
    if(scroll_flag!=0)
    {
        return;
    }
    int mid=0,new_image=0;
    char index[32]={0};

    mid=(cur_head+DYNAMIC_IMAGE_NUM/2)%(DYNAMIC_IMAGE_NUM);

    if((cur_index+DYNAMIC_IMAGE_NUM/2)<0)
    {
        if((cur_index+DYNAMIC_IMAGE_NUM/2)%DYNAMIC_IMAGE_NUM==0)
            mid_image=0;
        else
            mid_image=DYNAMIC_IMAGE_NUM+((cur_index+DYNAMIC_IMAGE_NUM/2)%(DYNAMIC_IMAGE_NUM));
    }
    else
    {
        mid_image = (cur_index+DYNAMIC_IMAGE_NUM/2)%DYNAMIC_IMAGE_NUM;
    }
    menulist[mid]->set_size(78,78);
    menulist[mid]->set_main_bg_img_src(imagelist.small[mid_image]);
    menulist[mid]->set_pos(point_list[DYNAMIC_IMAGE_NUM/2].x+26,point_list[DYNAMIC_IMAGE_NUM/2].y+26);

    scroll_flag=-1;
    cur_index--;

    if((cur_index)<0)
    {
        if((cur_index)%DYNAMIC_IMAGE_NUM==0)
            new_image=0;
        else
            new_image=DYNAMIC_IMAGE_NUM+((cur_index)%(DYNAMIC_IMAGE_NUM));
    }
    else
    {
        new_image = (cur_index)%DYNAMIC_IMAGE_NUM;
    }
    menulist[cur_tail]->set_main_bg_img_src(imagelist.small[new_image]);

}


void Dynamic::switch_cartoon_right(void)
{
    if(scroll_flag!=0)
    {
        return;
    }
    int mid=0,new_image=0;
    char index[32]={0};

    mid=(cur_head+DYNAMIC_IMAGE_NUM/2)%(DYNAMIC_IMAGE_NUM);

    if((cur_index+DYNAMIC_IMAGE_NUM/2)<0)
    {
        if((cur_index+DYNAMIC_IMAGE_NUM/2)%DYNAMIC_IMAGE_NUM==0)
            mid_image=0;
        else
            mid_image=DYNAMIC_IMAGE_NUM+((cur_index+DYNAMIC_IMAGE_NUM/2)%(DYNAMIC_IMAGE_NUM));
    }
    else
    {
        mid_image = (cur_index+DYNAMIC_IMAGE_NUM/2)%DYNAMIC_IMAGE_NUM;
    }

    menulist[mid]->set_size(78,78);
    menulist[mid]->set_main_bg_img_src(imagelist.small[mid_image]);
    menulist[mid]->set_pos(point_list[DYNAMIC_IMAGE_NUM/2].x+26,point_list[DYNAMIC_IMAGE_NUM/2].y+26);

    scroll_flag=1;
    cur_index++;

    if((cur_index+DYNAMIC_IMAGE_NUM-1)<0)
    {
        if((cur_index+DYNAMIC_IMAGE_NUM-1)%DYNAMIC_IMAGE_NUM==0)
            new_image=0;
        else
            new_image=DYNAMIC_IMAGE_NUM+((cur_index+DYNAMIC_IMAGE_NUM-1)%(DYNAMIC_IMAGE_NUM));
    }
    else
    {
        new_image = (cur_index+DYNAMIC_IMAGE_NUM-1)%DYNAMIC_IMAGE_NUM;
    }
    menulist[cur_head]->set_main_bg_img_src(imagelist.small[new_image]);
}


void Dynamic::draw_point(void)
{
    memset(point,0,sizeof(point));
    int X = (int)(sqrt(abs((DYNAMIC_LIST_LEN-DYNAMIC_LIST_LEN)*(DYNAMIC_LIST_LEN-DYNAMIC_LIST_LEN))/2));
    int Y = (int)(sqrt(abs((DYNAMIC_LIST_LEN-DYNAMIC_LIST_LEN)*(DYNAMIC_LIST_LEN-DYNAMIC_LIST_LEN))/2));
    //LV_LOG_USER("Center of the circle:X=%d,Y=%d",X,Y);
    for(int i=0;i<DYNAMIC_LIST_LEN+1;i++)
    {
        point[i].x =X+i;
        point[i].y =Y+SOUNDS_LIST_HIGH/2;
    }
    /*
    LvcppLine* line = new LvcppLine(cont->myobj);
    line->set_points(point,DYNAMIC_LIST_LEN);
    lv_obj_set_style_line_color(line->myobj,lv_color_white(),0);
    */
    memset(point_list,0,sizeof(point_list));
    for(int j=0;j< DYNAMIC_IMAGE_NUM;j++)
    {
        if(j<DYNAMIC_IMAGE_NUM/2)
        {
            point_list[j].x = point[abs(DYNAMIC_LIST_LEN/(DYNAMIC_IMAGE_NUM-1)*j-1)].x;
            point_list[j].y =point[abs(DYNAMIC_LIST_LEN/(DYNAMIC_IMAGE_NUM-1)*j-1)].y;
        }
        else if(j>DYNAMIC_IMAGE_NUM/2)
        {
            point_list[j].x = point[abs(DYNAMIC_LIST_LEN/(DYNAMIC_IMAGE_NUM-1)*j-1)].x;
            point_list[j].y =point[abs(DYNAMIC_LIST_LEN/(DYNAMIC_IMAGE_NUM-1)*j-1)].y;
        }
        else
        {
            point_list[j].x = point[abs(DYNAMIC_LIST_LEN/(DYNAMIC_IMAGE_NUM-1)*j-1)].x-26;
            point_list[j].y =point[abs(DYNAMIC_LIST_LEN/(DYNAMIC_IMAGE_NUM-1)*j-1)].y-26;
        }
        scroll_len = (int)(DYNAMIC_LIST_LEN/(DYNAMIC_IMAGE_NUM-1));
        //point_list[j].x = //X+(int)(sqrt(DYNAMIC_LIST_LEN*DYNAMIC_LIST_LEN-X*X))-(int)(DYNAMIC_LIST_LEN*cos(PI/180*(90*1.0f/(DYNAMIC_IMAGE_NUM-1))*j));
        //point_list[j].y = //-Y+(int)(DYNAMIC_LIST_LEN*sin(PI/180*(90*1.0f/(DYNAMIC_IMAGE_NUM-1))*j))-60;
        //LV_LOG_USER("x[%d]=%d,y[%d]=%d",j,point_list[j].x,j,point_list[j].y);
    }

}


void Dynamic::lvgl_scroll_anim(void)
{
    cont = new LvcppScreen(m_parent);
    cont->set_style_radius(0,0);
    cont->set_size(DYNAMIC_LIST_LEN+(int)(DYNAMIC_LIST_LEN/(DYNAMIC_IMAGE_NUM-1)/2), SOUNDS_LIST_HIGH);
    cont->align(LV_ALIGN_CENTER,0,0);
    cont->set_style_bg_color(lv_color_hex(0xff0000),LV_OPA_0,0);
    cont->set_style_clip_corner(true, 0);
    cont->set_scrollbar_mode( LV_SCROLLBAR_MODE_OFF);
    cont->set_style_pad_row(0,0);
    cont->set_style_pad_column(0,0);
    cont->set_style_pad_all(0,0);

    draw_point();

    memset(menulist,0,sizeof(menulist));
    for(int i = 0; i < DYNAMIC_IMAGE_NUM; i++) {
        menulist[i] = new LvcppButton(cont->myobj);
        menulist[i]->set_style_pad_all(0,0);
        menulist[i]->set_style_bg_color(lv_color_white(),LV_OPA_0,0);
        if(i==DYNAMIC_IMAGE_NUM/2)
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
void Dynamic::TimerCB(lv_timer_t * tmr)
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


void Dynamic::scroll_anim_exe(int step)
{
    int step_len=(int)(scroll_len/ANIM_STEP);
    int cnt = 0;

    if(scroll_flag==1)
    {
        for(int i = 0; i < DYNAMIC_IMAGE_NUM; i++)
        {
            if(i!=cur_head)
            {
                if((i-cur_head)%(DYNAMIC_IMAGE_NUM)<0)
                {
                    if((i-cur_head)%DYNAMIC_IMAGE_NUM==0)
                        cnt=0;
                    else
                        cnt=DYNAMIC_IMAGE_NUM+((i-cur_head)%(DYNAMIC_IMAGE_NUM));
                }
                else
                {
                    cnt = (i-cur_head)%(DYNAMIC_IMAGE_NUM);
                }
                menulist[i]->set_pos(point[(int)(abs(DYNAMIC_LIST_LEN/(DYNAMIC_IMAGE_NUM-1)*cnt)-step_len*step)].x,point[(int)(abs(DYNAMIC_LIST_LEN/(DYNAMIC_IMAGE_NUM-1)*cnt)-step_len*step)].y);
            }
            else
            {
                menulist[i]->set_pos(point[(int)(abs(DYNAMIC_LIST_LEN))].x,point[(int)(abs(DYNAMIC_LIST_LEN))].y);
            }
        }
    }
    else if(scroll_flag==-1)
    {
        for(int i = 0; i < DYNAMIC_IMAGE_NUM; i++)
        {
            if(i!=cur_tail)
            {
                if((i-cur_head)%(DYNAMIC_IMAGE_NUM)<0)
                {
                    if((i-cur_head)%DYNAMIC_IMAGE_NUM==0)
                        cnt=0;
                    else
                        cnt=DYNAMIC_IMAGE_NUM+((i-cur_head)%(DYNAMIC_IMAGE_NUM));
                }
                else
                {
                    cnt = (i-cur_head)%(DYNAMIC_IMAGE_NUM);
                }
                menulist[i]->set_pos(point[(int)(abs(DYNAMIC_LIST_LEN/(DYNAMIC_IMAGE_NUM-1)*abs(cnt))+step_len*step)].x,point[(int)(abs(DYNAMIC_LIST_LEN/(DYNAMIC_IMAGE_NUM-1)*abs(cnt))+step_len*step)].y);
            }
            else
            {
                menulist[i]->set_pos(point[(int)(abs(0))].x,point[(int)(abs(0))].y);
            }
        }
    }
}

void Dynamic::imagelist_update(void)
{
    int cnt=0,mid=0;
    if(cur_index<0)
    {
        if(cur_index%DYNAMIC_IMAGE_NUM==0)
            cur_head=0;
        else
            cur_head=DYNAMIC_IMAGE_NUM+(cur_index%(DYNAMIC_IMAGE_NUM));
    }
    else
    {
        cur_head=cur_index%(DYNAMIC_IMAGE_NUM);
    }

    mid=(cur_head+DYNAMIC_IMAGE_NUM/2)%(DYNAMIC_IMAGE_NUM);
    cur_tail=(cur_head+DYNAMIC_IMAGE_NUM-1)%(DYNAMIC_IMAGE_NUM);
    //LV_LOG_USER("cur_head=%d",cur_head);
    //LV_LOG_USER("cur_tail=%d",cur_tail);

    if((cur_index+DYNAMIC_IMAGE_NUM/2)<0)
    {
        if((cur_index+DYNAMIC_IMAGE_NUM/2)%DYNAMIC_IMAGE_NUM==0)
            mid_image=0;
        else
            mid_image=DYNAMIC_IMAGE_NUM+((cur_index+DYNAMIC_IMAGE_NUM/2)%(DYNAMIC_IMAGE_NUM));
    }
    else
    {
        mid_image = (cur_index+DYNAMIC_IMAGE_NUM/2)%DYNAMIC_IMAGE_NUM;
    }

    //update list
    for(int i = 0; i < DYNAMIC_IMAGE_NUM; i++)
    {
        if((i-cur_head)%(DYNAMIC_IMAGE_NUM)<0)
        {
            if((i-cur_head)%DYNAMIC_IMAGE_NUM==0)
                cnt=0;
            else
                cnt=DYNAMIC_IMAGE_NUM+((i-cur_head)%(DYNAMIC_IMAGE_NUM));
        }
        else
        {
            cnt = (i-cur_head)%(DYNAMIC_IMAGE_NUM);
        }

        if(i==mid)
        {
            menulist[i]->set_size(130,130);
            menulist[i]->set_pos(point_list[DYNAMIC_IMAGE_NUM/2].x,point_list[DYNAMIC_IMAGE_NUM/2].y);
            menulist[i]->set_main_bg_img_src(imagelist.big[mid_image]);
            if(current_function != NULL)
            {
                current_function->set_txt(txtlist[mid_image]);
                media_player_to_play(video_url[mid_image]);
            }
        }
        else
        {
            menulist[i]->set_size(78,78);
            menulist[i]->set_pos(point_list[cnt].x,point_list[cnt].y);
        }
    }
}




void Dynamic::media_player_initial(void)
{
    //video play
    #if QTSIM_PLATFORM==0
    player_ui_t* player_ui = media_get_player_data();
    tplayer_init(player_ui->tplayer, CEDARX_PLAYER);
    usleep(30000);
    #endif
}

void Dynamic::media_player_deinitial(void)
{
    #if QTSIM_PLATFORM==0
    player_ui_t *player_ui = media_get_player_data();
    tplayer_exit(player_ui->tplayer);
    #endif
}

void Dynamic::media_player_to_play(const char* url)
{
    #if QTSIM_PLATFORM==0
    player_ui_t* player_ui = media_get_player_data();
    tplayer_play_url(player_ui->tplayer, url);
    tplayer_play(player_ui->tplayer);
    tplayer_volume(player_ui->tplayer,0);
    tplayer_set_looping(player_ui->tplayer, true);
    #endif
}

void Dynamic::wallpaper_initial(int cur_type)
{
    if(cur_type!=1)
    {
        media_player_initial();
    }
    media_player_to_play(video_url[mid_image]);
}
