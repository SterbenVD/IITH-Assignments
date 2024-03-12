# Name: Vishal Vijay Devadiga
# Roll No.: CS21BTECH11061
# Programming Assignment 3

import csv
import random

# input file name, edit as required
input_file = "inputSquareRoots.csv"

# output file name
output_file = "output.txt"

# read input file and return input data
def file_read():
    with open(input_file, 'r') as f:
        reader = csv.reader(f)
        input_data = list(reader)
    return input_data

# write to output file from output data
def file_write(output_data):
    with open(output_file, 'w') as f:
        writer = csv.writer(f)
        writer.writerows(output_data)


# Find x = a^b mod n
def find_x(a, b, n):
    # Find x = a^b mod n without using pow function.
    # pow function is simple to use: p = pow(a, b, n) 
    x = a
    p = 1
    while b > 0:
        if b % 2 == 1:
            p = (p * x) % n
        x = (x * x) % n
        b = b // 2
    return p

# Find the smallest positive integer k such that z^(2^k) ≡ 1 (mod p)
def find_k(z, p):
    k = 0
    while z != 1:
        z = (z * z) % p
        k = k + 1
    return k

# For a pair (a, p), return the smallest positive integer x such that
# x^2≡a (mod p), if it exists, and return 0 otherwise.
# Use the Tonelli-Shanks algorithm to find the square root of a modulo p.
def squareRoot(a, p):
    # Find m,t such that p-1 = 2^t * m
    t = 0
    m = p - 1
    while m % 2 == 0:
        t = t + 1
        m = m // 2
    
    # Find b such that b = a^m (mod p)
    b = find_x(a, m , p)
    
    # Find k such that b^(2^k) ≡ 1 (mod p)
    k = find_k(b, p)
    
    # Find x such that x = a^((m+1)/2) (mod p)
    x = find_x(a, (m + 1) // 2, p)
    
    # If k = t, then no solution exists
    if k == t:
        return 0
    
    # Find a random r such that r^((p-1)/2) ≡ -1 (mod p)
    r = 0
    while 1:
        r = random.randint(0, p) % p
        if find_x(r, (p - 1) // 2, p) == (p - 1):
            break
      
    s = find_x(r, m, p)
    S = find_x(s, 1 << (t - k), p)
    
    while k > 0:
        b = (b * S) % p
        x = (x * find_x(s, 1 << (t-k-1), p)) % p
        k = find_k(b, p)
        S = find_x(s, 1 << (t - k), p)
    
    # return the smallest positive integer x such that x^2≡a (mod p)
    return min(x, p - x)
    

# main function
def main():
    # read input data
    input_data = file_read()
    
    # define output data
    output_data = []
    
    # for each test case
    for i in range(0, len(input_data)):
        # convert input data to integer
        a = int(input_data[i][0])
        p = int(input_data[i][1])
        
        # find square root of a modulo p
        x = squareRoot(a, p)
        
        # append the result to output data
        output_data.append([x])
        
        # print the result
        print(x)

    # write output data to output file
    file_write(output_data)

# call main function
if __name__ == "__main__":
    main()