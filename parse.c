#include "parse.h"

void parse_ramldr2_cmd(unsigned char *in, short len) {
  return;
}

void parse_moto_cmd(unsigned char *in, short len) {
  switch(*(in+1)) {
    case 'H':
      handle_ack();
      break;
    case 'R':
      handle_ramldr();
      break;
    case 'V':
      handle_version();
      break;
    default:
      handle_err();
  }

}

void parse_cmd(unsigned char *in, short len) {

  switch(*in) {
    case STX :

      parse_moto_cmd(in, len);
      break;

    case 'F': // RAMLDR2 write
    case 'Z': // RAMLDR2 shutdown
    case 'A': // RAMLDR2 init
    case 'R': // RAMLDR2 read block
    case 'B': // RAMLDR2 set blank
    case 'S': // RAMLDR2 start phone
    case 'C': // RAMLDR2 report flash id
      parse_ramldr2_cmd(in, len);
    break;
  }
}

