
#ifndef MAIN_AUX_H
#define MAIN_AUX_H

#include "game.h"

/**
 * Get user inputs for game initialization - number of fixed cells.
 * set the value of `fixed_cells` to be the number of fixed cells.
 * Return 0 if succeded, -1 otherwise.
 */
int user_input_setup(int* fixed_cells);

void print_board(SudokuBoard* board);

#endif /* !MAIN_AUX_H */
