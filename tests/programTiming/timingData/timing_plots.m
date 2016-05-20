clear all;
close all;
clc;

%% PRINT_11 -> everything
figure;
data = csvread('PRINT_11.CSV');
t1 = (data(3:end,1) - data(3,1))*1000;
v1 = data(3:end,2);

plot(t1,v1);
title('Timing of the `runController()` function')
xlabel('Time (ms)')
ylabel('Pin voltage (V)')
grid on;
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6);
axes_handles = findall(gcf, 'type','axes' );

%% PRINT_08 -> everything - powerAdc reading - tachAdc reading
figure;
data = csvread('PRINT_08.CSV');
t2 = (data(3:end,1) - data(3,1))*1000;
v2 = data(3:end,2);

plot(t2,v2);

%% PRINT_10 -> everything - powerAdc reading
figure;
data = csvread('PRINT_10.CSV');
t3 = (data(3:end,1) - data(3,1))*1000;
v3 = data(3:end,2);

plot(t3,v3);