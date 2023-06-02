#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
// Function declaration
// double **createMat(int m, int n);
// void readMat(double **p, int m, int n);
// void print(double **p, int m, int n);
// double **loadtxt(char *str, int m, int n);
// double linalg_norm(double **a, int m);
// double **linalg_sub(double **a, double **b, int m, int n);
// double **linalg_inv(double **mat, int m);
// double **matmul(double **a, double **b, int m, int n, int p);
// double **transpose(double **a, int m, int n);
double gen_mean(char *str);
double gen_var(char *str, double mean);
void uni_gen(char *str, int len, int t);
void gau_gen(char *str, int len, int t);
void tri_gen(char *str, int len);
void ber_gen(char *str, int len);
void chi_gen(char *str, int len, int x);
void ray_gen(char *str, int len);
void max_lik_gen(char *str, int len, double a);
// End function declaration

double gen_mean(char *str)
{
    FILE *fp = fopen(str, "r");
    double sum = 0, num = 0;
    int total_num = 0;
    while (fscanf(fp, "%lf", &num) != -1)
    {
        sum += num;
        total_num++;
        if (feof(fp))
        {
            break;
        };
    }
    fclose(fp);
    double mean = sum / total_num;
    return mean;
}

double gen_var(char *str, double mean)
{
    FILE *fp = fopen("./uni.dat", "r");
    double sum = 0, num = 0;
    int total_num = 0;
    while (fscanf(fp, "%lf", &num) != -1)
    {
        sum += pow((num - mean), 2.0);
        total_num++;
        if (feof(fp))
        {
            break;
        };
    }
    fclose(fp);
    double var = sum / total_num;
    return var;
}

void uni_gen(char *str, int len, int t)
{
    FILE *fp = fopen(str, "w");
    srand(t);
    for (int i = 0; i < len; i++)
    {
        double U = ((double)rand()) / RAND_MAX;
        fprintf(fp, "%lf\n", U);
    }
    fclose(fp);
}

void gau_gen(char *str, int len, int t)
{
    FILE *fp = fopen(str, "w");
    srand(t);
    for (int i = 0; i < len; i++)
    {
        double x = 0, U = 0;
        uni_gen("./tempuni.dat", 12, t * i);
        FILE *fpU = fopen("./tempuni.dat", "r");
        for (int j = 0; j < 12; j++)
        {
            fscanf(fpU, "%lf", &U);
            x += U;
        }
        fclose(fpU);
        remove("./tempuni.dat");
        fprintf(fp, "%lf\n", x - 6.0);
    }
    fclose(fp);
}

void tri_gen(char *str, int len)
{
    FILE *fp = fopen(str, "w");
    for (int i = 0; i < len; i++)
    {
        srand(i);
        double x = 0;
        for (int j = 0; j < 2; j++)
        {
            double U = ((double)rand()) / RAND_MAX;
            x += U;
        }
        fprintf(fp, "%lf\n", x);
    }
    fclose(fp);
}

void ber_gen(char *str, int len)
{
    FILE *fp = fopen(str, "w");
    for (int i = 0; i < len; i++)
    {
        double temp = 0;
        double random = (double)rand() / (double)RAND_MAX;
        if (random < 0.5)
            temp = -1;
        else
            temp = 1;
        fprintf(fp, "%lf\n", temp);
    }
    fclose(fp);
}

void max_lik_gen(char *str, int len, double a)
{
    FILE *fpN = fopen("gau.dat", "r");
    FILE *fpB = fopen("ber.dat", "r");
    FILE *fp = fopen(str, "w");
    for (int i = 0; i < len; i++)
    {
        double N = 0, B = 0;
        fscanf(fpN, "%lf", &N);
        fscanf(fpB, "%lf", &B);
        double x = a * B + N;
        fprintf(fp, "%lf\n", x);
    }
    fclose(fp);
}

double est_err(int len, int X)
{
    FILE *fpB = fopen("./ber.dat", "r");
    FILE *fp = fopen("./max_lik.dat", "r");
    int cases = 0, total = 0;
    for (int i = 0; i < len; i++)
    {
        double B = 0, Y = 0;
        fscanf(fp, "%lf", &Y);
        fscanf(fpB, "%lf", &B);
        if (X == -1 && B == -1.0)
        {
            total++;
            if (Y > 0.0)
                cases++;
        }
        else if (X == 1 && B == 1.0)
        {
            total++;
            if (Y < 0.0)
                cases++;
        }
    }
    double ans = (double)cases / (double)total;
    fclose(fp);
    fclose(fpB);
    return ans;
}

