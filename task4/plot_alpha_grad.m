clf, clc

data = importdata('alpha05.dat');
alpha05 = data(:,1);
data = importdata('alpha06.dat');
alpha06 = data(:,1);
data = importdata('alpha07.dat');
alpha07 = data(:,1);
data = importdata('alpha08.dat');
alpha08 = data(:,1);
data = importdata('alpha09.dat');
alpha09 = data(:,1);
data = importdata('alpha10.dat');
alpha10 = data(:,1);
x = (1:numel(alpha05));

hold on
plot(alpha05,'linewidth',3)
plot(alpha06,'linewidth',3)
plot(alpha07,'linewidth',3)
plot(alpha08,'linewidth',3)
plot(alpha09,'linewidth',3)
plot(alpha10,'linewidth',3)
hold off
set(gca,'fontsize',20)
xlabel('Iteration','interpret','latex')
ylabel('$\alpha$','interpret','latex')
ylim([0.142 0.17])
h = legend('$\beta=0.5$', '$\beta=0.6$', '$\beta=0.7$', '$\beta=0.8$', ...
  '$\beta=0.9$', '$\beta=1.0$');
set(h,'interpret','latex');
grid on