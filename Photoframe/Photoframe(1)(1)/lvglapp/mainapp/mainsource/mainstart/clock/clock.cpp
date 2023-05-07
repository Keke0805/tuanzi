#include  "../mainappstart.h"
#include "clock.h"
#include  "lvgl/src/extra/lv_extra.h"
#include  "mainstart/include/ui_config.h"
#include  "mainstart/include/str_config.h"
static int curClock = 0;

void ClockTime::ui_image_decode(void)
{
#ifdef IMAGE_DECODE
    HEAD_RETURN_PNG=(void*)parse_image_from_file(HEAD_RETURN_PNG_PATH);
    HEAD_RETURN_SEL_PNG=(void*)parse_image_from_file(HEAD_RETURN_SEL_PNG_PATH);
    HEAD_ICON_ClOCK_PNG=(void*)parse_image_from_file(HEAD_ICON_ClOCK_PNG_PATH);
#endif
}
void ClockTime::ui_image_free(void)
{
#ifdef IMAGE_DECODE

	if(HEAD_RETURN_PNG !=NULL)
	{
		free_image(HEAD_RETURN_PNG);
    	HEAD_RETURN_PNG =NULL;
	}
	if(HEAD_RETURN_SEL_PNG !=NULL)
	{
		free_image(HEAD_RETURN_SEL_PNG);
    	HEAD_RETURN_SEL_PNG =NULL;
	}
	if(HEAD_ICON_ClOCK_PNG !=NULL)
	{
		free_image(HEAD_ICON_ClOCK_PNG);
    	HEAD_ICON_ClOCK_PNG =NULL;
	}
	
	if(CLOCK_CLOCK0_PNG !=NULL)
	{
		free_image(CLOCK_CLOCK0_PNG);
    	CLOCK_CLOCK0_PNG =NULL;
	}
	if(CLOCK_CLOCK1_PNG !=NULL)
	{
		free_image(CLOCK_CLOCK1_PNG);
    	CLOCK_CLOCK1_PNG =NULL;
	}
	if(CLOCK_CLOCK2_PNG !=NULL)
	{
		free_image(CLOCK_CLOCK2_PNG);
    	CLOCK_CLOCK2_PNG =NULL;
	}
	if(CLOCK_CLOCK3_PNG !=NULL)
	{
		free_image(CLOCK_CLOCK3_PNG);
    	CLOCK_CLOCK3_PNG =NULL;
	}
	if(CLOCK_CLOCK4_PNG !=NULL)
	{
		free_image(CLOCK_CLOCK4_PNG);
    	CLOCK_CLOCK4_PNG =NULL;
	}
	if(CLOCK_CLOCK5_PNG !=NULL)
	{
		free_image(CLOCK_CLOCK5_PNG);
    	CLOCK_CLOCK5_PNG =NULL;
	}
	if(CLOCK_CLOCK6_PNG !=NULL)
	{
		free_image(CLOCK_CLOCK6_PNG);
    	CLOCK_CLOCK6_PNG =NULL;
	}
	if(CLOCK_CLOCK7_PNG !=NULL)
	{
		free_image(CLOCK_CLOCK7_PNG);
    	CLOCK_CLOCK7_PNG =NULL;
	}
	if(CLOCK_CLOCK8_PNG !=NULL)
	{
		free_image(CLOCK_CLOCK8_PNG);
    	CLOCK_CLOCK8_PNG =NULL;
	}
	if(CLOCK_SCENE0_PNG !=NULL)
	{
		free_image(CLOCK_SCENE0_PNG);
    	CLOCK_SCENE0_PNG =NULL;
	}
	if(CLOCK_SCENE1_PNG !=NULL)
	{
		free_image(CLOCK_SCENE1_PNG);
    	CLOCK_SCENE1_PNG =NULL;
	}
	if(CLOCK_SCENE2_PNG !=NULL)
	{
		free_image(CLOCK_SCENE2_PNG);
    	CLOCK_SCENE2_PNG =NULL;
	}
	if(CLOCK_SCENE3_PNG !=NULL)
	{
		free_image(CLOCK_SCENE3_PNG);
    	CLOCK_SCENE3_PNG =NULL;
	}
	if(CLOCK_SCENE4_PNG !=NULL)
	{
		free_image(CLOCK_SCENE4_PNG);
    	CLOCK_SCENE4_PNG =NULL;
	}
	if(CLOCK_SCENE5_PNG !=NULL)
	{
		free_image(CLOCK_SCENE5_PNG);
    	CLOCK_SCENE5_PNG =NULL;
	}
	if(CLOCK_SCENE6_PNG !=NULL)
	{
		free_image(CLOCK_SCENE6_PNG);
    	CLOCK_SCENE6_PNG =NULL;
	}
	if(CLOCK_SCENE7_PNG !=NULL)
	{
		free_image(CLOCK_SCENE7_PNG);
    	CLOCK_SCENE7_PNG =NULL;
	}
	if(CLOCK_SCENE8_PNG !=NULL)
	{
		free_image(CLOCK_SCENE8_PNG);
    	CLOCK_SCENE8_PNG =NULL;
	}
	if(CLOCK_HOURS1_PNG !=NULL)
	{
		free_image(CLOCK_HOURS1_PNG);
    	CLOCK_HOURS1_PNG =NULL;
	}
	if(CLOCK_HOURS2_PNG !=NULL)
	{
		free_image(CLOCK_HOURS2_PNG);
    	CLOCK_HOURS2_PNG =NULL;
	}
	if(CLOCK_HOURS3_PNG !=NULL)
	{
		free_image(CLOCK_HOURS3_PNG);
    	CLOCK_HOURS3_PNG =NULL;
	}
	if(CLOCK_HOURS4_PNG !=NULL)
	{
		free_image(CLOCK_HOURS4_PNG);
    	CLOCK_HOURS4_PNG =NULL;
	}
	if(CLOCK_HOURS5_PNG !=NULL)
	{
		free_image(CLOCK_HOURS5_PNG);
    	CLOCK_HOURS5_PNG =NULL;
	}
	if(CLOCK_HOURS6_PNG !=NULL)
	{
		free_image(CLOCK_HOURS6_PNG);
    	CLOCK_HOURS6_PNG =NULL;
	}
	if(CLOCK_HOURS7_PNG !=NULL)
	{
		free_image(CLOCK_HOURS7_PNG);
    	CLOCK_HOURS7_PNG =NULL;
	}
	if(CLOCK_HOURS8_PNG !=NULL)
	{
		free_image(CLOCK_HOURS8_PNG);
    	CLOCK_HOURS8_PNG =NULL;
	}
	if(CLOCK_MINUTE1_PNG !=NULL)
	{
		free_image(CLOCK_MINUTE1_PNG);
    	CLOCK_MINUTE1_PNG =NULL;
	}
	if(CLOCK_MINUTE2_PNG !=NULL)
	{
		free_image(CLOCK_MINUTE2_PNG);
    	CLOCK_MINUTE2_PNG =NULL;
	}
	if(CLOCK_MINUTE3_PNG !=NULL)
	{
		free_image(CLOCK_MINUTE3_PNG);
    	CLOCK_MINUTE3_PNG =NULL;
	}
	if(CLOCK_MINUTE4_PNG !=NULL)
	{
		free_image(CLOCK_MINUTE4_PNG);
    	CLOCK_MINUTE4_PNG =NULL;
	}
	if(CLOCK_MINUTE5_PNG !=NULL)
	{
		free_image(CLOCK_MINUTE5_PNG);
    	CLOCK_MINUTE5_PNG =NULL;
	}
	if(CLOCK_MINUTE6_PNG !=NULL)
	{
		free_image(CLOCK_MINUTE6_PNG);
    	CLOCK_MINUTE6_PNG =NULL;
	}
	if(CLOCK_MINUTE7_PNG !=NULL)
	{
		free_image(CLOCK_MINUTE7_PNG);
    	CLOCK_MINUTE7_PNG =NULL;
	}
	if(CLOCK_MINUTE8_PNG !=NULL)
	{
		free_image(CLOCK_MINUTE8_PNG);
    	CLOCK_MINUTE8_PNG =NULL;
	}
	if(CLOCK_SECOND1_PNG !=NULL)
	{
		free_image(CLOCK_SECOND1_PNG);
    	CLOCK_SECOND1_PNG =NULL;
	}
	if(CLOCK_SECOND2_PNG !=NULL)
	{
		free_image(CLOCK_SECOND2_PNG);
    	CLOCK_SECOND2_PNG =NULL;
	}
	if(CLOCK_SECOND3_PNG !=NULL)
	{
		free_image(CLOCK_SECOND3_PNG);
    	CLOCK_SECOND3_PNG =NULL;
	}
	if(CLOCK_SECOND4_PNG !=NULL)
	{
		free_image(CLOCK_SECOND4_PNG);
    	CLOCK_SECOND4_PNG =NULL;
	}
	if(CLOCK_SECOND5_PNG !=NULL)
	{
		free_image(CLOCK_SECOND5_PNG);
    	CLOCK_SECOND5_PNG =NULL;
	}
	if(CLOCK_SECOND6_PNG !=NULL)
	{
		free_image(CLOCK_SECOND6_PNG);
    	CLOCK_SECOND6_PNG =NULL;
	}
	if(CLOCK_SECOND7_PNG !=NULL)
	{
		free_image(CLOCK_SECOND7_PNG);
    	CLOCK_SECOND7_PNG =NULL;
	}
	if(CLOCK_SECOND8_PNG !=NULL)
	{
		free_image(CLOCK_SECOND8_PNG);
    	CLOCK_SECOND8_PNG =NULL;
	}
	if(CLOCK_DOT1_PNG !=NULL)
	{
		free_image(CLOCK_DOT1_PNG);
    	CLOCK_DOT1_PNG =NULL;
	}
	if(CLOCK_DOT2_PNG !=NULL)
	{
		free_image(CLOCK_DOT2_PNG);
    	CLOCK_DOT2_PNG =NULL;
	}
	if(CLOCK_DOT3_PNG !=NULL)
	{
		free_image(CLOCK_DOT3_PNG);
    	CLOCK_DOT3_PNG =NULL;
	}
	if(CLOCK_DOT4_PNG !=NULL)
	{
		free_image(CLOCK_DOT4_PNG);
    	CLOCK_DOT4_PNG =NULL;
	}
	if(CLOCK_DOT5_PNG !=NULL)
	{
		free_image(CLOCK_DOT5_PNG);
    	CLOCK_DOT5_PNG =NULL;
	}
	if(CLOCK_DOT6_PNG !=NULL)
	{
		free_image(CLOCK_DOT6_PNG);
		CLOCK_DOT6_PNG =NULL;
	}
	if(CLOCK_DOT7_PNG !=NULL)
	{
    	free_image(CLOCK_DOT7_PNG);
		CLOCK_DOT7_PNG =NULL;
	}
	if(CLOCK_DOT8_PNG !=NULL)
	{
	    free_image(CLOCK_DOT8_PNG);
		CLOCK_DOT8_PNG =NULL;
	}
#endif
}
void ClockTime::ui_image_decode_scene(int curScene)
{
	switch(curScene) 
	{
        case 0:
			if(CLOCK_SCENE0_PNG ==NULL)
            	CLOCK_SCENE0_PNG=(void*)parse_image_from_file(CLOCK_SCENE0_PNG_PATH);
            break;
        case 1:
			if(CLOCK_SCENE1_PNG ==NULL)
            	CLOCK_SCENE1_PNG=(void*)parse_image_from_file(CLOCK_SCENE1_PNG_PATH);
            if(CLOCK_HOURS1_PNG ==NULL)
				CLOCK_HOURS1_PNG=(void*)parse_image_from_file(CLOCK_HOURS1_PNG_PATH);
            if(CLOCK_MINUTE1_PNG ==NULL)
				CLOCK_MINUTE1_PNG=(void*)parse_image_from_file(CLOCK_MINUTE1_PNG_PATH);
            if(CLOCK_SECOND1_PNG ==NULL)
				CLOCK_SECOND1_PNG=(void*)parse_image_from_file(CLOCK_SECOND1_PNG_PATH);
            if(CLOCK_DOT1_PNG ==NULL)
				CLOCK_DOT1_PNG=(void*)parse_image_from_file(CLOCK_DOT1_PNG_PATH);
            break;
        case 2:
            if(CLOCK_SCENE2_PNG ==NULL)
				CLOCK_SCENE2_PNG=(void*)parse_image_from_file(CLOCK_SCENE2_PNG_PATH);
            if(CLOCK_HOURS2_PNG ==NULL)
				CLOCK_HOURS2_PNG=(void*)parse_image_from_file(CLOCK_HOURS2_PNG_PATH);
            if(CLOCK_MINUTE2_PNG ==NULL)
				CLOCK_MINUTE2_PNG=(void*)parse_image_from_file(CLOCK_MINUTE2_PNG_PATH);
            if(CLOCK_SECOND2_PNG ==NULL)
				CLOCK_SECOND2_PNG=(void*)parse_image_from_file(CLOCK_SECOND2_PNG_PATH);
            if(CLOCK_DOT2_PNG ==NULL)
				CLOCK_DOT2_PNG=(void*)parse_image_from_file(CLOCK_DOT2_PNG_PATH);
            break;
        case 3:
            if(CLOCK_SCENE3_PNG ==NULL)
				CLOCK_SCENE3_PNG=(void*)parse_image_from_file(CLOCK_SCENE3_PNG_PATH);
            if(CLOCK_HOURS3_PNG ==NULL)
				CLOCK_HOURS3_PNG=(void*)parse_image_from_file(CLOCK_HOURS3_PNG_PATH);
            if(CLOCK_MINUTE3_PNG ==NULL)
				CLOCK_MINUTE3_PNG=(void*)parse_image_from_file(CLOCK_MINUTE3_PNG_PATH);
            if(CLOCK_SECOND3_PNG ==NULL)
				CLOCK_SECOND3_PNG=(void*)parse_image_from_file(CLOCK_SECOND3_PNG_PATH);
            if(CLOCK_DOT3_PNG ==NULL)
				CLOCK_DOT3_PNG=(void*)parse_image_from_file(CLOCK_DOT3_PNG_PATH);
            break;
        case 4:
            if(CLOCK_SCENE4_PNG ==NULL)
				CLOCK_SCENE4_PNG=(void*)parse_image_from_file(CLOCK_SCENE4_PNG_PATH);
            if(CLOCK_HOURS4_PNG ==NULL)
				CLOCK_HOURS4_PNG=(void*)parse_image_from_file(CLOCK_HOURS4_PNG_PATH);
            if(CLOCK_MINUTE4_PNG ==NULL)
				CLOCK_MINUTE4_PNG=(void*)parse_image_from_file(CLOCK_MINUTE4_PNG_PATH);
            if(CLOCK_SECOND4_PNG ==NULL)
				CLOCK_SECOND4_PNG=(void*)parse_image_from_file(CLOCK_SECOND4_PNG_PATH);
            if(CLOCK_DOT4_PNG ==NULL)
				CLOCK_DOT4_PNG=(void*)parse_image_from_file(CLOCK_DOT4_PNG_PATH);
            break;
        case 5:
            if(CLOCK_SCENE5_PNG ==NULL)
				CLOCK_SCENE5_PNG=(void*)parse_image_from_file(CLOCK_SCENE5_PNG_PATH);
            if(CLOCK_HOURS5_PNG ==NULL)
				CLOCK_HOURS5_PNG=(void*)parse_image_from_file(CLOCK_HOURS5_PNG_PATH);
            if(CLOCK_MINUTE5_PNG ==NULL)
				CLOCK_MINUTE5_PNG=(void*)parse_image_from_file(CLOCK_MINUTE5_PNG_PATH);
            if(CLOCK_SECOND5_PNG ==NULL)
				CLOCK_SECOND5_PNG=(void*)parse_image_from_file(CLOCK_SECOND5_PNG_PATH);
            if(CLOCK_DOT5_PNG ==NULL)
				CLOCK_DOT5_PNG=(void*)parse_image_from_file(CLOCK_DOT5_PNG_PATH);
            break;
        case 6:
			if(CLOCK_SCENE6_PNG ==NULL)
				CLOCK_SCENE6_PNG=(void*)parse_image_from_file(CLOCK_SCENE6_PNG_PATH);
            if(CLOCK_HOURS6_PNG ==NULL)
				CLOCK_HOURS6_PNG=(void*)parse_image_from_file(CLOCK_HOURS6_PNG_PATH);
            if(CLOCK_MINUTE6_PNG ==NULL)
				CLOCK_MINUTE6_PNG=(void*)parse_image_from_file(CLOCK_MINUTE6_PNG_PATH);
            if(CLOCK_SECOND6_PNG ==NULL)
				CLOCK_SECOND6_PNG=(void*)parse_image_from_file(CLOCK_SECOND6_PNG_PATH);
            if(CLOCK_DOT6_PNG ==NULL)
				CLOCK_DOT6_PNG=(void*)parse_image_from_file(CLOCK_DOT6_PNG_PATH);
            break;
        case 7:
            if(CLOCK_SCENE7_PNG ==NULL)
				CLOCK_SCENE7_PNG=(void*)parse_image_from_file(CLOCK_SCENE7_PNG_PATH);
            if(CLOCK_HOURS7_PNG ==NULL)
				CLOCK_HOURS7_PNG=(void*)parse_image_from_file(CLOCK_HOURS7_PNG_PATH);
            if(CLOCK_MINUTE7_PNG ==NULL)
				CLOCK_MINUTE7_PNG=(void*)parse_image_from_file(CLOCK_MINUTE7_PNG_PATH);
            if(CLOCK_SECOND7_PNG ==NULL)
				CLOCK_SECOND7_PNG=(void*)parse_image_from_file(CLOCK_SECOND7_PNG_PATH);
            if(CLOCK_DOT7_PNG ==NULL)
				CLOCK_DOT7_PNG=(void*)parse_image_from_file(CLOCK_DOT7_PNG_PATH);
            break;
        case 8:
            if(CLOCK_SCENE8_PNG ==NULL)
				CLOCK_SCENE8_PNG=(void*)parse_image_from_file(CLOCK_SCENE8_PNG_PATH);
            if(CLOCK_HOURS8_PNG ==NULL)
				CLOCK_HOURS8_PNG=(void*)parse_image_from_file(CLOCK_HOURS8_PNG_PATH);
            if(CLOCK_MINUTE8_PNG ==NULL)
				CLOCK_MINUTE8_PNG=(void*)parse_image_from_file(CLOCK_MINUTE8_PNG_PATH);
            if(CLOCK_SECOND8_PNG ==NULL)
				CLOCK_SECOND8_PNG=(void*)parse_image_from_file(CLOCK_SECOND8_PNG_PATH);
            if(CLOCK_DOT8_PNG ==NULL)
				CLOCK_DOT8_PNG=(void*)parse_image_from_file(CLOCK_DOT8_PNG_PATH);
            break;
        default:
			break;
	}
}
void ClockTime::ui_image_free_scene(int curScene)
{
	switch(curScene)
	{
        case 0:
			if(CLOCK_SCENE0_PNG !=NULL)
			{
				free_image(CLOCK_SCENE0_PNG);
				CLOCK_SCENE0_PNG =NULL;
			}
            break;
        case 1:
			if(CLOCK_SCENE1_PNG !=NULL)
			{
				free_image(CLOCK_SCENE1_PNG);
				CLOCK_SCENE1_PNG =NULL;
			}            
			if(CLOCK_HOURS1_PNG !=NULL)
			{
				free_image(CLOCK_HOURS1_PNG);
				CLOCK_HOURS1_PNG =NULL;
			}            
			if(CLOCK_MINUTE1_PNG !=NULL)
			{
				free_image(CLOCK_MINUTE1_PNG);
				CLOCK_MINUTE1_PNG =NULL;
			}            
			if(CLOCK_SECOND1_PNG !=NULL)
			{
				free_image(CLOCK_SECOND1_PNG);
				CLOCK_SECOND1_PNG =NULL;
			}            
			if(CLOCK_DOT1_PNG !=NULL)
			{
				free_image(CLOCK_DOT1_PNG);
				CLOCK_DOT1_PNG =NULL;
			}
			break;
        case 2:
			if(CLOCK_SCENE2_PNG !=NULL)
			{
				free_image(CLOCK_SCENE2_PNG);
				CLOCK_SCENE2_PNG =NULL;
			}            
			if(CLOCK_HOURS2_PNG !=NULL)
			{
				free_image(CLOCK_HOURS2_PNG);
				CLOCK_HOURS2_PNG =NULL;
			}            
			if(CLOCK_MINUTE2_PNG !=NULL)
			{
				free_image(CLOCK_MINUTE2_PNG);
				CLOCK_MINUTE2_PNG =NULL;
			}            
			if(CLOCK_SECOND2_PNG !=NULL)
			{
				free_image(CLOCK_SECOND2_PNG);
				CLOCK_SECOND2_PNG =NULL;
			}            
			if(CLOCK_DOT2_PNG !=NULL)
			{
				free_image(CLOCK_DOT2_PNG);
				CLOCK_DOT2_PNG =NULL;
			}            
			break;
        case 3:
			if(CLOCK_SCENE3_PNG !=NULL)
			{
				free_image(CLOCK_SCENE3_PNG);
				CLOCK_SCENE3_PNG =NULL;
			}            
			if(CLOCK_HOURS3_PNG !=NULL)
			{
				free_image(CLOCK_HOURS3_PNG);
				CLOCK_HOURS3_PNG =NULL;
			}            
			if(CLOCK_MINUTE3_PNG !=NULL)
			{
				free_image(CLOCK_MINUTE3_PNG);
				CLOCK_MINUTE3_PNG =NULL;
			}            
			if(CLOCK_SECOND3_PNG !=NULL)
			{
				free_image(CLOCK_SECOND3_PNG);
				CLOCK_SECOND3_PNG =NULL;
			}            
			if(CLOCK_DOT3_PNG !=NULL)
			{
				free_image(CLOCK_DOT3_PNG);
				CLOCK_DOT3_PNG =NULL;
			}            
			break;
        case 4:
			if(CLOCK_SCENE4_PNG !=NULL)
			{
				free_image(CLOCK_SCENE4_PNG);
				CLOCK_SCENE4_PNG =NULL;
			}            
			if(CLOCK_HOURS4_PNG !=NULL)
			{
				free_image(CLOCK_HOURS4_PNG);
				CLOCK_HOURS4_PNG =NULL;
			}            
			if(CLOCK_MINUTE4_PNG !=NULL)
			{
				free_image(CLOCK_MINUTE4_PNG);
				CLOCK_MINUTE4_PNG =NULL;
			}            
			if(CLOCK_SECOND4_PNG !=NULL)
			{
				free_image(CLOCK_SECOND4_PNG);
				CLOCK_SECOND4_PNG =NULL;
			}            
			if(CLOCK_DOT4_PNG !=NULL)
			{
				free_image(CLOCK_DOT4_PNG);
				CLOCK_DOT4_PNG =NULL;
			}            
			break;
        case 5:
			if(CLOCK_SCENE5_PNG !=NULL)
			{
				free_image(CLOCK_SCENE5_PNG);
				CLOCK_SCENE5_PNG =NULL;
			}            
			if(CLOCK_HOURS5_PNG !=NULL)
			{
				free_image(CLOCK_HOURS5_PNG);
				CLOCK_HOURS5_PNG =NULL;
			}            
			if(CLOCK_MINUTE5_PNG !=NULL)
			{
				free_image(CLOCK_MINUTE5_PNG);
				CLOCK_MINUTE5_PNG =NULL;
			}            
			if(CLOCK_SECOND5_PNG !=NULL)
			{
				free_image(CLOCK_SECOND5_PNG);
				CLOCK_SECOND5_PNG =NULL;
			}            
			if(CLOCK_DOT5_PNG !=NULL)
			{
				free_image(CLOCK_DOT5_PNG);
				CLOCK_DOT5_PNG =NULL;
			}            
			break;
        case 6:
			if(CLOCK_SCENE6_PNG !=NULL)
			{
				free_image(CLOCK_SCENE6_PNG);
				CLOCK_SCENE6_PNG =NULL;
			}            
			if(CLOCK_HOURS6_PNG !=NULL)
			{
				free_image(CLOCK_HOURS6_PNG);
				CLOCK_HOURS6_PNG =NULL;
			}            
			if(CLOCK_MINUTE6_PNG !=NULL)
			{
				free_image(CLOCK_MINUTE6_PNG);
				CLOCK_MINUTE6_PNG =NULL;
			}            
			if(CLOCK_SECOND6_PNG !=NULL)
			{
				free_image(CLOCK_SECOND6_PNG);
				CLOCK_SECOND6_PNG =NULL;
			}            
			if(CLOCK_DOT6_PNG !=NULL)
			{
				free_image(CLOCK_DOT6_PNG);
				CLOCK_DOT6_PNG =NULL;
			}            
			break;
        case 7:
			if(CLOCK_SCENE7_PNG !=NULL)
			{
				free_image(CLOCK_SCENE7_PNG);
				CLOCK_SCENE7_PNG =NULL;
			}            
			if(CLOCK_HOURS7_PNG !=NULL)
			{
				free_image(CLOCK_HOURS7_PNG);
				CLOCK_HOURS7_PNG =NULL;
			}            
			if(CLOCK_MINUTE7_PNG !=NULL)
			{
				free_image(CLOCK_MINUTE7_PNG);
				CLOCK_MINUTE7_PNG =NULL;
			}            
			if(CLOCK_SECOND7_PNG !=NULL)
			{
				free_image(CLOCK_SECOND7_PNG);
				CLOCK_SECOND7_PNG =NULL;
			}            
			if(CLOCK_DOT7_PNG !=NULL)
			{
				free_image(CLOCK_DOT7_PNG);
				CLOCK_DOT7_PNG =NULL;
			}            
			break;
        case 8:
			if(CLOCK_SCENE8_PNG !=NULL)
			{
				free_image(CLOCK_SCENE8_PNG);
				CLOCK_SCENE8_PNG =NULL;
			}            
			if(CLOCK_HOURS8_PNG !=NULL)
			{
				free_image(CLOCK_HOURS8_PNG);
				CLOCK_HOURS8_PNG =NULL;
			}            
			if(CLOCK_MINUTE8_PNG !=NULL)
			{
				free_image(CLOCK_MINUTE8_PNG);
				CLOCK_MINUTE8_PNG =NULL;
			}            
			if(CLOCK_SECOND8_PNG !=NULL)
			{
				free_image(CLOCK_SECOND8_PNG);
				CLOCK_SECOND8_PNG =NULL;
			}            
			if(CLOCK_DOT8_PNG !=NULL)
			{
				free_image(CLOCK_DOT8_PNG);
				CLOCK_DOT8_PNG =NULL;
			}           
			break;
        default:
			break;
	}
}
void ClockTime::ui_image_decode_list(void)
{
	if(CLOCK_CLOCK0_PNG ==NULL)
		CLOCK_CLOCK0_PNG=(void*)parse_image_from_file(CLOCK_CLOCK0_PNG_PATH);
	if(CLOCK_CLOCK1_PNG ==NULL)
		CLOCK_CLOCK1_PNG=(void*)parse_image_from_file(CLOCK_CLOCK1_PNG_PATH);
	if(CLOCK_CLOCK2_PNG ==NULL)
		CLOCK_CLOCK2_PNG=(void*)parse_image_from_file(CLOCK_CLOCK2_PNG_PATH);
	if(CLOCK_CLOCK3_PNG ==NULL)
		CLOCK_CLOCK3_PNG=(void*)parse_image_from_file(CLOCK_CLOCK3_PNG_PATH);
	if(CLOCK_CLOCK4_PNG ==NULL)
		CLOCK_CLOCK4_PNG=(void*)parse_image_from_file(CLOCK_CLOCK4_PNG_PATH);
	if(CLOCK_CLOCK5_PNG ==NULL)
		CLOCK_CLOCK5_PNG=(void*)parse_image_from_file(CLOCK_CLOCK5_PNG_PATH);
	if(CLOCK_CLOCK6_PNG ==NULL)
		CLOCK_CLOCK6_PNG=(void*)parse_image_from_file(CLOCK_CLOCK6_PNG_PATH);
	if(CLOCK_CLOCK7_PNG ==NULL)
		CLOCK_CLOCK7_PNG=(void*)parse_image_from_file(CLOCK_CLOCK7_PNG_PATH);
	if(CLOCK_CLOCK8_PNG ==NULL)
		CLOCK_CLOCK8_PNG=(void*)parse_image_from_file(CLOCK_CLOCK8_PNG_PATH);

}
void ClockTime::ui_image_free_list(void)
{
	if(CLOCK_CLOCK0_PNG !=NULL)
	{
		free_image(CLOCK_CLOCK0_PNG);
		CLOCK_CLOCK0_PNG =NULL;
	} 
	if(CLOCK_CLOCK1_PNG !=NULL)
	{
		free_image(CLOCK_CLOCK1_PNG);
		CLOCK_CLOCK1_PNG =NULL;
	}
	if(CLOCK_CLOCK2_PNG !=NULL)
	{
		free_image(CLOCK_CLOCK2_PNG);
		CLOCK_CLOCK2_PNG =NULL;
	}
	if(CLOCK_CLOCK3_PNG !=NULL)
	{
		free_image(CLOCK_CLOCK3_PNG);
		CLOCK_CLOCK3_PNG =NULL;
	}
	if(CLOCK_CLOCK4_PNG !=NULL)
	{
		free_image(CLOCK_CLOCK4_PNG);
		CLOCK_CLOCK4_PNG =NULL;
	}
	if(CLOCK_CLOCK5_PNG !=NULL)
	{
		free_image(CLOCK_CLOCK5_PNG);
		CLOCK_CLOCK5_PNG =NULL;
	}
	if(CLOCK_CLOCK6_PNG !=NULL)
	{
		free_image(CLOCK_CLOCK6_PNG);
		CLOCK_CLOCK6_PNG =NULL;
	}
	if(CLOCK_CLOCK7_PNG !=NULL)
	{
		free_image(CLOCK_CLOCK7_PNG);
		CLOCK_CLOCK7_PNG =NULL;
	}
	if(CLOCK_CLOCK8_PNG !=NULL)
	{
		free_image(CLOCK_CLOCK8_PNG);
		CLOCK_CLOCK8_PNG =NULL;
	}
}
void ClockTime::set_image_scene(int curScene)
{
	if(ClockScene == NULL)
		return;
#ifdef IMAGE_DECODE
	void *scenePatch[8]={CLOCK_SCENE1_PNG,CLOCK_SCENE2_PNG,CLOCK_SCENE3_PNG,CLOCK_SCENE4_PNG,
	                            CLOCK_SCENE5_PNG,CLOCK_SCENE6_PNG,CLOCK_SCENE7_PNG,CLOCK_SCENE8_PNG};
	void *hoursPatch[8]={CLOCK_HOURS1_PNG,CLOCK_HOURS2_PNG,CLOCK_HOURS3_PNG,CLOCK_HOURS4_PNG,
	                            CLOCK_HOURS5_PNG,CLOCK_HOURS6_PNG,CLOCK_HOURS7_PNG,CLOCK_HOURS8_PNG};
	void *minutePatch[8]={CLOCK_MINUTE1_PNG,CLOCK_MINUTE2_PNG,CLOCK_MINUTE3_PNG,CLOCK_MINUTE4_PNG,
	                            CLOCK_MINUTE5_PNG,CLOCK_MINUTE6_PNG,CLOCK_MINUTE7_PNG,CLOCK_MINUTE8_PNG};
	void *secondPatch[8]={CLOCK_SECOND1_PNG,CLOCK_SECOND2_PNG,CLOCK_SECOND3_PNG,CLOCK_SECOND4_PNG,
	                            CLOCK_SECOND5_PNG,CLOCK_SECOND6_PNG,CLOCK_SECOND7_PNG,CLOCK_SECOND8_PNG};
	void *dotPatch[8]={CLOCK_DOT1_PNG,CLOCK_DOT2_PNG,CLOCK_DOT3_PNG,CLOCK_DOT4_PNG,
	                            CLOCK_DOT5_PNG,CLOCK_DOT6_PNG,CLOCK_DOT7_PNG,CLOCK_DOT8_PNG};
#endif
	if(curScene ==0)	
	{
		if((timeList_item !=NULL)&&(timeList_item->plateImage !=NULL))
		{
			timeList_item->plateImage->set_main_bg_img_src(CLOCK_SCENE0_PNG);
		}
	}
	else if(curScene <CLOCK_LIST_MAX)
	{
		if((clockScene_id.list_item[curScene-1] !=NULL)&&(clockScene_id.list_item[curScene-1]->plateImage !=NULL))
		{
			clockScene_id.list_item[curScene-1]->plateImage->set_main_bg_img_src(scenePatch[curScene-1]);
		}
		if((clockScene_id.list_item[curScene-1] !=NULL)&&(clockScene_id.list_item[curScene-1]->hoursImage !=NULL))
		{
			clockScene_id.list_item[curScene-1]->hoursImage->set_src(hoursPatch[curScene-1]);
		}
		if((clockScene_id.list_item[curScene-1] !=NULL)&&(clockScene_id.list_item[curScene-1]->minuteImage !=NULL))
		{
			clockScene_id.list_item[curScene-1]->minuteImage->set_src(minutePatch[curScene-1]);
		}
		if((clockScene_id.list_item[curScene-1] !=NULL)&&(clockScene_id.list_item[curScene-1]->secondImage !=NULL))
		{
			clockScene_id.list_item[curScene-1]->secondImage->set_src(secondPatch[curScene-1]);
		}
		if((clockScene_id.list_item[curScene-1] !=NULL)&&(clockScene_id.list_item[curScene-1]->dotImage !=NULL))
		{
			clockScene_id.list_item[curScene-1]->dotImage->set_src(dotPatch[curScene-1]);
		}
	}
}
ClockTime::ClockTime(lv_obj_t* parent)
{
	read_int_type_param(PUBLIC_SCENE, CLOCKTYPE, &curClock);
	LV_LOG_USER("curClock:%d",curClock);
    ui_image_decode();
	ui_image_decode_scene(curClock);
    frame = new LvcppScreen(parent);
    frame->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    frame->set_main_bg_color(lv_color_black(),LV_OPA_100);
    mainscreen = frame->myobj;
}

