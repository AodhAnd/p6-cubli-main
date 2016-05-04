function [ angle ] = accToAngle(accX, accY )
%Function takes accelerometer data and convertes it to an angle
temp = accY./accX;
angle = atan(temp); 
end

