#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "func.h"
#define PI 3.141592653589


/* Main program */
int main() {

    /* Declare variables */
    int i, j, k, n;
    int N;
    int nbr_accept;
    double delta, q, r;
    double alpha;
    double energy;
    double alpha_energy[20];
    double xvar, s;
    double R[6], Rt[6];
    FILE *file_E;

    // Initialize random seed
    srand(time(NULL));

    // Set parameters
    N = pow(10,5);
    alpha = 0.05;
    delta = 1;


    for (k=0; k < 20; k++)
    {
        printf("alpha value currently at %f\n", alpha);
        energy = 0;
        nbr_accept = 0;
        for (n=0; n < 10; n++)
        {
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
                }
            }
        }
        alpha_energy[k] = energy / (double) (10*(N-1000));
        alpha += 0.01;
    }


    file_E = fopen("alpha_energy_indie.dat","w");
    // Print to file
    for (k=0; k<20; k++) {
        fprintf(file_E,"%e \n", alpha_energy[k]);
    }
    fclose(file_E);

    return 0;

}



