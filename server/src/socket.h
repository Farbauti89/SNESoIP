/* socket.h -*-c-*-
 * Connection handler
 * Copyright (c) 2013 Michael Fitzmayer.  All rights reserved.
 *
 * This program has has been released under the terms of a BSD-like
 * license.  See the file LICENSE for details. */


#ifndef CONN_h
#define CONN_h

#include <netinet/in.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>


#define BufferSize 260


struct sockaddr_in clientAddr;
struct sockaddr_in serverAddr;


int  sockfd;
char recvBuffer[BufferSize];
char sendBuffer[BufferSize];


int initServer();


#endif
