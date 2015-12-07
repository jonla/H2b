#ifndef _H2_func_h
#define _H2_func_h

double local_energy(double[6], double);
double log_wavefun(double[6], double);
double d_log_wave(double[6], double);
double accept_ratio(double[6], double[6], double);
void draw(double *, double[6], double);
double block_var(double *, int, int);

#endif
