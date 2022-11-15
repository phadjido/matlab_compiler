% test0.m
N=8

A=1:N;

tic
%parfor i = 1:N
for i = 1:N
	pause(1)
	B(i) = A(i)*A(i);
end
toc
[A;B]
