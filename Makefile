all: run
run: build
	./sudoku-solver
build:
	gcc -std=c11 -Wall sudoku-solver.c -o sudoku-solver
clean:
	rm -f sudoku-solver
