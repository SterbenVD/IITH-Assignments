import pandas as pd
import numpy as np

# Define the dimensions
m = 5
n = 4

# Generate the initial feasible point z, cost vector c, constraint vector b, and matrix A
z = np.random.rand(n)
c = np.random.rand(n)
b = np.random.rand(m)
A = np.random.rand(m, n)

# Create a DataFrame for the CSV file
df = pd.DataFrame(np.zeros((m+2, n+1)))

# Fill in the DataFrame with z, c, b, and A
df.iloc[0, :-1] = z
df.iloc[1, :-1] = c
df.iloc[2:, -1] = b
df.iloc[2:, :-1] = A

# Write the DataFrame to a CSV file
df.to_csv('input.csv', index=False, header=False)