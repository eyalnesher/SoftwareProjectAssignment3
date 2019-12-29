
#include "main_aux.h"
#include <stdio.h>

#define MAX_SIZE (80)
#define SEPERATOR_ROW ("----------------------------------\n")

int user_input_setup(int* fixed_cells) {
	int ret;

	printf("Please enter the number of cells to fill[0 - %d]:\n", MAX_SIZE);
	while ((ret = scanf("%d", fixed_cells)) != 1 || *fixed_cells < 0 || *fixed_cells > MAX_SIZE) { /* Error - not in format */
		if (ret <= 0) {
			if (ret != EOF){
				printf("Error: not a number\n");
			}
			printf("Exiting...\n");
			return -1;
		}
		printf("Error: invalid number of cells to fill(should be between 0 and %d)\n", MAX_SIZE);
	}

	return 0;
}

void print_board(SudokuBoard* board) {
	size_t block_row, block_col, row, col;

	printf(SEPERATOR_ROW);
	for (block_row = 0; block_row < board->block_width; block_row++) {
		/* prints a full batch of row blocks */
		for (row = 0; row < board->block_height; row++) {
			/* prints a full row */
			printf("|");
			for (block_col = 0; block_col < board->block_height; block_col++) {
				/* prints a row in the block (block_row, block_col) */
				for (col = 0; col < board->block_width; col++) {
					/* prints cell (row, col) of block (block_row, block_col) */
					printf("%s", cell_string_repr(board, block_row * board->block_height + row, block_col * board->block_width + col));
				}
				printf("|");
			}
			printf("\n");
		}
		printf(SEPERATOR_ROW);
	}
}

static int cell_string_repr(SudokuBoard* board, size_t row, size_t column, char** cell_repr) {
	int cell_val;
	bool is_fixed;

	if (get_cell_value(board, row, column, &cell_val)) {
		return -1;
	}
	if (is_cell_fixed(board, row, column, &is_fixed)) {
		return -1;
	}

	if (is_fixed) {
		*cell_repr = ".0";
	}
	else {
		*cell_repr = " 0";
	}

	return 0;
}