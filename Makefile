build_s:
	gcc s_brownian.c -lfreeimage -o s_brownian

build_pth:
	gcc pth_brownian.c -lfreeimage -lpthread -o pth_brownian

build_omp:
	gcc omp_brownian.c -lfreeimage -fopenmp -o omp_brownian

run_s:
	time ./s_brownian

run_pth:
	time ./pth_brownian 4

run_omp:
	time ./omp_brownian 4