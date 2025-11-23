# Define o formato de saída
set terminal pngcairo size 800,600 enhanced font 'Verdana,12'

# Define o nome do arquivo de saída da imagem para a solução numérica
set output 'solucao_numerica.png'

# Define os rótulos dos eixos x, y e z para a solução numérica
set xlabel 'x'
set ylabel 'y'
set zlabel 'Solução Numérica'

# Define o intervalo dos eixos x e y
set xrange [0:1]
set yrange [0:1]
set zrange [0:1]

# Define o título do gráfico para a solução numérica
set title 'Solução Numérica da Equação de Poisson 2D'

# Plota os dados do arquivo "saida.dat" (solução numérica)
splot 'saida.dat' using 1:2:3 with lines
#------------------------------------------------

# Define o formato de saída
set terminal pngcairo size 800,600 enhanced font 'Verdana,12'

# Define o nome do arquivo de saída da imagem para a solução analítica
set output 'solucao_analitica.png'

# Define os rótulos dos eixos x, y e z para a solução analítica
set xlabel 'ax'
set ylabel 'y'
set zlabel 'Solução Analítica'

# Define o intervalo dos eixos x e y
set xrange [0:1]
set yrange [0:1]
set zrange [0:1]

# Define o título do gráfico para a solução analítica
set title 'Solução Analítica da Equação de Poisson 2D'

# Plota os dados do arquivo "solucao_analitica.dat" (solução analítica)
splot 'solucao_analitica.dat' using 1:2:3 with lines
