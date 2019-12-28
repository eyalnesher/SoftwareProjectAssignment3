
#include "game.h"

void create_game_board(SudokuBoard* board, int size) {
	
}

int get_cell(const SudokuBoard* board, int row, int column) {
	if (row < board->board_size && column < board->board_size) {
		return board->board[row * board->board_size + column];
	}
	return -1;
}

void initialize_game() {

}

void do_turn() {

}