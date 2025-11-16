#include <math.h>
#include <stdio.h>

#define Nx 130           // Número de pontos x
#define Ny 130           // Número de pontos y
#define MAX_ITER 1000000 // Número máximo de iterações
#define TOLERANCE 1e-16  // Tolerância para a convergência
#define PI 3.14159265359
#define centerCel 1.0
#define Ymin 0.0
#define Ymax 1.0
#define Xmin 0.0
#define Xmax 1.0

// Função fonte
double sourceFunction(double a, double b) {
  return -2 * PI * PI * sin(PI * a) * sin(PI * b);
}

// Discretização DIFERENÇAS CENTRADAS DE 2ª ORDEM
double centralDifference(double u[Nx][Ny], int i, int j, double dx, double dy) {
  double x = Xmin + ((double)(i)-0.5 * centerCel) * dx;
  double y = Ymin + ((double)(j)-0.5 * centerCel) * dy;

  return (dy * dy * (u[i + 1][j] + u[i - 1][j]) +
          dx * dx * (u[i][j + 1] + u[i][j - 1]) -
          dx * dx * dy * dy * sourceFunction(x, y)) /
         (2.0 * (dx * dx + dy * dy));
}

// Solução analítica
double analyticalSolution(double x, double y) {
  return sin(PI * x) * sin(PI * y);
}
int main() {
  // Inicialização das variáveis
  int i, j, iter = 0;
  double x, y, max_diff, diff;
  double error, error_norm = 0.0;
  double u[Nx][Ny];
  double u_new[Nx][Ny];
  double dx = 1.0 / (Nx - 2); // Espaçamento em x
  double dy = 1.0 / (Ny - 2); // Espaçamento em y

  //  Arquivo de saída
  FILE *file = fopen("saida.dat", "w");
  FILE *analyticalFile = fopen("solucao_analitica.dat", "w");
  FILE *logFile = fopen("log_erro.dat", "a");
  if (file == NULL || analyticalFile == NULL || logFile == NULL) {
    perror("Erro ao abrir o arquivo de saída!");
    return 1;
  }
  //  Condições iniciais
  for (i = 0; i < Nx; i++) {
    for (j = 0; j < Ny; j++) {
      u[i][j] = 0.0;
      u_new[i][j] = 0.0;
    }
  }

  // Método iterativo de aproximação GAUSS-SEIDEL
  for (iter = 0; iter < MAX_ITER; iter++) {
    max_diff = 0.0;

    for (i = 1; i < Nx - 1; i++) {
      for (j = 1; j < Ny - 1; j++) {
        u_new[i][j] = centralDifference(u_new, i, j, dx, dy);
        diff = fabs(u_new[i][j] - u[i][j]);
        if (diff > max_diff)
          max_diff = diff;
      }
    }
    // Contorno Dirichlet
    for (i = 1; i < Nx - 1; i++) {
      x = Xmin + ((double)(i)-0.5 * centerCel) * dx;
      u_new[i][0] = 2.0 * analyticalSolution(x, 0.0) - u_new[i][1];
      u_new[i][Ny - 1] = 2.0 * analyticalSolution(x, 1.0) - u_new[i][Ny - 2];
    }
    for (j = 1; j < Ny - 1; j++) {
      y = Ymin + ((double)(j)-0.5 * centerCel) * dy;
      u_new[0][j] = 2.0 * analyticalSolution(0, y) - u_new[1][j];
      u_new[Nx - 1][j] = 2.0 * analyticalSolution(1.0, y) - u_new[Nx - 2][j];
    }
    // Atualização das soluções
    for (i = 1; i < Nx - 1; i++) {
      for (j = 1; j < Ny - 1; j++) {
        u[i][j] = u_new[i][j];
      }
    }
    // Verificação da convergência
    if (max_diff < TOLERANCE)
      break;
  }

  // Cálculo da norma do erro
  for (i = 1; i < Nx - 1; i++) {
    for (j = 1; j < Ny - 1; j++) {
      x = Xmin + ((double)(i)-0.5 * centerCel) * dx;
      y = Ymin + ((double)(j)-0.5 * centerCel) * dy;
      error = analyticalSolution(x, y) - u[i][j];
      error_norm += (error * error) * (dx * dy);
    }
  }
  fprintf(logFile, "%e %e \n", dx, sqrt(error_norm / Nx * Ny));
  // Solução no arquivo saída
  printf("Solucão após %d iteracões. ", iter);
  printf("\n\nNorma para h=%e: %e \n\n", dx, sqrt(error_norm / Nx * Ny));
  for (i = 1; i < Nx - 1; i++) {
    for (j = 1; j < Ny - 1; j++) {
      x = Xmin + ((double)(i)-0.5 * centerCel) * dx;
      y = Ymin + ((double)(j)-0.5 * centerCel) * dy;
      fprintf(file, "%.2f\t%.2f\t%.8f\n", x, y, u[i][j]);
      fprintf(analyticalFile, "%.2f\t%.2f\t%.8f\n", x, y,
              analyticalSolution(x, y));
    }
  }

  fclose(file);
  fclose(analyticalFile);
  fclose(logFile);
  return 0;
}