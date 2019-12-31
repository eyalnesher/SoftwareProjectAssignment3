
#ifndef SOLVER_H
#define SOLVER_H

#include "game.h"

/**
 * Generate a board with `fixed` initial fixed cells.
 */
void generate_board(SudokuBoard* board, int fixed);

/**
 * Solve the board from its current state.
 * Change the board to the first solution found (if such solution exists).
 * Return if the board is solvable.
 */
bool validate_board(SudokuBoard* board);

#endif /* !SOLVER_H */
