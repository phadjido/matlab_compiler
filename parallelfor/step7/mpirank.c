#include "mex.h"
#ifdef USE_MPI
#include <mpi.h>
#endif


void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{
#ifdef USE_MPI
	int rank;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	plhs[0] = mxCreateDoubleScalar(rank);
#endif
}
