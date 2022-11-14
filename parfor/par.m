% https://www.mathworks.com/help/parallel-computing/parfor.html
tic
n = 200;
A = 500;
a = zeros(1,n);
parfor (i = 1:n, 4)
    a(i) = max(abs(eig(rand(A))));
end
toc
