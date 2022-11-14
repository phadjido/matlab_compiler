function test7()

mpiinit();

rank=mpirank()
size=mpisize()

N=8;
P=size;	% number of processors
C=N/P;	% work per processor

B = zeros(1,N);
A = 1:N;

for i=1:3	% outer loop (steps)

if rank == 0

	A=A+B;	% accumulate using the output of the previous step

	mpibarrier();
	tic 
	B = pdriver_mpi(A,N,P);
	toc
	[A;B]
	mpibarrier();
else
	mpibarrier();
	dummy_A = zeros(1,N);
	dummy_B = zeros(1,N);
	dummy_B = pdriver_mpi(dummy_A,N,P);
	mpibarrier();
end

end % for

mpifinalize();

end
