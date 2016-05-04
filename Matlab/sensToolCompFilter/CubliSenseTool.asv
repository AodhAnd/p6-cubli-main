clear all
close all
clc
%%
[count, potADC, accX1, accY1, accX2, accY2, gyroRads1, gyroRads2] = ImportIMU('sensorstestwSimon3.csv');
delta_T = 0.01;

tau = 0.01;
%C = 0.98;
%% Change value accordint to data file
% for file sensorstestwSimon1 q = 3500
% for file sensorstestwSimon2 q = 1600
% for file sensorstestwSimon3 q = 4500
% for file sensorstestwSimon4 q = 2050
q = 4500;

count = count(1:q,:);
potADC = potADC(1:q,:);
accX1 = accX1(1:q,:);
accY1 = accY1(1:q,:);
accX2 = accX2(1:q,:);
accY2 = accY2(1:q,:);
gyroRads1 = gyroRads1(1:q,:);
gyroRads2 = gyroRads2(1:q,:);

ADCmin = 2.3893;
ADCmax = 1.4113e+03;
ADCequ = 640.5645;
resRadADC = (1.5769)/(ADCmax-ADCmin);   % calculates the resolution of the ADC for the potmeter

potRad = (potADC-ADCequ) * resRadADC;   % set up so pot has 0 when cubli is upright

%% get angle from accel measurements
accAngle1 = accToAngle(accX1, accY1);
gyroAngle1 = gyroIntegration(gyroRads1, delta_T);

%accAngle1offset = accAngle1 + 0.785398163;
accAngle1offset = accAngle1 + 0.82
% %%
% accAngle1roll = zeros(numel(count), 1);
% accAngle1roll(1:7,1) = accAngle1offset(1:7,1);
% for k = 8:1:numel(count)
% accAngle1roll(k) = (accAngle1offset(k) + accAngle1offset(k-1) + accAngle1offset(k-2)+ accAngle1offset(k-3)+accAngle1offset(k-4) + accAngle1offset(k-5) + accAngle1offset(k-6)+ accAngle1offset(k-7))/8;
% end
%%
%for the last part of the signal:
t = count*delta_T;

u = [accAngle1offset, gyroAngle1];
% u = [accAngle1roll, gyroAngle1];
uin = [ t u ];

y = potRad;

scatter(t',y)

%%

par0 = [tau];% m_f l_f ];

Ynew = simSensToolCompFilter(u,t,par0);

save measSensToolCompFilter t u y %creating measTestName

process = 'SensToolCompFilter';

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

%% ADDON
% rolling average thing
fused = Ynew';

fusedRoll = zeros(numel(count), 1);
fusedRoll(1:15,1) = fused(1:15,1);
for k = 16:1:numel(count)
fusedRoll(k) = (sum(fused(k-(0:15))))/(16);
end

figure
plot(t', fusedRoll, t, potRad), grid on, grid minor;