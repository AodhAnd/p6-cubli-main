%-------------------------------------------------------------------------%
%------------ ESTIMATION OF THE PARAMETERS OF THE FRAME ------------------%
%-------------------------------------------------------------------------%

clear all;
close all;
clc;

% If you have conflicting model paths, run this command
% close_system('CubliParameterEstimation')
% Warning: It will take longer, since it has to completely reload the model,
%         but you only have to run the command once

% Set documentation to 1 for best report-graph
% Set documentation to 0 for best run-time experience :)
documentation = 1;

%----- IMPORTING TEST-DATA ------------------------------------------------
testData = csvread('PRINT_03.CSV');% <-- simTime=3.75
t = (testData(:,1)'+5)';
Yvolt = testData(:,2);

%Data from Volt to radians
Vmin = 0.4708;    %   mean(voltage( 667:1243,1)) %voltage mean from 3.3 to 6.2 in time
Vmax = 0.9513;    %   mean(voltage(1336:2000,1)) %voltage mean from 6.7 to 10 in time
equVolt = 0.6945; %   mean(voltage(   1: 591,1)) %voltage mean from 0 to 2.9 in time
resRad = (1.5769)/(Vmax-Vmin);
Y = (Yvolt - equVolt)*resRad-0.005;

%----- SIMULATION ---------------------------------------------------------
stopI = 0;
isDone = 0;
u = zeros(size(Yvolt)); %<--vector of zeroes for simulation input
simIn = [ t u ];        %<--variables for simulation input

%----- CUBLI PARAMETERS ---------------------------------------------------
J_w=0.601e-3;
B_w=17.03e-6;
m_w=0.222;
l_w=0.093;
m_f=0.77-m_w;
l_f=0.08498;
g=9.82;

J_f= 0.00936;    %<---initial guess parameter
initJf = J_f;
B_f= 0.003505;   %<---initial guess parameter
initBf = B_f;

%------- PLOT OF TEST DATA ------------------------------------------------
% To reposition figure window:
% - Resize figure windows and place it on the screen as you wish
% - Type get(gcf, 'position') in the terminal
% - Insert new positions below
if documentation == 1
    fig1 = figure;%('Position', [412, 313, 660, 485]);
else
   fig1 = figure('Position', [1114 306 486 510]);%[-1022, -348, 576, 437]);
end

scatter(t,Y, 'r', '.')
grid on, grid minor;
title('Parameter Estimation of Cubli')
xlabel('Time (s)')
ylabel('Angular Position (rad)')
hold on
copyobj(gcf,0);
%---- PLOTTING PERFORMANCE/COST FUNCTION ----------------------------------

Jf    = csvread('J.csv');
Bf    = csvread('B.csv');
Cost1 = csvread('C.csv');

[ m, n ] = size(Jf);

map = csvread('mapHotRodRed.csv');

fig2 = figure;%('position', [2   304   560   512]);%[79   219   560   512]);
%mesh(Jf, Bf, Cost1, 'FaceColor', 'none');
mesh(Jf, Bf, Cost1, 'EdgeColor', 'none', 'FaceColor','interp');
hold on
alpha(1)
colormap(map);
axis([ 0 0.012 0 0.04 0 6e-3 ])

fig3 = figure;%('position', [558   305   559   511]);%[646   218   559   511]);
contourf(Jf, Bf, Cost1, 60, 'LineColor', '[ .6 0 0]', 'LineWidth', .001)
hold on
colormap(map);
axis([ 0 0.012 0 0.04])
    
% Minimum
[~, minColon ] = min(min(Cost1,[],1),[],2);
[~, minRow ] = min(Cost1(:,minColon),[],1);

figure(fig2);
mini = plot3( Jf(minRow,minColon),         ...
              Bf(minRow,minColon),         ...
              Cost1(minRow,minColon),      ...
              'o',                         ...
              'MarkerEdgeColor', '[0 0 0]',...
              'MarkerFaceColor', 'k',      ...
              'MarkerSize', 6 );

% Minimum found with Senstools
% sensToolP = evalCostFunction2(Y, t, 0.0048, 0.0077, J_f, B_f );
    
% sens = plot3( 0.0048, 0.0077, sensToolP,   ...
%               'o',                          ...
%               'MarkerEdgeColor', '[0 .7 0]',...
%               'MarkerFaceColor', '[0 .7 0]',...
%               'MarkerSize', 6 );

