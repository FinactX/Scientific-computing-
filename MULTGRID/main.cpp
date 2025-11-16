#include "Array.h"
#include "functions.h"
#include <cmath>   // For Mathematical Functions
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <fstream> // For file Operations
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

int main(int argc, char **argv) {
  if (argc != 5) {
    std::cout << " Args : nrows ncols levels cycles " << std::endl ;
exit ( 0 );
  }
  int nrows = atoi(argv[1]);
  int ncols = atoi(argv[2]);
  int nlevels = atoi(argv[3]);
  int iters = atoi(argv[4]);
  
  // Solution and right hand side on each level
  Array<double> *Sol = new Array<double>[nlevels];
  Array<double> *RHS = new Array<double>[nlevels];
  // add 1 ghost layer in each direction
   //  int sizeadd = 2;
  hx = new double[nlevels];
  hy = new double[nlevels];
  
  // allocate memory on each grid level
  for (int i = 0; i < nlevels; i++) {
    Sol[i].resize(nrows + sizeadd, ncols + sizeadd);
    RHS[i].resize(nrows + sizeadd, ncols + sizeadd);
    hx[i] = (xmax - xmin) / (nrows); // Espaçamento em x
    hy[i] = (ymax - ymin) / (ncols); // Espaçamento em y
    nrows = (nrows / 2);
    ncols = (ncols / 2);
  }

  //Sol[nlevels -1].initzeros();
  Sol [ nlevels -1]. initrandom ( 0 , 1 );
  // initialize RHS with source function
  initialize_grid(Sol[0], RHS[0], 0);

  //for (int lev = 1; lev < nlevels; lev++)
    //rhsAdjust(RHS[lev], Sol[lev].nrows(), Sol[lev].ncols(), lev);
    
  // restrict right hand side to all coarse grids
  for (int i = 1; i < nlevels; i++)
      Restrict(RHS[i - 1], RHS[i]);


      
  // compute normalized starting residual
  double res_0 = residual(0, Sol, RHS);
  std::cout << "Starting residual: " << res_0 << std::endl;
  // call FMG solver
  std::cout << "Residual after FMG iteration: "
            << FMG_Solver(Sol, RHS, nlevels, iters, res_0) << std::endl;

  double error = 0.0;

for (int i = 1; i < Sol[0].nrows() - sizeadd; ++i) {
    double x = xmin + (double(i) - center) * hx[0];  // Centro da célula
    for (int j = 1; j < Sol[0].ncols() - sizeadd; ++j) {
        double y = ymin + (double(j) - center) * hy[0];  // Centro da célula no eixo y
        double analytical = analyticalSolution(x, y);  // Solução analítica no centro da célula
        error += pow(Sol[0](i, j) - analytical, 2);  // Erro quadrático

//         std::cout << "dif=    " << Sol[0](i, j) - analytical  << "Sol[0](i, j)= " << Sol[0](i, j) << "analytical= " << analytical;
    }
}
    // Salvar a solução analítica
    save_analytical_solution("solucao_analitica.dat", Sol[0].nrows(), Sol[0].ncols(), hx, hy, 0);
    error = sqrt(error) / (Sol[0].nrows() * Sol[0].ncols());
    std::cout << "h: " << *hx << "\tErro relativo L2: " << error << std::endl;

  delete[] Sol;
  delete[] RHS;
  delete[] hx;
  delete[] hy;
  return 0;
}
