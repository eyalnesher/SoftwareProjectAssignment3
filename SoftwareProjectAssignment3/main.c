
#include "game.h"
#include "main_aux.h"
#include "parser.h"

#include <stdlib.h>

int main(int argc, char* argv[]) {
	int ret;
	int fixed_cells;
	SudokuBoard game_board;
	bool execute = True, won_game = False;
	
	if (user_input_setup(&fixed_cells) < 0) {
		return 0;
	}

	srand(argc > 1 ? atoi(argv[1]) : 5);

	create_game_board(&game_board, 3, 3, (int) fixed_cells);

	print_board(&game_board);
	
	while (execute) {
		ret = get_and_run(&game_board, &execute, &won_game);
		
		if (!ret) {
			print_board(&game_board);
		}

		if (won_game){
			printf("Puzzle solved successfully\n");
		}
	}

	return 0;
}
