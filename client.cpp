#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string>

#define SERVERPORT 8888
#define MAXDATASIZE 1000
#define SERVERERADDRESS "192.168.1.102" //服务器地址

using std::cin;
using std::string;

int main(int argc, char *argv[]) {
  int sockfd, recvbytes;
  char buf[MAXDATASIZE];
  struct hostent *host;
  struct sockaddr_in server;
  if (argc < 2) {
    fprintf(stderr, "Please enter the server's hostname!");
    exit(1);
  }
  if ((host = gethostbyname(argv[1])) == NULL) {
    herror("gethostbyname fail!");
    exit(1);
  }
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("create socket fail!");
    exit(1);
  }
  server.sin_family = AF_INET;
  server.sin_port = htons(SERVERPORT);
  server.sin_addr = *((struct in_addr *)host->h_addr);
  bzero(&(server.sin_zero), 8);
  if (connect(sockfd, (struct sockaddr *)&server, sizeof(struct sockaddr))
  == -1) {
    perror("connect fail");
    exit(1);
  }
  while (1) {
    if ((recvbytes = recv(sockfd, buf, MAXDATASIZE, 0)) == -1) {
      perror("receive fail!");
      exit(1);
    }
    buf[recvbytes] = '\0';
    printf("%s", buf);
    if (buf[strlen(buf) - 2] == ' ') {
      char str[100];
      scanf("%s", str);
      send(sockfd, str, sizeof(str), 0);
    }
  }
  close(sockfd);
}
