
#ifndef PARSER_H
#define PARSER_H

#define MAX_ARG_CNT (4)

/**
 * Parse a commant from the user and runs it.
 * Return 0 on success, -1 otherwise.
 */
int parse_and_run(char* str_input, int str_len);

#endif /* !PARSER_H */
