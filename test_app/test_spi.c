#include <stdio.h>
#include <plt_lib.h>
#include <plt_spi.h>
#include <plt_cfg.h>

plt_spi_config cfg = 
{
    .clock = 1000000,
    .bits_per_word = 8,
    .mode = PLT_SPI_MODE_0,
    .lsb_first = true,
    .cs_exists = true,
    .cs_state = PLT_SPI_CS_ACTIVE_LOW,
};


plt_handle spi_hnd;
void readdata(uint08 * Id){

    uint08 write_buff[8+3] = {0};
    uint08 rx_buf[8+3] = {0};
    uint16 addr = 0;
    int i = 0;
    addr =  8;
    
    
    write_buff[0] = 0x03; //read
    write_buff[1] = (uint08)((addr & 0xFF00) >> 8);
    write_buff[2] = (uint08)((addr & 0x00FF) >> 0);

    plt_spi_transfer(spi_hnd, write_buff, rx_buf, 8+3);

    for(i = 0; i < 8; i++)
    {
        printf("%x\n", rx_buf[i]);
    }    
}

int main()
{
    plt_lib_init();
    
    spi_hnd = plt_spi_new_device(0);

    printf("HDN %p\n", spi_hnd);    
    plt_spi_init(spi_hnd);
    
    plt_spi_configure(spi_hnd, &cfg);
    
 // plt_spi_transfer(spi_hnd, tx_buf, rx_buf, 2);
    readdata(NULL);
    
    plt_lib_term();
    return 0;
}
