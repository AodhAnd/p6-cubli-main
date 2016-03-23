function  y=simCubli(u,t,par)    %u = input vector
                                 %t = time vector
                                 %par = [K tau]  (model parameters)

B_f = par(1);
J_f = par(2);
m_f = par(3);
l_f = par(4);
%m_f=0.354;
%l_f=0.076;
l_w = 0.093;
m_w = 0.076;
J_w = 0.601e-3;
g  = 9.82;

t = [ 0  t(1:length(t)-1) ]; 

warning('off');
sim('CubliSenseToolSim.slx');
warning('on');

y = output;