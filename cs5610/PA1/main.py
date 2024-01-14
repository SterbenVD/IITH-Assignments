import csv

input_file = "input-gcd.csv"
output_file = "output.csv"

# read input file
def file_read():
    with open(input_file, 'r') as f:
        reader = csv.reader(f)
        input_data = list(reader)
    return input_data

# write output file
def file_write(output_data):
    with open(output_file, 'w') as f:
        writer = csv.writer(f)
        writer.writerows(output_data)

# extended euclidean algorithm
def extended_euclidean(a, b):
    if a == 0:
        return 0, 1, b

    xx, yy, gcd = extended_euclidean(b % a, a)

    x = yy - xx * (b // a)
    y = xx

    return x, y, gcd

# main function
def main():
    input_data = file_read()
    output_data = []
    for i in range(0, len(input_data)):
        a = int(input_data[i][0])
        b = int(input_data[i][1])
        x, y, gcd = extended_euclidean(a, b)
        print("Test #", i+1)
        print("x =", x)
        print("y =", y)
        print("gcd =", gcd, "\n")
        output_data.append([x, y, gcd])
    file_write(output_data)

if __name__ == "__main__":
    main()