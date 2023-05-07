#include "brightness.h"
#include "common/common.h"
#include "math.h"

using namespace LVGLOPTAPI;

void Brightness::ui_image_decode(void)
{
    int index=0;
    LvcppMemory::memset(&imagelist,0,sizeof(brightimage_t));

    bright_lightoff_B_PNG=(void*)parse_image_from_file((char*)SOUNDS_OFF_B_PNG_PATH);
    bright_lightoff_S_PNG=(void*)parse_image_from_file((char*)SOUNDS_OFF_S_PNG_PATH);
    imagelist.big[index]= bright_lightoff_B_PNG;
    imagelist.small[index]= bright_lightoff_S_PNG;
    index++;

    bright_blue_B_PNG=(void*)parse_image_from_file((char*)SOUNDS_BLUE_B_PNG_PATH);
    bright_blue_S_PNG=(void*)parse_image_from_file((char*)SOUNDS_BLUE_S_PNG_PATH);
    imagelist.big[index]= bright_blue_B_PNG;
    imagelist.small[index]= bright_blue_S_PNG;
    index++;

    bright_green_B_PNG=(void*)parse_image_from_file((char*)SOUNDS_GREEN_B_PNG_PATH);
    bright_green_S_PNG=(void*)parse_image_from_file((char*)SOUNDS_GREEN_S_PNG_PATH);
    imagelist.big[index]= bright_green_B_PNG;
    imagelist.small[index]= bright_green_S_PNG;
    index++;

    bright_lemon_B_PNG=(void*)parse_image_from_file((char*)SOUNDS_LEMON_B_PNG_PATH);
    bright_lemon_S_PNG=(void*)parse_image_from_file((char*)SOUNDS_LEMON_S_PNG_PATH);
    imagelist.big[index]= bright_lemon_B_PNG;
    imagelist.small[index]= bright_lemon_S_PNG;
    index++;

    bright_yellow_B_PNG=(void*)parse_image_from_file((char*)SOUNDS_YELLOW_B_PNG_PATH);
    bright_yellow_S_PNG=(void*)parse_image_from_file((char*)SOUNDS_YELLOW_S_PNG_PATH);
    imagelist.big[index]= bright_yellow_B_PNG;
    imagelist.small[index]= bright_yellow_S_PNG;
    index++;

    bright_RGB_B_PNG=(void*)parse_image_from_file((char*)SOUNDS_RGB_B_PNG_PATH);
    bright_RGB_S_PNG=(void*)parse_image_from_file((char*)SOUNDS_RGB_S_PNG_PATH);
    imagelist.big[index]= bright_RGB_B_PNG;
    imagelist.small[index]= bright_RGB_S_PNG;
    index++;

    bright_red_B_PNG=(void*)parse_image_from_file((char*)SOUNDS_RED_B_PNG_PATH);
    bright_red_S_PNG=(void*)parse_image_from_file((char*)SOUNDS_RED_S_PNG_PATH);
    imagelist.big[index]= bright_red_B_PNG;
    imagelist.small[index]= bright_red_S_PNG;
    index++;

    bright_pink_B_PNG=(void*)parse_image_from_file((char*)SOUNDS_PINK_B_PNG_PATH);
    bright_pink_S_PNG=(void*)parse_image_from_file((char*)SOUNDS_PINK_S_PNG_PATH);
    imagelist.big[index]= bright_pink_B_PNG;
    imagelist.small[index]= bright_pink_S_PNG;
    index++;

    bright_purple_B_PNG=(void*)parse_image_from_file((char*)SOUNDS_PURPLE_B_PNG_PATH);
    bright_purple_S_PNG=(void*)parse_image_from_file((char*)SOUNDS_PURPLE_S_PNG_PATH);
    imagelist.big[index]= bright_purple_B_PNG;
    imagelist.small[index]= bright_purple_S_PNG;
    index++;

    bright_orange_B_PNG=(void*)parse_image_from_file((char*)SOUNDS_ORANGE_B_PNG_PATH);
    bright_orange_S_PNG=(void*)parse_image_from_file((char*)SOUNDS_ORANGE_S_PNG_PATH);
    imagelist.big[index]= bright_orange_B_PNG;
    imagelist.small[index]= bright_orange_S_PNG;
    index++;





}

