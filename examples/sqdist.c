/* sqdist - computes pairwise squared Euclidean distances between points
 * original version by Roland Bunschoten, 1999
 * implemented as a mex file by P.E. Hadjidoukas
 */

#include "mex.h"

void process_single(mxArray *plhs[], const mxArray *prhs[], int n1, int n2);
void process_double(mxArray *plhs[], const mxArray *prhs[], int n1, int n2);

void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{
	int m1, n1;
	int m2, n2;
	int i;
	mxClassID category1, category2;
	mwSize dims[2];

	if (nrhs != 2) 
	{
		mexErrMsgTxt("Two inputs required.");
	} 
	else if (nlhs > 1) 
	{
		mexErrMsgTxt("Too many output arguments");
	}	

	m1 = mxGetM(prhs[0]);
	n1 = mxGetN(prhs[0]);
	m2 = mxGetM(prhs[1]);
	n2 = mxGetN(prhs[1]);

	category1 = mxGetClassID(prhs[0]);
	category2 = mxGetClassID(prhs[1]);

	if (category1 != category2)
	{
		mexErrMsgTxt("Input arrays have different class");
		printf("category1: %d, category2: %d\n", category1, category2);
		return;
	}

	/* Create matrix for the return argument. */
#if 0
	plhs[0] = mxCreateDoubleMatrix(n1, n2, mxREAL);
#else
	dims[0] = n1;
	dims[1] = n2;
	plhs[0] = mxCreateNumericArray(2, dims, category1, mxREAL);
#endif

	switch (category1)  {
		case mxSINGLE_CLASS:
			process_single(plhs, prhs, n1, n2);
			break;
		case mxDOUBLE_CLASS:
			process_double(plhs, prhs, n1, n2);
			break;
		case mxINT8_CLASS:
		case mxUINT8_CLASS:
		case mxINT16_CLASS:
		case mxUINT16_CLASS:
		case mxINT32_CLASS:
		case mxUINT32_CLASS:
		default:
			mxDestroyArray(plhs[0]);
			mexErrMsgTxt("Not supported data type for sqdist");
			break;
	}
}

void process_single(mxArray *plhs[], const mxArray *prhs[], int n1, int n2)
{
	int i;
	int div, mod, ii;
	float si;
	float *a, *b, *y;

	a = (float *)mxGetPr(prhs[0]);
	b = (float *)mxGetPr(prhs[1]);
	y = (float *)mxGetPr(plhs[0]);

	for (i = 0; i < n1*n2; i++) {
		div = i/n2;
		mod = i%n2;
		ii = div+mod*n1; 
		si = a[div]-b[mod];
		y[ii] = si*si;
	}
}


void process_double(mxArray *plhs[], const mxArray *prhs[], int n1, int n2)
{
	int i;
	int div, mod, ii;
	double si;
	double *a, *b, *y;

	a = mxGetPr(prhs[0]);
	b = mxGetPr(prhs[1]);
	y = mxGetPr(plhs[0]);

	for (i = 0; i < n1*n2; i++) {
		div = i/n2;
		mod = i%n2;
		ii = div+mod*n1; 
		si = a[div]-b[mod];
		y[ii] = si*si;
	}
}

