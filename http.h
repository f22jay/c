/*==================================
*   Copyright (C) 2015 All rights reserved.
*
*   文件名称：http.h
*   创 建 者：moon
*   创建日期：2015年02月27日
*   描    述：
*
================================================================*/
#pragma once
#ifndef HTTP_H
#define HTTP_H

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
typedef struct clientData{
	int status;
	char path[100];
} clientData;


void accept_request(int client,clientData * result);
void bad_request(int);
void cat(int, FILE *);
void cannot_execute(int);
void error_die(const char *);
void execute_cgi(int, const char *, const char *, const char *);
int get_line(int, char *, int);
void headers(int, const char *);
void not_found(int);
void serve_file(int, const char *);
int startup(u_short *);
void unimplemented(int);



#endif
