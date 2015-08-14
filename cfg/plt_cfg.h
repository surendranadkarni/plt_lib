/*
    plt_cfg.h
    platform library plt cfg header
    Copyright (C) <2013> Surendra Nadkarni <suren.nadkarni@gmail.com>

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

#ifndef ___PLT__CFG__H___
#define ___PLT__CFG__H___

#define PLT_CFG_SPI_HOST_CNT  (1)

#define PLT_CFG_SPI_HOST_ID_0 (0x00)

#define PLT_CFG_MODULE_ENABLED              (0x01)
#define PLT_CFG_MODULE_DISABLED             (0x00)

/*Enable Indivisual Module*/
#define PLT_CFG_LOGGER_MODULE               PLT_CFG_MODULE_ENABLED
#define PLT_CFG_I2C_MODULE                  PLT_CFG_MODULE_ENABLED
#define PLT_CFG_SPI_MODULE                  PLT_CFG_MODULE_ENABLED
#define PLT_CFG_SYSTEM_TIMER_MODULE         PLT_CFG_MODULE_ENABLED




#endif
 
/*@}*/

//  Local Variables:
//    mode: c++
//    tab-width: 4
//    c-basic-offset: 4
//    indent-tabs-mode: nil
//  End:
