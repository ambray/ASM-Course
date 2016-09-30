#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TMP_FILE_STR  "tmp.txt"
#define BEGIN_OFFSET  1
#define BUFSZ		  1024
#define LOG_ERROR(x)\
	do { fprintf(stderr, "[x] %s : %d : %d - " x "\n", __FILE__, __LINE__, errno); } while(0)

int main(int argc, char** argv, char** envp)
{
	char  buf[BUFSZ] = {0};
	char* newenvp[] = { NULL };
	pid_t child = 0;
	int   fd = -1;

	if(argc < 2) {
		errno = EINVAL;
		LOG_ERROR("Must provide one or more arguments!");
		return 0;
	}

	if(-1 == (fd = open(TMP_FILE_STR, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP))) {
		LOG_ERROR("File open failed!");
		return 0;
	}

	if(-1 == dup2(fd, STDOUT_FILENO)) {
		LOG_ERROR("Output redirection failed!");
		close(fd);
		return 0;
	}

	if(-1 == dup2(fd, STDERR_FILENO)) {
		LOG_ERROR("Error redirection failed!");
		close(fd);
		return 0;
	}
	close(fd);
	if(0 == (child = fork())) {
		execve(argv[BEGIN_OFFSET], &argv[BEGIN_OFFSET], newenvp);
	} else {
		wait(NULL);
	}

	return 0;
}