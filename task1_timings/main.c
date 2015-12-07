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

    // Initialize random seed
    srand(time(NULL));

    // Set parameters
    N = pow(10,6);
    alpha = 0.1;
    delta = 1;
    for (i=0; i<3; i++) {
        R[i] = 2*((double)rand() / (double)RAND_MAX - 0.5);
        R[i+3] = 2*((double)rand() / (double)RAND_MAX - 0.5);
    }

    nbr_accept = 0;
    energy = 0;
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
    energy /= (double) N;
    printf("Ground State Energy: %f", energy);

    return 0;

}





