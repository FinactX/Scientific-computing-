set terminal pngcairo size 900,700 enhanced font "Arial,12"
set output 'graficos_ising.png'

# Configurações gerais
set grid
set key left top
set xlabel "Temperatura (T)" font "Arial,12"
set xtics font "Arial,10"
set ytics font "Arial,10"

# Margens
set multiplot layout 2,2 margins 0.1,0.9,0.1,0.9 spacing 0.1

# 1. Energia média por spin
set ylabel "<E>/N" font "Arial,12"
plot 'saida.dat' using 1:2 with linespoints lw 2 pt 7 ps 0.8 lc rgb "blue" title "<E>/N"

# 2. Magnetização média por spin
set ylabel "<|M|>/N" font "Arial,12"
plot 'saida.dat' using 1:3 with linespoints lw 2 pt 5 ps 0.8 lc rgb "red" title "<|M|>/N"

# 3. Calor específico (C_v)
set ylabel "C_v" font "Arial,12"
plot 'saida.dat' using 1:4 with linespoints lw 2 pt 9 ps 0.8 lc rgb "green" title "C_v"

# 4. Suscetibilidade magnética (χ)
set ylabel "χ" font "Arial,12"
plot 'saida.dat' using 1:5 with linespoints lw 2 pt 13 ps 0.8 lc rgb "purple" title "χ"

unset multiplot
