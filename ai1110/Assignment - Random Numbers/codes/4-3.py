import numpy as np
import matplotlib.pyplot as plt
import scipy as sc
# Experimental Graph
maxrange = 60
x = np.linspace(-0.5, 2.5, maxrange)
size = 1000000
err = []
derr = []
arr = np.loadtxt('tri.dat', dtype='double')
for i in range(0, maxrange):
    arr_len = np.count_nonzero(arr < x[i])
    err.append(arr_len/size)

for i in range(0,maxrange-1):
    val = (err[i+1]-err[i])/(x[i+1]-x[i])
    derr.append(val)

# Theory Graph

def tpdf(y):
    ans = 0
    if(y < 0 or y > 2):
        ans = 0
    elif(y < 1):
        ans = y
    else:
        ans = 2 - y
    return ans


tg = sc.vectorize(tpdf, otypes=[np.float])
plt.plot(x,tg(x),color='orange',label = "Theoretical PDF")
plt.scatter((x[0:(maxrange-1)].T + x[1:].T)/2,derr,color='blue',label="Experimental PDF")
plt.xlabel('$T$')
plt.ylabel('$CDF$')
plt.legend(loc='best')
plt.savefig('../figs/4_pdf.png')
plt.show()