title('Cost Function')
xlabel('Frame inertia (J_F)')
ylabel('Frame friction (B_F)')
zlabel('Cost')

legend(mini, 'Minimum', 'location', 'northwest' )

% legend( [mini, sens],                         ...
%             {'Minimum', 'Senstools Result', },...
%             'location', 'northwest' )

drawnow
view([ -154.5000   26.0000 ])

figure(fig3);
mini = plot( Jf(minRow,minColon),         ...
             Bf(minRow,minColon),         ...
             'o',                         ...
             'MarkerEdgeColor', '[0 0 0]',...
             'MarkerFaceColor', 'k',      ...
             'MarkerSize', 6 );
    
% sens = plot( 0.0048, 0.0077,               ...
%              'o',                          ...
%              'MarkerEdgeColor', '[0 .7 0]',...
%              'MarkerFaceColor', '[0 .7 0]',...
%              'MarkerSize', 6 );

title('Contour of Cost Function')
xlabel('Frame inertia (J_F)')
ylabel('Frame friction (B_F)')
legend(mini, 'Minimum', 'location', 'northwest' )
% legend( [mini, sens],                     ...
%         {'Minimum', 'Senstools Result', },...
%         'location', 'northwest' )
drawnow


%--------- OPTIMIZATION ---------------------------------------------------

nrOfIterations = 100;         %|<--iterating only for the part needed
for i = 1:nrOfIterations      %|

    %----- SIMULATION OF CURRENT ITERATION --------------------------------
Ym = simCubli2( J_f, B_f, J_f, B_f );
    
%----- ERROR CALCULATION --------------------------------------------------
errn = sqrt(sum((Y-Ym).^2)/sum(Y.^2))*100;

%----- PERFORMANCE FUNCTION -----------------------------------------------
N = length(t); %<--setting N to degrees of freedom
Cost  = evalCostFunction2(Y, t, J_f, B_f, J_f, B_f);

%----- DISPLAY ACTUAL VALUES ----------------------------------------------
fprintf('---------------------------------------------------\n')
fprintf('\nJ_f = %4.4f\n',J_f);
fprintf('\nB_f = %4.4f\n',B_f);
fprintf('\nerrn = %4.4f\n',errn);
fprintf('\nCost = %4.4e\n',Cost);
fprintf('\n---------------------------------------------------\n')

%----- STOP THE OPTIMIZATION IF THE PERFORMANCE IS WRONG ------------------ 
if exist('CostOld', 'var')
    if Cost >= CostOld
        fprintf('---------------------------------------------------\n')
        fprintf('\nFinal estimation of the parameters\n');
        fprintf('\nJ_f = %4.4f\n',J_f_old);
        fprintf('\nB_f = %4.4f\n',B_f_old);
         fprintf('\n----------------------\n')       
        fprintf('\nerrn = %4.4f\n',errnOld);
        fprintf('\nCost = %4.4e\n',CostOld);
        fprintf('\n---------------------------------------------------\n')
        break;
    end
end

%----- PLOTTING THE RESULT OF EACH ITERATION ------------------------------
figure(fig1)
h = plot( t, Ym, 'linewidth', 1.2 );
if documentation == 1
    set(h, 'color', '[ .4 0 .6 ]');
end

if exist('hVeryOld', 'var')
    delete(hVeryOld);
end

if exist('hOld', 'var')
    if documentation == 1
        delete(hOld);
        legend('Test data', 'Estimation', 'Location', 'SouthEast')
    else
        hVeryOld = hOld;
        legend('Test data',            ...
               'Previous estimation',  ...
               'New estimation',       ...
               'Location', 'SouthEast')
    end
end

% Adding Normed RMS error label
if exist('tex', 'var')
    delete(tex);
end
if exist('errn', 'var')
    if documentation == 1
        errorSTR = ['Normed RMS Error = ', num2str(errn), ' %'];
    else
        errorSTR = ['Normed RMS Error  =  ', num2str(errn), ' %'];
    end
        tex = text(0.52, 0.13,        ...
               errorSTR,              ...
               'Color', '[ 0 .55 0 ]',...
               'FontSize', 12);
end

hOld = h;
drawnow;
copyobj(gcf,0);
%--------- STORING OLD VALUES ---------------------------------------------
if exist('errn', 'var')
    errnOld = errn; %<-- saving old error value for reference
