function [A,M] = A_complet (U, V, X, Y, Z)
    %A
    [L,~] = size(U);
    A = zeros(2*L,12);
    for i = 1:L
        A(2*i-1,:) = [X(i), Y(i), Z(i), 1, 0, 0, 0, 0, -(U(i)*X(i)), -(U(i)*Y(i)),-(U(i)*Z(i)),U(i)];
        A(2*i,:)   = [0, 0, 0, 0, X(i), Y(i), Z(i), 1, -(V(i)*X(i)), -(V(i)*Y(i)),-(V(i)*Z(i)),V(i)];
    end
    
    %B
    B = A'*A;
    [vectprop,valprop] = eig(B);
    select = min(valprop(valprop~=0));
    
    posip = find(valprop == select);
    posvp = mod(posip,12);
    %M
    M = vectprop(:,posvp);
    
end 