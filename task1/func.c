#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define PI 3.141592653589

double integrand(double x[3]) {
    return pow(PI,-3.0/2.0)*x[0]*x[0]*(1 + x[1]*x[1]*(1 + x[2]*x[2])) \
        *exp(-x[0]*x[0] - x[1]*x[1] - x[2]*x[2]);
}

double log_wavefun(double R[6], double alpha) {
    int i;
    double r1=0, r2=0, r12=0;

    for (i=0; i<3; i++) {
        r1 += R[i]*R[i];
        r2 += R[i+3]*R[i+3];
        r12 += (R[i]-R[i+3])*(R[i]-R[i+3]);
    }

    r1 = sqrt(r1);
    r2 = sqrt(r2);
    r12 = sqrt(r12);

    return -2*(r1+r2) + r12/(2+2*alpha*r12);
}

double accept_ratio(double R[6], double Rt[6], double alpha) {
    return exp(2*log_wavefun(Rt, alpha) - 2*log_wavefun(R, alpha));
}

void draw(double *Rt, double R[6], double delta) {
    int i;

    for (i=0; i<6; i++) {
        Rt[i] = R[i] + delta*((double)rand()/(double)RAND_MAX - 0.5);
    }
}

