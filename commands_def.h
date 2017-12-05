#ifndef __COMMAND_DEF__ 
#define __COMMAND_DEF__ 
 
typedef unsigned char Uint8;
typedef unsigned short Uint16;
typedef unsigned int Uint32;

typedef unsigned short Int16;


#define CMD_HEADER				0x55aa 
#define CMD_TAILER				0xaa55 
 
#define CMD_TARGET_ANDROID		0x00 
#define CMD_TARGET_MCU			0x01 
#define CMD_TARGET_OPS			0x02 
#define CMD_TARGET_232			0x03 
#define CMD_TARGET_HOST			0x04 
#define CMD_TARGET_IR			0x05 
#define CMD_TARGET_EXTENDED		0x06 
 
#define CMD_PIPE_UART			0x00 
#define CMD_PIPE_IP				0x01 
 
 
#define CMD_NOT_DEFINED			0xffff 
 
#define CMD_POFF_REQ			0x0000

#define CMD_POWER_ON			0x0001 
#define CMD_POWER_OFF			0x0002 
//#define CMD_SLEEP				0x0003 
#define CMD_ENERGY_SAVE			0x0003  //ruandelu 20150410 add for IR Button on of ENERGY_SAVE


#define CMD_VOL_UP				0x0004 
#define CMD_VOL_DOWN			0x0005 

#if 0
#define CMD_VOL_MUTE			0x0006
#define CMD_CHANNEL_UP			0x0006 
#define CMD_CHANNEL_DOWN		0x0007 

#define CMD_INPUT_SOURCE		0x0010
#endif

#define CMD_VOL_MUTE			0x0006
#define CMD_CHANNEL_UP			0x0007 
#define CMD_CHANNEL_DOWN		0x0008 
#define CMD_INPUT_SOURCE		0x0010 
#define CMD_SOURCE_OPS			0x0011 	//ruandelu 20150112 add for IR input source Button on the NewLine keyboard 
#define CMD_SOURCE_VGA			0x0012  //ruandelu 20150112 add for IR input source Button on the NewLine keyboard
#define CMD_SOURCE_HDMI1		0x0013  //ruandelu 20150112 add for IR input source Button on the NewLine keyboard	 
#define CMD_SOURCE_HDMI2		0x0014  //ruandelu 20150112 add for IR input source Button on the NewLine keyboard
#define CMD_DISPLAY_RESOLUTION	0x0015 
#define CMD_SCREEN_SAVE			0x0016 
#define CMD_DISPLAY_PARA		0x0017  //CMD_DISPLAY_INFO
#define CMD_PRINT_SCREEN		0x0018 
#define CMD_DISPLAY_AUTO		0x0019  //ruandelu 20150112 add for IR Button on the NewLine keyboard
#define CMD_ANDROID_SETTING		0x001a  //ruandelu 20150112 add for IR Button on the NewLine keyboard
#define CMD_ANDROID_MODE		0x001b  //ruandelu 20150112 add for IR Button on the NewLine keyboard
#define CMD_WIFI_SETTING		0x001c  //0x001c  //ruandelu 20150410 add for IR Button on of WIFI
#define CMD_FUNC_ZOOM		    0x001d  //ruandelu 20150112
#define CMD_FUNC_RED		    0x001e  //ruandelu 20150112
#define CMD_FUNC_GREEN		    0x001f  //ruandelu 20150112
#define CMD_FUNC_YELLOW		    0x0020  //ruandelu 20150112
#define CMD_FUNC_BLUE		    0x0021  //ruandelu 20150112
#define CMD_ONLY_AUDIO		    0x0022  //ruandelu 20150112
#define CMD_SWITCH_HDMI		    0x0023  //ruandelu 20150113


//ruandelu 20160411 kbd2016 bgn
#define CMD_SOURCE_TV                  0x0024
#define CMD_SOURCE_AV                  0x0025
#define CMD_FREEZE_IMG                  0x0026

