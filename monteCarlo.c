#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    srand (time(NULL)); //set seed for random number generator
    int nthreads, tid;
    int pointsAmount;

    //Create the base square (2r)
    int squareSide = 10;
    int squareArea = squareSide*squareSide;
    printf("Square:\n Side: %d. Area: %d\n",squareSide,squareArea);

    //Create the circle (r)
    //area for a circle = pi*(r*r)
    float sphereRadius = 10/2; //This is r
    float sphereArea = 3.14159 * (sphereRadius*sphereRadius);
    printf("Sphere:\n Radius: %f. Area %0.4f\n",sphereRadius,sphereArea);

    //Fork a team of threads giving then their own copies of variables
    #pragma omp parallel private(nthreads, tid)
    {
        //Create a random amount of points
        //where N is the max num of points
        int N=500;
        pointsAmount = rand() % (N+1); 
        printf("Amount of points: %d",pointsAmount);

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

    return 0;
}