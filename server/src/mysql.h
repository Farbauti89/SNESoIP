/* mysql.h -*-c-*-
 * MySQL database handler.
 * Author: Michael Fitzmayer
 *
 * This program is part of the SNESoIP project and has has been released
 * under the terms of a BSD-like license.  See the file LICENSE for
 * details. */


#ifndef MYSQL_h
#define MYSQL_h

#include <mysql.h>
#include "config.h"


MYSQL *dbCon;


int  initMySQL();
void finiMySQL();


#endif
