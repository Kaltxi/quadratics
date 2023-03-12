#include "runtime.hpp"
#include <iostream>

using namespace quadratics;

int main(const int count, char* args[]) {
  if (count <= 1) {
    std::cout << "No coefficients were supplied.\n"
              << "Try: `quadratics 1 2 -3`" << std::endl;

    return 0;
  }

  Runtime(count, args, 3)();

  return 0;
}