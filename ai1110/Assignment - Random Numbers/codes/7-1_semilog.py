import numpy as np
import matplotlib.pyplot as plt
import mpmath as mp

x = np.linspace(0, 10, 50)
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


def terr_func(g):
    g_new = 10**(g/10.0)
    return 0.5*(1 - ((g_new/(g_new+2))**(0.5)))


terr = np.vectorize(terr_func, otypes=[np.float])

x2 = np.linspace(0, 10, 11)
err = np.vectorize(emp_err, otypes=[np.float])
plt.semilogy(x, terr(x), color='orange')
plt.semilogy(x2, err(x2), '.')
plt.legend(loc='best')
plt.grid()

plt.xlabel('$\gamma$')
plt.ylabel('$\log{P_e(\gamma)}$')
plt.savefig('../figs/7-1_semilog.png')
plt.show()
