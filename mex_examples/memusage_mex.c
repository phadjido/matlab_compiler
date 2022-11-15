#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/resource.h>
#include <mex.h>
#include <matrix.h>


void report_host_memory_usage(double out[2])
{
	FILE * foutput = stdout;
	struct rusage rusage;
	long peak_rss;

	getrusage(RUSAGE_SELF, &rusage);
	peak_rss = rusage.ru_maxrss*1024;

	long rss = 0;
	FILE* fp = NULL;
	if ( (fp = fopen( "/proc/self/statm", "r" )) == NULL )
	{
		return;
	}

	if ( fscanf( fp, "%*s%ld", &rss ) != 1 )
	{
		fclose( fp );
		return;
	}
	fclose( fp );

	long current_rss;

	current_rss = rss * sysconf( _SC_PAGESIZE);

	long max_peak_rss, sum_peak_rss;
	long max_current_rss, sum_current_rss;

#if 0
	MPI_Reduce(&peak_rss, &max_peak_rss, 1, MPI_LONG, MPI_MAX, 0, comm);
	MPI_Reduce(&peak_rss, &sum_peak_rss, 1, MPI_LONG, MPI_SUM, 0, comm);
	MPI_Reduce(&current_rss, &max_current_rss, 1, MPI_LONG, MPI_MAX, 0, comm);
	MPI_Reduce(&current_rss, &sum_current_rss, 1, MPI_LONG, MPI_SUM, 0, comm);
#else
	max_peak_rss = peak_rss;
	sum_peak_rss = peak_rss;
	max_current_rss = current_rss;
	sum_current_rss = current_rss;
#endif

	int rank = 0;
#if 0
	MPI_Comm_rank(comm, &rank);
#endif

	if (rank == 0)
	{
#if 0
		fprintf(foutput, "> peak resident set size: max = %.2lf Mbytes sum = %.2lf Mbytes\n",
			max_peak_rss/(1024.0*1024.0), sum_peak_rss/(1024.0*1024.0));
		fprintf(foutput, "> current resident set size: max = %.2lf Mbytes sum = %.2lf Mbytes\n",
			max_current_rss/(1024.0*1024.0), sum_current_rss/(1024.0*1024.0));
#else
		mexPrintf("> peak resident set size: max = %.2lf Mbytes sum = %.2lf Mbytes\n",
			max_peak_rss/(1024.0*1024.0), sum_peak_rss/(1024.0*1024.0));
		mexPrintf("> current resident set size: max = %.2lf Mbytes sum = %.2lf Mbytes\n",
			max_current_rss/(1024.0*1024.0), sum_current_rss/(1024.0*1024.0));
#endif
	}

	out[0] = max_peak_rss/(1024.0*1024.0);
	out[1] = max_current_rss/(1024.0*1024.0);
}



void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	double rss[2];
	report_host_memory_usage(rss);

	mxArray *r_m;
	r_m = plhs[0] = mxCreateDoubleMatrix(1,2,mxREAL);
	double *r;
	r = mxGetPr(r_m);
	r[0] = rss[0];
	r[1] = rss[1];

	return;
}

