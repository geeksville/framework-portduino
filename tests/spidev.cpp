/*
* Sample application that makes use of the SPIDEV interface
* to access an SPI slave device. Specifically, this sample
* reads a Device ID of a JEDEC-compliant SPI Flash device.
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
    int fd;
    struct spi_ioc_transfer xfer[2];
    unsigned char buf[32], *bp;
    int len, status;

    const char *name = "/dev/spidev0.0";
    fd = open(name, O_RDWR);
    if (fd < 0)
    {
        perror("open");
        return 1;
    }

    /*
    We want default SPI mode 0, MSB first 

    uint8_t mode = SPI_MODE_0;
    uint8_t lsb = 0; // we want MSB first SPI_LSB_FIRST;
    ioctl(fd, SPI_IOC_WR_MODE, &mode);
    ioctl(fd, SPI_IOC_WR_LSB_FIRST, &lsb);
    */

    memset(xfer, 0, sizeof xfer);
    memset(buf, 0, sizeof buf);
    len = sizeof buf;

    /*
* Send a GetID command
*/
    buf[0] = 0x9f;
    len = 6;
    xfer[0].tx_buf = (unsigned long)buf;
    xfer[0].len = 1;

    xfer[1].rx_buf = (unsigned long)buf;
    xfer[1].len = 6;
    xfer[1].cs_change = true; // deassert CS after last transaction

    status = ioctl(fd, SPI_IOC_MESSAGE(2), xfer);
    if (status < 0)
    {
        perror("SPI_IOC_MESSAGE");
        return -1;
    }

    printf("response(%d): ", status);
    for (bp = buf; len; len--)
        printf("%02x ", *bp++);
    printf("\n");

    return 0;
}