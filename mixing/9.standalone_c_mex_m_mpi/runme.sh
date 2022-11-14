mcc -W lib:libprime -T link:lib callprimes.m
mbuild -I"c:\program files\deinoMPI\include" -Ic:\pthread\include pprimedriver_mpi.c libprime.lib c:\pthread\lib\pthreadVC.lib "c:\program files\deinompi\lib\mpi.lib"

