 #SUMÁRIO
 
 I-INTRODUÇÃO
 II-INSTRUÇÕES PARA EXECUTAR
 III-ARQUIVOS PRESENTES NO PROJETO
 IV-REFERÊNCIAS
 
 
 ###############################################################################
 
 INTRODUÇÃO
 
 A equação de Poisson é um exemplo de EDP (Equação Diferencial Parcial) elíptica
 bastante conhecida na física e modela alguns problemas importantes, como 
 campos eletrostáticos, gravitação newtoniana e problemas de difusão em estado 
 estacionário.
 
 Ela é dada simplesmente pelo Laplaciano de um potencial, definido a partir de
 um termo fonte. Além disso, é uma equação cujas condições de contorno levam a 
 soluções tipicamente suaves.
 
 Há várias formas de resolver numericamente esse tipo de equação, o que
 utilizaremos neste código, é uma discretização por diferenças finitas em
 malha estruturada e solução via Gauss-Seidel para o problema bidimensional.
 
 ###############################################################################
 
 INSTRUÇÕES PARA EXECUTAR
 
 O código está escrito em C, então garanta ter o compilador GCC na sua máquina,
 além do gnuplot para vizualizar as saídas de dados.
 
 Estou usando o Makefile que automatiza as etapas. Logo, para compilar, executar
 e gerar os gráficos dos arquivos "*.dat" criados, apenas dê um
 ~$make
 
 Para apagar os arquivos "*.dat" e "*.png" gerados
 ~$make clean
 
 Não é necessário nenhuma entrada de valores, o que agiliza testes, mas você
 pode modificar como quiser várias quantidades no início do documento "main.c".
   
 ###############################################################################
 
 ARQUIVOS PRESENTES NO PROJETO
 
 [main.c] - Contém o solver.
 
 [graphic.gp] - Script responsável por plotar os gráficos das soluções
 analíticase numéricas.
 
 [Makefile] - Responsável por compilar, executar o código e o script e limpar os
 dados se necessário.
 
 Fiz também uma verificação de ordem desse solver. Como discretizei a equação
 com diferenças finiTas de 2ª ordem, o erro numérico deve cair com mesma ordem,
 a medida que refino minha malha.
 
 Verificação/[erro.gp] - Script responsável por plotar o erro em função do passo
 numa escala logarítimica revelando uma reta de coeficiente angular 2.
 
 ###############################################################################
 
 REFERÊNCIAS
 
 Computational Physics - Nicholas J. Giordano
