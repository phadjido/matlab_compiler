/*
 * MATLAB Compiler: 6.1 (R2015b)
 * Date: Mon Aug  1 22:23:06 2016
 * Arguments: "-B" "macro_default" "-W" "lib:libprime" "-T" "link:lib"
 * "callprimes.m" 
 */

#include <stdio.h>
#define EXPORTING_libprime 1
#include "libprime.h"

static HMCRINSTANCE _mcr_inst = NULL;


#ifdef __cplusplus
extern "C" {
#endif

static int mclDefaultPrintHandler(const char *s)
{
  return mclWrite(1 /* stdout */, s, sizeof(char)*strlen(s));
}

#ifdef __cplusplus
} /* End extern "C" block */
#endif

#ifdef __cplusplus
extern "C" {
#endif

static int mclDefaultErrorHandler(const char *s)
{
  int written = 0;
  size_t len = 0;
  len = strlen(s);
  written = mclWrite(2 /* stderr */, s, sizeof(char)*len);
  if (len > 0 && s[ len-1 ] != '\n')
    written += mclWrite(2 /* stderr */, "\n", sizeof(char));
  return written;
}

#ifdef __cplusplus
} /* End extern "C" block */
#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_libprime_C_API
#define LIB_libprime_C_API /* No special import/export declaration */
#endif

LIB_libprime_C_API 
bool MW_CALL_CONV libprimeInitializeWithHandlers(
    mclOutputHandlerFcn error_handler,
    mclOutputHandlerFcn print_handler)
{
    int bResult = 0;
  if (_mcr_inst != NULL)
    return true;
  if (!mclmcrInitialize())
    return false;
    {
        mclCtfStream ctfStream = 
            mclGetEmbeddedCtfStream((void *)(libprimeInitializeWithHandlers));
        if (ctfStream) {
            bResult = mclInitializeComponentInstanceEmbedded(   &_mcr_inst,
                                                                error_handler, 
                                                                print_handler,
                                                                ctfStream);
            mclDestroyStream(ctfStream);
        } else {
            bResult = 0;
        }
    }  
    if (!bResult)
    return false;
  return true;
}

LIB_libprime_C_API 
bool MW_CALL_CONV libprimeInitialize(void)
{
  return libprimeInitializeWithHandlers(mclDefaultErrorHandler, mclDefaultPrintHandler);
}

LIB_libprime_C_API 
void MW_CALL_CONV libprimeTerminate(void)
{
  if (_mcr_inst != NULL)
    mclTerminateInstance(&_mcr_inst);
}

LIB_libprime_C_API 
void MW_CALL_CONV libprimePrintStackTrace(void) 
{
  char** stackTrace;
  int stackDepth = mclGetStackTrace(&stackTrace);
  int i;
  for(i=0; i<stackDepth; i++)
  {
    mclWrite(2 /* stderr */, stackTrace[i], sizeof(char)*strlen(stackTrace[i]));
    mclWrite(2 /* stderr */, "\n", sizeof(char)*strlen("\n"));
  }
  mclFreeStackTrace(&stackTrace, stackDepth);
}


LIB_libprime_C_API 
bool MW_CALL_CONV mlxCallprimes(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "callprimes", nlhs, plhs, nrhs, prhs);
}

LIB_libprime_C_API 
bool MW_CALL_CONV mlfCallprimes(int nargout, mxArray** y, mxArray* n)
{
  return mclMlfFeval(_mcr_inst, "callprimes", nargout, 1, 1, y, n);
}

