#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdbool.h>

#define BUF_SIZE 1024
void errorHandling(char *message);

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage %s <addr> <port>!\n", argv[0]);
    exit(1);
  }

  int serverSocketFd = socket(PF_INET, SOCK_DGRAM, 0);
  if (serverSocketFd == -1) {
    errorHandling("socket create error()!\n");
  }

  struct sockaddr_in serverAddr, fromAddr;
  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
  serverAddr.sin_port = htons(atoi(argv[2]));

  int strLen, fromLen = sizeof(fromAddr);
  char buf[BUF_SIZE];

  /*
  // unconnect socket addr port
  while (strLen = read(0, buf, BUF_SIZE - 1)) {
    if (strLen == 2 && buf[1] == '\n' && (buf[0] == 'q' || buf[0] == 'Q')) {
      break;
    }
    buf[strLen] = 0;
    sendto(serverSocketFd, buf, BUF_SIZE - 1, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    
    strLen = recvfrom(serverSocketFd, buf, BUF_SIZE - 1, 0, (struct sockaddr*)&fromAddr, &fromLen);
    buf[strLen] = 0;

    printf("Server : %s", buf);
  }
  */

  // /*
  // connect socket addr port
  if (connect(serverSocketFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
    errorHandling("connect is error()!\n");
  }

  while (strLen = read(0, buf, BUF_SIZE - 1)) {
    if (strLen == 2 && buf[1] == '\n' && (buf[0] == 'q' || buf[0] == 'Q')) {
      break;
    }
    buf[strLen] = 0;
    write(serverSocketFd, buf, strLen);
    strLen = read(serverSocketFd, buf, BUF_SIZE - 1);
    printf("Server : %s", buf);
  }
  // */

  close(serverSocketFd);

  return 0;
}

void errorHandling(char *message) {
  fputs(message, stderr);
  fputs("\n", stderr);
  exit(1);
}