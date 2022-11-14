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
#include <mpi.h>

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
#include "libmatrix.h"

/* This function is used to display a double matrix stored in an mxArray */
void display(const mxArray* in);

mxArray *in1, *in2; /* Define input parameters */
mxArray *out = NULL;/* and output parameters to be passed to the library functions */

void * ThreadOne(void *lpParam)
{
	mxArray *out = NULL;/* and output parameters to be passed to the library functions */

	printf("Hello from thread %ld\n", (unsigned long)pthread_self());

    /* Call the library function */
    mlfAddmatrix(1, &out, in1, in2);
    /* Display the return value of the library function */
    printf("The value of added matrix is:\n");
    display(out);

    /* Destroy the return value since this varaible will be resued in
     * the next function call. Since we are going to reuse the variable,
     * we have to set it to NULL. Refer to MATLAB Compiler documentation
     * for more information on this. */
    mxDestroyArray(out); out=0;

	return 0;
}

void *ThreadTwo(void *lpParam)
{
	mxArray *out = NULL;/* and output parameters to be passed to the library functions */

	printf("Hello from thread %ld\n", (unsigned long)pthread_self());

    mlfMultiplymatrix(1, &out, in1, in2);
    printf("The value of the multiplied matrix is:\n");
    display(out);
    mxDestroyArray(out); out=0;

	return 0;
}


void *ThreadThree(void *lpParam)
{
	mxArray *out = NULL;/* and output parameters to be passed to the library functions */

	printf("Hello from thread %ld\n", (unsigned long)pthread_self());

    mlfEigmatrix(1, &out, in1);
    printf("The Eigen value of the first matrix is:\n");
    display(out);
    mxDestroyArray(out); out=0;
}

int main(int argc, char *argv[]){
	double t1, t2;
	double gt0;
	int Me, Procs;
    
    double data[] = {1,2,3,4,5,6,7,8,9};

    /* Call the mclInitializeApplication routine. Make sure that the application
     * was initialized properly by checking the return status. This initialization
     * has to be done before calling any MATLAB API's or MATLAB Compiler generated
     * shared library functions.  */

	gt0 = getwtime();
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &Me);
	MPI_Comm_size(MPI_COMM_WORLD, &Procs);

	printf("Hello from %d of %d (at %ld) [gt0 = %ld]\n", Me, Procs, getwtime()-gt0, gt0);

	t1 = getwtime();
    if( !mclInitializeApplication(NULL,0) )
    {
        fprintf(stderr, "Could not initialize the application.\n");
        exit(1);
    }
    t2 = getwtime();
	printf("Initialization: %d msec (at %ld)\n", t2-t1, getwtime()-gt0);

    /* Create the input data */
	t1 = getwtime();
    in1 = mxCreateDoubleMatrix(3,3,mxREAL);
    in2 = mxCreateDoubleMatrix(3,3,mxREAL);
    memcpy(mxGetPr(in1), data, 9*sizeof(double));
    memcpy(mxGetPr(in2), data, 9*sizeof(double));
	t2 = getwtime();
	printf("Create input data: %d msec (at %ld)\n", t2-t1, getwtime()-gt0);
    
    /* Call the library intialization routine and make sure that the
     * library was initialized properly. */

	t1 = getwtime();
    if (!libmatrixInitialize()){
        fprintf(stderr,"Could not initialize the library.\n");
        exit(1);
    }
	t2 = getwtime();

	printf("Library initialization: %d msec (at %ld)\n", t2-t1, getwtime()-gt0);

	MPI_Barrier(MPI_COMM_WORLD);

	ThreadOne(0);
	sleep(5);
	MPI_Barrier(MPI_COMM_WORLD);
	ThreadTwo(0);
	sleep(5);
	MPI_Barrier(MPI_COMM_WORLD);
	ThreadThree(0);
	sleep(5);
	MPI_Barrier(MPI_COMM_WORLD);

    /* Call the library termination routine */
    libmatrixTerminate();
    
    /* Free the memory created */
    mxDestroyArray(in1); in1=0;
    mxDestroyArray(in2); in2 = 0;
    mclTerminateApplication();

	MPI_Barrier(MPI_COMM_WORLD);
	printf("Goodbye from %d of %d (at %ld)\n", Me, Procs, getwtime()-gt0);
	MPI_Finalize();
    return 0;
}


/*DISPLAY This function will display the double matrix stored in an mxArray.
 * This function assumes that the mxArray passed as input contains double
 * array.
 */
void display(const mxArray* in)
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
    for( i = 0; i < c; i++ ){
        for( j = 0; j < r; j++){
            printf("%4.2f\t",data[i*c+j]);
        }
        printf("\n");
    }
    printf("\n");
}
