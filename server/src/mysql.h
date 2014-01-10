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



int  initMySQL(MYSQL *con, char *confFile);
void finiMySQL(MYSQL *con);



#endif
