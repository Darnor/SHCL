# Tools
GCC = g++
RM = rm
RMDIR = rm -r
CP = cp -R
SYMLINK = ln -s
PREBUILD_SCRIPT = ./prebuild/k2b.sh
DOXYGEN = doxygen
GIT = git
AS_ROOT = sudo

# GCC Flags
LIB_FLAG = -shared -fPIC
STD_FLAG = -std=c++14
VISIBILITY_FLAG = -fvisibility=hidden
OPTIMIZE_FLAG = -O3
WARNING_FLAG = -Wall -Wextra -Wconversion -Werror
PEDANTIC_FLAG = -pedantic -pedantic-errors

CXX_FLAGS = $(LIB_FLAG) $(STD_FLAG) $(VISIBILITY_FLAG) $(OPTIMIZE_FLAG) $(WARNING_FLAG) $(PEDANTIC_FLAG)

# Library dependencies
THREAD_LIB = -lpthread
MATH_LIB = -lm
GSL_LIB = -lgsl -lgslcblas
FFTW3_LIB = -lfftw3 -lfftw3_threads
OPENCL_LIB = -lOpenCL

DEPENDENCY_LIBS = $(THREAD_LIB) $(MATH_LIB) $(GSL_LIB) $(FFTW3_LIB) $(OPENCL_LIB)

# CPP implementation files
IMPL_FILE_DIR = ./src/shcl/internal/impl
ERROR_CPP = $(IMPL_FILE_DIR)/shcl_error.cpp
INFO_CPP = $(IMPL_FILE_DIR)/shcl_info.cpp
PLAN_CPP = $(IMPL_FILE_DIR)/shcl_plan.cpp
MEMORY_CPP = $(IMPL_FILE_DIR)/shcl_memory.cpp

CPP_FILES = $(ERROR_CPP) $(INFO_CPP) $(PLAN_CPP) $(MEMORY_CPP)

# Prebuild OpenCL to Binary file
OCL_TO_BINARY_H = ./src/ocl/shcl_ocl_binary.h

# Library headers
HEADER_DIR = ./include
INTERNAL_DIR = ./shcl
MAIN_LIB_FILE = shcl.h

# Docs directory
DOCS_DIR = ./docs

# Install directories
INCLUDE_DIR = /usr/include
LIB_DIR = /usr/lib

# Current library version
LIB_MAJOR_VERSION = 0
LIB_MINOR_VERSION = 1
LIB_PATCH_VERSION = 0

LIB_VERSION = $(LIB_MAJOR_VERSION).$(LIB_MINOR_VERSION).$(LIB_PATCH_VERSION)

# Library file name
LIB_FILE = libSHCL.so
LIB_FILE_FULL = $(LIB_FILE).$(LIB_VERSION)

.PHONY:	build prebuild install update gitupdate docs clean uninstall build

build:	prebuild $(LIB_FILE_FULL) docs

prebuild:
	$(PREBUILD_SCRIPT)

$(LIB_FILE_FULL):	$(CPP_FILES)
	$(GCC) $(CXX_FLAGS) -I$(HEADER_DIR) $^ -o $@ $(DEPENDENCY_LIBS)

install:	build
	$(AS_ROOT) $(CP) $(HEADER_DIR)/* $(INCLUDE_DIR)
	$(AS_ROOT) $(CP) $(LIB_FILE_FULL) $(LIB_DIR)
	$(AS_ROOT) $(SYMLINK) $(LIB_DIR)/$(LIB_FILE_FULL) $(LIB_DIR)/$(LIB_FILE)
	$(AS_ROOT) $(SYMLINK) $(LIB_DIR)/$(LIB_FILE_FULL) $(LIB_DIR)/$(LIB_FILE).$(LIB_MAJOR_VERSION)

update:	clean build uninstall install

docs:
	$(DOXYGEN)

clean:
	$(RM) $(LIB_FILE_FULL) $(OCL_TO_BINARY_H)
	$(RMDIR) $(DOCS_DIR)

uninstall:	uninstallheaders uninstalllib

uninstallheaders:
	$(AS_ROOT) $(RM) $(INCLUDE_DIR)/$(MAIN_LIB_FILE)
	$(AS_ROOT) $(RMDIR) $(INCLUDE_DIR)/$(INTERNAL_DIR)

uninstalllib:
	$(AS_ROOT) $(RM) $(LIB_DIR)/$(LIB_FILE) $(LIB_DIR)/$(LIB_FILE).$(LIB_MAJOR_VERSION) $(LIB_DIR)/$(LIB_FILE_FULL)

