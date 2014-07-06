#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVERPORT 8888 /*number of server terminal*/
#define BACKLOG 100 /*max number of connected clients*/

int main() {
  int sockfd, client_fd; /*socket: listen to socket, client_fd: data transport socket*/
  struct sockaddr_in my_addr; /*inforation of the server address*/
  struct sockaddr_in remote_addr; /*information of the client address*/
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket create fail!");
    exit(1);
  }
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(SERVERPORT);
  my_addr.sin_addr.s_addr = INADDR_ANY;
  bzero(&(my_addr.sin_zero), 8);
  if (bind(sockfd, (struct sockaddr *)& my_addr, sizeof(struct sockaddr)) == -1) {
  perror("bind error!");
  exit(1);
  }
  if (listen(sockfd, BACKLOG) == -1) {
    perror("listen error!");
    exit(1);
  }

  while (1) {
    unsigned int sin_size = sizeof(struct sockaddr_in);
    if ((client_fd = accept(sockfd, (struct sockaddr*)&remote_addr, &sin_size)) == -1) {
      perror("accept error");
      continue;
    }
    printf("received a connection from %s ", inet_ntoa(remote_addr.sin_addr));
    if (!fork()) {
      if (send(client_fd, "Welcome! You have connect successfully!", 26, 0) == -1) {
        perror("send error!");
        close(client_fd);
        exit(0);
      }
      close(client_fd);
    }
 }
}
