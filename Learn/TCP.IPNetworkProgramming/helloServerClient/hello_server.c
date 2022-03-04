#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void errorHandling(char *message);

int main(int argc, char *argv[]) {
  int serv_sock, clnt_sock;

  struct sockaddr_in serv_addr, clnt_addr;

  socklen_t clnt_addr_size;

  char message[] = "Hello World!";

  if (argc != 2) {
    printf("Usage : %s <port>\n", argv[0]); // 参数检验 ./server port
    exit(1);
  }

  serv_sock = socket(PF_INET, SOCK_STREAM, 0); // 创建对应的套接字 protocolFamily: PF_INET, type: SOCk_STREAM，得到对应的 文件描述符

  if (serv_sock == -1) { // 创建套接字文件失败
    errorHandling("socket() error!");
  }

  memset(&serv_addr, 0, sizeof serv_addr);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(atoi(argv[1]));
  printf("%u\n", serv_addr.sin_port);

  if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof serv_addr) == -1) {
    errorHandling("bind() error!");
  }
  
  if (listen(serv_sock, 5) == -1) {
    errorHandling("listen() error!");
  }
  printf("listen to accept\n");

  clnt_addr_size = sizeof(clnt_addr);
  clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
  
  if (clnt_sock == -1) {
    errorHandling("accetp() error!");
  }

  write(clnt_sock, message, sizeof message);
  close(clnt_sock), close(serv_sock);
  return 0;
}

void errorHandling(char *message) {
  fputs(message, stderr);
  fputs("\n", stderr);
  exit(1);
}