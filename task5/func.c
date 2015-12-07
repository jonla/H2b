#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define PI 3.141592653589

double local_energy(double R[6], double alpha) {
    int i;
    double r1=0, r2=0, r12=0, r1r2=0;
    double term12, term35;

    for (i=0; i<3; i++) {
        r1 += R[i]*R[i];
        r2 += R[i+3]*R[i+3];
        r12 += (R[i]-R[i+3])*(R[i]-R[i+3]);
        r1r2 += R[i]*R[i+3];
    }
    r1 = sqrt(r1);
    r2 = sqrt(r2);
    r12 = sqrt(r12);

    term12 = -4.0 + (r1+r2-r1r2/r1-r1r2/r2) / (r12*pow(1+alpha*r12, 2));
    term35 = -1.0/(r12*pow(1+alpha*r12, 3)) - 1.0/(4.0*pow(1+alpha*r12, 4)) + 1.0/r12;
    return term12 + term35;
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

double d_log_wave(double R[6], double alpha) {
    int i;
    double r12 = 0;

    for (i=0; i<3; i++) {
        r12 += (R[i]-R[i+3])*(R[i]-R[i+3]);
    }

    return -r12*r12*pow(1.0+alpha*r12,-2.0) / 2.0;
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

double block_var(double *data, int nbr_lines, int B) {
    int i,j;
    int NB;
    double xbarB, x2barB, Bvar;

    NB = nbr_lines / B;
    double *Bf = malloc((NB) * sizeof (double));

    /* Block averaging */
    xbarB = 0;
    x2barB = 0;
    for (i=0; i<NB; i++) {
        Bf[i] = 0;
        for (j=0; j<B; j++) {
            Bf[i] += data[B*i + j];
        }
        Bf[i] = Bf[i] / (double) B;
        xbarB += Bf[i];
        x2barB += Bf[i]*Bf[i];
    }
    xbarB = xbarB / (double) NB;
    x2barB = x2barB / (double) NB;
    Bvar = x2barB - xbarB*xbarB;

    free(Bf), Bf = NULL;

    return Bvar;
}
