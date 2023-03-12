#include "equationqueue.hpp"
#include "parser.hpp"
#include "solver.hpp"
#include <iostream>
#include <mutex>
#include <thread>

using namespace quadratics;

int main(const int count, char* args[]) {
  if (count <= 1) {
    std::cout << "No coefficients were supplied.\n"
              << "Try: `quadratics 1 2 -3`" << std::endl;

    return 0;
  }

  EquationQueue queue;
  std::mutex stdout_mutex;

  std::thread parser(Parser{Data{count, args}, queue});
  std::thread solver(Solver{queue, stdout_mutex});

  parser.join();
  solver.join();
}