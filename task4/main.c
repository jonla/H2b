#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "func.h"
#define PI 3.141592653589


/* Main program */
int main() {

    /* Declare variables */
    int i, j, k;
    int N, n_simul;
    n_simul = 40;
    int nbr_accept;
    double delta, q, r;
    double alpha;
    double energy;
    double deriv_log_wave;
    double E_deriv_log_wave;
    double grad_E;
    double gamma, beta, A;
    double alpha_vec[n_simul];
    double alpha_energy[n_simul];
    double R[6], Rt[6];
    FILE *file_E;

    // Initialize random seed
    srand(time(NULL));

    // Set parameters
    N = pow(10,6);
    alpha = 0.20;
    delta = 1;
    A = 0.01;
    beta = 0.65;


    for (k=0; k < n_simul; k++)
    {
        printf("alpha value currently at %f\n", alpha);
        alpha_vec[k] = alpha;
        energy = 0;
        deriv_log_wave = 0;
        E_deriv_log_wave = 0;
        nbr_accept = 0;
        for (i=0; i<3; i++) {
            R[i] = 2*((double)rand()/(double)RAND_MAX -0.5);
            R[i+3] = 2*((double)rand()/(double)RAND_MAX -0.5);
        }
        for (i=0; i<N; i++) {
            draw(Rt, R, delta);
            q = accept_ratio(R, Rt, alpha);
            r = (double)rand()/(double)RAND_MAX;
            if (r < q) {
                // Accept
                nbr_accept += 1;
                for (j=0; j<6; j++) {
                    R[j] = Rt[j];
                }
            }
            // Calculate local energy
            if (i > 1000) {
                energy += local_energy(R, alpha);
                deriv_log_wave += d_log_wave(R,alpha);
                E_deriv_log_wave += local_energy(R, alpha)*d_log_wave(R,alpha);
            }
        }
        energy = energy / (double) ((N-1000));
        deriv_log_wave = deriv_log_wave / (double) ((N-1000));
        E_deriv_log_wave = E_deriv_log_wave / (double) ((N-1000));
        grad_E = 2*(E_deriv_log_wave - energy*deriv_log_wave);
        alpha_energy[k] = energy / (double) ((N-1000));
        gamma = A*pow((double)(k+1),-beta);
        gamma = 0.01;
        alpha += -gamma*grad_E;
    }


    file_E = fopen("alpha_energy_grad.dat","w");
    // Print to file
    for (k=0; k<n_simul; k++) {
        fprintf(file_E,"%e \t %e \n", alpha_vec[k], alpha_energy[k]);
    }
    fclose(file_E);

    return 0;

}



