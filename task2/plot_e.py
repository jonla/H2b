import numpy as np
from matplotlib import pyplot as plt

data = np.loadtxt('energy.dat')
print data.shape
fig = plt.figure()
ax = fig.add_subplot(111)

ax.plot(data)
plt.show()
