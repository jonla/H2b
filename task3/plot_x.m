clc
data = importdata('position.dat');
R1 = data(:,1:3);
R2 = data(:,4:6);
N = size(data,1);
block_avg = importdata('block_avg.dat');
clear data;
%%
clc, clf
taumax = 200;
[aco, lags] = xcorr(R1(:,1),taumax,'unbiased');
plot(lags,aco/max(aco))
xlabel('Iterations')
ylabel('Auto correlation')
%%
clc, clf
plot(block_avg)
xlabel('Block size')
ylabel('s')