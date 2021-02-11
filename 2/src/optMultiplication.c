#include "optMultiplication.h"
#define NVEC 16
#define FORWARD 1
#if FORWARD 
void optMultiplication(double* output, double* input_matrix, double* input_vector,int N,int M,int B)
{
    /* I believe this is the wanted implementation */
    int Bleng = M/B;
    for(int h = 0; h < M; h+=Bleng)
        for(int i = 0; i < N; ++i)
            for(int j = h, end = h + Bleng; j < M && j < end; ++j)
                for(int k = 0; k < NVEC ; ++k)
                    *(output + i*NVEC + k) += *(input_matrix + i*M + j) * *(input_vector+j*NVEC+k);
}
#else
void optMultiplication(double* output, double* input_matrix, double* input_vector,int N,int M,int B)
{
    /* do backward looping to save a little space
     ? does is make a difference
    */
    int Bleng = M/B;
    for(int h = 0; h < M; h+=Bleng)
        for(--N; N >=0 ; --N)
            for(int j = h, end = h + Bleng; j < M && j < end; ++j)
                for(int k = 0; k < NVEC ; ++k)
                    *(output + N*NVEC + k) += *(input_matrix + N*M + j) * *(input_vector+j*NVEC+k);
}

#endif
