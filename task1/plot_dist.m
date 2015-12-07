clc, clf

data = importdata('position.dat');
R1 = data(:,1:3);
R2 = data(:,4:6);
N = size(data,1);
clear data;

clf
[count, r] = hist(sqrt(R1(:,1).^2 + R1(:,2).^2 + R1(:,3).^2),100);
P_teo = 2^5*r.^2.*exp(-4*r);
dr = r(2)-r(1);
hold on
set(gca,'fontsize',20)
plot(r,P_teo,'linewidth',3)
plot(r,count/(N*dr),'xk','markersize',10,'linewidth',3)
%h = legend('No interaction','$\alpha=0.1$');
h = legend('$2^5r^2\exp{[-4r]}$','Samples, $\alpha=0.1$');
set(h,'interpret','latex')
xlabel('$r$ (a.u)','interpret','latex')
ylabel('Probability','interpret','latex')
grid on
xlim([0 3])
hold off

%% Energy

energy = importdata('energy.dat');
E = mean(energy)