#include <stdio.h>
#include <plt_lib.h>
#include <plt_spi.h>


plt_spi_config cfg = 
{
    .clock = 1000000,
    .bits_per_word = 8,
    .mode = PLT_SPI_MODE_0,
    .lsb_first = true,
    .cs_exists = true,
    .cs_state = PLT_SPI_CS_ACTIVE_LOW,
};

uint08 tx_buf[2] = {0x00, 0x01};
uint08 rx_buf[2] = {0x00};

int main()
{
    plt_handle spi_hnd;
    plt_lib_init();
    
    spi_hnd = plt_spi_new_device(0);
    
    plt_spi_init(spi_hnd);
    
    plt_spi_configure(spi_hnd, &cfg);
    
    plt_spi_transfer(spi_hnd, tx_buf, rx_buf, 2);
    
    plt_lib_term();
    return 0;
}