/* protocol.h -*-c-*-
 * Protocol specification.
 * Author: Michael Fitzmayer
 *
 * This program is part of the SNESoIP project and has has been released
 * under the terms of a BSD-like license.  See the file LICENSE for
 * details. */


#ifndef PROTOCOL_h
#define PROTOCOL_h


/* +-------------+-------------+--------+----------------+
 * | Function ID | Data length |  Data  | CRC16 checksum |
 * +-------------+-------------+--------+----------------+
 * | 1 Byte      | 1 Byte      | N byte | 2 Byte         |
 * +-------------+-------------+--------+----------------+ */


// Function IDs.
#define Login          0
#define Hello          1
#define RequestIP      2
#define IP             3


// Data lengths.
#define LoginLen       0
#define HelloLen       0
#define RequestIPLen   0
#define IPLen          4


#endif
