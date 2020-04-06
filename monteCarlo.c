#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

//TODO: See if we really need the areas, i dont think so.

//Declare global variables for our shapes properties
int squareSide, squareArea;
int circleRadius; 
float circleArea;

//"Threads will count the number of points that occur within the circle and store that result in a global variable"
int pointsAmount;

//So its easier to pass the values to the calculate_pi function and return them from the create_points.
struct Points
    {
        int insideCircle, outsideCircle; 
    };

struct Points create_points()
{
    srand (time(NULL)); //set seed for random number generator
    int interval;
    int angle, position; //Properties of the point
    float angleRadians;
    float maxLenght;
    int intMaxLen;
    struct Points points = {0,0}; //initialize counter values as 0 
    

    //Set the amount of points
    interval = 50; //I can set this manually so I can play around with the ammount of points.
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
        maxLenght = ((cos(angleRadians))*circleRadius);

        //round the maxLenght to use as an integer for the rand()
        int intMaxLen = roundf(maxLenght);

        //Set the position of the number to [-intMaxLen, intMaxLen]
        position = (rand() % (intMaxLen - (-intMaxLen) + 1)) + intMaxLen;

        //Check if the point generated is inside or outside the circle.
        if((position>=(-circleRadius)) && (position<=circleRadius))
            points.insideCircle++;
        else
            points.outsideCircle++;
    }

    //Print the final number of points
    printf("For %d points:\n \t%d are inside the circle\n \t%d are outside the circle", pointsAmount, points.insideCircle, points.outsideCircle);

    return points;
}


//Takes the amount of points inside and outside the circle and runs the formula to aproximate pi.
int calculate_pi(struct Points points)
{
    //Formula given by text:
    // π = 4 X (number of points in the circle) / (total number of points) 
    float pi;

    pi = 4 * (points.insideCircle) / (points.outsideCircle);

    return pi;
}

int main(int argc, char *argv[])
{
    srand (time(NULL)); //set seed for random number generator
    int nthreads, tid;
    float pi;

    //Give values to the base square (2r)
    squareSide = 10;
    squareArea = squareSide*squareSide;
    printf("Square:\n Side: %d. Area: %d\n",squareSide,squareArea);

    //Give values to the circle (r)
    //area for a circle = pi*(r*r)
    circleRadius = squareSide/2; //This is r
    circleArea = 3.14159 * (circleRadius*circleRadius);
    printf("Sphere:\n Radius: %d. Area %0.4f\n",circleRadius,circleArea);

    //Fork a team of threads giving then their own copies of variables
    #pragma omp parallel private(nthreads, tid)
    {
        //Create a random amount of points and if they are inside or outside the circle
        //then
        //Calculate pi using Monte Carlo formula
        pi = calculate_pi(create_points());

        //Print the result.
        printf("PI aproximation: %f",pi);

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