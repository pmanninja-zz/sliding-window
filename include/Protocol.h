#ifnedf __PROTOCOL_H
#define __PROTOCOL_H

#include <cstdint>
#define DATA_SZ 256

struct simplepacket {
  uint8_t msb;
  uint8_t lsb;  // Most significant byte first = Network order
  char data[DATA_SZ];  // payload
};

// class to be tested. Implements a simple packet structure consisting of a 16 bit$
class SimpleHeader {
private:
  struct simplepacket packet;

public:
  // default constructor initializes the header to zero.
  SimpleHeader();

  // sets the 16 bit value of the header
  void setHeader(unsigned int val);

  // returns the header value
  unsigned int getHeader() const;

  // returns the size of the packet, including headers and data
  // to be used with recvfrom() or sendto()
  int packetSize() const {
    return sizeof(simplepacket);
  }

  // returns the size of the payload. Use with reading / writing to/from files
  int payloadSize() const {
    return DATA_SZ;
  }

  // returns pointer to the structure holding the thePacket, including the headers
  // To be used with recvfrom or sendto
  void * thePacket() {
    return &packet;
  }

  void * thePayload() {
    return packet.data;
  }
};

#endif
