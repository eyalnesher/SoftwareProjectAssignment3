
#include "game.h"

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

int get_cell(const SudokuBoard* board, size_t row, size_t column, int* value) {
	if (row < board->board_size && column < board->board_size) {
		*value = board->board[row * board->board_size + column].value; 
		return 0;
	}
	return -1;
}

int set_cell(SudokuBoard* board, size_t row, size_t column, int value) {
	SudokuCell cell;

	if (value >= 1 && row < board->board_size && column < board->board_size && (size_t) value <= board->board_size) {
		cell = board->board[row * board->board_size + column];

		if (!cell.is_fixed) {
			cell.value = value; 
		}
		return 0;
	}
	return -1;
}

static void initialize_game(SudokuBoard* board, int hints) {

}

void do_turn(void) {

}
