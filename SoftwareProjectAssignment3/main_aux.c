
#include <stdio.h>

#define MAX_SIZE (80)

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
