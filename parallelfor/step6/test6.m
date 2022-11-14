function test()

mpiinit();

rank=mpirank()
size=mpisize()

% N, P, C are common 
N=8;	% problem size
P=size;	% number of processors
C=N/P;	% work per processor

if rank == 0		% master

	A=1:N;		% initialize A

	mpibarrier();	% synchronize (not required here)
	tic 
	B = pdriver_mpi(A,N,P);		% parallel work - master
	toc
	[A;B]
	mpibarrier();
else
	mpibarrier();		% synchronize (not required here)
	dummy_A = zeros(1,N);
	dummy_B = zeros(1,N);
	dummy_B = pdriver_mpi(dummy_A,N,P);	% parallel work - workers
	clear dummy_A dummy_B;
	mpibarrier();
end

mpifinalize();

end
