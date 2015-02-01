/*==================================
 *   Copyright (C) 2015 All rights reserved.
 *
 *   文件名称：pe.c
 *   创 建 者：moon
 *   创建日期：2015年01月29日
 *   描    述：
 *
 ================================================================*/
#include<stdlib.h>
#include "event.h"
#include "my_epoll.h"
aeEventLoop * createMyEventLoop(void){
	aeEventLoop *eventLoop = malloc(sizeof(aeEventLoop));
	if (eventLoop == NULL) return NULL;
	eventLoop->stopLoop=0;
	eventLoop->maxFd=-1;
	if (aeApiCreate(eventLoop) != 0){
		free(eventLoop);
		return NULL;
	}
	return eventLoop;
}
void deleteMyEventLoop(aeEventLoop *eventLoop){

	aeApiFree(eventLoop);

	free(eventLoop);
}
void stopMyEventLoop(aeEventLoop *eventLoop){
	eventLoop->stopLoop = 1;
}
int createFileEvent(aeEventLoop *eventLoop,int fd,int mask,aeFileProc * proc,void * clientData){
	aeFileEvent * fileEvent = eventLoop->events+fd;
	fileEvent->mask |= mask;
	if (mask | AE_READABLE)  fileEvent->rfileProc = proc;
	if (mask | AE_WRITABLE)  fileEvent->wfileProc = proc;
	fileEvent->clientData = clientData;

	if (aeApiAddEvent(eventLoop,fd,mask) == -1)  return -1;
	if (fd > eventLoop->maxFd) eventLoop->maxFd = fd;

	return 0;
}
void deleteFileEvent(aeEventLoop *eventLoop,int fd,int mask){
	if (fd > MAXEVENT) return ;
	aeFileEvent *fe = eventLoop->events+fd;
	if (fe->mask == AE_NONE) return;
	fe->mask &= (~mask);
	aeApiDelEvent(eventLoop,fd,mask);
	return ;
}

int aeProcessEvents(aeEventLoop *eventLoop, int flags){
	int numevents;
	struct timeval tv;
	aeGetTime(&tv.tv_sec,&tv.tv_usec);
	tv.tv_usec += 5;

	numevents = aeApiPoll(eventLoop,NULL);

}
//int aeWait(int fd, int mask, long long milliseconds);
void aeMain(aeEventLoop *eventLoop);


