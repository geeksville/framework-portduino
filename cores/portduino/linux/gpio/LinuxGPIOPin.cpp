#ifdef PORTDUINO_LINUX_HARDWARE

#include "linux/gpio/LinuxGPIOPin.h"
#include <assert.h>
#include <dirent.h>

const char *consumer = "portduino";

static int chip_dir_filter(const struct dirent *entry)
{
	bool is_chip;
	char *path;
	int ret;

	ret = asprintf(&path, "/dev/%s", entry->d_name);
	if (ret < 0)
		return 0;

	is_chip = gpiod_is_gpiochip_device(path);
	free(path);
	return !!is_chip;
}

static struct gpiod_chip *chip_open_by_name(const char *name)
{
	struct gpiod_chip *chip;
	char *path;
	int ret;

	ret = asprintf(&path, "/dev/%s", name);
	if (ret < 0)
		return NULL;

	chip = gpiod_chip_open(path);
	free(path);

	return chip;
}

/**
 * Try to find the specified linux gpio line, throw exception if not found
 */
static gpiod_line *getLine(const char *chipLabel, const char *linuxPinName) {

  struct dirent **entries;
  int num_chips = scandir("/dev/", &entries, chip_dir_filter, alphasort);
  assert(num_chips > 0); // FIXME, throw exception

  log(SysGPIO, LogDebug, "getLine(%s, %s)", chipLabel, linuxPinName);
  for (int i = 0; i < num_chips; i++) {
    auto chip = chip_open_by_name(entries[i]->d_name);
    if (!chip) {
      if (errno == EACCES)
        continue; // skip chips we don't have access to

      assert(0); // die_perror("unable to open %s", entries[i]->d_name);
    } else {
      auto label = gpiod_chip_label(chip);
      if (strcmp(label, chipLabel) == 0) {
        auto offset = gpiod_chip_find_line(chip, linuxPinName);
        assert(offset >= 0); // fixme throw
        auto line = gpiod_chip_get_line(chip, offset);
        assert(line); // fixme throw

        struct gpiod_line_request_config request = {
            consumer, GPIOD_LINE_REQUEST_DIRECTION_AS_IS, 0};
        auto result = gpiod_line_request(line, &request, 0);
        assert(result == 0); // fixme throw
        return line;
      }
    }
  }
  assert(0); // FIXME throw
}

/**
 * Create a pin given a linux chip label and pin name
 */
LinuxGPIOPin::LinuxGPIOPin(pin_size_t n, const char *chipLabel,
                           const char *linuxPinName,
                           const char *portduinoPinName)
    : GPIOPin(n, portduinoPinName ? portduinoPinName : linuxPinName) {
  line = getLine(chipLabel, linuxPinName);
}

LinuxGPIOPin::~LinuxGPIOPin() { 
    gpiod_line_release(line); 
    // FIXME must call gpiod_chip_unref(chip);
}

/// Read the low level hardware for this pin
PinStatus LinuxGPIOPin::readPinHardware() {
    int res = gpiod_line_get_value(line);
    assert(res == 0 || res == 1); // FIXME throw instead

    // log(SysGPIO, LogDebug, "readPinHardware(%s, %d)", getName(), res); 
    return (PinStatus) res;
}

void LinuxGPIOPin::writePin(PinStatus s) {
  GPIOPin::writePin(s); // update status

  int res = gpiod_line_set_value(line, s);
  assert(res == 0);
}

void LinuxGPIOPin::setPinMode(PinMode m) {
  GPIOPin::setPinMode(m);

  // Set direction, if output use the current pinstate as the output value
  int res =
      gpiod_line_set_config(line,
                            (m == OUTPUT) ? GPIOD_LINE_REQUEST_DIRECTION_OUTPUT
                                          : GPIOD_LINE_REQUEST_DIRECTION_INPUT,
                            0, readPin());
  assert(res == 0);
}


#endif