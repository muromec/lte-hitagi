
void (*ramldr_start)() = (void*)0x3fd0010;

char _hlo[] = "BE @ LE\0";
short _hlo_len = 8;

char _err[] = "baAAkaAaA\0";
short _err_len = 10;

char _version[] = "\x02RSVN\x1eHitagi  0.1\x03";
short _version_len = 20;

void handle_ack() {
  usb_write_ep2( (unsigned short*)_hlo, _hlo_len);
}

void handle_err() {
  usb_write_ep2( (unsigned short*)_err, _err_len);
}

void handle_version() {
  usb_write_ep2( (unsigned short*)_version, _version_len);
}

void handle_echo(char *arg) {
  usb_write_ep2( (unsigned short*)arg, strlen(arg));
}


void handle_ramldr() {
  ramldr_start();
}


