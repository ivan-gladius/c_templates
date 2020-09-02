
// SIMPLE DAEMON SKELETTON JUST INCLUDE AND START THE FUNCION AND IT WILL BE A DAEMON

#ifndef DAEMON_FUNC
#define DAEMON_FUNC

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

void start_daemon()
{
	pid_t pid;

	pid = fork();

	if ( pid < 0 ) exit(EXIT_FAILURE);

	// close parent
	if ( pid > 0 ) exit(EXIT_SUCCESS);

	// detach from tty
	if ( setsid() < 0 ) exit(EXIT_FAILURE);

	signal(SIGCHLD, SIG_IGN);
	signal(SIGHUP, SIG_IGN);

	// redo to be sure it wont reconnect to tty

	pid = fork();

	if ( pid < 0 ) exit(EXIT_FAILURE);
	if ( pid > 0 ) exit(EXIT_SUCCESS);

	umask(0);

	chdir("/");	

	// close all file descriptors especially stdout, stdin, stderr, ( 0, 1, 2 )

	for ( int x = sysconf(_SC_OPEN_MAX); x >= 0; x--)
		close(x);
}
	
#endif
