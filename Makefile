SHELL := /bin/bash
RM    := rm -rf
MKDIR := mkdir -p
STATIC_LIB_NAME := "smartalloc"

all: ./build/Makefile
	@ $(MAKE) -C build

./build/Makefile:
	@  ($(MKDIR) build > /dev/null)
	@  (cd build > /dev/null 2>&1 && cmake -DOUTPUT_LIB=$(STATIC_LIB_NAME) ..)

libclean:
	@- $(RM) ./build/Makefile
	@- $(RM) ./build/src
	@- $(RM) ./build/test
	@- $(RM) ./build/CMake*
	@- $(RM) ./build/cmake.*
	@- $(RM) ./build/*.cmake
	@- $(RM) ./build/*.txt
	@- $(RM) ./build/lib/lib$(STATIC_LIB_NAME).a


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
	@- $(RM) ./build/lib/lib$(STATIC_LIB_NAME).a

ifeq ($(filter $(MAKECMDGOALS), distclean libclean),)

    $(MAKECMDGOALS): ./build/Makefile
	@ $(MAKE) -C build $(MAKECMDGOALS)

endif
