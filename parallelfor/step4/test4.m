clear all;
N=8;

P=4;
C=N/P;

A=1:N;

tic 

B = pdriver_seq(A,N,P);	% pdriver.m as a mex file

toc
[A;B]
