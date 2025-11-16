using CSV
using DataFrames
using Plots
using LaTeXStrings
gr()

default(
    fontfamily = "sans-serif",
    background_color = :white,
    legend = :topright,
    grid = :on,
    guidefont = font(12),
    legendfont = font(10),
    tickfont = font(10),
    lw = 2,
    size = (800, 600),
    dpi = 150
)

# Leitura robusta
dados = CSV.read("saida.dat", DataFrame; delim=' ', ignorerepeated=true)
dados = dropmissing(dados)  # Caso tenha linhas corrompidas

# Extrair tempo e coordenadas x
t  = dados[:, 10]
x1 = dados[:, 1]
x2 = dados[:, 4]
x3 = dados[:, 7]

# Diagnóstico
println("x1 range: ", extrema(x1))
println("x2 range: ", extrema(x2))
println("x3 range: ", extrema(x3))

# Cores
cores = [:blue, :red, :green]

# Plot
plt = plot(t, x1, c=cores[1], label=L"x_1(t)", alpha=0.9,
    xlabel=L"t\ \mathrm{(Adim.)}", ylabel=L"x\ \mathrm{(Adim.)}",
    title = L"\mathrm{Comportamento\ das\ coordenadas\ x_i(t)}",
    titlefont=font(16))

plot!(t, x2, c=cores[2], label=L"x_2(t)", alpha=0.9)
plot!(t, x3, c=cores[3], label=L"x_3(t)", alpha=0.9)

# Salvar
savefig(plt, "x(t)_triangulo_equilatero.png")
println("Gráfico x(t) salvo com sucesso.")

