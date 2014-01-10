/* server.h -*-c-*-
 * SNESoIP server.
 * Author: Michael Fitzmayer
 *
 * This program is part of the SNESoIP project and has has been released
 * under the terms of a BSD-like license.  See the file LICENSE for
 * details. */


#ifndef SERVER_h
#define SERVER_h

#include <errno.h>
#include <getopt.h>
#include <netinet/in.h>
#include <unistd.h>
#include "mysql.h"
#include "protocol.h"



#define BufferSize 260



char* uint16_t2bin(uint16_t num);



#endif
