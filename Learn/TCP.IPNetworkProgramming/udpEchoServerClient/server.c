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
  if (argc != 2) {
    printf("Usage %s <port>!\n", argv[0]);
    exit(1);
  }
  
  int serverSocketFd = socket(PF_INET, SOCK_DGRAM, 0);
  if (serverSocketFd == -1) {
    errorHandling("socket create error()!\n");
  }

  struct sockaddr_in serverAddr, clientAddr;
  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddr.sin_port = htons(atoi(argv[1]));

  if (bind(serverSocketFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
    errorHandling("bind error()!\n");
  }

  char buf[BUF_SIZE];
  int clientSize = sizeof(clientAddr), messageLen;
  while (messageLen = recvfrom(serverSocketFd, buf, BUF_SIZE - 1, 0, (struct sockaddr*)&clientAddr, &clientSize)) {
    buf[messageLen] = 0;
    sendto(serverSocketFd, buf, messageLen, 0, (struct sockaddr*)&clientAddr, clientSize);
    printf("Client : %s", buf);
  }

  close(serverSocketFd);

  return 0;
}

void errorHandling(char *message) {
  fputs(message, stderr);
  fputs("\n", stderr);
  exit(1);
}