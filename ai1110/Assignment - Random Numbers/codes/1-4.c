#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./func.h"
int main(){
    double mean = gen_mean("uni.dat");
    double var = gen_var("uni.dat",mean);
    printf("Mean: %lf\nVariance: %lf\n",mean,var);
    return 0;
}