ASSIGNMENT 1: Getting Acquainted with UNIX and C
================================================


Preperation to Run Code
-----------------------
The first step to making this bash script run is to download plot.sh. This will be our bash script that we run in order to redirect data and plot our graphs. We'll also need to download monte_carlo.c, which is a C program that generates our data for the Monte Carlo Estimation. We need Makefile in our folder to be able to run the files named above. If in case these files need permission granted to access them, use:
	`$ chmod +x <filename>`

DO NOT FORGET to Install gnuplot. Without this we are not able to plot data in graphs and give a visual representation of our data. To install in Linux use:
	`$ sudo apt install gnuplot`
	
Note that the data within the script will reset everytime the VM you are using is restarted.

Running the Shell Script
------------------------
As said before, the main code is in the bash script plot.sh

You need to make sure you compile monte_carlo.c by using one of the three options:
	`$make monte_carlo`
	`$make`
	`$make all`

You're ready to run the program. Enter:
	`$.\plot.sh
Be sure to be in the correct directory for this to work

Wait a few seconds and you should see your brand new plots in pdf format inside your folder
	


