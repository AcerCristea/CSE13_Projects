ASSIGNMENT 3: PUTTING YOUR AFFAIRS IN ORDER
=====================================

Preparation to Run Code
-------------------------
Before running this code, you must make sure that you have all of the deliverables list at the bottom of this document. This way, you can successfully compile the code prior to running it. To compile, simply type `make` into the terminal.

Running Code
-------------
Make sure you have sorting.c compiled. This will act as your testcase file:

`-a // this employs all sorting algorithms.`

`-h // this enables Heap Sort.`

`-b // this enables the Batcher Sort.`

`-s // this enables the Shell Sort.`

`-q // this enables the Quicksort.`
 
`-r // seed`

`-n // size`

`-p // elements`

`-H // prints out program usage`

To use the following options correctly, type the following into the terminal:
`./sorting __` On the underline, type the options you want to use. For seed and size, you will need to input a value after calling the letter like so `./sorting -a -r 10 -n 15`. This will run every sorting function which will sort 15 elements in a list that was generated using the random number generator with the seed of 10.


Deliverables
--------------
The following is the list of deliverables pertaining this assignment:
   * batcher.c, batcher.h
   * heap.c, heap.h
   * shell.c, shell.h
   * quick.c, quick.h
   * set.c, set.h
   * stats.c, stats.h
   * sorting.c
   * Makefile
   * README.md
   * DESIGN.pdf
   * WRITEUP.pdf
