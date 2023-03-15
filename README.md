# Quadratics

_Quadratics_ is a solver for quadratic equations with integer coefficients, utilizing multithreading capabilities of the hardware.

## Usage

Simply call the program and specify coefficients as command line arguments:

```sh
> ./quadratics [args]
```

## Features

- Solves quadratic equations
  ```sh
  > ./quadratics 1 -5 6
  (1 -5 6) => (2.000000,3.000000) Xmin=2.500000
  ```
- Finds extremums for true-quadratics (ignoring linear functions)

  ```sh
  > ./quadratics 1 4 -5
  (1 4 -5) => (-5.000000,1.000000) Xmin=-2.000000
  > ./quadratics 0 1 2
  (0 1 2) => (-2.000000) Xmin=-2.000000
  ```

- Processes many sets of parameters by treys in a multithreaded fashion, if a
  particular trey is ill-formed, it is ignored
  ```sh
  > ./quadratics 0 1 2 1 -5 6 as df 5 1 4 -5
  (0 1 2) => (-2.000000) Xmin=-2.000000
  (1 4 -5) => (-5.000000,1.000000) Xmin=-2.000000
  (1 -5 6) => (2.000000,3.000000) Xmin=2.500000
  ```

## Implementation

- Uses Object-Oriented Design
- Multithreading is implemented with Consumer-Producer pattern, with producer
  parsing the command line arguments and consumer solving the equations and
  outputting the results

## Observations and possible improvements

- As per specification, the program to use command line args, which limits the
  size of input. A better approach would be to also allow reading from standard
  input stream for processing of large dataset files.
- The simplicity of the task makes the threading an overkill, a sequential
  solution is significantly faster when it is passed little data, as spinning
  up threads and allocating memory for them is very expensive.
- On Linux threaded approach yields about 30% performance on larger datasets
  (1000 equations), but on Windows, with limited testing, the price for spinning
  up thread seems astronomical, and threading is extremely slow.
- Looking at profiler, it seems that the most cycles are spent on
  `std::to_string` converting the solution roots. Parsing is a small load, which
  makes sense, since we're using command-line arguments, and they are already
  in memory.
- For Linux the optimal number of solver threads seems to be around the number of
  actual hardware cores. I leave auto detection to use logical core, but perhaps
  halving this number will be a good decision, more testing is needed.

## Building

To build the binary you will need `CMake` version 3.20 or later, C++17-compliant
compiler and a build system, for example `Ninja`:

```sh
# Generate build system script
> cmake -DCMAKE_BUILD_TYPE:STRING=Release -B./build

# Build the binary
> cmake --build ./build --config Release --target quadratics_exe --
```

## Testing

To build additional utilities like `quadratics_gen` for test data generation you
can supply additional targets to `cmake` or build them all.

```sh
# Build all targets including `quadratics_gen`
> cmake --build ./build --config Release --target all --
> ./build/quadratics_gen 3
 -2 -58 -94 3 11 61 -75 -42 55
```

Additional options are available for testing and analysis that can be supplied
to `Cmake` with `-D` prefix:

- `ENABLE_COVERAGE` for code coverage
- `ENABLE_ASAN` for address sanitizer
- `ENABLE_TSAN` for thread sanitizer
- `ENABLE_TESTING` for unit tests
- `ENABLE_CLANG_TIDY` for `clang-tidy` static analysis
- `ENABLE_CPPCHECK` for `cppcheck` static analysis
- `FORCE_COLORED_OUTPUT` for compiler colored input (enabled by default)

> Note that for tests `doctest` library needs to be installed and findable by
> `CMake`. For example, it can be installed with `vcpkg`, don't forget to supply
> `-DCMAKE_TOOLCHAIN_FILE:STRING=<path>/vcpkg/scripts/buildsystems/vcpkg.cmake`
> to `CMake` during build system script generation to for it to discover the
> libraries.

For example:

```sh
# Build tests and run them
> cmake -DCMAKE_BUILD_TYPE:STRING=Release -DENABLE_TESTING:BOOL=TRUE -B./build
> cmake --build ./build --config Release --target quadratics_test --
> ./build/quadratics_test

[doctest] doctest version is "2.4.9"
[doctest] run with "--help" for options
===============================================================================
[doctest] test cases:  5 |  5 passed | 0 failed | 0 skipped
[doctest] assertions: 12 | 12 passed | 0 failed |
[doctest] Status: SUCCESS!
```
