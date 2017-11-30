#include "msrv_msd6a648_touch.h"

enum{
    U_MODE_FULL_422 = 0,
    U_MODE_HALF_485 = 1,
    U_MODE_FULL_232 = 2,
};
#define TIOCSERMODE	0x5460

static int uart_tty_fd = -1;
static int usb_hid_fd =-1;
uint8_t g_rvbuf[1024]={0,};//全局接收数据

MSRV_MSD6A648_TOUCH*MSRV_MSD6A648_TOUCH::m_pInstance=NULL;

MSRV_MSD6A648_TOUCH::MSRV_MSD6A648_TOUCH()
{
    memset(&m_pthread, 0, sizeof(pthread_t));
}

MSRV_MSD6A648_TOUCH::~MSRV_MSD6A648_TOUCH()
{
    uart_close(uart_tty_fd);
    hid_device_close(usb_hid_fd);
}

MSRV_MSD6A648_TOUCH *MSRV_MSD6A648_TOUCH::GetInstance()
{
    if(m_pInstance ==NULL)
    {
        m_pInstance = new MSRV_MSD6A648_TOUCH ();
        assert(m_pInstance);
    }
    return m_pInstance;
}

void MSRV_MSD6A648_TOUCH::DestoryInstance()
{
    if(m_pInstance !=NULL)
    {
        delete m_pInstance;
        m_pInstance =NULL;
    }
}
char* MSRV_MSD6A648_TOUCH::convert_hex_to_str(uint8_t *pBuf, const int nLen)
{
	static char    acBuf[20000]    = {0,};
	char           acTmpBuf[10]    = {0,};
	int            ulIndex         = 0;
	int            ulBufLen        = 0;

	if ((NULL == pBuf) || (0 >= nLen))
	{
		return NULL;
	}

	ulBufLen = sizeof(acBuf)/sizeof(acTmpBuf);
	if (ulBufLen >= nLen)
	{
		ulBufLen = nLen;
	}

	memset(acBuf, 0, sizeof(acBuf));
	memset(acTmpBuf, 0, sizeof(acTmpBuf));

	for(ulIndex=0; ulIndex<ulBufLen; ulIndex++)
	{
		//snprintf(acTmpBuf, sizeof(acTmpBuf), "0x%02X ", *(pBuf + ulIndex));
		snprintf(acTmpBuf, sizeof(acTmpBuf), "%02X ", *(pBuf + ulIndex));
		strcat(acBuf, acTmpBuf);
	}
	return acBuf;
}
void MSRV_MSD6A648_TOUCH::start()
{
    string  default_device = DEFAULT_DEVICE;
    const char *uart_tty_device = default_device.data();

    HHT_LOG_DEBUG("=====>operate on device:[%s]\n",uart_tty_device);
    struct termios old_termios,new_termios;

    uart_tty_fd = uart_open(uart_tty_device);
    if(uart_tty_device <0)
    {
        perror("uart_open() failed.\n");
        HHT_LOG_ERROR("uart_open() failed:[%d].\n\n",uart_tty_fd);
        return ;
    }
    else
    {
        HHT_LOG_DEBUG("uart_open() success:[%d].\n\n",uart_tty_fd);
    }

    ioctl(uart_tty_fd,TIOCSERMODE,U_MODE_FULL_232);
    get_termios(uart_tty_fd,&old_termios);
    HHT_LOG_DEBUG("old termios:\n");
    show_termios(&old_termios);

    sleep_ms(100);
    uart_config(uart_tty_fd,DEFAULT_BAUD_RATE,'n',8,1);//配置tty信息

    get_termios(uart_tty_fd,&new_termios);
    HHT_LOG_DEBUG("new termios:\n");
    show_termios(&new_termios);
    sleep_ms(1000);
    //创建线程
    int result= pthread_create(&m_pthread,NULL,Run,(void*)this);
    if(result==0)
    {
          HHT_LOG_DEBUG("pthread_create() success [%d].\n",result);
    }
    else
    {
         HHT_LOG_ERROR("pthread_create failed [%d].\n",result);
    }
    sleep_ms(1000);
    //主线程阻塞
    while (1)
    {
        sleep_ms(10);
    }
    hid_device_close(usb_hid_fd);
    uart_close(uart_tty_fd);
}

