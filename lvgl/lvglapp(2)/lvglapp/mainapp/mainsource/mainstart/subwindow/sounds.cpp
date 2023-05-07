#include "sounds.h"
#include "common/common.h"
#include "math.h"

using namespace LVGLOPTAPI;

void Sounds::ui_image_decode(void)
{
    int index=0;
    LvcppMemory::memset(&imagelist,0,sizeof(soundsimage_t));

    SOUNDS_MUSICBOX_B_PNG=(void*)parse_image_from_file((char*)SOUNDS_MUSICBOX_B_PNG_PATH);
    SOUNDS_MUSICBOX_S_PNG=(void*)parse_image_from_file((char*)SOUNDS_MUSICBOX_S_PNG_PATH);
    imagelist.big[index]= SOUNDS_MUSICBOX_B_PNG;
    imagelist.small[index]= SOUNDS_MUSICBOX_S_PNG;
    index++;

    SOUNDS_THUNDERSTORM_B_PNG=(void*)parse_image_from_file((char*)SOUNDS_THUNDERSTORM_B_PNG_PATH);
    SOUNDS_THUNDERSTORM_S_PNG=(void*)parse_image_from_file((char*)SOUNDS_THUNDERSTORM_S_PNG_PATH);
    imagelist.big[index]= SOUNDS_THUNDERSTORM_B_PNG;
    imagelist.small[index]= SOUNDS_THUNDERSTORM_S_PNG;
    index++;

    SOUNDS_RAIN_B_PNG=(void*)parse_image_from_file((char*)SOUNDS_RAIN_B_PNG_PATH);
    SOUNDS_RAIN_S_PNG=(void*)parse_image_from_file((char*)SOUNDS_RAIN_S_PNG_PATH);
    imagelist.big[index]= SOUNDS_RAIN_B_PNG;
    imagelist.small[index]= SOUNDS_RAIN_S_PNG;
    index++;

    SOUNDS_STREAM_B_PNG=(void*)parse_image_from_file((char*)SOUNDS_STREAM_B_PNG_PATH);
    SOUNDS_STREAM_S_PNG=(void*)parse_image_from_file((char*)SOUNDS_STREAM_S_PNG_PATH);
    imagelist.big[index]= SOUNDS_STREAM_B_PNG;
    imagelist.small[index]= SOUNDS_STREAM_S_PNG;
    index++;

    SOUNDS_WAVE_B_PNG=(void*)parse_image_from_file((char*)SOUNDS_WAVE_B_PNG_PATH);
    SOUNDS_WAVE_S_PNG=(void*)parse_image_from_file((char*)SOUNDS_WAVE_S_PNG_PATH);
    imagelist.big[index]= SOUNDS_WAVE_B_PNG;
    imagelist.small[index]= SOUNDS_WAVE_S_PNG;
    index++;

    SOUNDS_OCEAN_B_PNG=(void*)parse_image_from_file((char*)SOUNDS_OCEAN_B_PNG_PATH);
    SOUNDS_OCEAN_S_PNG=(void*)parse_image_from_file((char*)SOUNDS_OCEAN_S_PNG_PATH);
    imagelist.big[index]= SOUNDS_OCEAN_B_PNG;
    imagelist.small[index]= SOUNDS_OCEAN_S_PNG;
    index++;

    SOUNDS_SUMMERNIGHT_B_PNG=(void*)parse_image_from_file((char*)SOUNDS_SUMMERNIGHT_B_PNG_PATH);
    SOUNDS_SUMMERNIGHT_S_PNG=(void*)parse_image_from_file((char*)SOUNDS_SUMMERNIGHT_S_PNG_PATH);
    imagelist.big[index]= SOUNDS_SUMMERNIGHT_B_PNG;
    imagelist.small[index]= SOUNDS_SUMMERNIGHT_S_PNG;
    index++;

    SOUNDS_BIRD_B_PNG=(void*)parse_image_from_file((char*)SOUNDS_BIRD_B_PNG_PATH);
    SOUNDS_BIRD_S_PNG=(void*)parse_image_from_file((char*)SOUNDS_BIRD_S_PNG_PATH);
    imagelist.big[index]= SOUNDS_BIRD_B_PNG;
    imagelist.small[index]= SOUNDS_BIRD_S_PNG;
    index++;

    SOUNDS_BONFIRE_B_PNG=(void*)parse_image_from_file((char*)SOUNDS_BONFIRE_B_PNG_PATH);
    SOUNDS_BONFIRE_S_PNG=(void*)parse_image_from_file((char*)SOUNDS_BONFIRE_S_PNG_PATH);
    imagelist.big[index]= SOUNDS_BONFIRE_B_PNG;
    imagelist.small[index]= SOUNDS_BONFIRE_S_PNG;
    index++;

    SOUNDS_WIND_B_PNG=(void*)parse_image_from_file((char*)SOUNDS_WIND_B_PNG_PATH);
    SOUNDS_WIND_S_PNG=(void*)parse_image_from_file((char*)SOUNDS_WIND_S_PNG_PATH);
    imagelist.big[index]= SOUNDS_WIND_B_PNG;
    imagelist.small[index]= SOUNDS_WIND_S_PNG;
    index++;

    SOUNDS_FAN_B_PNG=(void*)parse_image_from_file((char*)SOUNDS_FAN_B_PNG_PATH);
    SOUNDS_FAN_S_PNG=(void*)parse_image_from_file((char*)SOUNDS_FAN_S_PNG_PATH);
    imagelist.big[index]= SOUNDS_FAN_B_PNG;
    imagelist.small[index]= SOUNDS_FAN_S_PNG;
    index++;

    SOUNDS_PENDULUM_B_PNG=(void*)parse_image_from_file((char*)SOUNDS_PENDULUM_B_PNG_PATH);
    SOUNDS_PENDULUM_S_PNG=(void*)parse_image_from_file((char*)SOUNDS_PENDULUM_S_PNG_PATH);
    imagelist.big[index]= SOUNDS_PENDULUM_B_PNG;
    imagelist.small[index]= SOUNDS_PENDULUM_S_PNG;
    index++;

    SOUNDS_TRAIN_B_PNG=(void*)parse_image_from_file((char*)SOUNDS_TRAIN_B_PNG_PATH);
    SOUNDS_TRAIN_S_PNG=(void*)parse_image_from_file((char*)SOUNDS_TRAIN_S_PNG_PATH);
    imagelist.big[index]= SOUNDS_TRAIN_B_PNG;
    imagelist.small[index]= SOUNDS_TRAIN_S_PNG;
    index++;

    SOUNDS_TV_B_PNG=(void*)parse_image_from_file((char*)SOUNDS_TV_B_PNG_PATH);
    SOUNDS_TV_S_PNG=(void*)parse_image_from_file((char*)SOUNDS_TV_S_PNG_PATH);
    imagelist.big[index]= SOUNDS_TV_B_PNG;
    imagelist.small[index]= SOUNDS_TV_S_PNG;
    index++;

    SOUNDS_LULLABY_B_PNG=(void*)parse_image_from_file((char*)SOUNDS_LULLABY_B_PNG_PATH);
    SOUNDS_LULLABY_S_PNG=(void*)parse_image_from_file((char*)SOUNDS_LULLABY_S_PNG_PATH);
    imagelist.big[index]= SOUNDS_LULLABY_B_PNG;
    imagelist.small[index]= SOUNDS_LULLABY_S_PNG;
    index++;
}

