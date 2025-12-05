#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define Lx 20
#define Ly 20
#define N (Lx * Ly)
#define J 1.0
#define k_B 1.0
#define MC_STEPS 100000
#define THERMALIZATION 5000
#define T_MIN 0.5
#define T_MAX 10.0
#define T_STEP 0.5

int spin[Lx][Ly];

//void ini_rede() {
//    for (int i = 0; i < L; i++)
//        for (int j = 0; j < L; j++)
//            spin[i][j] = (rand() % 2) * 2 - 1;
//}
void ini_rede() {
    // TODO MUNDO DOWN
    for (int i = 0; i < Lx; i++)
        for (int j = 0; j < Ly; j++)
            spin[i][j] = -1;

    // 1/4  SPIN UP
    int total_up = N / 4;
    int count = 0;

    while (count < total_up) {
        int i = rand() % Lx;
        int j = rand() % Ly;
        if (spin[i][j] == -1) {
            spin[i][j] = 1;
            count++;
        }
    }
}

// CONTORNOZINHO
int neighbor_x(int i) {
    if (i == -1) return Lx - 1;
    if (i == Lx) return 0;
    return i;
}
int neighbor_y(int j) {
    if (j == -1) return Ly - 1;
    if (j == Ly) return 0;
    return j;
}

double delta_E(int i, int j) {
	int up = spin[neighbor_x(i - 1)][j];
	int down = spin[neighbor_x(i + 1)][j];
	int left = spin[i][neighbor_y(j - 1)];
	int right = spin[i][neighbor_y(j + 1)];
	int neighbor_sum = up + down + left + right;
	return 2.0 * J * spin[i][j] * neighbor_sum;
}

//PASSO DE METRÓPOLIS
void metropolis(double T) {
	for (int n = 0; n < N; n++) {
		int i = rand() % Lx;
		int j = rand() % Ly;
		double dE = delta_E(i, j);
		//CRITÉRIO DE ACEITAÇÃO, IMPORTANTE ESSE TREM
		if (dE <= 0.0 || ((double)rand()/ RAND_MAX) < exp(-dE/ (k_B* T)))
		spin[i][j] *= -1;
	}
}

double t_Energy() {
    double E = 0.0;
    #pragma omp parallel for
    for (int i = 0; i < Lx; i++)
        for (int j = 0; j < Ly; j++) {
            int right = spin[i][neighbor_y(j + 1)];
            int down = spin[neighbor_x(i + 1)][j];
            E += -J * spin[i][j] * (right + down);
        }
    return E;
}

double t_Magnetization() {
    double M = 0.0;
    #pragma omp parallel for
    for (int i = 0; i < Lx; i++)
        for (int j = 0; j < Ly; j++)
            M += spin[i][j];
    return M;
}

int main() {
	//SEMENTINHA
    srand(time(NULL));
    FILE *fp = fopen("saida.dat", "w");
    fprintf(fp, "T, <E>, <|M|>, Cv, Chi\n");
	
	for (double T = T_MAX; T >=T_MIN + 1e-6; T -= T_STEP) {
		ini_rede();

		for (int t = 0; t < THERMALIZATION; t++)
			metropolis(T);

		double E_sum = 0.0, E2_sum = 0.0;
		double M_sum_abs = 0.0;       // Para <|M|>
		double M_sum = 0.0, M2_sum = 0.0; // Para \Chi

/*if (fabs(T - 4.0) < 1e-6) {  // T = slá, qualquer porra
    FILE *fconf = fopen("config_T%.1f.dat", "w");
    if (fconf == NULL) {
        perror("Erro ao abrir arquivo");
        exit(1);
    }

    for (int i = 0; i < Lx; i++) {
        for (int j = 0; j < Ly; j++) {
            fprintf(fconf, "%d ", spin[i][j]);
        }
        fprintf(fconf, "\n");
    }

    fclose(fconf);
}*/

//PRINTAR AS CONFIGURAÇÕES
		if (fabs(T- 1.0) < 1e-6 || fabs(T- 1.5) < 1e-6 || fabs(T- 2.0) < 1e-6 || fabs(T- 2.5) < 1e-6 || fabs(T- 3.0) < 1e-6 || fabs(T- 4.0) < 1e-6 || fabs(T- 5.0) < 1e-6 || fabs(T- 10.0) < 1e-6)  {
			char saida[64];
			snprintf(saida, sizeof(saida), "config_T%.1f.dat", T);
			FILE *fconf = fopen(saida, "w");
			for (int i = 0; i < Ly; i++) {
				for (int j = 0; j < Lx; j++)
					fprintf(fconf, "%d ", spin[i][j]);
				fprintf(fconf, "\n");
			}
		fclose(fconf);
		}

		for (int t = 0; t < MC_STEPS; t++) {
			metropolis(T);

			double E = t_Energy();
			double M = t_Magnetization();

			E_sum += E;
			E2_sum += E * E;
			M_sum += M;
			M2_sum += M * M;
			M_sum_abs += fabs(M); // Para <|M|>
		}
		double E_avg = E_sum / MC_STEPS;
		double E2_avg = E2_sum / MC_STEPS;
		double M_avg_abs = M_sum_abs / MC_STEPS;
		double M_avg = M_sum / MC_STEPS;
		double M2_avg = M2_sum / MC_STEPS;

	// NORMALIZAÇÃO POR SPIN
		double e_avg = E_avg / N;
		double cv = (E2_avg - E_avg * E_avg) / (k_B * T * T * N);
		double m_avg = M_avg_abs / N;
		double chi = (M2_avg - M_avg * M_avg) / (k_B * T * N);

		printf("T= %.2f\t<E>= %.3f\t<|M|>= %.3f\tCv= %.3f\tChi= %.3f\n", T, e_avg, m_avg, cv, chi);
		fprintf(fp, "%.2f, %.3f, %.3f, %.3f, %.3f\n", T, e_avg, m_avg, cv, chi);
		}

		fclose(fp);
		return 0;
}

