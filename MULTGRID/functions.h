#ifndef FUNCOES_H
#define FUNCOES_H

#include "Array.h"
#include <string>

#define RES(i, j, lev) RHS[lev](i, j) + \
            (Sol[lev](i + 1, j) - 2 * Sol[lev](i, j) + Sol[lev](i - 1, j)) / \
            (hx[lev] * hx[lev]) +  \
            (Sol[lev](i, j + 1) - 2 * Sol[lev](i, j) + Sol[lev](i, j - 1)) / \
            (hy[lev] * hy[lev]) -  \
            (alpha * Sol[lev](i, j))
 
extern bool isNeumann;
extern double *hx, *hy;

// Constants
constexpr double PI = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825;
constexpr double center = 0.5; // 0.5 to centered cell or 0.0 for node cell
constexpr int sizeadd = 2; // 2 to centered cell or 1 for node cell     
constexpr double xmin = 0.0;
constexpr double xmax = 1.0;
constexpr double ymin = 0.0;
constexpr double ymax = 1.0;
constexpr double alpha = 0.0;

double gammaFunction(double a, double b);

// Validation Functions
double sourceFunction(double a, double b);
double analyticalSolution(double a, double b);
double Dxu(double a, double b);
double Dyu(double a, double b);

// FMG Functions (Full Multigrid)
void initialize_grid(Array<double> &grid, Array<double> &rhs, int lev);
void interpolate(Array<double> &uf, Array<double> &uc, int l);
void interpolate_correct(Array<double> &uf, Array<double> &uc, int l);
void Restrict(Array<double> &fine, Array<double> &coarse);
void Restrict_Residual(int lev, Array<double> *Sol, Array<double> *RHS);
void treatboundary(Array<double> &grid, int lev, Array<double> *Sol, Array<double> *RHS);
void GaussSeidel( int lev , Array < double >* Sol , Array < double >* RHS);
double residual(int lev, Array<double> *Sol, Array<double> *RHS);
void VCycle(int lev, Array<double> *Sol, Array<double> *RHS, int nprae, int npost, int ncoarse, int nlevels);
double FMG_Solver(Array<double> *Sol, Array<double> *RHS, int nlevels, int iters, double res_0);
//void rhsAdjust(Array < double > & RHS, int nrows, int ncols,  int lev);

// Plot Functions                  
void plot_to_file(Array<double> &data, const std::string &filename, double* hx, double* hy, int lev);
void save_analytical_solution(const std::string& filename, int nx, int ny, double* hx, double* hy, int lev);

#endif // FUNCTIONS_H
