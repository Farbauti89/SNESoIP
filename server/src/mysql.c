/* mysql.c -*-c-*-
 * MySQL database handler.
 * Author: Michael Fitzmayer
 *
 * This program is part of the SNESoIP project and has has been released
 * under the terms of a BSD-like license.  See the file LICENSE for
 * details. */


#include "mysql.h"


int initMySQL() {
	dbCon = mysql_init(NULL);


	// Initialise database connection.
	if (! dbCon) {
		fprintf(stderr, "%s\n", mysql_error(dbCon));
		return -1;
	}


	// Establish database connection.
	if (mysql_real_connect(dbCon, dbHostname, dbUsername, dbPassword,
			dbDatabase, 0, NULL, 0) == NULL) {

		fprintf(stderr, "%s\n", mysql_error(dbCon));
		mysql_close(dbCon);
		return -1;
	}
	puts("Database connection established.");

	return 0;
}


void finiMySQL() { mysql_close(dbCon); }
