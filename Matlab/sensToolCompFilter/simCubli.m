function  y=simCubli(u,t,par)    %u = input vector
                                 %t = time vector
                                 %par = [K tau]  (model parameters)
assignin('base', 'B_f', par(1));
assignin('base', 'J_f', par(2));
%assignin('base', 'm_f', par(3));
%assignin('base', 'l_f', par(4));

t = [ 0  t(1:length(t)-1) ];

warning('off');
sim('CubliSenseToolSimOLD.slx');
warning('on');

y = output;