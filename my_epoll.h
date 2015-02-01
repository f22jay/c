/*==================================
*   Copyright (C) 2015 All rights reserved.
*
*   文件名称：ae_epoll.h
*   创 建 者：moon
*   创建日期：2015年01月30日
*   描    述：
*
================================================================*/
#ifndef AE_EPOLLH
#define AE_EPOLLH

int aeApiCreate(aeEventLoop *eventLoop) ;

void aeApiFree(aeEventLoop *eventLoop) ;

int aeApiAddEvent(aeEventLoop *eventLoop, int fd, int mask) ;

int aeApiDelEvent(aeEventLoop *eventLoop,int fd,int mask);

int aeApiPoll(aeEventLoop *eventLoop, struct timeval *tvp) ;

#endif
