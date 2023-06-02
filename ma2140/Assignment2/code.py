# Python libraries for math and graphics
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import scipy.stats as st

# Read EXCEL
df1 = pd.read_excel('./Data.xlsx')
df1.columns = ['TS']


# Convert to list
Money = df1['TS'].tolist()

print(st.t.interval(confidence=0.95, df=len(Money) - 1,
                    loc=np.mean(Money), scale=st.sem(Money)))
