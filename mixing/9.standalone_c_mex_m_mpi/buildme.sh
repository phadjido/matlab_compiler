set -e
set -x
# cp mex/ComputePrimes.mexa64 .
# mcc -W lib:libprime -T link:lib callprimes.m
mbuild -I/usr/include/x86_64-linux-gnu/mpich pprimedriver_mpi.c libprime.so  /usr/lib/x86_64-linux-gnu/libmpich.so

