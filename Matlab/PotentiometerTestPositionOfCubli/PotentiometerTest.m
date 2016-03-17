%------------------- SETUP FOR FIGURE HOLD & CLEANUP ----------------------
for folding = true
    if ishandle(a)
        p = get(a, 'Position')
    end
    if ishandle(b)
        q = get(b, 'Position')
    end

    close all;
    clearvars -except p q
    clc;
end

%% ---------------------- READING DATA FROM FILE --------------------------

data = csvread('PRINT_12.CSV');

time = data(:,1)+4;  %making the time Possitive
voltage = data(:,2);

%% -------------------------- PLOTTING DATA -------------------------------

for folding = true
    if exist('p','var') == 1
        set(0, 'DefaultFigurePosition', p)
    end
end %<--setting figure position

a = figure;
plot(time, voltage, 'linewidth', 1.5);
hold on;

%---------------------- CALCULATING CONSTANT VALUES -----------------------

Vmin =    mean(voltage(1321:1601,1))  %voltage mean from 2.3 to 3.0 in time

Vmax =    mean(voltage(881 :1081,1))  %voltage mean from 1.2 to 1.7 in time

equVolt = mean(voltage(1   :601 ,1))  %voltage mean from -1 to 0.5 in time

middleVolt = ( (Vmax-Vmin)/2 ) +Vmin  %mid-range voltage

%---------------------- PLOTTING REFFERENCE LINES -------------------------

Ymin = zeros(size(voltage))+Vmin;
plot(time, Ymin,...
'linestyle', '--', 'linewidth', 1.2, 'color', '[ .2 .2 .2 ]');

Ymax = zeros(size(voltage))+Vmax;
plot(time, Ymax,...
'linestyle', '--', 'linewidth', 1.2, 'color', 'r');

Yequ = zeros(size(voltage))+equVolt;
plot(time, Yequ,...
'linestyle', '--', 'linewidth', 1.2, 'color', '[ 0 .6 0 ]');

Ymiddle = zeros(size(voltage))+middleVolt;
plot(time, Ymiddle,...
'linestyle', '--', 'linewidth', 1.2, 'color', '[ .6 0 .6 ]');

%---------------------------- PLOT SETTINGS -------------------------------

%limmiting the axes
ylim([-.1 .5])
xlim([ 0 3 ])

%title and axis labels added
title('Potentiometer Test')
xlabel('Time (s)')
ylabel('Voltage (V)')

%adding legend
legend('Angular movement in volt',...
       'Lower limmit',...
       'Upper limmit',...
       'Equlibrium point',...
       'Mid-range',...
       'Location', 'southwest' )

%setting grid style
grid on, grid minor;
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)

hold off;

%% ---------------------- FURTHER CALCULATIONS ----------------------------

%Prints out the voltage offset
offsetVolt = middleVolt-equVolt

%Calculating resolution for convertion to rad and deg:
resRad = (pi/2)/(Vmax-Vmin)
resDeg = 90/(Vmax-Vmin)

%Calculating 10 deg from equlibrium point on either side:
tenDegFromEquRight = (-10-3.7)/resDeg  +  middleVolt  % = 0.1651
tenDegFromEquLeft  = ( 10-3.7)/resDeg  +  middleVolt  % = 0.2679

%% ----------------------- GENERAL CONVERTION -----------------------------

%----- TO VOLTAGE ------------------------

%Degrees to Voltage                             % Remember to take the
%Volt = (inputDeg)/resDeg  +  middleVolt        % offset (3.7 deg) into
                                                % account (see graphs)
%Radians to Voltage
% Volt = (inputRad)/resRad  +  middleVolt


%----- TO ANGLE --------------------------

%Voltage to Degrees
% Deg = (inputVolt - middleVolt)*resDeg;

%Voltage to Radians
% Rad = (inputVolt - middleVolt)*resRad;


%% -------------------------- EXAMPLE USE ---------------------------------

rad = (data(:,2) - middleVolt)*resRad;
deg = (data(:,2) - middleVolt)*resDeg;


%% ---------------------- PLOTTING THE EXAMPLE ----------------------------

for folding = true 
    if exist('q','var') == 1
        set(0, 'DefaultFigurePosition', q)
    end
end %<--setting figure position

b = figure;
subplot(1,2,1)
plot(time,deg)
%setting grid style
grid on, grid minor;
set(gca,...
    'GridLineStyle',':',...
    'GridColor', 'k',...
    'GridAlpha', .6,...
    'YTick', (-50:5:50),...
    'XLim', [ -.5  4 ])
title('Degree Range of Cubli')
xlabel('Time (s)')
ylabel('Degrees (^\circ)')

hold on;%---------- PLOTTING REFFERENCE LINES -----------------------------

YminDeg = (Ymin - middleVolt) * resDeg;
plot(time, YminDeg,...
'linestyle', '--', 'linewidth', 1.2, 'color', '[ .2 .2 .2 ]');

YmaxDeg = (Ymax - middleVolt) * resDeg;
plot(time, YmaxDeg,...
'linestyle', '--', 'linewidth', 1.2, 'color', 'r');

YequDeg = (Yequ - middleVolt) * resDeg;
plot(time, YequDeg,...
'linestyle', '--', 'linewidth', 1.2, 'color', '[ 0 .6 0 ]');

YmiddleDeg = (Ymiddle - middleVolt) * resDeg;
plot(time, YmiddleDeg,...
'linestyle', '--', 'linewidth', 1.2, 'color', '[ .6 0 .6 ]');

hold off;%-----------------------------------------------------------------

subplot(1,2,2)
plot(time,rad)
%setting grid style
grid on, grid minor;
set(gca,...
    'GridLineStyle',':',...
    'GridColor', 'k',...
    'GridAlpha', .6,...
    'YTick', (-8:.1:8),...
    'YLim', [ -.9 .9 ],...
    'XLim', [ -.5  4 ])
title('Radian Range of Cubli')
xlabel('Time (s)')
ylabel('Radians (rad)')

hold on;%---------- PLOTTING REFFERENCE LINES -----------------------------

YminRad = (Ymin - middleVolt) * resRad;
plot(time, YminRad,...
'linestyle', '--', 'linewidth', 1.2, 'color', '[ .2 .2 .2 ]');

YmaxRad = (Ymax - middleVolt) * resRad;
plot(time, YmaxRad,...
'linestyle', '--', 'linewidth', 1.2, 'color', 'r');

YequRad = (Yequ - middleVolt) * resRad;
plot(time, YequRad,...
'linestyle', '--', 'linewidth', 1.2, 'color', '[ 0 .6 0 ]');

YmiddleRad = (Ymiddle - middleVolt) * resRad;
plot(time, YmiddleRad,...
'linestyle', '--', 'linewidth', 1.2, 'color', '[ .6 0 .6 ]');

hold off;%-----------------------------------------------------------------

set(groot,'DefaultFigurePosition','remove')%<--Resets default fig position