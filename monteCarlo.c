#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

//Best source: https://www.youtube.com/watch?v=PLURfYr-rdU

//Declare global variables for our shapes properties
int squareSide, squareArea;
int circleRadius; 
float circleArea;

//"Threads will count the number of points that occur within the circle and store that result in a global variable"
int pointsAmount=-999;

float float_rand(float min, float max);

//So its easier to pass the values to the calculate_pi function and return them from the create_points.
struct Points
    {
        int insideCircle, outsideCircle; 
    };

struct Points create_points(int userInterval, int pointsAm)
{
    srand((time(NULL)) ^ omp_get_thread_num()); //source: https://www.viva64.com/en/b/0012/
    int interval;
    float posX;
    float posY;

    struct Points points = {0,0}; //initialize counter values as 0 
    
    //Chech if pointsAmount is different from default value, if it is then use that fixed value.
    if(pointsAm!=-999)
        pointsAmount=pointsAm;
    else
    {
        //Set the amount of points
        interval = userInterval;
        pointsAmount = rand() % (interval)+1;
    }
    
     //MAX INT VALUE
    //pointsAmount=2147483647; 

    for(int i=0; i<pointsAmount; i++)
    {
        //assign a random float value from [0,1]
        posX = float_rand(0,1);
        posY = float_rand(0,1);

        //Print the coordinates of each point (commented out in final code for performance reasons)
        //printf("\n(%f) , (%f)\n",posX,posY);

        //Check if the point generated is inside or outside the circle.
        if(((posX*posX) + (posY*posY)) < 1)
            points.insideCircle++;
        else
            points.outsideCircle++;
    }

    //Print the final number of points
    printf("For %d points:\n \t%d are inside the circle\n \t%d are outside the circle\n", pointsAmount, points.insideCircle, points.outsideCircle);

    return points;
}

//Generate random float from range https://stackoverflow.com/questions/13408990/how-to-generate-random-float-number-in-c
float float_rand( float min, float max )
{
    float scale = rand() / (float) RAND_MAX; /* [0, 1.0] */
    return min + scale * ( max - min );      /* [min, max] */
}

//Takes the amount of points inside and outside the circle and runs the formula to aproximate pi.
float calculate_pi(struct Points points)
{
    //Formula given by text:
    // π = 4 X (number of points in the circle) / (total number of points) 
    float pi;
    float dividend;

    //Convert int points to float to use correctly for division.
    dividend = (float)points.insideCircle / (points.insideCircle + points.outsideCircle);

    //do the formula
    pi = 4 * dividend;
    return pi;
}

int main(int argc, char *argv[])
{
    srand (time(NULL)); //set seed for random number generator
    int nthreads, tid, userInterval=1, selection;
    float pi;

    //ask user for specific value or random value inside interval
    printf("\n1. Give interval from which a random amount of points will be selected\n2. Input an specific amount of points\n");
    scanf("%d",&selection);

    //Check selection and do corresponding action
    if(selection==1)
    {
        //user sets the amount of points to test
        printf("\n Type the max amount of points to use \n");
        scanf("%d",&userInterval);
    }
    else
    {
        printf("\n Input the amount of points to use \n");
        scanf("%d",&pointsAmount);
    }
    

    //Give values to the base square (2r)
    squareSide = 2;
    squareArea = squareSide*squareSide;
    printf("\nSquare:\n Side: %d. Area: %d\n",squareSide,squareArea);

    //Give values to the circle (r)
    //area for a circle = pi*(r*r)
    circleRadius = squareSide/2; //This is r
    circleArea = 3.14159 * (circleRadius*circleRadius);
    printf("Sphere:\n Radius: %d. Area %0.4f\n",circleRadius,circleArea);
    printf("-----------------------\n\n");

    //Fork a team of threads giving then their own copies of variables
    #pragma omp parallel private(nthreads, tid)
    {
        //obtain thread number
        tid= omp_get_thread_num();
        printf("\t\t\tThis is thread %d\n",tid);

        //Create a random amount of points and if they are inside or outside the circle
        //then
        //Calculate pi using Monte Carlo formula
        pi = calculate_pi(create_points(userInterval,pointsAmount));

        //Print the result.
        printf("PI aproximation: %0.5f\n\n",pi);

    } //All threads join master thread and disband

    return 0;
}