#include <plt_i2c_pvt.h>

#define MAP_I2C_CONTEXT_TO_PLT_HND(context) ((plt_handle) context)



int adapter;
pthread_mutex_t i2c_mutex;

int i2c_init(int dev_id) 
{
    char adaptername[20];

    pthread_mutex_lock(&i2c_mutex);
    snprintf(adaptername, 19, "/dev/i2c-%d", dev_id);
    adapter = open(adaptername, O_RDWR);
    if (adapter < 0) {
        perror(adaptername);
        exit(-1);
    }

    pthread_mutex_unlock(&i2c_mutex);
    
    return MAP_I2C_CONTEXT_TO_PLT_HND(adapter);
}

int i2c_term(void) {
    close(adapter);
    return 0;
}

int i2c_write(UCHAR dev, UCHAR reg, UCHAR* data, int len) {
    int ret;
    if(len == 0)
        return -1;

    UCHAR* buffer = malloc(sizeof(UCHAR)*len + 1);
    buffer[0] = reg;
    memcpy(&buffer[1], data, len);

    pthread_mutex_lock(&i2c_mutex);

    ret = ioctl(adapter, I2C_SLAVE, dev >> 1);
    if(ret < 0) {
        perror("Could not write I2C slave address");
        goto out;
    }

    ret = write(adapter, buffer, len+1);
    if(ret != len+1) {
        perror("Write data fail");
        goto out;
    }

    ret = 0;
out:
    pthread_mutex_unlock(&i2c_mutex);
    free(buffer);

    return ret;
}

int i2c_read(UCHAR dev, UCHAR reg, UCHAR* data, int len) {
    int ret;
    struct i2c_rdwr_ioctl_data i2c_data;
    struct i2c_msg msg[2];
    char tmp[2];

    i2c_data.msgs = msg;
    i2c_data.nmsgs = 2;     // two i2c_msg

    tmp[0] = reg;
    i2c_data.msgs[0].addr = dev >> 1;
    i2c_data.msgs[0].flags = 0;     // write
    i2c_data.msgs[0].len = 1;       // only one byte
    i2c_data.msgs[0].buf = (__u8 *)tmp;

    i2c_data.msgs[1].addr = dev >> 1;
    i2c_data.msgs[1].flags = I2C_M_RD;      // read command
    i2c_data.msgs[1].len = len;
    i2c_data.msgs[1].buf = (__u8 *)data;

    pthread_mutex_lock(&i2c_mutex);

    ret = ioctl(adapter, I2C_RDWR, &i2c_data);
    if (ret < 0) {
        perror("read data fail");
        goto out;
    }

    ret = len;
out:
    pthread_mutex_unlock(&i2c_mutex);

    return ret;
}

int i2c_read16(UCHAR dev, UINT16 reg, UCHAR* data, UINT16 len) {
    int ret;
    struct i2c_rdwr_ioctl_data i2c_data;
    struct i2c_msg msg[2];
    char tmp[2];

    i2c_data.msgs = msg;
    i2c_data.nmsgs = 2;     // two i2c_msg

    tmp[0] = (reg >> 8) & 0xFF;
    tmp[1] = reg & 0xFF;
    i2c_data.msgs[0].addr = dev >> 1;
    i2c_data.msgs[0].flags = 0;     // write
    i2c_data.msgs[0].len = 2;       // 2 address bytes
    i2c_data.msgs[0].buf = (__u8 *)tmp;

    i2c_data.msgs[1].addr = dev >> 1;
    i2c_data.msgs[1].flags = I2C_M_RD;      // read command
    i2c_data.msgs[1].len = len;
    i2c_data.msgs[1].buf = (__u8 *)data;

    pthread_mutex_lock(&i2c_mutex);

    ret = ioctl(adapter, I2C_RDWR, &i2c_data);
    if (ret < 0) {
        perror("read data fail");
        goto out;
    }

    ret = len;
out:
    pthread_mutex_unlock(&i2c_mutex);

    return ret;
}

int i2c_write16(UCHAR dev, UINT16 reg, UCHAR* data, UINT16 len) {
    int ret;
    if(len == 0)
        return;

    UCHAR* buffer = malloc(sizeof(UCHAR)*len + 2);
    buffer[0] = (reg >> 8) & 0xFF;
    buffer[1] = reg & 0xFF;
    memcpy(&buffer[2], data, len);

    pthread_mutex_lock(&i2c_mutex);

    ret = ioctl(adapter, I2C_SLAVE, dev >> 1);
    if(ret < 0) {
        perror("Could not write I2C slave address");
        goto out;
    }

    ret = write(adapter, buffer, len+2);
    if(ret != len+2) {
        perror("Write data fail");
        goto out;
    }

    ret = 0;
out:
    pthread_mutex_unlock(&i2c_mutex);
    free(buffer);

    return ret;
}
