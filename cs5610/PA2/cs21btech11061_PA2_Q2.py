# Name: Vishal Vijay Devadiga
# Roll No.: CS21BTECH11061
# Programming Assignment 2: Problem 2

import csv

# input file name, edit as required
input_file = "input-crt.txt"

# output file name
output_file = "output-crt.txt"

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

# extended euclidean algorithm 
def extended_euclidean(a, b):
    # base case
    if a == 0:
        return 0, 1, b

    # recursive case
    xx, yy, gcd = extended_euclidean(b % a, a)

    # update x and y
    x = yy - xx * (b // a)
    y = xx

    # return x, y, and gcd
    return x, y, gcd

# Find a^(-1) mod n

def find_a_inv(a, n):
    # Find x, y, and gcd
    x, _, _ = extended_euclidean(a, n)

    # if x is negative, make it positive
    if x < 0:
        x = x + n

    return x

# Given 4 integers a, b, m, and n, find x such that x = a mod m and x = b mod n
        
def find_x(a, b, m, n):
    # Find m inverse and n inverse
    m_inv = find_a_inv(m, n)
    n_inv = find_a_inv(n, m)

    # Find t1 and t2
    t1 = (m * m_inv) % (m * n)
    t2 = (n * n_inv) % (m * n)

    # Find x
    x = (a * t2 + b * t1) % (m * n)

    return x

# main function
def main():
    # read input data
    input_data = file_read()
    
    # define output data
    output_data = []
    
    # for each test case
    for i in range(0, len(input_data)):
        # convert input data to integers
        a, m, b, n = map(int, input_data[i])

        # if m and n are not coprime
        _, _, g = extended_euclidean(m, n) 
        if g != 1:
            # Print the results
            print(-1)

            # append -1 to output data
            output_data.append([-1])

            # continue to next test case
            continue

        # find x
        x = find_x(a, b, m, n)

        # Print the results
        print(x)

        # append x to output data
        output_data.append([x])

    # write output data to output file
    file_write(output_data)

# call main function
if __name__ == "__main__":
    main()