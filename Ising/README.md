# Modelo de Ising 2D - Algorítmo de Metrópolis

## SUMÁRIO

1. INTRODUÇÃO
2. ESTRUTURA DOS ARQUIVOS
3. INSTRUÇÕES PARA EXECUTAR
4. REFERÊNCIAS 

## 📘 INTRODUÇÃO

O **Modelo de Ising** é um dos sistemas mais estudados na física estatística, servindo como base para compreender fenômenos de magnetismo, transições de fase e comportamento crítico.
 Neste projeto implementamos o Modelo de Ising 2D clássico, definido por spins $s_{i,j}= \pm1$. A energia do sistema é  dada por
 
$$
	H = -J \sum_{\langle i,j\rangle} s_i s_j
$$

onde a soma é feita sob pares de primeiros vizinhos.

---

## 📂 ESTRUTURA DOS ARQUIVOS

- **ising.c**

Implementação completa da simulação: inicialização, atualização de spins pelo método de Metropolis, cálculo das médias termodinâmicas e escrita da saída no arquivo saida.dat.

- **Makefile**
Automatiza:	
	- Compilação;
	- Execução da simulação;
	- Geração de gráficos via Gnuplot;
	- Limpeza dos arquivos gerados.

- **graphic.gp**
Script Gnuplot que gera gráficos individuais das quantidades físicas.

- **graphicc.gp**
Script Gnuplot que produz um multiplot 2×2 com energia, magnetização, calor específico e suscetibilidade.

---

## 🛠️ INSTRUÇÕES PARA EXECUTAR

Garanta que o compilador GCC esteja instalado em sua máquina, além disso, voceê também deve ter o gnuplot, para vizualizar as saídas de dados.

Para compilar, executar e gerar os gráficos:
`make`

Para excluir os arquivos gerados:
`make clean`

Não é necessário fornecer entrada pelo terminal — os parâmetros principais (tamanho da malha, temperaturas, passos de Monte Carlo) podem ser alterados diretamente no início do arquivo **ising.c**.

---

## 🔗 REFERÊNCIAS
