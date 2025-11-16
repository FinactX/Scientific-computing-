using CSV
using DataFrames
using Plots
using LaTeXStrings
gr()

# Carregar dados
dados = CSV.read("saida.dat", DataFrame, delim=' ', ignorerepeated=true)

# Posições absolutas
x1, y1 = dados[:, 1], dados[:, 2]
x2, y2 = dados[:, 4], dados[:, 5]
x3, y3 = dados[:, 7], dados[:, 8]

# Massas iguais
m = 1.0/3.0

# Coordenadas do CM
x_cm = m .* (x1 + x2 + x3)
y_cm = m .* (y1 + y2 + y3)

# Subtrair o CM de cada posição
x1_rel = x1 .- x_cm
y1_rel = y1 .- y_cm
x2_rel = x2 .- x_cm
y2_rel = y2 .- y_cm
x3_rel = x3 .- x_cm
y3_rel = y3 .- y_cm

# se os dados contiverem muitos pontos
step = 100
x1_sub, y1_sub = x1_rel[1:step:end], y1_rel[1:step:end]
x2_sub, y2_sub = x2_rel[1:step:end], y2_rel[1:step:end]
x3_sub, y3_sub = x3_rel[1:step:end], y3_rel[1:step:end]

# Cores
cores = [:blue, :red, :green]

# Configuração
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

# Efeito de rastro
trail_length = 100

# Animação
anim = @animate for i in 1:length(x1_sub)
    plt = plot(
        #xlabel=L"x\ \mathrm{(CM)}", ylabel=L"y\ \mathrm{(CM)}",
        title = "", legend=false,
        xlims=(minimum([x1_sub; x2_sub; x3_sub]) - 0.1, maximum([x1_sub; x2_sub; x3_sub]) + 0.1),
        ylims=(minimum([y1_sub; y2_sub; y3_sub]) - 0.1, maximum([y1_sub; y2_sub; y3_sub]) + 0.1)
    )

    for (x, y, color) in zip((x1_sub, x2_sub, x3_sub), (y1_sub, y2_sub, y3_sub), cores)
            for j in 1:i
            plot!(plt, [x[j]], [y[j]], seriestype=:scatter, c=color, alpha=0.5, ms=2, label="")
        end

        #trail_start = max(1, i - trail_length + 1)
        #trail_indices = trail_start:i
        #trail_size = length(trail_indices)

        #for (j, idx) in enumerate(trail_indices)
         #   α = j / trail_size
          #  plot!(plt, [x[idx]], [y[idx]], seriestype=:scatter, c=color, alpha=α, ms=2, label="")
        #end

        # Marcar a posição atual
        scatter!([x[i]], [y[i]], markershape=:circle, ms=10, c=color, label="")
    end
end

# Salvar gif
gif(anim, "trajetorias_cm.gif", fps=30)
println("GIF gerado no referencial do centro de massa.")

