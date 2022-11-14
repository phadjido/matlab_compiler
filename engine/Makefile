all: engdemo

engdemo: engdemo.c
	mex -client engine engdemo.c
	# gcc -o engdemo  engdemo.c -I/usr/local/MATLAB/R2017b/extern/include/ -L/usr/local/MATLAB/R2017b/bin/glnxa64  -lmx -lmex -lmat -lmwspmatrix -lmwmclmcr -leng


clean:
	rm -f engdemo
