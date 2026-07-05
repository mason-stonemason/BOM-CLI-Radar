#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

#define CONTROL_PORT 21
#define DATA_PORT 20

const char* const ftpServer = "ftp.bom.gov.au/anon/gen/";

//error
const char* const socketError = "Unable to create socket.\n";
const char* const imageryError = "Latest radar imagery unavailable.\n";
const char* const controlError = "Control port unavailable\n";
const char* const dataError = "Data port unavailable\n";

//exit codes
typedef enum {
	EXIT_SOCKET = 6,
	EXIT_IMAGERY = 51
} ExitCodes;

int main(void)
{
	int controlSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (controlSocket < 0) {
		fprintf(stderr, "%s", socketError);
		exit(EXIT_SOCKET);
	}
}
