#include "tool.h"
 void aeGetTime(long *seconds, long *milliseconds)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	*seconds = tv.tv_sec;
	*milliseconds = tv.tv_usec/1000;
}

int setnoblocking (int fd){
	int old_option = fcntl(fd,F_GETFL );
	int new_optin = old_option | O_NONBLOCK;
	fcntl(fd,F_SETFL,new_optin);
	return old_option;
}

void addfd(int epollfd, int fd){
	struct epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN | EPOLLET;
	epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&event);
	setnoblocking(fd);
}


/*
 *void sig_handler(int sig){
 *    int save_errno = errno;
 *    int msg = sig;
 *    send(pipefd[1],(char *)&msg,1,0);
 *    errno = save_errno;
 *}
 *
 */
/*
 *void addsig(int sig){
 *    struct sigaction sa;
 *    memset( &sa,0,sizeof(sa));
 *    sa.sa_handler = sig_handler;
 *    sa.sa_flags |= SA_RESTART;
 *    sigfillset( &sa.sa_mask);
 *    assert(sigaction(sig,&sa,NULL) != -1);
 *}
 */
