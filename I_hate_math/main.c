#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include "compute_T.h"


int main(){
	float T_new, Cv, H, e, R; // R is mean Residual function
	float a1, a2, a3, a4, a5, a6;//coefficients of compute Cv and H
	float T = 300;
	float Tolerance = 0.001;
        float R_gas = 296.8; // R of N2 is 296.8 J/(kg*K)
        float e_target = 2000000;
        float error = 100.0;

	while(error > Tolerance){
		//Decide whether to use the high-temperature or low-temperature coefficients.
		if(T <= 1000){
		a1 = 3.298677;
		a2 = 0.14082404e-2;
		a3 = -0.03963222e-4;
		a4 = 0.05641514e-7;
		a5 = -0.02444854e-10;
		a6 = -0.10208999e4;
		}else{
		a1 = 2.926640;
		a2 = 0.14879768e-2;
		a3 = -0.05684760e-5;
		a4 = 0.10097038e-9;
		a5 = -0.06753351e-13;
		a6 = -0.09227977e4;
		}
		//Compute T
		Cv = R_gas * (a1 + a2*T + (a3 * pow(T,2)) + (a4 * pow(T,3)) + (a5 * pow(T,4))) - R_gas; //Cv = (Cp/R)dimensionless * Rgas - Rgas
		H = R_gas * T * (a1 + ((a2/2.0)*T) + ((a3/3.0) * pow(T,2)) + ((a4/4.0) * pow(T,3)) + ((a5/5.0) * pow(T,4)) + (a6/T)); //H = (H/RT)dimensionless * RgasT
		e = H - R_gas * T; //H = E + PV => h = e + Pv; Pv = RT => h = e + RT => e = h - RT.
		R = e - e_target;
		T_new = T - (R/Cv);
		//Preventing the temperature from rising too quickly
		if(T_new < 300){
		T_new = 300;
		}else if(T_new > 5000){
		T_new = 5000;
		}

		error = fabs(T_new - T);
		T = T_new;
	}
printf("Final temperature is %.9f K.\n", T);
printf("\nHello world!\n");
return 0;
}
