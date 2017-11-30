/**
 *@brief  msd6s648-touch
 *@author yangqian@honghe-tech.com
 *@date   2017/12/01
 */
#ifndef MSRV_MSD6A648_TOUCH_H
#define MSRV_MSD6A648_TOUCH_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>

/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>

#include <termios.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>
#include <ctime>
#include <pthread.h>
#include <string.h>

#include <iostream>
using namespace std;

//************************************************************************************************
#define DBG_UART_PRT   1

#if DBG_UART_PRT

#define HHT_LOG_DEBUG(msg...)\
    do{\
        { \
            printf(msg);\
        } \
    }while(0)

#else
    #define HHT_LOG_DEBUG(fmt, ...)
#endif

#define DBG_UART_ERROR   1

#if DBG_UART_ERROR

#define HHT_LOG_ERROR(msg...)\
    do{\
        { \
            printf("\n>>{%s}>>>[%s()]>>>(%d);\n",__FILE__,__func__,__LINE__);\
            printf(msg);\
        } \
    }while(0)

#else
    #define HHT_LOG_ERROR(fmt, ...)
#endif

#if 0
#define DEFAULT_DEVICE   "/dev/ttyUSB0"
#define DEFAULT_BAUD_RATE   921600
#else
#define DEFAULT_DEVICE     "/dev/ttyS1"
#define DEFAULT_BAUD_RATE   115200
#endif

#define HID_TOUCH_DEVICE  "/dev/isolution_touch"

#define UNUSED(expr) do { (void)(expr); } while (0)

//************************************************************************************************
static unsigned char  usb_hid_off_command[64]={6,6,6,0};
static unsigned char  usb_hid_on_command[64]={6,6,6,1};

//************************************************************************************************
class MSRV_MSD6A648_TOUCH
{
public:
    MSRV_MSD6A648_TOUCH();
    ~MSRV_MSD6A648_TOUCH();
    static  MSRV_MSD6A648_TOUCH* GetInstance();
    static  void DestoryInstance();
    //公共函数接口
	char*convert_hex_to_str(unsigned char *pBuf, const int nLen);
    void sleep_ms(unsigned int msec);
    //***********************************************************
    //termios操作
    void show_termios(const struct termios *s);

    int get_termios(int fd, struct termios *s);
    int set_termios(int fd, const struct termios *s);

    int baud_to_speed(int baud);
    int get_speed(const struct termios *s);
    int get_ispeed(const struct termios *s);
    int get_ospeed(const struct termios *s);
    int get_bsize(const struct termios *s);
    char get_parity(const struct termios *s);
    int get_stop(const struct termios *s);

    int speed_to_baud(int speed);
    int set_speed(struct termios *s, int speed);
    int set_ispeed(struct termios *s, int speed);
    int set_ospeed(struct termios *s, int speed);
    int set_bsize(struct termios *s, int bsize);
    int set_parity(struct termios *s, char parity);
    int set_stop(struct termios *s, int stop);
    int enable_read(struct termios *s);
    int disable_read(struct termios *s);
    int enable_flow_control(struct termios *s);
    int disable_flow_control(struct termios *s);
    //串口操作
    int uart_open(const char *path);
    int uart_config(int fd, int baud, char parity, int bsize, int stop);
    int uart_read(int fd, char *buf, int len);
    int uart_write(int fd, const char *data, int len);
    int uart_close(int fd);
    //******************************************************************
    //读写HID驱动设备
    int hid_device_open();
    int hid_device_write(int device_fd,unsigned char *cmd);
    int hid_device_read(int device_fd,unsigned char *rvbuf);
    //校验解析hid触摸数据
    int check_incoming_data(unsigned char* rvbuf,int len);
    void handle_incoming_data(unsigned char*rvbuf,int len);


    //******************************************************************
    //外部调用启动接口
    void start();
private:
    static  MSRV_MSD6A648_TOUCH *m_pInstance;
    static  void *Run(void*arg);
    pthread_t m_pthread;
};

#endif // MSRV_MSD6A648_TOUCH_H
