/*==================================
*   Copyright (C) 2015 All rights reserved.
*
*   文件名称：test.c
*   创 建 者：moon
*   创建日期：2015年01月29日
*   描    述：
*
================================================================*/
#include "tool.h"
#include "net.h"
#include <string.h>

#define perrmsg(MSG)  printf("eror : %s\n",MSG);

void maintest(int argc, char ** argv){
	long sec=0;
	long millsec=0;
	aeGetTime(&sec,&millsec);
	printf("%ld---%ld\n",sec,millsec);
	if (argc <2){
		perrmsg("argc error");
		exit(-1);
	}

	char *pp = "192.168.231.136";
	putchar(*index(pp,'9'));
	/*char *ip = "192.168.31.222";*/
	/*int port = 8888;*/
	char *ip = argv[1];
	int port = atoi(argv[2]);
	int fd = tcpConnect(ip,port);
	char *buf="hello";
	char inbuf[1023]={0};
	if (fd == -1){
		perrmsg("conncet ");
	}

	int n=0;
	while(1){
		n=anetRead(fd,inbuf,10);
		if (n== -1){
			break;
		}
		/*puts(inbuf);*/
		printf("%s\n",inbuf);

	    anetWrite(fd,inbuf,sizeof(buf));
		inbuf[0]=0;
	}


	return ;

}
