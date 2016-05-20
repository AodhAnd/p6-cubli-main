clear all
close all
clc

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

figSet1 = 0;
figSet2 = 0;

initJ = 0;
initB = 0;

N = length(Y); %<--setting N to degrees of freedom
initPoints = 300; %<--points/simulations per line (ONLY EVEN NUMBERS!!)
resolution = 0.04/(initPoints-2);

J = zeros(initPoints-1,initPoints);
B = zeros(initPoints-1,initPoints);
C = zeros(initPoints-1,initPoints);

plotting = 0;

joff = 0;
points = initPoints;
tic
for j = 1:initPoints
    each = tic;
    for i = 1:points-1
            if i == 1
                J(i,j+joff) = j*resolution-resolution*2;
                B(i,j+joff) = initB;
            else
                J(i,j+joff) = J(i-1,j+joff);
                B(i,j+joff) = B(i-1,j+joff)+resolution;
            end
            C(i,j+joff) = evalCostFunction( Y, t,                     ...
                                            J(i,j+joff), B(i,j+joff), ...
                                            J(i,j+joff), B(i,j+joff)  );
            
            %if C(i,j+joff) < 5
            if plotting == 1
                if C(i,j+joff) < 10e-2
                    fig1 = figure(1);
                    plot3( J(i,j+joff), B(i,j+joff), C(i,j+joff), 'ok', ...
                           'MarkerFaceColor', 'k', 'MarkerSize', 2      );
                else
                    fig2 = figure(2);
                    plot3( J(i,j+joff), B(i,j+joff), C(i,j+joff), 'ok', ...
                           'MarkerFaceColor', 'k', 'MarkerSize', 2      );
                end
            
                drawnow;
                if exist('fig1', 'var') && figSet1 == 0
                    figure(fig1);
                    hold on
                    xlabel('J');
                    ylabel('B');
                    zlabel('C');
                    grid on, grid minor;
                    figSet1 = 1;
                end
                if exist('fig2', 'var') && figSet2 == 0
                    figure(fig2);
                    hold on
                    xlabel('J');
                    ylabel('B');
                    zlabel('C');
                    grid on, grid minor;
                    figSet2 = 1;
                end
            end
    end
    fprintf('\nTime elapsed for line nr. %i:\n%f s\n', j, toc(each))
end
fprintf('\nTotal time elapsed:\n%f h\n', (toc/60)/60)

fprintf('\nAverage time for each line:\n%f s\n',...
         toc/initPoints )
fprintf('\nAverage time for each point:\n%f ms\n',...
         ((toc/initPoints)/(initPoints-1))*1000 )

figure;
map = csvread('mapHotRodRed.csv');
surf(J, B, C, 'EdgeColor', 'none');
hold on
alpha(0.8)
colormap(map);
colorbar
set(gca, 'view', [154.5000 16.0000]);




% 
% joff = initPoints;
% points = initPoints;
% for j = 1:initPoints
% 
%     for i = 1:points
%             if i == 1
%                 J(i,j+joff) = initJ;
%                 B(i,j+joff) = j*resolution;
%             else
%                 J(i,j+joff) = J(i-1,j+joff)+resolution;
%                 B(i,j+joff) = B(i-1,j+joff)+resolution;
%             end
%             C(i,j+joff) = evalCostFunction( Y, t,                     ...
%                                             J(i,j+joff), B(i,j+joff), ...
%                                             J(i,j+joff), B(i,j+joff)  );
%             
%             if C(i,j+joff) < 5
%                 if C(i,j+joff) < 10e-2
%                     figure(fig1);
%                     plot3( J(i,j+joff), B(i,j+joff), C(i,j+joff), 'ok', ...
%                            'MarkerFaceColor', 'k', 'MarkerSize', 2      );
%                 else
%                     figure(fig2);
%                     plot3( J(i,j+joff), B(i,j+joff), C(i,j+joff), 'ok', ...
%                            'MarkerFaceColor', 'k', 'MarkerSize', 2      );
%                 end
%             end
%             
%             drawnow;
%     end
%     
%     points = points-1
% end
% 
csvwrite('JV2.csv',J)
csvwrite('BV2.csv',B)
csvwrite('CV2.csv',C)