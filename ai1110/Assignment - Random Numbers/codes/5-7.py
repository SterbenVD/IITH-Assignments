import numpy as np
import matplotlib.pyplot as plt
import scipy as sc
import mpmath as mp

x = np.linspace(0,1,80)
def Q_gauss(y):
    return mp.erfc(y/mp.sqrt(2))/2

y_A = round(Q_gauss(0.5),6)

tg = np.vectorize(Q_gauss,otypes=[np.float])
txt = "A = (0.5 , " + str(y_A) + ")"
plt.plot(x, tg(x), color='orange')
plt.scatter(0.5,Q_gauss(0.5))
plt.annotate(txt,(0.5,Q_gauss(0.5)),textcoords="offset points",xytext=(65,0),ha='center')
plt.grid()
plt.xlabel('$A$')
plt.ylabel('$P_e$')
plt.legend(loc='best')
plt.xlim(left = -0.01,right = 1.01)
plt.savefig('../figs/5-7.png')
plt.show()