#include "Protocol.h"
#include "gtest/gtest.h"



TEST(testProtocol, checksum) {
  u_long sum = 0;
  int count = 5;

  while(count--) {
    sum += MAX_FRAME_SIZE;
    if (sum & 0xFFFF0000) {
      sum &= 0xFFFF
      sum++;
    }
  EXPECT_TRUE(sum >= 0);
  EXPECT_FALSE(sum <= 0);
}

TEST(testProtocol, create_frame) {

}
TEST(testProtocol, create_ack) {

}
TEST(testProtocol, read_frame) {

}
TEST(testProtocol, read_ack) {

}
