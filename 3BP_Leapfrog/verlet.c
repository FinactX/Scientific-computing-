#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define M1 1.0//1.989e30//1.0             // Massa dos Corpos
#define M2 1.0//5.972e24//1.0
#define M3 1.0///7.342e22//1.0
#define e 1e-8
const double PI = 3.14159265358979323846;
const double G = 1.0;//6.6743e-11; //G = 1.0;
const double h = 0.0001;//7200;//0.001;       // Passo temporal
const double t_max = 6.325963259; // Tempo total de simulação
const int steps = (int)(t_max / h);
const int N = 3; // Número de Corpos

typedef struct {
    double mass;
    double x, y, z;
    double vx, vy, vz;
    double ax, ay, az;
} Body;

void accelerations_calc(Body *bodies, int n) {
    // Reinicializar acelerações
    for (int i = 0; i < n; i++) {
        bodies[i].ax = 0.0;
        bodies[i].ay = 0.0;
        bodies[i].az = 0.0;
    }

    // FORÇA GRAVITACIONAL
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double dx = bodies[j].x - bodies[i].x;
            double dy = bodies[j].y - bodies[i].y;
            double dz = bodies[j].z - bodies[i].z;
            double r2 = dx*dx + dy*dy + dz*dz;
            double r = sqrt(r2);
            double r3 = r * r2;
            double inv_r3 = 1.0 / (r3 + 1e-10);  // Não divisibilidade por zero

            // Aceleração em i causada por j
            double ai_x = bodies[j].mass * dx * inv_r3;
            double ai_y = bodies[j].mass * dy * inv_r3;
            double ai_z = bodies[j].mass * dz * inv_r3;

            // Aceleração em j causada por i
            double aj_x = -bodies[i].mass * dx * inv_r3;
            double aj_y = -bodies[i].mass * dy * inv_r3;
            double aj_z = -bodies[i].mass * dz * inv_r3;

            bodies[i].ax += ai_x;
            bodies[i].ay += ai_y;
            bodies[i].az += ai_z;

            bodies[j].ax += aj_x;
            bodies[j].ay += aj_y;
            bodies[j].az += aj_z;
        }
    }
}

// MOMENTO LINEAR TOTAL
void linear_momentum_calc(Body *bodies, int n, double *px, double *py, double *pz) {
    *px = *py = *pz = 0.0;
    for (int i = 0; i < n; i++) {
        *px += bodies[i].mass * bodies[i].vx;
        *py += bodies[i].mass * bodies[i].vy;
        *pz += bodies[i].mass * bodies[i].vz;
    }
}

// ENERGIA TOTAL DO SISTEMA
double total_energy_calc(Body *bodies, int n) {
    double E_cinetica = 0.0;
    double E_potencial = 0.0;

    // CINÉTICA K
    for (int i = 0; i < n; i++) {
        double v2 = bodies[i].vx * bodies[i].vx + 
                    bodies[i].vy * bodies[i].vy + 
                    bodies[i].vz * bodies[i].vz;
        E_cinetica += 0.5 * bodies[i].mass * v2;
    // POTENCIAL GRAVITACIONAL V
        for (int j = i + 1; j < n; j++) {
            double dx = bodies[j].x - bodies[i].x;
            double dy = bodies[j].y - bodies[i].y;
            double dz = bodies[j].z - bodies[i].z;
            double r = sqrt(dx*dx + dy*dy + dz*dz); // + 1e-10;// Pequeno incremento para evitar r/0
            E_potencial -= G * (bodies[i].mass * bodies[j].mass) / r;
        }    
    }
    // K + V
    return E_cinetica + E_potencial;
}

int main() {
	double time = 0.0;

    	// CONDIÇÕES INICIAIS
	Body bodies[3] = {
{1.0, 0.97000436, -0.24308753, 0.0, 0.4662036850, 0.4323657300, 0.0},	
{1.0, - 0.97000436, 0.24308753, 0.0, 0.4662036850, 0.4323657300, 0.0},
{1.0, 0.0, 0.0, 0.0, -0.93240737, -0.86473146, 0.0}
	};

	// Arquivos de saída
    FILE *file = fopen("saida.dat", "w");
    FILE *file_energy = fopen("Energy_Momentum.dat", "w");
    if (!file || !file_energy) { perror("Erro ao abrir arquivo"); return 1;}

        // ACELERAÇÕES EM T=0
    accelerations_calc(bodies, 3);
    	// CABEÇALHOS PARA OS ARQUIVOS DE SAÍDA
        fprintf(file_energy, "Tempo Energia_Total Momento_x Momento_y Momento_z\n");
        fprintf(file, "x1 y1 z1 x2 y2 z2 x3 y3 z3 Tempo\n");
    
    //LOOP DE INTEGRAÇÃO - LEAPFROG
    for (int s = 0; s < steps; s++) {
    
        // Meio passo de velocidade
        for (int i = 0; i < 3; i++) {
            bodies[i].vx += 0.5 * h * bodies[i].ax;
            bodies[i].vy += 0.5 * h * bodies[i].ay;
            bodies[i].vz += 0.5 * h * bodies[i].az;
        }
        // Passo completo de posição
        for (int i = 0; i < 3; i++) {
            bodies[i].x += h * bodies[i].vx;
            bodies[i].y += h * bodies[i].vy;
            bodies[i].z += h * bodies[i].vz;
        }
        // Atualizar acelerações
        accelerations_calc(bodies, 3);
        double px, py, pz;
    linear_momentum_calc(bodies, 3, &px, &py, &pz);
    double E_total = total_energy_calc(bodies, 3);
        
        // Segundo meio passo de velocidade
        for (int i = 0; i < 3; i++) {
            bodies[i].vx += 0.5 * h * bodies[i].ax;
            bodies[i].vy += 0.5 * h * bodies[i].ay;
            bodies[i].vz += 0.5 * h * bodies[i].az;
        }

        //linear_momentum_calc(bodies, 3, &px, &py, &pz);
        //E_total = total_energy_calc(bodies, 3);
        //fprintf(file_energy, "%.4f %.6f %.6f %.6f %.6f\n", t, E_total, px, py, pz);

       
	//if(s==0 || s%100000==0){
        for (int i = 0; i < 3; i++){
            	fprintf(file, " %.6f %.6f %.6f ", bodies[i].x, bodies[i].y, bodies[i].z);}
        //}
        //if(s==0 || s%100000==0)
        	fprintf(file_energy, "%.6f %.12f %.12f %.12f %.12f\n", time, E_total, px, py, pz);
        
        //if(s==0 || s%100000==0)
        	//fprintf(file, "\n");
        time+=h;
        	fprintf(file, "\t %.6f\n ", time);
    }
	printf("\nSimulação Concluída com Sucesso!\n");
    fclose(file);
    fclose(file_energy);
    return 0;
}
