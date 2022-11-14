MPI_INC=/usr/include/x86_64-linux-gnu/mpich
MPI_LIB=/usr/lib/x86_64-linux-gnu/libmpich.so

all: test5

pdriver_seq.mexa64: pdriver_seq.c
	mex -v COPTIMFLAGS='-O3 -DNDEBUG' pdriver_seq.c

mpiinit.mexa64: mpiinit.c
	mex -DUSE_MPI -I$(MPI_INC) mpiinit.c $(MPI_LIB)

mpifinalize.mexa64: mpifinalize.c
	mex -DUSE_MPI -I$(MPI_INC) mpifinalize.c $(MPI_LIB)

mpirank.mexa64: mpirank.c
	mex -DUSE_MPI -I$(MPI_INC) mpirank.c $(MPI_LIB)

mpisize.mexa64: mpisize.c
	mex -DUSE_MPI -I$(MPI_INC) mpisize.c $(MPI_LIB)

mpibarrier.mexa64: mpibarrier.c
	mex -DUSE_MPI -I$(MPI_INC) mpibarrier.c $(MPI_LIB)


test5: test5.m proutine.m pdriver_seq.mexa64 mpiinit.mexa64 mpifinalize.mexa64 mpirank.mexa64 mpisize.mexa64 mpibarrier.mexa64
	mcc -m test5.m proutine.m

clean:
	rm -f test5 mccExcludedFiles.log readme.txt requiredMCRProducts.txt run_test5.sh mpibarrier.mexa64 mpifinalize.mexa64 mpiinit.mexa64 mpirank.mexa64 mpisize.mexa64 pdriver_seq.mexa64



# to run: 
# source ../setup.sh;  mpirun -n 2 ./test5
# or add the MPI library path to LD_LIBRARY_PATH in run_test5.sh

