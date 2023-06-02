Inputs "N" and "K" are taken from "input.txt" where N is the size of the matrix(sudoku) and k is the threads used.
Then a n x n matrix is taken as input.

input.txt must be of the following format:
k n
a_11 a_12 ... a_1n
a_21 a_22 ... a_2n
..................
a_n1 a_n2 ... a_nn

For the pthreads program:
Compile the program using the command: g++ -o pthr Assgn2SrcpthreadCS21BTECH11061.cpp -lpthread

Run the program using the command: ./pthr

For the openmp program:
Compile the program using the command: g++ -o open Assgn2SrcOpenMpCS21BTECH11061.cpp -fopenmp

Run the program using the command: ./open

Output file contains the the log part: Row/Column/Grid checked by which thread, and whether it is valid or not.
In the end, it concludes whether sudoku is valid or not, and has the time taken to compute the decision.