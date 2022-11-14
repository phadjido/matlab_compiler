set -e
set -x
cp ../4.mex_demo/ComputePrimes.mexa64 .
mcc -W lib:libprime -T link:lib callprimes.m
mbuild primedriver.c libprime.so # ComputePrimes.mexa64
