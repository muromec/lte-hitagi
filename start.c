#include "parse.h"

void start (void) __attribute__ ((section (".startup")));




void start() {

  while(1) {
    usb_wait_ep1();
  }

}

