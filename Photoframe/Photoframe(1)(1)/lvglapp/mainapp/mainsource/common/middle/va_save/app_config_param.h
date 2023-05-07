#ifndef __APP_CONFIG_PARAM_H__
#define __APP_CONFIG_PARAM_H__
#include "rat_common.h"
/* user data save by sence */
#define VA_SAVE_PATH			"/etc/param_save.cfg"
#define VA_USER_PATH			"/etc/userinfo.cfg"
#define VA_DOWNFILE_INFO		"/etc/downfile_info.cfg"
#define	ROOT_PATCH				"/mnt/UDISK"
#define	SDCARD_PATCH			"/mnt/SDCARD"
#define	UDISK_PATCH				"/mnt/exUDISK"
#define	SDCARD_OTA_PATCH		"/mnt/SDCARD/update.zip"
#define	UDISK_OTA_PATCH			"/mnt/exUDISK/update.zip"
#define	OTA_PATCH				"/usr/bin/"
#define WEA_PATCH  				"/usr/bin/resource/image/weathericon/"
/* major key */
#define PUBLIC_SCENE			"public"
#define MUSIC_SCENE				"music"
#define MOVIE_SCENE				"movie"
#define EXT_MUSIC_SCENE			"ext_music"
#define WLAN_SCENE				"WLAN"
#define OTA_SCENE				"OTA"
#define PHOTO_SCENE				"photo"
#define WEATHER_SCENE			"weather"
#define DOWNFILE_INFO			"fileData"
#define USER_ID					"userID"
#define DOWNFILE_PATCH			"filePatch"
#define DOWNFILE_URL			"fileUrl"
#define SETTING_SCENE			"setting"


/*PUBLIC_SCENE*/
#define VOLUME						"volume"
#define DEFAULT_VOLUME				(20)
#define AUTO_SLEEP					"auto_sleep"
#define DEFAULT_AUTO_SLEEP			(5)
#define AUTO_CLOSE_SCREEN			"auto_close_screen"
#define DEFAULT_CLOSE_SCREEN		(5)
#define AUTO_POWEROFF				"auto_power_off_time"
#define DEFAULT_AUTO_POWEROFF		(5)
#define BACKLIGHT					"backlight"
#define DEFAULT_BACKLIGHT			(50)
#define ENHANCE_MODE				"enhance_mode"
#define DEFAULT_ENHANCE_MODE		(0)
#define ENHANCE_BRIGHT				"enhance_bright"
#define DEFAULT_ENHANCE_BRIGHT		(50)
#define ENHANCE_STATUTION			"enhance_statution"
#define DEFAULT_ENHANCE_STATUTION	(50)
#define ENHANCE_CONTRAST			"enhance_contrast"
#define DEFAULT_ENHANCE_CONTRAST	(50)
#define	LANGUAGE					"language"
#define DEFAULT_LANGUAGE			(7)
#define	DATE						"date"
#define DEFAULT_DATE				("2022-09-19")
#define	TIME						"time"
#define DEFAULT_TIME				("08:30")
#define	TIMETYPE					"TimeType"
#define DEFAULT_TIMETYPE			(12)
#define	TIMEZONE					"TimeZone"
#define DEFAULT_TIMEZONE			(8)
#define	NETTIME						"netTime"
#define DEFAULT_NETTIME				(1)
#define	USERINFO					"userInfo"
#define DEFAULT_USERINFO			(NULL)
#define	CLOCKTYPE					"clocktype"
#define DEFAULT_CLOCKTYPE			(0)
#define	VERSION						"version"
#define DEFAULT_VERSION				("1.00.00.00")
#define	MODEL						"model"
#define DEFAULT_MODEL				("T113")
#define	BUILDNUM					"buildNum"
#define DEFAULT_BUILDNUM			("ZX101_T113_AC_V2.0")
#define BREAK_TAG_ROOT_PATH			 "root_path"
/*MUSIC_SCENE*/
/*MOVIE_SCENE*/
/*EXT_MUSIC_SCENE*/
#define	PLAYMODE					"playmode"
#define DEFAULT_PLAYMODE			(RAT_PLAY_MODE_ROTATE_ALL)
#define	LOOP						"loop"
#define DEFAULT_LOOP				(0)
#define	PATH						"path"
#define DEFAULT_PATH				(NULL)
#define	FILENAME					"filename"
#define DEFAULT_FILENAME			(NULL)
#define	FILETYPE					"fileType"
#define DEFAULT_FILETYPE			(NULL)
#define	OFFSET						"offset"
#define DEFAULT_OFFSET				(0)
#define	INDEX						"index"
#define DEFAULT_INDEX				(0)
#define	DURATION					"nDurationSec"
#define DEFAULT_DURATION			(0)
#define	LOOPMUSIC					"loop_music"
#define DEFAULT_LOOPMUSIC			(0)

