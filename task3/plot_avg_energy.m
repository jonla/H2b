clc, clf
% Var(E_loc) = 0.1367
% s = 40
% -> Effective sampling size = N*N_simul/s
N = 10^5; s = 40; N_simul = 10;
std_div = sqrt(0.1367/(N*N_simul/s));
energy = importdata('alpha_energy_indie.dat');
alpha = linspace(0.05,0.24,20);
errBar = std_div*ones(size(energy));
errorbar(alpha,energy,errBar,'linewidth',3)
set(gca,'fontsize',20)
xlabel('$\alpha$','interpret','latex')
ylabel('$E_0$ (a.u.)','interpret','latex')
xlim([min(alpha) max(alpha)])
grid on