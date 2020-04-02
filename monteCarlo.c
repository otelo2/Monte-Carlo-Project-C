#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    int nthreads, tid;

    //Fork a team of threads giving then their own copies of variables
    #pragma omp parallel private(nthreads, tid)
    {

        //obtain thread number
        tid= omp_get_thread_num();
        printf("This is thread %d\n",tid);
        
        //only master thread does this
        if(tid==0)
        {
            nthreads = omp_get_num_threads();
            printf("Number of threads= %d\n", nthreads);
        }

    } //All threads join master thread and disband
}