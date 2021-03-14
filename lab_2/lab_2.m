L = 0;
R = 1;
eps = 1e-3;

iter = 0;

while 1

    iter = iter + 1
    
    z = z_foo(R, L)
    d = diff(z)
    if(d > 0)
        R = z
    else
        L = z
    end    
    
    if (abs(diff(z)) <= eps)
        break;
    end
    
end

z
iter

function [ y ] = diff( x )
    %F = x^3 - x
    y = 3 * x * x - 1;
end

function [ y ] = z_foo( r, l )
    y = r - diff(r) * (r - l) / (diff(r) - diff(l));
end
