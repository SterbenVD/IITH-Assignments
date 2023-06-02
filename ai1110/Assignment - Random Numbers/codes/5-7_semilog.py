import numpy as np
import matplotlib.pyplot as plt
import mpmath as mp

x = np.linspace(0, 10, 30)
ber = np.loadtxt('./ber.dat',dtype='double')
gau = np.loadtxt('./gau.dat',dtype='double')
def error(y):
    var = y * ber + gau
    e0 = np.count_nonzero((var < 0) & (ber > 0))
    e1 = np.count_nonzero((var > 0) & (ber < 0))
    n0 = np.count_nonzero(ber > 0)
    n1 = np.count_nonzero(ber > 0)
    return 0.5 * (e0/n0 + e1/n1)

def Q_gauss(y):
    return mp.erfc(y/mp.sqrt(2))/2


y_A = round(Q_gauss(0.5), 6)
x2 = np.linspace(0,4,15)
tg = np.vectorize(Q_gauss, otypes=[np.float])
err = np.vectorize(error, otypes=[np.float])
txt = "A = (0.5 , " + str(y_A) + ")"
plt.semilogy(x, tg(x), color='orange')
plt.semilogy(x2,err(x2),'.')
plt.annotate(txt, (0.5, Q_gauss(0.5)), textcoords="offset points",
             xytext=(65, 0), ha='center')
plt.xlabel('$A$')
plt.ylabel('$P_e$')
plt.legend(loc='best')
plt.grid()
plt.savefig('../figs/5-7_semilog.png')
plt.show()
