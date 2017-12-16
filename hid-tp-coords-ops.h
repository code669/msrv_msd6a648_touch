#ifndef __HID_TP_COORDS_OPS_H
#define __HID_TP_COORDS_OPS_H

//ruandelu 20150826 ops coords bgn
#if 1
#define MAX_POINT_COUNT     10

typedef struct __attribute__((packed)) _touch_point
{
    unsigned char    penid;
    unsigned char    status;
    unsigned short    x_ops;
    unsigned short    y_ops;
	//ruandelu 20161227 transfer pos attribute of w,h,p,r bgn
	unsigned short    w;
    unsigned short    h;
    unsigned short    p;
    unsigned short    r;	
    //unsigned short    x_android;
    //unsigned short    y_android;
    //ruandelu 20161227 transfer pos attribute of w,h,p,r end	
}touch_point;

typedef struct
{
	touch_point item[MAX_POINT_COUNT];
}hht_one_frame;
#endif
//ruandelu 20150826 ops coords end
//ruandelu 20160408 transfer pen and touch pos to ops bgn
typedef struct __attribute__((packed)) _pen_point
{
    unsigned char    id;
    unsigned char    state;
    unsigned short    x_ops;
    unsigned short    y_ops;
    unsigned short    w;
    unsigned short    h;
    unsigned short    p;
    unsigned short    r;
}pen_point;

typedef union
{
	pen_point pen;
	hht_one_frame touch;
}un_touch_trans;

#define defTypeTouch 0x01
#define defTypePen   0x02

typedef struct __attribute__((packed)) _trans_point_data
{
	unsigned short type;
	unsigned short npt;
	un_touch_trans un_data;
}trans_point_data;

//ruandelu 20160408 transfer pen and touch pos to ops end

// add by yangqain
typedef struct __attribute__((packed)) _uart_touch_w_h_pt
{
    unsigned char id;
    unsigned char status;

    //uart_id_down id_down;
    unsigned short x;
    unsigned short y;

    //ruandelu 20170205 w/h not transfer bgn
    //unsigned short w;
    //unsigned short h;
    //ruandelu 20170205 w/h not transfer end

    //unsigned char radius;
    //unsigned radius		:5;	//pen id
    //unsigned down :3; 	//up/down

}uart_touch_w_h_pt;

#endif
