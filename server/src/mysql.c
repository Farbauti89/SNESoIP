/* mysql.c -*-c-*-
 * MySQL database handler.
 * Author: Michael Fitzmayer
 *
 * This program is part of the SNESoIP project and has has been released
 * under the terms of a BSD-like license.  See the file LICENSE for
 * details. */


#include "mysql.h"



int initMySQL(MYSQL *con, char *confFile) {
	const char *hostname;
	const char *username;
	const char *password;
	const char *database;

	char error = 0;
	con = mysql_init(NULL);


	// Initialise and read configuration file.
	config_t          conf;
	config_setting_t *setting;
	config_init(&conf);

	if (! config_read_file(&conf, confFile)) {
		config_destroy(&conf);
		fprintf(stderr, "%s: wrong file format or file does not exist.\n", confFile);
		return -1;
	}

	if ( (! config_lookup_string(&conf, "hostname", &hostname)) || (strlen(hostname) == 0) ) {
		fprintf(stderr, "%s: hostname is not set\n", confFile);
		error = 1;
	}

	if ( (! config_lookup_string(&conf, "username", &username)) || (strlen(username) == 0) ) {
		fprintf(stderr, "%s: username is not set\n", confFile);
		error = 1;
	}

	if ( (! config_lookup_string(&conf, "password", &password)) || (strlen(password) == 0) ) {
		fprintf(stderr, "%s: password is not set\n", confFile);
		error = 1;
	}

	if ( (! config_lookup_string(&conf, "database", &database)) || (strlen(database) == 0) ) {
		fprintf(stderr, "%s: database is not set\n", confFile);
		error = 1;
	}

	if (error == 1) return -1;
	printf("Sucessfully laoded %s.\n", confFile);


	// Initialise database connection.
	if (! con) {
		fprintf(stderr, "%s\n", mysql_error(con));
		return -1;
	}


	// Establish database connection.
	if (mysql_real_connect(con, hostname, username, password,
			database, 0, NULL, 0) == NULL) {

		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		return -1;
	}
	puts("Database connection established.");


	config_destroy(&conf);
	return 0;
}



void finiMySQL(MYSQL *con) { mysql_close(con); }
