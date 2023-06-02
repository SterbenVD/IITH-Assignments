#include <stdio.h>
#include <stdlib.h>
#include "./func.h"

int main()
{
    double Pe0 = est_err(1000000, 1);
    double Pe1 = est_err(1000000, -1);
    printf("Pe0 : %lf \nPe1 : %lf", Pe0, Pe1);
    return 0;
}