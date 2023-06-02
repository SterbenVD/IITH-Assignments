import numpy as np
import matplotlib.pyplot as plt
from matplotlib.pyplot import stem

X = np.array([1, 2, 3, 4, 5, 6])
Y = np.array([1/6, 1/6, 1/6, 1/6, 1/6, 1/6])

X_pmf = np.array([0, 7])
Y_pmf = np.array([0, 0])
X_cdf = np.array([-1, 0, 7])
Y_cdf = np.array([0, 0, 1])

T = np.array([-1, 0, 1, 2, 3, 4, 5, 6, 7])

plt.xlabel('Value of X')
plt.ylabel('Probability Mass Function')
plt.xticks(T)
stem(X, Y, linefmt='k--', markerfmt='ko', basefmt='k-')
stem(X_pmf, Y_pmf, linefmt='k--', markerfmt='ko', basefmt='k-')
plt.savefig("../figs/figure.png")
plt.show()