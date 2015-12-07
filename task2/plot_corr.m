clc
data = importdata('position.dat');
R1 = data(:,1:3);
R2 = data(:,4:6);
N = size(R1,1);
energy = importdata('energy.dat');
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
[aco, lags] = autocorr(R1(:,1),taumax);
subplot(2,1,1)
hold on
plot(lags,aco/max(aco),'linewidth',3)
line([0 200],[exp(-2) exp(-2)])
annotation('textarrow',[0.55 0.45],[0.80 0.70], ...
  'string','$\Phi \approx 0.135 \Rightarrow \; s\approx 40$', ...
  'fontsize',20,'interpret','latex')
hold off
set(gca,'fontsize',20)
grid on
xlabel('Iterations','interpret','latex')
ylabel('Auto correlation $\Phi$','interpret','latex')
ylim([-0.1 1])
xlim([0 100])

subplot(2,1,2)
plot(block_avg,'linewidth',3)
set(gca,'fontsize',20)
xlabel('Block size','interpret','latex')
ylabel('$s$','interpret','latex')
ylim([0 45])
grid on