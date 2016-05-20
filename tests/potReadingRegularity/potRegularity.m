clear all;
close all;
clc;

figure;
data = csvread('potResTest3.csv');
t1 = data(2:end,1)/1000;
v1 = (data(2:end,2));%- 640) * 0.00068569;

h = scatter(t1,v1,'filled','SizeData',30);
title('Acquisition of potentiometer data')
xlabel('Time (s)')
ylabel('Potentiometer ADC values (mV)')
grid on;
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6);
axes_handles = findall(gcf, 'type','axes' );