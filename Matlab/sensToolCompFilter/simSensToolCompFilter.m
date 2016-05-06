function [ fusedAngle ] = simSensToolCompFilter( u, t, par)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

assignin('base', 'tau', par(1));

Q1 = (2*par-0.01)/(2*par+0.01);
Q2 = 0.01/(2*par+0.01);

fusedAngle = zeros(numel(t), 1);
fusedAngle(1) = 0.5 * u(1,1) + 0.5*u(1,2)*0.01;

    for i = 2:1:numel(t)
        fusedAngle(i) = Q1*fusedAngle(i-1) + Q2*(u((i),1)+u((i-1),1) + par*u((i),2) + par*u((i-1),2));
    end

end

