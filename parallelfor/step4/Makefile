all: test4

pdriver_seq.mexa64: pdriver_seq.c
	mex pdriver_seq.c 

test4: test4.m proutine.m pdriver_seq.mexa64
	mcc -m test4.m proutine.m

clean:
	rm -f test4 mccExcludedFiles.log readme.txt requiredMCRProducts.txt run_test4.sh pdriver_seq.mexa64
