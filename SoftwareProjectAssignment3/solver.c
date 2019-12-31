
#include "solver.h"

/**
 * Solve the board using backtracking algorithm, with the function
 * `legal_cell_values` to iterate through the values (the function
 * passes to the caller an array of size `max_value` and with values
 * in the range [1, `max_value`] (each value appears once at last),
 * which represents an iterator of the legal values of the cell in
 * the position [row, column], ordered in the wanted iteration order, 
 * and returns the number of legal values. The values of index greater
 * than the legal values number might be garbage values, as they are
 * not ment to be iterated).
 * Return if the board is solvable.
 */
 /* TODO */
static bool solve_board(SudokuBoard* board, 
	size_t (*legal_cell_values)(const SudokuBoard* board, size_t row, size_t column, 
		int* values, size_t max_value)) {
	return True;
}

/**
 * Pass to the caller an array of size `max_value` and with values
 * in the range [1, `max_value`] (each value appears once at last), 
 * which represents an iterator of the legal values of the cell in
 * the position [row, column], ordered from 1 to `max_value`.
 * The values of index greater than the legal values number might
 * be garbage values, as they are not ment to be iterated.
 * Return the number of legal values.
 */
/* TODO */
static size_t deterministic_legal_cell_values(const SudokuBoard* board, size_t row, size_t column, 
	int* values, size_t max_value) {
	return 0;
}

/**
 * Pass to the caller an array of size `max_value` and with values
 * in the range [1, `max_value`] (each value appears once at last),
 * which represents an iterator of the legal values of the cell in
 * the position [row, column], ordered randomly.
 * The values of index greater than the legal values number might
 * be garbage values, as they are not ment to be iterated.
 * Return the number of legal values.
 */
/* TODO */
static size_t random_legal_cell_values(const SudokuBoard* board, size_t row, size_t column, 
	int* values, size_t max_value) {
	return 0;
}

/* TODO */
void generate_board(SudokuBoard* board, int fixed) {

}

/* TODO */
bool validate_board(SudokuBoard* board) {
	return True;
}
