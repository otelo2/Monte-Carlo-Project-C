#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

//TODO: See if we really need the areas, i dont think so.

//Declare global variables for our shapes properties
int squareSide, squareArea;
int sphereRadius; 
float sphereArea;

//"Threads will count the number of points that occur within the circle and store that result in a global variable"
int pointsAmount;

void create_points()
{
    srand (time(NULL)); //set seed for random number generator
    int pointsAmount, interval;
    int angle, position; //Properties of the point
    float angleRadians;
    float maxLenght;
    int intMaxLen;
    int insideCircle=0,outsideCircle=0; //Counter of points inside and out the circle.
    interval = 500; //I can set this manually so I can play around with the ammount of points.
    pointsAmount = rand() % (interval+1);
    for(int i=0; i<pointsAmount; i++)
    {
        //this will only work if a random number is generated each cycle, lets pray.

        //Random number from 0 to 360, thus this is the angle from the center of the circle.
        angle = rand() % (360+1);

        //Convert the angle to radians for use in trigonometric functions
        //soucre: https://www.dummies.com/programming/c/trigonometry-for-c-programming/
        angleRadians= 0.0174532925*angle;

        //Obtain the max possible lenght given the angle
        maxLenght = ((cos(angleRadians))*sphereRadius);

        //round the maxLenght to use as an integer for the rand()
        int intMaxLen = roundf(maxLenght);

        //Set the position of the number to [-intMaxLen, intMaxLen]
        position = (rand() % (intMaxLen - (-intMaxLen) + 1)) + intMaxLen;

        //Check if the point generated is inside or outside the circle.
        if((position>=(-sphereRadius)) && (position<=sphereRadius))
            insideCircle++;
        else
            outsideCircle++;
    }

    //Print the final number of points
    printf("For %d points:\n \t%d are inside the circle\n \t%d are outside the circle",pointsAmount,insideCircle,outsideCircle);
}

int main(int argc, char *argv[])
{
    srand (time(NULL)); //set seed for random number generator
    int nthreads, tid;

    //Give values to the base square (2r)
    squareSide = 10;
    squareArea = squareSide*squareSide;
    printf("Square:\n Side: %d. Area: %d\n",squareSide,squareArea);

    //Give values to the circle (r)
    //area for a circle = pi*(r*r)
    sphereRadius = squareSide/2; //This is r
    sphereArea = 3.14159 * (sphereRadius*sphereRadius);
    printf("Sphere:\n Radius: %d. Area %0.4f\n",sphereRadius,sphereArea);

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