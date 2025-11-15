#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>



#define G 9.81   // gravedad

double yf(double y0, double x, double v, double theta_rad) {
    double t = x / (v * cos(theta_rad));
    return y0 + v*sin(theta_rad)*t - 0.5*G*t*t;
}

int main(int argc, char *argv[]) {
    if (argc != 10) {
        printf("Uso: %s y0 x v0 dv0 theta dtheta N Nbins seed\n", argv[0]);
        return 1;
    }

    double y0      = atof(argv[1]);
    double x       = atof(argv[2]);
    double v0      = atof(argv[3]);
    double dv0     = atof(argv[4]);
    double theta0  = atof(argv[5]) * M_PI / 180.0;      // grados → radianes
    double dtheta  = atof(argv[6]) * M_PI / 180.0;      // grados → radianes
    long N         = atol(argv[7]);
    int Nbins      = atoi(argv[8]);
    long seed      = atol(argv[9]);

    srand48(seed); 

    double *Y = malloc(N * sizeof(double));
    if (!Y) {
        printf("Error de memoria.\n");
        return 1;
    }

    // Generar datos simulados
    for (long i = 0; i < N; i++) {
        double r = drand48();
        double q = drand48();
        double R = sqrt(-2.0 * log(r));
        double v_i     = v0     + dv0     * R * cos(2*M_PI*q);
        double theta_i = theta0 + dtheta  * R * sin(2*M_PI*q);

        Y[i] = yf(y0, x, v_i, theta_i);
    }

    // Calcular media y desviación
    double sum = 0;
    for (long i = 0; i < N; i++) sum += Y[i];
    double mean = sum / N;

    double var = 0;
    for (long i = 0; i < N; i++) var += (Y[i] - mean)*(Y[i] - mean);
    var /= N;
    double std = sqrt(var);

    // Construir histograma
    double min = Y[0], max = Y[0];
    for (long i = 1; i < N; i++) {
        if (Y[i] < min) min = Y[i];
        if (Y[i] > max) max = Y[i];
    }

    double binw = (max - min) / Nbins;
    int *hist = calloc(Nbins, sizeof(int));

    for (long i = 0; i < N; i++) {
        int b = (int)((Y[i] - min) / binw);
        if (b == Nbins) b--; 
        hist[b]++;
    }

    
    printf("\n=== HISTOGRAMA DE y_f ===\n");
    for (int i = 0; i < Nbins; i++) {
        double a = min + i*binw;
        double b = min + (i+1)*binw;
        printf("[%.4f , %.4f): %d\n", a, b, hist[i]);
    }

    printf("\nMedia = %.6f\n", mean);
    printf("Desviacion estandar = %.6f\n", std);

    free(Y);
    free(hist);

    return 0;
}
