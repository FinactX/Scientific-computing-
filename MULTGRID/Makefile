# Definições de variáveis
CXX = g++
CXXFLAGS = -Wall -O2
TARGET = main
INPUTS = 1024 1024 8 2 
GP_SCRIPT = graphic2.gp

# Alvo padrão
all: $(TARGET)

# Regra para compilar o código
$(TARGET): main.cpp functions.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp functions.cpp

# Regra para executar o programa com as entradas
run: $(TARGET)
	mkdir -p data_output
	./$(TARGET) $(INPUTS)

# Regra para executar o script do Gnuplot
gnuplot: run
	mkdir -p plots
	gnuplot $(GP_SCRIPT)

# Alvo para limpar arquivos gerados
clean:
	rm -f $(TARGET)
	rm -rf plots/* 
	rm -rf data_output/*
all: $(TARGET) run gnuplot

.PHONY: all run gnuplot clean
