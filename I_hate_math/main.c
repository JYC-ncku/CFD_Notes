#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "compute_T.h"


int main(){
	float T = 300.0;
	float e_target = 770.0 * 400.0;

	float Final_T = compute_T(T, e_target);

printf("Final temperature is %.9f K.\n", Final_T);

return 0;
}
