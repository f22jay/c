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

void main(){
	long sec=0;
	long millsec=0;
	aeGetTime(&sec,&millsec);
	printf("%ld---%ld\n",sec,millsec);
	return ;

}
