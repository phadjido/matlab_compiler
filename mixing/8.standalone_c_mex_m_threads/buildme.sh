set -e
set -x
cp mex/ComputePrimes.mexa64 .
mcc -W lib:libprime -T link:lib callprimes.m
mbuild pprimedriver.c libprime.so
# ComputePrimes.mexa64
