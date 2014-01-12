/* utils.h -*-c-*-
 * Various nonspecific helper functions.
 * Author: Michael Fitzmayer
 *
 * Copyright (c) 2013 Michael Fitzmayer.  All rights reserved.
 *
 * This program has has been released under the terms of a BSD-like
 * license.  See the file LICENSE for details. */


#ifndef UTILS_h
#define UTILS_h

#include <arpa/inet.h>
#include <time.h>
#include <string.h>


int    isValidIP(char *ipAddr);
char  *getTimestamp();



#endif
