#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


int main(int argc, char** argv, char** envp)
{
  if (argc < 2)
    return 0;

  int fd = open(argv[1], O_WRONLY | O_CREAT);
  if(fd == -1)
   return -1;

  dup2(fd, STDOUT_FILENO);
  
  for(int i = 0; envp[i] != NULL; ++i)
    printf("%s\n", envp[i]);

  close(fd);

  return 0;
}
