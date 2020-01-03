
#include "solver.h"

/**
 * Solve the board using backtracking algorithm, with the function `get_next_legal`
 * to generate every time the next legal value when iterating through all of them.
 * This function gets an ordered list of all the legal values (the list is of size
 * `legal_values_count`) and returns the next value to be iterated.
 * Return if the board is solvable.
 */
 /* TODO */
static bool solve_board(SudokuBoard* board, 
	int (*get_next_legal)(int* legal_values, size_t legal_values_count)) {
	return True;
}

/**
 * A generator which gets an ordered list of all the legal values (the list is of size
 * `legal_values_count`), and generates deterministically the next value to be iterated.
 * Return the first value the list.
 */
/* TODO */
static int deterministic_legal_cell_values(int* legal_values, size_t legal_values_count) {
	return 0;
}

/**
 * A generator which gets an ordered list of all the legal values (the list is of size
 * `legal_values_count`), and generates randomly the next value to be iterated.
 * Return a random value from the list.
 */
/* TODO */
static int random_legal_cell_values(int* legal_values, size_t legal_values_count) {
	return 0;
}

/* TODO */
void generate_board(SudokuBoard* board, int fixed) {

}

/* TODO */
bool validate_board(SudokuBoard* board) {
	return True;
}
