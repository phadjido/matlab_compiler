#include "mex.h"
#ifdef USE_MPI
#include <mpi.h>
#endif


void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{
#ifdef USE_MPI
	int size;

	MPI_Comm_size(MPI_COMM_WORLD, &size);

	plhs[0] = mxCreateDoubleScalar(size);
#endif
}
