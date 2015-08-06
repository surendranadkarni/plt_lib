/*
    plt_spi.h
    platform library spi header
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


#ifndef ___PLT__SPI__H___
#define ___PLT__SPI__H___

#include <datatypes.h>

#include <plt_lib.h>

/*SPI MODE based on SPI_CPHA and SPI_CPOL

           +---+   +---+   +---+      
CPOL=0     |   |   |   |   |   |      
        +--+   +---+   +---+   +--+   
                                      
        +--+   +---+   +---+   +--+   
CPOL=1     |   |   |   |   |   |      
           +---+   +---+   +---+      
                                      
    +---+-------+-------+-------+---+
CPHA=0  |  D1   |  D2   | D3    |    
    +---+-------+-------+-------+---+

     
      +---+-------+-------+-------+---+
CPHA=1    |  D1   |  D2   | D3    |    
      +---+-------+-------+-------+---+

Mode    CPOL    CPHA
0       0       1
1       0       0
2       1       1
3       1       1
 
*/



#define PLT_SPI_MODE_0 (0x00)
#define PLT_SPI_MODE_1 (0x01)
#define PLT_SPI_MODE_2 (0x02)
#define PLT_SPI_MODE_3 (0x03)


/*

*/

#define PLT_SPI_CS_ACTIVE_HIGH (0)
#define PLT_SPI_CS_ACTIVE_LOW  (1)

typedef struct _tag_plt_spi_config_
{
    uint32      clock;
    uint08      bits_per_word;
    uint32      delay;
    uint08      mode;
    bool        lsb_first;
    bool        cs_exists;
    uint08      cs_state;
}plt_spi_config;


#ifdef __cplusplus
extern "C" {
#endif

plt_handle plt_spi_new_device(int dev_id);

plt_status plt_spi_init(plt_handle hnd);

plt_status plt_spi_configure(plt_handle hnd, const plt_spi_config *cfg);

plt_status plt_spi_transfer(plt_handle hnd, uint08 const *tx, uint08 const *rx, int len);

plt_status plt_spi_delete_device(plt_handle hnd);

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