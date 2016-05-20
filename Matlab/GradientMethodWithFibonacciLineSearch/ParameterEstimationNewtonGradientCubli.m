clear all
close all
clc
%If you have conflicting model paths, run this command
%close_system('CubliParameterEstimation')
%Warning: It will take longer, since it has to completely reload the model,
%         but you only have to run the command once

%set documentation to 1 for best report-graph
%set documentation to 0 for best run-time experience :)
documentation = 0;

%----- IMPORTING TEST-DATA ------------------------------------------------
testData = csvread('PRINT_03.CSV');%, 0, 0, [0 0 1500 1]);% <-- simTime=3.75
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
%Defining Cubli parameters
T_m=0.005;
K=0.5;
J_w=0.601e-3;
J_f= 0.00936;   %0.8e-3;    %2.8e-3   <---initial guess parameter
initJf = J_f;
B_w=17.03e-6;
B_f= 0.003505;   %6.08e-3;   %6.08e-3  <---initial guess parameter
initBf = B_f;
m_w=0.222;
m_f=0.77-m_w;%0.354;
g=9.82;
l_w=0.093;
l_f=0.08498;%0.076;

u = zeros(size(Yvolt));  %<--vector of zeroes for simulation input
simIn = [ t u ];        %<--variables for simulation input

%Plot the test-data for refference
%To reposition figure window:
% - Resize figure windows and place it on the screen as you wish
% - Type get(gcf, 'position') in the terminal
% - Insert new positions below
if documentation == 1
    fig1 = figure;%('Position', [412, 313, 660, 485]);
else
   %fig1 = figure('Position', [277, 84, 1049, 700])
   %fig1 = figure('Position', [2,   32,  798, 784])
   fig1 = figure;%('Position', [-1022, -348, 576, 437]);
end

scatter(t,Y, 'r', '.')
grid on, grid minor;
title('Parameter Estimation of Cubli')
xlabel('Time (s)')
ylabel('Angle (rad)')
hold on

nrOfIterations = 100;         %|<--iterating only for the part needed
for i = 1:nrOfIterations     %|

%----- SIMULATION OF CURRENT ITERATION ------------------------------------
    
    Ym = simCubli( J_f, B_f, J_f, B_f );
    
%--------------------------------------------------------------------------

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

%Adding Normed RMS error label
if exist('tex', 'var')
    delete(tex);
end
if exist('errn', 'var')
    if documentation == 1
        errorSTR = ['Normed RMS error = ', num2str(errn), ' %'];
    else
        errorSTR = ['Normed RMS error  =  ', num2str(errn), ' %'];
    end
        tex = text(0.52, 0.13,        ...
               errorSTR,              ...
               'Color', '[ 0 .55 0 ]',...
               'FontSize', 12);
end

hOld = h;
drawnow;

%----- storing old values -------------------------------------------------
%error function
errn = sqrt(sum((Y-Ym).^2)/sum(Y.^2))*100;

if exist('errn', 'var')
    errnOld = errn; %<-- saving old error value for refference
end

if exist('Pval', 'var')
    PvalOld = Pval; %<-- saving old preformance value for refference
end

N = length(t); %<--setting N to degrees of freedom
% 
% %----- PERFORMANCE FUNCTION -----------------------------------------------
% %N = length(Y); %<--setting N to degrees of freedom
% %Pval = (1/(2*N))*sum( ((Y-Ym).^2) );
% P = (Y-Ym).^2;
% Pval = (1/(2*N))*sum(P) %<-- calculating new preformance value
% %--------------------------------------------------------------------------

Pval  = evalCostFunction(Y, t, J_f, B_f, J_f, B_f);

%----- Jump back to previous point if the performance is worse ------------
if exist('PvalOld', 'var')
    if Pval >= PvalOld
        J_f = J_f_old;
        B_f = B_f_old;
        break;
    end
end
%--------------------------------------------------------------------------

%----- PLOTTING PERFORMANCE/COST FUNCTION ---------------------------------

