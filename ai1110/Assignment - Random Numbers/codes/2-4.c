#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
    FILE *fp1 = fopen("./gau.dat","r");
    double sum = 0,num=0,var=0;
    int total_num=0;
    while(fscanf(fp1,"%lf",&num)!=-1){
        sum+=num;
        total_num++;
        if(feof(fp1)){break;};
    }
    fclose(fp1);
    double mean = sum/total_num;
    FILE *fp2 = fopen("./gau.dat","r");
    while(fscanf(fp2,"%lf",&num)!=-1){
        var+= pow((num - mean),2.0)/total_num;
        if(feof(fp2)){break;};
    }
    printf("Mean: %lf\nVariance: %lf\n",mean,var);
    fclose(fp2);
    return 0;
}
