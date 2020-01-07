
#include "solver.h"

#include <stdlib.h>
#include <string.h>

/**
 * A generator which gets an ordered list of all the legal values (the list is of size
 * `legal_values_count`), and generates the next value to be iterated.
 * The value in the given index would be deleted.
 * Return a value from `legal_values`.
 */
static size_t get_next_legal(size_t* legal_values, size_t legal_values_count,
	size_t (*legal_index_generator)(size_t legal_values_count)) {
	size_t index = legal_index_generator(legal_values_count);
	size_t value = legal_values[index];
	if (index < legal_values_count - 1) {
		/* Delete the value by overriding it with the values after it */
		memmove(legal_values + index, legal_values + index + 1, (legal_values_count - index - 1) * sizeof(int));
	}
	return value;
}

/**
 * Pass to the caller all the legal values of the cell at place [row, column] in the board.
 * Return the number of legal values.
 */
static size_t get_all_legal(const SudokuBoard* board, size_t row, size_t column, size_t* legal_values) {
	size_t value = 1;
	size_t values_count = 0;

	while (value <= board->board_size) {
		if (is_leagl(board, row, column, value)) {
			legal_values[values_count] = value;
			values_count++;
		}
		value++;
	}

	return values_count;
}

/**
 * Solve the board using backtracking algorithm, with the function
 * `legal_index_generator` to generate every time the index in the of legal
 * values of the next legal value inwhen iterating through all of them.
 * Solve the board recursively from the cell at place [row, column].
 * Return if the board is solvable.
 */
static bool solve_board_recursive(SudokuBoard* board, size_t row, size_t column,
	size_t (*legal_index_generator)(size_t legal_values_count)) {
	size_t* legal_values;
	size_t values_count;
	size_t next_row = row, next_column = column + 1;
	size_t value;
	
	/* Base case - all of the board cells are solved */
	if (row >= board->board_size) {
		return True;
	}

	legal_values = (size_t*) malloc(board->board_size * sizeof(size_t));
	if (!legal_values) {
		return False;
	}

	/* Get all legal values */
	values_count = get_all_legal(board, row, column, legal_values);

	/* Moving  from left to right, then top to bottom */
	if (next_column == board->board_size) {
		next_column = 0;
		next_row++;
	}

	value = get_cell_value(board, row, column);
	if (value > 0) {
		/* The cell already has a value */
		free(legal_values);
		return solve_board_recursive(board, next_row, next_column, legal_index_generator);
	}
	else {
		/* Try to solve the board recursively for every potential value */
		for (; values_count > 0; values_count--) {
			set_cell_value(board, row, column, get_next_legal(legal_values, values_count, legal_index_generator));

			if (solve_board_recursive(board, next_row, next_column, legal_index_generator)) {
				/* The solution is correct (and therefore the board is solvable) */
				value = get_cell_value(board, row, column);
				clear_cell(board, row, column); /* We don't want the user to see the solution */
				set_cell_hint(board, row, column, value); /* The current value is a possible value of the sudoku cell */
				free(legal_values);
				return True;
			}
		}
	}

	/* The board is not solvable */
	clear_cell(board, row, column); /* We don't want the user to see the (wrong) solution */
	free(legal_values);
	return False;
}

bool solve_board(SudokuBoard* board, 
	size_t (*get_next_legal)(size_t legal_values_count)) {
	return solve_board_recursive(board, 0, 0, get_next_legal);
}
