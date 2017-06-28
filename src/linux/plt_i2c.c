#include <plt_i2c_pvt.h>

#define MAP_I2C_CONTEXT_TO_PLT_HND(context) ((plt_handle) context)

#define MAP_PLT_HND_TO_I2C_CONTEXT(hnd) ((i2c_context*) hnd)


plt_handle i2c_init(int dev_id) 
{
    char *i2c_dev = PLT_SPI_CFG_GET_DEVICE_FILE(dev_id);
    i2c_context *context = (i2c_context*) malloc(sizeof(i2c_context));
    pthread_mutex_lock(&context->i2c_mutex);
    context->fd = open(i2c_dev, O_RDWR);
    if (adapter < 0) {
        perror(i2c_dev);
        exit(-1);
    }

    pthread_mutex_unlock(&context->i2c_mutex);
    
    return MAP_I2C_CONTEXT_TO_PLT_HND(context);
}

plt_status i2c_term(plt_handle hnd) 
{
    i2c_context *context = MAP_PLT_HND_TO_I2C_CONTEXT(hnd);
    plt_assert(context != NULL);
    close(context->fd);
    free(context);

    return 0;
}

plt_status i2c_write(plt_handle hnd, uint08 dev, uint08 reg, uint08* data, int len) 
{
    plt_status ret;
    if(len == 0)
        return -1;

    i2c_context *context = MAP_PLT_HND_TO_I2C_CONTEXT(hnd);
    plt_assert(context != NULL);

    uint08* buffer = malloc(sizeof(uint08)*len + 1);
    buffer[0] = reg;
    memcpy(&buffer[1], data, len);

    pthread_mutex_lock(&context->i2c_mutex);

    ret = ioctl(context->fd, I2C_SLAVE, dev >> 1);
    if(ret < 0) 
    {
        perror("Could not write I2C slave address");
        goto out;
    }

    ret = write(adapter, buffer, len+1);
    if(ret != len+1) 
    {
        perror("Write data fail");
        goto out;
    }

    ret = 0;
out:
    pthread_mutex_unlock(&context->i2c_mutex);
    free(buffer);

    return ret;
}

plt_status i2c_read(plt_handle hnd, uint08 dev, uint08 reg, uint08* data, int len) 
{
    plt_status ret;
    struct i2c_rdwr_ioctl_data i2c_data;
    struct i2c_msg msg[2];
    char tmp[2];
    i2c_context *context = MAP_PLT_HND_TO_I2C_CONTEXT(hnd);
    plt_assert(context != NULL);

    i2c_data.msgs = msg;
    i2c_data.nmsgs = 2;     // two i2c_msg

    tmp[0] = reg;
    i2c_data.msgs[0].addr = dev >> 1;
    i2c_data.msgs[0].flags = 0;     // write
    i2c_data.msgs[0].len = 1;       // only one byte
    i2c_data.msgs[0].buf = (uint08 *)tmp;

    i2c_data.msgs[1].addr = dev >> 1;
    i2c_data.msgs[1].flags = I2C_M_RD;      // read command
    i2c_data.msgs[1].len = len;
    i2c_data.msgs[1].buf = (uint08 *)data;

    pthread_mutex_lock(&context->i2c_mutex);

    ret = ioctl(context->fd, I2C_RDWR, &i2c_data);
    if (ret < 0) 
    {
        perror("read data fail");
        goto out;
    }

    ret = len;
out:
    pthread_mutex_unlock(&context->i2c_mutex);

    return ret;
}

plt_status i2c_read16(plt_handle hnd, uint08 dev, uint16 reg, uint08* data, uint16 len) 
{
    plt_status ret;
    struct i2c_rdwr_ioctl_data i2c_data;
    struct i2c_msg msg[2];
    char tmp[2];
    i2c_context *context = MAP_PLT_HND_TO_I2C_CONTEXT(hnd);
    plt_assert(context != NULL);

    i2c_data.msgs = msg;
    i2c_data.nmsgs = 2;     // two i2c_msg

    tmp[0] = (reg >> 8) & 0xFF;
    tmp[1] = reg & 0xFF;
    i2c_data.msgs[0].addr = dev >> 1;
    i2c_data.msgs[0].flags = 0;     // write
    i2c_data.msgs[0].len = 2;       // 2 address bytes
    i2c_data.msgs[0].buf = (uint08 *)tmp;

    i2c_data.msgs[1].addr = dev >> 1;
    i2c_data.msgs[1].flags = I2C_M_RD;      // read command
    i2c_data.msgs[1].len = len;
    i2c_data.msgs[1].buf = (uint08 *)data;

    pthread_mutex_lock(&context->i2c_mutex);

    ret = ioctl(context->fd, I2C_RDWR, &i2c_data);
    if (ret < 0) 
    {
        perror("read data fail");
        goto out;
    }

    ret = len;
out:
    pthread_mutex_unlock(&context->i2c_mutex);

    return ret;
}

plt_status i2c_write16(plt_handle hnd, uint08 dev, uint16 reg, uint08* data, uint16 len) 
{
    plt_status ret;
    if(len == 0)
        return;

    i2c_context *context = MAP_PLT_HND_TO_I2C_CONTEXT(hnd);
    plt_assert(context != NULL);

    uint08* buffer = malloc(sizeof(uint08)*len + 2);
    buffer[0] = (reg >> 8) & 0xFF;
    buffer[1] = reg & 0xFF;
    memcpy(&buffer[2], data, len);

    pthread_mutex_lock(&context->i2c_mutex);

    ret = ioctl(context->fd, I2C_SLAVE, dev >> 1);
    if(ret < 0) 
    {
        perror("Could not write I2C slave address");
        goto out;
    }

    ret = write(adapter, buffer, len+2);
    if(ret != len+2) 
    {
        perror("Write data fail");
        goto out;
    }

    ret = 0;
out:
    pthread_mutex_unlock(&context->i2c_mutex);
    free(buffer);

    return ret;
}
