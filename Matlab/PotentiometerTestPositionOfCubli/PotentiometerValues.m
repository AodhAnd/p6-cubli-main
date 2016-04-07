
%---------------------- CALCULATING CONSTANT VALUES -----------------------

Vmin = 0.4708;%   mean(voltage( 667:1243,1)) %voltage mean from 3.3 to 6.2 in time

Vmax = 0.9513;%   mean(voltage(1336:2000,1)) %voltage mean from 6.7 to 10 in time

equVolt = 0.6945;%mean(voltage(   1: 591,1)) %voltage mean from 0 to 2.9 in time

middleVolt = ( (Vmax-Vmin)/2 ) +Vmin;  %mid-range voltage


%% ---------------------- FURTHER CALCULATIONS ----------------------------

%Prints out the voltage offset
offsetVolt = middleVolt-equVolt;

%Calculating resolution for convertion to rad and deg:
resRad = (1.5769)/(Vmax-Vmin);
resDeg = 90.35/(Vmax-Vmin);

%Calculating 10 deg from equlibrium point on either side:
tenDegFromEquRight = (-10-3.7)/resDeg  +  equVolt;  % = 0.1651
tenDegFromEquLeft  = ( 10-3.7)/resDeg  +  equVolt;  % = 0.2679

%% ----------------------- GENERAL CONVERTION -----------------------------

%----- TO VOLTAGE ------------------------

%Degrees to Voltage                             % Remember to take the
%Volt = (inputDeg)/resDeg  +  equVolt        % offset (3.7 deg) into
                                                % account (see graphs)
%Radians to Voltage
% Volt = (inputRad)/resRad  +  equVolt


%----- TO ANGLE --------------------------

%Voltage to Degrees
% Deg = (inputVolt - equVolt)*resDeg;

%Voltage to Radians
% Rad = (inputVolt - equVolt)*resRad;


%% -------------------------- EXAMPLE USE ---------------------------------

rad = (data(:,2) - equVolt)*resRad;
deg = (data(:,2) - equVolt)*resDeg;
