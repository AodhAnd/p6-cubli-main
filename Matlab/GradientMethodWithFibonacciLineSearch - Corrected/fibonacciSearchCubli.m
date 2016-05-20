function [ X1new, X2new, isDone ] = fibonacciSearchCubli(t, Y, J_f, B_f, initX1, initX2, X1upper, X2upper )

    isDone = 0;

    if ~exist('X1a', 'var')
        
        %initializing range
        fXupper = evalCostFunction(Y, t, X1upper, X2upper, J_f, B_f);
        fXinit = evalCostFunction(Y, t, initX1, initX2, J_f, B_f);
        
        if fXupper < fXinit
            X1max = initX1;
            X2max = initX2;

            X1min = X1upper;
            X2min = X2upper;
        elseif fXupper > fXinit
            X1max = X1upper;
            X2max = X2upper;
            
            X1min = initX1;
            X2min = initX2;
        end

        I1 = sqrt( (X1min-X1max)^2 + (X2min-X2max)^2 );

        %---- The first 50 fibonacci numbers (from F0 to F49) ---------------------
        fibonacci = [ 1 1 2 3 5 8 13 21 34 55 89 144 233 377 610 987 1597 2584 ...
                      4181 6765 10946 17711 28657 46368 75025 121393 196418    ...
                      317811 514229 832040 1346269 2178309 3524578 5702887     ...
                      9227465 14930352 24157817 39088169 63245986 102334155    ...
                      165580141 267914296 433494437 701408733 1134903170       ...
                      1836311903 2971215073 4807526976 7778742049 12586269025  ]';
        %--0.010 ms----------------------------------------------------------------

        %setting highest magnitude fibonacci-number for a precision interval of In
        In = 0.0001;
        FnWanted = I1/In;
        if FnWanted > fibonacci(49+1)
            fprintf('ERROR: Wanted fibonacci number is too large\n\n')
            return;
        end

        %---- Selecting Fn from the fibonacci numbers -----------------------------
        for i = 1:50
            if FnWanted < fibonacci(i)
                Fn = fibonacci(i);
                n = i-1;
                In = I1/Fn;
                break;
            end
        end
        %--0.153 ms----------------------------------------------------------------

        nn = n+1;
        I = zeros(nn,1);

        for i = 1:nn
            I(n+2-nn) = fibonacci(nn)*In;
            nn = nn-1;
        end
    end

    for i = 2:n+1
        
    IratioL = (I(i-1)-I(i))/I(i-1);
    IratioU = I(i)/I(i-1);

    if i == 2
        X1a = IratioL*(X1max-X1min)+X1min;
        X2a = IratioL*(X2max-X2min)+X2min;
        
        X1b = IratioU*(X1max-X1min)+X1min;
        X2b = IratioU*(X2max-X2min)+X2min;
        
        fXa = evalCostFunction(Y, t, X1a, X2a, J_f, B_f);
        fXb = evalCostFunction(Y, t, X1b, X2b, J_f, B_f);
    elseif setX == -1                         %<-- (-1) means Xa was set last
        X1a = X1b;
        X2a = X2b;
        
        fXa = fXb;
        
        X1b = IratioU*(X1max-X1min)+X1min;
        X2b = IratioU*(X2max-X2min)+X2min;
        
        fXb = evalCostFunction(Y, t, X1b, X2b, J_f, B_f);
    elseif setX == 1                          %<-- (+1) means Xb was set last
        X1b = X1a;
        X2b = X2a;
        
        fXb = fXa;
        
        X1a = IratioL*(X1max-X1min)+X1min;
        X2a = IratioL*(X2max-X2min)+X2min;
        
        fXa = evalCostFunction(Y, t, X1a, X2a, J_f, B_f);
    end

        if fXb > fXa
            X1max = X1b;
            X2max = X2b;
            
            setX = 1;  %Xb was set as limit
            
        elseif fXa >= fXb
            X1min = X1a;
            X2min = X2a;
            
            setX = -1; %Xa was set as limit
            
        end

    end
    
    if n < 2
        isDone = 1;
        X1new = J_f;
        X2new = B_f;
        return;
    end
    
    if fXa < fXb
        X1new = X1a;
        X2new = X2a;
    else
        X1new = X1b;
        X2new = X2b;
    end

end

