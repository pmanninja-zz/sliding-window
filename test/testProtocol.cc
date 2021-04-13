#include "Protocol.h"
#include "gtest/gtest.h"

TEST(testProtocol, checksum) {
  u_long sum = 0;
  int count = 5;

  while(count--) {
    sum += MAX_FRAME_SIZE;
    if (sum & 0xFFFF0000) {
      sum &= 0xFFFF;
      sum++;
    }
  }
  EXPECT_TRUE(sum >= 0);
  EXPECT_FALSE(sum <= 0);
}

TEST(testProtocol, create_frame) {
  uint32_t net_seq_num = htonl(12345);
  uint32_t net_data_size = htonl(1024);
  memcpy(frame + 1, &net_seq_num, 4);
  memcpy(frame + 5, &net_data_size, 4);
  memcpy(frame + 9, data, data_size);
  frame[data_size + 9] = checksum(frame, data_size + (int) 9);

  EXPECT_TRUE(data_size >= 0);
  EXPECT_TRUE(frame[data_size] >= 0);

}
TEST(testProtocol, create_ack) {
  uint32_t net_seq_num = htonl(12345);
  memcpy(ack + 1, &net_seq_num, 4);
  ack[5] = checksum(ack, ACK_SIZE - (int) 1);

  EXPECT_TRUE(ack[5] >= 0);
  EXPECT_FALSE(ack[5] <= 0);

}
TEST(testProtocol, read_frame) {

  uint32_t net_seq_num;
  memcpy(&net_seq_num, frame + 1, 4);
  *seq_num = ntohl(net_seq_num);

  uint32_t net_data_size;
  memcpy(&net_data_size, frame + 5, 4);
  *data_size = ntohl(net_data_size);

  memcpy(data, frame + 9, *data_size);

  EXPECT_TRUE(frame[*data_size]) >= 0);
  EXPECT_TRUE(frame[*data_size + 9]  !=  checksum(frame, *data_size + (int) 9));

}
TEST(testProtocol, read_ack) {

  uint32_t net_seq_num;
  memcpy(&net_seq_num, ack + 1, 4);
  *seq_num = ntohl(net_seq_num);

  EXPECT_TRUE(ack[5]) >= 0);
  EXPECT_TRUE(ack[5]  !=  checksum(frame, *data_size + (int) 9));

}
