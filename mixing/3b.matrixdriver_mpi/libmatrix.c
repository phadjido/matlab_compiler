/*
 * MATLAB Compiler: 6.1 (R2015b)
 * Date: Mon Aug  1 18:21:52 2016
 * Arguments: "-B" "macro_default" "-W" "lib:libmatrix" "-T" "link:lib"
 * "addmatrix.m" "eigmatrix.m" "multiplymatrix.m" 
 */

#include <stdio.h>
#define EXPORTING_libmatrix 1
#include "libmatrix.h"

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
#ifndef LIB_libmatrix_C_API
#define LIB_libmatrix_C_API /* No special import/export declaration */
#endif

LIB_libmatrix_C_API 
bool MW_CALL_CONV libmatrixInitializeWithHandlers(
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
            mclGetEmbeddedCtfStream((void *)(libmatrixInitializeWithHandlers));
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

LIB_libmatrix_C_API 
bool MW_CALL_CONV libmatrixInitialize(void)
{
  return libmatrixInitializeWithHandlers(mclDefaultErrorHandler, mclDefaultPrintHandler);
}

LIB_libmatrix_C_API 
void MW_CALL_CONV libmatrixTerminate(void)
{
  if (_mcr_inst != NULL)
    mclTerminateInstance(&_mcr_inst);
}

LIB_libmatrix_C_API 
void MW_CALL_CONV libmatrixPrintStackTrace(void) 
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


LIB_libmatrix_C_API 
bool MW_CALL_CONV mlxAddmatrix(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "addmatrix", nlhs, plhs, nrhs, prhs);
}

LIB_libmatrix_C_API 
bool MW_CALL_CONV mlxEigmatrix(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "eigmatrix", nlhs, plhs, nrhs, prhs);
}

LIB_libmatrix_C_API 
bool MW_CALL_CONV mlxMultiplymatrix(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "multiplymatrix", nlhs, plhs, nrhs, prhs);
}

LIB_libmatrix_C_API 
bool MW_CALL_CONV mlfAddmatrix(int nargout, mxArray** a, mxArray* a1, mxArray* a2)
{
  return mclMlfFeval(_mcr_inst, "addmatrix", nargout, 1, 2, a, a1, a2);
}

LIB_libmatrix_C_API 
bool MW_CALL_CONV mlfEigmatrix(int nargout, mxArray** e, mxArray* a1)
{
  return mclMlfFeval(_mcr_inst, "eigmatrix", nargout, 1, 1, e, a1);
}

LIB_libmatrix_C_API 
bool MW_CALL_CONV mlfMultiplymatrix(int nargout, mxArray** m, mxArray* a1, mxArray* a2)
{
  return mclMlfFeval(_mcr_inst, "multiplymatrix", nargout, 1, 2, m, a1, a2);
}

