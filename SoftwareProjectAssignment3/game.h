
#include <stddef.h>

#ifndef GAME_H
#define GAME_H

typedef struct {
	size_t board_size;
	size_t cell_width;
	size_t cell_height;
	int* board;
} SudokuBoard;

void create_game_board(SudokuBoard* board, int size);
void free_game_board(SudokuBoard board);

void initialize_game();
void do_turn();

#endif /* !GAME_H */
