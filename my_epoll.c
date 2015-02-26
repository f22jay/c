/*==================================
 *   Copyright (C) 2015 All rights reserved.
 *
 *   文件名称：ae_epoll.c
 *   创 建 者：moon
 *   创建日期：2015年01月29日
 *   描    述：
 *
 ================================================================*/
#include "event.h"
#include "tool.h"
#include<stdlib.h>
#include <sys/epoll.h>

typedef struct aeApiState {
	int epfd;
	struct epoll_event events[MAXEVENT];
} aeApiState;

 int aeApiCreate(aeEventLoop *eventLoop) {
	aeApiState *state = malloc(sizeof(aeApiState));

	if (!state) return -1;
	state->epfd = epoll_create(1024); /* 1024 is just an hint for the kernel */
	if (state->epfd == -1) return -1;
	eventLoop->apidata = state;
	return 0;
}
 void aeApiFree(aeEventLoop *eventLoop) {
	aeApiState *state = eventLoop->apidata;
	close(state->epfd);
	free(state);
}
int aeApiAddEvent(aeEventLoop *eventLoop, int fd, int mask) {
	aeApiState *state = eventLoop->apidata;
	int op = eventLoop->events[fd].mask == AE_NONE ?
		EPOLL_CTL_ADD : EPOLL_CTL_MOD;
	struct epoll_event ee;
	ee.events = 0;
	if (mask & AE_READABLE) {
		ee.events |= EPOLLIN;
	}

	if (mask & AE_WRITABLE) {
		ee.events |= EPOLLOUT;
	}
	ee.data.u64 = 0; /* avoid valgrind warning */
	ee.data.fd = fd;
	if (epoll_ctl(state->epfd,op,fd,&ee) == -1) return -1;
	return 0;
}
int aeApiDelEvent(aeEventLoop *eventLoop,int fd,int mask){
	aeApiState *state = eventLoop->apidata;
	struct epoll_event ee;
	int delmask = eventLoop->events[fd].mask & (~mask);

	ee.events = 0;
	if (delmask & AE_READABLE) ee.events |= EPOLLIN;
	if (delmask & AE_WRITABLE) ee.events |= EPOLLOUT;
	ee.data.u64 = 0; /* avoid valgrind warning */
	ee.data.fd = fd;
	if (delmask != AE_NONE) {
		epoll_ctl(state->epfd,EPOLL_CTL_MOD,fd,&ee);
	} else {
		/* Note, Kernel < 2.6.9 requires a non null event pointer even for
		 *          * EPOLL_CTL_DEL. */
		epoll_ctl(state->epfd,EPOLL_CTL_DEL,fd,&ee);
	}
}
int aeApiPoll(aeEventLoop *eventLoop, struct timeval *tvp) {
	aeApiState *state = eventLoop->apidata;
	int retval, numevents = 0;

	retval = epoll_wait(state->epfd,state->events,MAXEVENT,
			tvp ? (tvp->tv_sec*1000 + tvp->tv_usec/1000) : -1);
	if (retval > 0) {
		int j;

		numevents = retval;
		for (j = 0; j < numevents; j++) {
			int mask = 0;
			struct epoll_event *e = state->events+j;

			if (e->events & EPOLLIN) mask |= AE_READABLE;
			if (e->events & EPOLLOUT) mask |= AE_WRITABLE;
			eventLoop->fired[j].fd = e->data.fd;
			eventLoop->fired[j].mask = mask;
		}
	}
	return numevents;
}
