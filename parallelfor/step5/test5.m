function test5()	% not actually necessary

mpiinit();

rank=mpirank()
size=mpisize()

if rank == 0		% only rank zero does something useful

	N=8;

	P=4;
	C=N/P;

	A=1:N;

	tic
	B = pdriver_seq(A,N,P);
	%B = pdriver(A,N,P);
	toc

	[A;B]

	mpibarrier();
else
	mpibarrier();		% any other process (rank) just waits for the master to finish
end

mpifinalize();

end
