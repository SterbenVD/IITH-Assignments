#include <stdio.h>
#include <stdlib.h>
#include "./func.h"

int main()
{
    double gamma;
    double j;
    char buffer[50];
    for (int i = 0; i <= 20; i++)
    {
        j = (double)i;
        gamma = pow(10, j / 10.0);
        sprintf(buffer, "./ral_data/%d.dat", i);
        cond_prob(buffer, gamma, 1000000);
    }
    return 0;
}