/*
    plt_i2c_pvt.h
    platform library spi private header
    Copyright (C) <2017> Saurabh Namjoshi <saurabh.namjoshi@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies 
of the Software, and to permit persons to whom the Software is furnished to do 
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
IN THE SOFTWARE.
*/

/** \addtogroup grp_plt_lib Platform Library*/

/*@{*/

#ifndef ___PLT__I2C__PVT__H___
#define ___PLT__I2C__PVT__H___




#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>


typedef unsigned long   uint32;
typedef unsigned short  uint16;
typedef unsigned char   uint08;
typedef void*           plt_handle;
typedef int             plt_status;
typedef unsigned char   bool;


#define false   (0)
#define true    (!false)
#define plt_assert(condn) assert(condn)

int i2c_init(void);
int i2c_term(void);
int i2c_write(UCHAR dev, UCHAR reg, UCHAR* data, int len);
int i2c_read(UCHAR dev, UCHAR reg, UCHAR* data, int len);
int i2c_read16(UCHAR dev, UINT16 reg, UCHAR* data, UINT16 len);
int i2c_write16(UCHAR dev, UINT16 reg, UCHAR* data, UINT16 len);

#endif
