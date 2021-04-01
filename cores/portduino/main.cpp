#include "Arduino.h"
#include "PortduinoFS.h"
#include "PortduinoGPIO.h"
#include <argp.h>
#include <stdio.h>

/** # msecs to sleep each loop invocation.  FIXME - make this controlable via
 * config file or command line flags.
 */
static long loopDelay = 100;

/** apps run under portduino can optionally define a portduinoSetup() to
 * use portduino specific init code (such as gpioBind) to setup portduino on
 * their host machine, before running 'arduino' code.
 */
void __attribute__((weak)) portduinoSetup() {
  printf("No portduinoSetup() found, using default settings...\n");
}

void __attribute__((weak)) portduinoCustomInit() {}




// FIXME - move into app client (out of lib) and use real name and version
// FIXME - add app specific options as child options
// http://www.gnu.org/software/libc/manual/html_node/Argp.html
const char *argp_program_version = "portduino 0.1.0";
const char *argp_program_bug_address = "https://github.com/meshtastic/Meshtastic-device";
static char doc[] = "An application written with porduino";
static char args_doc[] = "...";

static struct argp_option options[] = {
    // FIXME not yet implemented
    // {"erase", 'e', 0, 0, "Erase virtual filesystem before use"},

    {"fsdir", 'd', "DIR", 0, "The directory to use as the virtual filesystem"},
    {"hwid", 'h', "HWID", 0, "The mac address to assign to this virtual machine"},
    {0}};

struct TopArguments {
  bool erase;
  char *fsDir;
  uint32_t hwId;
};

// In bss (inited to zero)
TopArguments portduinoArguments;


static struct argp_child children[2] = {
  {NULL},
  {NULL}
};

static void *childArguments;

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
  auto args = (TopArguments *)state->input;
  switch (key) {
    case ARGP_KEY_INIT:
    if(children[0].argp)
      state->child_inputs[0] = childArguments;
    break;
  case 'e':
    args->erase = true;
    break;
  case 'd':
    args->fsDir = arg;
    break;
  case 'h':
    sscanf(arg, "%d", &args->hwId);
    break;    
  case ARGP_KEY_ARG:
    return 0;
  default:
    return ARGP_ERR_UNKNOWN;
  }
  return 0;
}


void getMacAddr(uint8_t *dmac)
{
    dmac[0] = 0x80;
    dmac[1] = 0;
    dmac[2] = portduinoArguments.hwId >> 24;
    dmac[3] = portduinoArguments.hwId >> 16;
    dmac[4] = portduinoArguments.hwId >> 8;
    dmac[5] = portduinoArguments.hwId & 0xff;
}



static struct argp argp = {
  options, 
  parse_opt, 
  args_doc, 
  doc, 
  children, 
  0, 
  0};

/**
 * call from portuinoCustomInit() if you want to add custom command line arguments
 */
void portduinoAddArguments(const struct argp_child &child, void *_childArguments) {
  // We only support one child for now
  children[0] = child;
  childArguments = _childArguments;
}

int main(int argc, char *argv[]) {

  portduinoCustomInit();

  auto *args = &portduinoArguments;
  args->fsDir = "/tmp/portduinofs";
  args->hwId = 1;

  auto parseResult = argp_parse(&argp, argc, argv, 0, 0, args);
  if (parseResult == 0) {
      printf("Portduino is starting, HWID=%d, VFS root at %s\n", args->hwId, args->fsDir);

    String fsroot(args->fsDir);
    mkdir(fsroot.c_str(), 0777);

    // FIXME erase FS if needed

    portduinoVFS->mountpoint(fsroot.c_str());

    gpioInit();
    portduinoSetup();
    setup();
    while (true) {
      gpioIdle(); // FIXME, do this someplace better
      loop();

      // Even if the Arduino code doesn't want to sleep, ensure we don't  burn
      // too much CPU
      delay(loopDelay);
    }
    return 0;
  } else
    return parseResult;
}