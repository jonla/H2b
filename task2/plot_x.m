clc
data = importdata('position.dat');
R1 = data(:,1:3);
R2 = data(:,4:6);
N = size(R1,1);
energy = importdata('energy.dat');
block_avg = importdata('block_avg.dat');
clear data;
%%
clc, clf
taumax = 200;
%[aco, lags] = xcorr(energy,taumax,'unbiased');
[aco, lags] = autocorr(R1(:,1),taumax);
plot(lags,aco/max(aco))
grid on
xlabel('Iterations')
ylabel('Auto correlation')
%%
clc, clf
plot(block_avg)
xlabel('Block size')
ylabel('s')
grid on