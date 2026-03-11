#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 建議使用 #define 或在 main 裡定義變數
#define N_TERMS 200 // 級數累加的項數

int main() {
    // 1. 定義已知參數
    double C0 = 0.0;
    double Csat = 1.0;
    double D = 2.0e-5;
    double t = 50.0;
    double L = 0.10;   // Length of your domain
    double dx = 0.0005; // 你的 dx 位置
    
    double Pi = M_PI;

    double Fourier[200];

    // 2. 使用 for 迴圈計算級數累加 (n 從 0 到 N_TERMS)
    for (int i = 0; i < 200; i++) {
        double x = (i+0.5)*dx;
        double sum = 0.0;
        for (int n = 1; n < N_TERMS; n++) {
            // 每次迴圈都要重新計算當前的 Bn
            double An = ((2.0 * pow(-1.0, n)) / (n*Pi));

            // 計算級數的當前項 (term)
            double term = An * sin((n * Pi * x) / L) * exp(-( n * n * Pi * Pi * D * t) / (L * L));
            
            // 累加到 sum
            sum += term;
        }
        double C_xt = (x/L)+sum;
        Fourier[i] = C_xt;
    }

    FILE *pFile;
    pFile = fopen("FourierSolution.txt", "w");
    for (int i = 0; i < 200; i++) {
        double x = (i+0.5)*dx;
        fprintf(pFile, "%g\t%g\n", x, Fourier[i]);
    }
    fclose(pFile);

    return 0;
}
