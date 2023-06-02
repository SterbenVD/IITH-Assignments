import numpy as np
import matplotlib.pyplot as plt

# Experimental Graph	
maxrange = 40
x = np.linspace(-0.5,1.5,maxrange)
size = 1000000
err = []
arr = np.loadtxt('uni.dat',dtype = 'double')
for i in range(0,maxrange):
	arr_len= np.count_nonzero(arr < x[i])
	err.append(arr_len/size)

# Theory Graph
def cdf(i):
    if(i < 0):
        return 0
    elif(i > 1):
        return 1
    else:
        return i

tg= np.vectorize(cdf,otypes=[np.float])
plt.scatter(x.T,err,label="Experimental CDF")
plt.plot(x,tg(x),color="orange",label="Theoretical CDF")
plt.xlabel('$x$')
plt.ylabel('$CDF$')
plt.legend(loc='best')
plt.savefig('../figs/1_cdf.png')
plt.show()
