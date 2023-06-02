#Python libraries for math and graphics
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# Read EXCEL
df1 = pd.read_excel('./Data.xlsx')
df1.columns = ['Year']

# roup Number
group_no = 22

# Convert to list
Year = df1['Year'].tolist()
samples_mean = []

# Generate 100 samples
for i in range(100):
    temp_sample = np.random.choice(Year,22 * 5)
    samples_mean.append(np.mean(temp_sample))

# Plot Histogram
plt.hist(samples_mean)

# Print Mean and Standard Deviation
print("Mean of sample means: ", np.mean(samples_mean))
print("Standard Deviation of sample means: ", np.std(samples_mean))

# Plot Details
plt.title("Year Mean vs Frequency")
plt.grid()
plt.xlabel('Year Mean')
plt.ylabel('Frequency')
plt.legend(loc='best')

# Save Graph
plt.savefig("./graph.png")