//ruandelu 20161217 IR UC v2017 bgn
#define CMD_SOURCE_HDMI3		0x0027  //ir UC Rear2
#define CMD_SOURCE_HDMI4		0x0028  //ir UC Rear3
#define CMD_SOURCE_DP		0x0029  //ir UC Rear3
//ruandelu 20161217 IR UC v2017 end


// ruandelu 20161212 ir keys for 828_11(UC) bgn
#define CMD_KEY_UC			0x0030
//#define CMD_KEY_ZOOM_IN				0x0031
#define CMD_KEY_ZOOM_OUT			0x0032
#define CMD_KEY_SPEAKER_MUTE		0x0033
#define CMD_KEY_MIC_SWTICH			0x0034
// ruandelu 20161212 ir keys for 828_11(UC) end

#define CMD_KEY_F1_F12		0x0508
#define CMD_PC_F1				0x050a
#define CMD_PC_F2				0x050b
#define CMD_PC_F3				0x050c
#define CMD_PC_F4				0x050d
#define CMD_PC_F5				0x050e
#define CMD_PC_F6				0x050f
#define CMD_PC_F7				0x0510
#define CMD_PC_F8				0x0511
#define CMD_PC_F9				0x0512
#define CMD_PC_F10				0x0513
#define CMD_PC_F11				0x0514
#define CMD_PC_F12				0x0515
//ruandelu 20160411 kbd2016 end

#define CMD_APP_WHITEBOARD		0x0040  //ruandelu 20150410 add for IR Button on of WHITEBOARD
#define CMD_APP_UC				0x0041  //ruandelu 20150410 add for IR Button on of UC

//ruandelu 20151206 ChangHong Air Mouse 2.4G Wireless Air Mouse idVendor=26e3, idProduct=af02 bgn
//#define CMD_PEN_VOL_UP 		    0x0042
#define CMD_APP_CUSTOM 		    0x0042
#define CMD_PEN_ZOOMIN_SNAP	    0x0043
#define CMD_PEN_ANDRIOD_UC	    0x0044
#define CMD_PEN_PPT_PLAY_ENTRY  0x0045
#define CMD_PEN_PPT_ANNOTATION  0x0046

#define CMD_PEN_FILE_CLOSE	    0x0047
#define CMD_PEN_PPT_BLACK		0x0048
#define CMD_PEN_PPT_WHITE	    0x0049
#define CMD_PEN_PPT_ZOOM	    0x004A
#define CMD_PEN_PPT_PLAY_EXIT   0x004B
#define CMD_PEN_FILE_OPEN       0x004C  //OK,APP_OPEN
//ruandelu 20151206 ChangHong Air Mouse 2.4G Wireless Air Mouse idVendor=26e3, idProduct=af02 end


#define CMD_TOUCH_DATA			0x0080 
#define CMD_PEN_DATA			0x0081
//ruandelu 20170205 w/h not transfer bgn
//#define CMD_TOUCH_W_H_DATA		0x0082
//ruandelu 20170205 w/h not transfer end

#define CMD_KEY_0				0x0100 
#define CMD_KEY_1				0x0101 
#define CMD_KEY_2				0x0102 
#define CMD_KEY_3				0x0103 
#define CMD_KEY_4				0x0104 
#define CMD_KEY_5				0x0105 
#define CMD_KEY_6				0x0106 
#define CMD_KEY_7				0x0107 
#define CMD_KEY_8				0x0108 
#define CMD_KEY_9				0x0109 
#define CMD_KEY_HOME			0x010a 
#define CMD_KEY_RETURN			0x010b 
#define CMD_KEY_MENU			0x010c 
#define CMD_KEY_OK				0x010d 
#define CMD_KEY_LEFT			0x010e 
#define CMD_KEY_RIGHT			0x010f 
#define CMD_KEY_UP				0x0110 
#define CMD_KEY_DOWN			0x0111 

#define CMD_KEY_PAGE_UP			0x0112  //ruandelu 20150410 add for IR Button
#define CMD_KEY_PAGE_DOWN		0x0113  //ruandelu 20150410 add for IR Button


