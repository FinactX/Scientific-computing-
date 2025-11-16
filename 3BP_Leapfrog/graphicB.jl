using CSV
using DataFrames
using Plots
using LaTeXStrings
gr()

# --- Carregar dados ---
dados = CSV.read("saida.dat", DataFrame, delim=' ', ignorerepeated=true)

x1, y1 = dados[:, 1], dados[:, 2]
x2, y2 = dados[:, 4], dados[:, 5]
x3, y3 = dados[:, 7], dados[:, 8]

# --- Massas dos corpos ---
m1, m2, m3 = 1/3, 1/3, 1/3  # ajuste aqui conforme necessário
M = m1 + m2 + m3

# --- Centro de massa (baricêntrico) ---
x_cm = (m1 .* x1 .+ m2 .* x2 .+ m3 .* x3) ./ M
y_cm = (m1 .* y1 .+ m2 .* y2 .+ m3 .* y3) ./ M

# --- Referencial baricêntrico ---
x1b, y1b = x1 .- x_cm, y1 .- y_cm
x2b, y2b = x2 .- x_cm, y2 .- y_cm
x3b, y3b = x3 .- x_cm, y3 .- y_cm

# --- Referencial heliocêntrico (corpo 1 fixo) ---
x1h, y1h = x1 .- x1, y1 .- y1  # = 0
x2h, y2h = x2 .- x1, y2 .- y1
x3h, y3h = x3 .- x1, y3 .- y1

# --- Cores e estilo ---
cores = [:blue, :red, :green]
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

# --- Gráfico 1: Referencial inercial ---
plt_inercial = plot(x1, y1, c=:blues, label=L"Corpo\ 1", alpha=0.9,
    xlabel=L"x\ \mathrm{(Adim.)}", ylabel=L"y\ \mathrm{(Adim.)}",
        #title=L"\mathrm{Referencial\ inercial\ da\ solução\ } S_{10}^{(1/3)}\ \mathrm{em}\ 2T",
    titlefont=font(16, "Computer Modern"))
plot!(x2, y2, c=:reds, label=L"Corpo\ 2", alpha=0.9)
plot!(x3, y3, c=:greens, label=L"Corpo\ 3", alpha=0.9)

# Após os plot! do gráfico inercial
scatter!(plt_inercial, [x1[1]], [y1[1]], markershape=:circle, ms=6, c=cores[1], label="")
scatter!(plt_inercial, [x2[1]], [y2[1]], markershape=:circle, ms=6, c=cores[2], label="")
scatter!(plt_inercial, [x3[1]], [y3[1]], markershape=:circle, ms=6, c=cores[3], label="")


savefig(plt_inercial, "S_10_1-3_inercial.png")

# --- Gráfico 2: Referencial heliocêntrico (corpo 1 fixo) ---
plt_helio = plot(x2h, y2h, c=:reds, label=L"Corpo\ 2", alpha=0.9,
    xlabel=L"x\ \mathrm{(Adim.)}", ylabel=L"y\ \mathrm{(Adim.)}",
    #title=L"\mathrm{Referencial\ helioc\^entrico\ da\ solução\ } S_{10}^{(1/3)}",
    titlefont=font(16, "Computer Modern"))
plot!(x3h, y3h, c=:greens, label=L"Corpo\ 3", alpha=0.9)

scatter!(plt_helio, [x1h[1]], [y1h[1]], markershape=:circle, ms=6, c=cores[1], label="")
scatter!(plt_helio, [x2h[1]], [y2h[1]], markershape=:circle, ms=6, c=cores[2], label="")
scatter!(plt_helio, [x3h[1]], [y3h[1]], markershape=:circle, ms=6, c=cores[3], label="")

savefig(plt_helio, "S_10_1-3_heliocentrico.png")

# --- Gráfico 3: Referencial baricêntrico ---
plt_bari = plot(x1b, y1b, c=:blues, label=L"Corpo\ 1", alpha=0.9,
    xlabel=L"x\ \mathrm{(Adim.)}", ylabel=L"y\ \mathrm{(Adim.)}",
    #title=L"\mathrm{Referencial\ baric\^entrico\ da\ solução\ } S_{10}^{(1/3)}",
    titlefont=font(16, "Computer Modern"))
plot!(x2b, y2b, c=:reds, label=L"Corpo\ 2", alpha=0.9)
plot!(x3b, y3b, c=:greens, label=L"Corpo\ 3", alpha=0.9)

scatter!(plt_bari, [x1b[1]], [y1b[1]], markershape=:circle, ms=6, c=cores[1], label="")
scatter!(plt_bari, [x2b[1]], [y2b[1]], markershape=:circle, ms=6, c=cores[2], label="")
scatter!(plt_bari, [x3b[1]], [y3b[1]], markershape=:circle, ms=6, c=cores[3], label="")

savefig(plt_bari, "S_10_1-3_baricentrico.png")

println("Todos os gráficos foram salvos com sucesso.")

