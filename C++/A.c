#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

void errorHandling(char *message) {
  fputs(message, stderr);
  fputs("\n", stderr);
  exit(1);
}

int main() {
  // int fd1 = socket(PF_INET, SOCK_STREAM, 0);
  // int fd2 = open("write.txt", O_CREAT | O_WRONLY | O_TRUNC);
  int fd3 = socket(PF_INET, SOCK_DGRAM, 0);

  // printf("%d %d %d\n", fd1, fd2, fd3);
  
  // close(fd1), close(fd2), close(fd3);
  char buf[110];
  int flag1 = read(0, buf, sizeof buf);
  int flag2 = write(1, buf, strlen(buf) * sizeof(char));
  printf("%d %d %s\n", flag1, flag2, buf);
  return 0;
}