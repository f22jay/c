/*==================================
*   Copyright (C) 2015 All rights reserved.
*
*   文件名称：tool.h
*   创 建 者：moon
*   创建日期：2015年01月29日
*   描    述：
*
================================================================*/
#ifndef TOOL_H
#define TOOL_H
#pragma once
#include<sys/types.h>
#include<sys/time.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<assert.h>
#include<memory.h>
#include<signal.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/epoll.h>


void aeGetTime(long *seconds, long *milliseconds);


#endif
