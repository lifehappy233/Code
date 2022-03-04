#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

void errorHandling(char *message);

int main(int argc, char *argv[]) {
  if (argc != 2) { // ./server port
    printf("Usage %s <port> !\n", argv[0]);
    exit(1);
  }

  // create socket file descriptor
  int socketFd = socket(PF_INET, SOCK_STREAM, 0);
  if (socketFd == -1) {
    errorHandling("socket file descriptro create error!\n");
  }

  // bind
  struct sockaddr_in serverAddr, clientAddr;
  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddr.sin_port = htons(atoi(argv[1]));
  if (bind(socketFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
    errorHandling("bind error!\n");
  }

  // listen
  if (listen(socketFd, 5) == -1) {
    errorHandling("listen error!\n");
  }
  for (int cas = 0; cas < 5; cas++) {
    int clientFd, clientSize = sizeof(clientAddr);
    clientFd = accept(socketFd, (struct sockaddr*)&clientAddr, &clientSize);
    if (clientFd == -1) {
      printf("%d ", cas);
      errorHandling("accept error!\n");
    }
    printf("accept server %d\n", cas + 1);
    char buf[BUF_SIZE];
    int str_len;
    while (str_len = read(clientFd, buf, BUF_SIZE - 1)) {
      buf[str_len] = 0;
      printf("%s", buf);
      write(clientFd, buf, str_len);
    }
    write(1, "\n", 1);
    close(clientFd);
  }

  // close
  close(socketFd);
  return 0;
}

void errorHandling(char *message) {
  fputs(message, stderr);
  fputs("\n", stderr);
  exit(1);
}