void Brightness::ui_txt_decede(void)
{
    int index=0;
    LvcppMemory::memset(txtlist,0,sizeof(txtlist));

    txtlist[index] = (char *)"Lightoff";
    index++;

    txtlist[index] = (char *)"blue";
    index++;

    txtlist[index] = (char *)"green";
    index++;

    txtlist[index] = (char *)"lemon";
    index++;

    txtlist[index] = (char *)"yellow";
    index++;

    txtlist[index] = (char *)"RGB";
    index++;

    txtlist[index] = (char *)"red";
    index++;

    txtlist[index] = (char *)"pink";
    index++;

    txtlist[index] = (char *)"purple";
    index++;

    txtlist[index] = (char *)"orange";
    index++;

}

void Brightness::ui_image_free(void)
{
    if(bright_lightoff_B_PNG !=NULL)
    {
        free_image(bright_lightoff_B_PNG);
        bright_lightoff_B_PNG =NULL;
    }
    if(bright_lightoff_S_PNG !=NULL)
    {
        free_image(bright_lightoff_S_PNG);
        bright_lightoff_S_PNG =NULL;
    }
    if(bright_blue_B_PNG !=NULL)
    {
        free_image(bright_blue_B_PNG);
        bright_blue_B_PNG =NULL;
    }
    if(bright_blue_S_PNG !=NULL)
    {
        free_image(bright_blue_S_PNG);
        bright_blue_S_PNG =NULL;
    }

    if(bright_green_B_PNG !=NULL)
    {
        free_image(bright_green_B_PNG);
        bright_green_B_PNG =NULL;
    }
    if(bright_green_S_PNG !=NULL)
    {
        free_image(bright_green_S_PNG);
        bright_green_S_PNG =NULL;
    }

    if(bright_lemon_B_PNG !=NULL)
    {
        free_image(bright_lemon_B_PNG);
        bright_lemon_B_PNG =NULL;
    }
    if(bright_lemon_S_PNG !=NULL)
    {
        free_image(bright_lemon_S_PNG);
        bright_lemon_S_PNG =NULL;
    }

    if(bright_orange_B_PNG !=NULL)
    {
        free_image(bright_orange_B_PNG);
        bright_orange_B_PNG =NULL;
    }
    if(bright_orange_S_PNG !=NULL)
    {
        free_image(bright_orange_S_PNG);
        bright_orange_S_PNG =NULL;
    }

    if(bright_pink_B_PNG !=NULL)
    {
        free_image(bright_pink_B_PNG);
        bright_pink_B_PNG =NULL;
    }
    if(bright_pink_S_PNG !=NULL)
    {
        free_image(bright_pink_S_PNG);
        bright_pink_S_PNG =NULL;
    }

    if(bright_purple_B_PNG !=NULL)
    {
        free_image(bright_purple_B_PNG);
        bright_purple_B_PNG =NULL;
    }
    if(bright_red_S_PNG !=NULL)
    {
        free_image(bright_red_S_PNG);
        bright_red_S_PNG =NULL;
    }
    if(bright_red_B_PNG !=NULL)
    {
        free_image(bright_red_B_PNG);
        bright_red_B_PNG =NULL;
    }
    if(bright_RGB_B_PNG !=NULL)
    {
        free_image(bright_RGB_B_PNG);
        bright_RGB_B_PNG =NULL;
    }
    if(bright_RGB_S_PNG !=NULL)
    {
        free_image(bright_RGB_S_PNG);
        bright_RGB_S_PNG =NULL;
    }
    if(bright_yellow_B_PNG !=NULL)
    {
        free_image(bright_yellow_B_PNG);
        bright_yellow_B_PNG =NULL;
    }
    if(bright_yellow_S_PNG !=NULL)
    {
        free_image(bright_yellow_S_PNG);
        bright_yellow_S_PNG =NULL;
    }

    LvcppMemory::memset(imagelist.big,0,sizeof(imagelist.big));
    LvcppMemory::memset(imagelist.small,0,sizeof(imagelist.small));
    LvcppMemory::memset(&imagelist,0,sizeof(brightimage_t));
}

Brightness::Brightness(lv_obj_t* parent)
{
    mscreen = new LvcppScreen(parent);
    mscreen->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    mscreen->set_main_bg_color(lv_color_white(),LV_OPA_100);
    m_parent = mscreen->myobj;
    initial();
}

Brightness::~Brightness()
{
    deinitial();
    ui_image_free();
}

