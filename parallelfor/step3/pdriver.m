function [B] = pdriver(A, N, P)

%class(A)
C = N/P;
for i=1:P
	a=(i-1)*C+1
	b=a+C-1
	B(a:b)=proutine(A(a:b),C);
end

end
