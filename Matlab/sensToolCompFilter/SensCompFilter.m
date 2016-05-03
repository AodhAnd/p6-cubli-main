function [ fusedAngle ] = SensCompFilter( u, t, accel, gyro, tau)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

Q1 = (2*tau-0.01)/(2*tau+0.01);
Q2 = 0.01/(2*tau+0.01);

fusedAngle = zeros(numel(accel), 1);
fusedAngle(1) = 0;

for i = 2:1:numel(accel)
    %fusedAngle(i) = Q1*fusedAngle(i-1)+(0.4975e-2)*accAngle11(i)+(0.4975e-2)*gyroAngle11(i)+(0.4975e-2)*accAngle11(i-1)+(0.4975e-2)*gyroAngle11(i-1);
    fusedAngle(i) = Q1*fusedAngle(i-1) + Q2*(accel(i)+accel(i-1) + tau*gyro(i) + tau*gyro(i-1));
end

end

