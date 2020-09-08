#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include <string.h>

void magic(int fd)
{
	struct stat buf;
	memset(&buf, 0, sizeof(buf));


	char buffer[100];
	char *device;
	char sys_call[100];

	FILE *fp = popen("df -hT | grep /$", "r");
	if ( fp == NULL )
		perror("");


	fread(buffer, sizeof(buffer), sizeof(char), fp);
	pclose(fp);

	device = strtok(buffer, "\t ");

	printf("%s\n", device);


	sprintf(sys_call, "mount -o remount,mand %s", device);

	system(sys_call);

	for ( ;; )
	{
		if ( (fstat( fd, &buf)) == -1 )
			perror("");

		if ( !( buf.st_mode & S_ISGID ) )
		{
			fchmod(fd, S_IRWXU | S_IRGRP | S_ISGID | S_IROTH | S_IXOTH );
		}
	}



}

void set_lock( struct flock *fl , int fd)
{
	if ( fcntl(fd, F_SETLK, fl) == -1 )
	{
		perror("lock failed.");
		exit(EXIT_FAILURE);
	}

	
}




int main(int argc, char **argv)
{
	int fd = open(argv[1], O_WRONLY);
	if ( fd == -1 )
		perror("");

	struct flock fl;
	memset(&fl, 0, sizeof(fl));

	fl.l_type = F_WRLCK;
	fl.l_whence = SEEK_SET;
	fl.l_start = 0;
	fl.l_len = 0;
	fl.l_pid = getpid();

	set_lock(&fl, fd);

	magic(fd);



	return 0;
}
