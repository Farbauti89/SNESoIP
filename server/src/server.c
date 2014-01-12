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
	int           options;           // Database.
	char         *confFile = "server.conf";

	struct   sockaddr_in clientAddr; // Server.
	struct   sockaddr_in serverAddr;
	int      sockfd;
	int      length, received;
	char     recvBuffer[BufferSize];
	char     sendBuffer[BufferSize];

	uint16_t checksum;               // Misc.
	char*    timestamp;
	char*    username;
	char*    opponentID;
	char*    ipAddr;


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


		timestamp = getTimestamp();


		// Parse commands.
		switch(recvBuffer[0]) {

			case Login:
				/* +-------+----------+-----------+----------+
					 | Login | LoginLen | Client ID | Checksum |
					 +-------+----------+-----------+----------+ */
				if ( (username = getMySQLrow(Username, recvBuffer[2]) )  == NULL)
					continue;
				printf("%s Login: %s. ", timestamp, username);

				if (setMySQLrow(IPaddress, recvBuffer[2], inet_ntoa(clientAddr.sin_addr) ) == -1)
					continue;
				ipAddr = inet_ntoa(clientAddr.sin_addr);
				printf("IP set to %s.\n", ipAddr);

				sendBuffer[0] = Hello;
				sendBuffer[1] = HelloLen;
				sendBuffer[2] = recvBuffer[2];
				checksum      = crc16(sendBuffer, HelloLen);
				sendBuffer[3] = checksum >> 8;
				sendBuffer[4] = checksum  & 0xff;
				break;


			case RequestIP:
				/* +-----------+--------------+-----------+----------+
					 | RequestIP | RequestIPLen | Client ID | Checksum |
					 +-----------+--------------+-----------+----------+ */
				if (getMySQLrow(Username, recvBuffer[2]) == NULL)
					continue;

				if (getMySQLrow(Username, atoi(getMySQLrow(OpponentID, recvBuffer[2]) ) ) == NULL)
					continue;

				username = getMySQLrow(Username, recvBuffer[2]);
				printf("%s RequestIP: %s requested IP of ", timestamp, username);

				username = getMySQLrow(Username, atoi(getMySQLrow(OpponentID, recvBuffer[2] ) ) );
				printf("%s.\n", username);

				sendBuffer[0] = IP;
				sendBuffer[1] = IPLen;
				// TODO.
				break;
		}


		sendto(sockfd, sendBuffer, BufferSize, 0, (struct sockaddr *)&clientAddr, sizeof(clientAddr) );
	}


	finiMySQL(dbCon);
	close(sockfd);
	return EXIT_SUCCESS;
}
