CC = gcc
CFLAGS = -Wall -Wextra -pg -std=c99 -lm -O3 -ofast

all: compile run_simulation plot_graph

compile: ising.o
		$(CC) $(CFLAGS) -o ising_simulation ising.o -lm

main.o: ising.c
		$(CC) $(CFLAGS) -c ising.c

run_simulation: compile
		./ising_simulation

plot_graph: run_simulation
		gnuplot graphic.gp graphicc.gp 

clean:
		rm -f ising_simulation ising.o *.png *.dat
