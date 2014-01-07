/* protocol.h -*-c-*-
 * Protocol specification.
 * Author: Michael Fitzmayer
 *
 * This program is part of the SNESoIP project and has has been released
 * under the terms of a BSD-like license.  See the file LICENSE for
 * details. */


#ifndef PROTOCOL_h
#define PROTOCOL_h

#include <stdint.h>
#include <stdlib.h>


/* A brief explanation of how the protocol works.

	 A package is constructed as follows:
	 +-------------+-------------+--------+----------------+
	 | Function ID | Data length |  Data  | CRC16 checksum |
	 +-------------+-------------+--------+----------------+
	 | 1 Byte      | 1 Byte      | N byte | 2 Byte         |
	 +-------------+-------------+--------+----------------+


	 A simple login sequence could be implemented like this:

	 At startup the SNESoIP sends following package to the server.
	 +-------+----------+-----------+----------+
	 | Login | LoginLen | Client ID | Checksum |
	 +-------+----------+-----------+----------+

	 On success (e.g. server is up), the server sends following reply:
	 +-------+----------+-----------+----------+
	 | Hello | HelloLen | Client ID | Checksum |
	 +-------+----------+-----------+----------+

	 If received successfully, the SNESoIP goes on by requesting various
	 configuration parameters (e.g. IP address of the opponent etc.):
	 +-----------+--------------+-----------+----------+
	 | RequestIP | RequestIPLen | Client ID | Checksum |
	 +-----------+--------------+-----------+----------+

	 Which would lead to an appropriate reply:
	 +----+-------+-----+-----+-----+----+----------+
	 | IP | IPLen | 109 | 193 | 192 | 40 | Checksum |
	 +----+-------+-----+-----+-----+----+----------+ */


// Function IDs.
#define Login          0
#define Hello          1
#define RequestIP      2
#define IP             3


// Data lengths.
#define LoginLen       1
#define HelloLen       1
#define RequestIPLen   1
#define IPLen          4


uint16_t checksum;


uint16_t crc16(const uint8_t *data, uint8_t length);


#endif
