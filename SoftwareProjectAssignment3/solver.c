
#include "solver.h"

#include <string.h>

/**
 * A generator which gets an ordered list of all the legal values (the list is of size
 * `legal_values_count`), and generates the next value to be iterated.
 * The value in the given index would be deleted.
 * Return a value from `legal_values`.
 */
static int get_next_legal(int* legal_values, size_t legal_values_count,
	size_t (*legal_index_generator)(size_t legal_values_count)) {
	int index = legal_index_generator(legal_values_count);
	int value = legal_values[index];
	if (index < legal_values_count - 1) {
		/* Delete the value by overriding it with the values after it */
		memmove(legal_values + index, legal_values + index + 1, legal_values_count - index - 1);
	}
	return value;
}

/**
 * Solve the board using backtracking algorithm, with the function
 * `legal_index_generator` to generate every time the index in the of legal
 * values of the next legal value inwhen iterating through all of them.
 * Solve the board recursively from the cell at place [row, column].
 * Return if the board is solvable.
 */
/* TODO */
static bool solve_board_recursive(SudokuBoard* board, size_t row, size_t column,
	size_t (*legal_index_generator)(size_t legal_values_count)) {
	return False;
}

/**
 * Solve the board using backtracking algorithm, with the function
 * `legal_index_generator` to generate every time the index in the of legal
 * values of the next legal value inwhen iterating through all of them.
 * This function gets an ordered list of all the legal values (the list is of size
 * `legal_values_count`) and returns the next value to be iterated.
 * Return if the board is solvable.
 * A wrapper function to `solve_board_recursive`, which begins from the first cell.
 */
static bool solve_board(SudokuBoard* board, 
	size_t (*get_next_legal)(size_t legal_values_count)) {
	return solve_board_recursive(board, 0, 0, get_next_legal);
}

/**
 * Generate deterministically the index of the next value to be iterated in a list
 * of legal values.
 * Return the first value the list.
 */
static size_t deterministic_legal_cell_values(size_t legal_values_count) {
	return 0;
}

/**
 * Generate randomly the index of the next value to be iterated in a list
 * of legal values.
 * Return the first value the list.
 */
static size_t random_legal_cell_values(size_t legal_values_count) {
	return legal_values_count > 1 ? rand() % legal_values_count : 0;
}

/* TODO */
void generate_board(SudokuBoard* board, int fixed) {

}

/* TODO */
bool validate_board(SudokuBoard* board) {
	return True;
}
