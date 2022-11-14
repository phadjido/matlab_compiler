set -e
set -x
cp ../4.mex_demo/ComputePrimes.mexa64 .
mcc -m CallPrim.m ComputePrimes.mexa64
