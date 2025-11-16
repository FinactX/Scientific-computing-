set terminal pngcairo enhanced font 'Verdana,12'
set output 'three_body_simulation.png'

set title 'Three Body Simulation'
set xlabel 'X Position (m)'
set ylabel 'Y Position (m)'
set zlabel 'Z Position (m)'
set grid
plot 'saida.dat' using 1:2:3 with lines title 'Body 1', \
     'saida.dat' using 4:5:6 with lines title 'Body 2', \
     'saida.dat' using 7:8:9 with lines title 'Body 3'
