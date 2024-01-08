.PHONY: prepare all clean

all: prepare
	cmake -S . -B build && cd build && make && ./main && cd ..

prepare: clean
	mkdir build

clean:
	rm -rf build
