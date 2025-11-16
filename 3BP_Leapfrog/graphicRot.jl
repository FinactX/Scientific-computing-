using CSV
using DataFrames
using Plots
using LaTeXStrings
gr()

# Parâmetros da rotação
ω = 1.0          # Frequência angular (normalizada)
Δt = 0.001       # Defina seu Δt aqui de acordo com a simulação
N = 0            # será atualizado abaixo

# Carregar dados
dados = CSV.read("saida.dat", DataFrame, delim=' ', ignorerepeated=true)

# Extrair colunas
x1, y1 = dados[:, 1], dados[:, 2]
x2, y2 = dados[:, 4], dados[:, 5]
x3, y3 = dados[:, 7], dados[:, 8]

N = length(x3)  # número de passos

# Aplicar rotação no tempo em cada ponto
x3_rot = similar(x3)
y3_rot = similar(y3)

for i in 1:N
    θ = ω * (i - 1) * Δt
    cosθ, sinθ = cos(θ), sin(θ)
    x3_rot[i] =  cosθ * x3[i] + sinθ * y3[i]
    y3_rot[i] = -sinθ * x3[i] + cosθ * y3[i]
end

# Início e fim
p_start = [(x1[1], y1[1]), (x2[1], y2[1]), (x3_rot[1], y3_rot[1])]
p_end   = [(x1[end], y1[end]), (x2[end], y2[end]), (x3_rot[end], y3_rot[end])]

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
    title = L"\mathrm{Trajetória\ no\ referencial\ rotativo}",
    titlefont=font(16, "Computer Modern"))

plot!(x2, y2, c=:reds, label=L"Corpo\ 2", alpha=0.9)
plot!(x3_rot, y3_rot, c=:greens, label=L"Corpo\ 3\ (rotativo)", alpha=0.9)

# Marcar início com círculos coloridos
scatter!([x1[1]], [y1[1]], markershape=:circle, ms=6, c=cores[1], label="")
scatter!([x2[1]], [y2[1]], markershape=:circle, ms=6, c=cores[2], label="")
scatter!([x3_rot[1]], [y3_rot[1]], markershape=:circle, ms=6, c=cores[3], label="")

# Salvar
savefig(plt, "trajetoria_rotativo.png")
println("Gráfico no referencial rotativo salvo com sucesso.")

