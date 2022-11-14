mcc -W lib:libmatrix -T link:lib addmatrix.m eigmatrix.m multiplymatrix.m
mbuild -I/opt/mpich/include matrixdriver_mpi.c libmatrix.lib  /opt/mpich/lib/libmpi.so