if i == 1
    Jf    = csvread('J.csv');
    Bf    = csvread('B.csv');
    Pval1 = csvread('C.csv');

    [ m, n ] = size(Jf);

    map = csvread('mapHotRodRed.csv');

    fig2 = figure;%('position', [-1022, 175, 576, 641]); %2    32   798   784
    mesh(Jf, Bf, Pval1, 'FaceColor', 'none');
    hold on
    alpha(0.8)
    colormap(map);
    %colorbar
    set(gca, 'view', [-177.5000   90.0000]); %-176.5000   30.0000 %194.5000   32.0000  %154.5000 16.0000

    %axis([ 0.00144 0.014     0.000505 0.02551     0 6e-3 ])
    
    %Minimum
    [minP, minColon ] = min(min(Pval1,[],1),[],2);
    [minP, minRow ] = min(Pval1(:,minColon),[],1);
    
    mini = plot3( Jf(minRow,minColon),         ...
                  Bf(minRow,minColon),         ...
                  Pval1(minRow,minColon),...
                  'o',                         ...
                  'MarkerEdgeColor', '[0 0 0]',...
                  'MarkerFaceColor', 'k',      ...
                  'MarkerSize', 6 );

    %SensTool finds this minimum
    sensToolP = evalCostFunction(Y, t, 0.0048, 0.0077, J_f, B_f );
    
    sens = plot3( 0.0048, 0.0077, sensToolP    ,...
                  'o',                          ...
                  'MarkerEdgeColor', '[0 .7 0]',...
                  'MarkerFaceColor', '[0 .7 0]',...
                  'MarkerSize', 6 );

    %Our own algorithm finds this
    ownP = evalCostFunction(Y, t, 0.0048, 0.0060, J_f, B_f );
    
    own = plot3( 0.0048, 0.0060, ownP         ,...
                 'o',                          ...
                 'MarkerEdgeColor', '[0 0 .9]',...
                 'MarkerFaceColor', '[0 0 .9]',...
                 'MarkerSize', 6 );

    title('Cost Function')
    xlabel('Frame inertia (J_F)')
    ylabel('Frame friction (B_F)')
    zlabel('Cost')

    legend( [mini, sens, own],                                   ...
            {'Minimum', 'Senstools Result', 'Own Implementation'},...
            'location', 'northwest' )

    drawnow

end

% if i >= 2    
%     title('Cost Function')
%     xlabel('Frame inertia (J_F)')
%     ylabel('Frame friction (B_F)')
%     zlabel('Cost')
% 
%      legend( [mini, sens, own],                                   ...
%              {'Minimum', 'Simulink Result', 'Own Implementation'},...
%              'location', 'northwest' )
% end

%--------------------------------------------------------------------------

%---- CALCULATING THE GRADIENT OF THE PERFORMANCE FUNCTION ----------------

