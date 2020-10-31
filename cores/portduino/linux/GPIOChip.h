#pragma

#include <Arduino.h>
#include <linux/gpio.h>

#include "linux/PosixFile.h"

/** A linux GPIO chip interface
 * See "gpioinfo" command for info
 */

/** Userspace access to a set of GPIO lines */
class GPIOLines : private PosixFile
{
    gpiohandle_data data;

public:
    GPIOLines(int _fd) : PosixFile(_fd)
    {
        memset(&data, 0, sizeof(data));
    }

    /** Convience function for the common case of mapping to only one GPIO */
    bool read()
    {
        readLines();
        return data.values[0];
    }

    /** Convience function for the common case of mapping to only one GPIO */
    void write(bool hi)
    {
        data.values[0] = hi;
        writeLines();
    }

private:
    /** Read current set of lines */
    const uint8_t *readLines()
    {
        ioctl(GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data);
    }

    /** Write the current set of values to the chip */
    void writeLines()
    {
        ioctl(GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
    }
};

class GPIOChip : private PosixFile
{
public:
    GPIOChip(const char *name) : PosixFile(name) {}

    /** Open just a single line */
    GPIOLines *open(unsigned lineNum, unsigned flags = GPIOHANDLE_REQUEST_INPUT)
    {
        struct gpiohandle_request req;
        memset(&req, 0, sizeof(req));

        req.lineoffsets[0] = lineNum;
        req.flags = flags;
        // memcpy(req.default_values, &data, sizeof(req.default_values));
        strcpy(req.consumer_label, "portduino");
        req.lines = 1;

        ioctl(GPIO_GET_LINEHANDLE_IOCTL, &req);
        return new GPIOLines(req.fd);
    }
};