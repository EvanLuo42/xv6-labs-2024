#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int
main()
{
  int fd1[2];
  int fd2[2];

  int p;

  if (pipe(fd1) == -1)
  {
    fprintf(2, "pingpong: pipe failed\n");
    exit(1);
  }

  if (pipe(fd2) == -1)
  {
    fprintf(2, "pingpong: pipe failed\n");
    exit(1);
  }

  p = fork();

  if (p < 0)
  {
    fprintf(2, "pingpong: fork failed\n");
    exit(1);
  }
  else if (p > 0)
  {
    char byte = 'a';
    write(fd1[1], &byte, 1);
    wait(((void*) 0));
    char receive;
    read(fd2[0], &receive, 1);
    if (receive != 'a')
    {
      exit(1);
    }
    printf("%d: received pong\n", getpid());
    exit(0);
  }
  else
  {
    char receive;
    read(fd1[0], &receive, 1);
    if (receive != 'a')
    {
      exit(1);
    }
    printf("%d: received ping\n", getpid());
    char byte = 'a';
    write(fd2[1], &byte, 1);
    exit(0);
  }
}