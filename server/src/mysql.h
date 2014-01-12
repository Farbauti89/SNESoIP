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
#include "utils.h"



#define QueryBufferSize 150
// Row IDs for getMySQLrow() and setMySQLrow().
#define IPaddress  0
#define OpponentID 1
#define Username   2



MYSQL *dbCon;



int   initMySQL(char *confFile);
void  finiMySQL();

char *getMySQLrow(int rowID, int hwID); // This function should be simplified in the future!
int   setMySQLrow(int rowID, int hwID, char *string);



#endif
