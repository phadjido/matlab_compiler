clear all;
N=8;

P=4;		% number of chunks
C=N/P;		% chunk size

A=1:N;

tic 
B = pdriver(A,N,P);

%The following code has been moved into pdriver()
%for i=1:P
%	a=(i-1)*C+1
%	b=a+C-1
%	B(a:b)=proutine(A(a:b),C);
%end
toc

[A;B]
