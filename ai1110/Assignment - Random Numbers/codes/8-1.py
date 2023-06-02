import numpy as np
import matplotlib.pyplot as plt

ber = np.loadtxt('./ber2d.dat', dtype='double')
y = np.loadtxt('./twod_data/5.dat', dtype='double')
C = np.where(ber[:, 0] > 0, 'b', 'r')
plt.scatter(y[:, 0], y[:, 1], s=3, c=C)
plt.grid()
plt.xlabel('$y_1$')
plt.ylabel('$y_2$')
plt.savefig('../figs/8-1.png')
plt.show()
