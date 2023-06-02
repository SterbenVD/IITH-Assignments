import pandas as pd
import numpy as np

# Load Excel file
Data = pd.read_excel("./../table/table.xlsx")

#Read File
ranofmarks = Data["Marks"]
freq = Data["Number of Students"]
list = dict((x,y) for x,y in zip(ranofmarks,freq))

# Find probability 
def prob(key,dict):
    return "{:.3f}".format(dict[key]/dict["Total"])

def find_prob(key,dict):
    print("Probability of Marks",key,"is",prob(key,dict))

# Find required probability
find_prob('0 - 20',list)
find_prob('60 - 70',list)
find_prob('70 - 100',list)
print("Thus, Probability of Marks 60 - 100 is",float(prob('60 - 70',list)) + float(prob('70 - 100',list)))