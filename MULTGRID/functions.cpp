#include "Array.h"
#include "functions.h"
#include <cmath> 
#include <iostream> 
#include <fstream>
#include <iomanip>

// Global Variables
double *hx = nullptr, *hy = nullptr;
bool isNeumann = false; //true for Neumann or false for Dirichlet

//Validation
//Gamma
double gammaFunction(double x, double y) {
    return 1.0 + 0.2 * sin(PI * x) * cos(PI * y);
}

// Source Term
double sourceFunction(double a, double b) {
	if(isNeumann){ return - 4.0 * PI * cos(2.0 * PI * a) * sin(2.0 * PI * b);}
	else{ return  2 * PI * PI * sin(PI * a) * sin(PI * b);}
}

// Analytical Solution
double analyticalSolution(double a, double b) {
	if(isNeumann){ return - cos(2.0 * PI * a) * sin(2.0 * PI * b) / (2.0 * PI);}
	else { return  sin(PI * a) * sin(PI * b);}
}

// Partial Dif. in x
double Dxu(double a, double b) { return - sin(2.0 * PI * a) * sin(2.0 * PI * b);}

// Partial Dif. in y
double Dyu(double a, double b) { return cos(2.0 * PI * a) * cos(2.0 * PI * b);}

// Initialize Grid's
void initialize_grid(Array<double> &grid, Array<double> &rhs, int lev) {
    int nrows = grid.nrows();
    int ncols = grid.ncols();
    double c, t, yy, x, y;
    double rhsSoma = 0.0;
    double rhsSoma2 = 0.0;
    c = 0.0;
    t = 0.0;
    yy = 0.0;

    for (int i = 1; i < nrows - 1; i++) {
        x = xmin + (double(i) - center) * hx[lev];  // Center Cell
        for (int j = 1; j < ncols - 1; j++) {
            y = ymin + (double(j) - center) * hy[lev];  // Center Cell
            grid(i, j) = 0.0;          
            rhs(i,j) = sourceFunction(x, y);// Inicialize a solução
            //gamma(i, j) = gammaFunction(x, y);// Inicialize gamma
            // using Kahan sum:
            yy = rhs(i,j) - c;
            t = rhsSoma + yy;
            c = (t - rhsSoma) - yy;
            rhsSoma = t;
        }//std::cout<< ncols<<"\n";
        //std::cout<< nrows<<"\n";
    }        // Correção para condições de Neumann
    if (isNeumann) {
        // Atualiza o termo fonte (RHS) com a correção
        c = 0.0;
        t = 0.0;
        yy = 0.0;
        for (int i = 1; i < nrows - 1; i++) {
            for (int j = 1; j < ncols - 1; j++) {
                rhs(i, j) = rhs(i,j) + rhsSoma / ((double)((nrows - sizeadd) * (ncols - sizeadd)));
                // using Kahan sum:
                yy = rhs(i, j) - c;
                t = rhsSoma2 + yy;
                c = t - rhsSoma2 - yy;
                rhsSoma2 = t;
                //std::cout<< ncols<<"\n";
            }
        }
     }
}

void rhsAdjust(Array < double > & RHS, int nrows, int ncols, int lev) {
    // RHS Sum
    double sum = 0.0;
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            sum += RHS(i,j);
        }
    }

    double mean = sum / (double)((nrows - sizeadd) * (ncols - sizeadd));
    // Subtracting the mean
    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++) {
            RHS(i,j) -= mean;
        }
    }
}

void interpolate(Array<double> &uf, Array<double> &uc, int l) {
  double v;
  // loop over coarse grid points
  for (int i = 1; i < uc.nrows() - 1; i++) {
    int fi = 2 * i;
    for (int j = 1; j < uc.ncols() - 1; j++) {
      int fj = 2 * j;
      v = uc(i, j);
      uf(fi, fj) = v;
      uf(fi - 1, fj) = v;
      uf(fi, fj - 1) = v;
      uf(fi - 1, fj - 1) = v;
    }
  }
}

void interpolate_correct(Array<double> &uf, Array<double> &uc, int l) {
  double v;
  // loop over coarse grid points
  for (int i = 1; i < uc.nrows() - 1; i++) {
    int fi = 2 * i;
    for (int j = 1; j < uc.ncols() - 1; j++) {
      int fj = 2 * j;
      v = uc(i, j);
      uf(fi, fj) += v;
      uf(fi - 1, fj) += v;
      uf(fi, fj - 1) += v;
      uf(fi - 1, fj - 1) += v;
    }
  }
}

void Restrict(Array<double> &fine, Array<double> &coarse) {
  // loop over coarse grid points
  for (int i = 1; i < coarse.nrows() - 1; i++) {
    int fi = 2 * i;
    for (int j = 1; j < coarse.ncols() - 1; j++) {
      int fj = 2 * j;
      coarse(i, j) = double(0.25) * (fine(fi, fj) + fine(fi - 1, fj) +
                                     fine(fi, fj - 1) + fine(fi - 1, fj - 1));
    }
  }
}
void Restrict_Residual(int lev, Array<double> *Sol, Array<double> *RHS) {
  // loop over coarse grid points
  for (int i = 1; i < RHS[lev + 1].nrows() - 1; i++) {
    int fi = 2 * i;
    for (int j = 1; j < RHS[lev + 1].ncols() - 1; j++) {
      int fj = 2 * j;
      RHS[lev + 1](i, j) =
          double(0.25) * (RES(fi, fj, lev) + RES(fi - 1, fj, lev) +
                          RES(fi, fj - 1, lev) + RES(fi - 1, fj - 1, lev));
    }
  }
}

