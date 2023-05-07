#ifndef LVCPP_OPTAPI_H
#define LVCPP_OPTAPI_H

#include  "lv_code/lvgl/lvgl.h"

namespace LVGLOPTAPI
{
  class LvcppImageDEC
   {
     public:
      static lv_res_t imgdecoderFromPicture(lv_img_dsc_t* imgdata, const void* name)
       {
         lv_img_decoder_dsc_t dec_dsc;
         if(lv_img_decoder_get_info(name, &dec_dsc.header) != LV_RES_OK)
          {
              LV_LOG_USER("devoder get info error");
              return LV_RES_INV;
          }

         if(lv_img_decoder_open(&dec_dsc, name, lv_color_white(), 0) != LV_RES_OK)
          {
              LV_LOG_USER("devoder open error");
              return LV_RES_INV;
          }

         imgdata->data = dec_dsc.img_data;
         imgdata->data_size = dec_dsc.header.w * dec_dsc.header.h * LV_IMG_PX_SIZE_ALPHA_BYTE;
         imgdata->header = dec_dsc.header;
         imgdata->header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA;

         return LV_RES_OK;
        }

      static void imgdata_free(lv_img_dsc_t* imageSrc)
       {
           if(imageSrc->data != NULL)
           {
               lv_mem_free((void *)imageSrc->data);
           }
       }
   };

  class LvcppMemory
   {
     public:
      static void* mem_alloc(size_t size)
      {
          return lv_mem_alloc(size);
      }

      static void  mem_free(void* data)
      {
          lv_mem_free(data);
      }

      static void* mem_realloc(void* data_p, size_t new_size)
      {
          return lv_mem_realloc(data_p, new_size);
      }

      static void memset(void* dst, uint8_t v, size_t len)
      {
          lv_memset(dst, v, len);
      }

      static void* memcpy(void* dst, const void* src, size_t len)
      {
          return lv_memcpy(dst, src, len);
      }
  };



  class LvcppDisp
  {
    public:
		static lv_disp_t* get_default_disp(void)
		{
            lv_disp_t* disp = lv_disp_get_default();
			if(!disp)
			{
				return nullptr;
			}
			return disp;
		}

		static int get_disp_hor_res(int* disp_w)
		{
          lv_disp_t* disp = lv_disp_get_default();
		  if(!disp)
		  {
		      return -1;
		  }

		  *disp_w = lv_disp_get_hor_res(disp);
		  return 0;
		}
		static int get_disp_ver_res(int* disp_h)
		{
          lv_disp_t* disp = lv_disp_get_default();
		  if(!disp)
		  {
		      return -1;
		  }

		  *disp_h = lv_disp_get_ver_res(disp);
		  return 0;
		}
		static int get_disp_offset_x(int* disp_x)
		{
          lv_disp_t* disp = lv_disp_get_default();
		  if(!disp)
		  {
		      return -1;
		  }

		  *disp_x = lv_disp_get_offset_x(disp);
		  return 0;
		}
		static int get_disp_offset_y(int* disp_y)
		{
          lv_disp_t* disp = lv_disp_get_default();
		  if(!disp)
		  {
		      return -1;
		  }

		  *disp_y = lv_disp_get_offset_y(disp);
		  return 0;
		}

		static int set_disp_rotation(lv_disp_rot_t rotation)
		{
          lv_disp_t* disp = lv_disp_get_default();
		  if(!disp)
		  {
		      return -1;
		  }
		  if(rotation == lv_disp_get_rotation(disp))
		  {
			  return 0;
		  }
		  lv_disp_set_rotation(disp,rotation);
		  return 0;
		}

		static int get_disp_rotation(lv_disp_rot_t* rotation)
		{
          lv_disp_t* disp = lv_disp_get_default();
		  if(!disp)
		  {
		      return -1;
		  }

		  *rotation = lv_disp_get_rotation(disp);
		  return 0;
		}
	
  };

  class LvcppIndev
  {
    public:
	  static lv_indev_t* get_indev_act(void)
      {
          lv_indev_t* indev = lv_indev_get_act();
		  if(!indev)
		  {
			  return nullptr;
		  }
		  return indev;
      }
	  static int get_indev_type(lv_indev_type_t* type)
      {
          lv_indev_t* indev = lv_indev_get_act();
          if(!indev)
          {
              return -1;
          }
          *type = lv_indev_get_type(indev);
          return 0;
      }

	  static int set_indev_group(lv_group_t * group)
      {
          lv_indev_t* indev = lv_indev_get_act();
          if(!indev)
          {
              return -1;
          }
          lv_indev_set_group(indev,group);
          return 0;
      }
	  
      static int get_indev_point(lv_point_t* point)
      {
          lv_indev_t* indev = lv_indev_get_act();
          if (lv_indev_get_type(indev) != LV_INDEV_TYPE_POINTER)
          {
              return -1;
          }

          lv_indev_get_point(indev, point);
          return 0;
      }
	  
	  static int get_indev_vect(lv_point_t* vect)
      {
          lv_indev_t* indev = lv_indev_get_act();
          if (lv_indev_get_type(indev) != LV_INDEV_TYPE_POINTER)
          {
              return -1;
          }

          lv_indev_get_vect(indev, vect);
          return 0;
      }

	  static int get_indev_key(int* key_val,int* key_state)
      {
          lv_indev_t* indev = lv_indev_get_act();
          if (lv_indev_get_type(indev) != LV_INDEV_TYPE_KEYPAD)
          {
              return -1;
          }

		  *key_val = lv_indev_get_key(indev);
		  *key_state = lv_indev_get_key_state(indev);
          return 0;
      }
  };

  class LvcppEvent
  {
    public:
      static lv_obj_t* get_target(lv_event_t* event)
      {
          return lv_event_get_target(event);
      }

      static void* get_target_userdata(lv_event_t* event)
      {
          lv_obj_t* obj = get_target(event);
          return lv_obj_get_user_data(obj);
      }

      static lv_event_code_t get_event_code(lv_event_t* event)
      {
          return lv_event_get_code(event);
      }

      static void* get_event_userdata(lv_event_t* event)
      {
          return lv_event_get_user_data(event);
      }
  };

  class LvcppGroup
  {
    public:
 	  static int add_group_obj(lv_group_t * group, lv_obj_t * obj)
 	  {
 	      if(group==nullptr || obj==nullptr)
 	      {
		      return -1;	
		  }
 	      lv_group_add_obj(group,obj);
		  return 0;
 	  }
	  static int remove_group_obj(lv_obj_t * obj)
 	  {
 	      if(obj==nullptr)
 	      {
		      return -1;	
		  }
 	      lv_group_remove_obj(obj);
		  return 0;
 	  }
	  static int remove_group_all_obj(lv_group_t * group)
 	  {
 	      if(group==nullptr)
 	      {
		      return -1;	
		  }
 	      lv_group_remove_all_objs(group);
		  return 0;
 	  }
  };


  class LvcppNewGroup
  {
    public:
		LvcppNewGroup(){	group = lv_group_create();};
		~LvcppNewGroup(){lv_group_del(group);};

		lv_group_t * get_group(){return group;};

	private:
		lv_group_t * group=nullptr;
	
  };

  class LvcppLayer
  {
    public:
      static lv_obj_t* get_scr_act(void)
      {
          return lv_scr_act();
      }
      static lv_obj_t* get_layer_top(void)
      {
          return lv_layer_top();
      }
      static lv_obj_t* get_layer_sys(void)
      {
          return lv_layer_sys();
      }
  };

}

#endif // LVCPP_OPTAPI_H
