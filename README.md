# Monte-Carlo-Project-C
“Multithreaded Monte Carlo technique for calculating PI” in C

Project 
“Multithreaded Monte Carlo technique for calculating PI” 
This project will be reviewed not only by your teacher but also but other reviewers from the Computing, Electronics and Mechatronics Department from UDLAP. This project is mandatory and the following two student learning outcomes will be graded following the rubrics attached with this document.  
SO1 .- An ability to identify, formulate, and solve complex engineering problems by applying principles of engineering, science and mathematics. SO7.- An ability to acquire and apply new knowledge as needed, using appropriate learning strategies. 
 
Deadline:   April 16th, 2020 
Requirements: 
 Individual  English  A PDF document with a maximum of 7 pages. (Arial 10 interlineado 1.5)  To read the three rubrics before you start with your project.  
Problem: 
An interesting way of calculating π is to use a technique known as Monte Carlo, which involves randomization. This technique works as follows:  
Suppose you have a circle inscribed within a square, as shown in the figure below. (Assume that the radius of this circle is 1.) First, generate a series of the Cartesian coordinates that bound the square. Of the total number of random points that are generated, some will occur within the circle. Next, estimate π by performing the following calculation: 
π = 4 X (number of points in the circle) / (total number of points) 
Write a multithreaded version of this algorithm using OpenMP threads to generate a number of random points. Threads will count the number of points that occur within the circle and store that result in a global variable. When each thread has exited, the program will calculate and output the estimated value of π. It is worth experimenting with the number of random points generated. As a general rule, the greater the number of points, the closer the approximation to π.  
 

 
 
Instructions: 
1. Write an OpenMP implementation for calculating π using the Monte Carlo technique.  
2. Make a comparison in performance (time in seconds) setting up different number of threads (1, 2, 3 and 4). Plot a graph of all of them and make a data analysis of it.  
3. To write a PDF document that contains the following sections: 
  a. Information (Student name and student ID, Name of the course, Project´s name) 
  b. Introduction 
  c. Description of the problem 
  d. Methodology 
  e. Results and Data Analysis 
  f. Learning strategies – To describe the learning strategies that you use to learn new tools and knowledge involved in the development of the project. 
  Also, you need to add the following sections: 
  Gap awareness, Growth awareness, Research (introduction and references) and Apply knowledge. Take a look into the SO7 ABET Rubric to cover this section. 
  g. Conclusions 
IMPORTANT: Beware that the report  will be graded by using the rubrics SO1 and SO7 ABET Rubrics attached to this document. 