void Sounds::ui_txt_decede(void)
{
    int index=0;
    LvcppMemory::memset(txtlist,0,sizeof(txtlist));

    txtlist[index] = (char *)"Musicbox";
    index++;

    txtlist[index] = (char *)"Thunderstorm";
    index++;

    txtlist[index] = (char *)"Rain";
    index++;

    txtlist[index] = (char *)"Stream";
    index++;

    txtlist[index] = (char *)"Wave";
    index++;

    txtlist[index] = (char *)"Ocean";
    index++;

    txtlist[index] = (char *)"Summernight";
    index++;

    txtlist[index] = (char *)"Birdsong";
    index++;

    txtlist[index] = (char *)"Bonfire";
    index++;

    txtlist[index] = (char *)"Wind";
    index++;

    txtlist[index] = (char *)"Fan";
    index++;

    txtlist[index] = (char *)"Pendulum";
    index++;

    txtlist[index] = (char *)"Train";
    index++;

    txtlist[index] = (char *)"TV";
    index++;

    txtlist[index] = (char *)"Lullaby";
    index++;
}

void Sounds::ui_image_free(void)
{
    if(SOUNDS_BIRD_B_PNG !=NULL)
    {
        free_image(SOUNDS_BIRD_B_PNG);
        SOUNDS_BIRD_B_PNG =NULL;
    }
    if(SOUNDS_BIRD_S_PNG !=NULL)
    {
        free_image(SOUNDS_BIRD_S_PNG);
        SOUNDS_BIRD_S_PNG =NULL;
    }

    if(SOUNDS_BONFIRE_B_PNG !=NULL)
    {
        free_image(SOUNDS_BONFIRE_B_PNG);
        SOUNDS_BONFIRE_B_PNG =NULL;
    }
    if(SOUNDS_BONFIRE_S_PNG !=NULL)
    {
        free_image(SOUNDS_BONFIRE_S_PNG);
        SOUNDS_BONFIRE_S_PNG =NULL;
    }

    if(SOUNDS_FAN_B_PNG !=NULL)
    {
        free_image(SOUNDS_FAN_B_PNG);
        SOUNDS_FAN_B_PNG =NULL;
    }
    if(SOUNDS_FAN_S_PNG !=NULL)
    {
        free_image(SOUNDS_FAN_S_PNG);
        SOUNDS_FAN_S_PNG =NULL;
    }

    if(SOUNDS_LULLABY_B_PNG !=NULL)
    {
        free_image(SOUNDS_LULLABY_B_PNG);
        SOUNDS_LULLABY_B_PNG =NULL;
    }
    if(SOUNDS_LULLABY_S_PNG !=NULL)
    {
        free_image(SOUNDS_LULLABY_S_PNG);
        SOUNDS_LULLABY_S_PNG =NULL;
    }

    if(SOUNDS_MUSICBOX_B_PNG !=NULL)
    {
        free_image(SOUNDS_MUSICBOX_B_PNG);
        SOUNDS_MUSICBOX_B_PNG =NULL;
    }
    if(SOUNDS_MUSICBOX_S_PNG !=NULL)
    {
        free_image(SOUNDS_MUSICBOX_S_PNG);
        SOUNDS_MUSICBOX_S_PNG =NULL;
    }

    if(SOUNDS_OCEAN_B_PNG !=NULL)
    {
        free_image(SOUNDS_OCEAN_B_PNG);
        SOUNDS_OCEAN_B_PNG =NULL;
    }
    if(SOUNDS_OCEAN_S_PNG !=NULL)
    {
        free_image(SOUNDS_OCEAN_S_PNG);
        SOUNDS_OCEAN_S_PNG =NULL;
    }

    if(SOUNDS_PENDULUM_B_PNG !=NULL)
    {
        free_image(SOUNDS_PENDULUM_B_PNG);
        SOUNDS_PENDULUM_B_PNG =NULL;
    }
    if(SOUNDS_PENDULUM_S_PNG !=NULL)
    {
        free_image(SOUNDS_PENDULUM_S_PNG);
        SOUNDS_PENDULUM_S_PNG =NULL;
    }

    if(SOUNDS_RAIN_B_PNG !=NULL)
    {
        free_image(SOUNDS_RAIN_B_PNG);
        SOUNDS_RAIN_B_PNG =NULL;
    }
    if(SOUNDS_RAIN_S_PNG !=NULL)
    {
        free_image(SOUNDS_RAIN_S_PNG);
        SOUNDS_RAIN_S_PNG =NULL;
    }

    if(SOUNDS_STREAM_B_PNG !=NULL)
    {
        free_image(SOUNDS_STREAM_B_PNG);
        SOUNDS_STREAM_B_PNG =NULL;
    }
    if(SOUNDS_STREAM_S_PNG !=NULL)
    {
        free_image(SOUNDS_STREAM_S_PNG);
        SOUNDS_STREAM_S_PNG =NULL;
    }

    if(SOUNDS_SUMMERNIGHT_B_PNG !=NULL)
    {
        free_image(SOUNDS_SUMMERNIGHT_B_PNG);
        SOUNDS_SUMMERNIGHT_B_PNG =NULL;
    }
    if(SOUNDS_SUMMERNIGHT_S_PNG !=NULL)
    {
        free_image(SOUNDS_SUMMERNIGHT_S_PNG);
        SOUNDS_SUMMERNIGHT_S_PNG =NULL;
    }

    if(SOUNDS_THUNDERSTORM_B_PNG !=NULL)
    {
        free_image(SOUNDS_THUNDERSTORM_B_PNG);
        SOUNDS_THUNDERSTORM_B_PNG =NULL;
    }
    if(SOUNDS_THUNDERSTORM_S_PNG !=NULL)
    {
        free_image(SOUNDS_THUNDERSTORM_S_PNG);
        SOUNDS_THUNDERSTORM_S_PNG =NULL;
    }

    if(SOUNDS_TRAIN_B_PNG !=NULL)
    {
        free_image(SOUNDS_TRAIN_B_PNG);
        SOUNDS_TRAIN_B_PNG =NULL;
    }
    if(SOUNDS_TRAIN_S_PNG !=NULL)
    {
        free_image(SOUNDS_TRAIN_S_PNG);
        SOUNDS_TRAIN_S_PNG =NULL;
    }

    if(SOUNDS_TV_B_PNG !=NULL)
    {
        free_image(SOUNDS_TV_B_PNG);
        SOUNDS_TV_B_PNG =NULL;
    }
    if(SOUNDS_TV_S_PNG !=NULL)
    {
        free_image(SOUNDS_TV_S_PNG);
        SOUNDS_TV_S_PNG =NULL;
    }
    if(SOUNDS_WAVE_B_PNG !=NULL)
    {
        free_image(SOUNDS_WAVE_B_PNG);
        SOUNDS_WAVE_B_PNG =NULL;
    }
    if(SOUNDS_WAVE_S_PNG !=NULL)
    {
        free_image(SOUNDS_WAVE_S_PNG);
        SOUNDS_WAVE_S_PNG =NULL;
    }

    if(SOUNDS_WIND_B_PNG !=NULL)
    {
        free_image(SOUNDS_WIND_B_PNG);
        SOUNDS_WIND_B_PNG =NULL;
    }
    if(SOUNDS_WIND_S_PNG !=NULL)
    {
        free_image(SOUNDS_WIND_S_PNG);
        SOUNDS_WIND_S_PNG =NULL;
    }

    LvcppMemory::memset(imagelist.big,0,sizeof(imagelist.big));
    LvcppMemory::memset(imagelist.small,0,sizeof(imagelist.small));
    LvcppMemory::memset(&imagelist,0,sizeof(soundsimage_t));
}