/*WLAN_SCENE*/
#define	WLAN_MANU_ON				"manu_on"
#define DEFAULT_WLAN_MANU_ON		(1)
#define	WLAN_MANU_CONNECTED			"manu_connected"
#define DEFAULT_MANU_CONNECTED		(1)
#define	WLAN_MANU_SSID				"manu_ssid"
#define DEFAULT_MANU_SSID			("ZXF_CJ_TEST")
#define	WLAN_MANU_PASSWORD			"manu_password"
#define DEFAULT_MANU_PASSWORD		("88880000")

/*SETTING_SCENE*/
#define	SET_DEV_NAME							"device_name"
#define DEFAULT_SET_DEV_NAME					"Vphoto"
#define	SET_USER_NAME							"User_name"
#define	DEFAULT_SET_USER_NAME					"User"
#define	SET_TP_VOL_MOD							"tp_vol_mod"        
#define	DEFAULT_SET_TP_VOL_MOD					(0)
#define	SET_BOY									"levitation_ball"
#define	DEFAULT_SET_BOY							(0)
#define	SET_AUTOPLAY_MOD						"autoplay"
#define	DEFAULT_SET_AUTOPLAY_MOD				(0)
#define	SET_PHOTO_DISP_ORDER					"photo_disp_order"
#define	DEFAULT_SET_PHOTO_DISP_ORDER			(0)
#define	SET_PHOTO_SORT_ORDER					"photo_sort_order"
#define	DEFAULT_SET_PHOTO_SORT_ORDER			(0)
#define	SET_DESCRIBE							"describe"
#define	DEFAULT_SET_DESCRIBE					(1)
#define	SET_DATA_STY							"data_sty"
#define	DEFAULT_SET_DATA_STY					(0)
#define	SET_TIME_STY							"time_sty"
#define	DEFAULT_SET_TIME_STY					(0)
#define	SET_AUTO_STARTUP						"auto_startup"
#define	DEFAULT_SET_AUTO_STARTUP				(0)
#define	SET_BODY_INDUCTION						"body_induction"
#define	DEFAULT_SET_BODY_INDUCTION				(0)
#define	SET_MSG_VOL								"msg_vol"
#define	DEFAULT_SET_MSG_VOL						(0)
#define	SET_RES_FACTORY							"res_factory"
#define	DEFAULT_SET_RES_FACTORY					(0)
#define	SET_CONNECT_NUM							"connect"
#define	DEFAULT_SET_CONNECT_NUM					(0)


/*weather*/
#define	ANDROIDINFO					"androidinfo"
#define DEFAULT_ANDROIDINFO			(NULL)
#define	IOSINFO						"iosinfo"
#define DEFAULT_IOSINFO				(NULL)
#define	EMAILLINFO					"emailinfo"
#define DEFAULT_EMAILLINFO			(NULL)
#define	DEVNICKNAME					"deviceNickname"
#define DEFAULT_DEVNICKNAME			(NULL)
#define	IOSLINK						"ios_download_link"
#define DEFAULT_IOSLINK				(NULL)
#define	GOOGLELINK					"android_download_link"
#define DEFAULT_GOOGLELINK			(NULL)

#define	TEMPCORF					"temp_c_f"
#define DEFAULT_TEMPCORF			(0)
#define	SERIALADDRESS				"serialAddress"
#define DEFAULT_SERIALADDRESS		("ZXF8FA9D9637AEBC175A")
#define	MACADDRESS					"macAddress"
#define DEFAULT_MACADDRESS			("00:e0:4c:53:3e:b3")
#define	NICKNAME					"nickName"
#define DEFAULT_NICKNAME			("zxf")
#define	COMPANYNAME					"companyName"
#define DEFAULT_COMPANYNAME			("VPhoto")
#define	DEVID						"devId"
#define DEFAULT_DEVID				(NULL)
#define	DEVICETOKEN					"device_token"
#define DEFAULT_DEVICETOKEN			(NULL)
#define	ACCESSTOKEN					"accessToken"
#define DEFAULT_ACCESSTOKEN			(NULL)
#define	DEVCODE						"devCode"
#define DEFAULT_DEVCODE				(NULL)
#define	EMAILDATA					"EmailData"
#define DEFAULT_EMAILDATA			(NULL)
#define	FCMTOKEN					"fcmToken"
#define DEFAULT_FCMTOKEN			(NULL)

