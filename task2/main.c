#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "func.h"
#define PI 3.141592653589


/* Main program */
int main() {

    /* Declare variables */
    int i, j;
    int N;
    int B_max;
    int nbr_accept;
    double delta, q, r;
    double alpha;
    double xvar, s;
    double R[6], Rt[6];
    FILE *file_R, *file_E, *file_B;

    // Initialize random seed
    srand(time(NULL));

    // Set parameters
    N = 5*pow(10,5);
    B_max = 1000;
    alpha = 0.1;
    delta = 1;
    for (i=0; i<3; i++) {
        R[i] = (double)rand()/(double)RAND_MAX-0.5;
        R[i+3] = (double)rand()/(double)RAND_MAX-0.5;
    }

    double *energy = malloc(N*sizeof(double));

    file_R = fopen("position.dat","w");
    file_E = fopen("energy.dat","w");
    nbr_accept = 0;
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
        energy[i] = local_energy(R, alpha);

        // Print to file
        for (j=0; j<6; j++) {
            fprintf(file_R,"%e \t", R[j]);
        }
        fprintf(file_R,"\n");
        fprintf(file_E,"%e \n", energy[i]);

    }

    printf("Accept ratio: %e \n", (double)nbr_accept/(double)N);
    fclose(file_R);
    fclose(file_E);

    file_B = fopen("block_avg.dat","w");
    xvar = block_var(energy, N, 1);
    fprintf(file_B,"%e \n", 1.0);
    for (i=2; i<B_max; i++) {
        s = i*block_var(energy, N, i)/xvar;
        fprintf(file_B,"%e \n", s);
    }
    fclose(file_B);

    free(energy), energy = NULL;
}



