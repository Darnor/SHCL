# Spheric Harmonic Coefficient Library - SHCL
Home of the SHCL library code.

This software was created as part of a Student Research Projekt during the
fall semester of 2016.

## License
The SHCL Library is licensed under the GNU GPLv3 license.

## Dependencies
- FFTW3 library
- GSL Library
- OpenCL (1.2)
- pthread

## Supported platforms
Currently only Linux is supported.

Maybe it could also be used under Windows with Cygwin but this has not been tested.

## How to build
Run `make` or `make build` to build the SHCL library.

_Note: One can simply run `make install` which will also build the library if
not already done so._

## How to clean this directory
Run `make clean` to clean this directory.

## How to install
Run `make install` to install the library file and it's header files
to /usr/lib and /usr/include.

_Note: Requires root access._

_Note: The library and header install paths can be changed by setting
the LIB\_DIR and INCLUDE\_DIR macros when running `make install`._

## How to uninstall
To simply uninstall the software run `make uninstall`.

_Note: Requires root access._

## How to reinstall/update
Run `make update` to reinstall/update the library.

_Note: Requires root access to perform the uninstall and install process._

