
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
 * and with `hints` fixed cells, and returns it through `board`.
 * Return 0 on success, -1 otherwise (can fail due to memory allocation failure).
 */
int create_game_board(SudokuBoard* board, const size_t block_width, const size_t block_height, int hints);

/**
 * Cleanup the given `SudokuBoard` object.
 */
void free_game_board(SudokuBoard* board);

/**
 * Retrieve the cell at the given position in the board.
 */
int get_cell(const SudokuBoard* board, size_t row, size_t column, int* value);

/**
 * Set the value of the cell at the given position if its not a fixed cell
 */
int set_cell(SudokuBoard* board, size_t row, size_t column, int value);

void do_turn(void);

#endif /* !GAME_H */
