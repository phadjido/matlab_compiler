// mexFunction.cpp : Defines the entry point for the DLL application.
//

#include "mex.h"

void ComputePrimes(double* y, int n);
int IsPrime(int n);

void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{
	if (nrhs != 1) 
	{
		mexErrMsgTxt("One input required.");
	} 
	else if (nlhs > 1) 
	{
		mexErrMsgTxt("Too many output arguments");
	}	

	/* The input must be a noncomplex scalar integer.*/
	int mrows, ncols;
	mrows = mxGetM(prhs[0]);
	ncols = mxGetN(prhs[0]);
	
	if (!mxIsDouble(prhs[0]) || mxIsComplex(prhs[0]) || 
		!(mrows == 1 && ncols == 1)) 
	{
		mexErrMsgTxt("Input must be a noncomplex scalar integer.");
	}

	double x, *y;
	/*
		e.g.   
				*x=4,
				*y=2, 3, 5, 7
	*/
	
	x = mxGetScalar(prhs[0]);
		
	/* Create matrix for the return argument. */
	plhs[0] = mxCreateDoubleMatrix(mrows /* 1 */, (int) x, mxREAL);

	y = mxGetPr(plhs[0]);
	
	//call ComputePrimes subroutines to fill vector of primes
	ComputePrimes(y, (int) x);	
}

void ComputePrimes(double* y, int n)
{
	int index=0, i=2;


	while (index!=n)
	{
		if (IsPrime(i))
		{
			y[index]=i;
			index++;
		}

		i++;
	}
}

//return TRUE if n is a prime number
int IsPrime(int n)
{
	for (int i=2; i<=n/2; i++)
	{
		if (n%i==0)
			return 0;
	}

	return 1;
}