//ruandelu 20141230 add to the define of command by manager lu
#define CMD_GET_CALENDAR		0x0200 
#define CMD_SET_CALENDAR		0x0201 
#define CMD_SET_ON_TIME			0x0202 
#define CMD_SET_OFF_TIME		0x0203 
#define CMD_SWITCH_USB_HOST1	0x0204 
#define CMD_SWITCH_USB_HOST2	0x0205 
#define CMD_SWITCH_USB_HOST3	0x0206 
#define CMD_SWITCH_USB_HOST4	0x0207 
#define CMD_SWITCH_USB_HOST5	0x0219
#define CMD_SWITCH_USB_HOST6	0x0230
#define CMD_SWITCH_USB_HOST7	0x0231


//ruandelu 20141230 add for send "command of usb switch" to mcu bgn
#define CMD_SWITCH_USB_ANDROID	0x0904 //not transfer
//ruandelu 20141230 add for send "command of usb switch" to mcu end

#define CMD_SWITCH_CAMERA		0x0208 
#define CMD_SWITCH_CAMERA1		0x0209 
#define CMD_SWITCH_CAMERA2		0x020a 
#define CMD_SWITCH_CAMERA_HOST	0x020b 
#define CMD_SWITCH_CAMERA_TO_OPS		0x020c 
#define CMD_SWITCH_CAMERA_TO_ANDROID	0x020d 

//ruandelu 20150421 tell mcu to boot by net bgn
#define CMD_BOOT_NET_EN      	0x020e
#define CMD_BOOT_NET_DIS      	0x020f
//ruandelu 20150421 tell mcu to boot by net end


#define CMD_SET_ENV			0x0210
#define CMD_SET_MCU_VER		0x0211

#define CMD_TV_EN			0x0212
#define CMD_TV_DIS			0x0213

#define CMD_GET_CALIBRATE			0x0214
#define CMD_SET_CALIBRATE			0x0215

#define CMD_LOCK_DEVICE			0x0216
#define CMD_UNLOCK_DEVICE		0x0217

//ruandelu 20150720 cut power from apk bgn
#define CMD_POWER_CUT		    0x0218  
//ruandelu 20150720 cut power from apk end

//ruandelu 20160421 tell mcu to boot ops bgn
#define CMD_BOOT_OPS_ON      	0x021a
#define CMD_BOOT_OPS_OFF      	0x021b
//ruandelu 20160421 tell mcu to boot ops end

//ruandelu 20160427 tell mcu to boot up ops bgn
#define CMD_BOOT_OPS_BOOTUP      	0x021c
//ruandelu 20160427 tell mcu to boot up ops end

#define CMD_TELL_MCU_POWER_ON_OPS	0x0226

#define CMD_TELL_MCU_POWER_OFF_OPS	0x0227


#define CMD_POWERLED_FLASH		    0x021d 
#define CMD_POWERLED_ALWAYSLIGHT	0x021e 

#define CMD_LONG_HOMEINPUT     0x021f

// ruandelu 20160906 bgn
#define CMD_SET_ON_TM_EN      	0x0221
#define CMD_SET_ON_TM_DIS      	0x0222
#define CMD_SET_OFF_TM_EN      	0x0223
#define CMD_SET_OFF_TM_DIS     	0x0224
// ruandelu 20160906 end

#define CMD_ASK_POWER_OFF_OPS	0x0225

#define CMD_DATA_TRANS_BILATERAL   0x0302

#define CMD_ENTER_BOOTLOADER	0x0400
#define CMD_BT_DATA_RAW			0x0401
#define CMD_BT_FLASH_WRITE		0x0402
#define CMD_BT_FLASH_STATUS		0x0403
#define CMD_EXIT_BOOTLOADER		0x0404


#define CMD_BT_DATA_LEN		64
#define CMD_BT_SECTOR_LEN		2048

#define CMD_UART_MAX		0x7FFF
//定义触摸框类型
#define defTouchPanelSharp 1
#define defTouchPanelHht   2
#define defTouchPanelFlatFrog 3
#define defTPFlatFrog2F    4

