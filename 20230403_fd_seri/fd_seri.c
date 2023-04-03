#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>

int main(void){
	int fd1, fd2, fd3;

	fd1 = socket(PF_INET, SOCK_STREAM, 0);

	if(fd1 == -1){
		perror("socket 1 error");
		exit(1);
	}

	fd2 = open("test.dat", O_CREAT|O_WRONLY|O_TRUNC);
	if(fd2 == -1){
		perror("open error");
		exit(1);
	}

	fd3 = socket(PF_INET, SOCK_DGRAM, 0);
	if(fd3 == -1){
		perror("socket 2 error");
		exit(1);

	}

	printf("file descriptor 1: %d\n", fd1);
	printf("file descriptor 2: %d\n", fd2);
	printf("file descriptor 3: %d\n", fd3);

	close(fd1);
	close(fd2);
	close(fd3);

	return 0;
}
