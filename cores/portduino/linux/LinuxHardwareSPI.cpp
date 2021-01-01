//
// Created by kevinh on 9/1/20.
//

#include "HardwareSPI.h"
#include "Utility.h"
#include "logging.h"
#include "linux/PosixFile.h"

#include <assert.h>
#include <linux/spi/spidev.h>

class SPIChip : private PosixFile
{
public:
    SPIChip(const char *name = "/dev/spidev0.0") : PosixFile(name) {}

    /**
     * Do a SPI transaction to the selected device
     * 
     * @param outBuf if NULL it will be not used (zeros will be sent)
     * @param inBuf if NULL it will not be used (device response bytes will be discarded)
     * @param deassertCS after last transaction (if not set, it will be left asserted)
     * @return 0 for success, else ERRNO fault code
     */
    int transfer(const uint8_t *outBuf, uint8_t *inBuf, size_t bufLen, bool deassertCS = true)
    {
        struct spi_ioc_transfer xfer;
        static uint8_t scratchBuf[256];

        assert(bufLen <= sizeof(scratchBuf));

        /*
        We want default SPI mode 0, MSB first 

        uint8_t mode = SPI_MODE_0;
        uint8_t lsb = 0; // we want MSB first SPI_LSB_FIRST;
        ioctl(fd, SPI_IOC_WR_MODE, &mode);
        ioctl(fd, SPI_IOC_WR_LSB_FIRST, &lsb);
        */

        memset(&xfer, 0, sizeof xfer);
        memset(inBuf, 0x55, bufLen);

        if(!outBuf) {
            memset(scratchBuf, 0, bufLen);
            outBuf = scratchBuf;
        }

        if(!inBuf)
            inBuf = scratchBuf;

        xfer.tx_buf = (unsigned long)outBuf;
        xfer.len = bufLen;

        xfer.rx_buf = (unsigned long)inBuf;
        xfer.cs_change = deassertCS; 

        int status = ioctl(SPI_IOC_MESSAGE(1), &xfer);
        if (status < 0)
        {
            perror("SPI_IOC_MESSAGE");
            return status;
        }

        /* printf("SPI response(%d): ", status);
        size_t len = bufLen;
        for (auto bp = inBuf; len; len--)
            printf("%02x ", *bp++);
        printf("\n"); */

        return 0;
    }
};

// FIXME, this is kinda skanky, but for now we assume one SPI device
SPIChip *spiChip;

namespace arduino
{

    uint8_t HardwareSPI::transfer(uint8_t data)
    {
        uint8_t response;
        assert(spiChip);
        spiChip->transfer(&data, &response, 1, false); // leave CS asserted
        return response;
    }

    uint16_t HardwareSPI::transfer16(uint16_t data)
    {
        notImplemented("transfer16");
        assert(0); // make fatal for now to prevent accidental use
        return 0x4242;
    }

    // BIG PERFORMANCE FIXME!  Change the RadioLib transfer code to use this method
    // for many fewer kernel switches/USB transactions.
    // In fact - switch the API to the nrf52/esp32 arduino version that takes both an
    // inbuf and an outbuf;
    void HardwareSPI::transfer(void *buf, size_t count) {
        NOT_IMPLEMENTED("transferBuf");
        assert(0); // make fatal for now to prevent accidental use
    }
        

    // Transaction Functions
    void HardwareSPI::usingInterrupt(int interruptNumber) {
        // Do nothing
    }

    void HardwareSPI::notUsingInterrupt(int interruptNumber){
        // Do nothing
    }

    void HardwareSPI::beginTransaction(SPISettings settings)
    {
        // Do nothing
    }

    void HardwareSPI::endTransaction(void)
    {
        assert(spiChip);
        spiChip->transfer(NULL, NULL, 0, true); // turn off chip select
    }

    // SPI Configuration methods
    void HardwareSPI::attachInterrupt()
    {
        // Do nothing
    }

    void HardwareSPI::detachInterrupt()
    {
        // Do nothing
    }

    void HardwareSPI::begin()
    {
        if(spiChip)
            delete spiChip;

        spiChip = new SPIChip();
    }

    void HardwareSPI::end()
    {
        if(spiChip)
            delete spiChip;
        spiChip = NULL;
    }

} // namespace arduino

HardwareSPI SPI;
