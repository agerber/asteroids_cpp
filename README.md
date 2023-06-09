# Asteroids - CPP

## Build notes

### Dependencies
Qt > 6.x

[C++ Streams](https://github.com/jscheiny/Streams)

### Instructions

Please run this command first in project root to fetch dependencies:

```git submodule update --init```

### Windows
Use MinGW-based Qt and compiler toolchain to compile this project.

you have to make sure that cmake, mingw32-make and Qt binaries are in your
environment PATH like (```C:\msys64\mingw64\bin```)

then use these commands to build the project:

```
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
```

you can also use any cmake-based IDE like CLion to build the project

### MacOS
must run git submodule update --init --recursive

Install minimum Qt 6.6.0 to build for m1 silicon mac chip.

my current location of Qt is /Users/macbook/Qt

## Todo
Must implement streams + lambdas
