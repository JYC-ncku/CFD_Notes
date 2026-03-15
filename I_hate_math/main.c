#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include "compute_T.h"


int main(){
	int step = 0;
	float T_new, T_old;
	float T_guess = 300;
        float a1 = 3.298677;
        float a2 = 1.4082404e-3;
        float a3 = -3.963222e-6;
        float a4 = 5.641515e-9;
        float a5 = -2.444854e-12;
        float a6 = -1.0208999e3;
        float R_gas = 296.8; // R of N2 is 296.8 J/(kg*K)

        float Cv = R_gas * (a1 + (a2 * T_guess) + (a3 * pow(T_guess,2)) + (a4 * pow(T_guess,3)) + (a5 * pow(T_guess,4)) - 1.0);
        float u = R_gas * ( ((a1 - 1.0) * T_guess) + ((a2/2) * (T_guess * T_guess)) + ((a3/3) * pow(T_guess,3)) + ((a4/4) * pow(T_guess,4)) + ((a5/5) * pow(T_guess,5)) + a6);
        float u_target = 625000; // u_target = (E/rho) - 0.5(u*u + v*v + w*w)
        float R = u - u_target;
	printf("R/Cv = %g\n", R/Cv);
	//Firtst calculation
	T_old = T_guess;
        T_new = T_old - (R/Cv);
        T_old = T_new;
        printf("T_old1 = %.6f\n", T_old);
        // Iteration 1
        Cv = R_gas * (a1 + (a2 * T_old) + (a3 * pow(T_old,2)) + (a4 * pow(T_old,3)) + (a5 * pow(T_old,4)) - 1.0);
        u = R_gas * ((a1 - 1.0)*T_old + (a2/2)*T_old*T_old + (a3/3)*pow(T_old,3) + (a4/4)*pow(T_old,4) + (a5/5)*pow(T_old,5) + a6);
	R = u - u_target;
	T_new = T_old - (R/Cv);
	T_old = T_new;
	printf("T_old2 = %.6f\n", T_old);
	//Interation 2
	Cv = R_gas * (a1 + (a2 * T_old) + (a3 * pow(T_old,2)) + (a4 * pow(T_old,3)) + (a5 * pow(T_old,4)) - 1.0);
        u = R_gas * ((a1 - 1.0)*T_old + (a2/2)*T_old*T_old + (a3/3)*pow(T_old,3) + (a4/4)*pow(T_old,4) + (a5/5)*pow(T_old,5) + a6);
        R = u - u_target;
        T_new = T_old - (R/Cv);
        T_old = T_new;
	printf("T_old3 = %.6f\n", T_old);

printf("\nHello world!\n");
return 0;
}