Sounds::Sounds(lv_obj_t* parent)
{
    mscreen = new LvcppScreen(parent);
    mscreen->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    mscreen->set_main_bg_color(lv_color_white(),LV_OPA_100);
    m_parent = mscreen->myobj;
    initial();
}

Sounds::~Sounds()
{
    deinitial();
    ui_image_free();
}

//User starts here
void Sounds::initial(void)
{
    ui_image_decode();
    ui_txt_decede();
    lvgl_scroll_anim();
    current_position = new LvcppLabel(m_parent);
    current_position->set_txt("Sounds");
    current_position->txt_font_size(100,0);
    current_position->align(LV_ALIGN_CENTER,0,-200);
    current_position->set_size(300,200);
    current_position->txt_align(LV_TEXT_ALIGN_CENTER);

    current_function = new LvcppLabel(m_parent);
    current_function->set_txt("Birdsong");
    current_function->txt_font_size(30,0);
    current_function->set_size(200,100);
    current_function->align(LV_ALIGN_CENTER,0,180);
    current_function->txt_align(LV_TEXT_ALIGN_CENTER);

    maintimer = startTimer(20,this);
}

void Sounds::deinitial(void)
{
    for(int i = 0; i < SOUNDS_IMAGE_NUM; i++) {
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



void Sounds::switch_cartoon_left(void)
{
    if(scroll_flag!=0)
    {
        return;
    }
    int mid=0,new_image=0;

    mid=(cur_head+SOUNDS_IMAGE_NUM/2)%(SOUNDS_IMAGE_NUM);

    if((cur_index+SOUNDS_IMAGE_NUM/2)<0)
    {
        if((cur_index+SOUNDS_IMAGE_NUM/2)%SOUNDS_IMAGE_NUM==0)
            mid_image=0;
        else
            mid_image=SOUNDS_IMAGE_NUM+((cur_index+SOUNDS_IMAGE_NUM/2)%(SOUNDS_IMAGE_NUM));
    }
    else
    {
        mid_image = (cur_index+SOUNDS_IMAGE_NUM/2)%SOUNDS_IMAGE_NUM;
    }

    menulist[mid]->set_size(78,78);
    menulist[mid]->set_main_bg_img_src(imagelist.small[mid_image]);
    menulist[mid]->set_pos(point_list[SOUNDS_IMAGE_NUM/2].x+26,point_list[SOUNDS_IMAGE_NUM/2].y+26);

    scroll_flag=-1;
    cur_index--;

    if((cur_index)<0)
    {
        if((cur_index)%SOUNDS_IMAGE_NUM==0)
            new_image=0;
        else
            new_image=SOUNDS_IMAGE_NUM+((cur_index)%(SOUNDS_IMAGE_NUM));
    }
    else
    {
        new_image = (cur_index)%SOUNDS_IMAGE_NUM;
    }
    menulist[cur_tail]->set_main_bg_img_src(imagelist.small[new_image]);

}


void Sounds::switch_cartoon_right(void)
{
    if(scroll_flag!=0)
    {
        return;
    }
    int mid=0,new_image=0;
    char index[32]={0};

    mid=(cur_head+SOUNDS_IMAGE_NUM/2)%(SOUNDS_IMAGE_NUM);

    if((cur_index+SOUNDS_IMAGE_NUM/2)<0)
    {
        if((cur_index+SOUNDS_IMAGE_NUM/2)%SOUNDS_IMAGE_NUM==0)
            mid_image=0;
        else
            mid_image=SOUNDS_IMAGE_NUM+((cur_index+SOUNDS_IMAGE_NUM/2)%(SOUNDS_IMAGE_NUM));
    }
    else
    {
        mid_image = (cur_index+SOUNDS_IMAGE_NUM/2)%SOUNDS_IMAGE_NUM;
    }

    menulist[mid]->set_size(78,78);
    menulist[mid]->set_main_bg_img_src(imagelist.small[mid_image]);
    menulist[mid]->set_pos(point_list[SOUNDS_IMAGE_NUM/2].x+26,point_list[SOUNDS_IMAGE_NUM/2].y+26);

    scroll_flag=1;
    cur_index++;

    if((cur_index+SOUNDS_IMAGE_NUM-1)<0)
    {
        if((cur_index+SOUNDS_IMAGE_NUM-1)%SOUNDS_IMAGE_NUM==0)
            new_image=0;
        else
            new_image=SOUNDS_IMAGE_NUM+((cur_index+SOUNDS_IMAGE_NUM-1)%(SOUNDS_IMAGE_NUM));
    }
    else
    {
        new_image = (cur_index+SOUNDS_IMAGE_NUM-1)%SOUNDS_IMAGE_NUM;
    }
    menulist[cur_head]->set_main_bg_img_src(imagelist.small[new_image]);
}


void Sounds::draw_point(void)
{
    memset(point,0,sizeof(point));
    int X = (int)(sqrt(abs((SOUNDS_LIST_LEN-SOUNDS_LIST_LEN)*(SOUNDS_LIST_LEN-SOUNDS_LIST_LEN))/2));
    int Y = (int)(sqrt(abs((SOUNDS_LIST_LEN-SOUNDS_LIST_LEN)*(SOUNDS_LIST_LEN-SOUNDS_LIST_LEN))/2));
    //LV_LOG_USER("Center of the circle:X=%d,Y=%d",X,Y);
    for(int i=0;i<SOUNDS_LIST_LEN+1;i++)
    {
        point[i].x =X+i;
        point[i].y =Y+SOUNDS_LIST_HIGH/2;
    }

    /*LvcppLine* line = new LvcppLine(cont->myobj);
    line->set_points(point,SOUNDS_LIST_LEN);
    lv_obj_set_style_line_color(line->myobj,lv_color_black(),0);*/

    memset(point_list,0,sizeof(point_list));
    for(int j=0;j< SOUNDS_IMAGE_NUM;j++)
    {
        if(j<SOUNDS_IMAGE_NUM/2)
        {
            point_list[j].x = point[abs(SOUNDS_LIST_LEN/(SOUNDS_IMAGE_NUM-1)*j)].x;
            point_list[j].y =point[abs(SOUNDS_LIST_LEN/(SOUNDS_IMAGE_NUM-1)*j)].y;
        }
        else if(j>SOUNDS_IMAGE_NUM/2)
        {
            point_list[j].x = point[abs(SOUNDS_LIST_LEN/(SOUNDS_IMAGE_NUM-1)*j)].x;
            point_list[j].y =point[abs(SOUNDS_LIST_LEN/(SOUNDS_IMAGE_NUM-1)*j)].y;
        }
        else
        {
            point_list[j].x = point[abs(SOUNDS_LIST_LEN/(SOUNDS_IMAGE_NUM-1)*j)].x-26;
            point_list[j].y =point[abs(SOUNDS_LIST_LEN/(SOUNDS_IMAGE_NUM-1)*j)].y-26;
        }
        scroll_len = (int)(SOUNDS_LIST_LEN/(SOUNDS_IMAGE_NUM-1));

    }

}


void Sounds::lvgl_scroll_anim(void)
{
    cont = new LvcppScreen(m_parent);
    cont->set_style_radius(0,0);
    cont->set_size(SOUNDS_LIST_LEN+(int)(SOUNDS_LIST_LEN/(SOUNDS_IMAGE_NUM-1)), SOUNDS_LIST_HIGH);
    cont->align(LV_ALIGN_CENTER,20,0);
    cont->set_style_bg_color(lv_color_hex(0xff0000),LV_OPA_0,0);
    cont->set_style_clip_corner(true, 0);
    cont->set_scrollbar_mode( LV_SCROLLBAR_MODE_OFF);
    cont->set_style_pad_row(0,0);
    cont->set_style_pad_column(0,0);
    cont->set_style_pad_all(0,0);

    draw_point();

    memset(menulist,0,sizeof(menulist));
    for(int i = 0; i < SOUNDS_IMAGE_NUM; i++) {
        menulist[i] = new LvcppButton(cont->myobj);
        menulist[i]->set_style_pad_all(0,0);
        menulist[i]->set_style_bg_color(lv_color_white(),LV_OPA_0,0);
        if(i==SOUNDS_IMAGE_NUM/2)
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
void Sounds::TimerCB(lv_timer_t * tmr)
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


void Sounds::scroll_anim_exe(int step)
{
    int step_len=(int)(scroll_len/ANIM_STEP);
    int cnt = 0;

    if(scroll_flag==1)
    {
        for(int i = 0; i < SOUNDS_IMAGE_NUM; i++)
        {
            if(i!=cur_head)
            {
                if((i-cur_head)%(SOUNDS_IMAGE_NUM)<0)
                {
                    if((i-cur_head)%SOUNDS_IMAGE_NUM==0)
                        cnt=0;
                    else
                        cnt=SOUNDS_IMAGE_NUM+((i-cur_head)%(SOUNDS_IMAGE_NUM));
                }
                else
                {
                    cnt = (i-cur_head)%(SOUNDS_IMAGE_NUM);
                }
                menulist[i]->set_pos(point[(int)(abs(SOUNDS_LIST_LEN/(SOUNDS_IMAGE_NUM-1)*cnt)-step_len*step)].x,point[(int)(abs(SOUNDS_LIST_LEN/(SOUNDS_IMAGE_NUM-1)*cnt)-step_len*step)].y);
            }
            else
            {
                menulist[i]->set_pos(point[(int)(abs(SOUNDS_LIST_LEN))].x,point[(int)(abs(SOUNDS_LIST_LEN))].y);
            }
        }
    }
    else if(scroll_flag==-1)
    {
        for(int i = 0; i < SOUNDS_IMAGE_NUM; i++)
        {
            if(i!=cur_tail)
            {
                if((i-cur_head)%(SOUNDS_IMAGE_NUM)<0)
                {
                    if((i-cur_head)%SOUNDS_IMAGE_NUM==0)
                        cnt=0;
                    else
                        cnt=SOUNDS_IMAGE_NUM+((i-cur_head)%(SOUNDS_IMAGE_NUM));
                }
                else
                {
                    cnt = (i-cur_head)%(SOUNDS_IMAGE_NUM);
                }
                menulist[i]->set_pos(point[(int)(abs(SOUNDS_LIST_LEN/(SOUNDS_IMAGE_NUM-1)*abs(cnt))+step_len*step)].x,point[(int)(abs(SOUNDS_LIST_LEN/(SOUNDS_IMAGE_NUM-1)*abs(cnt))+step_len*step)].y);
            }
            else
            {
                menulist[i]->set_pos(point[(int)(abs(0))].x,point[(int)(abs(0))].y);
            }
        }
    }
}

void Sounds::imagelist_update(void)
{
    int cnt=0,mid=0;
    if(cur_index<0)
    {
        if(cur_index%SOUNDS_IMAGE_NUM==0)
            cur_head=0;
        else
            cur_head=SOUNDS_IMAGE_NUM+(cur_index%(SOUNDS_IMAGE_NUM));
    }
    else
    {
        cur_head=cur_index%(SOUNDS_IMAGE_NUM);
    }

    mid=(cur_head+SOUNDS_IMAGE_NUM/2)%(SOUNDS_IMAGE_NUM);
    cur_tail=(cur_head+SOUNDS_IMAGE_NUM-1)%(SOUNDS_IMAGE_NUM);
    //LV_LOG_USER("cur_head=%d",cur_head);
    //LV_LOG_USER("cur_tail=%d",cur_tail);

    if((cur_index+SOUNDS_IMAGE_NUM/2)<0)
    {
        if((cur_index+SOUNDS_IMAGE_NUM/2)%SOUNDS_IMAGE_NUM==0)
            mid_image=0;
        else
            mid_image=SOUNDS_IMAGE_NUM+((cur_index+SOUNDS_IMAGE_NUM/2)%(SOUNDS_IMAGE_NUM));
    }
    else
    {
        mid_image = (cur_index+SOUNDS_IMAGE_NUM/2)%SOUNDS_IMAGE_NUM;
    }

    //update list
    for(int i = 0; i < SOUNDS_IMAGE_NUM; i++)
    {
        if((i-cur_head)%(SOUNDS_IMAGE_NUM)<0)
        {
            if((i-cur_head)%SOUNDS_IMAGE_NUM==0)
                cnt=0;
            else
                cnt=SOUNDS_IMAGE_NUM+((i-cur_head)%(SOUNDS_IMAGE_NUM));
        }
        else
        {
            cnt = (i-cur_head)%(SOUNDS_IMAGE_NUM);
        }

        if(i==mid)
        {
            menulist[i]->set_size(130,130);
            menulist[i]->set_pos(point_list[SOUNDS_IMAGE_NUM/2].x,point_list[SOUNDS_IMAGE_NUM/2].y);
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
