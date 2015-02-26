/*==================================
*   Copyright (C) 2015 All rights reserved.
*
*   文件名称：server.h
*   创 建 者：moon
*   创建日期：2015年02月04日
*   描    述：
*
================================================================*/
#pragma once
#ifndef SERVER_H
#define SERVER_H


void sockServer(struct aeEventLoop *eventLoop, int fd, void *client, int mask);

void client_read(struct aeEventLoop *eventLoop, int fd, void *clientData, int mask);

void client_write(struct aeEventLoop *eventLoop, int fd, void *clientData, int mask);

#endif


