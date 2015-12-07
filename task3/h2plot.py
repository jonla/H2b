import numpy as np
from matplotlib import pyplot as plt

s = 40.0
N = 10^6
var = 0.1367

data = np.loadtxt('alpha_energy_indie.dat')

errbar = np.sqrt(0.1367 / (N/s)) * np.ones( len(data) )

xaxis = np.arange(0.05, 0.25, 0.01)

fig = plt.figure()
plt.title('Alpha Parameter Sweep')
ax = fig.add_subplot(111)
ax.errorbar(xaxis, data, errbar)
plt.xlabel(r'$\alpha$', fontsize = 20)
plt.ylabel('Energy [a.u]', fontsize = 20)
plt.grid()
plt.show()