#define	CITYNAME					"cityName"
#define DEFAULT_CITYNAME			("shenzhen")
#define	CITYID						"cityId"
#define DEFAULT_CITYID				(2161853)
#define	LATDATA						"latData"
#define DEFAULT_LATDATA				("22.54679")
#define	LONDATA						"lonData"
#define DEFAULT_LONDATA				("114.11256")
#define	CITYNAME1					"cityName1"
#define DEFAULT_CITYNAME1			(NULL)
#define	CITYID1						"cityId1"
#define DEFAULT_CITYID1				(0)
#define	LATDATA1					"latData1"
#define DEFAULT_LATDATA1			(NULL)
#define	LONDATA1					"lonData1"
#define DEFAULT_LONDATA1			(NULL)
#define	CITYNAME2					"cityName2"
#define DEFAULT_CITYNAME2			(NULL)
#define	CITYID2						"cityId2"
#define DEFAULT_CITYID2				(0)
#define	LATDATA2					"latData2"
#define DEFAULT_LATDATA2			(NULL)
#define	LONDATA2					"lonData2"
#define DEFAULT_LONDATA2			(NULL)
#define	CITYNAME3					"cityName3"
#define DEFAULT_CITYNAME3			(NULL)
#define	CITYID3						"cityId3"
#define DEFAULT_CITYID3				(0)
#define	LATDATA3					"latData3"
#define DEFAULT_LATDATA3			(NULL)
#define	LONDATA3					"lonData3"
#define DEFAULT_LONDATA3			(NULL)
#define	CITYNAME4					"cityName4"
#define DEFAULT_CITYNAME4			(NULL)
#define	CITYID4						"cityId4"
#define DEFAULT_CITYID4				(0)
#define	LATDATA4					"latData4"
#define DEFAULT_LATDATA4			(NULL)
#define	LONDATA4					"lonData4"
#define DEFAULT_LONDATA4			(NULL)
#define	CITYNAME5					"cityName5"
#define DEFAULT_CITYNAME5			(NULL)
#define	CITYID5						"cityId5"
#define DEFAULT_CITYID5				(0)
#define	LATDATA5					"latData5"
#define DEFAULT_LATDATA5			(NULL)
#define	LONDATA5					"lonData5"
#define DEFAULT_LONDATA5			(NULL)
#define	CITYNAME6					"cityName6"
#define DEFAULT_CITYNAME6			(NULL)
#define	CITYID6						"cityId6"
#define DEFAULT_CITYID6				(0)
#define	LATDATA6					"latData6"
#define DEFAULT_LATDATA6			(NULL)
#define	LONDATA6					"lonData6"
#define DEFAULT_LONDATA6			(NULL)
#define	CITYNAME7					"cityName7"
#define DEFAULT_CITYNAME7			(NULL)
#define	CITYID7						"cityId7"
#define DEFAULT_CITYID7				(0)
#define	LATDATA7					"latData7"
#define DEFAULT_LATDATA7			(NULL)
#define	LONDATA7					"lonData7"
#define DEFAULT_LONDATA7			(NULL)
#define	CITYNAME8					"cityName8"
#define DEFAULT_CITYNAME8			(NULL)
#define	CITYID8						"cityId8"
#define DEFAULT_CITYID8				(0)
#define	LATDATA8					"latData8"
#define DEFAULT_LATDATA8			(NULL)
#define	LONDATA8					"lonData8"
#define DEFAULT_LONDATA8			(NULL)
#define	CITYNAME9					"cityName9"
#define DEFAULT_CITYNAME9			(NULL)
#define	CITYID9						"cityId9"
#define DEFAULT_CITYID9				(0)
#define	LATDATA9					"latData9"
#define DEFAULT_LATDATA9			(NULL)
#define	LONDATA9					"lonData9"
#define DEFAULT_LONDATA9			(NULL)
#define	CITYNAME10					"cityName10"
#define DEFAULT_CITYNAME10			(NULL)
#define	CITYID10					"cityId10"
#define DEFAULT_CITYID10			(0)
#define	LATDATA10					"latData10"
#define DEFAULT_LATDATA10			(NULL)
#define	LONDATA10					"lonData10"
#define DEFAULT_LONDATA10			(NULL)


