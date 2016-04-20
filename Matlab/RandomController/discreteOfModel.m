close all;
clc;

% Cubli model parameters
T_m=0.005;
K=0.5;
J_w=0.601e-3;
J_f=5.6e-3;%2.8e-3;
B_w=17.03e-6;
B_f=7.4e-3;%6.08e-3;
m_w=0.222;
m_f=0.77-m_w;%0.354;
g=9.82;
l_w=0.093;
l_f=0.08498;%0.076;

s=tf('s');

%-- Sampling time --%
T=1/100;%1/100;

%-- Plant definition --%
G=(-J_w*s^2)/((J_w*s^2+B_w*s)*((J_f+m_w*l_w^2)*s^2+B_f*s-(m_w*l_w+m_f*l_f)*g+((B_w*J_w*s^3)/(J_w*s^2+B_w*s))));
G_reduced=minreal(G);

Gt=c2d(G_reduced,T,'tustin');
Gz=c2d(G_reduced,T,'zoh');

bodeplot(G_reduced,Gt,Gz);
grid on;
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6);
axes_handles = findall(gcf, 'type','axes' );
legend(axes_handles(3),'Continuous Plant','Discretized Plant (ZOH)','Discretized Plant (Tustin)','Location','Southeast');



%% Controller analysis %%
%-- Controller definition --%
D=-4583.5*(s+9.483)*(s+1.599)/((s-5.539)*(s+100)*(s+200))%/0.62737;



disp('Discretized controller: Zero-Order Hold method');
Dz = c2d(D,T,'zoh')
disp('Discretized controller: Tustin method');
Dt = c2d(D,T,'tustin')
disp('Discretized controller: Tustin w/ pre-warping method');
opts = c2dOptions('Method', 'tustin', 'PrewarpFrequency', 33.5); % Look at wp = 38.351 or 33.27356999 or in between
Dtp = c2d(D,T,opts)

% Plotting
figure
b = bodeplot(D,Dz,Dt,Dtp);
p = getoptions(b);
p.PhaseMatching = 'on';
p.PhaseMatchingFreq = 0;
p.PhaseMatchingValue = 0;
setoptions(b,p);
grid on;
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6);
axes_handles = findall(gcf, 'type','axes' );
legend(axes_handles(3),'Continuous controller','Discretized Controller (ZOH)','Discretized Controller (Tustin)','Discretized Controller (Tustin with Pre-Warping)','Location','Southeast');

figure
b2 = bodeplot(D*G_reduced/(1+D*G_reduced),Dz*Gz/(1+Dz*Gz),Dt*Gz/(1+Dt*Gz),Dtp*Gz/(1+Dtp*Gz));
p2 = getoptions(b2);
p2.PhaseMatching = 'on';
p2.PhaseMatchingFreq = 0;
p2.PhaseMatchingValue = 0;
setoptions(b2,p2);
grid on;
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6);
axes_handles = findall(gcf, 'type','axes' );
legend(axes_handles(3),'Continuous controller (CL)','Discretized Controller (ZOH)(CL)','Discretized Controller (Tustin)(CL)','Discretized Controller (Tustin with Pre-Warping)(CL)','Location','Southeast');

figure
b3 = bodeplot(D*G_reduced,Dz*Gz,Dt*Gz,Dtp*Gz);
p3 = getoptions(b3);
p3.PhaseMatching = 'on';
p3.PhaseMatchingFreq = 0;
p3.PhaseMatchingValue = 0;
setoptions(b3,p3);
grid on;
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6);
axes_handles = findall(gcf, 'type','axes' );
legend(axes_handles(3),'Continuous controller (OL)','Discretized Controller (ZOH)(OL)','Discretized Controller (Tustin)(OL)','Discretized Controller (Tustin with Pre-Warping)(OL)','Location','Southeast');

%nyqlog(D*G_reduced);
%nyquist(Gz*Dz);
%rlocus(D*G);
%nyquist(Gz*Dz);
%rlocus(D*G);