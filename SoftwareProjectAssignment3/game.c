
#include "game.h"

#include "solver.h"

#include <stdlib.h>
#include <string.h>

static void generate_board(SudokuBoard* board, size_t fixed);

int create_game_board(SudokuBoard* board, const size_t block_width, const size_t block_height, int hints) {
	board->board = NULL;
	return restart_board(board, block_width, block_height, hints);
}

void free_game_board(SudokuBoard* board) {
	free(board->board);
}

void clear_game_board(SudokuBoard* board) {
	memset(board->board, 0, board->board_size * board->board_size * sizeof(SudokuCell));
	board->filled_cells = 0;
}

int restart_board(SudokuBoard* board, const size_t block_width, const size_t block_height, size_t hints) {
	SudokuCell* new_board;
	size_t board_size = block_width * block_height;

	/* Allocate memory for the board */
	new_board = (SudokuCell*) realloc(board->board, sizeof(SudokuCell) * board_size * board_size);
	if (!new_board) {
		return -1;
	}
	board->board = new_board;

	/* Set dimentions */
	board->block_width = block_width;
	board->block_height = block_height;
	board->board_size = board_size;

	/* Generate an initial solution */
	generate_board(board, hints);

	return 0;
}

bool is_solved(SudokuBoard* board) {
	return board->filled_cells == board->board_size * board->board_size;
}

/**
 * Return if the place [row, column] exists in the board.
 */
static bool does_cell_exist(const SudokuBoard* board, size_t row, size_t column) {
	return row < board->board_size && column < board->board_size;
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
static void get_cell(const SudokuBoard* board, size_t row, size_t column, SudokuCell** cell) {
	if (does_cell_exist(board, row, column)) {
		*cell = board->board + cell_index(board, row, column); 
	}
}

size_t get_cell_value(const SudokuBoard* board, size_t row, size_t column) {
	SudokuCell* cell;
	size_t value;
	
	get_cell(board, row, column, &cell);

	value = cell->value;

	return value;
}

int is_cell_fixed(const SudokuBoard* board, size_t row, size_t column){
	SudokuCell* cell;

	get_cell(board, row, column, &cell);
	
	return cell->is_fixed;
}

int set_cell_value(SudokuBoard* board, size_t row, size_t column, size_t value) {
	SudokuCell* cell;

	get_cell(board, row, column, &cell);

	if (value == 0 && cell->value > 0) {
		board->filled_cells--;
	} else if (value > 0 && cell->value == 0) {
		board->filled_cells++;
	}

	cell->value = value;

	return 0;
}

int legal_set_cell_value(SudokuBoard* board, size_t row, size_t column, size_t value) {
	SudokuCell* cell;

	get_cell(board, row, column, &cell);

	if (cell->is_fixed) {
		printf("Error: cell is fixed\n");
		return -1;
	}

	if (value == 0 || is_legal(board, row, column, value)) {
		set_cell_value(board, row, column, value);
		return 0;
	}

	printf("Error: value is invalid\n");
	return -1;

}

void clear_cell(SudokuBoard* board, size_t row, size_t column) {
	set_cell_value(board, row, column, 0);
}

/**
 * Set the value of the cell at place [row, column] in `board`, and set it to be fixed.
 */
static int set_cell_fixed(SudokuBoard* board, size_t row, size_t column) {
	SudokuCell* cell;
	
	get_cell(board, row, column, &cell);

	cell->is_fixed = True;

	return 0;
}

size_t get_cell_hint(SudokuBoard* board, size_t row, size_t column) {
	SudokuCell* cell;

	get_cell(board, row, column, &cell);

	return cell->hint;
}

int set_cell_hint(SudokuBoard* board, size_t row, size_t column, size_t hint) {
	SudokuCell* cell;

	if (hint < 1 || (size_t) hint > board->board_size) {
		return -1;
	}

	get_cell(board, row, column, &cell);

	if (!cell->is_fixed) {
		cell->hint = hint;
	}

	return 0;
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

bool is_legal(const SudokuBoard* board, const size_t row, const size_t column, size_t value) {
	size_t cell_row, cell_column;
	size_t cell_value;
	size_t start_block_row, start_block_column;

	/* Search in row */
	for (cell_column = 0; cell_column < board->board_size; cell_column++) {
		if (cell_index(board, row, column) != cell_index(board, row, cell_column)) {
			cell_value = get_cell_value(board, row, cell_column); /* Iterating over existing cells only */
			if (cell_value == value) {
				return False; /* An identical value have been found in the same row */
			}
		}
	}

	/* Search in column */
	for (cell_row = 0; cell_row < board->board_size; cell_row++) {
		if (cell_index(board, row, column) != cell_index(board, cell_row, column)) {
			cell_value = get_cell_value(board, cell_row, column); /* Iterating over existing cells only */
			if (cell_value == value) {
				return False; /* An identical value have been found in the same column */
			}
		}
	}

	/* Search in block */
	find_block(board, row, column, &start_block_row, &start_block_column);
	for (cell_row = start_block_row; cell_row < start_block_row + board->block_height; cell_row++) {
		for (cell_column = start_block_column; cell_column < start_block_column + board->block_width; cell_column++) {
			if (cell_index(board, row, column) != cell_index(board, cell_row, cell_column)) {
				cell_value = get_cell_value(board, cell_row, cell_column); /* Iterating over existing cells only */
				if (cell_value == value) {
					return False; /* An identical value have been found in the same block */
				}
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
	(void) legal_values_count; /* There is no use for `legal_values_count` */
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

/**
 * Generate a board with `fixed` initial fixed cells.
 */
static void generate_board(SudokuBoard* board, size_t fixed) {
	size_t hint_index;
	size_t row, column;
	bool is_fixed;
	size_t hint;

	clear_game_board(board);
	solve_board(board, random_legal_cell_values); /* The board is empty and therefore solvable */
	for (hint_index = 0; hint_index < fixed; hint_index++) {
		do {
			column = rand() % board->board_size;
			row = rand() % board->board_size;
			is_fixed = is_cell_fixed(board, row, column);
		} while (is_fixed);

		hint = get_cell_hint(board, row, column);
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

void exit_game(void) {
}

void restart_game(SudokuBoard* board) { (void) board; }