typedef struct { 
	Uint16 header; 
}__attribute__((__packed__)) COMMAND_HEADER; 
//typedef struct COMMAND_HEADER COMMAND_HEADER; 
 
typedef struct  {
	// ruandelu 20170108 the name and data of png file bgn
	//cmd_length = this struct and data 
	// after header of COMMAND_HEADER and before body_checksum of COMMAND_TAILER
	// exclude header of COMMAND_HEADER and exclude body_checksum/tailer of COMMAND_TAILER
	// ruandelu 20170108 the name and data of png file end
	Uint16 cmd_length;
	Uint8 cmd_seq; 
	Uint8 src:3; 
	Uint8 dst:3; 
	Uint8 pipe:2; 
	Uint16 cmd; 
 
//	Uint16 data[1]; 
}__attribute__((__packed__))  COMMAND_UART_BODY; 

//typedef struct COMMAND_UART_BODY COMMAND_UART_BODY; 
/*typedef struct { 
	Uint16 year;				// BCD format 
	Uint8 month;				// BCD format 
	Uint8 day;					// BCD format 
	Uint8 dayofweek;			// BCD format 
	Uint8 hour;					// BCD format 
	Uint8 minute;				// BCD format 
	Uint8 second;				// BCD format 
}__attribute__((__packed__)) CMD_UART_DATA_CALENDAR; 
*/

typedef struct  { 
	Uint16 body_checksum; 
	Uint16 tailer; 
}__attribute__((__packed__)) COMMAND_TAILER; 
//typedef struct COMMAND_TAILER COMMAND_TAILER; 

typedef struct  {
	COMMAND_HEADER headflag;
	COMMAND_UART_BODY body;
}__attribute__((__packed__)) CMD_UART_HEAD;


typedef struct { 
	Uint16 year;				// BCD format 
	Uint8 month;				// BCD format 
	Uint8 day;					// BCD format 
	Uint8 dayofweek;			// BCD format 
	Uint8 hour;					// BCD format 
	Uint8 minute;				// BCD format 
	Uint8 second;				// BCD format 
}__attribute__((__packed__)) CMD_UART_DATA_CALENDAR; 

typedef struct { 
	Uint16 right;
	Uint16 bottom;
	Uint16 left;
	Uint16 top;
}__attribute__((__packed__)) CMD_UART_DATA_CALIBRATE; 

typedef struct { 
	Int16 ambient_temperature; 
	Int16 board_temperature; 
	Uint16 humidity; 
	Uint16 ambient_light; 
	

	uint16_t ops_ready:1;
	uint16_t ops_on:1;
	uint16_t ambient_sensor:1;
	uint16_t temp_sensor:1;
	uint16_t vga_detect:1;
	uint16_t dp_detect:1;

	uint16_t rsvd:9;
	uint16_t bootloader:1;

	uint16_t status;

	uint32_t mcu_dev_id;
	uint16_t flash_page_size, flash_sector_size;
	uint32_t flash_size;
	uint32_t app_start_addr;

}__attribute__((__packed__)) CMD_UART_DATA_ENV; 

#define FLASH_WRITE_OK			0x00
#define FLASH_DATA_INVALID		0x01
#define FALSH_ERASE_FAIL		0x02
#define FLASH_WRITE_BUSY		0x03
#define FLASH_WRITE_FAIL		0x04

typedef struct {
	COMMAND_HEADER headflag;
	COMMAND_UART_BODY body;

	COMMAND_TAILER tailer;
}__attribute__((__packed__)) CMD_UART_MSG_NONE; //no data

typedef struct {
	COMMAND_HEADER headflag;
	COMMAND_UART_BODY body;

	Uint8 ip_addr[4];
	COMMAND_TAILER tailer;
}__attribute__((__packed__)) CMD_UART_MSG_IP;

typedef struct {
	COMMAND_HEADER headflag;
	COMMAND_UART_BODY body;

	CMD_UART_DATA_CALENDAR data;
	COMMAND_TAILER tailer;
}__attribute__((__packed__)) CMD_UART_MSG_CALENDER;

