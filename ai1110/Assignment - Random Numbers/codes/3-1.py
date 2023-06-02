import numpy as np
import matplotlib.pyplot as plt
import scipy as sc
maxrange = 50
x = np.linspace(-2, 10, maxrange)
size = 1000000
err = []
arr = np.loadtxt('uni.dat', dtype='double')
log = np.log(arr)
var = np.array([-2 * i for i in log])
for i in range(0, maxrange):
    arr_leq = np.nonzero(var < x[i])
    arr_n = np.size(arr_leq)
    err.append(arr_n/size)


def tcdf(y):
    if(y < 0):
        return 0
    else:
	    return 1 - np.exp(-y/2)

tg = sc.vectorize(tcdf, otypes=[np.float])
plt.plot(x,tg(x),color='orange',label = "Theoretical C  DF")
plt.scatter(x, err, color="blue", label="Experimental CDF")
plt.xlabel('$V$')
plt.ylabel('$CDF$')
plt.legend(loc='best')
plt.savefig('../figs/3_cdf.png')
plt.show()
