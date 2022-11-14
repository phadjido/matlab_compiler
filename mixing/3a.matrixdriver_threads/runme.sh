mcc -W lib:libmatrix -T link:lib addmatrix.m eigmatrix.m multiplymatrix.m
mbuild matrixdriver_threads.c libmatrix.so
