CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -lm
EXECUTABLE = programa
GNUPLOT_SCRIPT = graphic.gp

all: $(EXECUTABLE) plot

$(EXECUTABLE): main.c
	$(CC) $(CFLAGS) -o $(EXECUTABLE) main.c

run: $(EXECUTABLE)
	./$(EXECUTABLE)

plot: run
	gnuplot $(GNUPLOT_SCRIPT)

clean:
	rm -f $(EXECUTABLE) graphic.png
