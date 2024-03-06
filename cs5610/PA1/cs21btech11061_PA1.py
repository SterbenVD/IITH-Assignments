# Name: Vishal Vijay Devadiga
# Roll No.: CS21BTECH11061
# Programming Assignment 1

import csv

# input file name, edit as required
input_file = "input-gcd.csv"

# output file name
output_file = "output.csv"

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

# main function
def main():
    # read input data
    input_data = file_read()
    
    # define output data
    output_data = []
    
    # for each test case
    for i in range(0, len(input_data)):
        # convert input data to integers
        a = int(input_data[i][0])
        b = int(input_data[i][1])
        
        # find x, y, and gcd
        x, y, gcd = extended_euclidean(a, b)
        
        # Print the results
        stx = "x=" + str(x)
        sty = "y=" + str(y)
        stgcd = "gcd=" + str(gcd)
        print(stx,",", sty,",", stgcd)
        
        # append to output data
        tc = "TC#" + str(i+1)
        output_data.append([tc,x, y, gcd])
        
    # write output data to output file
    file_write(output_data)

# call main function
if __name__ == "__main__":
    main()