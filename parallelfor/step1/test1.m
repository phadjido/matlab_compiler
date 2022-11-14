N=8

A=1:N;

tic 
for i = 1:N
	B(i)=proutine(A(i));	% body loop 
end
toc
[A;B]
