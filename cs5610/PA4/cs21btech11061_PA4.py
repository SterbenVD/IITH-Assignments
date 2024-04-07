# Name: Vishal Vijay Devadiga
# Roll No.: CS21BTECH11061
# Programming Assignment 3

import csv
import random

# input file name, edit as required
input_file = "input-polygcd1.csv"

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

# To do: 
# 1) gcd of two polynomials
# 2) For two polynomials f(x) and g(x), find u(x) and v(x) such that f(x)u(x) + g(x)v(x) = gcd(f(x), g(x))

# Class Zn

# For a prime number p, the class Zn represents the set of integers modulo p
class Zn:
    # Initialize the class Zn
    def __init__(self, n, value):
        self.n = n
        self.value = value % n
    
    def __add__(self, other):
        return Zn(self.n, self.value + other.value)
    
    def __sub__(self, other):
        return Zn(self.n, self.value - other.value)
    
    def __mul__(self, other):
        return Zn(self.n, self.value * other.value)
    
    def __truediv__(self, other):
        return Zn(self.n, self.value * other.__inv__().value)
    
    def __floordiv__(self, other):
        return self.__truediv__(other)
    
    def __mod__(self, other):
        return Zn(self.n, self.value % other.value)
    
    def __eq__(self, other):
        return self.value == other.value
    
    def __ne__(self, other):
        return self.value != other.value
    
    def __pow__(self, other):
        if other.value == 0:
            return Zn(self.n, 1)
        p = self.__pow__(Zn(self.n, other.value // 2))
        if other.value % 2 == 0:
            return p * p
        else:
            return p * p * self
        
    def __inv__(self):
        # Since n is prime, a^(n-1) = 1 mod n
        return self.__pow__(Zn(self.n, self.n-2))
    
    def __str__(self):
        return str(self.value)
    

    
# For a polynomial f(x) = a0 + a1x + a2x^2 + ... + anx^n, the polynomial object is represented as [a0, a1, a2, ..., an]
# For example, f(x) = 2 + 3x + 4x^2 is represented as [2, 3, 4]
# For example, f(x) = 2x + 4x^3 is represented as [0, 2, 0, 4]
class poly:
    # Initialize the polynomial object
    # p here is a prime number
    def __init__(self, polynom, p):
        while len(polynom) > 0 and polynom[-1] == Zn(p, 0):
            polynom = polynom[:-1]
        self.polynom = polynom
        self.deg = len(polynom) - 1
        self.p = p
        
    def raise_degree(self, deg):
        p = poly(self.polynom, self.p)
        p.polynom.extend([Zn(self.p, 0) for _ in range(deg - self.deg)])
        
    def __add__(self, other):
        # Find the degree of the sum of two polynomials
        deg = max(self.deg, other.deg)
        
        # Initialize the sum of two polynomials
        sum_poly = [Zn(self.p, 0) for _ in range(deg + 1)]
        
        # Add the two polynomials
        for i in range(deg + 1):
            if i <= self.deg:
                sum_poly[i] += self.polynom[i]
            if i <= other.deg:
                sum_poly[i] += other.polynom[i]
        
        return poly(sum_poly, self.p)
    
    def __sub__(self, other):
        # Find the degree of the difference of two polynomials
        deg = max(self.deg, other.deg)
        
        # Initialize the difference of two polynomials
        diff_poly = [Zn(self.p, 0) for _ in range(deg + 1)]
        
        # Subtract the two polynomials
        for i in range(deg + 1):
            if i <= self.deg:
                diff_poly[i] += self.polynom[i]
            if i <= other.deg:
                diff_poly[i] -= other.polynom[i]
        
        return poly(diff_poly, self.p)
    
    def __mul__(self, other):
        # Find the degree of the product of two polynomials
        deg = self.deg + other.deg
        
        # Initialize the product of two polynomials
        prod_poly = [Zn(self.p, 0) for _ in range(deg + 1)]
        
        # Multiply the two polynomials
        for i in range(self.deg + 1):
            for j in range(other.deg + 1):
                prod_poly[i + j] += self.polynom[i] * other.polynom[j]
        
        return poly(prod_poly, self.p)
    
    def __truediv__(self, other):
        # Initialize the quotient of two polynomials
        q = [Zn(self.p, 0) for _ in range(self.deg - other.deg + 1)]
        
        # Find the quotient of two polynomials
        r = self
        
        while r.deg >= other.deg and not r.is_zero():
            d = [Zn(self.p, 0) for _ in range(r.deg - other.deg + 1)]
            d[-1] = r.polynom[r.deg] / other.polynom[other.deg]
            q += d
            r -= other * poly(d, self.p)
            
        q = q[::-1]
            
        return poly(q, self.p)
        
    def __mod__(self, other):
        # Find the quotient of two polynomials
        r = self
        
        while r.deg >= other.deg and not r.is_zero():
            d = [Zn(self.p, 0) for _ in range(r.deg - other.deg + 1)]
            d[-1] = r.polynom[r.deg] / other.polynom[other.deg]
            r -= other * poly(d, self.p)
        
        return r
    
    # Integer division of two polynomials
    def __floordiv__(self, other):
        return self.__truediv__(other)
    
    def __eq__(self, other):
        return self.deg == other.deg and all([self.polynom[i] == other.polynom[i] for i in range(self.deg + 1)])   
    
    ## Find the gcd of two polynomials by using the extended euclidean algorithm
    def gcd(self, other):
        # Initialize the polynomials    
        a = self
        b = other
        
        r, r_ = a, b
        s, s_ = poly([Zn(self.p, 1)], self.p), poly([Zn(self.p, 0)], self.p)
        t, t_ = poly([Zn(self.p, 0)], self.p), poly([Zn(self.p, 1)], self.p)
        
        while not r_.is_zero():
            q = r // r_
            r, r_ = r_, r - q * r_
            s, s_ = s_, s - q * s_
            t, t_ = t_, t - q * t_
        
        return r, s, t
        
    # If polynomial is equal to zero
    def is_zero(self):
        return self.deg == -1
        
    def __str__(self):
        # Reverse the polynomial
        polynom = self.polynom[::-1]
        
        # Initialize the string
        s = ""
        
        first_term = 1
        
        if self.is_zero():
            return "0"
        
        for i in range(self.deg + 1):
            deg = self.deg - i
            coeff = str(polynom[i])
            if deg == 0:
                if coeff != "0":
                    if first_term == 0:
                        s += " + "
                    s += str(coeff)
                elif first_term == 1:
                    s += "0"
            else:
                if coeff != "0":
                    
                    if first_term == 0:
                        s += " + "
                    if coeff != "1":
                        s += str(coeff)
                    if deg > 1:
                        s += "x^" + str(deg)
                    else:
                        s += "x"
                    first_term = 0
                    
        return s
    
# main function
def main():
    # read input data
    input_data = file_read()

    prime = input_data[0][0]
    prime = int(prime)

    # Read the input data

    p1 = input_data[1]
    p2 = input_data[2]

    if p1[-1] == '':
        p1 = p1[:-1]
    
    if p2[-1] == '':
        p2 = p2[:-1]

    # Reverse the input data
        
    p1 = p1[::-1]
    p2 = p2[::-1]
    
    # Convert the input data to Zn objects
    p1 = [Zn(prime, int(i)) for i in p1]
    p2 = [Zn(prime, int(i)) for i in p2]

    # Convert the input data to polynomial objects

    p1 = poly(p1, prime)
    p2 = poly(p2, prime)
    
    # # Find the gcd of two polynomials
    
    gcd, u, v = p1.gcd(p2)
    
    # # Part 1: Find the gcd of two polynomials
    
    print("GCD:", gcd)
    
    # # Part 2: Find u(x) and v(x) such that f(x)u(x) + g(x)v(x) = gcd(f(x), g(x))
    
    print("u:", u)
    print("v:", v)
    
    c = p1 * u
    d = p2 * v
    
    print("f(x)u(x) + g(x)v(x):", c + d)
    
# call main function
if __name__ == "__main__":
    main()