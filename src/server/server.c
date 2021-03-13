/*
server.c
Author(s): Nwabunor Onwuanyi , Prosper ibhamawu
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#include <limits.h>

#define BUFFERLEN 1000   // how many pending connections queue will hold

int main() {
  double port;
  printf("Enter port number: ");
  scanf("%lf", &port);
  printf("hostname: %s\n", hostname);

  char buffer[BUFFERLEN] = {0};
  struct sockaddr_in servaddr = {0};

  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);  // IPv4 socket made

  // if socket failed to be made output error and exit
  if (sockfd == -1) {
    perror("failed to create");
    exit(EXIT_FAILURE);
  }

  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(port);
  servaddr.sin_addr.s_addr = INADDR_ANY;

  int reciv = bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)); // bind the made socket to reciv

  // if socket failed to bind output error and exit
  if (reciv == -1) {
    perror("failed to bind");
    close(sockfd);
    exit(EXIT_FAILURE);
  } else {
    printf("%s\n","_________________");
    printf("%s\n","Server is running");
    printf("%s\n","-----------------");
  }

  socklen_t len = 0;
  int n = recvfrom(sockfd, (char *)buffer, BUFFERLEN, MSG_WAITALL, 0, &len);

  printf("%s","recived transmision : " );
  printf("%s", buffer);

  close(sockfd);

  return 0;
}
