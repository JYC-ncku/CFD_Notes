#include <stdlib.h>
#include <stdio.h>
#include <math.h>

float Residual(float T){
	float a1 = 3.298677;
	float a2 = 1.4082404e-3;
	float a3 = -3.963222e-6;
	float a4 = 5.641515e-9;
	float a5 = -2.444854e-12;
	float a6 = 1.0208999e3;
	float R_gas = 296.8; // R of N2 is 296.8 J/(kg*K)

	float Cv = R_gas * (a1 + a2*T + a3*pow(T,2) + a4*pow(T,3) + a5*pow(T,4) - 1.0);
	float u = R_gas * ((a1 - 1.0)*T + (a2/2)*T*T + (a3/3)*pow(T,3) + (a4/4)*pow(T,4) + (a5/5)*pow(T,5) + a6);
	float u_target = 625000; // u_target = (E/rho) - 0.5(u*u + v*v + w*w)
	float R = u - u_target;
return R/Cv;
}

void compute_T(float T_new, float T, float RR){
	T = T_old;
	T_new = T_old - RR;
}
