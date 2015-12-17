#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include "func.h"
#define PI 3.141592653589


/* Main program */
int main() {

    /* Declare variables */
    int i, j, k, n;
    int N, N_eq, N_simul, N_alpha;
    N_alpha = 20;
    int nbr_accept;
    double delta, Q, r;
    double alpha;
    double energy;
    double deriv_log_wave;
    double E_deriv_log_wave;
    double grad_E;
    double gamma, beta, A;
    double alpha_vec[N_alpha];
    double alpha_energy[N_alpha];
    double R[6], Rt[6];
    FILE *file_E;

    // Initialize random seed
    const gsl_rng_type *T;
    gsl_rng *q;
    gsl_rng_env_setup();
    T = gsl_rng_default;
    q = gsl_rng_alloc(T);
    gsl_rng_set(q,time(NULL));

    // Set parameters
    N = pow(10,5);
    N_eq = 1000;
    N_simul = 100;
    alpha = 0.20;
    delta = 1;
    A = 1;
    beta = 0.6;


    for (k=0; k < N_alpha; k++)
    {
        printf("alpha: %f \t", alpha);
        alpha_vec[k] = alpha;
        energy = 0;
        deriv_log_wave = 0;
        E_deriv_log_wave = 0;
        nbr_accept = 0;
        for (n=0; n<N_simul; n++) {
            for (i=0; i<3; i++) {
                R[i] = 2*gsl_rng_uniform(q)-1.0;
                R[i+3] = 2*gsl_rng_uniform(q)-1.0;
            }
            for (i=0; i<N+N_eq; i++) {
                //draw(Rt, R, delta);
                for (j=0; j<6; j++) {
                    Rt[j] = R[j] + delta*(gsl_rng_uniform(q)-0.5);
                }
                Q = accept_ratio(R, Rt, alpha);
                r = (double)rand()/(double)RAND_MAX;
                if (r < Q) {
                    // Accept
                    nbr_accept += 1;
                    for (j=0; j<6; j++) {
                        R[j] = Rt[j];
                    }
                }
                // Calculate local energy
                if (i > N_eq) {
                    energy += local_energy(R, alpha);
                    deriv_log_wave += d_log_wave(R,alpha);
                    E_deriv_log_wave += local_energy(R, alpha)*d_log_wave(R,alpha);
                }
            }
        }
        energy = energy / (double)(N*N_simul);
        deriv_log_wave = deriv_log_wave / (double) (N*N_simul);
        E_deriv_log_wave = E_deriv_log_wave / (double) (N*N_simul);
        grad_E = 2.0*(E_deriv_log_wave - energy*deriv_log_wave);
        gamma = A*pow((double)(k+1),-beta);
        alpha += -gamma*grad_E;
        alpha_energy[k] = energy;
        printf("Energy: %f \n", energy);
    }


    file_E = fopen("alpha_energy_grad.dat","w");
    // Print to file
    for (k=0; k<N_alpha; k++) {
        fprintf(file_E,"%e \t %e \n", alpha_vec[k], alpha_energy[k]);
    }
    fclose(file_E);

    return 0;

}



