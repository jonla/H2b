import numpy as np
from matplotlib import pyplot as plt



data = np.loadtxt('alpha_energy.dat')

xaxis = np.arange(0.05, 0.25, 0.01)

fig = plt.figure()
ax = fig.add_subplot(111)
ax.plot(xaxis, data)

plt.show()
