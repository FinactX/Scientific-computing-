do for [temp in "1.0 1.5 2.0 2.5 3.0 4.0 5.0 10.0"] {
    set terminal pngcairo size 600,600 enhanced font 'Computer Modern,12'
    set output sprintf("config_T%s.png", temp)
    unset key; unset xtics; unset ytics
    set size ratio -1
    set palette defined (-1 "black", 1 "white")
    set cbrange [-1:1]
    set title sprintf("Configuração de spins (T = %s)", temp)
    plot sprintf("config_T%s.dat", temp) matrix with image
}

