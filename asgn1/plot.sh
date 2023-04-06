#!/bin/bash

make clean && make monte_carlo # Rebuild the monte carlo executable .
./monte_carlo > /tmp/mc.dat # Place the data points into a file .

# Need to use a loop in Bash, to get multiple random points, in PI



for (( i=0;i < 1001; i++));do ./monte_carlo -n "$i" > /tmp/mc.dat; done

#reference column 5 if it's a 1 or 0
#get distance from monte carlo
#can get 1 and 0 from monte carlo, 1 is if it's in square and circle, 0 if not
#	if the point (i) distance <= 1; plot in sqaure and circle, make color blue,
#	else make other circles red and outside circle but in square


#n number of points

#get pi column - pi, use that number as y. Need to create new data column to store that number



./monte_carlo -n "116384" -r "1" > /tmp/mc.dat2;  
awk  '{print $2 = $2 - 3.14159}' /tmp/mc.dat2 > /tmp/mc.dat22; 

./monte_carlo -n "16384" -r "50" > /tmp/mc.dat3; 
awk  '{print $2 = $2 - 3.14159}' /tmp/mc.dat3 > /tmp/mc.dat33; 

./monte_carlo -n "16384" -r "500" > /tmp/mc.dat4; 
awk  '{print $2 = $2 - 3.14159}' /tmp/mc.dat4 > /tmp/mc.dat44; 

./monte_carlo -n "16384" -r "1000" > /tmp/mc.dat5; 
awk  '{print $2 = $2 - 3.14159}' /tmp/mc.dat5 > /tmp/mc.dat55; 

./monte_carlo -n "16384" -r "150" > /tmp/mc.dat6;
awk  '{print $2 = $2 - 3.14159}' /tmp/mc.dat6 > /tmp/mc.dat66; 

./monte_carlo -n "16384" -r "125" > /tmp/mc.dat7; 
awk  '{print $2 = $2 - 3.14159}' /tmp/mc.dat7 > /tmp/mc.dat77; 


# This is the here - document that is sent to gnuplot .
gnuplot <<END
set terminal pdf
set output "monte_carlo.pdf"
set title "Monte Carlo"
set xlabel "x"
set ylabel "y"
set zeroaxis
set xtics 0.2 nomirror
set ytics 0.2 nomirror
set tics scale 0
set palette defined (0 "red", 1 "blue")
unset colorbox
set size ratio 1
set object 1 circle front at 0,0 size 1 fillcolor rgb "black" lw 1
plot "/tmp/mc.dat" using 3:4:5 ls 7 ps 0.2 palette title""
END




gnuplot <<END
set terminal pdf
set output "monte_carlo2.pdf"
set title "Monte Carlo Error Estimation"
set xlabel "Iterations"
set ylabel "Error"
set zeroaxis
set logscale x 4
set xtics ("1" 1, "4" 4,"16" 16, "64" 64,"256" 256, "1024" 1024,"4096" 4096, "16304" 16304)
set grid
set xrange [1:30000]

plot "/tmp/mc.dat22" with lines lt rgb "blue" title"", \
"/tmp/mc.dat33" with lines lt rgb "orange" title"", \
"/tmp/mc.dat44" with lines lt rgb "red" title"", \
"/tmp/mc.dat55" with lines lt rgb "green" title"", \
"/tmp/mc.dat66" with lines lt rgb "pink" title"", \
"/tmp/mc.dat77" with lines lt rgb "purple" title""
END








