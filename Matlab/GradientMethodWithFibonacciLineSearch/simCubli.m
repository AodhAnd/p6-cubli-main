function [ Ym ] = simCubli( J_f, B_f, saveJ_f, saveB_f )

    assignin('base', 'J_f', J_f);
    assignin('base', 'B_f', B_f);

%     if exist('CubliParameterEstimation', 'file')
%         simStatus = get_param('CubliParameterEstimation','SimulationStatus');
%         if strcmp('terminating', simStatus)
%             error('The model is stuck - only solution found so far: Force matlab restart')
%         end
%     end
    
    try
        warning('off', 'all');
        sim('CubliParameterEstimation.slx');
        warning('on', 'all');
    catch errormsg
        if ~exist('simOut', 'var') %<--in case it runs into error in the
            rethrow(errormsg)      %   very first simulation.
        end
        fprintf('\n\nERROR in Simulation, Ym set to previous simulation output.\n\n')
    end
    
    Ym = simOut;
    
    %making sure that J_f and B_f are unaltered in the base workspace
    assignin('base', 'J_f', saveJ_f);
    assignin('base', 'B_f', saveB_f);
end

