/*==================================
*   Copyright (C) 2015 All rights reserved.
*
*   文件名称：net.h
*   创 建 者：moon
*   创建日期：2015年02月01日
*   描    述：
*
================================================================*/
#pragma once
#ifndef NET_H
#define NET_H
#define MAXCONNECT 100000
int tcpServer(char *ip,int port);

int tcpConnect(char *ip,int port);

int anetRead(int fd, char *buf, int count);

int anetWrite(int fd, char *buf, int count);

#endif
