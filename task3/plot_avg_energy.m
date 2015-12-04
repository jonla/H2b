clc, clf
% Var(E_loc) = 0.1367
% N = 10^7
% s = 40
% -> Effective sampling size = N/s
N = 10^7; s = 40;
energy = importdata('alpha_energy.dat');
alpha = linspace(0.05,0.24,20);
errBar = sqrt(0.1367/(N/s))*ones(size(energy));
errorbar(alpha,energy,errBar,'linewidth',3)
xlabel('Alpha')
ylabel('Energy')
xlim([min(alpha) max(alpha)])
grid on