//User starts here
void Brightness::initial(void)
{
    ui_image_decode();
    ui_txt_decede();
    lvgl_scroll_anim();
    current_position = new LvcppLabel(m_parent);
    current_position->set_txt("Brightness");
    current_position->txt_font_size(100,0);
    current_position->align(LV_ALIGN_CENTER,0,-200);
    current_position->set_size(500,200);
    current_position->txt_align(LV_TEXT_ALIGN_CENTER);


    current_function = new LvcppLabel(m_parent);
    current_function->set_txt("RGB");
    current_function->txt_font_size(50,0);
    current_function->set_size(200,100);
    current_function->align(LV_ALIGN_CENTER,0,180);
    current_function->txt_align(LV_TEXT_ALIGN_CENTER);

    maintimer = startTimer(20,this);
}

void Brightness::deinitial(void)
{
    for(int i = 0; i < LIGHT_IMAGE_NUM; i++) {
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



void Brightness::switch_cartoon_left(void)
{
    if(scroll_flag!=0)
    {
        return;
    }
    int mid=0,new_image=0;
    char index[32]={0};

    mid=(cur_head+LIGHT_IMAGE_NUM/2)%(LIGHT_IMAGE_NUM);

    if((cur_index+LIGHT_IMAGE_NUM/2)<0)
    {
        if((cur_index+LIGHT_IMAGE_NUM/2)%LIGHT_IMAGE_NUM==0)
            mid_image=0;
        else
            mid_image=LIGHT_IMAGE_NUM+((cur_index+LIGHT_IMAGE_NUM/2)%(LIGHT_IMAGE_NUM));
    }
    else
    {
        mid_image = (cur_index+LIGHT_IMAGE_NUM/2)%LIGHT_IMAGE_NUM;
    }

    menulist[mid]->set_size(78,78);
    menulist[mid]->set_main_bg_img_src(imagelist.small[mid_image]);
    menulist[mid]->set_pos(point_list[LIGHT_IMAGE_NUM/2].x+26,point_list[LIGHT_IMAGE_NUM/2].y+26);

    scroll_flag=-1;
    cur_index--;

    if((cur_index)<0)
    {
        if((cur_index)%LIGHT_IMAGE_NUM==0)
            new_image=0;
        else
            new_image=LIGHT_IMAGE_NUM+((cur_index)%(LIGHT_IMAGE_NUM));
    }
    else
    {
        new_image = (cur_index)%LIGHT_IMAGE_NUM;
    }
    menulist[cur_tail]->set_main_bg_img_src(imagelist.small[new_image]);

}


void Brightness::switch_cartoon_right(void)
{
    if(scroll_flag!=0)
    {
        return;
    }
    int mid=0,new_image=0;
    char index[32]={0};

    mid=(cur_head+LIGHT_IMAGE_NUM/2)%(LIGHT_IMAGE_NUM);

    if((cur_index+LIGHT_IMAGE_NUM/2)<0)
    {
        if((cur_index+LIGHT_IMAGE_NUM/2)%LIGHT_IMAGE_NUM==0)
            mid_image=0;
        else
            mid_image=LIGHT_IMAGE_NUM+((cur_index+LIGHT_IMAGE_NUM/2)%(LIGHT_IMAGE_NUM));
    }
    else
    {
        mid_image = (cur_index+LIGHT_IMAGE_NUM/2)%LIGHT_IMAGE_NUM;
    }

    menulist[mid]->set_size(78,78);
    menulist[mid]->set_main_bg_img_src(imagelist.small[mid_image]);
    menulist[mid]->set_pos(point_list[LIGHT_IMAGE_NUM/2].x+26,point_list[LIGHT_IMAGE_NUM/2].y+26);

    scroll_flag=1;
    cur_index++;

    if((cur_index+LIGHT_IMAGE_NUM-1)<0)
    {
        if((cur_index+LIGHT_IMAGE_NUM-1)%LIGHT_IMAGE_NUM==0)
            new_image=0;
        else
            new_image=LIGHT_IMAGE_NUM+((cur_index+LIGHT_IMAGE_NUM-1)%(LIGHT_IMAGE_NUM));
    }
    else
    {
        new_image = (cur_index+LIGHT_IMAGE_NUM-1)%LIGHT_IMAGE_NUM;
    }
    menulist[cur_head]->set_main_bg_img_src(imagelist.small[new_image]);
}


void Brightness::draw_point(void)
{
    memset(point,0,sizeof(point));
    int X = (int)(sqrt(abs((LIGHT_LIST_LEN-LIGHT_LIST_LEN)*(LIGHT_LIST_LEN-LIGHT_LIST_LEN))/2));
    int Y = (int)(sqrt(abs((LIGHT_LIST_LEN-LIGHT_LIST_LEN)*(LIGHT_LIST_LEN-LIGHT_LIST_LEN))/2));
    //LV_LOG_USER("Center of the circle:X=%d,Y=%d",X,Y);
    for(int i=0;i<LIGHT_LIST_LEN+1;i++)
    {
        point[i].x =X+i;
        point[i].y =Y+SOUNDS_LIST_HIGH/2;
    }
    /*
    LvcppLine* line = new LvcppLine(cont->myobj);
    line->set_points(point,LIGHT_LIST_LEN);
    lv_obj_set_style_line_color(line->myobj,lv_color_white(),0);
    */
    memset(point_list,0,sizeof(point_list));
    for(int j=0;j< LIGHT_IMAGE_NUM;j++)
    {
        if(j<LIGHT_IMAGE_NUM/2)
        {
            point_list[j].x = point[abs(LIGHT_LIST_LEN/(LIGHT_IMAGE_NUM-1)*j)].x;
            point_list[j].y =point[abs(LIGHT_LIST_LEN/(LIGHT_IMAGE_NUM-1)*j)].y;
        }
        else if(j>LIGHT_IMAGE_NUM/2)
        {
            point_list[j].x = point[abs(LIGHT_LIST_LEN/(LIGHT_IMAGE_NUM-1)*j)].x;
            point_list[j].y =point[abs(LIGHT_LIST_LEN/(LIGHT_IMAGE_NUM-1)*j)].y;
        }
        else
        {
            point_list[j].x = point[abs(LIGHT_LIST_LEN/(LIGHT_IMAGE_NUM-1)*j)].x-26;
            point_list[j].y =point[abs(LIGHT_LIST_LEN/(LIGHT_IMAGE_NUM-1)*j)].y-26;
        }
        scroll_len = (int)(LIGHT_LIST_LEN/(LIGHT_IMAGE_NUM-1));
        //point_list[j].x = //X+(int)(sqrt(LIGHT_LIST_LEN*LIGHT_LIST_LEN-X*X))-(int)(LIGHT_LIST_LEN*cos(PI/180*(90*1.0f/(LIGHT_IMAGE_NUM-1))*j));
        //point_list[j].y = //-Y+(int)(LIGHT_LIST_LEN*sin(PI/180*(90*1.0f/(LIGHT_IMAGE_NUM-1))*j))-60;
        //LV_LOG_USER("x[%d]=%d,y[%d]=%d",j,point_list[j].x,j,point_list[j].y);
    }

}


void Brightness::lvgl_scroll_anim(void)
{
    cont = new LvcppScreen(m_parent);
    cont->set_style_radius(0,0);
    cont->set_size(LIGHT_LIST_LEN+(int)(LIGHT_LIST_LEN/(LIGHT_IMAGE_NUM-1)/2), SOUNDS_LIST_HIGH);
    cont->align(LV_ALIGN_CENTER,-(int)(LIGHT_LIST_LEN/(LIGHT_IMAGE_NUM-1)/2),0);
    cont->set_style_bg_color(lv_color_hex(0xff0000),LV_OPA_0,0);
    cont->set_style_clip_corner(true, 0);
    cont->set_scrollbar_mode( LV_SCROLLBAR_MODE_OFF);
    cont->set_style_pad_row(0,0);
    cont->set_style_pad_column(0,0);
    cont->set_style_pad_all(0,0);

    draw_point();

    memset(menulist,0,sizeof(menulist));
    for(int i = 0; i < LIGHT_IMAGE_NUM; i++) {
        menulist[i] = new LvcppButton(cont->myobj);
        menulist[i]->set_style_pad_all(0,0);
        menulist[i]->set_style_bg_color(lv_color_white(),LV_OPA_0,0);
        if(i==LIGHT_IMAGE_NUM/2)
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
void Brightness::TimerCB(lv_timer_t * tmr)
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


void Brightness::scroll_anim_exe(int step)
{
    int step_len=(int)(scroll_len/ANIM_STEP);
    int cnt = 0;

    if(scroll_flag==1)
    {
        for(int i = 0; i < LIGHT_IMAGE_NUM; i++)
        {
            if(i!=cur_head)
            {
                if((i-cur_head)%(LIGHT_IMAGE_NUM)<0)
                {
                    if((i-cur_head)%LIGHT_IMAGE_NUM==0)
                        cnt=0;
                    else
                        cnt=LIGHT_IMAGE_NUM+((i-cur_head)%(LIGHT_IMAGE_NUM));
                }
                else
                {
                    cnt = (i-cur_head)%(LIGHT_IMAGE_NUM);
                }
                menulist[i]->set_pos(point[(int)(abs(LIGHT_LIST_LEN/(LIGHT_IMAGE_NUM-1)*cnt)-step_len*step)].x,point[(int)(abs(LIGHT_LIST_LEN/(LIGHT_IMAGE_NUM-1)*cnt)-step_len*step)].y);
            }
            else
            {
                menulist[i]->set_pos(point[(int)(abs(LIGHT_LIST_LEN))].x,point[(int)(abs(LIGHT_LIST_LEN))].y);
            }
        }
    }
    else if(scroll_flag==-1)
    {
        for(int i = 0; i < LIGHT_IMAGE_NUM; i++)
        {
            if(i!=cur_tail)
            {
                if((i-cur_head)%(LIGHT_IMAGE_NUM)<0)
                {
                    if((i-cur_head)%LIGHT_IMAGE_NUM==0)
                        cnt=0;
                    else
                        cnt=LIGHT_IMAGE_NUM+((i-cur_head)%(LIGHT_IMAGE_NUM));
                }
                else
                {
                    cnt = (i-cur_head)%(LIGHT_IMAGE_NUM);
                }
                menulist[i]->set_pos(point[(int)(abs(LIGHT_LIST_LEN/(LIGHT_IMAGE_NUM-1)*abs(cnt))+step_len*step)].x,point[(int)(abs(LIGHT_LIST_LEN/(LIGHT_IMAGE_NUM-1)*abs(cnt))+step_len*step)].y);
            }
            else
            {
                menulist[i]->set_pos(point[(int)(abs(0))].x,point[(int)(abs(0))].y);
            }
        }
    }
}

void Brightness::imagelist_update(void)
{
    int cnt=0,mid=0;
    if(cur_index<0)
    {
        if(cur_index%LIGHT_IMAGE_NUM==0)
            cur_head=0;
        else
            cur_head=LIGHT_IMAGE_NUM+(cur_index%(LIGHT_IMAGE_NUM));
    }
    else
    {
        cur_head=cur_index%(LIGHT_IMAGE_NUM);
    }

    mid=(cur_head+LIGHT_IMAGE_NUM/2)%(LIGHT_IMAGE_NUM);
    cur_tail=(cur_head+LIGHT_IMAGE_NUM-1)%(LIGHT_IMAGE_NUM);
    //LV_LOG_USER("cur_head=%d",cur_head);
    //LV_LOG_USER("cur_tail=%d",cur_tail);

    if((cur_index+LIGHT_IMAGE_NUM/2)<0)
    {
        if((cur_index+LIGHT_IMAGE_NUM/2)%LIGHT_IMAGE_NUM==0)
            mid_image=0;
        else
            mid_image=LIGHT_IMAGE_NUM+((cur_index+LIGHT_IMAGE_NUM/2)%(LIGHT_IMAGE_NUM));
    }
    else
    {
        mid_image = (cur_index+LIGHT_IMAGE_NUM/2)%LIGHT_IMAGE_NUM;
    }

    //update list
    for(int i = 0; i < LIGHT_IMAGE_NUM; i++)
    {
        if((i-cur_head)%(LIGHT_IMAGE_NUM)<0)
        {
            if((i-cur_head)%LIGHT_IMAGE_NUM==0)
                cnt=0;
            else
                cnt=LIGHT_IMAGE_NUM+((i-cur_head)%(LIGHT_IMAGE_NUM));
        }
        else
        {
            cnt = (i-cur_head)%(LIGHT_IMAGE_NUM);
        }

        if(i==mid)
        {
            menulist[i]->set_size(130,130);
            menulist[i]->set_pos(point_list[LIGHT_IMAGE_NUM/2].x,point_list[LIGHT_IMAGE_NUM/2].y);
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
