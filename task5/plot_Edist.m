clc, clf

energy = importdata('energy.dat');

hist(energy,30)
grid on
xlabel('Energy','interpret','latex')
ylabel('Frequency','interpret','latex')
set(gca,'fontsize',15)