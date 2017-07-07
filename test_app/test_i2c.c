#include <stdio.h>
#include <plt_i2c.h>
#include <plt_lib.h>

plt_handle i2c_hnd;
void readdata(uint08 * Id){

    uint08 write_buff[8+3] = {0};
    uint08 rx_buf[8+3] = {0};
    uint16 addr = 0,reg = 0x03;
    int i = 0;
    int len = 8;
    addr =  0x98;
    
    plt_i2c_read(i2c_hnd, addr, reg, rx_buf, len);
    for(i = 0; i < 8; i++)
    {
        printf("%x\n", rx_buf[i]);
    }    
}

int main()
{
    
    i2c_hnd = plt_i2c_new_device(0);

    printf("HDN %p\n", i2c_hnd);    
    
    
    readdata(NULL);
    
    plt_i2c_delete_device(i2c_hnd);
    return 0;
}
