/*
    plt_lib.h
    platform library header
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

#ifndef ___PLT__LIB__H___
#define ___PLT__LIB__H___

#include <datatypes.h>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

int plt_lib_init();

int plt_lib_term();

int plt_lib_get_plt_capability();

int plt_lib_get_system_time();


#define plt_assert(condn) assert(condn)


#ifdef __cplusplus
}
#endif

#endif 
/*@}*/

//  Local Variables:
//    mode: c++
//    tab-width: 4
//    c-basic-offset: 4
//    indent-tabs-mode: nil
//  End: