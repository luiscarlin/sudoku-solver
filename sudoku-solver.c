#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

struct GlobalArgs {
    int verbosity;    // -v 
    char *input;      // -i
    int pretty;       // -p
    int help;         // -h
} globalArgs;

static const char *optString = "i:pvh";

void print_grid(int array[][9], int pretty);
int solve(int grid[][9], int x, int y); 
int is_valid_candidate(int grid[][9], int x, int y, int possible_value);
void print_usage();
void parse_args(int argc, char **argv);
int populate_grid(int grid[][9]);

int main(int argc, char **argv) {
    int grid[9][9];

    parse_args(argc, argv);
    
    if (globalArgs.help) {
        print_usage();
        return EXIT_SUCCESS;
    }
 
    if (!populate_grid(grid)) { 
        printf("Could not populate the grid.\n");
        printf("Check your values\n");
        
        return EXIT_FAILURE;
    }
 
    if (globalArgs.pretty || globalArgs.verbosity) {
        printf("Original:\n");
        print_grid(grid, 1);
    }

    int found_solution = solve(grid, 0, 0);
   
    if (found_solution) {
        if (globalArgs.verbosity || globalArgs.pretty) {
            printf("Solution:\n");
            print_grid(grid, 1);   
        }
        else {
            print_grid(grid, 0);
        }
    }
    else {
        printf("No solution found!\n");   
    }
    
    return found_solution ? EXIT_SUCCESS : EXIT_FAILURE;
}

int populate_grid(int grid[][9]) {    
    char input[81];

    if (globalArgs.input == NULL) { 
        printf("Enter the sudoku numbers by using '0' for empty squares:\n");
        scanf("%s", input); 
    }
    else {
        if (strlen(globalArgs.input) != 81) { 
            return 0;
        }
        strcpy(input, globalArgs.input);
    }

    if (strlen(input) != 81) {
        return 0;
    }
    
    int input_index = 0;

    for (int x = 0; x < 9; x++) { 
        for (int y = 0; y < 9; y++) { 
            grid[x][y] = input[input_index] - '0';
            input_index++;
        }
    }

    return 1;
}

void parse_args(int argc, char **argv) {
    int opt = 0;

    globalArgs.verbosity = 0;
    globalArgs.input = NULL;
    globalArgs.pretty = 0;

    opt = getopt(argc, argv, optString);
    while (opt != -1) { 
        switch (opt) {
            case 'v':
                globalArgs.verbosity = 1;
                break;

            case 'i':
                globalArgs.input = optarg;
                break;

            case 'p':
                globalArgs.pretty = 1;
                break;

            case 'h':
                globalArgs.help = 1;
                break;

            default:
                break;
        }
        opt = getopt(argc, argv, optString);
    }
}

void print_grid(int array[][9], int pretty) {
    if (pretty) { 
        printf("-------------------------------\n");
 
        for (int x = 0; x < 9; x++) {
            printf("|");

            for (int y = 0; y < 9; y++) { 
                printf(" %d ", array[x][y]);
                if ((y + 1) % 3 == 0) { 
                    printf("|");
                }
            }

            printf("\n");
            if ((x + 1) % 3 == 0) {
                printf("-------------------------------\n");
            }
        }
    }
    else {
        for (int x = 0; x < 9; x++) { 
            for (int y = 0; y < 9; y++) { 
                printf("%d", array[x][y]);
            }
        }
        printf("\n");
    }
}

void print_usage() {
    printf("NAME\n");
    printf("    sudoku-solver - solves a sudoku based on input grid\n");
    printf("\n"); 
    printf("SYNOPSIS\n");
    printf("    sudoku_solver [-i start_grid] [-pvh]\n");
    printf("\n");
    printf("DESCRIPTION\n");
    printf("    -i    start_grid\n");
    printf("              Enter the numbers corresponding to the initial state of the sudoku\n");
    printf("              all in one line. Enter '0' for empty squares.\n");
    printf("    -p    pretty print\n");
    printf("    -v    verbose\n");
    printf("    -h    this help\n");
}

int solve(int grid[][9], int x, int y) {
    if (globalArgs.verbosity) { 
        printf("Current position [%d][%d]\n", x, y);
    }

    if (x == 9) { 
        return 1;
    }
    
    int next_x = 0;
    int next_y = 0;
    
    if (y == 8) {
        next_x = x + 1;
        next_y = 0;
    }
    else {
        next_x = x;
        next_y = y + 1;
    }

    if (globalArgs.verbosity) {
        printf("next step [%d][%d]\n", next_x, next_y);
    }

    if (grid[x][y] == 0) {
        int possible_value = 1;
 
        while (1) { 
            if (possible_value > 9) {
                return 0;
            }
            if (is_valid_candidate(grid, x, y, possible_value)) {
                grid[x][y] = possible_value;
                
                if (globalArgs.verbosity) {
                    print_grid(grid, 1);
                }

                if (solve(grid, next_x, next_y)) { 
                    return 1;
                }
                grid[x][y] = 0;
            }
            possible_value++;
        }
    }
    else {
        return(solve(grid, next_x, next_y)); 
    }  
}

int is_valid_candidate(int grid[][9], int x, int y, int possible_value) {
    if (globalArgs.verbosity) {
        printf("Testing row=%d col=%d possible_value=%d\n", x, y, possible_value);
    }

    // check row
    for (int i = 0; i < 9; i++) { 
        if (grid[x][i] == possible_value) {
            if (globalArgs.verbosity) {
                printf("found %d in row %d\n", possible_value, x);
            } 
            return 0;
        }
    }
    
    // check column
    for (int i = 0; i < 9; i++) { 
        if (grid[i][y] == possible_value) {
            if (globalArgs.verbosity) { 
                printf("found %d in col %d\n", possible_value, y); 
            }
            return 0;
        }
    }
    
    // check group
    int x_min = (int)(x / 3) * 3;
    int y_min = (int)(y / 3) * 3;
    int x_max = x_min + 2;
    int y_max = y_min + 2;

    for (int xn = x_min; xn <= x_max; xn++) {
        for(int yn = y_min; yn <= y_max; yn++) {
            if (grid[xn][yn] == possible_value) {
                if (globalArgs.verbosity) {
                    printf("found %d in group\n", possible_value);
                }
                return 0;
            }
        } 
    }   
    return 1;
}