void treatboundary(Array<double> &grid, int lev, Array<double> *Sol, Array<double> *RHS, double* hx, double* hy) {
    int nrows = grid.nrows();
    int ncols = grid.ncols();

    // Dirichlet node cell
    if ((isNeumann == false) && (center < 0.25)){
        for (int i = 0; i < Sol[lev].nrows(); i++) {
            double x = xmin + (double(i) - center) * hx[lev];  // Center Cell
            Sol[lev](i, 0) = analyticalSolution(x, ymin); // Botton
            Sol[lev](i, Sol[lev].ncols() - 1) = analyticalSolution(x, ymax); // Top
        }
        for (int j = 0; j < Sol[lev].ncols(); j++) {
            double y = (double(j) + center) * hy[lev];
            Sol[lev](0, j) = analyticalSolution(xmin, y); // Left
            Sol[lev](Sol[lev].nrows() - 1, j) = analyticalSolution(xmax, y); // Right
        }
     }
    //Neumann centered cell
    if (isNeumann == true && center > 0.25){
        for (int i = 0; i < Sol[lev].nrows(); i++) {
            double x = xmin + (double(i) - center) * hx[lev];  // Center Cell
            Sol[lev](i, 0) = - hy[lev] * Dxu(x, ymin) + Sol[lev](i, 1); // Botton
            //std::cout << "x = " << x << ", Sol[lev](" << i << ", 0) = " << Sol[lev](i, 0) << "\n";
            Sol[lev](i, Sol[lev].ncols() - 1) = hy[lev] * Dxu(x, ymax) + Sol[lev](i, Sol[lev].ncols() - sizeadd); // Top
            //std::cout << "x = " << x << ", Sol[lev](" << i << ", " << Sol[lev].ncols() - 1 << ") = " 
                  //<< Sol[lev](i, Sol[lev].ncols() - 1) << "\n";
            
            //Sol[lev](i, 0) = Sol[lev](i, 1);
            //Sol[lev](i, Sol[lev].ncols() - 1) = Sol[lev](i, Sol[lev].ncols() - 2);
        }
        for (int j = 0; j < Sol[lev].ncols(); j++) {
            double y = ymin + (double(j) - center) * hy[lev];
            Sol[lev](0, j) = - hx[lev] * Dyu(xmin, y) + Sol[lev](1, j); // Left
            //std::cout << "y = " << y << ", Sol[lev](0, " << j << ") = " << Sol[lev](0, j) << "\n";
            Sol[lev](Sol[lev].nrows() - 1, j) = + hx[lev] * Dyu(xmax, y) + Sol[lev](Sol[lev].nrows() - sizeadd, j); // Right
            //std::cout << "y = " << y << ", Sol[lev](" << Sol[lev].nrows() - 1 << ", " << j << ") = " 
                  //<< Sol[lev](Sol[lev].nrows() - 1, j) << "\n";
                  
            //Sol[lev](0, j) = Sol[lev](1, j);
            //Sol[lev](Sol[lev].nrows() - 1, j) = Sol[lev](Sol[lev].nrows() - 2, j); 
            
        }
    }
    // Dirichlet centered cell
    if (isNeumann == false && center > 0.25) {
        for (int i = 0; i < Sol[lev].nrows(); i++) {
            double x = xmin + (double(i) - center) * hx[lev];  // Center Cell
            Sol[lev](i, 0) = 2.0 * analyticalSolution(x, ymin) - Sol[lev](i, 1); // Botton
            Sol[lev](i, Sol[lev].ncols() - 1) = 2.0 * analyticalSolution(x, ymax) - Sol[lev](i, Sol[lev].ncols() - sizeadd); // Top
        }
        for (int j = 0; j < Sol[lev].ncols(); j++) {
            double y = ymin + (double(j) - center) * hy[lev];
            Sol[lev](0, j) = 2.0 * analyticalSolution(xmin, y) - Sol[lev](1, j); // Left
            Sol[lev](Sol[lev].nrows() - 1, j) = 2.0 * analyticalSolution(xmax, y) - Sol[lev](Sol[lev].nrows() - sizeadd, j); // Right
    	}
    }
}
void GaussSeidel( int lev , Array < double >* Sol , Array < double >* RHS )
{
double denom = double (2.0) * (hx[lev] * hx[lev]) + double (2.0) * (hy[lev] * hy[lev]); 
// assure boundary conditions
treatboundary ( Sol[lev], lev , Sol, RHS, hx, hy);
// Gauss - Seidel relaxation with damping parameter
for ( int i =1; i < Sol [ lev ]. nrows () -1; i ++ )
{
for ( int j =1; j < Sol [ lev ]. ncols () -1; j ++ )
{
Sol[lev](i, j)= (RHS[lev](i, j) * hx[lev] * hx[lev] * hy[lev] * hy[lev] + \
 		(Sol[lev](i+1, j) + Sol[lev](i-1, j)) * hy[lev] * hy[lev] + \
		(Sol[lev](i, j+1) + Sol[lev](i, j-1)) * hx[lev] * hx[lev]) / denom;
		
}
}
// assure boundary conditions
treatboundary (Sol[lev], lev , Sol, RHS, hx, hy);
}

