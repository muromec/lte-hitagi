void ack();
void start (void) __attribute__ ((section (".startup")));

void (*ramldr_start)() = (void*)0x3fd0010;
unsigned short *usbint = (unsigned short*)0x24852004;

char _hlo[] = "BE @ LE\0";
short _hlo_len = 8;

char _err[] = "baAAkaAaA\0";
short _err_len = 10;

char _version[] = "Hitagi  0.1\0";
short _version_len = 12;

void write_ep2(unsigned short* data, short lenc);

void send_ack() {
  write_ep2( (unsigned short*)_hlo, _hlo_len);
}

void send_err() {
  write_ep2( (unsigned short*)_err, _err_len);
}

void send_version() {
  write_ep2( (unsigned short*)_version, _version_len);
}

void wait_cmd() {
  unsigned short *e1cr = (unsigned short*) 0x2485200A;
  unsigned char *in = (unsigned char*)0x24852090;

  while(!(*usbint & (1<<5)));;

  *e1cr |= 1<<13;

  switch(*(in+1)) {
    case 'H':
      send_ack();
      break;
    case 'R':
      ramldr_start();
      break;
    case 'V':
      send_version();
      break;
    default:
      send_err();
  }

}


void write_ep2(unsigned short* data, short len) {

  unsigned short *e2cr = (unsigned short*) 0x2485200C;
  unsigned short *e1cr = (unsigned short*) 0x2485200A;

  unsigned short *out = (unsigned short*)0x248520b0;


  while(!(*usbint & 1<<6));;// wait for transfer end on ep2
//  while(*e2cr & (1<<10));;

  short _len = len;
  
  while(len > 0) {
    *out++ = *data++;
    len -= 2;
  }

  *e2cr &= ~0x3f;
  *e2cr |= _len;

  *e2cr |= 1<<13;
  *e2cr |= 1<<10;

}

void start() {

  while(1) {
    wait_cmd();
  }

  ramldr_start();

}

