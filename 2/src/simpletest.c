#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "naiveMultiplication.h"
#include "optMultiplication.h"
#define TOL .00001


void asserteq(double * matrix, double * test, int size);
void fill(double * matrix, int size);
double uniform(double a , double b);


/* Pass sizes through command line */
int main(int argc, char * args[])
{
   if(argc < 3)
   {
      printf("Please specifiy matrix dimensions");
      return 0;
   }
   int n = atoi(*(args+1));
   int m = atoi(*(args+2));
   int b = *(args+3) ? atoi(*(args+3)) : 10;
   int k = 16;

   double* prod1 = (double*)calloc(n*k, sizeof(double));
   double* prod2 = (double*)calloc(n*k, sizeof(double));
   double * m1 = (double*)malloc(n * m * sizeof(double));
   double * m2 = (double*)malloc(m * k * sizeof(double));

   double * t1 = (double*)malloc(n * m * sizeof(double));
   double * t2 = (double*)malloc(m * k * sizeof(double));

   fill(m1, n * m), fill(m2, m*k);
   memcpy(t1, m1, sizeof(double) * n *m), memcpy(t2,m2, sizeof(double)*m*k);
   
   naiveMultiplication(prod2, m1, m2 ,n,m);
   optMultiplication(prod1, t1, t2 , n ,m, k);

   asserteq(prod1,prod2,n*k);
   return 0;
}

void asserteq(double * matrix, double * test, int size)
{
    for(int i = 0; i < size ;++i)
    {
       if (!(fabs(*(test+i) - *(matrix+i)) < TOL))
          printf("%.3f != %.3f item: %d\n",*(test+i),*(matrix+i),size);
       assert( fabs(*(test+i) - *(matrix+i)) < TOL);
    }
    printf("Assert complete!!!\n");
}

void fill(double * matrix, int size)
{
   for(double * end = matrix + size; matrix < end ; ++matrix)
      *matrix = uniform(0, 10000);
}

double uniform(double a , double b)
{
    return (1.0 * rand() / RAND_MAX) * (b - a) + a;
}
