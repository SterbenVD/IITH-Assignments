import numpy as np
import matplotlib.pyplot as plt
import mpmath as mp
import scipy as sc

maxrange=50
x = np.linspace(-6,6,maxrange)
size = 1000000
err = []
derr = []
arr = np.loadtxt('gau.dat',dtype = 'double')

for i in range(0,maxrange):
	arr_leq= np.nonzero(arr < x[i])
	arr_n = np.size(arr_leq)
	err.append(arr_n/size)

for i in range(0,maxrange-1):
    val = (err[i+1]-err[i])/(x[i+1]-x[i])
    derr.append(val)

def gauss_pdf(x):
	return 1/mp.sqrt(2*np.pi)*np.exp(-x**2/2.0)
	
vec_gauss_pdf = sc.vectorize(gauss_pdf)
plt.plot(x,vec_gauss_pdf(x),color='orange',label = "Theoretical PDF")

plt.scatter((x[0:(maxrange-1)].T + x[1:].T)/2,derr,color='blue',label="Experimental PDF")
plt.xlabel('$x$')
plt.ylabel('$PDF$')
plt.legend(loc='best')
plt.savefig('../figs/2_pdf.png')
plt.show()