#include "funciones.h"

double predict(double coef[], double x[], int n) {
    double y = coef[0];  

    for (int i = 0; i < n; i++) {
        y += coef[i + 1] * x[i];
    }

    return y;
}