void *MSRV_MSD6A648_TOUCH::Run(void *arg)
{
    MSRV_MSD6A648_TOUCH *msrv = (MSRV_MSD6A648_TOUCH*)arg;
    uint8_t m_rvbuf[64]={0};
    int usb_hid =-1;
    usb_hid = msrv->hid_device_open();
    if(usb_hid<0)
    {
        HHT_LOG_ERROR("open hid drv device failed [%d].\n",usb_hid);
        return ((void*)0);
    }
    else
    {
        HHT_LOG_DEBUG("===>open hid drv device status:[%d]\n",usb_hid);
    }
    //写入指令
    msrv->hid_device_write(usb_hid_fd,usb_hid_off_command);
    HHT_LOG_DEBUG("send usb-off commands.\n");
    msrv->hid_device_write(usb_hid_fd,usb_hid_on_command);
    HHT_LOG_DEBUG("send usb-on commands.\n");

    while (1)
    {
        //校验从HID接收的数据
#if 1
       int buflen = msrv->check_incoming_data(m_rvbuf,sizeof(m_rvbuf));
       HHT_LOG_DEBUG("check incoming data len: %d\n",buflen);
       if(buflen==0)
       {
            ;
       }
       else if(buflen==sizeof(m_rvbuf))
       {
#if 1
            HHT_LOG_DEBUG("read data from hid drv: \n");
            for (int i = 0; i < buflen; i++)
            {
                printf("%02x ", m_rvbuf[i]);
                if ((i % 16) == 15)
                    printf("\n");
            }
#endif
           //处理接收到的合法数据
            msrv->handle_incoming_data(m_rvbuf,buflen);
            memset(m_rvbuf,0,sizeof(m_rvbuf));
       }
       else
       {
          HHT_LOG_ERROR("incoming data len: [%d]\n",buflen);
          memset(m_rvbuf,0,sizeof(m_rvbuf));
       }
#else
        int size = msrv->hid_device_read(usb_hid_fd,m_rvbuf);
        if(size >0)
        {
            HHT_LOG_DEBUG("read data from hid drv: \n");
            for (int i = 0; i < size; i++)
            {
                printf("%02x ", m_rvbuf[i]);
                if ((i % 16) == 15)
                    printf("\n");
            }
            //读取该内容并做解析
            //-------------------------------------------------------
            //解析将数据通过串口发送只MCU

            memset(m_rvbuf,0,sizeof(m_rvbuf));
        }
        else
        {
            ;
        }
#endif
        msrv->sleep_ms(200);
    }
    return ((void*)0);
}

int MSRV_MSD6A648_TOUCH::hid_device_open()
{
    usb_hid_fd = open(HID_TOUCH_DEVICE,O_RDWR);

    return usb_hid_fd;
}

void MSRV_MSD6A648_TOUCH::hid_device_close(int hid_device)
{
    if (hid_device >0)
    {
        close(hid_device);
    }
}

int MSRV_MSD6A648_TOUCH::hid_device_write(int device_fd,uint8_t *cmd)
{
    int size = write(device_fd,cmd,sizeof(cmd));
    return size;
}

int MSRV_MSD6A648_TOUCH::hid_device_read(int device_fd,uint8_t *rvbuf)
{
    int size = read(device_fd,rvbuf,sizeof(rvbuf));
    return size;
}

int MSRV_MSD6A648_TOUCH::check_incoming_data(uint8_t *rvbuf, int len)
{
    //校验从HID接收的一帧数据
    int nbr_received_bytes = 0;
    nbr_received_bytes = read(usb_hid_fd,rvbuf,len);

    return nbr_received_bytes;
}

void MSRV_MSD6A648_TOUCH::handle_incoming_data(uint8_t *rvbuf, int len)
{
    //梳理从HID接收到的数据,通过串口发送一帧数据给MCU
     Report_touch_info *m_info =get_report_info(rvbuf,len);
     transfer_report_info_to_uart(m_info);
     if (m_info != NULL) //必须释放先前开辟的内存空间
     {
         free(m_info);
         m_info = NULL;
     }
     return;
}

