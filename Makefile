# Define the preset name (default or debug)
PRESET ?= release

# Conditionally set BUILD_DIR based on the value of PRESET
ifeq ($(PRESET), debug)
    BUILD_PRESET = Debug
else ifeq ($(PRESET), release)
    BUILD_PRESET = Release
else
    BUILD_PRESET = Release
endif

.PHONY: all configure build clean install

all: configure build install

configure:
	cmake --preset=$(PRESET)

build:
	cmake --build --preset=$(BUILD_PRESET)

install:
	cd build/dev; \
    cmake --install .

clean:
	rm -rf build