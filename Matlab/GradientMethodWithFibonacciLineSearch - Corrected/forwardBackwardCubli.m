function [ X1upper, X2upper ] = forwardBackwardCubli( J_f, B_f, Y, t, gJf, gBf, fig2 )

    plotRange = 1;
    initX1 = J_f;
    initX2 = B_f;
    initF = evalCostFunction(Y, t, initX1, initX2, J_f, B_f);
    dfXX1 = gJf;
    dfXX2 = gBf;

    %--->Finding a 'bracket'/'search interval'/'interval of uncertainty'<--
    
    step = 2;
    
    newX1 = initX1-dfXX1*step;
    newX2 = initX2-dfXX2*step;

    done = 0;
    while done == 0
        newX1 = initX1-dfXX1*step;
        newX2 = initX2-dfXX2*step;

        newF = evalCostFunction(Y, t, newX1, newX2, J_f, B_f);

        pause(3);
        
        if newF < initF  %-------------------------------------------------
       
           % The first step is less than the initial one,
           % so we take a tiny step FORWARD to determine the slope
           step = step+0.0001;
           newX1new = initX1-dfXX1*step;
           newX2new = initX2-dfXX2*step;
           
           newFnew = evalCostFunction(Y, t, newX1new, newX2new, J_f, B_f);
           
           if newFnew > newF
               %The selected bracket is [ (initX1, initX2) ; (newX1new newX2new) ]
               X1upper = newX1new;
               X2upper = newX2new;
               done = 1;           %<-----------------------------EXIT loop
           elseif newFnew < newF
               % Initial step was too short (on same slope)
               step = step*1.5; % so we increase the step size
           end
    
        elseif newF > initF %----------------------------------------------
       
           % The first step is more than the initial one,
           % so we take a tiny step BACKWARD to determine the slope
           step = step-0.0001;
           newX1new = initX1-dfXX1*step;
           newX2new = initX2-dfXX2*step;
           
           newFnew = evalCostFunction(Y, t, newX1new, newX2new, J_f, B_f);
       
           if  newFnew < newF
               % The selected bracket is [ (initX1, initX2) ; (newX1 newX2) ]
               X1upper = newX1;
               X2upper = newX2;
               done = 1;           %<-----------------------------EXIT loop
           elseif newF < newFnew
               % Initial step was too short (very close to minimum)
               step = step*1.1; % so we increase the step size a bit
           end
    
        end  %-------------------------------------------------------------
    end
    if plotRange == 1
        figure(fig2)
        fXupper = evalCostFunction(Y, t, X1upper, X2upper, J_f, B_f);
        plot3(X1upper, X2upper, fXupper, 'ok', ...
             'MarkerFaceColor', 'k',           ...
             'MarkerSize', 2)
        v1 = [X1upper X2upper fXupper];
        v2 = [initX1 initX2 initF];
        v = [v1; v2];
        plot3(v(:,1),v(:,2),v(:,3),'k', 'LineWidth', 1, 'LineStyle', ':')
    end


end