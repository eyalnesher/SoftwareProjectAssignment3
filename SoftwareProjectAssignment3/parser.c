
#include "parser.h"

#define NULL (0) /* WTF? why isnt it already defined? */

static char** parse_delim(char* str, char* delim, int* arg_count) {
	char* parsed_string[MAX_ARG_CNT];
	char* token;
	int cnt = 0;

	token = strtok(str, delim);

	while (token && cnt < MAX_ARG_CNT) {
		parsed_string[cnt++] = token;
		token = strtok(NULL, delim);
	}
	*arg_count = cnt;

	return parsed_string;
}

int parse_and_run(char* str_inp, int str_len) {
	char** parsed_string;
	int arg_count;

	parsed_string = parse_delim(str_inp, " ", &arg_count);


	return 0;
}