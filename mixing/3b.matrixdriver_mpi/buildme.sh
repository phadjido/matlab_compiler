# $ mpicc.mpich -show
# gcc -Wl,-Bsymbolic-functions -Wl,-z,relro -I/usr/include/x86_64-linux-gnu/mpich -L/usr/lib/x86_64-linux-gnu -lmpich


mcc -W lib:libmatrix -T link:lib addmatrix.m eigmatrix.m multiplymatrix.m
mbuild -I/usr/include/x86_64-linux-gnu/mpich matrixdriver_mpi.c libmatrix.so  /usr/lib/x86_64-linux-gnu/libmpich.so
