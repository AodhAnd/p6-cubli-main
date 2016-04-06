%------------------- SETUP FOR FIGURE HOLD & CLEANUP ----------------------
for folding = true
    if exist('a','var') == 1
        if ishandle(a)
            p = get(a, 'Position')
        end
    end
    if exist('b','var') == 1
        if ishandle(b)
        q = get(b, 'Position')
        end
    end

    close all;
    clearvars -except p q
    clc;
end

%% ---------------------- READING DATA FROM FILE --------------------------

data = csvread('PRINT_04.CSV');
data2 = csvread('potResTest3.csv');

time = data(:,1)+5;  %making the time Possitive
voltage = data(:,2);

time2 = data2(:,1)*0.010 -.63; %10 ms per tick (& alligning with volt data)
ADCval = data2(:,2);

%% -------------------------- PLOTTING DATA -------------------------------

for folding = true
    if exist('p','var') == 1
        set(0, 'DefaultFigurePosition', p)
    end
end %<--setting figure position

a = figure;
[AAX, volt, ADC] = plotyy(time,voltage,time2,ADCval)

%% -------------------- CALCULATING CONSTANT VALUES -----------------------

Vmin =    mean(voltage( 753:1241,1)) %voltage mean from 1.88 to 3.1 in time

Vmax =    mean(voltage(1569:2000,1)) %voltage mean from 3.92 to 10 in time

equVolt = mean(voltage(   1: 493,1)) %voltage mean from 0 to 1.23 in time

middleVolt = ( (Vmax-Vmin)/2 ) +Vmin  %mid-range voltage

%---------------------- PLOTTING REFFERENCE LINES -------------------------

hold on;

Ymin = zeros(size(voltage))+Vmin;
plot(AAX(1), time, Ymin,...
'linestyle', '--', 'linewidth', 1.2, 'color', '[ .2 .2 .2 ]');

Ymax = zeros(size(voltage))+Vmax;
plot(AAX(1), time, Ymax,...
'linestyle', '--', 'linewidth', 1.2, 'color', 'r');

Yequ = zeros(size(voltage))+equVolt;
plot(AAX(1), time, Yequ,...
'linestyle', '--', 'linewidth', 1.2, 'color', '[ 0 .6 0 ]');

Ymiddle = zeros(size(voltage))+middleVolt;
plot(AAX(1), time, Ymiddle,...
'linestyle', '--', 'linewidth', 1.2, 'color', '[ .6 0 .6 ]');

%% ------------------------ PLOT SETTINGS ---------------------------------

set(volt, 'LineWidth', 1.4 )
set(ADC, 'LineWidth', 1.4 )

%setting options for radian axis
set(AAX(1),...
    'Xgrid', 'on',...
    'Ygrid', 'on',...
    'XMinorGrid', 'on',...
    'YMinorGrid', 'on',...
    'ytick', (0:.1:.5),...
    'YLim', [ -.02 .5 ],...                   <-- Crummy allignment of
    'XLim', [ 0  5 ],...                          the two graphs, by
    'GridLineStyle',':',...                       moving the radian graph
    'GridColor', 'k',...
    'GridAlpha', .6)

%turning off degree plot since it is now alligned with the radian plot
set(ADC,'Visible','off')
 
%setting options for degree axis
set(AAX(2),...
    'Xgrid', 'off',...
    'Ygrid', 'off',...
    'XMinorGrid', 'off',...
    'YMinorGrid', 'off',...
    'ytick', ( 0:200:1600),...
    'YLim', [ -60 1500 ],...
    'XLim', [ 0  5 ],...
    'GridLineStyle', ':',...
    'GridColor', 'k',...
    'GridAlpha', .6)

%adding title and axes labels
title('Potentiometer Range')
xlabel('Time (s)')
ylabel(AAX(1), 'Voltage (V)')
ylabel(AAX(2), 'ADC Values')

legend('Angular movement',...
       'Lower limmit',...
       'Upper limmit',...
       'Equlibrium point',...
       'Mid-range',...
       'Location', 'northwest' )

hold off;

%% ---------------------- FURTHER CALCULATIONS ----------------------------

%Prints out the voltage offset
offsetVolt = middleVolt-equVolt

%Calculating resolution for convertion to rad and deg:
resRad = (1.5769)/(Vmax-Vmin)
resDeg = 90.35/(Vmax-Vmin)

%Calculating 10 deg from equlibrium point on either side:
tenDegFromEquRight = (-10-3.7)/resDeg  +  equVolt  % = 0.1651
tenDegFromEquLeft  = ( 10-3.7)/resDeg  +  equVolt  % = 0.2679

%% ----------------------- GENERAL CONVERTION -----------------------------

%----- TO VOLTAGE ------------------------

%Degrees to Voltage
%Volt = (inputDeg)/resDeg  +  equVolt

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


%% ---------------------- PLOTTING THE EXAMPLE ----------------------------

for folding = true 
    if exist('q','var') == 1
        set(0, 'DefaultFigurePosition', q)
    end
end %<--setting figure position

b = figure;
[AX, rad1, deg1] = plotyy(time,rad,time,deg)

hold on;%------------ PLOTTING REFFERENCE LINES ---------------------------

YminRad = (Ymin - equVolt) * resRad;
plot(AX(1), time, YminRad,...
'linestyle', '--', 'linewidth', 1.2, 'color', '[ .2 .2 .2 ]');

YmaxRad = (Ymax - equVolt) * resRad;
plot(AX(1), time, YmaxRad,...
'linestyle', '--', 'linewidth', 1.2, 'color', 'r');

YequRad = (Yequ - equVolt) * resRad;
plot(AX(1), time, YequRad,...
'linestyle', '--', 'linewidth', 1.2, 'color', '[ 0 .6 0 ]');

YmiddleRad = (Ymiddle - equVolt) * resRad;
plot(AX(1), time, YmiddleRad,...
'linestyle', '--', 'linewidth', 1.2, 'color', '[ .6 0 .6 ]');

hold off;%-----------------------------------------------------------------

%% ----------------------- PLOT SETTINGS ----------------------------------

set(rad1,'LineWidth', 1.4 )

%setting options for radian axis
set(AX(1),...
    'Xgrid', 'on',...
    'Ygrid', 'on',...
    'XMinorGrid', 'on',...
    'YMinorGrid', 'on',...
    'ytick', (-.9:.1:.9),...
    'YLim', [ -.785395694 .95992832 ],...     <-- Crummy allignment of
    'XLim', [ 0  5 ],...                          the two graphs, by
    'GridLineStyle',':',...                       moving the radian graph
    'GridColor', 'k',...
    'GridAlpha', .6)

%turning off degree plot since it is now alligned with the radian plot
set(deg1,'Visible','off')

%setting options for degree axis
set(AX(2),...
    'Xgrid', 'off',...
    'Ygrid', 'off',...
    'XMinorGrid', 'off',...
    'YMinorGrid', 'off',...
    'ytick', (-50:5:50),...
    'YLim', [ -45 55 ],...
    'XLim', [ 0  5 ],...
    'GridLineStyle', ':',...
    'GridColor', 'k',...
    'GridAlpha', .6)

%adding title and axes labels
title('Angle Range of Cubli')
xlabel('Time (s)')
ylabel(AX(1), 'Radians (rad)')
ylabel(AX(2), 'Degrees (^\circ)')

%adding legend
legend('Angular movement',...
       'Lower limmit',...
       'Upper limmit',...
       'Equlibrium point',...
       'Mid-range',...
       'Location', 'northwest' )



set(groot,'DefaultFigurePosition','remove')%<--Resets default fig positions