#include "Protocol.h"

SimpleHeader::SimpleHeader() {
  packet.msb = packet.lsb = 0;
}

void SimpleHeader::setHeader(unsigned int val) {
  packet.msb = (val>>8); // shift the integer to right by 8 bits to get the msb
  packet.lsb = (val&255); // bitwise AND with 8 LSB bits set to 1.
}

unsigned int SimpleHeader::getHeader() const {
  return packet.lsb | (packet.msb<<8);
}