Report_touch_info *MSRV_MSD6A648_TOUCH::get_report_info(uint8_t *rvbuf, int len)
{
    //rvbuf为64bytes完整一帧数据
    Report_touch_info *m_report;
    m_report = (struct _Report_touch_info*)malloc(sizeof(struct _Report_touch_info));
    memset(m_report,0,sizeof(struct _Report_touch_info));
    m_report->report_id =rvbuf[0];
    HHT_LOG_DEBUG("\n====>report->report_id:[0x%02x]\n", m_report->report_id);
    int i;
    for(i=0;i<MAX_POINTS_PER_FRAME;i++)
    {
        Touch_point_info *info = (struct _Touch_point_info*)(&rvbuf[i*10+1]);
        memcpy(&m_report[i],info,sizeof(struct _Touch_point_info));
        HHT_LOG_DEBUG("\n====>point[%d]: %s\n",i,convert_hex_to_str(&rvbuf[i*10+1],10));
    }

    m_report->nr = rvbuf[10*(i)+1];
    
    HHT_LOG_DEBUG("\n====>report->nr:[0x%02x]\n",m_report->nr);

    memcpy(m_report->reserved,&rvbuf[10*(i)+2],2);

    HHT_LOG_DEBUG("\n====>report->reserved:[0x%02x 0x%02x]\n", rvbuf[10*(i)+2], rvbuf[10*(i)+3]);
    return m_report;
}

void MSRV_MSD6A648_TOUCH::transfer_report_info_to_uart(Report_touch_info *info)
{
    write(uart_tty_fd,info,sizeof(Report_touch_info));
}


void MSRV_MSD6A648_TOUCH::sleep_ms(unsigned int msec)
{
    struct timeval tval;
    tval.tv_sec = msec/1000;
    tval.tv_usec = (msec*1000)%1000000;
    select(0,NULL,NULL,NULL,&tval);
}

int MSRV_MSD6A648_TOUCH::m_strlen(uint8_t *s)
{
    int i=0;
    while(*s!='\0')
    {
        i++;
        s++;
    }
    return i;
}

void MSRV_MSD6A648_TOUCH::show_termios(const termios *s)
{
    if( s )
    {
#if 0
        printf("speed=%d ", get_speed(s));
        printf("parity=%c ", get_parity(s));
        printf("bsize=%d ", get_bsize(s));
        printf("stop=%d\n", get_stop(s));
#endif
        HHT_LOG_DEBUG("termios settings: speed=[%d] parity=[%c] bsize=[%d] stop=[%d]\n\n",get_speed(s),get_parity(s),get_bsize(s),get_stop(s));
    }
}

int MSRV_MSD6A648_TOUCH::get_termios(int fd, termios *s)
{
    if( -1 == fd || 0 == s )
    {
        return -1;
    }
    return tcgetattr(fd, s);
}

int MSRV_MSD6A648_TOUCH::set_termios(int fd, const termios *s)
{
    if( -1 == fd || 0 == s )
    {
        return -1;
    }
    return tcsetattr(fd, TCSANOW, s);
}

int MSRV_MSD6A648_TOUCH::baud_to_speed(int baud)
{
    switch( baud )
    {
    case B1200:
        return 1200;
    case B2400:
        return 2400;
    case B4800:
        return 4800;
    case B9600:
        return 9600;
    case B19200:
        return 19200;
    case B38400:
        return 38400;
    case B57600:
        return 57600;
    case B115200:
        return 115200;
    case B921600:
        return 921600;
    }
    return 0;
}

int MSRV_MSD6A648_TOUCH::get_speed(const termios *s)
{
    if( s )
    {
        return baud_to_speed(s->c_cflag & CBAUD);
    }
    return -1;
}

int MSRV_MSD6A648_TOUCH::get_ispeed(const termios *s)
{
    if( s )
    {
        return baud_to_speed(s->c_iflag & CBAUD);
    }
    return -1;
}

int MSRV_MSD6A648_TOUCH::get_ospeed(const termios *s)
{
    if( s )
    {
        return baud_to_speed(s->c_oflag & CBAUD);
    }
    return 0;
}

int MSRV_MSD6A648_TOUCH::get_bsize(const termios *s)
{
    if( s )
    {
        switch(s->c_cflag & CSIZE)
        {
        case CS5:
            return 5;
        case CS6:
            return 6;
        case CS7:
            return 7;
        case CS8:
            return 8;
        }
    }
    return -1;
}

char MSRV_MSD6A648_TOUCH::get_parity(const termios *s)
{
    if( s )
    {
        if( s->c_cflag & PARENB )
        {
            if( s->c_cflag & PARODD )
            {
                return 'O';
            }
            else
            {
                return 'E';
            }
        }
        return 'N';
    }
    return -1;
}

int MSRV_MSD6A648_TOUCH::get_stop(const termios *s)
{
    if( s )
    {
        if( s->c_cflag & CSTOPB )
        {
            return 2;
        }
        return 1;
    }
    return -1;
}

int MSRV_MSD6A648_TOUCH::speed_to_baud(int speed)
{
    switch(speed)
    {
    case 1200:
        return B1200;
    case 2400:
        return B2400;
    case 4800:
        return B4800;
    case 9600:
        return B9600;
    case 19200:
        return B19200;
    case 38400:
        return B38400;
    case 57600:
        return B57600;
    case 115200:
        return B115200;
    case 921600:
        return B921600;
    }
    return B9600;
}

