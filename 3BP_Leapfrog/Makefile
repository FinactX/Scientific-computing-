CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -lm

all: compile run_simulation plot_graph

compile: verlet.o
		$(CC) $(CFLAGS) -o planet_simulation verlet.o -lm

main.o: verlet.c
		$(CC) $(CFLAGS) -c verlet.c

run_simulation: compile
		./planet_simulation

plot_graph: run_simulation
		gnuplot graphic.gp Energia_x_Tempo.gp

clean:
		rm -f planet_simulation verlet.o saida.dat Energy_Momentum.dat graphic.png Energy_x_Time.png
