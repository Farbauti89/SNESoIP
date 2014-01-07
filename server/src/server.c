/* server.c -*-c-*-
 * SNESoIP server.
 * Author: Michael Fitzmayer
 *
 * This program is part of the SNESoIP project and has has been released
 * under the terms of a BSD-like license.  See the file LICENSE for
 * details. */


#include "server.h"


int main(int argc, char* argv[]) {
	char  *configfd = "server.conf";
	int    opt;
	int    len, received;


	puts(" _______ _______ _______ _______         _______ ______");
	puts("|     __|    |  |    ___|     __|.-----.|_     _|   __ \\");
	puts("|__     |       |    ___|__     ||  _  | _|   |_|    __/");
	puts("|_______|__|____|_______|_______||_____||_______|___|   server\n");
	puts("-c <config>\tload specific config file (defalt: server.conf).\n");


	// Parse command-line arguments.
	while ((opt = getopt(argc, argv, "c:")) != -1)
		switch (opt) {
			case 'c':
				configfd = optarg;
				break;
		}

	// Initialise configuration file.
	if (initConfig(configfd) == -1)
		return EXIT_FAILURE;

	// Initialise database connection.
	if (initMySQL() == -1)
		return EXIT_FAILURE;

	// Setting up the server.
	if (initServer() == -1)
		return EXIT_FAILURE;

	puts("Listening on port 57350.\n");



	while (1) {
		len = sizeof(clientAddr);
		received = recvfrom(sockfd, recvBuffer, 260, 0, (struct sockaddr *)&clientAddr, &len);

		if (received == -1) {
			fprintf(stderr, "Couldn't receive message: %s\n", strerror(errno));
			continue;
		}


		// Get checksum from received data.
		// Lo-Byte.
		for (int i = 0; i < 8; i++) {
			(recvBuffer[3 + recvBuffer[1]] & (1 << i))
				? (checksum |=  (1 << i))
				: (checksum &= ~(1 << i));
		}
		// Hi-Byte.
		for (int i = 0; i < 8; i++) {
			(recvBuffer[2 + recvBuffer[1]] & (1 << i))
				? (checksum |=  (1 << i + 8))
				: (checksum &= ~(1 << i + 8));
		}
		// Drop data if checksum is invalid.
		if (checksum != crc16(recvBuffer, 2 + recvBuffer[1]))
			continue;


	}


	finiMySQL();
	close(sockfd);
	return EXIT_SUCCESS;
}