int MSRV_MSD6A648_TOUCH::set_speed(termios *s, int speed)
{
    if( s )
    {
        s->c_cflag &= ~CBAUD;
        s->c_cflag |= speed_to_baud(speed);
        return 0;
    }
    return -1;
}

int MSRV_MSD6A648_TOUCH::set_ispeed(termios *s, int speed)
{
    if( s )
    {
        return cfsetispeed(s, speed_to_baud(speed) );
    }
    return -1;
}

int MSRV_MSD6A648_TOUCH::set_ospeed(termios *s, int speed)
{
    if( s )
    {
        return cfsetospeed(s, speed_to_baud(speed) );
    }
    return -1;
}

int MSRV_MSD6A648_TOUCH::set_bsize(termios *s, int bsize)
{
    if( s )
    {
        s->c_cflag &= ~CSIZE;
        switch( bsize )
        {
        case 5:
            s->c_cflag |= CS5;
            break;
        case 6:
            s->c_cflag |= CS6;
            break;
        case 7:
            s->c_cflag |= CS7;
            break;
        case 8:
            s->c_cflag |= CS8;
            break;
        }
        return 0;
    }
    return -1;
}

int MSRV_MSD6A648_TOUCH::set_parity(termios *s, char parity)
{
    if( s )
    {
        switch(parity)
        {
        case 'n':
        case 'N':
            s->c_cflag &= ~PARENB;
            break;
        case 'o':
        case 'O':
            s->c_cflag |= PARENB;
            s->c_cflag |= PARODD;
            break;
        case 'e':
        case 'E':
            s->c_cflag |= PARENB;
            s->c_cflag &= ~PARODD;
            break;
        }
        return 0;
    }
    return -1;
}

int MSRV_MSD6A648_TOUCH::set_stop(termios *s, int stop)
{
    if( s )
    {
        if( 1 == stop )
        {
            s->c_cflag &= ~CSTOPB;
        }
        else
        {
            s->c_cflag |= CSTOPB;
        }
        return 0;
    }
    return -1;
}

int MSRV_MSD6A648_TOUCH::enable_read(termios *s)
{
    if( s )
    {
        s->c_cflag |= CREAD;
        return 0;
    }
    return -1;
}

int MSRV_MSD6A648_TOUCH::disable_read(termios *s)
{
    if( s )
    {
        s->c_cflag &= ~CREAD;
        return 0;
    }
    return -1;
}

int MSRV_MSD6A648_TOUCH::enable_flow_control(termios *s)
{
    if( s )
    {
        s->c_cflag |= CRTSCTS;
        return 0;
    }
    return -1;
}

int MSRV_MSD6A648_TOUCH::disable_flow_control(termios *s)
{
    if( s )
    {
        s->c_cflag &= ~CRTSCTS;
        return 0;
    }
    return -1;
}

int MSRV_MSD6A648_TOUCH::uart_open(const char *path)
{
    if( path )
    {
        return open(path, O_RDWR);
    }
    return -1;
}

int MSRV_MSD6A648_TOUCH::uart_config(int fd, int baud, char parity, int bsize, int stop)
{
    if( fd < 0 )
    {
        return -1;
    }
    else
    {
        struct termios new_termios = {0};

        bzero(&new_termios, sizeof(new_termios));
        if( set_speed(&new_termios, baud))
        {
            return -2;
        }
        if( set_parity(&new_termios, parity))
        {
            return -3;
        }
        if( set_bsize(&new_termios, bsize))
        {
            return -4;
        }
        if( set_stop(&new_termios, stop))
        {
            return -5;
        }
        enable_read(&new_termios);
        disable_flow_control(&new_termios);
        if( set_termios(fd, &new_termios))
        {
            return -6;
        }
    }
    return 0;
}

int MSRV_MSD6A648_TOUCH::uart_read(int fd, char *buf, int len)
{
    if( fd < 0 || 0 == buf || len < 1 )
    {
        return -1;
    }
    return read(fd, buf, len);
}

int MSRV_MSD6A648_TOUCH::uart_write(int fd, const char *data, int len)
{
    if( fd < 0 || 0 == data || len < 1 )
    {
        return -1;
    }
    return write(fd, data, len);
}

int MSRV_MSD6A648_TOUCH::uart_close(int fd)
{
    return close(fd);
}
