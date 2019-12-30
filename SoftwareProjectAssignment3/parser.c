
#include "parser.h"

#include <stdlib.h>

/**
 * Split a string into an array of `max_args` strings, using `delimiter` as a delimiter,
 * and pass it to the caller through `parsed_string`.
 * Return the number of the generated strings.
 */
static int parse_deliminator(char* str, char* delimiter, char** parsed_string, size_t max_args) {
	char* token;
	int count = 0;

	token = strtok(str, delimiter);

	while (token && count < max_args) {
		parsed_string[count++] = token;
		token = strtok(NULL, delimiter);
	}

	return parsed_string;
}

int parse_and_run(char* str_input, int str_len) {
	char* parsed_string[MAX_ARG_CNT];
	int arg_count = parse_deliminator(str_input, " ", parsed_string, MAX_ARG_CNT);
	return -1;
}
