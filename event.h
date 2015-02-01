/*==================================
 *   Copyright (C) 2015 All rights reserved.
 *
 *   文件名称：pe.h
 *   创 建 者：moon
 *   创建日期：2015年01月29日
 *   描    述：
 *
 ================================================================*/

#pragma once
#ifndef EVENT_H
#define EVENT_H

#define MAXEVENT 1024*10
#define AE_NONE 0
#define AE_READABLE 1
#define AE_WRITABLE 2
struct aeEventLoop;

/* Types and data structures */
typedef void aeFileProc(struct aeEventLoop *eventLoop, int fd, void *clientData, int mask);
typedef int aeTimeProc(struct aeEventLoop *eventLoop, long long id, void *clientData);

typedef struct firedEvent {
	int fd;
	int mask;
}firedEvent;

/* File event structure */
typedef struct aeFileEvent {
	int mask; /* one of EVENT_(READABLE|WRITABLE) */
	aeFileProc *rfileProc;
	aeFileProc *wfileProc;
	void *clientData;
} aeFileEvent;

typedef struct aeEventLoop {
	aeFileEvent events[MAXEVENT];
	firedEvent fired[MAXEVENT];
	int stopLoop;
	void * apidata;
	int maxFd;
} aeEventLoop;

aeEventLoop * createMyEventLoop(void);
void deleteMyEventLoop(aeEventLoop *);
void stopMyEventLoop();
int createFileEvent(aeEventLoop *eventLoop,int fd,int mask,aeFileProc *,void * clientData);
void deleteFileEvent(aeEventLoop *eventLoop,int fd,int mask);
int aeProcessEvents(aeEventLoop *eventLoop, int flags);
//int aeWait(int fd, int mask, long long milliseconds);
void aeMain(aeEventLoop *eventLoop);




#endif
