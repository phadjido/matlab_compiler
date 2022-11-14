#include "mex.h"
#include <string.h>
#include <mpi.h>

/*
function [B] = pdriver(A, N, P)
C = N/P;
for i=1:P
	a=(i-1)*C+1
        b=a+C-1
        B(a:b)=proutine(A(a:b),C);
end

end
*/


void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{
	int m, n;
        m = mxGetM(prhs[0]);
        n = mxGetN(prhs[0]);

	printf("m = %d\n", m);
        printf("n = %d\n", n);

	double *A = mxGetPr(prhs[0]);		/* input array A */
	int N = mxGetScalar(prhs[1]);		/* problem size */
	int P = mxGetScalar(prhs[2]);		/* P = number of ranks = number of chunks */

	printf("N = %d\n", N);
	printf("P = %d\n", P);

	plhs[0] = mxCreateDoubleMatrix(1, (int) N, mxREAL);	/* this can be avoid if rank > 0 */
	double *B = mxGetPr(plhs[0]);

	int C = N / P;		/* chunk size */

	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int i;
	if (rank == 0) 		/* master */
	{
		mxArray *in[2];
		mxArray *out[1];

		for (i = 1; i < P; i++)		/* send parts of A to the workers */
		{
			int a = i*C;
			int b = a + C;

#if VERBOSE
			int j;
			for (j = a; j < b; j++)
				printf("--> A[%d]=%f\n", j, A[j]);
#endif

			MPI_Send(&A[a], C, MPI_DOUBLE, i, 33, MPI_COMM_WORLD);
		}

		/* call proutine */
		in[0] = mxCreateDoubleMatrix(1,C,mxREAL);
		double *A_in = mxGetPr(in[0]);
		memcpy(A_in, A, C*sizeof(double)); 

		in[1] = mxCreateDoubleScalar(C);

		mexCallMATLAB(1,&out[0],2,in,"proutine");

		mxDestroyArray(in[0]);
		mxDestroyArray(in[1]);



		double *Bp = mxGetPr(out[0]);
		memcpy(&B[0], Bp, C*sizeof(double));	/* copy my partial result to B */
		mxDestroyArray(out[0]);
		
		for (i = 1; i < P; i++)	/* receive parts of B from the workers */
		{
			MPI_Status status;
			int a = i*C;
			int b = a + C;

			MPI_Recv(&B[a], C, MPI_DOUBLE, i, 34, MPI_COMM_WORLD, &status);		/* receive + copy to the corresponding part of B */
		}
	}
	else
	{
		mxArray *in[2];
		mxArray *out[1];

		in[0] = mxCreateDoubleMatrix(1,C,mxREAL);
		double *A_in = mxGetPr(in[0]);

		in[1] = mxCreateDoubleScalar(C);

		MPI_Status status;
		MPI_Recv(A_in, C, MPI_DOUBLE, 0, 33, MPI_COMM_WORLD, &status);	/* receive my part of A */

#if VERBOSE
		int i;
		for (i = 0; i < C; i++)
			printf("===> A_in[%d]=%f\n", i, A_in[i]);
#endif

		/* call proutine */
		mexCallMATLAB(1,&out[0],2,in,"proutine");

		mxDestroyArray(in[0]);
		mxDestroyArray(in[1]);

		double *Bp = mxGetPr(out[0]);
		MPI_Send(Bp, C, MPI_DOUBLE, 0, 34, MPI_COMM_WORLD);	/* send my result back of the master */

		mxDestroyArray(out[0]);
	}

}
