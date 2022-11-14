MPI_INC=/usr/include/x86_64-linux-gnu/mpich
MPI_LIB=/usr/lib/x86_64-linux-gnu/libmpich.so

all: test7

pdriver_mpi.mexa64: pdriver_mpi.c
	mex -I$(MPI_INC) pdriver_mpi.c $(MPI_LIB)

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


test7: test7.m proutine.m pdriver_mpi.mexa64 mpiinit.mexa64 mpifinalize.mexa64 mpirank.mexa64 mpisize.mexa64 mpibarrier.mexa64
	mcc -m test7.m proutine.m

clean:
	rm -f test7 mccExcludedFiles.log readme.txt requiredMCRProducts.txt run_test7.sh mpibarrier.mexa64 mpifinalize.mexa64 mpiinit.mexa64 mpirank.mexa64 mpisize.mexa64 pdriver_mpi.mexa64


# to run: 
# source ../setup.sh;  mpirun -n 2 ./test7
# or add the MPI library path to LD_LIBRARY_PATH in run_test7.sh

