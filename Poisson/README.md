# Solver da Equação de Poisson 2D

## 📑 SUMÁRIO

 1. INTRODUÇÃO
 2. INSTRUÇÕES PARA EXECUTAR
 3. ARQUIVOS PRESENTES NO PROJETO
 4. REFERÊNCIAS


# INTRODUÇÃO

A equação de Poisson é um exemplo de EDP (Equação Diferencial Parcial) elíptica bastante conhecida na física e modela alguns problemas importantes, como campos eletrostáticos, gravitação newtoniana e problemas de difusão em estado estacionário. Suas condições de contorno levam a soluções tipicamente suaves. Este código resolve numericamente a equação dada por

$
\begin{cases}
-\Delta u = f, & \text{em } \Omega,\\
u = g, & \text{em } \partial\Omega.
\end{cases}
$

A discretização é feita por diferenças finitas de segunda ordem e o sistema linear que obtemos é resolvido iterativamente via Gauss-Seidel.
---

## 📂 Estrutura dos Arquivos

- **main.c**  
  Implementação do solver da equação de Poisson (discretização, malha, condições de contorno, iterações e cálculo de erro).

- **Makefile**  
  Automatiza:
  - compilação  
  - execução  
  - geração de gráficos  
  - limpeza dos arquivos criados

- **graphic.gp**  
  Script Gnuplot para gerar os gráficos da solução.

- **verificacao/**  
  Pasta contendo o código usado para estudar a ordem de convergência do método.

---