end

if exist('Cost', 'var')
    CostOld = Cost; %<-- saving old preformance value for reference
end

if exist('J_f', 'var')
    J_f_old = J_f; %<-- saving old J_f value for reference
end

if exist('B_f', 'var')
    B_f_old = B_f; %<-- saving old B_f value for reference
end

%---- CALCULATING THE GRADIENT OF THE PERFORMANCE FUNCTION ----------------

% gradientOfP = 1/N  * ( Y - Ym ) * Ym' 
% Where:
%   Y      is the data recorded from test
%   Ym     is the model simulation output
%   Ym'    is the partial derivative of the simulated model with respect to
%          each of the parameters to be estimated.

% Problem:  We cannot directly differentiate the model since it is used
%          through simulation in Simulink
% Solution: Partial derivaties can be calculated nummericaly:

% In this case:
% parameters: J_f B_f
% Small magnitude deviation from these parameters is set
p = 0.01;
     
% Calculating the deviation
deltaJ_f = J_f+p*J_f;
deltaB_f = B_f+p*B_f;

% Running the simulation again, now with the deviating parameter J_f
% and storing the result of the simulation
deltaYmJf = simCubli2( deltaJ_f, B_f, J_f, B_f );

% Running the simulation again, now with the deviating parameter B_f
% and storring the result of the simulation
deltaYmBf = simCubli2( J_f, deltaB_f, J_f, B_f );

% Finally calculating the derivatives of the model
YmDiffBf = ( deltaYmBf - Ym )/ p;
YmDiffJf = ( deltaYmJf - Ym )/ p;

% This however is just for the model.. and we need
% the gradient of the preformance function as stated earlier:
% gradientOfP = 1/N  * ( Y - Ym ) * Ym'
gJf = -(1/N)* ((Y - Ym )'*YmDiffJf);
gBf = -(1/N)* ((Y - Ym )'*YmDiffBf);
        
if exist('a','var')
   if c <= initCost
      initJf = a;
      initBf = b;
      initCost  = c;
   end
else
   initCost  = evalCostFunction2(Y, t, initJf, initBf, J_f, B_f);
end

%---------- THE FORWARD-BACKWARD METHOD -----------------------------------
[ JFupper, BFupper ] = forwardBackwardCubli2( J_f, B_f, Y, t, gJf, gBf, fig2, fig3 );
    
Cost = evalCostFunction2(Y, t, J_f, B_f, J_f, B_f );

if (0) 
  figure(fig2)
  fPupper = evalCostFunction2(Y, t, JFupper, BFupper, J_f, B_f);
  plot3(JFupper, BFupper, fPupper, 'ok', ...
       'MarkerFaceColor', 'k',           ...
       'MarkerSize', 2)
  plot3(J_f, B_f, Cost, 'ok',           ...
        'MarkerFaceColor', 'k',           ...
         'MarkerSize', 2)
  v1 = [JFupper BFupper fPupper];
  v2 = [J_f B_f Cost];
  v = [v1; v2];
  plot3(v(:,1),v(:,2),v(:,3),'k', 'LineWidth', 1, 'LineStyle', ':')
end
    
%--------- FIBONACCI SEARCH -----------------------------------------------
[ a, b, isDone ] = fibonacciSearchCubli2(t, Y, J_f, B_f, initJf, initBf, JFupper, BFupper);
    
c = evalCostFunction2(Y, t, a, b, J_f, B_f);
figure(fig2)
if c <= initCost && isDone == 0
    plot3(a, b, c, 'o',                   ...
          'MarkerFaceColor', '[ 1 1 1  ]',...
          'Color', '[ 1 1 1  ]',          ...
          'MarkerSize', 1)
    v1 = [initJf initBf initCost];
    v2 = [a b c];
    v = [v1; v2];
    plot3(v(:,1),v(:,2),v(:,3),...
        'LineWidth', 1.2,      ...
        'Color', '[ 1 1 1 ]')
    
    figure(fig3)
    plot([initJf a], [initBf b], 'o',   ...
         'MarkerFaceColor', '[ 1 1 1 ]',...
         'Color', '[ 1 1 1 ]',          ...
         'MarkerSize', 1,               ...
         'LineWidth', 1.2,              ...
         'LineStyle', '-')

end



J_f = a;
B_f = b;
end