%gradientOfP = 1/N  * sumFrom1toN( ( Y - Ym ) * Ym' )
%where:
%   Y      is the data recorded from test
%   Ym     is the model simulation output
%   Ym'    is the partial derivative of the simulated model with respect to
%          each of the parameters to be estimated.

%Problem:  We cannot directly differentiate the model since it is used
%          through simulation in Simulink
%Solution: Partial derivaties can be calculated nummericaly:

%In this case:
%parameters: J_f B_f
%small magnitude deviation from these parameters is set
p = 0.01;
     
%calculating the deviation
deltaJ_f = J_f+p*J_f;
deltaB_f = B_f+p*B_f;

%running the simulation again, now with the deviating parameter J_f
%and storring the result of the simulation
deltaYmJf = simCubli( deltaJ_f, B_f, J_f, B_f );

%running the simulation again, now with the deviating parameter B_f
%and storring the result of the simulation
deltaYmBf = simCubli( J_f, deltaB_f, J_f, B_f );

%finally calculating the derivatives of the model
YmDiffBf = ( deltaYmBf - Ym )/ p;
YmDiffJf = ( deltaYmJf - Ym )/ p;

%this however is just for the model.. and we need
%the gradient of the preformance function as stated earlier:
%gradientOfP = 1/N  * sumFrom1toN( ( Y - Ym ) * Ym' )
gJf = -(1/N)* sum((Y - Ym ).*YmDiffJf);
gBf = -(1/N)* sum((Y - Ym ).*YmDiffBf);

% %IF YOU SHOULD WANT TO PLOT THE GRADIENT
% gradJF = J_f-gJf;
% gradBF = B_f-gBf;
% 
% figure(fig2)
% gradP = evalCostFunction(Y, t, gradJF, gradBF, J_f, B_f);
% plot3(J_f, B_f, Pval, 'or',           ...
%              'MarkerFaceColor', 'r',  ...
%              'MarkerSize', 4)
% plot3(gradJF, gradBF, gradP, 'or',    ...
%              'MarkerFaceColor', 'b',  ...
%              'MarkerSize', 4)
% v1 = [J_f B_f Pval];
% v2 = [gradJF gradBF gradP];
% v = [v1; v2];
% plot3(v(:,1),v(:,2),v(:,3),'r', 'LineWidth', 1, 'LineStyle', ':')

J_f_old = J_f;
B_f_old = B_f;



    Pval = evalCostFunction(Y, t, J_f, B_f, J_f, B_f );

    Ym = simCubli( J_f, B_f, J_f, B_f );

    deltaJ_f = J_f+p*J_f;
    deltaB_f = B_f+p*B_f;

    deltaYmJf = simCubli( deltaJ_f, B_f, J_f, B_f );
    deltaYmBf = simCubli( J_f, deltaB_f, J_f, B_f );

    YmDiffBf = ( deltaYmBf - Ym )/ p;
    YmDiffJf = ( deltaYmJf - Ym )/ p;

    gJf = -(1/N)* ((Y - Ym )'*YmDiffJf);
    gBf = -(1/N)* ((Y - Ym )'*YmDiffBf);
    
    %Calculating hessian
    
    
    G = [ gJf gBf ]';
    
%      HJJf = (1/N) * (YmDiffJf'*YmDiffJf);
%      HJBf = (1/N) * (YmDiffJf'*YmDiffBf);
%      HBJf = (1/N) * (YmDiffBf'*YmDiffJf);
%      HBBf = (1/N) * (YmDiffBf'*YmDiffBf);
%      
%      H = [ HJJf  HJBf
%            HBJf  HBBf  ];
%      
%      theta = [ J_f B_f ]';
%      
%      
%      if (theta' * H * theta) > 0%<-- if H is positive definite in the 
%                                      %    current point, then we assume that
%                                      %    it is positive definite in the
%                                      %    neiborhood of the minimum.
%         posDef = 1;
%      else
%          posDef = 0;
%      end
%        
%      if posDef && i >= 6     
% 
%          detH = H(1,1)*H(2,2)-H(2,1)*H(1,2);
% 
%          invH = (1/detH)*[  H(2,2) -H(1,2)
%                            -H(2,1)  H(1,1) ]
% 
% 
% 
%         %figure;
%         %plot(t,P)
%         %hold on;
%         %plot(t,YmDiff)
% 
%         theta = theta -invH * G;
% 
%         J_f = theta(1);
%         B_f = theta(2);
% 
%         %calculate the new parameters
%         %J_f = J_f-gJf*s
%         %B_f = B_f-gBf*s*.1
%         %J_f = J_f-invH(1,1)*gJf-invH(1,2)*gBf
%         %B_f = B_f-invH(2,1)*gJf-invH(2,2)*gBf%*.01%<--the *.01 is an attempt to counter the too
%                                   %   high sensitivity of the parameter.
%                                   %   There exists a more beautifull method
%                                   %   for determining sensitivity
%         Pval = evalCostFunction(Y, t, J_f, B_f, J_f, B_f );
%         %----------------------------------------------------------------------
% 
%         figure(fig2)
%         plot3(J_f, B_f, Pval, 'ok', ...
%                      'MarkerFaceColor', 'k',           ...
%                      'MarkerSize', 2)
%               v1 = [J_f B_f Pval];
%               v2 = [J_f_old B_f_old PvalOld];
%               v = [v1; v2];
%         plot3(v(:,1),v(:,2),v(:,3),'k', 'LineWidth', 2, 'LineStyle', '-')
%      elseif posDef == 0 || i <6









    

%if isDone == 0;
    %----- STEEPEST DESCEND WITH FIBONACCI LINE SEARCH --------------------

%     while isDone == 0
%         %----- CALCULATING THE GRADIENT ---------------------------------------
%         Pval = evalCostFunction(Y, t, J_f, B_f, J_f, B_f );
%         
%         Ym = simCubli( J_f, B_f, J_f, B_f );
%         
%         deltaJ_f = J_f+p*J_f;
%         deltaB_f = B_f+p*B_f;
% 
%         deltaYmJf = simCubli( deltaJ_f, B_f, J_f, B_f );
%         deltaYmBf = simCubli( J_f, deltaB_f, J_f, B_f );
% 
%         YmDiffBf = ( deltaYmBf - Ym )/ p;
%         YmDiffJf = ( deltaYmJf - Ym )/ p;
% 
%         gJf = -(1/N)* sum((Y - Ym ).*YmDiffJf);
%         gBf = -(1/N)* sum((Y - Ym ).*YmDiffBf);
        
%         %IF YOU SHOULD WANT TO PLOT THE GRADIENT
%         gradJF = J_f-gJf;
%         gradBF = B_f-gBf;
%         
%         figure(fig2)
%         gradP = evalCostFunction(Y, t, gradJF, gradBF, J_f, B_f);
%         plot3(J_f, B_f, Pval, 'or',           ...
%                      'MarkerFaceColor', 'r',  ...
%                      'MarkerSize', 4)
%         plot3(gradJF, gradBF, gradP, 'or',    ...
%                      'MarkerFaceColor', 'b',  ...
%                      'MarkerSize', 4)
%         v1 = [J_f B_f Pval];
%         v2 = [gradJF gradBF gradP];
%         v = [v1; v2];
%         plot3(v(:,1),v(:,2),v(:,3),'r', 'LineWidth', 1, 'LineStyle', ':')
        
        %----------------------------------------------------------------------
        
    if exist('a','var')
        if c <= initPval
            initJf = a;
            initBf = b;
            initPval  = c;
        end
    else
        initPval  = evalCostFunction(Y, t, initJf, initBf, J_f, B_f);
%         figure(fig2);
%         initJf
%         initBf
%         initPval
%         plot3(initJf, initBf, initPval, 'ob', 'MarkerFaceColor', 'b', 'MarkerSize', 8)
%         drawnow;
    end

    % gradient is then:   g = [ gJf
    %                           gBf ]

    %------ The Forward-Backward Method -----------------------------------
    [ JFupper, BFupper ] = forwardBackward( J_f, B_f, Y, t, gJf, gBf, fig2 );
    
    Pval = evalCostFunction(Y, t, J_f, B_f, J_f, B_f );
    
    if 1 %plotRange == 
        figure(fig2)
        fPupper = evalCostFunction(Y, t, JFupper, BFupper, J_f, B_f);
        plot3(JFupper, BFupper, fPupper, 'ok', ...
             'MarkerFaceColor', 'k',           ...
             'MarkerSize', 2)
         plot3(J_f, B_f, Pval, 'ok',           ...
             'MarkerFaceColor', 'k',           ...
             'MarkerSize', 2)
        v1 = [JFupper BFupper fPupper];
        v2 = [J_f B_f Pval];
        v = [v1; v2];
        plot3(v(:,1),v(:,2),v(:,3),'k', 'LineWidth', 1, 'LineStyle', ':')
    end
    
    % bracket = [ (J_f, B_f) ; (JFupper BFupper) ]

    %----- FIBONACCI SEARCH -----------------------------------------------
    fprintf('\n\nfibonacciSearch Started\n\n')
    [ a, b, isDone ] = fibonacciSearchCubli(t, Y, J_f, B_f, initJf, initBf, JFupper, BFupper);
    
    c = evalCostFunction(Y, t, a, b, J_f, B_f);
    figure(fig2)
    if c <= initPval && isDone == 0
        plot3(a, b, c, 'ob', 'MarkerFaceColor', 'b', 'MarkerSize', 2)
        v1 = [initJf initBf initPval];
        v2 = [a b c];
        v = [v1; v2];
        plot3(v(:,1),v(:,2),v(:,3),'b', 'LineWidth', 1.4)
    end
    fprintf('\n\n---------------------------------------------------\n\n')
    J_f = a
    B_f = b
    fprintf('\n\n---------------------------------------------------\n\n')
    drawnow;

    %----------------------------------------------------------------------
%elseif isDone == 1;
    %----- NEWTON METHOD --------------------------------------------------
    
    
    %----- CALCULATING THE GRADIENT ---------------------------------------
    
%     J_f = J_f_old;
%     B_f = B_f_old;

    %end
errn
Pval
end


% plot3(J_f, B_f, Pval, 'ob',  ...
%       'MarkerFaceColor', 'b',...
%       'MarkerSize', 3)
%   
%   plot3(deltaJ_f, deltaB_f, Pval, 'or',  ...
%       'MarkerFaceColor', 'r',...
%       'MarkerSize', 3)
%   pause(10)