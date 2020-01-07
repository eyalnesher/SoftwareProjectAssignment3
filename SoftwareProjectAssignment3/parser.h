
#ifndef PARSER_H
#define PARSER_H

#include "game.h"

#define MAX_ARG_CNT (4)
#define MAX_CHAR_CNT (1024)

/**
 * Run the given coomand
 * Return 0 on success, -1 otherwise.
 */
int run_command(SudokuBoard* board, char* func_name, size_t* func_args, size_t args_count, bool* continue_executing);

/**
 * Get a command and its arguments through stdin, and runs the command
 */
int get_and_run(SudokuBoard* board, bool* continue_executing);

#endif /* !PARSER_H */
