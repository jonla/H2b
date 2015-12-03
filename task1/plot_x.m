clc, clf

data = importdata('position.dat');
R1 = data(:,1:3);
R2 = data(:,4:6);
clear data;

%hist(R2(:,3),50)
hist3(R2(:,1:2),[100 100])