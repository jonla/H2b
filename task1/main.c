#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define PI 3.141592653589

/* Declare functions */
double integrand(double x[3]);
double accept_ratio(double x[3], double y[3]);
void draw(double *y, double x[3], double delta);

/* Main program */
int main() {

    /* Declare variables */
    int i;
    int N;
    int nbr_accept;
    double delta, q, r, p, f, estimate;
    double x[3], y[3];
    FILE *file_x;

    // Initialize random seed
    srand(time(NULL));


    N = pow(10,5);
    delta = 1.8;
    x[0] = 0; x[1] = 0; x[2] = 0;
    estimate = integrand(x);

    file_x = fopen("samples.dat","w");
    nbr_accept = 0;
    for (i=0; i<N; i++) {
        draw(y, x, delta);
        q = accept_ratio(x, y);
        r = (double)rand()/(double)RAND_MAX;
        if (r < q) {
            // Accept
            nbr_accept += 1;
            x[0] = y[0];
            x[1] = y[1];
            x[2] = y[2];
        }

        p = pow(PI,-3.0/2.0)*exp(-x[0]*x[0] - x[1]*x[1] - x[2]*x[2]);
        f = integrand(x)/p;
        estimate = i/((double)i+1)*estimate + 1/((double)i+1)*f;

        // Print to file
        fprintf(file_x,"%e \t %e \t %e \t %e \n", x[0], x[1], x[2], estimate);
    }

    //printf("N = %d : \t Approx: %e \t Error: %e  \n", N, output, error);
    printf("Accept ratio: %e \n", (double)nbr_accept/(double)N);
    printf("value: %e \n", estimate);
    fclose(file_x);
}


double integrand(double x[3]) {
    return pow(PI,-3.0/2.0)*x[0]*x[0]*(1 + x[1]*x[1]*(1 + x[2]*x[2])) \
        *exp(-x[0]*x[0] - x[1]*x[1] - x[2]*x[2]);
}


double accept_ratio(double x[3], double y[3]) {
    return exp(-y[0]*y[0] - y[1]*y[1] - y[2]*y[2] \
            +x[0]*x[0] + x[1]*x[1] + x[2]*x[2]);
}

void draw(double *y, double x[3], double delta) {
    y[0] = x[0] + delta*((double)rand()/(double)RAND_MAX - 0.5);
    y[1] = x[1] + delta*((double)rand()/(double)RAND_MAX - 0.5);
    y[2] = x[2] + delta*((double)rand()/(double)RAND_MAX - 0.5);
}






