/*==================================
 *   Copyright (C) 2015 All rights reserved.
 *
 *   文件名称：server.c
 *   创 建 者：moon
 *   创建日期：2015年02月03日
 *   描    述：
 *
 ================================================================*/
#include "event.h"
#include "http.h"
#include "net.h"
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/sendfile.h>
#include "assert.h"
#include "tool.h"
#include "server.h"


int sina;

void sockServer(struct aeEventLoop *eventLoop, int fd, void *client, int mask){
	struct sockaddr_in  address;
	int len;

	assert (mask & AE_READABLE);
	clientData *data = malloc(sizeof(clientData));
	int connecFd = accept(fd,(struct sockaddr *)&address,&len);
	if ( connecFd < 0 )
		perr();
	/*assert (connecFd > 0);*/
	createFileEvent(eventLoop,connecFd,AE_READABLE,client_read,data);
}

void client_read(struct aeEventLoop *eventLoop, int fd, void *data, int mask){
	accept_request(fd,data);
	createFileEvent(eventLoop,fd,AE_WRITABLE,client_write,data);
}
void client_write(struct aeEventLoop *eventLoop, int fd, void *data, int mask){

      clientData * result =  (clientData *)data;
	  if (result->status)
		  serve_file(fd,result->path);
	  else {
		  not_found(fd);
	  }
     deleteFileEvent(eventLoop,fd,AE_WRITABLE);
     deleteFileEvent(eventLoop,fd,AE_READABLE);
	 close(fd);

/*
 *    int file = ((clientData *)data)->fd;
 *    struct stat stat_buf;
 *    fstat(file,&stat_buf);
 *    char *buf = "hello";
 *    off_t offset = 0;
 *    sendfile(fd,file,&offset,stat_buf.st_size);
 *    [>write(fd,buf,5);<]
 */
}

void main(){
	aeEventLoop *eventLoop = createMyEventLoop();
	assert(eventLoop != NULL);

	int sockfd = tcpServer("192.168.11.154",8888);
	int ret = createFileEvent(eventLoop,sockfd,AE_READABLE,sockServer,NULL);
	assert (ret != -1);
	sina = open("sina.html",O_RDONLY);

	while (eventLoop->stopLoop != 1){
		int num = aeProcessEvents(eventLoop,0);
		int i = 0 ;
		for(i;i<num;i++) {
			firedEvent *fe = eventLoop->fired+i;
			aeFileEvent *event = eventLoop->events+fe->fd;
			int mask = fe->mask;
			if (mask & AE_READABLE & event->mask){
				event->rfileProc(eventLoop,fe->fd,event->clientData,fe->mask);
			}
			if (mask & AE_WRITABLE & event->mask){
				event->wfileProc(eventLoop,fe->fd,event->clientData,fe->mask);
			}

		}
	}


}
