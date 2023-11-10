# Assumption
# 1. Polytope is non-degenerate.
# 2. Polytope is bounded
# 3. Rank of A is n 

# Implement the simplex algorithm to maximize the objective function, You need to implement the method discussed in class. 

# Input: CSV file with m+2 rows and n+1 column. 
#              The first row excluding the last element is the initial feasible point z of length n
#              The second row excluding the last element is the cost vector c of length n
#              The last column excluding the top two elements is the constraint vector b of length m
#              Rows third to m+2 and column one to n is the matrix A of size m*n

# Output: You need to print the sequence of vertices visited and the value of the objective function at that vertex

import numpy as np
import pandas as pd

EPS = 1e-6

def read_data():
    df = pd.read_csv('input.csv', header=None)
    df = df.to_numpy()
    return df

def inter_data(mat):
    m, n = mat.shape
    z = mat[0, :-1]
    c = mat[1, :-1]
    b = mat[2:, -1]
    A = mat[2:, :-1]
    print('The Initial Feasible Point is :', z)
    print('The Cost Vector is :', c)
    print('The Constraint Vector is :', b)
    print('The Matrix A is :', A)
    return z, c, b, A

def get_direction(A, B, C, X):
    ei = np.where(np.abs(np.dot(A, X)-B) < EPS)[0]
    print(ei)
    A_bar = A[ei]
    print(A_bar)
    Z = -np.linalg.inv(np.transpose(A_bar))
    return Z

def get_neighbour(A, B, C, X):
    Z = get_direction(A, B, C, X)
    c = np.dot(Z, C)
    pcd = np.where(c > 0)[0]
    if len(pcd) == 0:
        return None
    else:
        v = Z[pcd[0]]
        ei = np.where(np.abs(np.dot(A, X)-B) < EPS)[0]
        nei = ~np.isin(np.arange(len(A)), ei)
        nei_A = A[nei]
        nei_B = B[nei]
        n = nei_B - np.dot(nei_A, X)
        d = np.dot(nei_A, v)
        n = n[np.where(d > 0)[0]]
        d = d[np.where(d > 0)[0]]
        s = n/d
        t = np.min(s[s >= 0])
        return X + t*v
    
def SimplexAlgorithm(A, B, C, X):
    while True:
        
        V = get_neighbour(A, B, C, X)
        
        if V is None:
            return X
        else:
            X = V
    
def main():
    mat = read_data()
    z, c, b, A = inter_data(mat)
    X = SimplexAlgorithm(A, b, c, z)
    # print('The Solution is :', X)
    # print('The Optimal Value is :', np.dot(c, X))
    
if __name__ == "__main__":
    main()
