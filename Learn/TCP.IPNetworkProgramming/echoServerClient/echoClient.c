#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void errorHandling(char *message);

int main(int argc, char *argv[]) {
  if (argc != 3) { // addr port;
    printf("Usage %s <addr> <port>!\n", argv[0]);
    exit(1);
  }
  
  // create socket file descriptor
  int socketFd = socket(PF_INET, SOCK_STREAM, 0);
  if (socketFd == -1) {
    errorHandling("socket file descriptor create error!\n");
  }


  // connect;
  struct sockaddr_in clientAddr;
  memset(&clientAddr, 0, sizeof(clientAddr));
  clientAddr.sin_family = AF_INET;
  clientAddr.sin_port = htons(atoi(argv[2]));
  clientAddr.sin_addr.s_addr = inet_addr(argv[1]);
  if (connect(socketFd, (struct sockaddr*)&clientAddr, sizeof(clientAddr)) == -1) {
    errorHandling("connect error!\n");
  }
  
  // read and write 
  char buf[BUF_SIZE];
  int str_len;
  while (str_len = read(0, buf, BUF_SIZE - 1)) {
    if (str_len == 2 && buf[1] == '\n' && (buf[0] == 'q' || buf[0] == 'Q')) {
      break;
    }
    buf[str_len] = 0;
    write(socketFd, buf, str_len);
    int recLen = 0;
    while (recLen < str_len) {
      int cur = read(socketFd, buf + recLen, BUF_SIZE - 1);
      if (cur == -1) {
        errorHandling("read error()!\n");
      }
      recLen += cur;
    }
    buf[recLen] = 0;
    printf("%s", buf);
  }

  close(socketFd);

  return 0;
}

void errorHandling(char *message) {
  fputs(message, stderr);
  fputs("\n", stderr);
  exit(1);
}