typedef struct {
	uint32_t addr;
	uint8_t data[CMD_BT_DATA_LEN];
}__attribute__((__packed__)) CMD_UART_BT_DATA; 

typedef struct {
	COMMAND_HEADER headflag;
	COMMAND_UART_BODY body;

	CMD_UART_BT_DATA data;
	COMMAND_TAILER tailer;
}__attribute__((__packed__)) CMD_UART_MSG_MCU_UPGRADE;

typedef struct {
	COMMAND_HEADER headflag;
	COMMAND_UART_BODY body;

	CMD_UART_DATA_ENV data;
	COMMAND_TAILER tailer;
}__attribute__((__packed__)) CMD_UART_MSG_ENV;

//ruandelu 20150618 receive command from pc by mcu and response bgn
typedef struct { 
	Uint8 h7F;
	Uint8 h08;
	Uint8 h99;
	Uint8 hA2;
	Uint8 hB3;
	Uint8 hC4;
	Uint8 h02;
    Uint8 hFF;

	Uint8 hType;
	Uint8 hValue;

	Uint8 hCF;
    Uint8 hResv;

}__attribute__((__packed__)) CMD_UART_PC_REQ; 

typedef struct { 
	Uint8 h7F;
	Uint8 h09;
	Uint8 h99;
	Uint8 hA2;
	Uint8 hB3;
	Uint8 hC4;
	Uint8 h02;
    Uint8 hFF;

	Uint8 hType;
	Uint8 hValue;
	Uint8 hResp;

	Uint8 hCF;
}__attribute__((__packed__)) CMD_UART_PC_RESP;

typedef struct {
	COMMAND_HEADER headflag;
	COMMAND_UART_BODY body;

	CMD_UART_PC_RESP data;
	COMMAND_TAILER tailer;
}__attribute__((__packed__)) CMD_UART_MSG_PC_RESP;

//ruandelu 20150618 receive command from pc by mcu and response end

// ruandelu 20170108 the name and data of png file bgn
typedef struct {
	COMMAND_HEADER headflag;
	COMMAND_UART_BODY body;

	CMD_UART_PC_RESP resp;
	Uint8* pfndata;  // file name or file content
	int    nfnlen;  // lenght of file name or file content
	COMMAND_TAILER tailer;
}__attribute__((__packed__)) CMD_UART_OPS_FILE_RESP;

typedef struct {
	COMMAND_HEADER headflag;
	COMMAND_UART_BODY body;

	CMD_UART_PC_REQ req;
	Uint8* pfndata;  // file name or file content
	int    nfnlen;  // lenght of file name or file content
	COMMAND_TAILER tailer;
}__attribute__((__packed__)) CMD_UART_OPS_FILE_REQ;
// ruandelu 20170108 the name and data of png file end

//ruandelu 20160921 bgn
typedef struct { 
	Uint8 h7F;
	Uint8 hlen; //08,09,=after this and before hCF
	Uint8 h99;
	Uint8 hA2;
	Uint8 hB3;
	Uint8 hC4;
	Uint8 h02;
    Uint8 hFF;
}__attribute__((__packed__)) CMD_UART_SN_CMD_HEAD; //sn==supernova

typedef struct {
	COMMAND_HEADER headflag;
	COMMAND_UART_BODY body;

	//CMD_UART_SN_CMD_REQ req;
	CMD_UART_PC_REQ req;
	
	COMMAND_TAILER tailer;
}__attribute__((__packed__)) CMD_UART_MSG_PC_REQ;

//ruandelu 20160921 end

//ruandelu 20160921 bgn
typedef struct  {
	int ops_screw_fix;
	int ops_cpu_fan_speed;
	int ops_cpu_temperature;
	int ops_board_temperature;
	int ops_run_status;
	int ops_model_num;
	int ops_ID;
}__attribute__((__packed__))  OPS_PARA_TYPE; 
//ruandelu 20160921 end
#endif 
