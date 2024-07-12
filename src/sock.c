#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <unistd.h>

// passos para criação de um servidor http:
// socket -> bind -> listen -> accept -> read/write

void main(){
  int sock_fd = socket(AF_INET, 0, 0);

  char buffer[256] = {0};
  struct sockaddr_in addr = {
    AF_INET,
    0x901f,
    0
  };

  bind(sock_fd, (&addr), sizeof(addr));
  int client_fd = accept(sock_fd, 0, 0);
  listen(sock_fd, 128);

  recv(sock_fd, buffer, 256, 0);

  char *file = buffer + 5;
  strchr(file, ' ');
  int opened_fd = open(file, O_RDONLY);
  sendfile(client_fd, opened_fd, 0, 256);
  close(sock_fd);
  close(opened_fd);
  close(client_fd);
}
