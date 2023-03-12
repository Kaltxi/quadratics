cmake_minimum_required(VERSION 3.20)

project(quadratics
  VERSION 0.1.0
  DESCRIPTION "Solver for quadratic equations with integer coefficients"
  LANGUAGES CXX
)

# Add these to cmake to enable functionality
option(ENABLE_COVERAGE "Enable coverage reporting (gcc/clang)" FALSE)
option(ENABLE_ASAN "Enable address sanitizer" FALSE)
option(ENABLE_TESTING "Enable building tests" FALSE)
option(ENABLE_CLANG_TIDY "Enable testing with clang-tidy" FALSE)
option(ENABLE_CPPCHECK "Enable testing with cppcheck" FALSE)
option(FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (gcc/clang)" TRUE)

# Interface for options
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

if(ENABLE_COVERAGE)
  target_compile_options(project_options INTERFACE --coverage -O0 -g)
  target_link_libraries(project_options INTERFACE --coverage)
endif()

if(ENABLE_ASAN)
  target_compile_options(project_options INTERFACE -fsanitize=address)
  target_link_libraries(project_options INTERFACE -fsanitize=address)
endif()

# Interface for warnings
add_library(project_warnings INTERFACE)
target_compile_options(project_warnings INTERFACE
  -Wall
  -Wextra
  -Wshadow
  -Wnon-virtual-dtor
  -Wold-style-cast
  -Wcast-align
  -Wunused
  -Woverloaded-virtual
  -Wpedantic
  -Wconversion
  -Wsign-conversion
  -Wnull-dereference
  -Wdouble-promotion
  -Wformat=2
)

# GCC specific warnings
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  target_compile_options(project_warnings INTERFACE
    -Wmisleading-indentation
    -Wduplicated-cond
    -Wlogical-op
    -Wuseless-cast
  )
endif()

# CLI coloring for compiler 
if (${FORCE_COLORED_OUTPUT})
  if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options (project_options INTERFACE -fdiagnostics-color=always)
  elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options (project_options INTERFACE -fcolor-diagnostics)
  endif ()
endif ()

# Static analysis focused on bugs
if(ENABLE_CPPCHECK)
  find_program(CPPCHECK cppcheck)

  if(CPPCHECK)
    set(CMAKE_CXX_CPPCHECK
      ${CPPCHECK}
      --suppress=missingIncludeSystem
      --inconclusive)
    else()
      message(SEND_ERROR "cppcheck requested but executable not found")
  endif()
endif()

# Static analysis focused on best practices
if(ENABLE_CLANG_TIDY)
  find_program(CLANGTIDY clang-tidy)

  if(CLANGTIDY)
    set(CMAKE_CXX_CLANG_TIDY ${CLANGTIDY})
  else()
    message(SEND_ERROR "clang-tidy requested but executable not found")
  endif()
endif()

# Main library
add_library(quadratics
  src/quadratic.cpp
  src/equationqueue.cpp
  src/parser.cpp
  src/solver.cpp
)

target_include_directories(quadratics PRIVATE src)

target_link_libraries(quadratics
  PRIVATE
    project_options
    project_warnings
)

# CLI executable
add_executable(quadratics_exe
  src/main.cpp
)

set_property(TARGET quadratics_exe PROPERTY OUTPUT_NAME quadratics)

target_include_directories(quadratics_exe PRIVATE src)

target_link_libraries(quadratics_exe
  PRIVATE
    project_options
    project_warnings
    quadratics
)

# Tests
if(ENABLE_TESTING)
  enable_testing()
  find_package(doctest REQUIRED)
  include(CTest)
  include(doctest)

  add_executable(quadratics_test
    src/main.t.cpp
    src/quadratic.t.cpp
  )

  target_include_directories(quadratics_test PRIVATE src)

  target_link_libraries(quadratics_test PRIVATE
    doctest::doctest
    project_options
    project_warnings
    quadratics
  )

  doctest_discover_tests(quadratics_test)
endif()