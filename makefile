#
# InfinityC MakeFile
#	use 'make build' to build infinity.
#	Windows requires 'make' and 'gcc'.	
#



.PHONY: build
build:
ifeq ($(OS), Windows_NT)
	@echo "Building InfinityC for Windows"
	mkdir -p build
	gcc -D_WIN64 -Wl,-subsystem,windows --shared -o build/secur32.dll -I src/ src/*.c
else
	@ehco "Building InfinityC for Linux"
	mkdir -p build
	gcc -D_GNU_SOURCE -ldl -pthread -Wno-attributes -fPIC -fvisibility=hidden --shared -o build/infinityc.so -I src/ src/*.c
endif

.PHONY: clean
clean:
ifeq ($(OS), Windows_NT)
	@echo "Cleaning InfinityC for Windows"
	powershell.exe -c 'Remove-Item -Recurse -Confirm:$$false build'
else
	@echo "Cleaning InfinityC for Linux"
	rm -rf ./build
endif 

.PHONY: test
test:
ifeq ($(OS), Windows_NT)
	@echo "Testing InfinityC for Windows"
	mkdir -p build
	gcc -D_WIN64 -Wl,-subsystem,windows -o build/test.exe -I src/ -I tests/ tests/*c src/*c
	build/test.exe
else
	@echo "Testing InfinityC for Linux"
	mkdir -p build
	gcc -D_GNU_SOURCE -ldl -pthread -Wno-attributes -fPIC -fvisibility=hidden -e main -o build/test -I tests/ -I src/ tests/*.c src/*.c
	build/test
endif 

