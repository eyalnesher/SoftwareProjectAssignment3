
#include <stddef.h>

#ifndef GAME_H
#define GAME_H

#define True (1)
#define False (0)

typedef char bool;

/**
 * A structure which represents a sudoku cell (its value and whether it's a fixed cell)
 */
typedef struct {
    int value; /* The current value of the sudoku cell. 0 represents no value. */
	int hint; /* A possible value of the sudoku cell. Use to generate hints. 0 represents no value. */
    bool is_fixed; /* Whether the cell is fixed or not */
} SudokuCell;

/**
 * A structure which represents the sudoku board.
 */
typedef struct {
	size_t board_size; /* The width/height of the board (the board is `board_size` x `board_size`) */
	size_t block_width; /* The width of a board's block (the block is `block_width` x `block_height`) */
	size_t block_height; /* The height of a board's block (the block is `block_width` x `block_height`) */
	SudokuCell* board; /* An array of the board's cells */
} SudokuBoard;

/**
 * Create a `SudokuBoard` object of block sizes `block_width` x `block_height`
 * and with `hints` fixed cells, and pass it to the caller through `board`.
 * Return 0 on success, -1 otherwise (can fail due to memory allocation failure).
 */
int create_game_board(SudokuBoard* board, const size_t block_width, const size_t block_height, int hints);

/**
 * Cleanup the given `SudokuBoard` object.
 */
void free_game_board(SudokuBoard* board);

/**
 * Retrieve the cell value at the given position in the board,
 * and pass it to the caller through `value`.
 * Return 0 if the cell exists, -1 otherwise.
 */
int get_cell_value(const SudokuBoard* board, size_t row, size_t column, int* value);

/**
 * Retrieve whether the cell at the given position is a fixed cell,
 * and pass it to the caller through `is_fixed`.
 * Return 0 if the cell exists, -1 otherwise.
 */
int is_cell_fixed(const SudokuBoard* board, size_t row, size_t column, bool* is_fixed);

/**
 * Set the value of the cell at the given position if its not a fixed cell.
 * Return 0 if the cell exists, -1 otherwise.
 */
int set_cell_value(SudokuBoard* board, size_t row, size_t column, int value);

/**
 * Clear  the cell at the given position (set its value to be the default value).
 * Return 0 if the cell exists and the value is valid, -1 otherwise.
 */
int clear_cell(SudokuBoard* board, size_t row, size_t column);

/**
 * Set the hint of the cell at the given position if its not a fixed cell.
 * Return 0 if the cell exists, -1 otherwise.
 */
int set_cell_hint(SudokuBoard* board, size_t row, size_t column, int hint);

/**
 * Return if the value `value` is legal for the cell in [row, column] in `board`
 * (there is no identical value in the same row, column or block).
 */
bool is_leagl(const SudokuBoard* board, size_t row, size_t column, int value);

void do_turn(void);

#endif /* !GAME_H */
