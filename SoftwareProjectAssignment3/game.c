
#include "game.h"

#include <stdlib.h>

int create_game_board(SudokuBoard* board, const int n, const int m, int hints) {
	board->board_size = n * m;
	board->board = (int*) calloc(board->board_size * board->board_size, sizeof(int));
	if (!board->board) {
		return -1;
	}
	board->block_width = n;
	board->block_height = m;
	board->hints = hints;		
	return 0;
}

void free_game_board(SudokuBoard* board) {
	(void) board;
}

int get_cell(const SudokuBoard* board, size_t row, size_t column, int* value) {
	if (row < board->board_size && column < board->board_size) {
		*value = board->board[row * board->board_size + column]; 
		return 0;
	}
	return -1;
}

int set_cell(SudokuBoard* board, size_t row, size_t column, int value) {
	if (value >= 1 && row < board->board_size && column < board->board_size && (size_t) value <= board->board_size) {
		board->board[row * board->board_size + column] = value;
		return 0;
	}
	return -1;
}

void initialize_game(SudokuBoard* board, size_t board_size, size_t block_width, size_t block_height, int hints) {

}

void do_turn(void) {

}
