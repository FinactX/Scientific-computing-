using CSV
using DataFrames
using Plots
using LaTeXStrings
gr()

# Carregar dados
dados = CSV.read("Energy_Momentum.dat", DataFrame, delim=' ', ignorerepeated=true)

# Extrair colunas: tempo e energia
tempo = dados[:, 1]
energia = dados[:, 2]

# Configuração global de estilo
default(
    background_color = :white,
    legend = :topright,
    grid = :on,
    guidefont = font("Computer Modern", 12),
    legendfont = font("Computer Modern", 10),
    tickfont = font("Computer Modern", 10),
    lw = 2,
    size = (800, 800),
    dpi = 150,
)

# Plotar energia vs tempo
plt = plot(tempo, energia,
    c=:blue,
    label=L"Energia\ Total",
    xlabel=L"Tempo\ (Adim.)",
    ylabel=L"Energia\ (Adim.)",
    title="Evolução da Energia Total",
    titlefont=font(16, "Computer Modern"),
    alpha=0.9
)

# Salvar gráfico
savefig(plt, "Energia_vs_Tempo.png")
println("Gráfico salvo como 'Energia_vs_Tempo.png'")

