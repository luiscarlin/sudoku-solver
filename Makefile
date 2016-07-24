all: run
run: build
	./sudoku-solver -p
build:
	gcc -std=c11 -Wall sudoku-solver.c -o sudoku-solver
clean:
	rm -f sudoku-solver

test: build
	./run-tests.sh tests.txt 
