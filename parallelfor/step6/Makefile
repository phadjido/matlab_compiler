MPIDIR=/opt/mpich

all: test6

pdriver_mpi.mexa64: pdriver_mpi.c
	mex -I$(MPIDIR)/include pdriver_mpi.c $(MPIDIR)/lib/libmpi.so

mpiinit.mexa64: mpiinit.c
	mex -DUSE_MPI -I$(MPIDIR)/include mpiinit.c $(MPIDIR)/lib/libmpi.so

mpifinalize.mexa64: mpifinalize.c
	mex -DUSE_MPI -I$(MPIDIR)/include mpifinalize.c $(MPIDIR)/lib/libmpi.so

mpirank.mexa64: mpirank.c
	mex -DUSE_MPI -I$(MPIDIR)/include mpirank.c $(MPIDIR)/lib/libmpi.so

mpisize.mexa64: mpisize.c
	mex -DUSE_MPI -I$(MPIDIR)/include mpisize.c $(MPIDIR)/lib/libmpi.so

mpibarrier.mexa64: mpibarrier.c
	mex -DUSE_MPI -I$(MPIDIR)/include mpibarrier.c $(MPIDIR)/lib/libmpi.so


test6: test6.m proutine.m pdriver_mpi.mexa64 mpiinit.mexa64 mpifinalize.mexa64 mpirank.mexa64 mpisize.mexa64 mpibarrier.mexa64
	mcc -m test6.m proutine.m

clean:
	rm -f test6 mccExcludedFiles.log readme.txt requiredMCRProducts.txt run_test6.sh mpibarrier.mexa64 mpifinalize.mexa64 mpiinit.mexa64 mpirank.mexa64 mpisize.mexa64 pdriver_mpi.mexa64


# to run: 
# source ../setup.sh;  mpirun -n 2 ./test6
# or add the MPI library path to LD_LIBRARY_PATH in run_test6.sh

