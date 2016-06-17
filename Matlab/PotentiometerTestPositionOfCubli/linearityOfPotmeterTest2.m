clear all
close all
clc

degToRad = 2*pi/360;
radToDeg = 360/(2*pi);

angMesDeg = [ -41.7 -40 -38.5 -30 -20 -10 ((1.058)/2)-0.05 10 20 30 40 48.65 ]';

angMesRad = angMesDeg*degToRad;
                                                %  211.32
angPotVraw = [ 0.066 0.067 4.25 50.55 103.66 159.2 213.64 264.66 317.95 370.74 425.10 472.11 ]';

fig1 = figure;

%plotting data - leaving out the two first points (form dead-zone)
h1 = scatter(angMesDeg(3:12,1)-((1.058)/2), angPotVraw(3:12,1), 20, 'filled')
axis([ -50 50 -10 500 ])

%adding least square line:
hold on;
h2 = lsline;
set( h2, 'color', 'k', 'LineWidth', 1.4 );
h3 = scatter(angMesDeg(3:12,1)-((1.058)/2), angPotVraw(3:12,1), 20, 'filled', 'b')
h4 = scatter(angMesDeg(1:2,1), angPotVraw(1:2,1), 20, [ .6 0 .6 ], '*')

l1 = legend([h1 h2 h4],{'Reliable measurements', 'Least square line of reliable data', 'Unreliable measurements'}, 'location', 'SouthEast');
title('Linearity Test of Potentiometer')
xlabel('Degrees (^\circ)')
ylabel('Volt (mV)')

grid on, grid minor;

hold off;

fig2 = figure;
copyobj(get(fig1, 'children'),fig2);
hold on

stableRangeVolt  = [  211.8      217   ]'
stableRangeDeg   = [ 0.0894-((1.058)/2)    1.0582-((1.058)/2)  ]'

h5 = plot(stableRangeDeg, stableRangeVolt, 'r', 'LineWidth', 1.4)
h6 = scatter(stableRangeDeg, stableRangeVolt, 20, 'filled', 'k')

axis([ -.6 .6 210 218 ])

legend([ h5 h6 ], {'Outher balance points', 'Equlibrium range'}, 'location', 'southeast')

%setting new legend and title of zoomed figure

title('Zoom on Equlibrium Range')

grid on, grid minor;















