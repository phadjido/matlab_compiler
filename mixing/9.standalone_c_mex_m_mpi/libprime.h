/*
 * MATLAB Compiler: 6.1 (R2015b)
 * Date: Mon Aug  1 22:28:48 2016
 * Arguments: "-B" "macro_default" "-W" "lib:libprime" "-T" "link:lib"
 * "callprimes.m" 
 */

#ifndef __libprime_h
#define __libprime_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#ifdef __cplusplus
extern "C" {
#endif

#if defined(__SUNPRO_CC)
/* Solaris shared libraries use __global, rather than mapfiles
 * to define the API exported from a shared library. __global is
 * only necessary when building the library -- files including
 * this header file to use the library do not need the __global
 * declaration; hence the EXPORTING_<library> logic.
 */

#ifdef EXPORTING_libprime
#define PUBLIC_libprime_C_API __global
#else
#define PUBLIC_libprime_C_API /* No import statement needed. */
#endif

#define LIB_libprime_C_API PUBLIC_libprime_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_libprime
#define PUBLIC_libprime_C_API __declspec(dllexport)
#else
#define PUBLIC_libprime_C_API __declspec(dllimport)
#endif

#define LIB_libprime_C_API PUBLIC_libprime_C_API


#else

#define LIB_libprime_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_libprime_C_API 
#define LIB_libprime_C_API /* No special import/export declaration */
#endif

extern LIB_libprime_C_API 
bool MW_CALL_CONV libprimeInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_libprime_C_API 
bool MW_CALL_CONV libprimeInitialize(void);

extern LIB_libprime_C_API 
void MW_CALL_CONV libprimeTerminate(void);



extern LIB_libprime_C_API 
void MW_CALL_CONV libprimePrintStackTrace(void);

extern LIB_libprime_C_API 
bool MW_CALL_CONV mlxCallprimes(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);



extern LIB_libprime_C_API bool MW_CALL_CONV mlfCallprimes(int nargout, mxArray** y, mxArray* n);

#ifdef __cplusplus
}
#endif
#endif
