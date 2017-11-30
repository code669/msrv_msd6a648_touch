/**
 *@brief  msd6s648-touch
 *@author yangqian@honghe-tech.com
 *@date   2017/12/01
 */
#ifndef FFPROTOCOL_INFO
#define FFPROTOCOL_INFO

#include <string.h>
#include "stdint.h"

typedef struct __attribute__((packed)) _Touch_point_info
{
       uint8_t  down;
       uint8_t  id;
       uint16_t x;
       uint16_t y;
       uint16_t width;
       uint16_t height;
}Touch_point_info;

typedef struct __attribute__((packed)) _Report_touch_info
{
       uint8_t  report_id;
       Touch_point_info m_point[6];
       uint8_t  nr;
       uint8_t  reserved[2];
}Report_touch_info;



#endif // FFPROTOCOL_INFO

