ASSIGNMENT 6: Lempel-Ziv Compression
=================================================================

Preparation to Run
------------------
To ensure a successful run, it is crucial to clean and compile the necessary files beforehand. Failure in doing so will result in error messages stating that there are no such files in the directory. 

Running the Code
-------------------
To run the program, is simple and similar to how we have been executing the past programs using getopt() along with switch cases. For this assignment in particular, there will be two executables to run: `encode.c` and `decode.c`. Each of which have these as their options:

   * `-h // prints out a help message describing the purpose of the program and the command-line options it accepts, exiting the program afterwards.`
   * `-i infile // specifies the input file to encode/decode using Huffman coding (default: stdin)`
   * `-o outfile // specifies the output file to write the compressed input to (default: stdout)`
   * `-v // prints compression statistics to stderr`
   
Using the options listed above, we can run the following code `./encode [options]` for encode.c and `./decode [options]` for decode.c. To find more detailed instructions on how to use getopt(), look to run the `-h` option by simply writing `./encode -h` or `decode -h`, both of which will correspond to their respective statements. If a file is incorrectly spelt, or not put in at all, a helpful error messgage will show.

Ultimately, we want to print out the compression statistics of the Huffman Tree compression method. This can be found using the `-v` option given above.

Deliverables
----------------------
The following are the deliverables for this assignment:
   * encode.c (implementation of the LZ78 encoder)
   * decode.c (implementation of the LZ78 decoder)
   * trie.c (the source file for the Trie ADT)
   * trie.h (the header file for the Trie ADT)
   * word.c (the source file for the Word ADT)
   * word.h (the header file for the Word ADT)
   * io.c (implementation of I/O module)
   * io.h (I/O module interface)
   * endian.h (header file for the endianness module)
   * code.h (header file containing macros for reserved codes)
   * Makefile
   * README.md
   * DESIGN.pdf

