#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
  printf("%d about to create 2 child processes", getpid());
  pid_t p = fork();
  if (p < 0) {
    perror("fork failed");
    exit(1);
  }
  else if (p == 0) {
    int random_num;
    int fd = open("/dev/random", O_RDONLY);
    if (fd == -1) {
      perror("failed to open dev random");
      exit(1);
    }
    read(fd, &random_num, sizeof(random_num));
    printf("%d %dsec", getpid(), random_num);
    sleep(random_num);
    printf("%d finished after %d seconds", getpid(), random_num);
    kill(getpid(), 3);

  }
  else {

  }
}