double residual(int lev, Array<double> *Sol, Array<double> *RHS) {
  double res = double(0.0);
  double rf;
  for (int i = 1; i < Sol[lev].nrows() - 1; i++) {
    for (int j = 1; j < Sol[lev].ncols() - 1; j++) {
      rf = RES(i, j, lev); // dar uma olhada nisso!!!
      res += rf * rf;
    }
  }

  return sqrt(res) / (Sol[lev].nrows() * Sol[lev].ncols());
}

void VCycle(int lev, Array<double> *Sol, Array<double> *RHS, int nprae,
            int npost, int ncoarse, int nlevels) {

  // solve problem on coarsest grid ...
  if (lev == nlevels - 1) {
    for (int i = 0; i < ncoarse; i++)
      GaussSeidel(lev, Sol, RHS);
  } else {
    // ... or recursively do V-cycle
    // do some presmoothing steps
    for (int i = 0; i < nprae; i++)
      GaussSeidel(lev, Sol, RHS);
    // compute and restrict the residual
    Restrict_Residual(lev, Sol, RHS);
    // initialize the coarse solution to zero
    Sol[lev + 1].initzeros();
    VCycle(lev + 1, Sol, RHS, nprae, npost, ncoarse, nlevels);
    // interpolate error and correct fine solution
    interpolate_correct(Sol[lev], Sol[lev + 1], lev + 1);
    // do some postsmoothing steps
    for (int i = 0; i < npost; i++)
      GaussSeidel(lev, Sol, RHS);
  }
}

double FMG_Solver(Array<double> *Sol, Array<double> *RHS, int nlevels, int iters, double res_0) {
    double res = res_0, res_old;
    int nprae = 3, npost = 2, ncoarse = 10;
    
    for (int lev = nlevels - 1; lev >= 0; lev--) {

//       std::cout << "lev=" << lev << "\t iters=" << iters;
//       getchar();

        for (int i = 0; i < iters; i++) {
            res_old = res;
            VCycle(lev, Sol, RHS, nprae, npost, ncoarse, nlevels);
            res = residual(lev, Sol, RHS);
            
            std::cout << " \tFMG level: " << lev << " \tcycle: " << i
                      << " \tresidual: " << res
                      << " \tresidual reduction: " << res_0 / res
                      << " \tConvergence factor: " 
                      << res / res_old << std::endl;
        }
	std::string filename = "solution_level_" + std::to_string(lev) + ".dat";
        plot_to_file(Sol[lev], filename, hx, hy, lev);  // Chamada correta
        // Salva os dados da solução para o arquivo
        if (lev > 0) {
            interpolate(Sol[lev - 1], Sol[lev], lev);
        }
    }
    return res;
}

// Plots
void plot_to_file(Array<double> &data, const std::string &filename, double* hx, double* hy, int lev) {

    std::string output_dir = "data_output/";  // Pasta para salvar os arquivos .dat
    std::string full_filename = output_dir + filename; 
    std::ofstream outfile(full_filename);
    if (!outfile.is_open()) {
        std::cerr << "Error opening file: " << full_filename << std::endl;
        return;
    }
    for (int i = 1; i < data.nrows() -1; ++i) {
        double x = xmin + (double(i) - center) * hx[lev];  // Centro da célula
        for (int j = 1; j < data.ncols() - 1; ++j) {
          double y = ymin + (double(j) - center) * hy[lev];  // Centro da célula
          outfile << x << "\t" << y << "\t" << data(i, j) << std::endl;
        }
        outfile << std::endl;
    }
    outfile.close();
}

void save_analytical_solution(const std::string& filename, int nx, int ny, double* hx, double* hy, int lev) {

    std::string output_dir = "data_output/";  // Pasta para salvar os arquivos .dat
    std::string full_filename = output_dir + filename;
    std::ofstream outfile(full_filename);
    
    if (!outfile) {
        std::cerr << "Erro ao abrir o arquivo " << full_filename << std::endl;
        return;
    }
    for (int i = 1; i < nx - 1; ++i) {
        for (int j = 1; j < ny - 1; ++j) {
            double x = xmin + (double(i) - center) * hx[lev];  // Centro da célula
            double y = ymin + (double(j) - center) * hy[lev];  // Centro da célula
            double u_analytical = analyticalSolution(x, y);
            outfile << std::setprecision(8) << x << " " << y << " " << u_analytical << std::endl;
        }
        outfile << std::endl;
    }

    outfile.close();
}
