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

#ifndef ___PLT__I2C__H___
#define ___PLT__I2C__H___

#include <datatypes.h>
#include <plt_lib.h>

plt_handle plt_i2c_new_device(int dev_id);
plt_status plt_i2c_init(plt_handle hnd);
plt_status plt_i2c_delete_device(plt_handle hnd);
plt_status plt_i2c_write(plt_handle hnd, uint08 dev, uint08 reg, uint08* data, int len);
plt_status plt_i2c_read(plt_handle hnd, uint08 dev, uint08 reg, uint08* data, int len);
plt_status plt_i2c_read16(plt_handle hnd, uint08 dev, uint16 reg, uint08* data, uint16 len);
plt_status plt_i2c_write16(plt_handle hnd, uint08 dev, uint16 reg, uint08* data, uint16 len);

#endif
