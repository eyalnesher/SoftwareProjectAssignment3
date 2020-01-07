
#include "game.h"
#include "main_aux.h"
#include "parser.h"

#include <stdlib.h>

int main(int argc, char* argv[]) {
	int ret;
	int fixed_cells;
	SudokuBoard game_board;
	
	if (user_input_setup(&fixed_cells) < 0) {
		return 0;
	}

	srand(argc > 1 ? atoi(argv[1]) : 5);

	create_game_board(&game_board, 3, 3, (size_t) fixed_cells);

	print_board(&game_board);
	
	while (True) {
		ret = get_and_run(&game_board);
		
		if (ret < 0) {
			return ret;
		}

		print_board(&game_board);
	}

	return 0;
}
