
#include "game.h"
#include "main_aux.h"

int main(void) {
	int ret;
	int fixed_cells;
	int oooo;
	SudokuBoard game_board;

	if (user_input_setup(&fixed_cells) < 0) {
		return 0;
	}

	create_game_board(&game_board, 3, 3, fixed_cells);

	print_board(&game_board);
	
	/*while (True) {
		ret = do_turn(user_turn());
		
		if (ret) {
			return ret;
		}
	}*/

	return 0;
}
