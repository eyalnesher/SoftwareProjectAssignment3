
#ifndef MAIN_AUX_H
#define MAIN_AUX_H

#define True (1)
#define False (0)

typedef char bool;

/**
 * Get user inputs for game initialization - number of fixed cells.
 * set the value of `fixed_cells` to be the number of fixed cells.
 * Return 0 if succeded, -1 otherwise.
 */
int user_input_setup(int* fixed_cells);

#endif /* !MAIN_AUX_H */
