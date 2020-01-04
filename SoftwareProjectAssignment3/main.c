
#include "game.h"
#include "main_aux.h"

#include <stdlib.h>

int main(int argc, char* argv[]) {
	int ret;
	int fixed_cells;
	SudokuBoard game_board;

	if (user_input_setup(&fixed_cells) < 0) {
		return 0;
	}

	srand(argc > 1 ? atoi(argv[1]) : 5);

	create_game_board(&game_board, 3, 3, fixed_cells);
	generate_board(&game_board, (size_t) fixed_cells);

	print_board(&game_board);
	
	/*while (True) {
		ret = do_turn(user_turn());
		
		if (ret) {
			return ret;
		}
	}*/

	return 0;
}
