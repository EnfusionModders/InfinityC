#
# InfinityC MakeFile
#	use 'make build' to build infinity.
#	Windows requires 'make' and 'gcc'.	
#

# variables

.PHONY: push
push:
	git add .
	git commit -m "new work done :)"
	git push


.PHONY: windows
windows:
	mkdir -p build
	gcc -D_WIN64 -Wl,-subsystem,windows --shared -o build/secur32.dll -I src/ src/*.c

.PHONY: linux
linux:
	# first we must build proc_maps_parser
	cd proc_maps_parser && \
	mkdir -p build && \
	gcc pmparser.c -I include/ -c -o build/pmparser.o && \
	ar rcs build/libpmparser.a build/pmparser.o
	# now we can build our library
	mkdir -p build
	gcc -ldl -pthread -Wno-attributes -fPIC --shared -o build/infinityc.so -I src/ src/*.c