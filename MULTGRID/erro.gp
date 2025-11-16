# Configurações do gráfico
set terminal pngcairo enhanced font 'Verdana,12'
set output 'erro_vs_tamanho_passo.png'
set title 'Erro em função do Passo (Escala Logarítmica)'
set xlabel 'h'
set ylabel 'E(h)'
set logscale xy
set grid               # Adiciona uma grade para melhor visualização
set key top left      # Muda a legenda para o canto superior direito

# Personalização das linhas e pontos
set style line 3 lt 1 lw 2 lc rgb 'green' pt 9 ps 1.5   # Linha verde com pontos quadrados
set style line 1 lt 1 lw 2 lc rgb 'blue' pt 7 ps 1.5  # Linha azul com pontos grandes
set style line 2 lt 1 lw 2 lc rgb 'red' pt 5 ps 1.5   # Linha vermelha com pontos quadrados


# Plot dos dados
plot 'erroo.dat' using 1:2 title 'Dirichlet L2' with linespoints ls 1, \
     'ref_erro.dat' using 1:2 title 'Analytical' with linespoints ls 3
