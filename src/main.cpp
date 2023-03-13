#include "runtime.hpp"
#include <iostream>

using namespace quadratics;

int main(const int count, char* args[]) {
  // Program does heavy std::cout output, C stdio is not used
  std::ios_base::sync_with_stdio(false);

  if (count <= 1) {
    std::cout << "No coefficients were supplied.\n"
              << "Try: `quadratics 1 2 -3`" << std::endl;

    return 0;
  }

  Runtime(count, args, 3)();

  return 0;
}