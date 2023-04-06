ASSIGNMENT 5: PUBLIC KEY CRYPTOGRAPGY
========================================

Preparation Before Running
----------------------------------
To run this code and compile it properly you must start by cleaning the files. Run the following code in your terminal: `make clean`. 

To compile all of the files (keygen, decrypt, and encrypt), you can run the following code: `make all`

To compile just the keygen, you can run the following code: `make keygen`

To compile just the decrypt, you can run the following code: `make decrypt`

To compile just the encrypt, you can run the following code: `make encrypt`

Make sure that after you write any of the following in the terminal, you clear using the `make clean` mentioned at the top of this section.

Running the Code
------------------
There are three executable files in this assignment: `keygen.c` `encrypt.c` `decrypt.c`. Each of these files have their own options that can be inputted by the user.

keygen.c -
This file has the following options listed:

	-b bits     // bits for the public modulus
	-i iters    // amount of Miller-Rabin iterations
	-n pb name  // specifies the public key file
	-d pv name  // specifies the private key file
	-s seed     // specifies the random seed for the random state
	-v          // enables verbose output
	-h          // displays program synopsis
   
encrypt.c -
These files have the same options, but the only underlying difference is the default file at which their key information is stored.

	-i infile   // specifies the input file to encrypt
	-o outfile  // specifies the output file to send your encrypted message
	-n keyfile  // specifies the file containing the public/private key
	-v          // enables the verbose output
	-h          // displays program synopsis and usage


decrypt.c -
These files have the same options, but the only underlying difference is the default file at which their key information is stored.

	-i infile   // specifies the input file to decrypt (the file you sent the decrypted 
	-o outfile  // specifies the output file send the decrypted message
	-n keyfile  // specifies the file containing the public/private key
	-v          // enables the verbose output
	-h          // displays program synopsis and usage

You can run this code using the following options above. For the keygen executable, "b" "i" "n" "d", and "s" can be changed by user input. To see how to do this, run `./keygen -h` to see how to use the program. For both encrypt and decrypt, "i", "o", and "n" can be altered as well by following the instructions when running `./encrypt -h` or `./decrypt - h`.

If you would like to create a specific public key and private key pair for encrypting and decrypting, that must be done in keygen using -n and -d. You then need to use that specific public key in encrypting and that specific private key in decrypting for it to work.

For example `./keygen -n pb.txt -d pv.txt`, then `./encrypt -i (filename with your message) -o (file where you want your encrypted message) -n pb.txt`, then `./decrypt -i output.txt -n pv.txt`. 

Deliverables
--------------
The following are the deliverables associated with this assignment:

   * decrypt.c: contains implementation for decrypt program
   * encrypt.c: contains implementation for encrypt program
   * keygen.c: contains implementation for keygen program
   * numtheory.c: contains the implementation for number theory functions
   * numtheory.h: specifies the interface for the number theory functions
   * randstate.c: contains the implementation of the random state interface for the ss library and number theory functions
   * ss.c: contains the implementation of the ss library
   * ss.h: specifies the interface for the ss library
   * Makefile
   * DESIGN.pdf

