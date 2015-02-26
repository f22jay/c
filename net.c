/*==================================
 *   Copyright (C) 2015 All rights reserved.
 *
 *   文件名称：net.c
 *   创 建 者：moon
 *   创建日期：2015年02月01日
 *   描    述：
 *
 ================================================================*/
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<memory.h>
#include<error.h>
#include "net.h"
#include "tool.h"

int tcpServer(char *ip,int port){
	int sock;
	struct sockaddr_in  address;
	memset(&address,0,sizeof(struct sockaddr_in));
	address.sin_family = AF_INET;
	inet_pton(AF_INET,ip,&address.sin_addr);
	address.sin_port = htons(port);

	if ((sock=socket(PF_INET,SOCK_STREAM,0)) <= 0) return -1;
	if (bind(sock,(struct sockaddr *) &address ,sizeof(address)) == -1) return -1;
	if (listen(sock,MAXCONNECT) == -1 ) return -1;

	return sock;
}
int tcpConnect(char *ip,int port){
	int sock;
	struct sockaddr_in  address;
	memset(&address,0,sizeof(struct sockaddr_in));
	address.sin_family = AF_INET;
	/*address.sin_addr.s_addr = inet_addr(ip);*/
	inet_pton(AF_INET,ip,&address.sin_addr);
	address.sin_port = htons(port);
	sock=socket(PF_INET,SOCK_STREAM,0);

	if (connect(sock,(struct sockaddr *) &address,sizeof(address)) == -1){
		/*
		 *perror(strerror(error));
		 */
		perr();
		close(sock);
		return -1;
	}

	return sock;
}

int anetRead(int fd, char *buf, int count)
{
	int nread, totlen = 0;
	while(totlen != count) {
		nread = read(fd,buf,count-totlen);
		if (nread == 0) return totlen;
		if (nread == -1) return -1;
		totlen += nread;
		buf += nread;
	}
	return totlen;
}

int anetWrite(int fd, char *buf, int count)
{
	int nwritten, totlen = 0;
	while(totlen != count) {
		nwritten = write(fd,buf,count-totlen);
		if (nwritten == 0) return totlen;
		if (nwritten == -1) return -1;
		totlen += nwritten;
		buf += nwritten;
	}
	return totlen;
}

