#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30

void errorHandling(char *message);

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage %s <Addr> <Port>!\n", argv[0]);
    exit(1);
  }
  int socketFd = socket(PF_INET, SOCK_STREAM, 0);
  if (socketFd == -1) {
    errorHandling("socket create error!\n");
  }

  struct sockaddr_in clientAddr;
  memset(&clientAddr, 0, sizeof(clientAddr));
  clientAddr.sin_family = AF_INET;
  clientAddr.sin_addr.s_addr = inet_addr(argv[1]);
  clientAddr.sin_port = htons(atoi(argv[2]));
  if (connect(socketFd, (struct sockaddr*)&clientAddr, sizeof(clientAddr)) == -1) {
    errorHandling("connect is error!\n");
  }

  FILE *fp = fopen("out.c", "wb");
  int reciveLen;
  char buf[BUF_SIZE];
  while (reciveLen = read(socketFd, buf, BUF_SIZE)) {
    buf[reciveLen] = 0;
    fwrite((void *)buf, 1, reciveLen, fp);
    printf("%s", buf);
  }
  puts("\nrevice is OK\n");
  write(socketFd, "Is over", 8);
  fclose(fp);
  close(socketFd);
  return 0;
}

void errorHandling(char *message) {
  fputs(message, stderr);
  fputs("\n", stderr);
  exit(1);
}