close all;
clc;

s=tf('s');
T=1/100;%1/100;

D=-4583.5*(s+9.483)*(s+1.599)/((s-5.539)*(s+100)*(s+200))/0.62737;
G=(-J_w*s^2)/((J_w*s^2+B_w*s)*((J_f+m_w*l_w^2)*s^2+B_f*s-(m_w*l_w+m_f*l_f)*g+((B_w*J_w*s^3)/(J_w*s^2+B_w*s))));
G_reduced=minreal(G);

Gz=c2d(G_reduced,T,'tustin');

Dz=c2d(D,T,'tustin')
opts = c2dOptions('Method', 'tustin', 'PrewarpFrequency', 33.5);
Dz2 = c2d(D,T,opts)

bodeplot(D,Dz,Dz2);
grid on;
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6);
legend('Continuous controller','Discretized Controller (Tustin)','Discretized Controller (Tustin with Pre-Warping)','Location','Southeast');

figure
bodeplot(D*G_reduced/(1+D*G_reduced),Dz*Gz/(1+Dz*Gz),Dz2*Gz/(1+Dz2*Gz));
grid on;
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6);
legend('Continuous controller (CL)','Discretized Controller (Tustin)(CL)','Discretized Controller (Tustin with Pre-Warping)(CL)','Location','Southeast');

figure
bodeplot(D*G_reduced,Dz*Gz,Dz2*Gz);
grid on;
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6);
legend('Continuous controller (OL)','Discretized Controller (Tustin)(OL)','Discretized Controller (Tustin with Pre-Warping)(OL)','Location','Southeast');

%nyqlog(D*G_reduced);
%nyquist(Gz*Dz);
%rlocus(D*G);