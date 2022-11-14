// mexFunction.cpp : Defines the entry point for the DLL application.
//

#include "mex.h"
#include <pthread.h>
#include <unistd.h>

#include <sys/time.h>

double getwtime()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return (double)t.tv_sec + (double)t.tv_usec*1.0E-6;
}

void ComputePrimes(double* y, int n);
void *ComputePrimesThread(void *Param);
int IsPrime(int n);

pthread_mutex_t cs = PTHREAD_MUTEX_INITIALIZER;
pthread_t hThread[2];
long dwID[2];

double *g_y;
long g_n;
int global_index = 0;
int curr_i = 2;

void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{
	double t1, t2;

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
	x = mxGetScalar(prhs[0]);

	/* Create matrix for the return argument. */
	plhs[0] = mxCreateDoubleMatrix(mrows /* 1 */, (int) x, mxREAL);

	y = mxGetPr(plhs[0]);

	//call ComputePrimes subroutines to fill vector of primes
	t1 = getwtime();
#if defined(USE_THREADS)
#warning  "Using the multithreaded implementation"
	g_n = (int)x;
	g_y = y;

	dwID[0] = 0;
	dwID[1] = 1;
	pthread_create(&hThread[0], NULL, ComputePrimesThread, &dwID[0]);
	pthread_create(&hThread[1], NULL, ComputePrimesThread, &dwID[1]);

	pthread_join(hThread[0], NULL);
	pthread_join(hThread[1], NULL);
#else
#warning  "Using the sequential implementation"
	ComputePrimes(y, (int) x);
#endif
	t2 = getwtime();
	printf("Elapsed time = %lf secs\n", t2-t1);
}

void *ComputePrimesThread(void *Param)
{
	int index, i;
	double *y = g_y;
	int n = g_n;

	int myid = *(long *)Param;
	printf("Hello from thread %ld\n", myid);

	while (1) {
		pthread_mutex_lock(&cs);
		i = curr_i++;
		index = global_index;
		pthread_mutex_unlock(&cs);

		if (index != n)
		{
			printf("[%ld] Checking %d\n", myid, i);
			usleep(100*1000);

			if (IsPrime(i))
			{
				pthread_mutex_lock(&cs);
				if (global_index != n) {
					printf("[%ld] Storing Prime %d (index=%d)\n", myid, i, global_index);
					y[global_index]=i;
					global_index++;
					pthread_mutex_unlock(&cs);
				}
				else {
					pthread_mutex_unlock(&cs);
					break;
				}
			}
		}
		else
		{
			break;
		}
	}

	return 0;
}

void ComputePrimes(double* y, int n)
{
	int index=0, i=2;

	while (index!=n)
	{
		usleep(100*1000);
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
