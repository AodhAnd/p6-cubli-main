close all, clc
%% plotting of the complementary
%dataToPicture(time1, accAngle11, accAngle21, potRad1, 'Accelerotemer angle from IMU nr. 1', 'Accelerotemer angle from IMU nr. 2');

%dataToPicture(time1, gyroAngle11, gyroAngle21, potRad1, 'Gyroscope angle from IMU nr. 1', 'Gyroscope angle from IMU nr. 2');

%% trying to correct the offset

accAngle14offset = accAngle14 + 0.785398163;
accAngle24offset = accAngle24 - 0.785398163;

C = 0.94;
%% Rolling Average for accel data
accAngle14offsetfilter = zeroes(numel(time4));

for i =1:1:3
accAngle14offsetfilter(i) = accAngle14offset(i);
end

for i = 4:1:numel(accel)
    accAngle14offsetFilter = accAngle14offset
end


%% THE COMPLEMTARY FILTER

fusedAngle1 = complementaryFilter(C, delta_T, accAngle14offset, gyroAngle14);
fusedAngle2 = complementaryFilter(C, delta_T, accAngle24offset, gyroAngle24);

% %sensor 1
% fusedAngle1(1) = C*gyroAngle11(1)*delta_T + (1-C)*accAngle11offset(1);
% 
% for i = 2:1:numel(time1)
%     fusedAngle1(i) = C*(fusedAngle1(i-1)+gyroAngle11(i)*delta_T)+(1-C)*accAngle11offset(i);
% end
% 
% %sensor2
% fusedAngle2(1) = C*gyroAngle21(1)*delta_T + (1-C)*accAngle21offset(1);
% 
% for i = 2:1:numel(time1)
%     fusedAngle2(i) = C*(fusedAngle2(i-1)+gyroAngle21(i)*delta_T)+(1-C)*accAngle21offset(i);
% end

%% PLOT THAT DATA

% dataToPicture(time4, accAngle14, accAngle24, potRad4, '1','2');
dataToPicture(time4, accAngle14offset, accAngle24offset, potRad4, '1','2');
% dataToPicture(time4, gyroAngle14, gyroAngle24, potRad4, '1', '2')
dataToPicture(time4, fusedAngle1, fusedAngle2, potRad4, 'Fusion from IMU nr. 1', 'Fusion from IMU nr. 2');

combineGyro = 0.5*gyroAngle14 + 0.5*gyroAngle24;
combineAccel = 0.5*accAngle14offset + 0.5*accAngle24offset;

combine = complementaryFilter(C, delta_T, combineAccel, combineGyro);

combine2 = 0.5*fusedAngle1 + 0.5*fusedAngle2;

dataToPicture(time4, combine, combine2, potRad4, 'Fused Raw data', 'Fused filter data')

