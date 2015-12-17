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
    int i, j, n;
    int N, N_eq, N_simul;
    int nbr_accept;
    double delta, Q, r;
    double alpha;
    double energy;
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
    N = pow(10,6);
    N_eq = 1000;
    N_simul = 2000;
    alpha = 0.1434;
    delta = 1;

    double E[N_simul];


    nbr_accept = 0;
    for (n=0; n<N_simul; n++) {
        if (n%100 == 0) {
            printf("Iteration %d out of %d \n", n, N_simul);
        }
        energy = 0;
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
            }
        }
        E[n] = energy / (double)(N);
    }

    // Print to file
    file_E = fopen("energy.dat","w");
    for (n=0; n<N_simul; n++) {
        fprintf(file_E,"%e \t", E[n]);
    }
    fclose(file_E);

    return 0;

}



