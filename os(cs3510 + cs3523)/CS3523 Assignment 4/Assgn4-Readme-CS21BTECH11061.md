Inputs are taken from "inp-params.txt".

P is the number of passenger threads.
C is the number of car threads.
$\lambda_1$ and $\lambda_2$ are average delay values.
k is the number of critical sections a thread must run.

input.txt must be of the following format:

P C $\lambda_P$ $\lambda_C$ k


Output file "output.txt" contains all requests, entry and exits time for the threads.

To run the program and generate output file, run: g++ -o prog Assgn3-Src-CS21BTECH11061.cpp -lpthread

Run the program using the command: ./prog


