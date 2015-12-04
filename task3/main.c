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
    int N;
    int nbr_accept;
    double delta, q, r;
    double alpha;
    double energy;
    double alpha_energy[20];
    double R[6], Rt[6];
    FILE *file_E;

    // Initialize random seed
    srand(time(NULL));

    // Set parameters
    N = 5*pow(10,7);
    alpha = 0.05;
    delta = 1;
    for (i=0; i<3; i++) {
        R[i] = 1;
        R[i+3] = -1;
    }

    for (k=0; k < 20; k++)
    {
        energy = 0;
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
            energy += local_energy(R, alpha);

        }
        alpha_energy[k] = energy / (double) N;
        alpha += 0.01;
    }


    file_E = fopen("alpha_energy.dat","w");
    // Print to file
    for (k=0; k<20; k++) {
        fprintf(file_E,"%e \n", alpha_energy[k]);
    }
    fclose(file_E);

    return 0;

}



