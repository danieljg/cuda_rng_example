all: cuda_rand cuda_rand_double

cuda_rand: source/cuda_rand.c
	nvcc source/cuda_rand.c -O0 -prec-div=true -prec-sqrt=true -lcurand -gencode=arch=compute_50,code=compute_50 -o cuda_rand

cuda_rand_double: source/cuda_rand_double.c
	nvcc source/cuda_rand_double.c -O0 -lcurand -gencode=arch=compute_50,code=compute_50 -o cuda_rand_double