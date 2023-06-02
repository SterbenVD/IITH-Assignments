import numpy as np
import matplotlib.pyplot as plt

arr = np.loadtxt('max_lik.dat',dtype = 'double')
x = np.arange(0,1000000)
plt.scatter(x,arr,s=5)
plt.grid()
plt.xlabel('$X-AXIS$')
plt.ylabel('$Y$')
plt.legend(loc='best')
plt.savefig('../figs/5_Y.png')
plt.show()