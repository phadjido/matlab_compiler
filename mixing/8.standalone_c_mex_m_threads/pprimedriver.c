/*=================================================================
 *
 * MATRIXDRIVER.C	Sample driver code that calls the shared
 *	        library created using MATLAB Compiler. Refer to the 
 *          documentation of MATLAB Compiler for more information on
 *          this
 *
 * This is the wrapper C code to call a shared library created 
 * using MATLAB Compiler.
 *
 * Copyright 1984-2000 The MathWorks, Inc.
 *
 *=================================================================*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include <sys/time.h>

double getwtime()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return (double)t.tv_sec + (double)t.tv_usec*1.0E-6;
}

/* Include the MCR header file and the library specific header file 
 * as generated by MATLAB Compiler */
#include "mclmcr.h" 
#include "libprime.h"

/* This function is used to display the primes stored in an mxArray */
void display_vector(const mxArray* in);

double gt0;

struct Work_t {
	mxArray *in, *out;
	int id;
};

void *ThreadDriverRoutine(void *arg)
{
	struct Work_t *work = (struct Work_t *) arg;
	int id = work->id;

	printf("[%d] Hello work from thread (%lf)\n", id, getwtime()-gt0); fflush(0);

	mlfCallprimes(1, (mxArray **)work->out, work->in);/* This function is called by a separate Matlab server thread,
						which means that it make no sense to be called in parallel!!!
						mlfCallprimes calls the generic routine mclMlfFeval */

	printf("[%d] Goodbye work from thread (%lf)\n", id, getwtime()-gt0); fflush(0);

	return 0;
}

int main(){
	double t1, t2;    
	mxArray *in1, *in2; /* Define input parameters */
	mxArray *out1 = NULL, *out2 = NULL;/* and output parameters to be passed to the library functions */
	double data1 = 6, data2 = 8;
	pthread_t hThread[2]; 
	struct Work_t work[2];

	if( !mclInitializeApplication(NULL,0) )
	{
		fprintf(stderr, "Could not initialize the application.\n");
		exit(1);
	}
    
	/* Create the input data */
	in1 = mxCreateDoubleMatrix(1,1,mxREAL);
	memcpy(mxGetPr(in1), &data1, 1*sizeof(double));

	in2 = mxCreateDoubleMatrix(1,1,mxREAL);
	memcpy(mxGetPr(in2), &data2, 1*sizeof(double));

	if (!libprimeInitialize()){
		fprintf(stderr,"Could not initialize the library.\n");
		exit(1);
	}

	/* Call the library function */
	gt0 = getwtime();
	printf("[%d] Creating two threads (%d)\n", -1, 0);
	t1 = getwtime();
#if 1
	work[0].in = in1;
	work[0].out = (mxArray *)&out1;
	work[0].id = 0;

	pthread_create(&hThread[0], NULL, ThreadDriverRoutine, &work[0]);

	work[1].in = in2;
	work[1].out = (mxArray *)&out2;
	work[1].id = 1;

	pthread_create(&hThread[1], NULL, ThreadDriverRoutine, &work[1]);

	pthread_join(hThread[0], NULL);
	pthread_join(hThread[1], NULL);
#else
	mlfCallprimes(1, &out1, in1);
	mlfCallprimes(1, &out2, in2);
#endif
	t2 = getwtime();

	printf("[%d] Elapsed Time = %lf secs\n", -1, t2-t1);

	/* Display the return value of the library function */
	printf("The 1st vector of primes is:\n");
	display_vector(out1);

	printf("The 2nd vector of primes is:\n");
	display_vector(out2);

	mxDestroyArray(out1); out1=0;
	mxDestroyArray(out2); out2=0;

	/* Call the library termination routine */
	libprimeTerminate();

	/* Free the memory created */
	mxDestroyArray(in1); in1=0;
	mxDestroyArray(in2); in2=0;
	mclTerminateApplication();

	return 0;
}


void display_vector(const mxArray* in)
{
    int i=0, j=0; /* loop index variables */
    int r=0, c=0; /* variables to store the row and column length of the matrix */
    double *data; /* variable to point to the double data stored within the mxArray */

    /* Get the size of the matrix */
    r = mxGetM(in);
    c = mxGetN(in);

    /* Get a pointer to the double data in mxArray */
    data = mxGetPr(in);

    /* Loop through the data and display the same in matrix format */
    for( i = 0; i < c; i++ ) {
			printf("%4.2f\t",data[i]);
    }
    printf("\n");
}
