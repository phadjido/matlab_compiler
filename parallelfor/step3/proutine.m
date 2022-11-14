function [B] = proutine(A, n)

A=A
n=n
for i=1:n
	pause(1)
	B(i) = A(i)*A(i);
end

end
