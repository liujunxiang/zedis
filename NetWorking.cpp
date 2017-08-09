/*
 * NetWorking.cpp
 *
 *  Created on: Aug 7, 2017
 *      Author: root
 */

#include "NetWorking.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
BEGIN_NAMESPACE
NetWorkingUtil::NetWorkingUtil()
{
}

NetWorkingUtil::~NetWorkingUtil()
{
}
SOCKET_T NetWorkingUtil::Sock( const char * ip ,unsigned port )
{
	int sock,   btrue = 1;
	struct sockaddr_in server_addr;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		return -1 ;
		exit(1);
	}
	if (setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&btrue,sizeof(int)) == -1) {
		perror("Setsockopt");
		return -1 ;
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = inet_addr( ip);
	bzero(&(server_addr.sin_zero),8);
	if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr))
			== -1) {
		perror("Unable to bind");
		return -1;
	}
	if (listen(sock, 5) == -1) {
		perror("Listen");
		return -1;
	}
	return sock ;
}

END_NAMESPACE
