/* mysql.c -*-c-*-
 * MySQL database handler.
 * Author: Michael Fitzmayer
 *
 * This program is part of the SNESoIP project and has has been released
 * under the terms of a BSD-like license.  See the file LICENSE for
 * details. */


#include "mysql.h"



int initMySQL(char *confFile) {
	const char *hostname;
	const char *username;
	const char *password;
	const char *database;

	char error = 0;
	dbCon = mysql_init(NULL);


	// Initialise and read configuration file.
	config_t          conf;
	config_setting_t *setting;
	config_init(&conf);

	if (! config_read_file(&conf, confFile)) {
		config_destroy(&conf);
		fprintf(stderr, "%s: wrong file format or file does not exist.\n", confFile);
		return -1;
	}

	if ( (! config_lookup_string(&conf, "hostname", &hostname) ) || (strlen(hostname) == 0) ) {
		fprintf(stderr, "%s: hostname is not set\n", confFile);
		error = 1;
	}

	if ( (! config_lookup_string(&conf, "username", &username) ) || (strlen(username) == 0) ) {
		fprintf(stderr, "%s: username is not set\n", confFile);
		error = 1;
	}

	if ( (! config_lookup_string(&conf, "password", &password) ) || (strlen(password) == 0) ) {
		fprintf(stderr, "%s: password is not set\n", confFile);
		error = 1;
	}

	if ( (! config_lookup_string(&conf, "database", &database) ) || (strlen(database) == 0) ) {
		fprintf(stderr, "%s: database is not set\n", confFile);
		error = 1;
	}

	if (error == 1) return -1;
	printf("Sucessfully laoded %s.\n", confFile);


	// Initialise database connection.
	if (! dbCon) {
		fprintf(stderr, "%s\n", mysql_error(dbCon) );
		return -1;
	}


	// Establish database connection.
	if (mysql_real_connect(dbCon, hostname, username, password,
			database, 0, NULL, 0) == NULL) {

		fprintf(stderr, "%s\n", mysql_error(dbCon) );
		mysql_close(dbCon);
		return -1;
	}
	puts("Database connection established.");


	config_destroy(&conf);
	return 0;
}



void finiMySQL() { mysql_close(dbCon); }



// This function should be simplified in the future!
char *getMySQLrow(int rowID, int hwID) {
	char       query[QueryBufferSize];
	MYSQL_RES *res;
	MYSQL_ROW  row;


	switch(rowID) {
		case IPaddress:
			sprintf(query,
				"SELECT currentip FROM snesoip_hw WHERE hwid = %i",
				hwID);
			break;

		case OpponentID:
			sprintf(query,
				"SELECT hwid_opponent FROM snesoip_hw WHERE hwid = %i",
				hwID);
			break;

		case Username:
			sprintf(query,
				"SELECT user.username FROM snesoip_hw INNER JOIN user ON snesoip_hw.user_userid = user.userid WHERE snesoip_hw.hwid = %i",
				hwID);
			break;

		default:
			return NULL;
	}


	if (mysql_query(dbCon, query) != 0) {
		fprintf(stderr, "%s", mysql_error(dbCon) );
		return NULL;
	}

	if ( (res = mysql_store_result(dbCon)) == NULL) {
		fprintf(stderr, "%s", mysql_error(dbCon) );
		return NULL;
	}

	if ( (row = mysql_fetch_row(res)) == NULL) {
		fprintf(stderr, "%s", mysql_error(dbCon) );
		return NULL;
	}


	mysql_free_result(res);
	return row[0];
}



int setMySQLrow(int rowID, int hwID, char *string) {
	char       query[QueryBufferSize];
	MYSQL_RES *res;


	switch(rowID) {
		case IPaddress:
			if (! isValidIP(string))
				return -1;

			sprintf(query,
				"UPDATE snesoip_hw SET currentip = \"%s\" WHERE hwid = %i;",
				string, hwID);
			break;

		default:
			return -1;
	}


	if (mysql_query(dbCon, query) != 0) {
		fprintf(stderr, "%s", mysql_error(dbCon) );
		return -1;
	}


	return 0;
}
