#Python libraries for math and graphics
import numpy as np
import matplotlib.pyplot as plt

#Generate line points
def line_gen(A,B):
  len =10
  dim = A.shape[0]
  x_AB = np.zeros((dim,len))
  lam_1 = np.linspace(0,1,len)
  for i in range(len):
    temp1 = A + lam_1[i]*(B-A)
    x_AB[:,i]= temp1.T
  return x_AB

def line_dir_pt(m,A,k1,k2):
  len = 10
  dim = A.shape[0]
  x_AB = np.zeros((dim,len))
  lam_1 = np.linspace(k1,k2,len)
  for i in range(len):
    temp1 = A + lam_1[i]*m
    x_AB[:,i]= temp1.T
  return x_AB

# Find Centroid of given points
def centroid(*points):
  G = np.mean(points,axis=0)
  return G

# Assigning the points
A = np.array([-1, 3])
B = np.array([4, 2])
C = np.array([3, -2])

# Finding centroid
G = centroid(A,B,C)

# Plot Sides of Triangle
xAB = line_gen(A,B)
xBC = line_gen(B,C)
xCA = line_gen(C,A)
plt.plot(xAB[0,:],xAB[1,:])
plt.plot(xBC[0,:],xBC[1,:])
plt.plot(xCA[0,:],xCA[1,:])

# Plot Line parallel to AC through G
m =  C-A
xG = line_dir_pt(m,G,-0.5,0.5)
plt.plot(xG[0,:],xG[1,:])

# Annotating the points
tri_coords = np.vstack((A,B,C,G)).T
plt.scatter(tri_coords[0,:], tri_coords[1,:])
vert_labels = ['A','B','C','G']
for i, txt in enumerate(vert_labels):
    plt.annotate(txt,(tri_coords[0,i], tri_coords[1,i]),textcoords="offset points",xytext=(0,10),ha='center')

# Other stuff on plot
plt.title("Figure 9.2")
plt.xlabel('$x$')
plt.ylabel('$y$')
plt.legend(loc='best')
plt.grid()
plt.axis('equal')
plt.savefig("../figs/9.2.png")
plt.show()