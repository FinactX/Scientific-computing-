CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lm

EXECUTABLE = programa
GNUPLOT_SCRIPT = graphic.gp

all: $(EXECUTABLE) plot

$(EXECUTABLE): main.c
	$(CC) $(CFLAGS) main.c -o $(EXECUTABLE) $(LDFLAGS)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

plot: run
	gnuplot $(GNUPLOT_SCRIPT)

clean:
	rm -f $(EXECUTABLE) saida.dat solucao_analitica.dat solucao_analitica.png solucao_numerica.png

