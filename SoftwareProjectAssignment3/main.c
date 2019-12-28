
#include "game.h"
#include "main_aux.h"

int main(void) {
	int ret;
	int fixed_cells;
	SudokuBoard game_board;

	if (user_input_setup(&fixed_cells) < 0) {
		return 0;
	}
	
	while (True) {
		/*ret = do_turn(user_turn());
		
		if (ret) {
			return ret;
		}*/
	}

	return 0;
}
