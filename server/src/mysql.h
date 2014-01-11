/* mysql.h -*-c-*-
 * MySQL database handler.
 * Author: Michael Fitzmayer
 *
 * This program is part of the SNESoIP project and has has been released
 * under the terms of a BSD-like license.  See the file LICENSE for
 * details. */


#ifndef MYSQL_h
#define MYSQL_h

#include <libconfig.h>
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define QueryBufferSize 150



MYSQL *dbCon;



int   initMySQL(char *confFile);
void  finiMySQL();

char *getUsername(int hwID);
int   setIP(char *ipAddr, int hwID);



#endif
