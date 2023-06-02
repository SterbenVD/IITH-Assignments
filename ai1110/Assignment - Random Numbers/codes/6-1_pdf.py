import numpy as np
import matplotlib.pyplot as plt

maxrange = 40
x = np.linspace(-2, 12, maxrange)
simlen = int(1e6)
err = []
randvar = np.loadtxt('./chi.dat', dtype='double')
for i in range(maxrange):
    err_ind = np.nonzero(randvar < x[i])
    err_n = np.size(err_ind)
    err.append(err_n/simlen)

pdf = []
for i in range(maxrange-1):
    test = (err[i+1]-err[i])/(x[i+1]-x[i])
    pdf.append(test)


def chi_pdf(x):
    if (x >= 0):
        return 0.5*np.exp(-x/2)
    else:
        return 0


chi_pdf_vec = np.vectorize(chi_pdf, otypes=[np.float])

plt.scatter((x[0:(maxrange-1)] + x[1:maxrange]) /
            2, pdf, label="Experimental PDF")
plt.plot(x, chi_pdf_vec(x), label="Theoretical PDF", color='orange')
plt.grid()
plt.xlabel('$x$')
plt.ylabel('$PDF$')
plt.legend(loc="best")
plt.savefig('../figs/6-1_pdf.png')
