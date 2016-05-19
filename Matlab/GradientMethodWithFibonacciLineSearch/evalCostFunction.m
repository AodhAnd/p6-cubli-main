function [ Pval ] = evalCostFunction( Y, t, J_f, B_f, saveJ_f, saveB_f )

    Ym = simCubli( J_f, B_f, saveJ_f, saveB_f );

    N = length(t); %<--setting N to degrees of freedom

    P = (Y-Ym).^2;
    Pval = (1/(2*N))*sum(P);
end