#define	WEEKCUR						"week_cur"
#define DEFAULT_WEEKCUR				(7)
#define	TEMPCUR						"temp_cur"
#define DEFAULT_TEMPCUR				(NULL)
#define	TEMPMAXCUR					"temp_max_cur"
#define DEFAULT_TEMPMAXCUR			(NULL)
#define	TEMPMINCUR					"temp_min_cur"
#define DEFAULT_TEMPMINCUR			(NULL)
#define	HUMCUR						"humidity_cur"
#define DEFAULT_HUMCUR				(0)
#define	IDCUR						"id_cur"
#define DEFAULT_IDCUR				(0)
#define	SPEEDCUR					"speed_cur"
#define DEFAULT_SPEEDCUR			(NULL)
#define	WEINFCUR					"weinfo_cur"
#define DEFAULT_WEINFCUR			(NULL)
#define	ICONCUR						"icon_cur"
#define DEFAULT_ICONCUR				(NULL)

#define	WEEKONE						"week_one"
#define DEFAULT_WEEKONE				(7)
#define	TEMPONE						"temp_one"
#define DEFAULT_TEMPONE				(NULL)
#define	TEMPMAXONE					"temp_max_one"
#define DEFAULT_TEMPMAXONE			(NULL)
#define	TEMPMINONE					"temp_min_one"
#define DEFAULT_TEMPMINONE			(NULL)
#define	HUMONE						"humidity_one"
#define DEFAULT_HUMONE				(0)
#define	IDONE						"id_one"
#define DEFAULT_IDONE				(0)
#define	SPEEDONE					"speed_one"
#define DEFAULT_SPEEDONE			(NULL)
#define	WEINFONE					"weinfo_one"
#define DEFAULT_WEINFONE			(NULL)
#define	ICONONE						"icon_one"
#define DEFAULT_ICONONE				(NULL)

#define	WEEKTOW						"week_tow"
#define DEFAULT_WEEKTOW				(7)
#define	TEMPTOW						"temp_tow"
#define DEFAULT_TEMPTOW				(NULL)
#define	TEMPMAXTOW					"temp_max_tow"
#define DEFAULT_TEMPMAXTOW			(NULL)
#define	TEMPMINTOW					"temp_min_tow"
#define DEFAULT_TEMPMINTOW			(NULL)
#define	HUMTOW						"humidity_tow"
#define DEFAULT_HUMTOW				(0)
#define	IDTOW						"id_tow"
#define DEFAULT_IDTOW				(0)
#define	SPEEDTOW					"speed_tow"
#define DEFAULT_SPEEDTOW			(NULL)
#define	WEINFTOW					"weinfo_tow"
#define DEFAULT_WEINFTOW			(NULL)
#define	ICONTOW						"icon_tow"
#define DEFAULT_ICONTOW				(NULL)

#define	WEEKTHREE					"week_three"
#define DEFAULT_WEEKTHREE			(7)
#define	TEMPTHREE					"temp_three"
#define DEFAULT_TEMPTHREE			(NULL)
#define	TEMPMAXTHREE				"temp_max_three"
#define DEFAULT_TEMPMAXTHREE		(NULL)
#define	TEMPMINTHREE				"temp_min_three"
#define DEFAULT_TEMPMINTHREE		(NULL)
#define	HUMTHREE					"humidity_three"
#define DEFAULT_HUMTHREE			(0)
#define	IDTHREE						"id_three"
#define DEFAULT_IDTHREE				(0)
#define	SPEEDTHREE					"speed_three"
#define DEFAULT_SPEEDTHREE			(NULL)
#define	WEINFTHREE					"weinfo_three"
#define DEFAULT_WEINFTHREE			(NULL)
#define	ICONTHREE					"icon_three"
#define DEFAULT_ICONTHREE			(NULL)

#define	SENDERID					"sender_id"
#define	SENDNAME					"sender_name"
#define	SENDERREMARKNAME			"sender_remarkname"
#define	SENDERNICKNAME				"sender_nickname"
#define	SENDERAVATAR				"sender_avatar"
/*PHOTO*/
#define	SET_MSG_BGM					"bgm"
#define	MSG_BGM						(0)
#define	SET_MSG_INTERVAL			"interval"
#define	MSG_INTERVAL				(0)
#define	SET_MSG_EFFECT				"effect"
#define	MSG_EFFECT					(0)

#endif