clear all
close all
clc

%% Cubli model parameters

T_m=0.005;
K=0.5;
J_w=0.601e-3;
J_f=2.8e-3;
B_w=17.03e-6;
B_f=6.08e-3;
m_w=0.222;
m_f=0.77-m_w;%0.354;
g=9.82;
l_w=0.093;
l_f=0.08498;%0.076;

%%

%for the last part of the signal:
pendulumData = csvread('PRINT_03.CSV'); %row 709 to 1300
%simulation time: 5.91
%initial condition: 0.1487

%for whole signal:
%pendulumData = csvread('pendulum.CSV', 72, 0, [ 72 0 1072 1 ]); %row 72 to 1072
%simulation time: 10
%initial condition: -pi/4

%for the last part of the signal:
t = pendulumData(:,1)'+5;
%for whole signal:
%t = pendulumData(:,1)'+10-.72;

Yvolt = pendulumData(:,2);

u = zeros(size(Yvolt));
uin = [ t' u ];

% Data from Volt to rads
Vmin = 0.4708;%   mean(voltage( 667:1243,1)) %voltage mean from 3.3 to 6.2 in time
Vmax = 0.9513;%   mean(voltage(1336:2000,1)) %voltage mean from 6.7 to 10 in time
equVolt = 0.6945;%mean(voltage(   1: 591,1)) %voltage mean from 0 to 2.9 in time
resRad = (1.5769)/(Vmax-Vmin);
y = (Yvolt - equVolt)*resRad-0.005;

scatter(t',y)

%%

par0 = [ B_f J_f ];% m_f l_f ];

Ynew = simCubli(u,t,par0);
%hold on;
%plot(t, Ynew);
%hold off;

save measCubli t u y %creating measTestName

process = 'Cubli';

%%

run mainest.m

%% PLOTTING IT PRETTILY :)

a = get(findall(gcf, 'Type', 'line', 'color', '[0.8500 0.3250 0.0980]'));
Ynew = a.YData;

figure;
plot(t', y, 'b')
hold on
plot(t', Ynew, 'r', 'LineWidth', 1.4)
grid on, grid minor;
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)

title('Parameter Estimation using Sense Tool')
xlabel('Time (s)')
ylabel('Angle (rad)')

hold off
