
#ifndef PARSER_H
#define PARSER_H

#include "game.h"
#include "main_aux.h"

#define MAX_ARG_CNT (4)
#define MAX_CHAR_CNT (1024)

/**
 * Run the given coomand
 * Return 0 on success, -1 otherwise.
 */
int run_command(SudokuBoard* board, char* func_name, int* func_args, int args_count, bool* continue_executing, bool* won);

/**
 * Get a command and its arguments through stdin, and runs the command
 */
int get_and_run(SudokuBoard* board, bool* continue_executing, bool* won_game);

#endif /* !PARSER_H */
