function [ gyroAngle ] = gyroIntegration(gyroData, delta_t)
%Function will integrate the entire gyro vector

temp = zeros(numel(gyroData), 1);
temp(1) = gyroData(1)*delta_t;
for i = 2:1:numel(gyroData)
    temp(i) = temp(i-1)+gyroData(i)*delta_t;
end

gyroAngle = temp;
end

