#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

//TODO: See if we really need the areas, i dont think so.

//Declare global variables for our shapes properties
int squareSide, squareArea;
float sphereRadius, sphereArea;

void create_points()
{
    srand (time(NULL)); //set seed for random number generator
    int pointsAmount, interval;
    int angle,position; //Properties of the point
    int insideCircle=0,outsideCircle=0; //Counter of points inside and out the circle.
    interval = 500;
    pointsAmount = rand() % (interval+1);
    for(int i=0; i<pointsAmount; i++)
    {
        //this will only work if a random number is generated each cycle, lets pray.

    }
}

int main(int argc, char *argv[])
{
    srand (time(NULL)); //set seed for random number generator
    int nthreads, tid;
    int pointsAmount;

    //Give values to the base square (2r)
    squareSide = 10;
    squareArea = squareSide*squareSide;
    printf("Square:\n Side: %d. Area: %d\n",squareSide,squareArea);

    //Give values to the circle (r)
    //area for a circle = pi*(r*r)
    sphereRadius = squareSide/2; //This is r
    sphereArea = 3.14159 * (sphereRadius*sphereRadius);
    printf("Sphere:\n Radius: %f. Area %0.4f\n",sphereRadius,sphereArea);

    //Fork a team of threads giving then their own copies of variables
    #pragma omp parallel private(nthreads, tid)
    {
        //Create a random amount of points
        //where N is the max num of points
        int N=500;
        pointsAmount = rand() % (N+1); 
        printf("Amount of points: %d\n",pointsAmount);

        //obtain thread number
        tid= omp_get_thread_num();
        printf("\tThis is thread %d\n",tid);
        
        //only master thread does this
        if(tid==0)
        {
            nthreads = omp_get_num_threads();
            printf("Number of threads= %d\n", nthreads);
        }

    } //All threads join master thread and disband

    return 0;
}