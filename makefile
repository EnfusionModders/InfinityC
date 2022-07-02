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
	mkdir -p build
	gcc -D_GNU_SOURCE -ldl -pthread -Wno-attributes -fPIC -fvisibility=hidden --shared -o build/infinityc.so -I src/ src/*.c