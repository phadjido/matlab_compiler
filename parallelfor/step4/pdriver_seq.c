#include "mex.h"
#include <string.h>

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
	int N = mxGetScalar(prhs[1]);		/* size of A */
	int P = mxGetScalar(prhs[2]);		/* number of chunks */

	printf("N = %d\n", N);
	printf("P = %d\n", P);

	plhs[0] = mxCreateDoubleMatrix(1, (int) N, mxREAL);	/* output array B */
	double *B = mxGetPr(plhs[0]);

	int C = N / P;	/* chunk size */

	mxArray *out[P];
	double *Bp[P];

	int i;
	for (i = 0; i < P; i++)			/* for each chunk */
	{
		mxArray *in[2];

		int a = i*C;
		int b = a + C;

		in[0] = mxCreateDoubleMatrix(1,C,mxREAL);	/* part of A */
		double *A_in = mxGetPr(in[0]);
		memcpy(A_in, &A[a], C*sizeof(double)); 

		in[1] = mxCreateDoubleScalar(C);

		mexCallMATLAB(1,&out[i],2,in,"proutine");	/* call proutine */

		mxDestroyArray(in[0]);
		mxDestroyArray(in[1]);

		int j;
		Bp[i] = mxGetPr(out[i]);		/* Bp : part of B */

		printf("Bp %d -> %p\n", i, Bp[i]);
		for (j = 0; j < C; j++)
		{
			printf("Bp[%d]=%f\n", j, Bp[i][j]);
		}
	}

	for (i = 0; i < P; i++)		/* merge the results */
	{
		int a = i*C;
		int b = a + C;

		Bp[i] = mxGetPr(out[i]);
		memcpy(&B[a], Bp[i], C*sizeof(double)); 
		mxDestroyArray(out[i]);
	}

}
