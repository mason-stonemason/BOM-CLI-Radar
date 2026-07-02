#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define PROGRAM_NAME "bomcli"
//messages
const char* const usageMessage = "Usage: bomcli [-o | --output <filePath>] [-i | --interact] location\n";

//error
const char* const invalidPath = "Invalid filepath.\n";
const char* const invalidLocation = "Invalid location.\n";
const char* const invalidFile = "Couldn't make file (\"bomcli.txt\"), try checking permissions or space.\n";

typedef enum {
	INVALID_USAGE_EXIT = 1,
	INVALID_FILEPATH_EXIT = 2,
	INVALID_LOCATION_EXIT = 3,
	INVALID_FILE_EXIT = 4
} ErrorCodes;

//struct to hold CLI parameter values
typedef struct {
	bool output; //-o | --output
	char* filePath; //optional filePath from --output
	bool interact; //-i | --interact
	char* location; //suburb
} UserValues;

UserValues set_user_values(int argc, char* argv[]);
void file_path(UserValues* cli);

int main(int argc, char* argv[])
{
	UserValues cli = set_user_values(argc, argv);
	if (cli.output) {
		file_path(&cli);
	}
}

/**
 * @brief exiting function for usage errors
 */
void exit_usage(void)
{
	fprintf(stderr, "%s", usageMessage);
	exit(INVALID_USAGE_EXIT);
}
/**
 * @brief this function parses the CLI into a UserValues struct
 * @param argc - the argument count
 * @param argv - the argument value
 * @returns the parsed CLI in the form of UserValues
 */
UserValues set_user_values(int argc, char* argv[])
{
	UserValues user = {.output = false};
	argv++;

	if (argc < 2) {
		exit_usage();
	}

	while (argv[0]) {
	    	if (!strcmp(argv[0], "-o") || !strcmp(argv[0], "--output")) {
			if (user.output) {
				exit_usage();
			}
			user.output = true;
			argv++;
			if (argv[0] && (!strncmp(argv[0], "--", 2) || !strncmp(argv[0], "-", 1))) {
				user.filePath = argv[0];
				argv++;
			}
		} else if (!strcmp(argv[0], "-i") || !strcmp(argv[0], "--interact")) {
			if (user.interact) {
				exit_usage();
			}
			user.interact = true;
			argv++;
		} else { //TODO: make that last location parameter!
			exit_usage();
		}
	}

	return user;
}

/**
 * @brief exiting function for file errors
 */
void exit_file(void)
{
	fprintf(stderr, "%s", invalidPath);
	exit(INVALID_FILEPATH_EXIT);
}

/**
 * @brief exiting function for file log creation errors.
 */
void exit_file_create(void)
{
	fprintf(stderr, "%s", invalidFile);
	exit(INVALID_FILE_EXIT);
}

/**
 * @brief determines whether file path is valid, and creates one if not specified
 * @param cli - to get the filepath from.
 */
void file_path(UserValues* cli)
{
	if (cli->filePath) {
		FILE* file = fopen(cli->filePath, "r");
		if (file == NULL) {
			exit_file();
		}
		fclose(file);
	} else {
		FILE* file = fopen("bomcli.txt", "w");
		if (file == NULL) {
			exit_file_create();
		}
		fclose(file);
	}


}
