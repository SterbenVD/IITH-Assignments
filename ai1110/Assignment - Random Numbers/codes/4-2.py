import numpy as np
import matplotlib.pyplot as plt
import scipy as sc
# Experimental Graph
maxrange = 60
x = np.linspace(-0.5, 2.5, maxrange)
size = 1000000
err = []
arr = np.loadtxt('tri.dat', dtype='double')
for i in range(0, maxrange):
    arr_len = np.count_nonzero(arr < x[i])
    err.append(arr_len/size)

def tcdf(i):
    if(i < 0):
        return 0
    elif(i < 1):
        return i**2/2
    elif(i < 2):
        return -(i**2)/2 + 2*i - 1
    else:
        return 1

tg = sc.vectorize(tcdf, otypes=[np.float])
plt.plot(x,tg(x),color='orange',label = "Theoretical CDF")
plt.scatter(x.T, err, label="Experimental CDF")
plt.xlabel('$T$')
plt.ylabel('$CDF$')
plt.legend(loc='best')
plt.savefig('../figs/4_cdf.png')
plt.show()
