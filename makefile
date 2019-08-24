.PHONY: all test
all: emtest.html

emtest.html : emtest.c
	emcc $^ --emrun -o $@
	#--preload-file data --exclude-file *.blend
	#-s TOTAL_MEMORY=33554432
	#--js-library library.js -DUSE_CANVAS

test:
	emrun emtest.html
	
clean:
	rm emtest.html emtest.js