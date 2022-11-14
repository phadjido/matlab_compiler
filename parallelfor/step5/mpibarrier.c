#include "mex.h"
#ifdef USE_MPI
#include <mpi.h>
#endif


void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{
#ifdef USE_MPI
	MPI_Barrier(MPI_COMM_WORLD);
#endif
}
