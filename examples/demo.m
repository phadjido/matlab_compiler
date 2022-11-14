memusage_mex()
a=rand(1024,1024);
memusage_mex()
b=rand(1024,1024);
memusage_mex()

tic; sqdist(a,b); toc
tic; sqdist_mex(a,b); toc

a=rand(4,4)
b=rand(4,4)

[c, d]=demo_mex(a,b)
