install: build
	cd build; \
    cmake --install .
build:
	cmake -S . -B build; \
	cmake --build build

clean:
	rm -rf build
