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
#include <string.h>

#define BUFFERLEN 32
#define IP_ADDRESS "127.0.0.1" // localhost || default address
#define PORT_NO 15050  // default port
#define IP_PROTOCOL 0
#define cipherKey 'S'
#define sendrecvflag 0
#define nofile "File Not Found!"

void clearBuf(char* b);
int sendFile(FILE* fp, char* buf, int s);
int recvFile(char* buf, int s);
char Cipher(char ch);

int main() {
  int sockfd, nbytes, selection, n, port;
  struct sockaddr_in servaddr;
  int addrlen = sizeof(servaddr);
  char buffer[BUFFERLEN];
  FILE* fp;
  socklen_t len = 0;

  printf("%s","Enter Port Number (example: 15050) enter 2 to use default: ");
  scanf("%d", &port);

  servaddr.sin_family = AF_INET;  // ipv4

  // port number for what service gets the data that comes from client||host to network short (htons)
  if(port == 2) {
    servaddr.sin_port = htons(PORT_NO);
  } else {
    servaddr.sin_port = htons(port);
  }

  // host address||host to network long (htonl)
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);


  // IPv4 socket made|| IPv4,UDP,protocol
  sockfd = socket(AF_INET, SOCK_DGRAM, IP_PROTOCOL);

  // if socket failed to be made output error and exit
  if (sockfd < 0) {
    perror("failed to create");
    exit(EXIT_FAILURE);
  }


  // bind the made socket to reciv ||file descriptor socket(),my address,address length
  int reciv = bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));

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

  START:
  printf("send an option\n");
  printf("1)Send file entry\n");
  printf("2)exit program\n");
  printf("Enter a number: ");
  scanf("%d",&selection);
  printf("%s\n","-----------------");


  if(selection == 1) {
    goto SENDFILE;
  } else if (selection == 2) {
    goto END;
  } else {
    printf("Select a valid number");
    goto START;
  }


//________________________________Sending a file block (e.g testfile.txt)________________________________________
  SENDFILE:
  while(1) {
    printf("\nWaiting for file name ....\n");
    clearBuf(buffer);

    nbytes = recvfrom(sockfd, buffer, BUFFERLEN, sendrecvflag, (struct sockaddr*)&servaddr, &addrlen);
    char path[100] = "./src/server/";
    strcat(path,buffer);
    
    fp = fopen(path,"r");
    printf("\nFile Name Received: %s\n",buffer);
    if(fp == NULL) {
      printf("\nFile Open Failed!\n");
      goto START;
    } else {
      printf("\nFile Successfully Opened!\n");
    }
    printf("%s\n","-----------------");

    while(1) {
      if (sendFile(fp,buffer,BUFFERLEN)) {
        sendto(sockfd,buffer,BUFFERLEN,sendrecvflag,(struct sockaddr*)&servaddr,addrlen);
        break;
      }
      sendto(sockfd,buffer,BUFFERLEN,sendrecvflag,(struct sockaddr*)&servaddr,addrlen);
      clearBuf(buffer);
    }
    if(fp != NULL) {
      fclose(fp);
      goto START;
    }
  }
//______________________________________________________________________________________________________________

  END:
  close(sockfd);
  return 0;
}


// function to clear buffer
void clearBuf(char* b) {
    int i;
    for (i = 0; i < BUFFERLEN; i++)
        b[i] = '\0';
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

char Cipher(char ch) {
    return ch ^ cipherKey;
}

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
