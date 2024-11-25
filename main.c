#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

void child_process() {
  unsigned int random_num;
  int fd = open("/dev/random", O_RDONLY);
  if (fd == -1) {
    perror("failed to open dev random");
    exit(1);
  }
  read(fd, &random_num, sizeof(random_num));
  random_num %= (5 + 1);
  printf("%d %dsec\n", getpid(), random_num);
  sleep(random_num);
  printf("%d finished after %d seconds\n", getpid(), random_num);
  exit(0);
}

int main() {
  printf("%d about to create 2 child processes\n", getpid());
  pid_t p1 = fork();
  if (p1 < 0) {
    perror("fork failed");
    exit(1);
  }
  else if (p1 == 0) {
    child_process();
  }
  else {
    pid_t p2 = fork();
    if (p1 < 0) {
      perror("fork failed");
      exit(1);
    }
    else if (p2 == 0) {
      child_process();
    }
    else {

    }

  }
  return 0;
}
