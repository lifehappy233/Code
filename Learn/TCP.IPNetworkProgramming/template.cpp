#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void errorHandling(char *message);

int main(int argc, char *argv[]) {
  return 0;
}

void errorHandling(char *message) {
  fputs(message, stderr);
  fputs("\n", stderr);
  exit(1);
}