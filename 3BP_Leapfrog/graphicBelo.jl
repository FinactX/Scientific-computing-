using CSV
using DataFrames
using Plots
using LaTeXStrings
gr()

# Carregar dados
dados = CSV.read("saida.dat", DataFrame, delim=' ', ignorerepeated=true)

# Extrair colunas
x1, y1 = dados[:, 1], dados[:, 2]
x2, y2 = dados[:, 4], dados[:, 5]
x3, y3 = dados[:, 7], dados[:, 8]

# Início e fim
p_start = [(x1[1], y1[1]), (x2[1], y2[1]), (x3[1], y3[1])]
p_end   = [(x1[end], y1[end]), (x2[end], y2[end]), (x3[end], y3[end])]

# Cores
cores = [:blue, :red, :green]

# Configuração global
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
    aspect_ratio = :equal
)

# Plot com estilo científico
plt = plot(x1, y1, c=:blues, label=L"Corpo\ 1 ", alpha=0.9,
    xlabel=L"x\ \mathrm{(Adim.)}", ylabel=L"y\ \mathrm{(Adim.)}",
    title = L"\mathrm{Trajetórias\ \mathrm{triângulo\ equilátero}}",
    #title="Trajetórias de S",
    titlefont=font(16, "Computer Modern"))

plot!(x2, y2, c=:reds, label=L"Corpo\ 2", alpha=0.9)
plot!(x3, y3, c=:greens, label=L"Corpo\ 3", alpha=0.9)

# Marcar início com círculos coloridos
scatter!([x1[1]], [y1[1]], markershape=:circle, ms=6, c=cores[1], label="")
scatter!([x2[1]], [y2[1]], markershape=:circle, ms=6, c=cores[2], label="")
scatter!([x3[1]], [y3[1]], markershape=:circle, ms=6, c=cores[3], label="")

# Salvar
savefig(plt, "Trajetórias.png")
println("Gráfico salvo com sucesso.")
