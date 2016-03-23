clear all
close all
clc

%% Cubli model parameters
T_m=0.005;
K=0.5;
J_w=0.601e-3;
J_f=(2.8e-3);
B_w=17.03e-6;
B_f=6.08e-3;
m_w=0.222;
m_f=0.354;
g=9.82;
l_w=0.093;
l_f=0.076;

%%
pendulumData = csvread('pendulum.CSV', 72, 0, [ 72 0 1072 1 ]); %row 72 to 1339

t = pendulumData(:,1)'+10-.72;
Yvolt = pendulumData(:,2);

u = zeros(size(Yvolt));
uin = [ t' u ]

% Data from Volt to rads
Vmin=0.004316370106762;
Vmax=0.466679601990048;
equVolt=0.215324792013310;  
middleVolt=0.235497986048405;

offsetVolt = middleVolt-equVolt;
resRad = (pi/2)/(Vmax-Vmin);
y = (Yvolt - middleVolt + offsetVolt)*resRad;

plot(t',y)

%%
par0 = [ B_f J_f m_f l_f ];

Ynew = simCubli(u,t,par0);

%hold on;
%plot(t, Ynew);
%hold off;

save measCubli t u y %creating measTestName

process = 'Cubli';


%%

run mainest.m






