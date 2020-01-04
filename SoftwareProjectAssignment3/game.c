
#include "game.h"

#include "solver.h"

#include <stdlib.h>

int create_game_board(SudokuBoard* board, const size_t block_width, const size_t block_height, int hints) {
	board->board_size = block_width * block_height;

	board->board = (SudokuCell*) calloc(board->board_size * board->board_size, sizeof(SudokuCell));
	if (!board->board) {
		return -1;
	}

	board->block_width = block_width;
	board->block_height = block_height;
		
	return 0;
}

void free_game_board(SudokuBoard* board) {
	free(board->board);
}

void clear_game_board(SudokuBoard* board) {
	memset(board->board, 0, board->board_size * board->board_size * sizeof(SudokuCell));
}

/**
 * Return if the place [row, column] exists in the board.
 */
static bool does_cell_exist(const SudokuBoard* board, size_t row, size_t column) {
	return (bool) row < board->board_size && column < board->board_size;
}

/**
 * Return the absulute index (one dimentional) of the cell in place [row, column]
 */
static size_t cell_index(const SudokuBoard* board, size_t row, size_t column) {
	return row * board->board_size + column;
}

/**
 * Retrieve a pointer to the cell at the place [row, column],
 * and pass it to the caller through `cell`.
 * Return 0 if the cell exists, -1 otherwise.
 */
static int get_cell(const SudokuBoard* board, size_t row, size_t column, SudokuCell** cell) {
	if (does_cell_exist(board, row, column)) {
		*cell = board->board + cell_index(board, row, column); 
		return 0;
	}
	return -1;
}

int get_cell_value(const SudokuBoard* board, size_t row, size_t column, int* value) {
	SudokuCell* cell;
	
	if (get_cell(board, row, column, &cell) < 0) {
		return -1;
	}

	*value = cell->value;

	return 0;
}

int is_cell_fixed(const SudokuBoard* board, size_t row, size_t column, bool* is_fixed){
	SudokuCell* cell;

	if (get_cell(board, row, column, &cell) < 0) {
		return -1;
	}
	
	*is_fixed = cell->is_fixed;

	return 0;
}

int set_cell_value(SudokuBoard* board, size_t row, size_t column, int value) {
	SudokuCell* cell;

	if (value < 1 || (size_t) value > board->board_size || get_cell(board, row, column, &cell) < 0) {
		return -1;
	}
	
	if (!cell->is_fixed) {
		cell->value = value;
	}

	return 0;
}

int clear_cell(SudokuBoard* board, size_t row, size_t column) {
	SudokuCell* cell;

	if (get_cell(board, row, column, &cell) < 0) {
		return -1;
	}

	if (!cell->is_fixed) {
		cell->value = 0;
	}

	return 0;
}

/**
 * Set the value of the cell at place [row, column] in `board`, and set it to be fixed.
 */
static int set_cell_fixed(SudokuBoard* board, size_t row, size_t column) {
	SudokuCell* cell;
	
	if (get_cell(board, row, column, &cell) < 0){
		return -1;
	}

	cell->is_fixed = True;

	return 0;
}

int get_cell_hint(SudokuBoard* board, size_t row, size_t column, int* hint) {
	SudokuCell* cell;

	if (get_cell(board, row, column, &cell) < 0) {
		return -1;
	}

	*hint = cell->hint;

	return 0;
}

int set_cell_hint(SudokuBoard* board, size_t row, size_t column, int hint) {
	SudokuCell* cell;

	if (hint < 1 || (size_t)hint > board->board_size || get_cell(board, row, column, &cell)) {
		return -1;
	}

	if (!cell->is_fixed) {
		cell->hint = hint;
	}

	return 0;
}

/* TODO */
static void initialize_game(SudokuBoard* board, int hints) {

}

/**
 * Find the block of the cell at place [row, column] in the board, and pass its top-left 
 * corner coordinates to the caller through `start_block_row`, `start_block_column`.
 * Assumes the cell exists in the board.
 */
static void find_block(const SudokuBoard* board, size_t row, size_t column,
	size_t* start_block_row, size_t* start_block_column) {
	*start_block_row = (row / board->block_height) * board->block_height;
	*start_block_column = (column / board->block_width) * board->block_width;
}

bool is_leagl(const SudokuBoard* board, const size_t row, const size_t column, int value) {
	size_t cell_row, cell_column;
	int cell_value;
	size_t start_block_row, start_block_column;

	/* Search in row */
	for (cell_column = 0; cell_column < board->board_size; cell_column++) {
		get_cell_value(board, row, cell_column, &cell_value); /* Iterating over existing cells only */
		if (cell_value == value) {
			return False; /* An identical value have been found in the same row */
		}
	}

	/* Search in column */
	for (cell_row = 0; cell_row < board->board_size; cell_row++) {
		get_cell_value(board, cell_row, column, &cell_value); /* Iterating over existing cells only */
		if (cell_value == value) {
			return False; /* An identical value have been found in the same column */
		}
	}

	/* Search in block */
	find_block(board, row, column, &start_block_row, &start_block_column);
	for (cell_row = start_block_row; cell_row < start_block_row + board->block_height; cell_row++) {
		for (cell_column = start_block_column; cell_column < start_block_column + board->block_width; cell_column++) {
			get_cell_value(board, cell_row, cell_column, &cell_value); /* Iterating over existing cells only */
			if (cell_value == value) {
				return False; /* An identical value have been found in the same block */
			}
		}
	}

	return True; /* No identical value have been found in the same row, column or block */
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

void generate_board(SudokuBoard* board, size_t fixed) {
	size_t hint_index;
	size_t row, column;
	bool is_fixed;
	int hint;

	clear_game_board(board);
	solve_board(board, random_legal_cell_values); /* The board is empty and therefore solvable */
	for (hint_index = 0; hint_index < fixed; hint_index++) {
		do {
			column = rand() % board->board_size;
			row = rand() % board->board_size;
			is_cell_fixed(board, row, column, &is_fixed);
		} while (is_fixed);

		get_cell_hint(board, row, column, &hint);
		set_cell_value(board, row, column, hint);
		set_cell_fixed(board, row, column);

	}
}

bool validate_board(SudokuBoard* board) {
	return solve_board(board, deterministic_legal_cell_values);
}


/* TODO */
void do_turn(void) {

}
