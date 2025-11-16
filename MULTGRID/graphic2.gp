# Criar a pasta para os plots
system("mkdir -p plots")

# Define o formato de saída
set terminal pngcairo size 800,600 enhanced font 'Verdana,12'

# Define o nome do arquivo de saída da imagem para a solução numérica
set output 'plots/solucao_numerica2.png'

# Define os rótulos dos eixos x, y e z para a solução numérica
set xlabel 'x'
set ylabel 'y'
set zlabel 'f(x, y)'

# Define o intervalo dos eixos x e y
#set xrange [-2:2]
#set yrange [-2:2]
#set zrange [-1:1]

# Define o título do gráfico para a solução numérica
set title 'Solução Numérica da Equação de Poisson 2D'

# Plota os dados do arquivo "saida.dat" (solução numérica)
set pm3d at s
set palette rgbformulae 33 ,13 ,10

# set output 'plots/rhs_0.png'
# set title "rhs_0"
# splot 'data_output/rhs_0.dat' using 1:2:3 with pm3d notitle

#set output 'plots/rhs_1.png'
#set title "rhs_1"
#splot 'data_output/rhs_1.dat' using 1:2:3 with pm3d notitle

set output 'plots/solucao_analitica.png'
set title "solucao_analitica"
splot 'data_output/solucao_analitica.dat' using 1:2:3 with pm3d notitle

set output 'plots/solution_level_0.png'
set title "Solution at Level 0"
splot 'data_output/solution_level_0.dat' using 1:2:3 with pm3d notitle

set output 'plots/solution_level_1.png'
set title "Solution at Level 1"
splot 'data_output/solution_level_1.dat' using 1:2:3 with pm3d notitle

set output 'plots/solution_level_2.png'
set title "Solution at Level 2"
splot 'data_output/solution_level_2.dat' using 1:2:3 with pm3d notitle

set output 'plots/solution_level_3.png'
set title "Solution at Level 3"
splot 'data_output/solution_level_3.dat' using 1:2:3 with pm3d notitle

set output 'plots/solution_level_4.png'
set title "Solution at Level 4"
splot 'data_output/solution_level_4.dat' using 1:2:3 with pm3d notitle

set output 'plots/solution_level_5.png'
set title "Solution at Level 5"
splot 'data_output/solution_level_5.dat' using 1:2:3 with pm3d notitle

set output 'plots/solution_level_6.png'
set title "Solution at Level 6"
splot 'data_output/solution_level_6.dat' using 1:2:3 with pm3d notitle

set output 'plots/solution_level_7.png'
set title "Solution at Level 7"
splot 'data_output/solution_level_7.dat' using 1:2:3 with pm3d notitle

set output 'plots/solution_level_8.png'
set title "Solution at Level 8"
splot 'data_output/solution_level_8.dat' using 1:2:3 with pm3d notitle

set output 'plots/solution_level_8.png'
set title "Solution at Level 8"
splot 'data_output/solution_level_8.dat' using 1:2:3 with pm3d notitle

set output 'plots/solution_level_9.png'
set title "Solution at Level 9"
splot 'data_output/solution_level_9.dat' using 1:2:3 with pm3d notitle

# set output 'plots/solution_level_10.png'
# set title "Solution at Level 10"
# splot 'data_output/solution_level_10.dat' using 1:2:3 with pm3d notitle

# set output 'plots/solution_level_11.png'
# set title "Solution at Level 11"
# splot 'data_output/solution_level_11.dat' using 1:2:3 with pm3d notitle


#------------------------------------------------
