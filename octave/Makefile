all: oct1 oct2 oct3 helloworld.oct hellomex.mex

oct1: oct1.cpp
	mkoctfile -v --link-stand-alone oct1.cpp -o oct1

oct2: oct2.cpp
	mkoctfile -v --link-stand-alone oct2.cpp -o oct2

oct3: oct3.cpp
	mkoctfile -v --link-stand-alone oct3.cpp -o oct3

helloworld.oct: helloworld.cpp
	mkoctfile helloworld.cpp 

hellomex.mex: hellomex.cpp
	mkoctfile -mex hellomex.cpp 

clean:
	rm -f oct1 oct2 oct3 helloworld.oct hellomex.mex *.o
