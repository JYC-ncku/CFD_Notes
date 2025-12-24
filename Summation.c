#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 建議使用 #define 或在 main 裡定義變數
#define N_TERMS 500 // 級數累加的項數

int main() {
    // 1. 定義已知參數
    double C0 = 0.0;
    double Csat = 1.0;
    double D = 2.0e-5;
    double t = 100.0;
    double h = 0.10;   // Length of your domain
    double dx = 0.001; // 你的 dx 位置
    
    double Pi = M_PI;

    double Fourier[100];

    // 2. 使用 for 迴圈計算級數累加 (n 從 0 到 N_TERMS)
    for (int i = 0; i < 100; i++) {
        double x = (i+0.5)*dx;
        double sum = 0.0;
        for (int n = 0; n < N_TERMS; n++) {
            // 每次迴圈都要重新計算當前的 Bn
            double Bn = ((2.0 * n + 1.0) * Pi)*0.5;

            // 計算級數的當前項 (term)
            double term = (pow(-1.0, n) / Bn) * cos((Bn * x) / h) * exp(-(Bn * Bn * D * t) / (h * h));
            
            // 累加到 sum
            sum += term;
        }
        double C_xt = (2.0 - (C0 + (Csat - C0) * 4.0 * sum))*0.5;
        Fourier[i] = C_xt;
    }

    FILE *pFile;
    pFile = fopen("FourierSolution.txt", "w");
    for (int i = 0; i < 100; i++) {
        double x = (i+0.5)*dx;
        fprintf(pFile, "%g\t%g\n", x, Fourier[i]);
    }
    fclose(pFile);

    return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int N = 200;
const double Pi = M_PI;
double c0 = 0;
double c1 = 1;
double Bn = (((2*N)+1)*Pi)/2;
double D = 2.0e-5;
const int t = 5;
double dx = 0.001

int main (){
    double count = cos((Bn*dx)*N)*exp(-((Bn*Bn*D*t)/(L*L))), sum = 0;

    for (i=0; i<N, i++){
        
    while(count <= N){
        sum = sum+count;
        count++;
    }
    printf("\n Sum = %d\n", sum);
    }

    return 0;
    
}
 */   