double gauss_gen(double var, double t)
{
    double x = 0;
    srand(t);
    for (int j = 0; j < 12; j++)
    {
        x += (double)rand() / RAND_MAX;
    }
    x -= 6;
    return x * var;
}

void chi_gen(char *str, int len, int x)
{
    FILE *fp = fopen(str, "w");
    for (int i = 0; i < len; i++)
    {
        double v = 0;
        for (int j = 0; j < x; j++)
        {
            v += pow(gauss_gen(1, (double)i + (double)j), 2.0);
        }
        fprintf(fp, "%lf\n", v);
    }
    fclose(fp);
}

void ray_gen(char *str, int len)
{
    FILE *fp = fopen(str, "w");
    FILE *fpc = fopen("./chi.dat", "r");
    double v = 0, a;
    for (int i = 0; i < len; i++)
    {
        fscanf(fpc, "%lf", &v);
        a = sqrt(v);
        fprintf(fp, "%lf\n", a);
    }
    fclose(fp);
}

void rayleigh_gen(char *str, int len)
{
    FILE *fpU = fopen("uni.dat", "r");
    FILE *fp = fopen(str, "w");
    double x, y = 0;
    for (int i = 0; i < len; i++)
    {
        fscanf(fpU, "%lf", &x);
        y = -2 * log(1 - x);
        fprintf(fp, "%lf\n", y);
    }

    fclose(fp);
    fclose(fpU);
}

void cond_prob_gen(char *str, int len)
{
    FILE *fpN = fopen("gau.dat", "r");
    FILE *fpB = fopen("ber.dat", "r");
    FILE *fpR = fopen("rayleigh.dat", "r");
    FILE *fp = fopen(str, "w");
    for (int i = 0; i < len; i++)
    {
        double N = 0, B = 0, R = 0;
        fscanf(fpN, "%lf", &N);
        fscanf(fpB, "%lf", &B);
        fscanf(fpR, "%lf", &R);
        double x = R * B + N;
        fprintf(fp, "%lf\n", x);
    }
    fclose(fp);
    fclose(fpN);
    fclose(fpB);
    fclose(fpR);
}

void cond_prob(char *str, double gamma, int len)
{
    FILE *fp = fopen(str, "w");
    FILE *fpB = fopen("./ber.dat", "r");
    double ber = 0;
    for (int i = 0; i < len; i++)
    {
        fscanf(fpB, "%lf", &ber);
        double a = sqrt(gamma / 2);
        double g1 = gauss_gen(a, 1);
        double g2 = gauss_gen(a, 2);
        double y = ber * sqrt(g1 * g1 + g2 * g2) + gauss_gen(1, 1);
        fprintf(fp, "%lf\n", y);
    }
    fclose(fp);
    fclose(fpB);
}

void ber_gen2D(char *str, int len)
{
    FILE *fp = fopen(str, "w");
    for (int i = 0; i < len; i++)
    {
        double random = (double)rand() / (double)RAND_MAX;
        if (random < 0.5)
            fprintf(fp, "%lf %lf\n", 1.0, -1.0);
        else
            fprintf(fp, "%lf %lf\n", -1.0, 1.0);
    }
    fclose(fp);
}
double gaussr_gen(double var)
{
    double x = 0;
    for (int j = 0; j < 12; j++)
    {
        x += (double)rand() / RAND_MAX;
    }
    x -= 6;
    return x * var;
}

void gau_genDim(char *str, double sig, int len, int dim)
{
    double temp;
    FILE *fp = fopen(str, "w");
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            fprintf(fp, "%lf", gaussr_gen(sig));
            if (j != dim - 1)
                fprintf(fp, " ");
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void twodim_gen(char *str, int len, double A)
{
    FILE *fpN = fopen("./gau2d.dat", "r");
    FILE *fpB = fopen("./ber2d.dat", "r");
    FILE *fp = fopen(str, "w");
    double N, B, Y;
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            fscanf(fpN, "%lf", &N);
            fscanf(fpB, "%lf", &B);
            Y = A * B + N;
            fprintf(fp, "%lf", Y);
            if (j != 1)
                fprintf(fp, " ");
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    fclose(fpB);
    fclose(fpN);
}