import numpy as np
import mpmath as mp
import matplotlib.pyplot as plt

ber = np.loadtxt('./ber2d.dat', dtype='double')


def emp_err(g):
    twod_file = "FILE"
    if g < 10:
        twod_file = "./twod_data/"+str(int(g)).zfill(1)+".dat"
    else:
        twod_file = "./twod_data/"+str(int(g)).zfill(2)+".dat"
    Y = np.loadtxt(twod_file, dtype='double')
    n0 = np.count_nonzero(ber[:, 0] > 0)
    e0 = np.count_nonzero((Y[:, 0] < Y[:, 1]) & (ber[:, 0] > 0))
    return e0/n0


err = np.vectorize(emp_err, otypes=[np.float])


def qfunc(y):
    return mp.erfc(y/mp.sqrt(2))/2


def expected_err(snr):
    snr_new = 10**(snr/10)
    return qfunc(np.sqrt(snr_new))


terr = np.vectorize(expected_err, otypes=[np.float])

maxrange = 100
G = np.linspace(0, 10, 11)
x = np.linspace(0, 10, 1000)
plt.plot(x, terr(x))
plt.plot(G, err(G), '.')
plt.grid()
plt.xlabel('SNR')
plt.ylabel('$P_e$(SNR)')
plt.savefig('../figs/8-3.png')
