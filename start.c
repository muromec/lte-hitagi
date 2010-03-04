#include "parse.h"

void start (void) __attribute__ ((section (".startup")));

void start() {

  make_table();

  while(1) {
    usb_wait_ep1();
  }

}

