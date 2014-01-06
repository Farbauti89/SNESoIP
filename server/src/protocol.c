/* protocol.c -*-c-*-
 * Protocol specification.
 * Author: Michael Fitzmayer
 *
 * This program is part of the SNESoIP project and has has been released
 * under the terms of a BSD-like license.  See the file LICENSE for
 * details. */


#include "protocol.h"


uint16_t crc16(const uint8_t *data, uint16_t length) {
	int      i, bitFlag, bitsRead = 0;
	uint16_t checksum = 0;
	uint16_t out = 0;


	if (data == NULL)
		return 0;


	while (length > 0) {
		bitFlag = out >> 15;

		out <<= 1;
		out |= (*data >> bitsRead) & 1;

		bitsRead++;
		if (bitsRead > 7) {
			bitsRead = 0;
			data++;
			length--;
		}

		if (bitFlag)
			out ^= 0x8005;
	}


	for (i = 0; i < 16; ++i) {
		bitFlag = out >> 15;
		out <<= 1;
		if (bitFlag)
			out ^= 0x8005;
	}


	i = 0x8000;
	for (int j = 0x0001; i != 0; i >>=1, j <<= 1)
		if (i & out) checksum |= j;


	return checksum;
}
