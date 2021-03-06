
#include <stddef.h>

#ifndef GAME_H
#define GAME_H

#define True (1)
#define False (0)

typedef int bool;

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
	int board_size; /* The width/height of the board (the board is `board_size` x `board_size`) */
	int block_width; /* The width of a board's block (the block is `block_width` x `block_height`) */
	int block_height; /* The height of a board's block (the block is `block_width` x `block_height`) */
	SudokuCell* board; /* An array of the board's cells */
	int filled_cells;
} SudokuBoard;

/**
 * Create a `SudokuBoard` object of block sizes `block_width` x `block_height`
 * and with `hints` fixed cells, and pass it to the caller through `board`.
 * Return 0 on success, -1 otherwise (can fail due to memory allocation failure).
 */
int create_game_board(SudokuBoard* board, const int block_width, const int block_height, int hints);

/**
 * Cleanup the given `SudokuBoard` object.
 */
void free_game_board(SudokuBoard* board);

/**
 * Clear the given `SudokuBoard` object, by setting all the fields to their default values.
 */
void clear_game_board(SudokuBoard* board);

/**
 * Return if all the cells are filled.
 */
bool is_solved(SudokuBoard* board);

/**
 * Return the cell value at the given position in the board.
 */
int get_cell_value(const SudokuBoard* board, int row, int column);

/**
 * Return the cell at the given position is a fixed cell.
 */
bool is_cell_fixed(const SudokuBoard* board, int row, int column);

/**
 * Set the value of the cell at the given position if its not a fixed cell.
 * Return 0 if value is valid, -1 otherwise.
 */
int set_cell_value(SudokuBoard* board, int row, int column, int value);

int legal_set_cell_value(SudokuBoard* board, int row, int column, int value);

/**
 * Clear the cell at the given position (set its value to be the default value).
 */
void clear_cell(SudokuBoard* board, int row, int column);

/**
 * Return the hint of the cell at the given position if its not a fixed cell.
 */
int get_cell_hint(SudokuBoard* board, int row, int column);

/**
 * Set the hint of the cell at the given position if its not a fixed cell.
 * Return 
 */
int set_cell_hint(SudokuBoard* board, int row, int column, int hint);

/**
 * Return if the value `value` is legal for the cell in [row, column] in `board`
 * (there is no identical value in the same row, column or block).
 */
bool is_legal(const SudokuBoard* board, const int row, const int column, int value);

/**
 * Solve the board from its current state.
 * Change the board to the first solution found (if such solution exists).
 * Return if the board is solvable.
 */
bool validate_board(SudokuBoard* board);

/**
 * Restart the board with new dimentions and number of fixed cells.
 * Return 0 on success, -1 otherwise (can fail due to memory allocation failure).
 */
int restart_board(SudokuBoard* board, const int block_width, const int block_height, int hints);

/**
 * Exit the game.
 */
void exit_game(void);

#endif /* !GAME_H */
