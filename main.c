#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int child_process() {
  unsigned int random_num;
  int fd = open("/dev/urandom", O_RDONLY);
  if (fd == -1) {
    perror("failed to open dev random");
    exit(1);
  }
  read(fd, &random_num, sizeof(random_num));
  random_num = (random_num % 5) + 1;
  printf("%d %dsec\n", getpid(), random_num);
  sleep(random_num);
  printf("%d finished after %dsec\n", getpid(), random_num);
  return random_num;
}

int main() {
  printf("%d about to create 2 child processes\n", getpid());
  pid_t p1 = fork();
  if (p1 < 0) {
    perror("child 1 fork failed");
    exit(1);
  }
  else if (p1 == 0) {
    int time_waited = child_process();
    return time_waited;
  }
  else {
    pid_t p2 = fork();
    if (p2 < 0) {
      perror("child 2 fork failed");
      exit(1);
    }
    else if (p2 == 0) {
      int time_waited = child_process();
      return time_waited;
    }
    else {
      int status;
      int child_pid = wait(&status);
      if (WIFEXITED(status)) {
        printf("Main Process %d is done. Child %d slept for %dsec\n", getpid(), child_pid, WEXITSTATUS(status));
      }
    }

  }
  return 0;
}
