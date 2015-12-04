clf, clc

data = importdata('alpha_energy_grad.dat');
alpha = data(:,1);
energy = data(:,2);
clear data;

subplot(2,1,1)
plot(alpha)

subplot(2,1,2)
plot(energy)