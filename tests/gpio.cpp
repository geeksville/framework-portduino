#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <errno.h>

#include <linux/gpio.h>


int main(int argc, char **argv)
{
	struct gpiohandle_request req;
	struct gpiohandle_data data;
	char chrdev_name[20];
	int fd, ret = 0;

	strcpy(chrdev_name, "/dev/gpiochip2");

	/*  Open device: gpiochip0 for GPIO bank A */
	fd = open(chrdev_name, 0);
	if (fd == -1) {
        ret = -errno;
		fprintf(stderr, "Failed to open %s\n", chrdev_name);

		return ret;
	}

	/* request GPIO line: GPIO_A_14 */
    int gpionum = 0;
    memset(&req, 0, sizeof(req));
	req.lineoffsets[0] = 0;
	req.flags = GPIOHANDLE_REQUEST_OUTPUT;
	// memcpy(req.default_values, &data, sizeof(req.default_values));
	strcpy(req.consumer_label, "gpiotestapp");
	req.lines  = 1;

	ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req);
	if (ret == -1) {
		ret = -errno;
		fprintf(stderr, "Failed to issue GET LINEHANDLE IOCTL (%d)\n",
			ret);

        return ret;
	}
	if (close(fd) == -1)
		perror("Failed to close GPIO character device file");

    memset(&data, 0, sizeof(data));
	/*  Start led blinking */
	while(1) {
		data.values[0] = !data.values[0];
        printf("Setting LED %d\n", data.values[0]);
		ret = ioctl(req.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
		if (ret == -1) {
			ret = -errno;
			fprintf(stderr, "Failed to issue %s (%d)\n",
					"GPIOHANDLE_SET_LINE_VALUES_IOCTL", ret);
		}
		sleep(1);
	}

	/*  release line */
	ret = close(req.fd);
	if (ret == -1) {
		perror("Failed to close GPIO LINEHANDLE device file");
		ret = -errno;
	}
	return ret;
}