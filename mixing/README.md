MIXING MATLAB AND C

Directory											:	Test Case
----------------------------------------------------------------------------------------------
1_magic												: file.m -> file.exe	
2_matrixdriver								: file1.c + file2.m -> file1.exe
3_matrixdriver_{threads,mpi}	:	pfile1.c + file2.m -> pfile1.exe
4_mex_demo										: file.mex -> file.dll , matlab + file.dll
5_standalone_mex_m						:	file1.mex -> file1.dll, file2.m + file1.dll -> file2.exe
6_standalone_c_mex_m					:	file1.c + file2.m + file3.mex ->file1.exe
7_standalone_mex_m_threads		:	pfile1.mex -> pfile1.dll , file2.m + pfile1.dll -> file2.exe
8_standalone_c_mex_m_threads	:	pfile1.c + file2.m + pfile3.mex -> pfile1.exe
9_standalone_c_mex_m_mpi			:	ppfile1.c + file2.m + pfile3.mex -> ppfile1.exe
	

Important note for cases (3, 8):
Calls from main program routine to functions in m-files have the following features:
1. They are executed by a separated matlab server thread.
2. They are called within the mclMlfFeval internal Matlab routine.
3. They are serialized, i.e. only one call is active at the same time. 
   However, the function in the m-file can call parallel code within a mex function call.
4. They can be called independently within separate mpi processes.


pfile: parallel code
.mex ≡ .c
.exe: executable 
.dll ≡ .so
 
