# Name: Vishal Vijay Devadiga
# Roll No.: CS21BTECH11061
# Programming Assignment 2: Problem 1

import csv

# input file name, edit as required
input_file = "input-Zn.txt"

# output file name
output_file = "output-Zn.txt"

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

# Find whether a belongs to Zn* or not

def find_zn_star(a, n):
    # Find gcd of a and n
    _, _, gcd = extended_euclidean(a, n)

    # if gcd is 1, a belongs to Zn*
    if gcd == 1:
        return True
    
    return False

# Find a^(-1) mod n

def find_a_inv(a, n):
    # Find x, y, and gcd
    x, _, _ = extended_euclidean(a, n)

    # if x is negative, make it positive
    if x < 0:
        x = x + n

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
        n, a, b = map(int, input_data[i])

        # Find a^b mod n
        x = find_x(a, b, n)

        # Find whether a belongs to Zn* or not
        zn_star = find_zn_star(a, n)

        # if a belongs to Zn*
        if zn_star:
            # Find a^(-1) mod n
            a_inv = find_a_inv(a, n)

            # Print the results
            print(x, ",", zn_star, ",", a_inv)

            # append x to output data
            output_data.append([x, zn_star, a_inv])
        else:

            # Print the results
            print(x, ",", zn_star)

            # append x to output data
            output_data.append([x, zn_star])

    # write output data to output file
    file_write(output_data)

# call main function
if __name__ == "__main__":
    main()