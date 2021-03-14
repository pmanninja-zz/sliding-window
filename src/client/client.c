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

#define IP_PROTOCOL 0
#define IP_ADDRESS "127.0.0.1" // localhost
#define PORT_NO 15050
#define BUFFERLEN 32
#define cipherKey 'S'
#define sendrecvflag 0
#define nofile "File Not Found!"

void clearBuf(char* b);
int sendFile(FILE* fp, char* buf, int s);
int recvFile(char* buf, int s);
char Cipher(char ch);

int main() {
  int sockfd, nbytes, len, selection, port;
  char address[9];
  struct sockaddr_in servaddr;
  int addrlen = sizeof(servaddr);
  char buffer[BUFFERLEN];
  FILE* fp;

  printf("%s","Enter port number enter 2 to use default: ");
  scanf("%d", &port);

  servaddr.sin_family = AF_INET; // ipv4

  // port number for what service gets the data that comes from client||host to network short (htons)
  if(port == 2) {
    servaddr.sin_port = htons(PORT_NO);
  } else {
    servaddr.sin_port = htons(port);
  }
  // host address||host to network long (htonl)
    servaddr.sin_addr.s_addr = inet_addr(IP_ADDRESS);

    // IPv4 socket made|| IPv4,UDP,protocol
    sockfd = socket(AF_INET, SOCK_DGRAM, IP_PROTOCOL);

    // if socket failed to be made output error and exit
    if (sockfd < 0) {
      perror("failed to create");
      exit(EXIT_FAILURE);
      } else {
        printf("%s\n","_________________");
        printf("%s\n","client is running");
        printf("%s\n","-----------------");
      }
  START:
  printf("send an option\n");
  printf("1)Send single entry\n");
  printf("2)Recive file entry\n");
  printf("3)Send file entry\n");
  printf("Enter a number: ");
  scanf("%d",&selection);

  if (selection == 1 ) {
    goto SENDSINGLE;
  } else if(selection == 2) {
    goto RECIVEFILE;
  } else if(selection == 3) {
    goto SENDFILE;
  } else {
    printf("Select a valid number");
    goto START;
  }

//________________________________Reciving a single terminal input block (e.g test.txt)__________________
SENDSINGLE:
printf("%s\n","Enter your transmision: ");
fgets(buffer, BUFFERLEN, stdin);
len = sendto(sockfd, (const char *)buffer, strlen(buffer), 0, (const struct sockaddr*)&servaddr, sizeof(servaddr));
  if (len == -1) {
    perror("failed to send");
  }
  goto END;
//_______________________________________________________________________________________________________
//________________________________Reciving a file  block (e.g test.txt)__________________________________
RECIVEFILE:
  while (1) {
    printf("\nPlease enter file name to receive:\n");
    scanf("%s", buffer);
    sendto(sockfd, buffer, BUFFERLEN, sendrecvflag, (struct sockaddr*)&servaddr, addrlen);
    printf("\n---------Data Received---------\n");

    while (1) {
      // receive
      clearBuf(buffer);
      nbytes = recvfrom(sockfd,buffer,BUFFERLEN, sendrecvflag, (struct sockaddr*)&servaddr, &addrlen);
      // process
      if (recvFile(buffer, BUFFERLEN)) {
        break;
      }
    }
    printf("\n-------------------------------\n");
    goto END;
  }
//_______________________________________________________________________________________________________

  END:
  close(sockfd);
  return 0;
}

// function to clear buffer
void clearBuf(char* b)
{
    int i;
    for (i = 0; i < BUFFERLEN; i++)
        b[i] = '\0';
}

// function for decryption
char Cipher(char ch)
{
    return ch ^ cipherKey;
}

// function to receive file
int recvFile(char* buf, int s)
{
    int i;
    char ch;
    for (i = 0; i < s; i++) {
        ch = buf[i];
        ch = Cipher(ch);
        if (ch == EOF)
            return 1;
        else
            printf("%c", ch);
    }
    return 0;
}

// function sending file
int sendFile(FILE* fp, char* buf, int s) {
    int i, len;
    if (fp == NULL) {
        strcpy(buf, nofile);
        len = strlen(nofile);
        buf[len] = EOF;
        for (i = 0; i <= len; i++)
            buf[i] = Cipher(buf[i]);
        return 1;
    }

    char ch, ch2;
    for (i = 0; i < s; i++) {
        ch = fgetc(fp);
        ch2 = Cipher(ch);
        buf[i] = ch2;
        if (ch == EOF)
            return 1;
    }
    return 0;

}
