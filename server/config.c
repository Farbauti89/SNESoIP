/* config.c -*-c-*-
 * Configuration handler.
 * Author: Michael Fitzmayer
 *
 * This program is part of the SNESoIP project and has has been released
 * under the terms of a BSD-like license.  See the file LICENSE for
 * details. */


#include "config.h"


int initConfig(char *filename) {
	int error = 0;
	config_t cfg;
	config_setting_t *setting;


	config_init(&cfg);


	if (! config_read_file(&cfg, filename)) {
		config_destroy(&cfg);
		fprintf(stderr, "%s: wrong file format or file does not exist.\n", filename);
		error = 1;
	}

	if (
		(! config_lookup_string(&cfg, "hostname", &dbHostname)) ||
		(strlen(dbHostname) == 0)) {

		fprintf(stderr, "%s: hostname is not set\n", filename);
		error = 1;
	}

	if (
		(! config_lookup_string(&cfg, "username", &dbUsername)) ||
		(strlen(dbUsername) == 0)) {


		fprintf(stderr, "%s: username is not set\n", filename);
		error = 1;
	}

	if (
		(! config_lookup_string(&cfg, "password", &dbPassword)) ||
		(strlen(dbPassword) == 0)) {

		fprintf(stderr, "%s: password is not set\n", filename);
		error = 1;
	}

	if (
		(! config_lookup_string(&cfg, "database", &dbDatabase)) ||
		(strlen(dbDatabase) == 0)) {

		fprintf(stderr, "%s: database is not set\n", filename);
		error = 1;
	}


	if (error == 1) return -1;
	printf("Sucessfully laoded %s.\n", filename);
	return 0;
}
