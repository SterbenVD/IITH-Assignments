import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# Load Excel file
Data = pd.read_excel("./../table/table.xlsx")

#Read File
colours = Data["Colour"]
freq = Data["No. of Marbles"]
list = dict((x,y) for x,y in zip(colours,freq))

# Find probability 
def prob(key,dict):
    return "{:.3f}".format(dict[key]/dict["Total"])

def find_prob(key,dict):
    print("Probability of Marble being",key,"is",prob(key,dict))

def find_not_prob(key,dict):
    print("Probability of Marble being not",key,"is",1 - float(prob(key,dict)))

# Find required probability
find_prob('Red',list)
find_prob('White',list)
find_not_prob('Green',list)