import numpy as np
import matplotlib.pyplot as plt


maxrange = 80
x = np.linspace(-2, 12, maxrange)
simlen = int(1e6)
err = []
randvar = np.loadtxt('./chi.dat', dtype='double')
for i in range(maxrange):
    err_ind = np.nonzero(randvar < x[i])
    err_n = np.size(err_ind)
    err.append(err_n/simlen)
    

def chi_cdf(x):
    if (x < 0):
        return 0
        
    else:
        return 1 - np.exp(-x/2)


chi_cdf_vec = np.vectorize(chi_cdf, otypes=[np.float])


plt.scatter(x, err, label="Experimental CDF")
plt.plot(x, chi_cdf_vec(x), label="Theoretical CDF", color='orange')
plt.grid()
plt.xlabel('$x$')
plt.ylabel('$CDF$')
plt.legend(loc="best")
plt.savefig('../figs/6-1_cdf.png')
