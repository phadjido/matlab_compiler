In this folder, we demonstrate how a Matlab for loop can be manually parallelized using MPI and without any usage of the Parallel Matlab toolbox. 

step0: simple (parallel) for loop
step1: as above but the loop body has been moved into a Matlab function (proutine.m)
step2: as above but the loop iterations are processed in chunks 
step3: the for loop has been moved into a separate Matlab function (pdriver.m)
step4: pdriver.m has been implemented as a mex file (pdriver_seq.c)
step5: as before but the application can be executed with many processes using MPI. However, only rank 0 runs the application code of step4.
step6: MPI parallelization of the for loop by pdriver_mpi.c
step7: as above but the parallel for loop has been included in an outer loop

To build: just type 'make' - if MPI is used, you will need to specify the directory where MPI is installed
To run: you can use the generation run script. A better solution is to setup the appropriate environment variables
by sourcing setup.sh  (e.g. 'source setup.sh') and then run the generated executable (e.g. './test0' and 'mpirun -n 2 test6')

