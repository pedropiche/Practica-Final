#include <stdio.h>
#include "funciones.h"

int main() {
    
    double coef[] = {1.5, -2.0, 3.5, 0.5};

    
    double x[] = {2.0, -1.0, 4.0};

    double y_pred = predict(coef, x, 3);

    printf("Predicción con nuevos datos:\n");
    printf("ŷ = %.1f + (%.1f)(%.1f) + (%.1f)(%.1f) + (%.1f)(%.1f) = %.1f\n",
           coef[0], coef[1], x[0], coef[2], x[1], coef[3], x[2], y_pred);

    return 0;
}

