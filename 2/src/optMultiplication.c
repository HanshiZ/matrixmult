/*
 Hanshi Z and Jacob Z
*/

#include "optMultiplication.h"
#define NVEC 16
#define DUMMY 0
#if DUMMY

/* Test dereference with * vs [] */
void optMultiplication(double* output, double* input_matrix, double* input_vector,int N,int M,int B)
{
        B = M;
        for(int i = 0; i < N; ++i)
            for(int j = 0; j < B; ++j)
                for(int k = 0; k < NVEC ; ++k)
                    *(output + i*NVEC + k) += *(input_matrix + i*M + j) * *(input_vector+j*NVEC+k);
}
#else
/*
  Divide the columns into B blocks and then do the computations to avoid
  cache misses
*/
void optMultiplication(double* output, double* input_matrix, double* input_vector,int N,int M,int B)
{
    /* I believe this is the wanted implementation */
    for(int h = 0; h < M; h += B)
        for(int i = 0; i < N; ++i)
            for(int j = h, end = ((h + B) < M)? h + B : M; j < end; ++j)
                for(int k = 0; k < NVEC ; ++k)
                   *(output + i*NVEC + k) += *(input_matrix + i*M + j)* *(input_vector+j*NVEC+k);
}
#endif
