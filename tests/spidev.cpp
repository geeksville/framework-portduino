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
    unsigned char outbuf[32], inbuf[32], *bp;
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
    memset(outbuf, 0, sizeof outbuf);
    memset(inbuf, 0x55, sizeof inbuf);

    /*
* Send a sx127x get version command */
    outbuf[0] = 0x42;
    len = 2;
    xfer[0].tx_buf = (unsigned long)outbuf;
    xfer[0].len = len;

    xfer[0].rx_buf = (unsigned long)inbuf;
    xfer[0].cs_change = true; // deassert CS after last transaction

    status = ioctl(fd, SPI_IOC_MESSAGE(1), xfer);
    if (status < 0)
    {
        perror("SPI_IOC_MESSAGE");
        return -1;
    }

    printf("response(%d) (first byte of response should be ignored): ", status);
    for (bp = inbuf; len; len--)
        printf("%02x ", *bp++);
    printf("\n");

    return 0;
}