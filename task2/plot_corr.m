clc
energy = importdata('energy.dat');
N = size(energy,1);
block_avg = importdata('block_avg.dat');
clear data;
%%
plot(energy,'linewidth',3)
set(gca,'fontsize',20)
grid on
xlabel('Iteration','interpret','latex')
ylabel('Local energy (a.u.)','interpret','latex')
xlim([0 1000])
%%
clc, clf
taumax = 200;
%[aco, lags] = xcorr(energy,taumax,'unbiased');
[aco, lags] = autocorr(energy,taumax);
subplot(2,1,1)
hold on
plot(lags,aco/max(aco),'linewidth',3)
line([0 200],[exp(-2) exp(-2)])
annotation('textarrow',[0.50 0.35],[0.83 0.71], ...
  'string','$\Phi \approx 0.135 \Rightarrow \; s\approx 10$', ...
  'fontsize',20,'interpret','latex')
hold off
set(gca,'fontsize',20)
grid on
xlabel('Iterations','interpret','latex')
ylabel('Auto correlation $\Phi$','interpret','latex')
ylim([-0.1 1])
xlim([0 40])

subplot(2,1,2)
plot(block_avg,'linewidth',3)
set(gca,'fontsize',20)
xlabel('Block size','interpret','latex')
ylabel('$s$','interpret','latex')
ylim([0 20])
grid on