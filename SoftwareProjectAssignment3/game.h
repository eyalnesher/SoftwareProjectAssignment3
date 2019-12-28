
#include <stddef.h>

#ifndef GAME_H
#define GAME_H

/**
 * A structure which represents the sudoku board.
 */
typedef struct {
	size_t board_size; /* The width/height of the board (the board is `board_size` x `board_size`) */
	size_t block_width; /* The width of a board's block (the block is `block_width` x `block_height`) */
	size_t block_height; /* The height of a board's block (the block is `block_width` x `block_height`) */
	int* board; /* An array of the board's cells */
	int hints; /* The number of fixed cells ("hints") */
} SudokuBoard;

int create_game_board(SudokuBoard* board, const int n, const int m);

void free_game_board(SudokuBoard* board);

int get_cell(const SudokuBoard* board, size_t row, size_t column, int* value);

int set_cell(SudokuBoard* board, size_t row, size_t column, int value);

void initialize_game(SudokuBoard* board, size_t board_size, size_t block_width, size_t block_height, int hints);

void do_turn(void);

#endif /* !GAME_H */
