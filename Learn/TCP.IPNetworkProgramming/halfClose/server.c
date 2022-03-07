#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
#define true 1

void errorHandling(char *message);

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage %s <port>!\n", argv[0]);
    exit(1);
  }
  FILE *fp = fopen("client.c", "rb");
  int socketFd = socket(PF_INET, SOCK_STREAM, 0);
  struct sockaddr_in serverAddr, clientAddr;

  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddr.sin_port = htons(atoi(argv[1]));
  if (bind(socketFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
    errorHandling("bind error!\n");
  }

  if (listen(socketFd, 5) == -1) {
    errorHandling("listen error!\n");
  }

  int clientFd, clientSize = sizeof(clientAddr);
  clientFd = accept(socketFd, (struct sockaddr*)&clientAddr, &clientSize);
  char buf[BUF_SIZE];
  while (true) {
    int readLen = fread((void *)buf, 1, BUF_SIZE, fp);
    printf("%d\n", readLen);
    write(clientFd, buf, readLen);
    if (readLen < BUF_SIZE) {
      break;
    }
  }
  shutdown(clientFd, SHUT_WR);
  read(clientFd, buf, BUF_SIZE);
  printf("Client : %s\n", buf);
  fclose(fp);
  close(socketFd);
  close(clientFd);
  return 0;
}

void errorHandling(char message[]) {
  fputs(message, stderr);
  fputs("\n", stderr);
  exit(1);
}