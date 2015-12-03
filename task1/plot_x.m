clc, clf

data = importdata('samples.dat');
X = data(:,1);
Y = data(:,2);
Z = data(:,3);
fAvg = data(:,4);
N = length(X);
error = fAvg(end) - 7/8

plot(fAvg, 'linewidth',3)
grid on
ylabel('Average')
xlabel('Iteration')
set(gca, 'fontsize',20)
%hist(X)
%[bars, centers] = hist(Z);
%hold on
%plot(centers,bars/N);
%plot(centers, exp(-centers.^2)/pi)
%hold off