void ClockTime::main_event_handler(lv_event_t *event)
{
    int curUser =CLOCK_LIST_MAX;
    ClockTime* opt = (ClockTime*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
    lv_obj_t* cont = lv_event_get_current_target(event);

    if(cont != target)
    {
        curUser = (uintptr_t)cont->user_data;
    }
    else
    {
       curUser =(uintptr_t)target->user_data;
    }
    switch(event->code)
    {
    	case LV_EVENT_PRESSED:
			opt->clockList_down =true;
			break;
        case LV_EVENT_RELEASED:
            opt->timecntback =0;
			if(opt->clockList_down)
			{
				opt->clockList_down =false;
	            if((curUser < CLOCK_LIST_MAX)&&(curUser >=0))
	            {
	                curClock =curUser;
	                if(opt->buttonReturn !=NULL)
	                {
	                    opt->buttonReturn->show(false);
	                }
	                if(opt->headIcon !=NULL)
	                {
	                    opt->headIcon->show(false);
	                }
	                if(opt->clockIcon !=NULL)
	                {
	                    opt->clockIcon->show(false);
	                }
					if(opt->ClockList !=NULL)
	                {
	                    opt->clocktime_clockList_delete();
	                }
	                if(opt->ClockScene ==NULL)
	                {
						opt->scene_set_clock();
						opt->clocktime_clockScene_creat(); 
	                }
	                opt->head_show =false;
	                opt->clockList_show =false;
	            }
			}
        break;
        default:
            break;
    }
}

ClockTime::~ClockTime(void)
{
    clocktime_head_dele();
    clocktime_clockScene_delete();
    if(frame !=NULL)
    {
        delete frame;
        frame =NULL;
        lv_obj_clear_flag(lv_scr_act(), LV_OBJ_FLAG_CLICKABLE);
    }
    ui_image_free();
}

int ClockTime::init_parament(void)
{
    SYSDateTime gettime;
    user_time = gettime.current_datetime();
    clocktime_clockScene_creat();
    clocktime_head_creat();
	StartTimerShow =true;
    clockTimer = startTimer(300, this);
    /*
	if(curClock ==0)
	{
		ui_image_decode_scene(curClock+1);
		set_image_scene(curClock+1);
	}
	else if(curClock ==( CLOCK_LIST_MAX-1))
	{
		ui_image_decode_scene(curClock-1);
		set_image_scene(curClock-1);
	}
	else
	{
		ui_image_decode_scene(curClock-1);
		set_image_scene(curClock-1);
		ui_image_decode_scene(curClock+1);
		set_image_scene(curClock+1);
	}*/
    return 0;
}

void ClockTime::TimerCB(lv_timer_t * tmr)
{
    LV_UNUSED(tmr);
    if(StartTimerShow !=true)
        return;
    SYSDateTime gettime;
    user_time = gettime.current_datetime();
	if(!clockList_show)
		updata_clockScene_index(curClock);
    if((timecntback >16)&&(head_show ==true)&&(clockList_show !=true))
    {
        timecntback =0;
        if(buttonReturn !=NULL)
        {
            buttonReturn->show(false);
        }
        head_show =false;
    }
    else if(head_show ==true)
    {
        timecntback++;
    }
}

void ClockTime::clocktime_head_creat(void)
{
	headIcon = new LvcppScreen(mainscreen);
    headIcon->set_size(LV_HOR_RES_MAX,82);
    headIcon->set_main_bg_color(lv_color_hex(0x00a7d4),LV_OPA_100);
    headIcon->align_to(mainscreen,LV_ALIGN_TOP_LEFT,0,0);
    headIcon->show(false);
	
    buttonReturn = new LvcppButton(lv_layer_top());
    buttonReturn->set_size(66,66);
    buttonReturn->align(LV_ALIGN_TOP_LEFT,30,8);
    buttonReturn->set_main_bg_opa(LV_OPA_0);
    buttonReturn->set_main_radius(0);
    buttonReturn->set_main_pad_all(0);
    buttonReturn->set_main_border_width(0);
    buttonReturn->set_main_bg_img_src(HEAD_RETURN_PNG);
    buttonReturn->add_flag(LV_OBJ_FLAG_EVENT_BUBBLE);
    buttonReturn->set_userdata((void*)HEAD_ICON_RETURN);
    buttonReturn->add_event_cb(head_event_handler,LV_EVENT_PRESSED,this);
    buttonReturn->add_event_cb(head_event_handler,LV_EVENT_RELEASED,this);

    clockIcon = new LvcppButton(lv_layer_top());
    clockIcon->set_size(66,66);
    clockIcon->align(LV_ALIGN_TOP_LEFT,114,8);
    clockIcon->set_main_bg_opa(LV_OPA_0);
    clockIcon->set_main_radius(0);
    clockIcon->set_main_pad_all(0);
    clockIcon->set_main_border_width(0);
    clockIcon->set_main_bg_img_src(HEAD_ICON_ClOCK_PNG);
    clockIcon->set_userdata(NULL);
    clockIcon->show(false);

    
}
void ClockTime::clocktime_head_dele(void)
{
    if(buttonReturn != NULL)
    {
        delete buttonReturn;
        buttonReturn =NULL;
    }
    if(clockIcon != NULL)
    {
        delete clockIcon;
        clockIcon =NULL;
    }
    if(headIcon != NULL)
    {
        delete headIcon;
        headIcon =NULL;
    }
}
void ClockTime::head_event_handler(lv_event_t *event)
{
    ClockTime* opt = (ClockTime*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);

    if((opt->buttonReturn !=NULL)&&(target == opt->buttonReturn->myobj))
    {
        if(event->code== LV_EVENT_PRESSED)
        {
        	opt->timecntback =0;
            opt->buttonReturn->set_main_bg_img_src(opt->HEAD_RETURN_SEL_PNG);
        }
        else
        {
            opt->StartTimerShow =false;
			opt->pause(opt->clockTimer);
    		MainAPPStart::clockTimemain_destory();
        }
    }
}

void ClockTime::clocktime_clockList_creat(void)
{
	ui_image_decode_list();
    ClockList = new LvcppList(mainscreen);
    ClockList->set_size(SCREEN_HOR_SIZE,718);
    ClockList->align(LV_ALIGN_TOP_LEFT,0,82);
    ClockList->set_main_bg_color(lv_color_hex(0x0a85a6),LV_OPA_100);
    ClockList->set_flex_flow(LV_FLEX_FLOW_ROW);
    ClockList->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
    ClockList->set_main_pad_all(0);
    ClockList->set_main_pad_row(0);
    ClockList->set_main_pad_column(0);
    ClockList->set_main_pad_L_R(530,530);
    ClockList->set_main_pad_T_B(217,217);
    ClockList->set_main_border_width(0);
    ClockList->set_main_radius(0);

#ifdef IMAGE_DECODE
void *clockPatch[9]={CLOCK_CLOCK0_PNG,CLOCK_CLOCK1_PNG,CLOCK_CLOCK2_PNG,CLOCK_CLOCK3_PNG,
                            CLOCK_CLOCK4_PNG,CLOCK_CLOCK5_PNG,CLOCK_CLOCK6_PNG,CLOCK_CLOCK7_PNG,
                            CLOCK_CLOCK8_PNG};
#endif
    memset(&clockList_id, 0 , sizeof(clocklist_item_info));
    for(int i=clockList_id.count;i < CLOCK_LIST_MAX;i++)
    {
        clockList_id.list_item[i] = new clockList(ClockList->myobj,(char*)clockPatch[i]);
        clockList_id.list_item[i]->btn->set_userdata((void*)i);
        clockList_id.list_item[i]->btn->add_event_cb(main_event_handler,LV_EVENT_PRESSED,this);
        clockList_id.list_item[i]->btn->add_event_cb(main_event_handler,LV_EVENT_RELEASED,this);
		clockList_id.count++;
    }
	ClockList->set_scroll_to(curClock*284, 0, LV_ANIM_OFF);
    ClockList->set_select_state(curClock,lv_color_hex(0x00a7d4));
}
void ClockTime::clocktime_clockList_delete(void)
{
    for(int i=clockList_id.count;i>0;i--)
    {
        clockList_id.count--;
        if(clockList_id.list_item[clockList_id.count] !=NULL)
        {
            delete clockList_id.list_item[clockList_id.count];
            clockList_id.list_item[clockList_id.count] =NULL;
        }
    }
    if(ClockList != NULL)
    {
        delete ClockList;
        ClockList =NULL;
    }
	ui_image_free_list();
}
void ClockTime::clocktime_clockScene_creat(void)
{
    clockSecne_img_t clockinfo;

    ClockScene = new LvcppList(mainscreen);
    ClockScene->set_size(SCREEN_HOR_SIZE,SCREEN_VER_SIZE);
    ClockScene->align(LV_ALIGN_TOP_LEFT,0,0);
    ClockScene->set_main_bg_color(lv_color_black(),LV_OPA_100);
    ClockScene->set_flex_flow(LV_FLEX_FLOW_ROW);
    ClockScene->set_scrollbar_mode(LV_SCROLLBAR_MODE_OFF);
    ClockScene->set_scrollbar_snap_x(LV_SCROLL_SNAP_START);
    ClockScene->set_main_pad_all(0);
    ClockScene->set_main_pad_row(0);
    ClockScene->set_main_border_width(0);
    ClockScene->set_main_radius(0);
    ClockScene->add_event_cb(scene_event_handler,LV_EVENT_SCROLL_END,this);

    clockinfo.hours =user_time.hour;
    clockinfo.minute =user_time.minute;
    clockinfo.second =user_time.second;
    memset(&clockScene_id,0,sizeof(clockscene_item_info));

    timeList_item = new clockTimeList(ClockScene->myobj,&user_time);
	timeList_item->plateImage->set_main_bg_img_src(CLOCK_SCENE0_PNG);
    timeList_item->plateImage->add_flag(LV_OBJ_FLAG_EVENT_BUBBLE);
    timeList_item->plateImage->add_event_cb(scene_event_handler,LV_EVENT_CLICKED,this);
    timeList_item->plateImage->add_event_cb(scene_event_handler,LV_EVENT_LONG_PRESSED,this);

#ifdef IMAGE_DECODE
void *scenePatch[8]={CLOCK_SCENE1_PNG,CLOCK_SCENE2_PNG,CLOCK_SCENE3_PNG,CLOCK_SCENE4_PNG,
                            CLOCK_SCENE5_PNG,CLOCK_SCENE6_PNG,CLOCK_SCENE7_PNG,CLOCK_SCENE8_PNG};
void *hoursPatch[8]={CLOCK_HOURS1_PNG,CLOCK_HOURS2_PNG,CLOCK_HOURS3_PNG,CLOCK_HOURS4_PNG,
                            CLOCK_HOURS5_PNG,CLOCK_HOURS6_PNG,CLOCK_HOURS7_PNG,CLOCK_HOURS8_PNG};
void *minutePatch[8]={CLOCK_MINUTE1_PNG,CLOCK_MINUTE2_PNG,CLOCK_MINUTE3_PNG,CLOCK_MINUTE4_PNG,
                            CLOCK_MINUTE5_PNG,CLOCK_MINUTE6_PNG,CLOCK_MINUTE7_PNG,CLOCK_MINUTE8_PNG};
void *secondPatch[8]={CLOCK_SECOND1_PNG,CLOCK_SECOND2_PNG,CLOCK_SECOND3_PNG,CLOCK_SECOND4_PNG,
                            CLOCK_SECOND5_PNG,CLOCK_SECOND6_PNG,CLOCK_SECOND7_PNG,CLOCK_SECOND8_PNG};
void *dotPatch[8]={CLOCK_DOT1_PNG,CLOCK_DOT2_PNG,CLOCK_DOT3_PNG,CLOCK_DOT4_PNG,
                            CLOCK_DOT5_PNG,CLOCK_DOT6_PNG,CLOCK_DOT7_PNG,CLOCK_DOT8_PNG};
#endif
    for(int i=clockScene_id.count;i < (CLOCK_LIST_MAX-1);i++)
    {
        clockinfo.platePath =scenePatch[i];
        clockinfo.hoursPath =hoursPatch[i];
        clockinfo.minutePath =minutePatch[i];
        clockinfo.secondPath =secondPatch[i];
        clockinfo.dotPath =dotPatch[i];
        clockScene_id.list_item[i] = new clockSecne(ClockScene->myobj,&clockinfo);
        clockScene_id.list_item[i]->plateImage->add_flag(LV_OBJ_FLAG_EVENT_BUBBLE);
        clockScene_id.list_item[i]->plateImage->add_event_cb(scene_event_handler,LV_EVENT_CLICKED,this);        
        clockScene_id.list_item[i]->plateImage->add_event_cb(scene_event_handler,LV_EVENT_LONG_PRESSED,this);
		clockScene_id.count++;
	}
    ClockScene->set_scroll_to(curClock*SCREEN_HOR_SIZE, 0, LV_ANIM_OFF);
    //ClockScene->invalidate();
}

void ClockTime::clocktime_clockScene_delete(void)
{
    if(timeList_item != NULL)
    {
        delete timeList_item;
        timeList_item =NULL;
    }
    for(int i=clockScene_id.count;i>0;i--)
    {
        clockScene_id.count--;
        if(clockScene_id.list_item[clockScene_id.count] !=NULL)
        {
            delete clockScene_id.list_item[clockScene_id.count];
            clockScene_id.list_item[clockScene_id.count] =NULL;
        }
    }
    if(ClockScene != NULL)
    {
        delete ClockScene;
        ClockScene =NULL;
    }
}
void ClockTime::updata_clockScene_index(int index)
{
	if(ClockScene == NULL)
		return;
	if(index == 0)
	{
		if(timeList_item != NULL)
	    {
	        timeList_item->update_time(&user_time);
	    }
	}
	else
	{
		if(clockScene_id.list_item[index-1] !=NULL)
        {
            clockScene_id.list_item[index-1]->update_time(user_time.hour,user_time.minute,user_time.second);
        }
	}
}
void ClockTime::scene_event_handler(lv_event_t *event)
{
    ClockTime* opt = (ClockTime*) event->user_data;
    lv_obj_t* target = lv_event_get_target(event);
	int curUser =CLOCK_LIST_MAX;
	
    if((opt->ClockScene !=NULL)&&(target == opt->ClockScene->myobj))
    {
        if(event->code == LV_EVENT_SCROLL_END)
        {
        	LV_LOG_USER("LV_EVENT_SCROLL_END");
            curUser = opt->ClockScene->get_scroll_x()/SCREEN_HOR_SIZE;
			if(curUser !=curClock)
			{
				curClock =curUser;
				//opt->scene_del_clock();
				write_int_type_param(PUBLIC_SCENE, CLOCKTYPE, curClock);
			}
			return;
        }
    }
    switch(event->code)
    {
        case LV_EVENT_CLICKED:
            opt->timecntback =0;
            if(opt->buttonReturn !=NULL)
            {
                opt->buttonReturn->show(true);
            }
            opt->head_show =true;
        break;
        case LV_EVENT_LONG_PRESSED:
            opt->timecntback =0;
			LV_LOG_USER("LV_EVENT_LONG_PRESSED-");
            if(opt->ClockList ==NULL)
            {
            	opt->clockList_show =true;
				
            	if(opt->ClockScene !=NULL)
	            {
	                opt->clocktime_clockScene_delete();
	            }
                opt->clocktime_clockList_creat();
				opt->head_show =true;
				opt->timecntback =0;
				if(opt->headIcon !=NULL)
	            {
	                opt->headIcon->show(true);
	            }
				if(opt->buttonReturn !=NULL)
	            {
	                opt->buttonReturn->show(true);
	            }
	            if(opt->clockIcon !=NULL)
	            {
	                opt->clockIcon->show(true);
	            }
			} 
        break;
        default:
        break;
    }
}
void ClockTime::scene_del_clock(void)
{
	if(curClock ==0)
	{
		ui_image_free_scene(curClock+2);
		set_image_scene(curClock+2);
	}
	else if(curClock ==( CLOCK_LIST_MAX-1))
	{
		ui_image_free_scene(curClock-2);
		set_image_scene(curClock-2);
	}
	else
	{
		ui_image_free_scene(curClock-2);
		set_image_scene(curClock-2);
		ui_image_free_scene(curClock+2);
		set_image_scene(curClock+2);
		usleep(50);
		ui_image_decode_scene(curClock-1);
		set_image_scene(curClock-1);
		ui_image_decode_scene(curClock+1);
		set_image_scene(curClock+1);
	}
}
void ClockTime::scene_set_clock(void)
{
	if(curClock ==0)
	{
		ui_image_decode_scene(curClock);
		set_image_scene(curClock);
		ui_image_decode_scene(curClock+1);
		set_image_scene(curClock+1);
	}
	else if(curClock ==( CLOCK_LIST_MAX-1))
	{
		ui_image_decode_scene(curClock);
		set_image_scene(curClock);
		ui_image_decode_scene(curClock-1);
		set_image_scene(curClock-1);
	}
	else
	{
		ui_image_decode_scene(curClock-1);
		set_image_scene(curClock-1);
		ui_image_decode_scene(curClock);
		set_image_scene(curClock);
		ui_image_decode_scene(curClock+1);
		set_image_scene(curClock+1);
	}
}

