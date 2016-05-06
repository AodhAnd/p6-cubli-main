close all, clc
%% Aleternate method to discretizize the complementary function
accAngle12offset = accAngle12 + 0.785398163;
%accAngle21offset = accAngle21 - 0.785398163;
%%
K = 0.2;
C = 0.95;

Q1 = (2*K-0.01)/(2*K+0.01)
Q2 = 0.01/(2*K+0.01)

fusedAngle = zeros(numel(accAngle12), 1);

fusedAngle(1) = 0;%Q2*(accAngle11(i) + gyroAngle11(i));

for i = 2:1:numel(accAngle12)
    %fusedAngle(i) = Q1*fusedAngle(i-1)+(0.4975e-2)*accAngle11(i)+(0.4975e-2)*gyroAngle11(i)+(0.4975e-2)*accAngle11(i-1)+(0.4975e-2)*gyroAngle11(i-1);
    fusedAngle(i) = Q1*fusedAngle(i-1) + Q2*(accAngle12offset(i)+accAngle12offset(i-1) + K*gyroAngle12(i) + K*gyroAngle12(i-1));
end

fusedAngle2 = complementaryFilter(C, 0.01, accAngle12offset, gyroAngle12);

figure
plot(time2, fusedAngle, time2, potRad2)
grid on, grid minor

figure
plot(time2, fusedAngle2, time2, potRad2)
grid on, grid minor