#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void errorHandling(char *message);

int main(int argc, char *argv[]) {
  int sock;
  struct sockaddr_in serv_addr;
  char message[30];

  if (argc != 3) {
    printf("Usage : %s <IP> <Port>\n", argv[0]);
    exit(1);
  }

  sock = socket(PF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    errorHandling("socker() error!");
  }

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_addr.sin_port = htons(atoi(argv[2]));

  if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
    errorHandling("connect() error!");
  }
  
  int idx = 0, str_len = 0, read_len;
  while (read_len = read(sock, &message[idx++], 1)) {
    if (read_len == -1) {
      errorHandling("read() error!");
    }
    str_len += read_len;
  }
  // str_len = read(sock, message, sizeof(message) - 1);
  // if (str_len == -1) {
  //   errorHandling("read() error!");
  // }

  printf("Message form server : %s\nFuncTion read call count: %d\n", message, str_len);
  close(sock);
  return 0;
}

void errorHandling(char *message) {
  fputs(message, stderr);
  fputs("\n", stderr);
  exit(1);
}