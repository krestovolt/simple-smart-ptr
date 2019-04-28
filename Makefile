SHELL := /bin/bash
RM    := rm -rf
MKDIR := mkdir -p
PROC := $(shell nproc)
OUTPUT_LIB := "smartalloc"
OUTPUT_COVERAGE := $(OUTPUT_LIB)_coverage.info
CMAKE_FLAGS := -DCODE_COVERAGE=ON \
							 -DCMAKE_BUILD_TYPE=Debug \
							 -DOUTPUT_LIB=$(OUTPUT_LIB)

all: ./build/Makefile
	@  echo "[INFO] Running build with $(PROC) cores"
	@  cd build && cmake --build . --config Debug -- -j $(PROC) && \
		 GTEST_COLOR=1 ctest -VV -j $(PROC) --output-on-failure
	@- lcov --base-directory . --directory . -c -o $(OUTPUT_COVERAGE)
	@- lcov --remove $(OUTPUT_COVERAGE) "/usr*" "*/build/*" -o $(OUTPUT_COVERAGE)
	@	 lcov --list $(OUTPUT_COVERAGE)

./build/Makefile:
	@  ($(MKDIR) build > /dev/null)
	@  (cd build > /dev/null 2>&1 && cmake $(CMAKE_FLAGS) ..)

libclean:
	@- $(RM) ./build/Makefile
	@- $(RM) ./build/src
	@- $(RM) ./build/test
	@- $(RM) ./build/CMake*
	@- $(RM) ./build/cmake.*
	@- $(RM) ./build/*.cmake
	@- $(RM) ./build/*.txt
	@- $(RM) ./build/lib/lib$(OUTPUT_LIB).a


distclean:
	@- (cd build >/dev/null 2>&1 && cmake .. >/dev/null 2>&1)
	@- $(MAKE) --silent -C build clean || true
	@- $(RM) ./build/Makefile
	@- $(RM) ./build/src
	@- $(RM) ./build/test
	@- $(RM) ./build/CMake*
	@- $(RM) ./build/cmake.*
	@- $(RM) ./build/*.cmake
	@- $(RM) ./build/*.txt
	@- $(RM) ./build/lib/lib$(OUTPUT_LIB).a

ifeq ($(filter $(MAKECMDGOALS), distclean libclean),)

    $(MAKECMDGOALS): ./build/Makefile
	@ $(MAKE) -C build $(MAKECMDGOALS)

endif
