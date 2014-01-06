/* server.c -*-c-*-
 * SNESoIP server.
 * Author: Michael Fitzmayer
 *
 * This program is part of the SNESoIP project and has has been released
 * under the terms of a BSD-like license.  See the file LICENSE for
 * details. */


#include "server.h"


int main(int argc, char* argv[]) {
	struct sockaddr_in clientAddr, serverAddr;
	int    opt, len, received, sockfd;
	char   recvBuffer[BufferSize];
	char   sendBuffer[BufferSize];
	char  *configfd = "server.cfg";


	puts(" _______ _______ _______ _______         _______ ______");
	puts("|     __|    |  |    ___|     __|.-----.|_     _|   __ \\");
	puts("|__     |       |    ___|__     ||  _  | _|   |_|    __/");
	puts("|_______|__|____|_______|_______||_____||_______|___|   server\n");
	puts("-c <config>\tload specific config file (defalt: server.cfg).\n");


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
	sockfd                     = socket(AF_INET, SOCK_DGRAM, 0);
	serverAddr.sin_family      = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port        = htons(57350);

	if ((bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr))) == -1) {
		fprintf(stderr, "Couldn't bind name to socket: %s\n", strerror(errno));
		return EXIT_FAILURE;

	} else
		puts("Listening on port 57350.\n");





	char *teststring = "123456789";
	printf("0x%x\n", crc16(teststring, strlen(teststring)));


	while (1) {
		len = sizeof(clientAddr);
		received = recvfrom(sockfd, recvBuffer, BufferSize, 0, (struct sockaddr *)&clientAddr, &len);

		if (received == -1) {
			fprintf(stderr, "Couldn't receive message: %s\n", strerror(errno));
			continue;
		}








		//getip:   "SELECT currentip FROM snesoip_hw WHERE hwid = %hwid%";
		//setip:   "UPDATE snesoip_hw SET currentip = '%ip%' WHERE hwid = %hwid%;"
		//getuser: "


		//sendto(sockfd, &data, BufferSize, 0, (struct sockaddr *)&clientAddr, sizeof(clientAddr));

	}




	finiMySQL();
	close(sockfd);
	return EXIT_SUCCESS;
}


char* uint16_t2bin(uint16_t num) {
	int   bitStrLen = sizeof(uint16_t) * 8 * sizeof(char);
	char* bin       = (char*)malloc(bitStrLen);

	for (int i = (bitStrLen - 1); i >= 0; i--) {
		int k = 1 & num;
		*(bin + i) = ((k == 1) ? '1' : '0');
		num >>= 1;
	}

	bin[16] = '\0';

	return bin;
}
