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

struct Points create_points(int userInterval)
{
    srand((time(NULL)) ^ omp_get_thread_num()); //source: https://www.viva64.com/en/b/0012/
    int interval;
    int angle; 
    //int position; //Properties of the point
    float angleRadians;
    float maxLenght;
    float position;
    int intMaxLen;
    struct Points points = {0,0}; //initialize counter values as 0 
    

    //Set the amount of points
    //interval = 10; //set the interval to a fixed ammunt
    interval = userInterval;
    pointsAmount = rand() % (interval)+1;
    
     //MAX INT VALUE
    pointsAmount=2147483647; 

    for(int i=0; i<pointsAmount; i++)
    {
        //Random number from 0 to 360, thus this is the angle from the center of the circle.
        angle = rand() % (360+1);

        //Convert the angle to radians for use in trigonometric functions
        //soucre: https://www.dummies.com/programming/c/trigonometry-for-c-programming/
        angleRadians= 0.0174532925*normalize_angle(angle);

        //Obtain the max possible lenght given the angle
        maxLenght = (circleRadius/(cos(angleRadians)));

        //round the maxLenght to use as an integer for the rand()
        int intMaxLen = roundf(maxLenght);

        //Set the position of the number to [-intMaxLen, intMaxLen]
        //This only generates an int
        //position = (rand() % (intMaxLen - (-intMaxLen) + 1)) + intMaxLen;
        //printf("\nPosition is %d with angle %d and max len of %f \n",position,angle, maxLenght);

        //Generate position as a float to increase accuracy
        position = ((float)rand()/(float)(RAND_MAX)) * maxLenght;
        //printf("\nPosition is %f with angle %d and max len of %f with circle radius of %d \n",position,angle,maxLenght,circleRadius);

        //Check if the point generated is inside or outside the circle.
        if((position>=(-circleRadius)) && (position<=circleRadius))
            points.insideCircle++;
        else
            points.outsideCircle++;
    }

    //Print the final number of points
    printf("For %d points:\n \t%d are inside the circle\n \t%d are outside the circle\n", pointsAmount, points.insideCircle, points.outsideCircle);

    return points;
}

//The function to get the max length will only work with angles from [0,45] so we need to find the equivalent angle in that range for any given angle >45 and <=360
int normalize_angle(int angle)
{
    int newAngle=999;
    if(angle>0 && angle<=45)
        return angle;
    else if (angle>45 && angle<=90)
    {
        newAngle=(angle - (45*2))*(-1);
        return newAngle;
    }
    else if (angle>90 && angle<=135)
    {
        newAngle=(angle - (45*2));
        return newAngle;
    }
    else if (angle>135 && angle<=180)
    {
        newAngle=(angle - (45*4))*(-1);
        return newAngle;
    }
    else if (angle>180 && angle<=225)
    {
        newAngle=(angle - (45*4));
        return newAngle;
    }
    else if (angle>225 && angle<=270)
    {
        newAngle=(angle - (45*6))*(-1);
        return newAngle;
    }
    else if (angle>270 && angle<=315)
    {
        newAngle=(angle - (45*6));
        return newAngle;
    }
    else if (angle>315 && angle<=360)
    {
        newAngle=(angle - (45*8))*(-1);
        return newAngle;
    }
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
    int nthreads, tid, userInterval;
    float pi;

    //user sets the amount of points to test
    printf("\n Type the max amount of points to use \n");
    scanf("%d",&userInterval);

    //Give values to the base square (2r)
    squareSide = 10;
    squareArea = squareSide*squareSide;
    printf("Square:\n Side: %d. Area: %d\n",squareSide,squareArea);

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
        pi = calculate_pi(create_points(userInterval));

        //Print the result.
        printf("PI aproximation: %0.5f\n\n",pi);

    } //All threads join master thread and disband

    return 0;
}