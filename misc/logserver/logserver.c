/* logserver.c -*-c-*-
 * Proof-of-concept log parser.
 * Copyright (c) 2013 Michael Fitzmayer.  All rights reserved.
 *
 * This program has has been released under the terms of a BSD-like
 * license.  See the file LICENSE for details. */


#include <netinet/in.h>
#include <sys/socket.h>
#include <errno.h>
#include <getopt.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef uint16_t snesIO;


char lastLine[240];


void setLastLine(FILE *file);
int  getFileSize(FILE *file);


int main(int argc, char* argv[]) {
	struct sockaddr_in clientAddr, serverAddr;
	int      index = 0;
	int      logsize = 0;
	int      opt, len, received, sockfd;
	char     recvBuffer[4];
	char     cache[240];
	char    *logfile = "default.log";
	FILE    *logfd;
	snesIO   data;


	puts(" __");
	puts("|  |.-----.-----.-----.-----.----.--.--.-----.----.");
	puts("|  ||  _  |  _  |__ --|  -__|   _|  |  |  -__|   _|");
	puts("|__||_____|___  |_____|_____|__|  \\___/|_____|__|");
	puts("          |_____| for SNESoIP\n");
  puts("-l <logfile>\tload specific logfile file (defalt: default.log).\n");


  // Parse command-line arguments.
  while ((opt = getopt(argc, argv, "c:")) != -1)
    switch (opt) {
      case 'c':
				logfile = optarg;
        break;
		}


	// Open log and retreive last line.
	logfd = fopen(logfile, "r");
	if (! logfd) {
		fprintf(stderr, "%s could not be opened.\n", logfile);
		return EXIT_FAILURE;
	}
	setLastLine(logfd);
	memcpy(cache, lastLine, 240);


	// Setting up the server.
	sockfd                     = socket(AF_INET, SOCK_DGRAM, 0);
	serverAddr.sin_family      = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port        = htons(57350);

	if ((bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr))) == -1) {
		fprintf(stderr, "Couldn't bind name to socket: %s\n", strerror(errno));
		return 1;

	} else
		printf("Listening on port 57350\n\n");


	while (1) {
		len = sizeof(clientAddr);
		received = recvfrom(sockfd, recvBuffer, 4, 0, (struct sockaddr *)&clientAddr, &len);
		if (received == -1) {
			fprintf(stderr, "Couldn't receive message: %s\n", strerror(errno));
			continue;
		}

		data = 0xffff - lastLine[index];
		sendto(sockfd, &data, 2, 0, (struct sockaddr *)&clientAddr, sizeof(clientAddr));

		if (data != 0xffff)
			index++;

		if (data == 0xffff) {
			memcpy(cache, lastLine, 240);
			setLastLine(logfd);
			if (strcmp(cache, lastLine) == 0)
				data = 0xffff;
			else {
				printf("%s", lastLine);
				index = 0;
			}
		}
	}


	close(sockfd);
	fclose(logfd);
	return 0;
}


void setLastLine(FILE *file) {
	int offsetStart = 0;
	int offsetEnd   = 0;
	int i, tmp = 0;

	while (fgetc(file) != EOF)
		offsetEnd++;
	offsetEnd = offsetEnd - 2;

	offsetStart = offsetEnd;
	while (fgetc(file) != '\n') {
		fseek(file, offsetStart, SEEK_SET);
		offsetStart--;
		if (offsetStart < 0) break;
	}
	offsetStart = offsetStart + 2;

	for (i = offsetStart; i <= offsetEnd; i++) {
		fseek(file, i, SEEK_SET);
		lastLine[tmp] = fgetc(file);
		tmp++;
		if (tmp > 237) break;
	}
	lastLine[tmp]   = '\n';
	lastLine[tmp+1] = '\0';

	fseek(file, 0, SEEK_SET);
}
