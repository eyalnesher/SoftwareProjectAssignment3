
#ifndef SOLVER_H
#define SOLVER_H

#include "game.h"

/**
 * Solve the board using backtracking algorithm, with the function
 * `legal_index_generator` to generate every time the index in the of legal
 * values of the next legal value inwhen iterating through all of them.
 * This function gets an ordered list of all the legal values (the list is of size
 * `legal_values_count`) and returns the next value to be iterated.
 * Return if the board is solvable.
 * A wrapper function to `solve_board_recursive`, which begins from the first cell.
 */
bool solve_board(SudokuBoard* board, size_t(*get_next_legal)(size_t legal_values_count));

#endif /* !SOLVER_H */
