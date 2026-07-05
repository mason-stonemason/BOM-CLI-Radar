#pragma once

#include <string.h>
#include <stdbool.h>

//struct to hold CLI parameter values
typedef struct {
	bool output; //-o | --output
	char* filePath; //optional filePath from --output
	bool noColour; //-nc | --no-colour
	char* location; //suburb
} UserValues;

UserValues set_user_values(int argc, char* argv[]);
void file_path(UserValues* cli);
