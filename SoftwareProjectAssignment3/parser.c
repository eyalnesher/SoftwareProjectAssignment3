
#include "parser.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Split a string into an array of `max_args` strings, using `delimiter` as a delimiter,
 * and pass it to the caller through `parsed_string`.
 * Return the number of the generated strings.
 */
static int parse_delimeter(char* str, char* delimiter, char** parsed_string, int max_args) {
	char* token;
	int count = 0;

	token = strtok(str, delimiter);

	while (token && count < max_args) {
		parsed_string[count++] = token;
		token = strtok(NULL, delimiter);
	}

	return count;
}

/**
 * Gets input from stdin, parses the input using parse_delimeter and calculates the function's name and arguments
 */
static int get_argumets(char** function_name, int* function_args, int* function_args_size) {
	char line[MAX_CHAR_CNT];
	char* parsed_func[MAX_ARG_CNT];
	int arg_cnt;
	int i;

	if (fgets(line, MAX_CHAR_CNT, stdin) == NULL) {
		return -1; /* EOF encountered */
	}
	line[strcspn(line, "\n")] = 0;

	arg_cnt = parse_delimeter(line, " \t\r\n", parsed_func, MAX_ARG_CNT + 1);
	

	if (arg_cnt == 0) {
		return -1; /* line is empty? */
	}

	*function_args_size = arg_cnt - 1;
	*function_name = parsed_func[0];
	for (i = 1; i < arg_cnt; i++) {
		function_args[i - 1] = strtol(parsed_func[i], (char**)NULL, 10);
	}

	return 0;
}

/**
 * Gets a Sudoku board, receives input from stdin and runs the command it was given
 */
int get_and_run(SudokuBoard* board, bool* continue_executing) {
	char* func_name;
	int func_args[MAX_ARG_CNT];
	int arg_count;
	
	get_argumets(&func_name, func_args, &arg_count);

	return run_command(board, func_name, func_args, arg_count, continue_executing);
}

/**
 * Test the equality of the function name and function argument count to the tested_name and tested_args_count
 */
static int test_args(char* func_name, int args_count, char* tested_name, int tested_args_count) {
	return func_name != NULL && tested_name != NULL && strcmp(func_name, tested_name) == 0 && args_count >= tested_args_count;
}


/* TODO - RETURN VALUE */
int run_command(SudokuBoard* board, char* func_name, int* func_args, int args_count, bool* continue_executing) {
	int hint;
	int row, column;
	int ret;

	*continue_executing = True;

	if (!is_solved(board)) {
		/* Syntax: set X Y Z; meaning: set column X row Y cell value to Z */
		if (test_args(func_name, args_count, "set", 3)) {
			ret = legal_set_cell_value(board, func_args[1] - 1, func_args[0] - 1, func_args[2]);
			
			if (is_solved(board)) {
				printf("Puzzle solved successfully\n");
			}

			return ret;
		}

		/* Syntax: hint X Y; meaning: get a hint on column X row Y cell */
		if (test_args(func_name, args_count, "hint", 2)) {
			hint = get_cell_hint(board, func_args[1] - 1, func_args[0] - 1);
			printf("Hint: set cell to %d\n", (int)hint);
			return 0;
		}

		/* Syntax: validate; meaning: checks to see whether the current board state is solveable */
		if (test_args(func_name, args_count, "validate", 0)) {
			if (validate_board(board)) {
				printf("Validation passed: board is solvable\n");
			}
			else {
				printf("Validation failed: board is unsolvable\n");
			}
			return 0;
		}
	}

	/* Syntax: restart; meaning: restart the game, creating a new puzzle */
	if (test_args(func_name, args_count, "restart", 0)) {
		restart_game(board);
		return 0;
	}

	/* Syntax: exit; meaning: exit the game, freeing all memory resources */
	if (test_args(func_name, args_count, "exit", 0)) {
		free_game_board(board);
		*continue_executing = False;
		return -1;
	}

	printf("Error: invalid command\n");
	return -1;
}
