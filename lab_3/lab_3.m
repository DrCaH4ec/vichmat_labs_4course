x_1i = [0, 0];
x_2i = [0, 0];
x_3i = [0, 0];
x_k = [0, 0];
    
state = 1;
    
for i = 1 : 10000
i
    switch state

        case 1  
            x_1i = [0, 0];
            d_x = [1 ,1];
            alpha = 2;
            eps = 1e-1;

            state = 2;
        case 2
            [x_2i(1), x_2i(2)] = expl_search(x_1i, d_x);

            state = 3;
        case 3
            if (foo(x_2i) < foo(x_1i))
                state = 5;
            else
                state = 4;
            end

        case 4
            if (mod(x_2i) < eps)
                break;
            else
                d_x(1) = d_x(1) / alpha;
                d_x(2) = d_x(2) / alpha;
                x_1i = x_2i;
                
                state = 2;
            end
            
        case 5
            x_k(1) = x_2i(1) + (x_2i(1) - x_1i(1));
            x_k(2) = x_2i(2) + (x_2i(2) - x_1i(2));
            
            state  = 6;
        case 6
            [x_3i(1), x_3i(2)] = expl_search(x_k, d_x);
            
            state = 7;
        case 7
            if (foo(x_3i) < foo(x_2i))
                x_1i = x_2i;
                x_2i = x_3i;
                
                state = 5;
            else
                state = 4;
            end
            
        otherwise
                disp('Err')
            
    end
    
end



function [ y ] = foo(x)
    x2 = x(2);
    x1 = x(1);
    y = x1^2 + x2^2 +3*x1 + 5*x2 - 7;
end

function [ y ] = mod(x)
    x1 = x(1);
    x2 = x(2);
    y = sqrt(x1^2 + x2^2);
end

function [ x1, x2 ] = expl_search(x, d_x)
    tmp = [x(1), x(2)];
    x_res = [0, 0];
    
    for i = 1 : 2
        tmp(i) = x(i) + d_x(i);

        if (foo(tmp) < foo(x))
            x_res(i) = tmp(i);
        else
            tmp(i) = x(i) - d_x(i);

            if (foo(tmp) < foo(x))
                x_res(i) = tmp(i);
            end 
        end        
    end
        x1 = x_res(1);
        x2 = x_res(2);
end
