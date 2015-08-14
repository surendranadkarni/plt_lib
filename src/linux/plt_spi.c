/*
    plt_spi.c
    platform library spi implementation
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

#include "plt_spi_pvt.h"
#include "plt_cfg_pvt.h"
#include <stdio.h>

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


#if (PLT_CFG_SPI_MODULE == PLT_CFG_MODULE_ENABLED )
//{

#define MAP_SPI_CONTEXT_TO_PLT_HND(context) ((plt_handle) context)

#define MAP_PLT_HND_TO_SPI_CONTEXT(hnd) ((spi_context*) hnd)


plt_handle plt_spi_new_device(int dev_id)
{
    char *device = PLT_SPI_CFG_GET_DEVICE_FILE(dev_id);
    spi_context *context = (spi_context*) malloc(sizeof(spi_context));
    
    printf("file to open %s\n", device);
    
    context->fd = open(device, O_RDWR);
    
    if(context->fd < 0)
    {
        free(context);
        return NULL;
    }
    
    return MAP_SPI_CONTEXT_TO_PLT_HND(context);
}

plt_status plt_spi_init(plt_handle hnd)
{
    return 0;
}



static int configure_mode(int fd, const plt_spi_config *cfg)
{
    int ret = 0;
    
    uint08 spi_mode = 0;
    
/*
    if(cfg->lsb_first == true)
    {
        spi_mode |= SPI_LSB_FIRST;
    }
    else
    {
        spi_mode &= (~SPI_LSB_FIRST);
    }
*/
    if(cfg->cs_exists == false)
    {
        spi_mode |= SPI_NO_CS;
    }
    else
    {
        spi_mode &= (~SPI_NO_CS);
        
        if(cfg->cs_state == PLT_SPI_CS_ACTIVE_HIGH)
        {
            spi_mode |= SPI_CS_HIGH;
        }
        else
        {
            spi_mode &= (~SPI_CS_HIGH);
        }
        
    }

    switch(cfg->mode)
    {
        case PLT_SPI_MODE_0:
            spi_mode |= SPI_CPHA;
            spi_mode &= (~SPI_CPOL);
        break;

        case PLT_SPI_MODE_1:
            spi_mode &= (~SPI_CPHA);
            spi_mode &= (~SPI_CPOL);
        break;
        case PLT_SPI_MODE_2:
            spi_mode &= (~SPI_CPHA);
            spi_mode |= SPI_CPOL;
        break;

        case PLT_SPI_MODE_3:
            spi_mode |= SPI_CPHA;
            spi_mode |= SPI_CPOL;
        break;

    }
  
   /* spi_mode =  SPI_CPOL | SPI_CPHA | SPI_CS_HIGH ;  */
    ret = ioctl(fd, SPI_IOC_WR_MODE, &spi_mode);
    assert (ret == 0);
    
    return 0;
}

plt_status plt_spi_configure(plt_handle hnd, const plt_spi_config *cfg)
{
    int ret = 0;
    spi_context *context = MAP_PLT_HND_TO_SPI_CONTEXT(hnd);
    plt_assert(context != NULL);
    uint08 bits = cfg->bits_per_word;
    
    
    configure_mode(context->fd, cfg);
    
    ret = ioctl(context->fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    plt_assert (ret == 0);
    
    ret = ioctl(context->fd, SPI_IOC_WR_MAX_SPEED_HZ, &cfg->clock);
    plt_assert (ret == 0);
    
    context->cfg = *cfg;
    
    return 0;
}

plt_status plt_spi_transfer(plt_handle hnd, uint08 const *tx, uint08 const *rx, int len)
{
    int ret;
    
    spi_context *context = MAP_PLT_HND_TO_SPI_CONTEXT(hnd);
    plt_assert(context != NULL);

    plt_spi_config *cfg = &context->cfg;
    
    struct spi_ioc_transfer tr = {
        .tx_buf = (unsigned long)tx,
        .rx_buf = (unsigned long)rx,
        .len = len,
        .delay_usecs = cfg->delay,
        .speed_hz = cfg->clock,
        .bits_per_word = cfg->bits_per_word,
    };
    
    ret = ioctl(context->fd, SPI_IOC_MESSAGE(1), &tr);
    
    return ret;
}

plt_status plt_spi_delete_device(plt_handle hnd)
{
    spi_context *context = MAP_PLT_HND_TO_SPI_CONTEXT(hnd);
    plt_assert(context != NULL);
    
    free(context);
    
    return 0;
}

#endif//}PLT_CFG_MODULE_ENABLED
 
/*@}*/

//  Local Variables:
//    mode: c++
//    tab-width: 4
//    c-basic-offset: 4
//    indent-tabs-mode: nil
//  End:
