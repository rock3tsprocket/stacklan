# Reference Stacklan interpreter in C

## Building

### Dependencies
- A standard C library
- C89 or later compiler

### Build configuration
You can configure the build to use a different compiler, or a cross-compiler:
- CC: Defaults to `${CROSS_COMPILE}cc`, specifies which compiler the build should use.
- CFLAGS: Defaults to `-g -O2`, specifies C compiler arguments.
- CROSS\_COMPILE: Defaults to nothing, specifies cross-compiler prefix.
- LDFLAGS: Defaults to nothing, specifies linker flags.
- PREFIX: Defaults to `/usr/local`, specifies installation prefix for the interpreter.

Examples:

- Regular build:
```
$ make
```
- Cross-compiling for GNU/Linux on armhf with -O3 optimizations:
```
$ make CROSS_COMPILE=arm-linux-gnueabihf- CC=arm-linux-gnueabihf-gcc CFLAGS="-O3"
```

### Installation
Examples:

- Regular installation (to /usr/local):
```
# make install
```

- Installation to /usr:
```
# make PREFIX=/usr install
```

## Language specification
The spec can be found in the `spec/` directory.

Example programs can be found in the [`examples/`](examples/) directory.

## Copyright
* This interpreter itself is licensed under the 3-clause BSD license (see [LICENSE.txt](LICENSE.txt))
* The Stacklan specification is licensed under the CC-BY 4.0 license (see [spec/LICENSE.txt](spec/LICENSE.txt))
* The example programs are licensed under the Unlicense (see [examples/UNLICENSE.txt](examples/UNLICENSE.txt))
