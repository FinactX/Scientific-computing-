# Solver da Equação de Poisson 2D

Este diretório contém uma implementação numérica da equação de Poisson em duas dimensões usando diferenças finitas e métodos iterativos. O objetivo é resolver

\[
\nabla^2 u = f(x,y)
\]

em um domínio bidimensional com condições de contorno prescritas, além de gerar visualizações da solução numérica.

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
