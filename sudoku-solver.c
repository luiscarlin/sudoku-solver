#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

void print_grid(int array[][9]);
int solve(int grid[][9], int x, int y); 
int is_valid_candidate(int grid[][9], int x, int y, int possible_value);

int main(int argc, char **argv) {
    int opt;
    int grid[9][9] = {{0, 0, 0, 2, 6, 0, 7, 0, 1}, 
                      {6, 8, 0, 0, 7, 0, 0, 9, 0},
                      {1, 9, 0, 0, 0 ,4 ,5 ,0 ,0},
                      {8, 2, 0, 1, 0, 0, 0, 4, 0},
                      {0, 0, 4, 6, 0, 2, 9, 0, 0},
                      {0, 5, 0, 0, 0, 3, 0, 2, 8},
                      {0, 0, 9, 3, 0, 0, 0, 7, 4},
                      {0, 4, 0, 0, 5, 0, 0, 3, 6},
                      {7, 0, 3, 0, 1, 8, 0, 0, 0}};
    
    print_grid(grid);
    
    int found_solution  = solve(grid, 0, 0);
   
    if (found_solution) { 
        print_grid(grid);
    }
    else {
        printf("No solution found!\n");   
    }
    
    return found_solution ? EXIT_SUCCESS : EXIT_FAILURE;
}

void print_grid(int array[][9]) {
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

int solve(int grid[][9], int x, int y) {

    printf("Current position [%d][%d]\n", x, y);
   
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
    printf("next step [%d][%d]\n", next_x, next_y);
 
    if (grid[x][y] == 0) {
        int possible_value = 1;
 
        while (1) { 
            if (possible_value > 9) {
                return 0;
            }
            if (is_valid_candidate(grid, x, y, possible_value)) {
                grid[x][y] = possible_value;
                
                print_grid(grid);
                
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
    printf("Testing row=%d col=%d possible_value=%d\n", x, y, possible_value);

    // check row
    for (int i = 0; i < 9; i++) { 
        if (grid[x][i] == possible_value) {
            printf("found %d in row %d\n", possible_value, x); 
            return 0;
        }
    }
    
    // check column
    for (int i = 0; i < 9; i++) { 
        if (grid[i][y] == possible_value) {
            printf("found %d in col %d\n", possible_value, y); 
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
                printf("found %d in group\n", possible_value);
                return 0;
            }
        } 
    }   
    return 1;
}

