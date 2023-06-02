import numpy as np
import matplotlib.pyplot as plt


maxrange = 100
x = np.linspace(0, 10, maxrange)
G = np.linspace(0, 10, 11)
ber = np.loadtxt('./ber.dat', dtype='double')
gau = np.loadtxt('./gau.dat', dtype='double')


def emp_err(g):
    ral_file = "FILE"
    if g < 10:
        ral_file = "./ral_data/"+str(int(g)).zfill(1)+".dat"
    else:
        ral_file = "./ral_data/"+str(int(g)).zfill(2)+".dat"
    rv = np.loadtxt(ral_file, dtype='double')
    n0 = np.count_nonzero(ber > 0)
    e0 = np.count_nonzero((rv < 0) & (ber > 0))
    return e0/n0


eerr = np.vectorize(emp_err, otypes=[np.float])


def expected_err(g):
    g_new = 10**(g/10.0)
    return (1 - ((g_new/(g_new+2))**(0.5)))/2


terr = np.vectorize(expected_err, otypes=['double'])


plt.plot(G, eerr(G), '.')
plt.plot(x, terr(x))
plt.grid()
plt.xlabel('$\gamma$')
plt.ylabel('$P_e(\gamma)$')
plt.legend(loc="best")
plt.savefig('../figs/7-1.png')
plt.show()
