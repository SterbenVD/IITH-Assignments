#include <stdio.h>
#include <stdlib.h>
#include "./func.h"

int main()
{
    double gamma;
    double j;
    char buffer[50];
    ber_gen2D("./ber2d.dat", 1000000);
    gau_genDim("./gau2d.dat", 1, 1000000, 2);
    for (int i = 0; i <= 10; i++)
    {
        gamma = pow(10, (double)i / 10.0);
        double a = sqrt(gamma/2);
        double g1 = gauss_gen(a, 1);
        double g2 = gauss_gen(a, 2);
        double A = sqrt(g1 * g1 + g2 * g2);
        sprintf(buffer, "./twod_data/%d.dat", i);
        twodim_gen(buffer, 1000000, A);
    }
    return 0;
}