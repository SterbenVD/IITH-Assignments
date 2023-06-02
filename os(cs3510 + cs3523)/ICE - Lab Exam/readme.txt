Input file should be named "input.txt" and should be in following format:
K M N Alpha Beta Lambda Mu

Where:
K = Number of Families
M = Number of Trays
N = Number of times a family eats ice cream
Alpha = Average Time a family takes to eat ice cream
Beta = Average Time a family takes to do community service
Lambda = Average Time Vendor takes to fill the pot
Mu = Average Time Vendor sleeps after refilling

Eg: 20 10 5 15 20 10 5

Output file "output.txt" contains all requests and exits time for the threads.

To run the program and generate output file, run: g++ -o prog code.cpp -lpthread

Run the program using the command: ./prog