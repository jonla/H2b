clf, clc

data = importdata('alpha_energy_grad.dat');
alpha = data(:,1);
energy = data(:,2);
clear data;

subplot(2,1,1)
plot(alpha,'linewidth',3)
set(gca,'fontsize',20)
xlabel('Iteration','interpret','latex')
ylabel('$\alpha$','interpret','latex')
grid on

subplot(2,1,2)
plot(energy,'linewidth',3)
set(gca,'fontsize',20)
xlabel('Iteration','interpret','latex')
ylabel('$E_0$ (a.u.)','interpret','latex')
grid on