clear all
close all
clc

%set documentation to 1 for best report-graph
%set documentation to 0 for best run-time experience :)
documentation = 1;

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

%Defining Cubli parameters
T_m=0.005;
K=0.5;
J_w=0.601e-3;
J_f=0.8e-3;    %2.8e-3   <---initial guess parameter
B_w=17.03e-6;
B_f=6.08e-3;   %6.08e-3  <---initial guess parameter
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
    figure('Position', [412, 313, 660, 485])
else
    figure('Position', [300, 50, 1049, 700])
end

scatter(t,Y, 'r', '.')
grid on, grid minor;
title('Parameter Estimation of Cubli')
xlabel('Time (s)')
ylabel('Angle (rad)')
hold on

%s = .0005; %<-- setting initial stepsize for steepest descent method

nrOfIterations = 23;         %|<--iterating only for the part needed
for i = 1:nrOfIterations     %|

clear('simOut')
%simulating and recording the output-data in Ym
warning('off');
sim('CubliParameterEstimation.slx');
warning('on');
Ym = simOut;

%plot the result of each iteration
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
        legend('Test data',...
               'Previous estimation',...
               'New estimation',...
               'Location', 'SouthEast')
    end
end

%adding Normed RMS error label
if exist('tex', 'var')
    delete(tex);
end
if exist('errn', 'var')
    if documentation == 1
        errorSTR = ['Normed RMS error = ', num2str(errn)];
    else
        errorSTR = ['Normed RMS error  =  ', num2str(errn)];
    end
        tex = text(0.52, 0.13,...
               errorSTR,...
               'Color', '[ 0 .55 0 ]',...
               'FontSize', 12);
end

hOld = h;
drawnow;

%----- USING STEEPEST DESCEND METHOD --------------------------------------

%error function
errn = sqrt(sum((Y-Ym).^2)/sum(Y.^2))*100;

if exist('errn', 'var')
    errnOld = errn; %<-- saving old error value for refference
end

%the 'error squared' part of the performance function
P = (Y-Ym).^2;

if exist('Pval', 'var')
    PvalOld = Pval; %<-- saving old preformance value for refference
end

N = length(t); %<--setting N to degrees of freedom

%this implements the 'mean' part or the performance function
Pval = (1/(2*N))*sum(P); %<-- calculating new preformance value

%stepsize
if exist('PvalOld', 'var')
    %if Pval <= PvalOld
         %s = s*1.2;       %    increase stepsize (double)
    %end
    if Pval > PvalOld
        J_f = J_f_old;
        B_f = B_f_old;
        %s = s*0.5;        %     decrease stepsize (half)
    end
end

% if exist('errnOld', 'var')
%     if errn <= errnOld%    increase stepsize (double)
%          s = s*1.2;
%     end
%     if errn > errnOld%     decrease stepsize (half)
%         J_f = J_f_old;
%         B_f = B_f_old;
%         s = s*0.5;
%     end
% end


%---- calculating the gradient of the preformance function-----------------

%gradientOfP = 1/N  * sumFrom1toN( ( Y - Ym ) * Ym' )
%where:
%   Y      is the 
%   Ym     is the model simulation output
%   Ym'    is the partial derivative of the simulated model with respect to
%          each of the parameters to be estimated.

%Problem:  We cannot directly differentiate the model since it is used
%          through simulation in Simulink
%Solution: Partial derivaties can be calculated nummericaly:

%In this case:
%parameters: J_f B_f
%small magnitude deviation from these parameters is set
p = 0.003;
     
%calculating the deviation
deltaJ_f = p*J_f;
deltaB_f = p*B_f;

%saving the old parameters:
J_f_old = J_f;
B_f_old = B_f;

%setting deviating parameters ready for simulation
J_f = deltaJ_f;

%running the simulation again, now with the deviating parameters
warning('off');
sim('CubliParameterEstimation.slx');
warning('on');

%storring the result of the simulation
deltaYmJf = simOut;

%setting deviating parameters ready for simulation
B_f = deltaB_f;
J_f = J_f_old;

%running the simulation again, now with the deviating parameters
warning('off');
sim('CubliParameterEstimation.slx');
warning('on');

%storring the result of the simulation
deltaYmBf = simOut;

%restoring the parameters to their original value
B_f = B_f_old;

%finally calculating the derivatives of the model
YmDiffBf = ( deltaYmBf - Ym )/ p;
YmDiffJf = ( deltaYmJf - Ym )/ p;

clc;
%this however is just for the model.. and we need
%the gradient of the preformance function as stated earlier:
%gradientOfP = 1/N  * sumFrom1toN( ( Y - Ym ) * Ym' )
gBf = -(1/N)* sum((Y - Ym ).*YmDiffBf);
gJf = -(1/N)* sum((Y - Ym ).*YmDiffJf);

%Calculating hessian
HBf = (1/N) * sum(YmDiffBf'*YmDiffBf);
HJf = (1/N) * sum(YmDiffJf'*YmDiffJf);

%figure;
%plot(t,P)
%hold on;
%plot(t,YmDiff)

%calculate the new parameters
%J_f = J_f-gJf*s
%B_f = B_f-gBf*s*.1
J_f = J_f-HJf^(-1)*gJf
B_f = B_f-HBf^(-1)*gBf*.01   %<--the *.01 is an attempt to counter the too
errn                         %   high sensitivity of the parameter.
Pval                         %   There exists a more beautifull method
                             %   for determining sensitivity

%where:
%  -g    is the negative gradient (the steepest descent)
%   s    is the step size

end
% figure;
% plot(t,YmDiffBf,'b', 'linewidth',1.4)
% hold on
% plot(t,Pval*ones(size(t)), 'c')
% plot(t,P, 'r', 'linestyle','--')
% %axis([ 0 5 0 5 ])