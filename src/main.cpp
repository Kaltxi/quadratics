#include "runtime.hpp"
#include <iostream>

using namespace quadratics;

int main(const int arg_count, char* args[]) {
  // Program does heavy std::cout output, C stdio is not used
  std::ios_base::sync_with_stdio(false);

  if (arg_count <= 1) {
    std::cout << "No coefficients were supplied.\n"
              << "Try: `quadratics 1 2 -3`" << std::endl;

    return 0;
  }

  // Skipping the first arg which contains program's name
  Runtime(arg_count - 1, args + 1)();

  return 0;
}