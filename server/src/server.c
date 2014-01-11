/* server.c -*-c-*-
 * SNESoIP server.
 * Author: Michael Fitzmayer
 *
 * This program is part of the SNESoIP project and has has been released
 * under the terms of a BSD-like license.  See the file LICENSE for
 * details. */


#include "server.h"



int main(int argc, char* argv[]) {
	extern MYSQL *dbCon;
	int           options;              // Database.
	char         *confFile = "server.conf";

	struct   sockaddr_in clientAddr; // Server.
	struct   sockaddr_in serverAddr;
	int      sockfd;
	int      length, received;
	char     recvBuffer[BufferSize];
	char     sendBuffer[BufferSize];

	char*    nlpos;                  // Timestamp.
	char*    timestamp;
	time_t   ltime;

	uint16_t checksum;               // Misc.


	puts(" _______ _______ _______ _______         _______ ______");
	puts("|     __|    |  |    ___|     __|.-----.|_     _|   __ \\");
	puts("|__     |       |    ___|__     ||  _  | _|   |_|    __/");
	puts("|_______|__|____|_______|_______||_____||_______|___|   server\n");
	puts("-c <config>\tload specific config file (defalt: server.conf).\n");


	// Parse command-line arguments.
	while ( (options = getopt(argc, argv, "c:") ) != -1)
		switch (options) {
			case 'c':
				confFile = optarg;
				break;
		}


	// Initialise database connection.
	if (initMySQL(confFile) == -1)
		return EXIT_FAILURE;


	// Setting up the server.
	sockfd                     = socket(AF_INET, SOCK_DGRAM, 0);
	serverAddr.sin_family      = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port        = htons(57350);


	if ( (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr) ) ) == -1) {
		fprintf(stderr, "Couldn't bind name to socket: %s\n", strerror(errno) );
		return EXIT_FAILURE;
	}
	puts("Listening on port 57350.\n");


	// Begin main program.
	while (1) {
		length   = sizeof(clientAddr);
		received = recvfrom(sockfd, recvBuffer, 260, 0, (struct sockaddr *)&clientAddr, &length);

		if (received == -1) {
			fprintf(stderr, "Couldn't receive message: %s\n", strerror(errno) );
			continue;
		}


		// Get checksum from received data.
		checksum = (uint8_t)recvBuffer[3 + recvBuffer[1]] | ( (uint8_t)recvBuffer[2 + recvBuffer[1]] << 8);
		// Drop data if checksum is invalid.
		if (checksum != crc16(recvBuffer, 2 + recvBuffer[1]) )
			continue;


		// Format timestamp.
		ltime     = time(NULL);
		timestamp = ctime(&ltime);
		nlpos     = strstr(timestamp, "\n");
		strncpy(nlpos, "\0", 1);


		// Parse commands.
		switch(recvBuffer[0]) {


			case Login:

				if (getUsername(recvBuffer[2]) != NULL)
					printf("%s Login: %s. ", timestamp, getUsername(recvBuffer[2]) );
				if (setIP(inet_ntoa(clientAddr.sin_addr), recvBuffer[2]) == 0)
					printf("IP set to %s.", inet_ntoa(clientAddr.sin_addr) );
				printf("\n");
				continue;


			case RequestIP:
				continue;
		}


		sendto(sockfd, sendBuffer, BufferSize, 0, (struct sockaddr *)&clientAddr, sizeof(clientAddr) );
	}


	finiMySQL(dbCon);
	close(sockfd);
	return EXIT_SUCCESS;
}
