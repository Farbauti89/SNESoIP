/* config.h -*-c-*-
 * Configuration handler.
 * Author: Michael Fitzmayer
 *
 * This program is part of the SNESoIP project and has has been released
 * under the terms of a BSD-like license.  See the file LICENSE for
 * details. */


#ifndef CONFIG_h
#define CONFIG_h

#include <libconfig.h>
#include <string.h>


const char  *dbHostname;
const char  *dbUsername;
const char  *dbPassword;
const char  *dbDatabase;


int initConfig(char *filename);


#endif
