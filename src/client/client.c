/*
server.c
Author(s): Nwabunor Onwuanyi , Prosper ibhamawu
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>


int main() {
  char  packet[100];
  double port;
  printf("%s","Enter your transmision: ");
  fgets(packet, 100, stdin);
  printf("%s","Enter port number: ");
  scanf("%lf", &port);

  struct sockaddr_in servaddr = {0};


  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  if (sockfd == -1) {
    perror("failed to create");
    exit(EXIT_FAILURE);
  }

  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(port);
  servaddr.sin_addr.s_addr = INADDR_ANY;


  int len = sendto(sockfd, (const char *)packet, strlen(packet), 0, (const struct sockaddr*)&servaddr, sizeof(servaddr));
  if (len == -1) {
    perror("failed to send");
  }

  close(sockfd);
  return 0;
}
