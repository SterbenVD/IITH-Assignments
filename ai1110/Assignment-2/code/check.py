# Python libraries for math
import numpy as np

# Finding roots for a Quadratic equation
def find_roots(*coeff):
    root_arr = np.roots(coeff)
    return root_arr

# Check if matrix is syymetric
def check_symmat(M):
    M_T = M.transpose()
    if np.array_equiv(M, M_T):
        print("Matrix is symmetric")
    else:
        print("Matrix is not symmetric")
        
if __name__ == "__main__":
    roots = find_roots(1,2,-15)
    for x in roots:
        M = np.array([[6,-(x**2)],[2*x-15,10]])
        print("For x =",x, end=", ")
        check_symmat(M)