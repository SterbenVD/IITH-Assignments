Inputs are taken from "inp-params.txt".

n is the number of threads.
k is the number of times a thread will enter the critical section.
$\lambda_1$ and $\lambda_2$ are average delay values.


input.txt must be of the following format:

n, k, $\lambda_1$, $lambda_2$


Output file "output.txt" contains all requests, entry and exits time for the threads.


To run the individual files

For the tas program:
Compile the program using the command: g++ -o tas Assgn3-Src-tas-CS21BTECH11061.cpp

Run the program using the command: ./tas


For the cas program:
Compile the program using the command: g++ -o cas Assgn3-Src-cas-CS21BTECH11061.cpp

Run the program using the command: ./cas


For the cas-bounded program:
Compile the program using the command: g++ -o casb Assgn3-Src-cas-bounded-CS21BTECH11061.cpp

Run the program using the command: ./cas-bounded


To run all programs and generate output file, run:
```
g++ -o tas Assgn3-Src-tas-CS21BTECH11061.cpp -lpthread
g++ -o cas Assgn3-Src-cas-CS21BTECH11061.cpp -lpthread
g++ -o casb Assgn3-Src-cas-bounded-CS21BTECH11061.cpp -lpthread
g++ -o prog Assgn3-Src-CS21BTECH11061.cpp
```

Run the program using the command: ./prog

Note: ./prog works best when all programs are compiled.


Output for all programs is in their respective text files and is compilated in "output.txt" file.

