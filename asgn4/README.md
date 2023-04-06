ASSIGNMENT 4: GAME OF LIFE
=====================================

Preparation to Run Code
-------------------------
Before running this code, you must make sure that you have all of the deliverables list at the bottom of this document and the folder "lists" found in the Resources git (you can also use your own text files). This way, you can successfully compile the code prior to running it. To compile, simply type `make` into the terminal.

Running Code
-------------
Make sure you have life.c compiled. This will act as your testcase file:

`-t // Specify that the Game of Life is to be played on a toroidal universe.`

`-s // Silence ncurses. Enabling the option means that nothing should be displayed by ncurses.`

`-n // Specify the number of generations that the universe goes through. The default is 100.`

`-i // Specify the input file to read in order to populate the universe. By default the input should be stdin.`

`-o // Specify the output file to print the final state of the universe to. By default the output should be stdout.`

To use the following options correctly, type the following into the terminal:
`./life __` On the underline, type the options you want to use. For n you fill need to input a value like so `./life -n 150`. For i, and o, you will need to input a file name after calling the letter like so `./life -t -i lists/test.txt`. For some reason I had put the name of the folder before my file, otherwise I got a seg fault. This might not be the case for you, in which you can remove "lists/".

Deliverables
--------------
The following is the list of deliverables pertaining this assignment:
   * universe.c, universe.h
   * life.c
   * Makefile
   * README.md
   * DESIGN.pdf
   * WRITEUP.pdf
