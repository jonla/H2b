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
    int nbr_accept;
    double delta, q, r;
    double alpha;
    double energy;
    double R[6], Rt[6];
    FILE *file_R, *file_E;

    // Initialize random seed
    srand(time(NULL));

    // Set parameters
    N = 5*pow(10,5);
    alpha = 0.1;
    delta = 1;
    for (i=0; i<3; i++) {
        R[i] = 1;
        R[i+3] = -1;
    }

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
        energy = local_energy(R, alpha);

        // Print to file
        for (j=0; j<6; j++) {
            fprintf(file_R,"%e \t", R[j]);
        }
        fprintf(file_R,"\n");
        fprintf(file_E,"%e \n", energy);

    }

    printf("Accept ratio: %e \n", (double)nbr_accept/(double)N);
    fclose(file_R);
    fclose(file_E);
}





