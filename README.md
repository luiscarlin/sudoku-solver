# sudoku solver


Very simple Sudoku solver using backtracking recursion.

## How to run
    git clone https://github.com/luiscarlin/sudoku-solver 
    cd sudoku-solver
    make

### Sample run
    $ make
    gcc -std=c11 -Wall sudoku-solver.c -o sudoku-solver
    ./sudoku-solver -p
    Enter the sudoku numbers by using '0' for empty squares:
    000260701680070090190004500820100040004602900050003028009300074040050036703018000
    Original:
    -------------------------------
    | 0  0  0 | 2  6  0 | 7  0  1 |
    | 6  8  0 | 0  7  0 | 0  9  0 |
    | 1  9  0 | 0  0  4 | 5  0  0 |
    -------------------------------
    | 8  2  0 | 1  0  0 | 0  4  0 |
    | 0  0  4 | 6  0  2 | 9  0  0 |
    | 0  5  0 | 0  0  3 | 0  2  8 |
    -------------------------------
    | 0  0  9 | 3  0  0 | 0  7  4 |
    | 0  4  0 | 0  5  0 | 0  3  6 |
    | 7  0  3 | 0  1  8 | 0  0  0 |
    -------------------------------
    Solution:
    -------------------------------
    | 4  3  5 | 2  6  9 | 7  8  1 |
    | 6  8  2 | 5  7  1 | 4  9  3 |
    | 1  9  7 | 8  3  4 | 5  6  2 |
    -------------------------------
    | 8  2  6 | 1  9  5 | 3  4  7 |
    | 3  7  4 | 6  8  2 | 9  1  5 |
    | 9  5  1 | 7  4  3 | 6  2  8 |
    -------------------------------
    | 5  1  9 | 3  2  6 | 8  7  4 |
    | 2  4  8 | 9  5  7 | 1  3  6 |
    | 7  6  3 | 4  1  8 | 2  5  9 |
    -------------------------------

## man pages
    $ ./sudoku-solver -h
    NAME
        sudoku-solver - solves a sudoku based on input grid

    SYNOPSIS
        sudoku_solver [-i start_grid] [-pvh]

    DESCRIPTION
        -i    start_grid
                  Enter the numbers corresponding to the initial state of the sudoku
                  all in one line. Enter '0' for empty squares.
        -p    pretty print
        -v    verbose
        -h    this help
  
