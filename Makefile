build_s:
	gcc s_brownian.c -lfreeimage -o s_brownian

build_pth:
	gcc pth_brownian.c -lfreeimage -lpthread -o pth_brownian

run_s:
	time ./s_brownian

run_pth:
	time ./pth_brownian
	convert -rotate "90" brownian_tree1.bmp brownian_tree1r.bmp
	convert -rotate "180" brownian_tree2.bmp brownian_tree2r.bmp
	convert -rotate "270" brownian_tree3.bmp brownian_tree3r.bmp
	convert brownian_tree0.bmp brownian_tree1r.bmp -append brownian_tree_right.bmp
	convert brownian_tree3r.bmp brownian_tree2r.bmp -append brownian_tree_left.bmp
	convert brownian_tree_left.bmp brownian_tree_right.bmp +append brownian_tree_pth.bmp
	rm brownian_tree0.bmp brownian_tree1.bmp brownian_tree1r.bmp brownian_tree2.bmp brownian_tree2r.bmp brownian_tree3.bmp brownian_tree3r.bmp brownian_tree_right.bmp brownian_tree_left.bmp

