# Configurações do gráfico
set terminal pngcairo enhanced font 'Verdana,12'
set output 'erro_vs_tamanho_passo.png'
set title 'Erro em função do Tamanho do Passo (Escala Logarítmica)'
set xlabel 'h'
set ylabel 'E(h)'
set logscale xy

# Plot dos dados
plot 'log_erro.dat' using 1:2 title 'L2' with linespoints lw 2 lc rgb 'blue', \
     'pontos.dat' using 1:($2/2) title 'Analítica' with linespoints lw 2 lc rgb 'red'
