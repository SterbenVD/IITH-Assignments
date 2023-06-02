# Python libraries for math and graphics
import numpy as np
import matplotlib.pyplot as plt

# Generating points on a parabola
def parab_gen(x, a,b,c):
    y = a*(x**2) + b*x + c
    return y

# Generate line points
def line_dir_pt(m, A, k1, k2):
    len = 10
    dim = A.shape[0]
    x_AB = np.zeros((dim, len))
    lam_1 = np.linspace(k1, k2, len)
    for i in range(len):
        temp1 = A + lam_1[i]*m
        x_AB[:, i] = temp1.T
    return x_AB

# Assigning and plotting points
O = np.array([0,0])

# Set up plot
plt.title("Figure 1")
plt.grid()

# Plot X-axis
m =  np.array([1,0])
xO = line_dir_pt(m,O,-7,5)
plt.plot(xO[0,:],xO[1,:],label="X-axis")

# Plot Parabola
x_parabola = np.linspace(-6,4,100)
y_parabola = parab_gen(x_parabola, 1, 2,-15)
plt.plot(x_parabola,y_parabola,label= "$y = x^2 + 2x - 15$")

# Plot the roots of the quadratic equation
coeff = [1,2,-15]
roots = np.roots(coeff)
for loc in roots:
    point = np.array([loc,0])
    plt.plot(loc,0,marker = "o", c = "green")
    plt.annotate((loc,0),point,xytext=(0,10),ha='center',textcoords="offset points")

# Extra
plt.xlabel('$x$')
plt.ylabel('$y$')
plt.xlim(left=-7,right=5)
plt.legend(loc='best')

# SAVE Figure
plt.savefig("../figs/figure.png")
plt.show()