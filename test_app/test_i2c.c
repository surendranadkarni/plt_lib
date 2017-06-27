#include <stdio.h>
#include <plt_i2c.h>

plt_handle i2c_hnd;
void readdata(uint08 * Id){

    uint08 write_buff[8+3] = {0};
    uint08 rx_buf[8+3] = {0};
    uint16 addr = 0,reg = 0x03;
    int i = 0;
    int len = 8;
    addr =  0x98;
    
    i2c_read(i2c_hnd, addr, reg, rx_buf, len);
    for(i = 0; i < 8; i++)
    {
        printf("%x\n", rx_buf[i]);
    }    
}

int main()
{
    
    i2c_hnd = i2c_init(0);

    printf("HDN %p\n", i2c_hnd);    
    
    
    readdata(NULL);
    
    i2c_term(i2c_hnd);
    return 0;
}
